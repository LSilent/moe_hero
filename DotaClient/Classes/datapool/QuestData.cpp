#include "./datapool/QuestData.h" 
#include "./base/UtilTools.h"

Quest::Quest()
{
	m_MissionID = -1;
	m_Status = MISSION_STATUS_INVALID;
	memset(m_Param,0,sizeof(m_Param));
}
bool Quest::setServerData( const MissionData* pData)
{
	if (!pData)return false;
	m_MissionID = pData->m_MissionID;
	m_Status = pData->m_Status;

	for (X_INT i = 0;i<MAX_MISSION_PARAM_COUNT;i++)
	{
		m_Param[i] = pData->m_Param[i];
	}
 
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_QUEST);
	if (pDataFile)
	{
		 m_pTableData = (const stDBC_FILE_QUEST*)pDataFile->GetFieldsByIndexKey(m_MissionID);
	}
	return m_pTableData !=X_NULL;
}
X_INT Quest::getAwardgold()const
{
	return m_pTableData->awardgold;
}
X_INT Quest::getAwardAction()const
{
	return m_pTableData->awardAction;
}
X_CHAR* Quest::getIcon()const
{
	return m_pTableData->icon;
}
X_INT Quest::getCopySceneId()const
{
	return m_pTableData->copyscene;
}
X_INT Quest::getNum()const
{
	return m_pTableData->num;
}
X_INT Quest::getDoneNum()const
{
	return m_Param[0];
}
X_CHAR* Quest::getDesc()const
{
	return m_pTableData->desc;
}
X_VOID Quest::GetDropItems(vector<X_INT>& items,vector<X_INT>& itemNums)const
{
		items.clear();itemNums.clear();
		UtilTools::ConvertStringToIntVector(m_pTableData->item,items,"|");
		UtilTools::ConvertStringToIntVector(m_pTableData->itemNum,itemNums,"|");
}

X_VOID QuestData::Initial()
{
	m_bAsked = false;
	m_bNewFlag = 0;
	m_Quest.clear();

}
X_VOID QuestData::Release()
{
	m_bNewFlag = 0;
	X_UINT size = m_Quest.size();
	for (X_UINT i =0;i<size;i++)
	{
		SAFE_DELETE(m_Quest[i]);
	}
	m_Quest.clear();
}
X_VOID QuestData::setServerData( const MissionData* pData)
{
	if (!pData)return;
	 Quest * pQuest = getQuestbyId(pData->m_MissionID);
	 if (pQuest)
	 {
		 if(!pQuest->setServerData(pData))
		 {
			 vector<Quest*>::iterator ifind= find(m_Quest.begin(),m_Quest.end(),pQuest);
			 if (ifind!= m_Quest.end())
			 {
				 m_Quest.erase(ifind);
			 }
		 } 
	 }

}
X_VOID QuestData::sortData()
{
	std::sort(m_Quest.begin(),m_Quest.end(),__dataSort1);
}
Quest * QuestData::getQuestbyId(X_INT id)
{
	X_UINT size = m_Quest.size();
	Quest * pQuest = X_NULL;
	for (X_UINT i =0;i<size;i++)
	{
		pQuest = m_Quest[i];
		 if (!pQuest)continue;
		 if (pQuest->m_MissionID == id)
		 {
			  return pQuest;
		 }
	}
	 
	 pQuest = new Quest();
	 m_Quest.push_back(pQuest);
	
	 return pQuest;
}
bool	QuestData::__dataSort1(const Quest *p1,const Quest *p2)
{
	MISSION_STATUS d1 = p1->getStatus();
	MISSION_STATUS d2 = p2->getStatus();

	X_INT id1 = p1->getId();
	X_INT id2 = p2->getId();
		//MISSION_STATUS_NOT_ACCEPT,		//=0  未接
		//MISSION_STATUS_NOT_COMPLETE,	//=1  已接未完成
		//MISSION_STATUS_NOT_SUBMIT,		//=2  完成未交
		//MISSION_STATUS_FAIL,			//=3  失败
		//MISSION_STATUS_DONE,			//=4  完成已交

	if(d1 == MISSION_STATUS_NOT_SUBMIT || d2 == MISSION_STATUS_NOT_SUBMIT  )
	{
		if (d2== d1)
		{
			return id1 > id2;
		}else
		{
			return d1 == MISSION_STATUS_NOT_SUBMIT;
		}
	}

	if(d1 == MISSION_STATUS_NOT_COMPLETE || d2 == MISSION_STATUS_NOT_COMPLETE  )
	{
		if (d2== d1)
		{
			return id1 > id2;
		}else
		{
			return d1 == MISSION_STATUS_NOT_COMPLETE;
		}
	}
	if(d1 == MISSION_STATUS_DONE || d2 == MISSION_STATUS_DONE  )
	{
		if (d2== d1)
		{
			return id1 > id2;
		}else
		{
			return d1 == MISSION_STATUS_DONE;
		}
	}
	return false;
}
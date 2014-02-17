#include "./datapool/AchievementData.h"
#include "./object/Item.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"
#include "./Packets/Other/GCRetAchievementPacket.h"

 

Achieve::Achieve()
{
	pData = X_NULL;
}
bool Achieve::setId(X_INT id)
{
	m_AchieveID = id;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE);
	pData = X_NULL;
	if (pDataFile)
	{
		 pData = (const stDBC_FILE_ACHIEVE*)pDataFile->GetFieldsByIndexKey(m_AchieveID);
		 if (pData)
		 {
			 return true;
		 }
	}
	return false;
}
X_INT    Achieve::getAllTimes()const
{
	if (!pData)
	{
		return 100;
	}
	if ( pData->type ==EM_ACHIEVE_TYPE_HERO_COUNT || pData->type == EM_ACHIEVE_TYPE_NEWHAND_HEROCOLR_COUNT)
	{
		return pData->param2;
	}
	else if(pData->type == EM_ACHIEVE_TYPE_SCENEGROUP || pData->type == EM_ACHIEVE_TYPE_SCENEGROUP_STAR5)
	{
		 return 1;
	}
	 return pData->param1;
}

const X_CHAR * Achieve::getIcon()const
{
	return pData->icon;
}
const X_CHAR * Achieve::getName()const
{
	return pData->name;
}
string Achieve::getDesc()const
{
	string str = pData->desc;
	if ( str != "-1")
	{
		return str;
	}
	return "";
}
X_VOID     Achieve::getItemNum(vector<X_INT>& num)const
{
	num.clear();
	UtilTools::ConvertStringToIntVector(pData->itemnum,num,"|");

}
X_VOID     Achieve::getItemId(vector<X_INT>& id)const
{
	id.clear();
	UtilTools::ConvertStringToIntVector(pData->item,id,"|");
}
void  AchievementData::__addAchieveToGroup(const Achieve* pData)
{
	if (!pData)
	{
		return;
	}
	X_INT group = pData->pData->group;
	
	const  DataBase* pDataFile_Group  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE_GROUP);
	const stDBC_FILE_ACHIEVE_GROUP	*  pTableData_Group = X_NULL;
	
	ACHIEVES::iterator ib = m_AchievesMap.begin();
	for (;ib != m_AchievesMap.end();++ib)
	{
		pTableData_Group = (const stDBC_FILE_ACHIEVE_GROUP*)pDataFile_Group->GetFieldsByIndexKey(ib->first);
		if (!pTableData_Group)
		{
			continue;
		}
		vector<X_INT> vec; vec.clear();
		UtilTools::ConvertStringToIntVector(pTableData_Group->group,vec,"|");
		if (UtilTools::findInVector(group,vec) != -1)
		{
			ib->second.push_back(pData);
		}
	}
}
string AchievementData::sortKey = "";
X_VOID AchievementData::Initial()
{
	m_DoneNum.clear();
	m_AchievesMap.clear();

	const  DataBase* pDataFile_Group  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE_GROUP);
	const stDBC_FILE_ACHIEVE_GROUP	*  pTableData_Group = X_NULL;
	X_UINT num = pDataFile_Group->GetRecordsNum();
	 
	for (X_UINT i = 0;i< num ;i++)
	{
		pTableData_Group = (const stDBC_FILE_ACHIEVE_GROUP*)pDataFile_Group->GetFieldsByLineNum(i);
		if (!pTableData_Group)
		{
			continue;
		}
		m_AchievesMap[pTableData_Group->id].clear();
		m_DoneNum[pTableData_Group->id] = 0;
	}
	  
	m_Achieves.clear();

	/*const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE);
	const stDBC_FILE_ACHIEVE	*  pTableData = X_NULL;
	 num = pDataFile->GetRecordsNum();
	for (X_UINT i = 0;i< num ;i++)
	{
		pTableData = (const stDBC_FILE_ACHIEVE*)pDataFile->GetFieldsByLineNum(i);
		if (!pTableData)
		{
			continue;
		}
		Achieve * pdata = new Achieve();
		bool b = pdata->setId(pTableData->id);
		pdata->m_Status = EM_ACHIEVE_STATUS_INVALID;
		pdata->m_Times = 0;
		if (b)
		{
			m_Achieves.push_back(pdata);
			__addAchieveToGroup(pdata);
		}
	}*/
}
Achieve* AchievementData::getData(X_INT id)
{
	X_UINT size = m_Achieves.size();
	Achieve *pData= 0;
	for (X_UINT i = 0;i<size ;i++)
	{
		 pData = m_Achieves[i];
		 if (pData&&pData->getId() == id )
		 {
			 return pData;
		 }
	}
	return 0 ;
}
X_VOID AchievementData::Release()
{
	X_UINT size = m_Achieves.size();
	for (X_UINT i = 0;i<size ;i++)
	{
		SAFE_DELETE(m_Achieves[i]);
	}
	m_Achieves.clear();
	m_AchievesMap.clear();
	m_DoneNum.clear();
}

X_VOID AchievementData::Reset()
{
	X_UINT size = m_Achieves.size();
	for (X_UINT i = 0;i<size ;i++)
	{
		SAFE_DELETE(m_Achieves[i]);
	}
	m_Achieves.clear();
	ACHIEVES::iterator ib = m_AchievesMap.begin();
	for (;ib != m_AchievesMap.end();++ib)
	{
		 ib->second.clear();
	}
 
	 
}
X_VOID AchievementData::AddData(const AchieveData*   data)
{
	if (!data)return;
	Achieve *pData  =   getData(data->m_AchieveID);
	if (!pData)
	{
		pData = new Achieve();
		bool b = pData->setId(data->m_AchieveID);
		if (b)
		{
			m_Achieves.push_back(pData);
			__addAchieveToGroup(pData);
		}
	}
	pData->m_Status = data->m_Status;
	pData->m_Times = data->m_Times;
	__onAchieveStatsChange();
}
void  AchievementData::__onAchieveStatsChange()
{ 

	const  DataBase* pDataFile_Group  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE_GROUP);
	const stDBC_FILE_ACHIEVE_GROUP	*  pTableData_Group = X_NULL;
	 
	ACHIEVES::iterator ib = m_AchievesMap.begin();
	
	for (;ib != m_AchievesMap.end();++ib)
	{
		 m_DoneNum[ib->first] = __calcAchievementDoneNum(ib->second);
		 pTableData_Group = (const stDBC_FILE_ACHIEVE_GROUP*)pDataFile_Group->GetFieldsByIndexKey(ib->first);
		 if (!pTableData_Group)
		 {
			 continue;
		 }
		 AchievementData::sortKey =	pTableData_Group->group;
		 sort(ib->second.begin() ,ib->second.end(),__dataSort1);
	}
}
X_VOID AchievementData::Sort()
{
	sort(m_Achieves.begin() ,m_Achieves.end(),__dataSort1);
}
X_BOOL	 AchievementData::__dataSort2(const Achieve *p1,const Achieve *p2)
{
	X_INT s1 = p1->getTableData()->group;
	X_INT s2 = p2->getTableData()->group;
	vector<X_INT> vec; vec.clear();
	UtilTools::ConvertStringToIntVector(AchievementData::sortKey.c_str(),vec,"|");
	X_INT pos1 = UtilTools::findInVector(s1,vec);
	X_INT pos2 = UtilTools::findInVector(s2,vec);
	return pos1 < pos2;

}
X_BOOL	AchievementData:: __dataSort1(const Achieve *p1,const Achieve *p2)
{
	 EM_ACHIEVE_STATUS s1 = p1->getStatus();
	 EM_ACHIEVE_STATUS s2 = p2->getStatus();
	 if (s1 == s2)
	 {
		 return p1->getId() < p2->getId();
	 }
	 return s1 >s2;
}
X_INT  AchievementData::__calcAchievementDoneNum( const vector<const Achieve*> & vec)
{
	X_UINT size = vec.size();
	X_INT num = 0;
	for (X_UINT i = 0;i<size ;i++)
	{
		if (!vec[i] )continue;
		if (vec[i]->getStatus() == EM_ACHIEVE_STATUS_NOT_SUBMIT)
		{
			num++;
		}
	}
	return num;
}
bool   AchievementData::HasAchievementDone()
{

	//策划要求按组配置 是否有可完成的成就计算。 
	/*X_UINT size = m_Achieves.size();
	for (X_UINT i = 0;i<size ;i++)
	{
		 if (!m_Achieves[i] )continue;
		 if (m_Achieves[i]->getStatus() == EM_ACHIEVE_STATUS_NOT_SUBMIT)
		 {
			 return true;
		 }
	}
	return false;*/

	X_UINT size = m_DoneNum.size();

	for (X_UINT i = 0;i<size;i++)
	{
		if (m_DoneNum[i] >0 )
		{
			return true;
		}
	}
	return false;

}
const vector<const Achieve*>  & AchievementData::getAchievesWithGroup(X_INT group)
{
	return m_AchievesMap[group];
}

X_INT AchievementData::getAchievesGroupDoneNum(X_INT group)
{
	return m_DoneNum[group];
}
X_INT AchievementData::getAchievesGroupAllNum(X_INT group)
{
	return m_AchievesMap[group].size();
}
X_INT AchievementData::getAchievesLayerNum()
{
	return m_AchievesMap.size();
	  
}
X_BOOL AchievementData::getAchievesGroupisNull(X_INT group)
{
	//return m_AchievesMap[group];
	return  m_AchievesMap[group].size() == 0;
}
const stDBC_FILE_ACHIEVE_GROUP	* AchievementData::getAchievesGroupTbaleData(X_INT group)
{
	const  DataBase* pDataFile_Group  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE_GROUP);
	const stDBC_FILE_ACHIEVE_GROUP	*  pTableData_Group = X_NULL;
	pTableData_Group = (const stDBC_FILE_ACHIEVE_GROUP*)pDataFile_Group->GetFieldsByIndexKey(group);
	return pTableData_Group;
}


vector<X_INT>   AchievementData::getAchievesGroupIds()
{
	vector<X_INT> vec;vec.clear();
	ACHIEVES::iterator ib = m_AchievesMap.begin();
	for (;ib != m_AchievesMap.end();++ib)
	{
		  vec.push_back(ib->first);
	}
	return vec;
}

 
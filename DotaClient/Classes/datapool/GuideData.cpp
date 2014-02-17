#include "./datapool/GuideData.h"
#include "./game/SendPacket.h"
#include "./event/EventSystem.h"
#include "./datapool//DataPool.h"
#include "./object/Object.h"
#include "./object/ObjectSelf.h"

X_VOID GuideData::Initial()
{
	m_TipGroup = -1;
	m_TipId = -1;
	m_PreTipId = -1;
	m_Tips.clear();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GUIDE);
	if (pDataFile)
	{
		const stDBC_FILE_GUIDE* pData = X_NULL;

		for (X_UINT i = 0;i<pDataFile->GetRecordsNum();i++)
		{
			pData =  (const stDBC_FILE_GUIDE* ) (pDataFile->GetFieldsByLineNum(i));
			if (!pData)continue;			 
			m_Tips[pData->group].push_back(pData->id);
		}
	}
}
X_VOID GuideData::SetTipGroup(X_INT id)
{
	//return;
	X_INT playerLevel =-1;
	if (DataPool::GetSingleton())
	{
		ObjectManager* pM = DataPool::GetSingleton()->getObjectManager();
		if (!pM)return;
		ObjectSelf* pSelf = pM->getSelf();
		if (!pSelf)return;

		PlayerData*  pData =  pSelf->playerData();
		if (!pData)return;
		playerLevel = pData->GetLevel();
	}
	if (playerLevel >1)
	{
		return;
	}

    
    
	m_TipGroup= id+1;//id为完成组
	m_PreTipId =-1;
	if(m_Tips.find(m_TipGroup) == m_Tips.end())
		return;
	if(m_Tips[m_TipGroup].size() <= 0) return;

	m_TipId = m_Tips[m_TipGroup].at(0);

	const stDBC_FILE_GUIDE* pData = getTableData(m_TipId);
	if (pData)
	{
		vector<string>str;
		str.clear();
		str.push_back(pData->ui);
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_GUIDE_SHOW,str);
	}

}

X_VOID GuideData::Release()
{
	m_TipGroup = -1;
	m_TipId =-1;
	m_PreTipId= -1;
	map<X_INT ,vector<X_INT> > ::iterator ib =m_Tips.begin();
	for (;ib!=m_Tips.end();++ib)
	{
		ib->second.clear();
	}
	m_Tips.clear();
}
X_VOID GuideData::HandleTip(X_INT id)
{
	const stDBC_FILE_GUIDE*  pData = X_NULL;
	if (id ==-1)
	{
		 pData = GuideData::getTableData(m_TipId);
		 m_PreTipId = m_TipId;
		 if (m_PreTipId == 13 ||m_PreTipId == 18)
		 {
			 m_TipId = m_TipId+2;
		 }else
		 {

			 m_TipId = m_TipId+1;
		 }
	}else
	{
		pData = GuideData::getTableData(id);
		m_PreTipId = id;
		if (m_PreTipId == 14 ||m_PreTipId == 18)
		{
			m_TipId = id+2;
		}else
		{
			m_TipId = id+1;
		}
	}
	if (pData &&pData->groupflag!=-1)
	{
		SendLogicPacket::ClickGuideTip(pData->group);
	}
	
    pData = getTableData(m_TipId);
	if (pData)
	{
		vector<string>str;
		str.clear();
		str.push_back(pData->ui);
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_GUIDE_SHOW,str);

	}else
	{
		m_TipId = -1;
	}
}

const stDBC_FILE_GUIDE* GuideData::getTableData(X_INT id)
{

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GUIDE);
	if (pDataFile)
	{
		return  (const stDBC_FILE_GUIDE* ) (pDataFile->GetFieldsByIndexKey(id));
	}
	return X_NULL;
}


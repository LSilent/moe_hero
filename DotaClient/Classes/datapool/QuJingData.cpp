#include "./datapool/QuJingData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"
#include "./Packets/QuJing/GCOpenQuJingUIPacket.h"
#include "./Packets/QuJing/GCQuJingHuSongBroadPacket.h"
#include "./object/ObjectSelf.h"
#include "./object/ObjectHero.h"
#include "cocos2d.h"

X_VOID  QuJingPlayerData::Tick(X_UINT nTime)
{
	 
	m_time -= nTime;
	if (m_time <= 0)
	{
		m_time = 0;
	}
}
QuJingPlayerData::QuJingPlayerData()
{
	m_time = 0;
    m_GUID = INVALID_INDEX;
	m_Name ="";
	 m_Level=0;
	m_HuSongID=0;
	m_TimeLeft=0;
	m_BeRobTimes =0;
	m_BeRobExp=0;
	m_BeRobWood=0;
	m_TotalExp=0;
	m_TotalWood=0;
 
}
X_FLOAT QuJingPlayerData::getPerCent()
{
	 
	const stDBC_FILE_QUJING  * pTableData =  QuJingData::getTableDataById(m_HuSongID);
	if (pTableData)
	{
		if ( pTableData->time > 0)
		{
			return m_time*0.001f/pTableData->time;
		}
	}
	return 1.0f;
}
 X_VOID QuJingData::Initial()
 { 
	 m_CurrentHuSongID = -1;
	 m_HuSongTimes = 0;
	 m_RobTimes = 0;
	 m_RobCDTime = 0;
	 m_TotalWood = 0;
	 m_QuJingDay = 0;
	 memset(m_HeroGuid,0,sizeof(X_GUID)*MAX_MATRIX_CELL_COUNT);
	 memset(m_HeroTableID,0,sizeof(X_INT)*MAX_MATRIX_CELL_COUNT);
	 m_heroes.clear();
	 m_bHeroSetMatrix = false;
	 m_pData.clear();
	 bGetAllHero = false;
	 m_bCanQujing = false;
 }
 X_VOID QuJingData::Release()
 {
	 X_UINT size = m_pData.size();
	 for (X_UINT i =0;i< size;i++)
	 {
		SAFE_DELETE( m_pData[i]); 
	 }
	 m_pData.clear();
 }

 X_VOID  QuJingData::Tick(X_UINT nTime)
 {
	 
	/* vector <QuJingPlayerData*>::iterator ib = m_pData.begin();
	 for (;ib != m_pData.end();)
	 {
		 if (!(*ib))
		 {
			 continue;;
		 }
		 (*ib)->Tick(nTime);
		 if ( (*ib)->m_time <=0)
		  {
			 ib = m_pData.erase(ib);
 
		  }else
		  {
			  ++ib;
		  }
	 }*/
	X_INT size  = m_pData.size();
	for (X_INT i = 0;i<size;i++)
	{
		QuJingPlayerData* pData = m_pData[i];

		if (!pData)
		{
			continue;
		}
		pData->Tick(nTime);
		if (pData->m_time <=0)
		{
			SAFE_DELETE(pData);
			m_pData[i] = 0;
		}
	}
 
 }
 X_VOID	QuJingData::SetQujingData(GCOpenQuJingUIPacket* pPacket)
 {
	 if (!pPacket)return;
	
	/* X_UINT size = m_pData.size();
	 for (X_UINT i =0;i< size;i++)
	 {
		 SAFE_DELETE( m_pData[i]); 
	 }
	 m_pData.clear();*/
	  X_INT num = pPacket->GetCurrentQuJingCount();
	 for (X_INT i = 0;i<num;i++)
	 {
		  QuJingPackData data;
		 if(pPacket->GetQuJingData(i,data)!=XTRUE) continue;
		 QuJingPlayerData *pData = new QuJingPlayerData();
	 
		    pData->m_GUID = data.m_GUID;
			pData->m_Name = data.m_Name;
			pData->m_Level = data.m_Level;
			pData->m_HuSongID = data.m_HuSongID;
			pData->m_TimeLeft = data.m_TimeLeft;
			pData->m_BeRobTimes = data.m_BeRobTimes;
			pData->m_BeRobExp = data.m_BeRobExp;
			pData->m_BeRobWood = data.m_BeRobWood;
			pData->m_TotalExp = data.m_TotalExp;
			pData->m_TotalWood = data.m_TotalWood;
		    pData->m_time = data.m_TimeLeft >0?data.m_TimeLeft*1000:0 ;
		 
			int id =  RemovePlayerDataByData(pData->m_GUID.GetValue());
			if (id >=0 && id < X_INT(m_pData.size()))
			{
				m_pData[id] = pData;
			}else
			{
				m_pData[getCanUseIndex()] = pData;
			}
		 

	 }
 }

 bool QuJingData::getPlayerSprite(QuJingPlayerData* pPlayer,int& id)
 {
	 id = -1;
	 if (!pPlayer)
	 {
		 return false;
	 }
	 X_INT size = m_pData.size();
	 for (int i =0;i < size;i++)
	 {
		 if (m_pData[i] == pPlayer)
		 {
			 id = i;
			 return true;
		 }
	 }
	 return false;
 }
 int  QuJingData::getCanUseIndex( )
 {
	 X_INT size = m_pData.size();
	 for (int i =0;i<size;i++)
	 {
		 if (!m_pData[i] )
		 {
			 return i;
		 }
	 }
	 m_pData.push_back(0);
	 return m_pData.size()-1;
 }
 int QuJingData::RemovePlayerDataByData(X_CLIENT_GUID guid)
 {
	 
	 if (guid == INVALID_INDEX)
	 {
		 return -1;
	 }
	 X_INT size = (X_INT)m_pData.size();
	 QuJingPlayerData *pPlayerData = X_NULL;
	 for (X_INT i = 0;i<size;i++)
	 {
		 pPlayerData = m_pData[i];
		 if (pPlayerData == X_NULL)continue;
		 if (pPlayerData->m_GUID.GetValue() == guid)
		 {
			 SAFE_DELETE(pPlayerData);
			 m_pData[i] = 0;
			 return  i;
		 }
	 }
	 return -1;
 }
 QuJingPlayerData* QuJingData::findPlayerDataByData(X_CLIENT_GUID guid)
 {
	 if (guid == INVALID_INDEX)
	 {
		 return X_NULL;
	 }
	  X_INT size = (X_INT)m_pData.size();
	  QuJingPlayerData *pPlayerData = X_NULL;
	  for (X_INT i = 0;i<size;i++)
	  {
		  pPlayerData = m_pData[i];
		  if (pPlayerData == X_NULL)continue;
		  if (pPlayerData->m_GUID.GetValue() == guid)
		  {
			  return pPlayerData;
		  }
	  }
	  return X_NULL;
 }
 X_VOID		QuJingData::upDataQujingData(GCQuJingHuSongBroadPacket* pPacket)
 {
	 if (!pPacket)return;
	 	//0 新加 1更新 2删除
	 QuJingPackData data = 	 pPacket->GetQuJingData();

	 X_INT type = pPacket->GetType();
	 if (type == 0)
	 {
		 QuJingPlayerData *pData = new QuJingPlayerData();
		 pData->m_GUID = data.m_GUID;
		 pData->m_Name = data.m_Name;
		 pData->m_Level = data.m_Level;
		 pData->m_HuSongID = data.m_HuSongID;
		 pData->m_TimeLeft = data.m_TimeLeft;
		 pData->m_BeRobTimes = data.m_BeRobTimes;
		 pData->m_BeRobExp = data.m_BeRobExp;
		 pData->m_BeRobWood = data.m_BeRobWood;
		 pData->m_TotalExp = data.m_TotalExp;
		 pData->m_TotalWood = data.m_TotalWood;
		 pData->m_time = data.m_TimeLeft >0 ? data.m_TimeLeft*1000:0 ;
		// m_pData.push_back(pData);

		 int id =  RemovePlayerDataByData(pData->m_GUID.GetValue());
		 if (id >=0 && id < X_INT(m_pData.size()))
		 {
			  m_pData[id] = pData;
		 }else
		 {
			  m_pData[getCanUseIndex()] = pData;
		 }
		

		 return;
	 }
	 if (type == 1)
	 {
		 QuJingPlayerData* pData = findPlayerDataByData(data.m_GUID.GetValue());
		 if (!pData) return;
		 pData->m_GUID = data.m_GUID;
		 pData->m_Name = data.m_Name;
		 pData->m_Level = data.m_Level;
		 pData->m_HuSongID = data.m_HuSongID;
		 pData->m_TimeLeft = data.m_TimeLeft;
		 pData->m_BeRobTimes = data.m_BeRobTimes;
		 pData->m_BeRobExp = data.m_BeRobExp;
		 pData->m_BeRobWood = data.m_BeRobWood;
		 pData->m_TotalExp = data.m_TotalExp;
		 pData->m_TotalWood = data.m_TotalWood;
		 pData->m_time = data.m_TimeLeft >0?data.m_TimeLeft*1000:0 ;
	 }
	 else  if (type == 2)
	 {
		 X_GUID guid = pPacket->GetHumanGuid();
		 vector <QuJingPlayerData*>::iterator ib = m_pData.begin();
		/* for (;ib!=m_pData.end();++ib)
		 {
			 if (!*ib )continue;
			 if ((*ib)->m_GUID == guid)
			 {
				 m_pData.erase(ib);
				 return;
			 }
		 }*/
 
		 RemovePlayerDataByData(guid.GetValue());
		
	 }
 }
const stDBC_FILE_QUJING  * QuJingData::getTableDataById(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_QUJING);
	const stDBC_FILE_QUJING	* m_pTableData =(const stDBC_FILE_QUJING*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData;
}
X_VOID    QuJingData::autoHeroMatrix()
{
	if (!m_bHeroSetMatrix)
	{
		bool HeroGetAll = isQuJingHeroGet();
		if (HeroGetAll)
		{
			X_GUID guid[MAX_MATRIX_CELL_COUNT];
			for (X_INT i=0;i< X_INT(m_heroes.size());i++ )
			{
				guid[i] = m_heroes[i]->GetGuid();
			}
			SendLogicPacket::QuJingSetMatrixt(guid);
		}

	}
}
X_VOID	QuJingData::HandlerNewHero(ObjectHero *pHero)
{
	if (!m_bHeroSetMatrix)
	{
		return;
	}
	if (!pHero || !isInQuJingHeroTable(pHero->GetTableID()))
	{
		return;
	}
	m_bHeroSetMatrix = false;

}
bool	  QuJingData::isQuJingHeroGet()
{
	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	X_UINT size = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	ObjectHero *pHero = X_NULL;
	m_heroes.clear();
	for (X_UINT i = 0;i< size;i++)
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero || !isInQuJingHeroTable(pHero->GetTableID()))
		{
			continue;
		}
		m_heroes.push_back(pHero);
	}

	return m_heroes.size() >= 1; //(MAX_MATRIX_CELL_COUNT-1);
}
bool      QuJingData::isInQuJingHeroTable(X_INT ID)
{
	if(ID <=0 ) return false;
	for(X_INT i=0;i<MAX_MATRIX_CELL_COUNT-1;++i)
	{
		 if(m_HeroTableID[i] == ID) return true;
	}
	return false;
}
X_VOID			QuJingData::SetHeroTableID(const X_INT* pHero)
{
	for(X_INT i=0;i<MAX_MATRIX_CELL_COUNT;++i)
	{
		m_HeroTableID[i] = pHero[i];
	}
}
bool	QuJingData::IsGetAllHeros()
{
	if (bGetAllHero)
	{
		return bGetAllHero;
	}
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
	if (!pDataFile)
	{
		return false;
	}
	const stDBC_FILE_HERO_ATTR	* m_pTableData =X_NULL;
	X_INT line = pDataFile->GetRecordsNum();
	 const ObjectHero *  pHero = X_NULL;
	for (X_INT i =0;i < line ;i++ )
	{
		m_pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByLineNum(i);
		if (!m_pTableData || m_pTableData->_id > 1000)continue;
			pHero = pSelf->getHeroWithTableid(m_pTableData->_id );
			if (!pHero)
			{
				return false;
			}
	}
	bGetAllHero = true;
	return true;
}
bool			 QuJingData::IsCanQujingForLevel(X_INT & needLevel)
{

	needLevel = 0;
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	if (X_NULL==pSelf)
	{
		return false;
	}

	PlayerData* pPlayerData = pSelf->playerData();
	if (X_NULL==pPlayerData)
	{
		return false;
	}
	X_INT level = pPlayerData->GetLevel();

	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_QUJING_LEVEL);
		if (pTableData)
		{
			needLevel = pTableData->m_value;
			if (level >= needLevel)
			{
				return true;
			}else
			{
				return false;
			}    
		}	
	}
	return true;
}
 
bool	QuJingData::IsCanQujing()
{
	__ENTER_FUNCTION

	if (m_bCanQujing)
	{
		return true;
	}

	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	if (X_NULL==pSelf)
	{
		return false;
	}

	PlayerData* pPlayerData = pSelf->playerData();
	if (X_NULL==pPlayerData)
	{
		return false;
	}


	QuJingData *pQujingData = DataPool::GetSingleton()->GetQuJingData();
	if (X_NULL==pQujingData)
	{
		return false;
	}

	const X_INT* pHeroTableID = pQujingData->GetHeroTableID();
	for (X_INT i=0; i<MAX_QUJING_RDHERO_NUM; ++i)
	{
		const ObjectHero * pHero = pSelf->getHeroWithTableid(pHeroTableID[i]);
		if (X_NULL != pHero)
		{
			m_bCanQujing = true;
			break;
		}
	}

	return m_bCanQujing;
	__LEAVE_FUNCTION
	return false;
}

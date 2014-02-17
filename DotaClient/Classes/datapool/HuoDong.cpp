#include "./datapool/HuoDong.h"
#include "./database/DataBaseSystem.h"
#include "./base/UtilTools.h"
#include "./base/Sdk_Handler.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectManager.h"
#include "./object/ObjectSelf.h"
#include "./game/SendPacket.h"
#include "./ui/cheeseActivityUI.h"
#include "./event/EventSystem.h"

const char * HuoDong::getName()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUODONG);
	const stDBC_FILE_HUODONG * m_pTableData = (const stDBC_FILE_HUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

	if (m_pTableData)
	{
		return m_pTableData->name;
	}
  return "";
}
X_INT HuoDong::getId()
{
	return m_Id;
}
X_INT HuoDong::getLevelNeed()
{
	if (m_Id >= EM_ID_HUODONG_EATCHEESE1 && m_Id<= EM_ID_HUODONG_EATCHEESE3)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EATCHEESE);
		const stDBC_FILE_EATCHEESE * m_pTableData = (const stDBC_FILE_EATCHEESE*)pDataFile->GetFieldsByIndexKey(m_Id);

		if (m_pTableData)
		{
			return m_pTableData->level;
		}

	}else if (m_Id >= EM_ID_HUODONG_GANK1 && m_Id<= EM_ID_HUODONG_DUIXIAN3)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_COPYSCENEHUODONG);
		const stDBC_FILE_COPYSCENEHUODONG * m_pTableData = (const stDBC_FILE_COPYSCENEHUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

		if (m_pTableData)
		{
			return m_pTableData->level;
		}
	}
	return 0;
}
X_INT HuoDong::getAddAction()
{
	if (m_Id >= EM_ID_HUODONG_EATCHEESE1 && m_Id<= EM_ID_HUODONG_EATCHEESE3)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EATCHEESE);
		const stDBC_FILE_EATCHEESE * m_pTableData = (const stDBC_FILE_EATCHEESE*)pDataFile->GetFieldsByIndexKey(m_Id);

		if (m_pTableData)
		{
			return m_pTableData->actionpoint;
		}

	}
	return 0;
}
X_INT HuoDong::getCopySceneId()
{
	if (m_Id >= EM_ID_HUODONG_GANK1 && m_Id<= EM_ID_HUODONG_DUIXIAN3)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_COPYSCENEHUODONG);
		const stDBC_FILE_COPYSCENEHUODONG * m_pTableData = (const stDBC_FILE_COPYSCENEHUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

		if (m_pTableData)
		{
			return m_pTableData->copySceneId;
		}
	}
	return -1;
}
X_INT HuoDong::getCopySceneNeedAction()
{
	if (m_Id >= EM_ID_HUODONG_GANK1 && m_Id<= EM_ID_HUODONG_DUIXIAN3)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_COPYSCENEHUODONG);
		const stDBC_FILE_COPYSCENEHUODONG * m_pTableDataHD = (const stDBC_FILE_COPYSCENEHUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);
		if (m_pTableDataHD)
		{
			const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILR_COPYSCENE);
			if (pDataFile)
			{
				const stDBC_FILR_COPYSCENE * m_pTableData = (const stDBC_FILR_COPYSCENE*)pDataFile->GetFieldsByIndexKey(m_pTableDataHD->copySceneId);
				if (m_pTableData)
				{
					return m_pTableData->_costAction;
				}
			}
		}
	} 
	return 0;
}
const char * HuoDong::getWeek()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUODONG);
	const stDBC_FILE_HUODONG * m_pTableData = (const stDBC_FILE_HUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

	if (m_pTableData)
	{
		return m_pTableData->openDay;
	}
	return "";
}
string HuoDong::getTime()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUODONG);
	const stDBC_FILE_HUODONG * m_pTableData = (const stDBC_FILE_HUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

	if (m_pTableData)
	{
		vector<string> str;
		str.clear();
	   UtilTools::ConvertStringToVector(m_pTableData->opentime,str,"|");

	   string s ="";
	   X_INT size = str.size();
	   for (X_INT i = 0;i<size;i++)
	   {
		   s += str[i];
		   if (i < size -1)
		   {
			   s+=":";
		   }
	   }
	   return s.substr(0,5);//
	}
	return "";
}
string HuoDong::getEndTime()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUODONG);
	const stDBC_FILE_HUODONG * m_pTableData = (const stDBC_FILE_HUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

	if (m_pTableData)
	{
		vector<int> str;
		str.clear();
		UtilTools::ConvertStringToIntVector(m_pTableData->opentime,str,"|");
	 
		X_INT sec = str[0]*3600 +str[1]*60 + str[2]+getcontinueTime()*60;
 
		return UtilTools::ConvertMillisecondToTimeString(sec*1000).substr(0,5);//
		 
	}
	return "";
}
X_INT HuoDong::getcontinueTime()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUODONG);
	const stDBC_FILE_HUODONG * m_pTableData = (const stDBC_FILE_HUODONG*)pDataFile->GetFieldsByIndexKey(m_Id);

	if (m_pTableData)
	{
		return m_pTableData->time;
	}
	return 0;
}

EM_STATE_HUODONG_CLIENT HuoDong::getState()
{
	switch(m_State)
	{
		case EM_STATE_HUODONG_INVALID:
			return EM_C_STATE_HUODONG_INVALID;
		case	EM_STATE_HUODONG_DIABLE:			//未开启
			return EM_C_STATE_HUODONG_DIABLE;
		case	EM_STATE_HUODONG_RUN:			//进行中
			{
				 
				if (m_Id >= EM_ID_HUODONG_EATCHEESE1 && m_Id<= EM_ID_HUODONG_EATCHEESE3)
				{
					  if(m_Param >= 1)
					  {
						  return EM_C_STATE_DONE;
					  } 

				}else if (m_Id >= EM_ID_HUODONG_GANK1 && m_Id<= EM_ID_HUODONG_DUIXIAN3)
				{

					if(m_Param >= 3)
					{
						return EM_C_STATE_DONE;
					} 
				}	
				return EM_C_STATE_HUODONG_RUN;
			}
		case	EM_STATE_HUODONG_END:			//结束
			return	EM_C_STATE_HUODONG_END;		 
		case 	EM_STATE_HUODONG_NUMBER:
			return EM_C_STATE_HUODONG_NUMBER;

	}
	 			
		return EM_C_STATE_HUODONG_INVALID;
}

EM_HUODONG_TYPE HuoDong::GetType()
{

	if (m_Id >= EM_ID_HUODONG_EATCHEESE1 && m_Id<= EM_ID_HUODONG_EATCHEESE3)
	{
		 return EM_EATCHEESE;

	}else if (m_Id >= EM_ID_HUODONG_GANK1 && m_Id<= EM_ID_HUODONG_GANK3)
	{
		return  EM_GANK;
	}
	else if (m_Id >= EM_ID_HUODONG_DAYE1 && m_Id<= EM_ID_HUODONG_DAYE3)
	{
		return  EM_FARM;
	}
	else if (m_Id == EM_ID_HUODONG_SHAKE)
	{
		return  EM_SHAKE;
	}
	//else if (m_Id >= EM_ID_HUODONG_DUIXIAN1 && m_Id<= EM_ID_HUODONG_DUIXIAN3)
	//{
		//return  EM_LINE;
	//}

	return EM_INVALID_HUODONG_TYPE;
}

X_INT HuoDong::getNum()
{
	return m_Param;
}
X_VOID HuoDongData::Initial()
{
	m_HuoDong.clear();
	m_ShakeTime = 0;
	m_ShakeTiming = XFALSE;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_SHAKE_TIME_OVER);
		if (pTableData)
		{
			m_ShakeTime = pTableData->m_value*1000;
		}	
	}
	m_ShakeNum = 0;
	m_ShakeReady = XFALSE;
}
X_VOID HuoDongData::setShakeNum(X_INT num,bool waitTime)
{
	m_ShakeNum = num;
	if (waitTime)
	{
		if ( m_ShakeTime <=0 )
		{
			//SendLogicPacket::RockHer(m_ShakeNum);
			vector<string> str;
			str.clear();
			str.push_back( UtilTools::IntToString(EM_SHAKE_WAITE_LAYER_SHOW));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SHAKE_UPDATA,str);
		}
    
	}
	else
	{
		//SendLogicPacket::RockHer(m_ShakeNum);
		vector<string> str;
		str.clear();
		str.push_back( UtilTools::IntToString(EM_SHAKE_WAITE_LAYER_SHOW));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SHAKE_UPDATA,str);
	}
}
X_VOID HuoDongData::resetShakeTime( )
{
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_SHAKE_TIME_OVER);
		if (pTableData)
		{
			m_ShakeTime = pTableData->m_value*1000;
		}	
	}
}
X_VOID HuoDongData::Release()
{
	X_UINT size = m_HuoDong.size();
	for (X_UINT i = 0 ;i < size ;i++)
	{
		SAFE_DELETE(m_HuoDong[i]);
	}

	m_HuoDong.clear();
}
X_VOID HuoDongData::setHuoDong(X_INT id,X_INT state,X_INT param)
{ 
	HuoDong* hd = new HuoDong();
	hd->m_Id = id;
	hd->m_State = EM_STATE_HUODONG(state);
	hd->m_Param = param;
 
	m_HuoDong.push_back(hd);
 
}
X_VOID HuoDongData::setHuoDongState(X_INT id,X_INT state,X_INT param)
{
	X_INT size = m_HuoDong.size();
	for (X_INT i = 0 ;i < size ;i++)
	{
		if(m_HuoDong[i]->m_Id != id)continue;
		m_HuoDong[i]->m_State = EM_STATE_HUODONG(state);
		m_HuoDong[i]->m_Param = param;
	}
}
X_BOOL    HuoDongData::getShakeHuoDongEnable()
{
	X_INT size = m_HuoDong.size();
	for (X_INT i = 0 ;i < size ;i++)
	{
		if(m_HuoDong[i]->GetType() != EM_SHAKE)continue;
		 return m_HuoDong[i]->m_State == EM_STATE_HUODONG_RUN;
		 
	}
	return XFALSE;
}
 X_VOID  HuoDongData::Tick(X_UINT nTime)
 {
	 if (m_ShakeTiming == XFALSE)
	 {
		 return;
	 }
	 m_ShakeTime = (m_ShakeTime  - nTime);
	 if (m_ShakeTime <= 0 )
	 {
		 m_ShakeTime = 0;
		 m_ShakeTiming = XFALSE;
	 }
 }
 X_VOID HuoDongData::onShake()
 {
	 if (!m_ShakeReady)
	 {
		 return ;
	 }
	 if (m_ShakeTime > 0 )
		 m_ShakeNum ++;
 }
 X_VOID   HuoDongData::ShakeReady(X_BOOL b)
 {
	 m_ShakeReady = b;
	 if(m_ShakeReady)
	 {
		 SdkHandler::shakeBegin();
	 }
 }
 X_BOOL HuoDongData::canShake()
 {
	 ObjectManager *pm =DataPool::GetSingleton()->getObjectManager();
	  X_CLIENT_GUID guid = pm->getSelf()->playerData()->GetGoddessHeroGuid();
	 if (guid == INVALID_ID )
	 {
		 return XTRUE;
	 }
	 vector<ObjectHero*>  heros = pm->getSelf()->playerData()->GetFightHero();
	 X_UINT size = heros.size();
	 for (X_UINT i = 0;i< size;i++)
	 {
		 if (!heros[i])continue;
		  if (heros[i]->GetGuid() == guid)
		  {
			  return XFALSE;
		  }

	 }
	 return XTRUE;
 }
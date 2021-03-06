

#include "Game.h"
#include "./timer/SystemTimer.h"
#include "./event/EventSystem.h"
#include "./net/NetworkSystem.h"
#include "./game/MainGame.h"
#include "./ui/UISystem.h"
#include "./load/ResourceSystem.h"
#include "./database/DataBaseSystem.h"
#include "./ui/SceneManger.h"
#include "./sound/SoundSystem.h"
#include "./datapool/DataPool.h"
#include "./load/ResourceCheck.h"
#include "./datapool/SettingData.h"
#include "./base/UtilTools.h"
#include "./base/nuts.h"
#include "GameVersion.h"


SystemTimer*		Game::sm_pSystemTimer = NULL;	
ResourceSystem*		Game::sm_pResourceSystem = NULL;	
DataBaseSystem*		Game::sm_DataBaseSystem = NULL;	
EventSystem*		Game::sm_pEventSystem = NULL;	
NetworkSystem*		Game::sm_pNetworkSystem = NULL;	
SceneManger*		Game::sm_SceneManger = NULL;	
UISystem*			Game::sm_pUISystem = NULL;	
SoundSystem*		Game::sm_pSoundSystem = NULL;
DataPool*			Game::sm_pDataPool = NULL;
ResourceCheck*		Game::sm_pResourceCheck = NULL;


MainGame*			Game::sm_pMain = NULL;	
MainTick			Game::sm_MainTick;	

const static   float LOGIC_FINTERVAL =  0.03f;//1.0f/30;

X_CHAR				Game::sm_IP[24] = "127.0.0.1";
 //X_CHAR				Game::sm_IP[24] = "127.0.0.1";

//X_CHAR				Game::sm_IP[24] = "127.0.0.1";
//X_CHAR				Game::sm_IP[24] = "192.168.1.201";

// X_CHAR				Game::sm_IP[24] = "127.0.0.1";
//X_CHAR				Game::sm_IP[24] = "192.168.1.202";



X_INT				Game::sm_Port =  8000;
//X_CHAR				Game::sm_IP[24] = "61.160.251.62";  //testsssssssssss

//X_CHAR				Game::sm_IP[24] = "61.160.249.5";//pp


X_CHAR				Game::sm_UpdataIP[24] = "61.160.245.232";//91

X_INT				Game::sm_SelectServer = -1;
 
X_VOID Game::ReInitialWithNewRes()
{
	if (sm_pDataPool)
	{
		sm_pDataPool->Release();
		//SAFE_DELETE(sm_pDataPool)
	}
	if(sm_DataBaseSystem)
	{
		sm_DataBaseSystem->Release();
		SAFE_DELETE(sm_DataBaseSystem)
	}
	sm_DataBaseSystem = new DataBaseSystem();
	sm_DataBaseSystem->Initial();

    SettingData::Init();
	if (sm_pDataPool && !sm_pDataPool->m_init)
	{
		sm_pDataPool->Initial();
	}
	sm_SelectServer = 	 UtilTools::StringToInt(SettingData::GetSelectServer().c_str());
	sm_SelectServer = getValidMaxServerID(sm_SelectServer);

}
 X_VOID Game::Initial()
 {
	 sm_pResourceCheck = new ResourceCheck();
		sm_pResourceCheck->Initial();
	 sm_pSystemTimer = new SystemTimer();
		 sm_pSystemTimer->Initial();
	 sm_pResourceSystem = new ResourceSystem();
		sm_pResourceSystem->Initial();
	sm_SceneManger = new SceneManger();
		sm_SceneManger->Initial();
	 sm_DataBaseSystem = new DataBaseSystem();
		sm_DataBaseSystem->Initial();
	 sm_pEventSystem = new EventSystem();
		 sm_pEventSystem->Initial();
	 sm_pNetworkSystem = new NetworkSystem();
		sm_pNetworkSystem->Initial();
	 sm_pSoundSystem = new SoundSystem();
		 sm_pSoundSystem->Initial();
	 sm_pUISystem = new UISystem();
		sm_pUISystem->Initial();
	 SettingData::Init();
 
	 if (!sm_pDataPool)
	 {

		 sm_pDataPool = new DataPool();
		 sm_pDataPool->Initial();
	 }

	 sm_pMain = new MainGame();
		sm_pMain->Initial();
	 sm_SelectServer = 	 UtilTools::StringToInt(SettingData::GetSelectServer().c_str());
	 sm_SelectServer = getValidMaxServerID(sm_SelectServer);
	 nuts::init();
	 
 }
X_VOID Game::Release()
{
	if (sm_pMain)
	{
		sm_pMain->Release();
		SAFE_DELETE(sm_pMain)
	}
	if (sm_pDataPool)
	{
		sm_pDataPool->Release();
		SAFE_DELETE(sm_pDataPool)
	}
	if (sm_pSoundSystem)
	{
		sm_pSoundSystem->Release();
		SAFE_DELETE(sm_pSoundSystem)
	}
	if(sm_pUISystem)
	{
		sm_pUISystem->Release();
		SAFE_DELETE(sm_pUISystem)
	}
	if (sm_pNetworkSystem)
	{
		sm_pNetworkSystem->Release();
		SAFE_DELETE(sm_pNetworkSystem)
	}
	if(sm_pEventSystem)
	{
		sm_pEventSystem->Release();
		SAFE_DELETE(sm_pEventSystem)
	}
	if(sm_DataBaseSystem)
	{
		sm_DataBaseSystem->Release();
		SAFE_DELETE(sm_DataBaseSystem)
	}
	if(sm_SceneManger)
	{
		sm_SceneManger->Release();
		SAFE_DELETE(sm_SceneManger)
	}
	if(sm_pResourceSystem)
	{
		sm_pResourceSystem->Release();
		SAFE_DELETE(sm_pResourceSystem)
	}
	if (sm_pSystemTimer)
	{
		sm_pSystemTimer->Release();
		SAFE_DELETE(sm_pSystemTimer)
	}
	if (sm_pResourceCheck)
	{
		sm_pResourceCheck->Release();
		SAFE_DELETE(sm_pResourceCheck);
	}
}
X_VOID Game::Tick(X_UINT nTime)
{
	if (sm_pSystemTimer)
	{
		sm_pSystemTimer->Tick(nTime);

	}
	if (sm_pNetworkSystem)
	{
		sm_pNetworkSystem->Tick(nTime);
	}
	if (sm_pDataPool)
	{
		sm_pDataPool->Tick(nTime);
	}
	if (sm_pEventSystem)
	{
		sm_pEventSystem->Tick(nTime);
	}
	if (sm_pUISystem)
	{
		sm_pUISystem->Tick(nTime);
	}
	if (sm_pMain)
	{
		sm_pMain->Tick(nTime);
	}
 
}
X_VOID  Game::StartGame()
{
	//sm_SceneManger->GetDirector()->getScheduler()->scheduleUpdateForTarget(&sm_MainTick ,0,XFALSE);
 
	/*sm_SceneManger->GetDirector()->getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&MainTick::updateLogic),&sm_MainTick ,LOGIC_FINTERVAL,-1,0,XFALSE);
	sm_SceneManger->EnterScene(SceneManger::EM_SS_LOGIN);
	sm_pEventSystem->PushEvent(GAME_EVENT_MAINPAGE_SHOW);;*/

	sm_SceneManger->GetDirector()->getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&MainTick::updateLogic),&sm_MainTick ,LOGIC_FINTERVAL,kCCRepeatForever,0,XFALSE);
	sm_SceneManger->GetDirector()->getScheduler()->retain();
	sm_pMain->GetSingleton()->SetGameMainProState(MainGame::NONE_STATE);
 	
}

string Game::getUpdateUrl()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(sm_SelectServer);
	string url = string(m_pTableData->upDataIp) + string("/dota/platform") + UtilTools::IntToString(SC_SDK)+"/"+ g_GameVersion + "/server" +UtilTools::IntToString(sm_SelectServer)+"/";
	return url;
}

string Game::getNewVersionUrl()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(sm_SelectServer);
	string url = "http://"+string(m_pTableData->upDataIp) + string("/dota/platform")+ UtilTools::IntToString(SC_SDK)+ string("/dotainstall/");
	return url;
}

string Game::getAppChargeUrl()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(Game::sm_SelectServer);
	std::string url = "http://" + string(m_pTableData->ip)  + string("/apple/deliver.php?billno=");
	return url;
}
string   Game::getSelectServerName()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(sm_SelectServer);
	return m_pTableData->name;
}
X_BOOL  Game::CheckVersion()
{
	return X_FALSE;
	string url = 	getUpdateUrl();
	CCLog(url.c_str());
	if( !sm_pResourceCheck->checkVersion(url.c_str()))
	{
		return X_FALSE; //不需要更新
	}
	return X_TRUE;
}

X_VOID  Game::CheckUpData()
{
	string url = 	getUpdateUrl();
	sm_pResourceCheck->updateRes(url.c_str()); 
}
X_VOID  Game::Connect()
{

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(sm_SelectServer);
	if (m_pTableData)
	{
		CCLog("connect ip %s",m_pTableData->ip);
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(589));
		strV.push_back("1");
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		sm_pMain->GetSingleton()->ConnectServer(m_pTableData->ip,m_pTableData->port);
	}
}

X_VOID  Game::EndGame()
{
	sm_SceneManger->EndGame();
	
	Release();
}
X_VOID  Game::logOffCallBack()
{
     EnterBackground();
	 EnterForeground();
}

X_VOID  Game::EnterBackground()
{
	sm_pNetworkSystem->Release();
	EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVENT_BATTLEFIELD_CLOSE);
	sm_pDataPool->Release();
}
X_VOID  Game::EnterForeground()
{
	if (MainGame::GetSingleton())
	{
		sm_pDataPool->Initial();
		sm_pNetworkSystem->Initial();
		MainGame::GetSingleton()->SetGameMainProState(MainGame::NONE_STATE);
	}
}


int  Game::getValidMaxServerID(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pCurData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(id);
	X_INT num = pDataFile->GetRecordsNum();
	while (!m_pCurData)
	{
		if (num >= 0)
		{
			m_pCurData  = (const stDBC_FILE_SELECT_SERVER*) pDataFile->GetFieldsByLineNum(num--);
		}
	}

	return m_pCurData->id;
}

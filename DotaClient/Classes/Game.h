#ifndef __GAME_H__
#define __GAME_H__

#include "./base/Global.h"
#include "./base/Singleton.h"


class SystemTimer;
class ResourceSystem;
class DataBaseSystem;
class EventSystem;
class NetworkSystem;
class SceneManger;
class UISystem;
class MainGame;
class MainTick;
class SoundSystem;
class DataPool;
class ResourceCheck;
class Game
{
public:
	 static	X_VOID ReInitialWithNewRes();
	 static	X_VOID Initial();
	 static X_VOID Release();
	 static X_VOID Tick(X_UINT nTime);
public:
	static X_BOOL  CheckVersion();
	static X_VOID  CheckUpData();
	static X_VOID  StartGame();
	static X_VOID  Connect();
	static X_VOID  EndGame();
    
    
    static X_VOID  logOffCallBack();

	static X_VOID  EnterBackground();
	static X_VOID  EnterForeground();


	static int  getValidMaxServerID(X_INT id);
	static string   getUpdateUrl();
	static string   getNewVersionUrl();
	static string   getAppChargeUrl();
	static string   getSelectServerName();
public:
	 
	static  SystemTimer*		sm_pSystemTimer;
	static	ResourceSystem*		sm_pResourceSystem;
	static	DataBaseSystem*		sm_DataBaseSystem;
	static	EventSystem*		sm_pEventSystem;
	static  NetworkSystem*		sm_pNetworkSystem;
	static	SceneManger*		sm_SceneManger;
	static	UISystem*			sm_pUISystem;
	static	MainGame*			sm_pMain;
	static  MainTick			sm_MainTick;
	static	SoundSystem*		sm_pSoundSystem;
	static	DataPool*			sm_pDataPool;
	static	ResourceCheck*		sm_pResourceCheck;

	static  X_CHAR				sm_UpdataIP[24];
	static  X_CHAR				sm_IP[24];
	static  X_INT				sm_Port;
	static  X_INT				sm_SelectServer;


};
#endif
#include "MainGame.h"
#include "./timer/SystemTimer.h"
#include "./net/NetworkSystem.h"
#include "./ui/SceneManger.h"
#include "./event/EventSystem.h"
#include "./Packets/Login/CGAskRolelistPacket.h"
#include "./datapool/DataPool.h"
#include "./datapool/loginData.h"
#include "./DataBase/DataBaseSystem.h"
#include "cocos2d.h"
#include "./object/ObjectManager.h"
#include "./object/ObjectSelf.h"
#include "./GameVersion.h"
#include "./sound/SoundSystem.h"
#include "./base/pp.h"
#include "./load/ResourceCheck.h"
#include "./datapool/BloodData.h"
#include "./game/SendPacket.h"
#include "./base/Sdk_Handler.h"


void NetErrorModalDialogDelegate::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	 
	Game::logOffCallBack();
}
void NewVersionModalDialogDelegate::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
    
    /*string url = "http://61.160.249.5/dota/dota/";
     CCHttpClient *pcleint = CCHttpClient::getInstance();
     CCHttpRequest *req = new CCHttpRequest();
     req->setRequestType(CCHttpRequest::kHttpPost);
     req->setUrl(url.c_str());
     req->setTag("down_To_nuts");
     // req->setResponseCallback(&phttp,(SEL_CallFuncND)&httpBack::CallFuncND);
     pcleint->send(req);
     req->release();*/
    
	SdkHandler::downNewVersion();

    pSender->closeDialogView();
    
}


IMPLEMENT_SINGLETON(MainGame);
MainGame::MainGame()
{
	 m_nGameRunState = NONE_STATE;
}
MainGame::~MainGame()
{
}

 X_VOID MainGame::Initial()
 {
	 m_nGameRunState = NONE_STATE;
	 m_pdelegate =X_NULL;
     m_newVersionDelegate =X_NULL;
 }
X_VOID MainGame::Release()
{
	SAFE_DELETE(m_pdelegate);
}
X_VOID MainGame::Tick(X_UINT nTime)
{
	switch(m_nGameRunState)
	{
	case RUNING_IN_LOGIN:
		break;
	case RUING_IN_SELECTPLAYER:
		break;
	case RUNING_IN_GAME:
		{

		}
		break;
	}

}
 X_VOID		MainGame::EndBattle(bool win)
 {
	 
	 //------------打开战斗前的界面
	 m_nGameRunState = RUNING_IN_GAME;
	 SceneManger::GetSingleton()->EnterScene(SceneManger::EM_SS_MAIN);

	if(DataPool::GetSingleton()->BattlyType == EM_COPY_SCENE)
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_SHOW);
	else if(DataPool::GetSingleton()->BattlyType == EM_SPORT)
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RANKLIST_SHOW);
	else if(DataPool::GetSingleton()->BattlyType == EM_WOODPVP)
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_SHOW);
	}
	else if(DataPool::GetSingleton()->BattlyType == EM_BATTLETYPE_QUJING)
	{
		vector<string> str;str.clear();
		str.push_back(UtilTools::IntToString(EM_HUSONG_WOOD));//
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_SHOW,str);
		SendLogicPacket::OpenQuJingUi();
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_SHOW);
	}
	else if(DataPool::GetSingleton()->BattlyType == EM_BATTLETYPE_BLOODBATTLE)
	{
		BloodData* pBloodData = DataPool::GetSingleton()->GetBloodData();
		if (win)
		{
				pBloodData->NextStep();
		}else
		{
				pBloodData->EnterBloodUi();
		}
	}
	else 
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_SHOW);


	ObjectManager* pManager = DataPool::GetSingleton()->getObjectManager();
	PlayerData* pData = pManager->getSelf()->playerData();
	if (pData && pData->IsLevelUp())
	{
		pData->resetLevelUp();
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_UPGRADE_SHOW);
	}
	

	 BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	 pBattle->DestroyBattleData();
	 


 }
X_VOID MainGame::SetGameMainProState(GAME_RUN_STATE nRunState)
{
	m_nGameRunState = nRunState;

	switch(m_nGameRunState)
	{
		case NONE_STATE:
			{
				SceneManger::GetSingleton()->EnterScene(SceneManger::EM_SS_LOGIN);
				EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVENT_LOGO_SHOW);  
			}
			break;
	case CONNECT_TO_SERVER:
		{
			
		}
		break;
	case RUNING_IN_LOGIN:
		{
			SoundSystem::GetSingleton()->playBackgroundMusic( ("login" +SOUND_EXT).c_str());
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOGIN_SHOW);
		}
		break;
	case RUING_IN_SELECTPLAYER:
		{
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SELECTROLE_SHOW);
		}
		break;
	case RUNING_IN_GAME:
		{
			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_LOGIN_CLOSE);
			SceneManger::GetSingleton()->EnterScene(SceneManger::EM_SS_MAIN);
			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVENT_MAINPAGE_SHOW);
		}
		break;
	case RUNING_IN_BATTLE:
		{
			SceneManger::GetSingleton()->EnterScene(SceneManger::EM_SS_BATTLE);
			//EventSystem::GetSingleton()->PushEvent();
		}
		break;
	}
}
#include "cocos2d.h"
X_VOID	MainGame::ConnectServer(const X_CHAR* szServerIP, X_INT nServerPort)
{
    cocos2d::CCLog(szServerIP);
	 NetworkSystem* pNetworkSystem =  NetworkSystem::GetSingleton();
	 if(pNetworkSystem == X_NULL)
		return;
	//if(m_nGameRunState == NONE_STATE )
	 {
		 SetGameMainProState(CONNECT_TO_SERVER);
		 pNetworkSystem->ConnectServer(szServerIP, nServerPort);
		 return;
	 }
}
X_VOID	MainGame::ConnectServerDone(X_BOOL nRet)
{
	NetworkSystem* pNetworkSystem =  NetworkSystem::GetSingleton();
	if(pNetworkSystem == X_NULL)
		return;
	if(nRet)
	{
			SettingData::onEnterServer(Game::sm_SelectServer);
			pNetworkSystem->SetNetworkState(NetworkSystem::NET_DATA_WORKING);

			if(LOGIN_CONNECT)
			{
				MainGame::GetSingleton()->AskRolelist();
			}
			else
				SetGameMainProState(RUNING_IN_LOGIN);


	}else
	{
			DataPool::GetSingleton()->bConnect = false;
			pNetworkSystem->SetNetworkState(NetworkSystem::NET_NORMAL);
			pNetworkSystem->DisconnectServer();
			if(LOGIN_CONNECT)
			{
				m_nGameRunState = NONE_STATE;
			

			}else
			{
				SetGameMainProState(NONE_STATE);	
			}
			// vector<string> strV;strV.clear();
			// strV.push_back(UtilTools::GET_TEXT_FROM_LANG(615));
			//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			//wstring str = UtilTools::utf8_wchar(strV[0].c_str());
			//OutputDebugString(str.c_str());
			 
			ModalDialogView * pView = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(615),getDelegate() ,DIALOG_MODEL_SINGLE);
			SceneManger::GetSingleton()->AddChildToScene(pView,true);

			 

#ifdef _WINDOWS_
			//MessageBoxA(0,"网络异常","error",MB_OK);
#endif // _WINDOWS_
 
	}
}

NetErrorModalDialogDelegate* MainGame::getDelegate()
{
	if (!m_pdelegate)
	{
		m_pdelegate = new NetErrorModalDialogDelegate();
	}
	return m_pdelegate;
}
NewVersionModalDialogDelegate* MainGame::getNewVersionDelegate()
{
    if (!m_newVersionDelegate)
	{
		m_newVersionDelegate = new NewVersionModalDialogDelegate();
	}
	return m_newVersionDelegate;
}
X_VOID	MainGame::AskRolelist()
{
	const LoginData* pData = DataPool::GetSingleton()->getLoginData();
	if (pData == X_NULL)
	{
		return;
	}
	cocos2d::CCLog("-------------------------MainGame::AskRolelist()");
	CGAskRolelistPacket packet;


	packet.SetGroupID(Game::sm_SelectServer);
	packet.SetPlayerID(0);
	packet.SetGameVersion(g_GameVersion);

	/*wchar_t *pUseId = X_NULL;
	UtilTools::MultiByte2WideChar(pUseId,pData->getUserId().c_str());
	packet.SetUserID( const_cast<X_CHAR*>(UtilTools::wchar_utf8(pUseId).c_str()) );
	SAFE_DELETE(pUseId)*/
 

		packet.SetUserID( pData->getUserId().c_str() );
    
    cocos2d::CCLog("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s",pData->getUserId().c_str());    
	//packet.SetMac();
	//packet.SetTimeStamp()
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
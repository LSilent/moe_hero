#include "./ui/loginUi.h"
#include "./ui/loginView.h"
#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./net/NetworkSystem.h"
#include "./event/EventSystem.h"
#include "./base/Sdk_Handler.h" 

loginUi::loginUi()
{
	 
}
loginUi::~loginUi()
{
 
}

X_VOID   loginUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_LOGIN_SHOW);
	m_Event.push_back(GAME_EVENT_LOGIN_CLOSE);
 
}
X_VOID		 loginUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_LOGIN_SHOW:
        {
			this->Show(XTRUE);
        }
		break;
	case GAME_EVENT_LOGIN_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
	 
}
X_VOID	loginUi::OnCreate()
{
	if (m_pUi) return;
	 loginView *layer=  loginView::create();
	 m_pUi  = (cocos2d::CCNode*)layer;
	layer->setUserData(this);
	 
}
X_VOID loginUi::onEnterClick()
{
	if(NetworkSystem::GetSingleton()->GetNetworkState()== NetworkSystem::NET_CONNECTING_STATE)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(589));	strV.push_back("1");
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return  ;
	}
	cocos2d::CCLog("---------------------------loginUi::onEnterClick()");
	if (LOGIN_CONNECT)
	{
            SdkHandler::loginPressDown();
 
	}else
	{
		MainGame::GetSingleton()->AskRolelist();
	}
	
}


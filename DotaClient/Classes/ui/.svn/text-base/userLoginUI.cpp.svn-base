#include "./ui/userLoginUI.h"
#include "./ui/userLoginUIView.h"

USING_NS_CC_EXT;

userLoginUI::userLoginUI()
{
	this->m_MutexGroup =2;
}
userLoginUI::~userLoginUI()
{

}
X_VOID   userLoginUI::CareEvent()
{
	m_Event.push_back(GAME_EVNET_USER_LOGIN_SHOW);
	m_Event.push_back(GAME_EVNET_USER_LOGIN_UPDATA);
	m_Event.push_back(GAME_EVNET_USER_LOGIN_CLOSE);
	m_Event.push_back(GAME_EVNET_USER_REG_SUCCESS);
}
X_VOID	 userLoginUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVNET_USER_LOGIN_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVNET_USER_LOGIN_UPDATA:
		this->UpData();
		break;
	case GAME_EVNET_USER_LOGIN_CLOSE:
		this->Show(XFALSE);
		break;
	case GAME_EVNET_USER_REG_SUCCESS:
		if (m_bShow)
		{
			static_cast< userLoginUIView* >( m_pUi )->registerResult(true);
		}
		break;
	default:
		break;
	}  
}

X_VOID	userLoginUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< userLoginUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	userLoginUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("userLoginUIView", userLoginUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("UserLogin.ccbi");
    
    ccbReader->release();
}

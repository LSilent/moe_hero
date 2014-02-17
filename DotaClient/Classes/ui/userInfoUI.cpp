#include "./ui/userInfoUI.h"
#include "./ui/userInfoUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

userInfoUI::userInfoUI()
{
	this->m_MutexGroup =2;
}
userInfoUI::~userInfoUI()
{

}

X_VOID   userInfoUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_USER_INFO_CLOSE);
	m_Event.push_back(GAME_EVENT_USER_INFO_UPDATA);
	m_Event.push_back(GAME_EVENT_USER_INFO_SHOW);
	m_Event.push_back(GAME_EVENT_USER_INFO_BUY_ACTION);
	m_Event.push_back(GAME_EVENT_RANKLIST_UPDATA);

}
X_VOID	 userInfoUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_USER_INFO_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_USER_INFO_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_USER_INFO_CLOSE:
		this->Show(XFALSE);
		break;
	case GAME_EVENT_USER_INFO_BUY_ACTION:
		if (m_bShow)
		{
			static_cast< userInfoUIView* >( m_pUi )->buyAction();
		}
		break;
	case GAME_EVENT_RANKLIST_UPDATA:
		if (m_bShow)
		{
			static_cast< userInfoUIView* >( m_pUi )->rankLevelUpdata();
		}
		break;
	default:
		break;
	}  
}

X_VOID	userInfoUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< userInfoUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	userInfoUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("userInfoUIView", userInfoUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("UserInfo.ccbi");
    
    ccbReader->release();
}

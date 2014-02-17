#include "./ui/secretStoreUI.h"
#include "./ui/secretStoreUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

SecretStoreUI::SecretStoreUI()
{

}
SecretStoreUI::~SecretStoreUI()
{

}

X_VOID   SecretStoreUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_SECRETSTORE_SHOW);
	m_Event.push_back(GAME_EVENT_SECRETSTORE_UPDATA);
	

}
X_VOID	 SecretStoreUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_SECRETSTORE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_SECRETSTORE_UPDATA:
		{
			if (m_bShow == XFALSE) return;
			static_cast< SecretStoreUIView* >( m_pUi )->UpdateStates();
		}
		 
			break;
	default:
		break;
	}  
}

X_VOID	SecretStoreUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< SecretStoreUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	SecretStoreUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("SecretStoreUIView", SecretStoreUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("SecretStore.ccbi");
    
    ccbReader->release();
}

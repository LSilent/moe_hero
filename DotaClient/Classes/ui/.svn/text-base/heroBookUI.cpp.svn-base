#include "./ui/HeroBookUI.h"
#include "./ui/HeroBookUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

HeroBookUI::HeroBookUI()
{
	nPage = 0;
}
HeroBookUI::~HeroBookUI()
{

}

X_VOID   HeroBookUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_HEROBOOK_SHOW);
	m_Event.push_back(GAME_EVENT_HEROBOOK_UPDATA);
	

}
X_VOID	 HeroBookUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_HEROBOOK_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_HEROBOOK_UPDATA:
		this->UpData();
		break;
	default:
		break;
	}  
}

X_VOID	HeroBookUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroBookUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroBookUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroBookUIView", HeroBookUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("HeroBook.ccbi");
    
    ccbReader->release();
}

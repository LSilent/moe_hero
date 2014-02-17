#include "./ui/heroEvolveUI.h"
#include "./ui/heroEvolveUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

HeroEvolveUI::HeroEvolveUI()
{
	this->m_MutexGroup = 2;
}
HeroEvolveUI::~HeroEvolveUI()
{

}

X_VOID   HeroEvolveUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_HEROEVOLVE_SHOW);
	m_Event.push_back(GAME_EVENT_HEROEVOLVE_UPDATA);
	m_Event.push_back(GAME_EVENT_HEROEVOLVE_CLOSE);

}
X_VOID	 HeroEvolveUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_HEROEVOLVE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_HEROEVOLVE_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_HEROEVOLVE_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
}

X_VOID	HeroEvolveUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroEvolveUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroEvolveUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroEvolveUIView", HeroEvolveUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("HeroEvolve.ccbi");
    
    ccbReader->release();
}

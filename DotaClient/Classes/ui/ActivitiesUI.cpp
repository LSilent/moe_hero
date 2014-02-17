#include "./ui/ActivitiesUI.h"
#include "./ui/ActivitiesUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

ActivitiesUI::ActivitiesUI()
{

}
ActivitiesUI::~ActivitiesUI()
{

}

X_VOID   ActivitiesUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_ACTIVITIES_SHOW);
}
X_VOID	 ActivitiesUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_ACTIVITIES_SHOW:
		this->Show(XTRUE);
	default:
		break;
	}  
	 
}
X_VOID	ActivitiesUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("ActivitiesUIView", ActivitiesUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("Activities.ccbi");
    
    ccbReader->release();
}

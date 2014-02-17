#include "./ui/teamListUI.h"
#include "./ui/teamListUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

TeamListUI::TeamListUI()
{

}
TeamListUI::~TeamListUI()
{

}

X_VOID   TeamListUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_TEAMLIST_SHOW);
	m_Event.push_back(GAME_EVENT_TEAMLIST_UPDATA);
	

}
X_VOID	 TeamListUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_TEAMLIST_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_TEAMLIST_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	TeamListUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< TeamListUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	TeamListUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("TeamListUIView", TeamListUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("TeamList.ccbi");
    
    ccbReader->release();
}

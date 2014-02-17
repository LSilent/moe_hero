#include "./ui/ranklistUI.h"
#include "./ui/ranklistUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

RankListUI::RankListUI()
{
}
RankListUI::~RankListUI()
{

}

X_VOID   RankListUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_RANKLIST_SHOW);
	m_Event.push_back(GAME_EVENT_RANKLIST_UPDATA);


	
}
X_VOID	 RankListUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_RANKLIST_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_RANKLIST_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	RankListUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< RankListUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	RankListUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("RankListUIView", RankListUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("RankList.ccbi");
    
    ccbReader->release();
}

#include "./ui/bagOwnUI.h"
#include "./ui/bagOwnUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

BagOwnUI::BagOwnUI()
{
		nPage = 0;
}
BagOwnUI::~BagOwnUI()
{

}

X_VOID   BagOwnUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_BAGOWN_SHOW);
	m_Event.push_back(GAME_EVENT_BAGOWN_UPDATA);
	m_Event.push_back(GAME_EVENT_TIPITEM_SHOW); //get bag 

}
X_VOID	 BagOwnUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_BAGOWN_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_BAGOWN_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_TIPITEM_SHOW:
		//this->getTip();
		break;
	default:
		break;
	}  
}


X_VOID	BagOwnUI::getTip()
{
	if (m_bShow == XFALSE) return;

	static_cast< BagOwnUIView* >( m_pUi )->onTipResult();
}

X_VOID	BagOwnUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< BagOwnUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	BagOwnUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("BagOwnUIView", BagOwnUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("BagOwn.ccbi");
    
    ccbReader->release();
}

#include "./ui/rechargeUI.h"
#include "./ui/rechargeUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

rechargeUI::rechargeUI()
{
	

}
rechargeUI::~rechargeUI()
{

}

X_VOID   rechargeUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_RECHARGE_SHOW);
	m_Event.push_back(GAME_EVENT_RECHARGE_UPDATA);
	

}
X_VOID	 rechargeUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_RECHARGE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_RECHARGE_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	rechargeUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< rechargeUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	rechargeUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("rechargeUIView", rechargeUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("Recharge.ccbi");
    
    ccbReader->release();
}

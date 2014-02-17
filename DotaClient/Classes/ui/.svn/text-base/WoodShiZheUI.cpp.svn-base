#include "./ui/WoodShiZheUI.h"
#include "./ui/WoodShiZheUIView.h"
#include "./game/SendPacket.h"

USING_NS_CC_EXT;

WoodShiZheUI::WoodShiZheUI()
{
	this->m_MutexGroup =6;
}
WoodShiZheUI::~WoodShiZheUI()
{

}

X_VOID   WoodShiZheUI::CareEvent()
{
	m_Event.push_back(GAME_EVNET_WOODSHIZHE_SHOW);
	m_Event.push_back(GAME_EVNET_WOODSHIZHE_UPDATA);
	m_Event.push_back(GAME_EVNET_WOODSHIZHE_CLOSE);
 
}
X_VOID	 WoodShiZheUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVNET_WOODSHIZHE_SHOW:
		{
			SendLogicPacket::AskQuJingData();
			this->Show(XTRUE);
		}
	
		break;
	case GAME_EVNET_WOODSHIZHE_UPDATA:
		this->UpData();
		break;
	case GAME_EVNET_WOODSHIZHE_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
}

X_VOID	WoodShiZheUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< WoodShiZheUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	WoodShiZheUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("WoodShiZheUIView",WoodShiZheUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("QuJingShiZhe.ccbi");
    
    ccbReader->release();
}

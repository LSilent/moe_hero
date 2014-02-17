#include "./ui/EscortWoodUI.h"
#include "./ui/EscortWoodUIView.h"

USING_NS_CC_EXT;

EscortWoodUI::EscortWoodUI()
{
	this->m_MutexGroup =7;
	m_bShowBuzhen = false;
}
EscortWoodUI::~EscortWoodUI()
{

}

X_VOID   EscortWoodUI::CareEvent()
{
	m_Event.push_back(GAME_EVNET_LVL_ESCORTWOOD_SHOW);
	m_Event.push_back(GAME_EVNET_LVL_ESCORTWOOD_UPDATA);
	m_Event.push_back(GAME_EVNET_LVL_ESCORTWOOD_CLOSE);
	

}
X_VOID	 EscortWoodUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVNET_LVL_ESCORTWOOD_SHOW:
		m_bShowBuzhen = true;
		this->Show(XTRUE);
		break;
	case GAME_EVNET_LVL_ESCORTWOOD_UPDATA:
		this->UpData();
		break;
	case GAME_EVNET_LVL_ESCORTWOOD_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
}

X_VOID	EscortWoodUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< EscortWoodUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	EscortWoodUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("EscortWoodUIView", EscortWoodUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("QuJing.ccbi");
    
    ccbReader->release();
}

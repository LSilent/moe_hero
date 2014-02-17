#include "./ui/altarUI.h"
#include "./ui/altarUIView.h"

USING_NS_CC_EXT;

AltarUI::AltarUI()
{
	this->m_MutexGroup = 2;
}
AltarUI::~AltarUI()
{

}

X_VOID   AltarUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_ALTAR_SHOW);
	m_Event.push_back(GAME_EVENT_ALTAR_UPDATA);
	m_Event.push_back(GAME_EVENT_ALTAR_CLOSE);
}
X_VOID	 AltarUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_ALTAR_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_ALTAR_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_ALTAR_CLOSE:
		this->Show(XFALSE);
	default:
		break;
	}  
}

X_VOID	AltarUI::UpData()
{
	if (m_bShow == XFALSE) return;
	if(! UISystem::GetSingleton()->isCanUpdate(this) )return;

	static_cast< AltarUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	AltarUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("AltarUIView", AltarUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("Altar.ccbi");
    
    ccbReader->release();
}

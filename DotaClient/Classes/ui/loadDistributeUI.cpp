#include "./ui/loadDistributeUI.h"
#include "./ui/loadDistributeUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

LoadDistributeUI::LoadDistributeUI()
{
	this->m_MutexGroup = 2;
}
LoadDistributeUI::~LoadDistributeUI()
{

}

X_VOID   LoadDistributeUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_LOADDISTRIBUTE_SHOW);
	m_Event.push_back(GAME_EVENT_LOADDISTRIBUTE_UPDATA);
	m_Event.push_back(GAME_EVENT_LOADDISTRIBUTE_CLOSE);
 
}
X_VOID	 LoadDistributeUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_LOADDISTRIBUTE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_LOADDISTRIBUTE_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_LOADDISTRIBUTE_CLOSE:
		this->Show(XFALSE);
	default:
		break;
	}  
}

X_VOID	LoadDistributeUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< LoadDistributeUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	LoadDistributeUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("LoadDistributeUIView", LoadDistributeUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("LoadDistribute.ccbi");
    
    ccbReader->release();
}

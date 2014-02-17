#include "./ui/levelListUI.h"
#include "./ui/levelListUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./ui/element/mainSatusView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

LevelListUI::LevelListUI()
{
	this->m_MutexGroup = 0;
	this->m_Name = "copyscene";
}
LevelListUI::~LevelListUI()
{

}

X_VOID   LevelListUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_LEVELLIST_SHOW);
	m_Event.push_back(GAME_EVENT_LEVELLIST_UPDATA);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 LevelListUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_LEVELLIST_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_LEVELLIST_UPDATA:
		this->UpData();
		break;
	case GAME_EVNET_GUIDE_SHOW:
		if (this->GetName() == pEvent->m_vArg[0])
		{
			this->setTipId(DataPool::GetSingleton()->getGuideData()->GetCurrentTipId());
			if (!m_bShow || UISystem::GetSingleton()->getCurrentHanlerUi()!= this)
			{
				this->Show(XTRUE);
			}else
			{
				this->UpData();
			}
		}
	default:
		break;
	}  
}

X_VOID	LevelListUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< LevelListUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	LevelListUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
	ccNodeLoaderLibrary->registerCCNodeLoader("LevelListUIView", LevelListUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("LevelList.ccbi");
    
    ccbReader->release();
}

#include "./ui/heroUpgradeUI.h"
#include "./ui/heroUpgradeUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./ui/element/mainSatusView.h"
#include "./datapool/EquipOperator.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

HeroUpgradeUI::HeroUpgradeUI()
{
	this->m_MutexGroup = 2;
	this->m_Name = "heroUpgrade";
}
HeroUpgradeUI::~HeroUpgradeUI()
{

}

X_VOID   HeroUpgradeUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_HEROUPGRADE_SHOW);
	m_Event.push_back(GAME_EVENT_HEROUPGRADE_UPDATA);
	m_Event.push_back(GAME_EVENT_HEROUPGRADE_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 HeroUpgradeUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_HEROUPGRADE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_HEROUPGRADE_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_HEROUPGRADE_CLOSE:
		this->Show(XFALSE);
		break;
	case GAME_EVNET_GUIDE_SHOW:
		if (this->GetName() == pEvent->m_vArg[0])
		{
			this->setTipId(DataPool::GetSingleton()->getGuideData()->GetCurrentTipId());
			if (m_bShow)
// 			{
// 				this->Show(XTRUE);
// 			}else
			{
				this->UpData();
			}
		}
		break;	
	default:
		break;
	}  
}

X_VOID	HeroUpgradeUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroUpgradeUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroUpgradeUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroUpgradeUIView", HeroUpgradeUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("HeroUpgrade.ccbi");
    
    ccbReader->release();
}

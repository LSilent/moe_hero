#include "./ui/UserUpgradeUI.h"
#include "./ui/UserUpgradeUIView.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"


USING_NS_CC_EXT;

UserUpgradeUI::UserUpgradeUI()
{
	this->m_MutexGroup =6;
}
UserUpgradeUI::~UserUpgradeUI()
{

}

X_VOID   UserUpgradeUI::CareEvent()
{
	m_Event.push_back(GAME_EVNET_LVL_UPGRADE_SHOW);
	m_Event.push_back(GAME_EVNET_LVL_UPGRADE_UPDATA);
	m_Event.push_back(GAME_EVNET_LVL_UPGRADE_CLOSE);
	

}
X_VOID	 UserUpgradeUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVNET_LVL_UPGRADE_SHOW:
		{
			this->Show(XTRUE);
			break;
		}
	case GAME_EVNET_LVL_UPGRADE_UPDATA:
		this->UpData();
		break;
	case GAME_EVNET_LVL_UPGRADE_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
}

X_VOID	UserUpgradeUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< UserUpgradeUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	UserUpgradeUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("UserUpgradeUIView", UserUpgradeUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("UserUpgrade.ccbi");
    
    ccbReader->release();
}

#include "./ui/settingUI.h"
#include "./ui/settingUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./ui/element/mainSatusView.h"

USING_NS_CC_EXT;

SettingUI::SettingUI()
{
}
SettingUI::~SettingUI()
{

}

X_VOID   SettingUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_SETTING_SHOW);
	m_Event.push_back(GAME_EVENT_SETTING_UPDATA);
}
X_VOID	 SettingUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_SETTING_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_SETTING_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	SettingUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< SettingUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	SettingUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("SettingUIView", SettingUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("Setting.ccbi");
    
    ccbReader->release();
}

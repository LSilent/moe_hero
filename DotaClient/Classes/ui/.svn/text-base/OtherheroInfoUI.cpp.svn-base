#include "./ui/OtherheroInfoUI.h"
#include "./ui/otherheroInfoUView.h"
//#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

OtherHeroInfoUI::OtherHeroInfoUI()
{
	this->m_MutexGroup =2;
	this->m_Name = "OtherHeroInfo";
}
OtherHeroInfoUI::~OtherHeroInfoUI()
{

}

X_VOID   OtherHeroInfoUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_OTHERHEROINFO_SHOW);
	m_Event.push_back(GAME_EVENT_OTHERHEROINFO_CLOSE);
	m_Event.push_back(GAME_EVENT_OTHERHEROINFO_UPDATA);

}
X_VOID	 OtherHeroInfoUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_OTHERHEROINFO_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_OTHERHEROINFO_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_OTHERHEROINFO_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
}

X_VOID	OtherHeroInfoUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< OherHeroInfoUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	OtherHeroInfoUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("OtherHeroInfoUIView", OtherHeroInfoUIViewLoader::loader());
	//ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("OtherHeroInfo.ccbi");
    
    ccbReader->release();
}

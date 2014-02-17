#include "./ui/MainPageUI.h"
#include "./ui/MainPageUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"

USING_NS_CC_EXT;

MainPageUI::MainPageUI()
{
	this->m_Name = "main";
}
MainPageUI::~MainPageUI()
{

}

X_VOID   MainPageUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_MAINPAGE_SHOW);
	m_Event.push_back(GAME_EVENT_MAINPAGE_UPDATA);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

	m_Event.push_back(GAME_EVENT_CHATMESSAGE_UPDATA);
}
X_VOID	 MainPageUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_MAINPAGE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_CHATMESSAGE_UPDATA:
		{
			if (m_bShow &&  UISystem::GetSingleton()->isCanUpdate(this))
			{
				static_cast< MainPageUIView* >( m_pUi )->updateChatMessageInfo();
			}			
		}
		break;
	case GAME_EVENT_MAINPAGE_UPDATA:
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
		break;
	default:
		break;
	}  
}

X_VOID	MainPageUI::UpData()
{   
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< MainPageUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	MainPageUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("MainPageUIView", MainPageUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    
    
    
    
    m_pUi = ccbReader->readNodeGraphFromFile("MainPage.ccbi");
    
    ccbReader->release();
}

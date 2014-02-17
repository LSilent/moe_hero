#include "./ui/HeroFightChooseUI.h"
#include "./ui/HeroFightChooseUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

HeroFightChooseUI::HeroFightChooseUI()
{
	this->m_MutexGroup =1;
	this->m_Name = "choosehero";

}
HeroFightChooseUI::~HeroFightChooseUI()
{

}

X_VOID   HeroFightChooseUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_HEROFIGHTCHOOSE_SHOW);
	m_Event.push_back(GAME_EVENT_HEROFIGHTCHOOSE_UPDATA);
	m_Event.push_back(GAME_EVENT_HEROFIGHTCHOOSE_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 HeroFightChooseUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_HEROFIGHTCHOOSE_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_HEROFIGHTCHOOSE_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_HEROFIGHTCHOOSE_CLOSE:
		this->Show(XFALSE);
		break;
	case GAME_EVNET_GUIDE_SHOW:
		if (this->GetName() == pEvent->m_vArg[0])
		{
			this->setTipId(DataPool::GetSingleton()->getGuideData()->GetCurrentTipId());
			if (m_bShow )
			{
				this->UpData();
			}
		}
		break;
	default:
		break;
	}  
}

X_VOID	HeroFightChooseUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroFightChooseUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroFightChooseUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroFightChooseUIView", HeroFightChooseUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("HeroFightChoose.ccbi");
    
    ccbReader->release();
}

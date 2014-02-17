#include "./ui/heroRecruitUI.h"
#include "./ui/HeroRecruitUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

HeroRecruitUI::HeroRecruitUI()
{
	this->m_Name = "recruit";

}
HeroRecruitUI::~HeroRecruitUI()
{

}

X_VOID   HeroRecruitUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_RECRUIT_SHOW);
	m_Event.push_back(GAME_EVENT_RECRUIT_UPDATA);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

}
X_VOID	 HeroRecruitUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_RECRUIT_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_RECRUIT_UPDATA:
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

X_VOID	HeroRecruitUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroRecruitUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroRecruitUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("HeroRecruitUIView", HeroRecruitUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("HeroRecruit.ccbi");
    
    ccbReader->release();
}

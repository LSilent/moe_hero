#include "./ui/skillInspectUI.h"
#include "./ui/skillInspectUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"

USING_NS_CC_EXT;

SkillInspectUI::SkillInspectUI()
{
	this->m_MutexGroup = 2;
	this->m_Name = "skillinfo";
}
SkillInspectUI::~SkillInspectUI()
{
	 
}

X_VOID   SkillInspectUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_SKILLINSPECT_SHOW);
	m_Event.push_back(GAME_EVENT_SKILLINSPECT_UPDATA);
	m_Event.push_back(GAME_EVENT_SKILLINSPECT_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

	m_Event.push_back(GAME_EVENT_SKILLUPGRADE_STATUS_SUCCESS);
}
X_VOID	 SkillInspectUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_SKILLINSPECT_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_SKILLINSPECT_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_SKILLINSPECT_CLOSE:
		this->Show(XFALSE);
		break;
	case GAME_EVNET_GUIDE_SHOW:
		if (this->GetName() == pEvent->m_vArg[0])
		{
			this->setTipId(DataPool::GetSingleton()->getGuideData()->GetCurrentTipId());
			if (m_bShow)
			{
				this->UpData();
			}
		}
		break;
	case GAME_EVENT_SKILLUPGRADE_STATUS_SUCCESS:
		if(m_bShow)
		{
			static_cast< SkillInspectUIView* >( m_pUi )->skillUpgradeStatus( true );
		}
		break;
	default:
		break;
	}  
}

X_VOID	SkillInspectUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< SkillInspectUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	SkillInspectUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("SkillInspectUIView", SkillInspectUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("SkillInspect.ccbi");
    
    ccbReader->release();
}

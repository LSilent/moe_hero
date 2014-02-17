#include "./ui/SkillUpgradeEquiUI.h"
#include "./ui/SkillUpgradeEquiUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

SkillUpgradeEquiUI::SkillUpgradeEquiUI()
{
	this->m_MutexGroup = 3;
	this->m_Name = "selskillbook";
}
SkillUpgradeEquiUI::~SkillUpgradeEquiUI()
{

}

X_VOID   SkillUpgradeEquiUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_SKILLUPGRADE_EQU_SHOW);
	m_Event.push_back(GAME_EVENT_SKILLUPGRADE_EQU_UPDATA);
	m_Event.push_back(GAME_EVENT_SKILLUPGRADE_EQU_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 SkillUpgradeEquiUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_SKILLUPGRADE_EQU_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_SKILLUPGRADE_EQU_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_SKILLUPGRADE_EQU_CLOSE:
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

X_VOID	SkillUpgradeEquiUI::UpData()
{
	if (m_bShow == XFALSE) return;

	static_cast< SkillUpgradeEquiUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	SkillUpgradeEquiUI::OnCreate()
{
	if (m_pUi) return;

	/* Create an autorelease CCNodeLoaderLibrary. */
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

	ccNodeLoaderLibrary->registerCCNodeLoader("SkillUpgradeEquiUIView", SkillUpgradeEquiUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

	/* Create an autorelease CCBReader. */
	cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

	/* Read a ccbi file. */
	m_pUi = ccbReader->readNodeGraphFromFile("SkillUpgradeChooseEqui.ccbi");

	ccbReader->release();
}

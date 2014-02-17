#include "./ui/HeroEquipUI.h"
#include "./ui/HeroEquipUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"

USING_NS_CC_EXT;

HeroEquipUI::HeroEquipUI()
{
	this->m_MutexGroup = 2;
	this->m_Name = "selectequip";
}
HeroEquipUI::~HeroEquipUI()
{

}

X_VOID   HeroEquipUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_HERO_EQUI_SHOW);
	m_Event.push_back(GAME_EVENT_HERO_EQUI_UPDATA);
	m_Event.push_back(GAME_EVENT_HERO_EQUI_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 HeroEquipUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_HERO_EQUI_SHOW:
		{
		this->Show(XTRUE);
		}
		break;
	case GAME_EVENT_HERO_EQUI_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_HERO_EQUI_CLOSE:
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
	default:
		break;
	}  
}

X_VOID	HeroEquipUI::UpData()
{
	if (m_bShow == XFALSE) return;
	if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< HeroEquipUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	HeroEquipUI::OnCreate()
{
	if (m_pUi) return;

	/* Create an autorelease CCNodeLoaderLibrary. */
	CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();

	ccNodeLoaderLibrary->registerCCNodeLoader("HeroEquipUIView", HeroEquipUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

	/* Create an autorelease CCBReader. */
	cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);

	/* Read a ccbi file. */
	m_pUi = ccbReader->readNodeGraphFromFile("HeroEquip.ccbi");

	ccbReader->release();
}

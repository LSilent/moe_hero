#include "./ui/achievementUI.h"
#include "./ui/achievementUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

achievementUI::achievementUI()
{
	this->m_Name = "achievement";
	m_layer = -1;
	this->m_MutexGroup = 6;
}
achievementUI::~achievementUI()
{

}

X_VOID   achievementUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_ACHIEVE_SHOW);
	m_Event.push_back(GAME_EVENT_ACHIEVE_UPDATA);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

}
X_VOID	 achievementUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_ACHIEVE_SHOW:
		{
			if (pEvent->m_vArg.size() >=1)
			{
				if(pEvent->m_vArg[0] == "close")
					this->Show(XFALSE);
				return;
			}
			this->Show(XTRUE);
		}
	
		break;
	case GAME_EVENT_ACHIEVE_UPDATA:
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

X_VOID	achievementUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 
	static_cast< achievementUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	achievementUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("achievementUIView", achievementUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */

    m_pUi = ccbReader->readNodeGraphFromFile("achievement.ccbi");
    
    ccbReader->release();
}

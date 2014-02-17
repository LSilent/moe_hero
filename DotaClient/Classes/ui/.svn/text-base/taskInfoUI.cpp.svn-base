#include "./ui/taskInfoUI.h"
#include "./ui/taskInfoUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
USING_NS_CC_EXT;

taskInfoUI::taskInfoUI()
{
	//this->m_Name = "achievement";
}
taskInfoUI::~taskInfoUI()
{

}

X_VOID   taskInfoUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_TASKINFO_SHOW);
	m_Event.push_back(GAME_EVENT_TASKINFO_UPDATA);
	//m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

}
X_VOID	 taskInfoUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_TASKINFO_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_TASKINFO_UPDATA:
		this->UpData();
			break;
// 	case GAME_EVNET_GUIDE_SHOW:
// 		if (this->GetName() == pEvent->m_vArg[0])
// 		{
// 			this->setTipId(DataPool::GetSingleton()->getGuideData()->GetCurrentTipId());
// 			if (!m_bShow || UISystem::GetSingleton()->getCurrentHanlerUi()!= this)
// 			{
// 				this->Show(XTRUE);
// 			}else
// 			{
// 				this->UpData();
// 			}
// 		}
// 		break;
	default:
		break;
	}  
}

X_VOID	taskInfoUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 
	static_cast< taskInfoUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	taskInfoUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("taskInfoUIView", taskInfoUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainStatusView", MainStatusViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("taskInfo.ccbi");
    
    ccbReader->release();
}

#include "./ui/fightResultUI.h"
#include "./ui/fightResultUIView.h"
#include "./datapool/DataPool.h"

USING_NS_CC_EXT;

FightResultUI::FightResultUI()
{
	this->m_MutexGroup =7;
	this->m_Name = "battleresult";
}
FightResultUI::~FightResultUI()
{

}

X_VOID   FightResultUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_FIGHTRESULT_SHOW);
	m_Event.push_back(GAME_EVENT_FIGHTRESULT_UPDATA);
	m_Event.push_back(GAME_EVENT_FIGHTRESULT_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

}
X_VOID	 FightResultUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_FIGHTRESULT_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_FIGHTRESULT_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_FIGHTRESULT_CLOSE:
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

X_VOID	FightResultUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< FightResultUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	FightResultUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("FightResultUIView", FightResultUIViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("FightResult.ccbi");
    
    ccbReader->release();
}

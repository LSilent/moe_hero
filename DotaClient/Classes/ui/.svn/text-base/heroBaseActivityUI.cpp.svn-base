#include "./ui/heroBaseActivityUI.h"
#include "./ui/heroBaseActivityUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"

USING_NS_CC_EXT;

heroBaseActivityUI::heroBaseActivityUI()
	:m_ShowLayer(EM_SELFWOOD_LAYER_SHOW)
{
	this->m_MutexGroup = 0;
	m_BuilderIndex = 0;//EM_HEROBASE_WOOD
	this->m_Name = "heroBase";
}
heroBaseActivityUI::~heroBaseActivityUI()
{

}

X_VOID   heroBaseActivityUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_BASE_ACTIVITY_SHOW);
	m_Event.push_back(GAME_EVENT_BASE_ACTIVITY_UPDATA);
	m_Event.push_back(GAME_EVENT_BASE_ACTIVITY_CLOSE);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);
}
X_VOID	 heroBaseActivityUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	m_ShowLayer = EM_SELFWOOD_LAYER_SHOW;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_BASE_ACTIVITY_SHOW:
		{
			DataPool::GetSingleton()->SetSelectItem(0);
			DataPool::GetSingleton()->SetSelectSkill(0);
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				m_BuilderIndex =  UtilTools::StringToInt(str[0].c_str());

				if (str.size() > 1)
				{
					if(str[1] == "Revenge")
						m_ShowLayer = EM_REVENGEWOOD_LAYER_SHOW;
				}
			}
			this->Show(XTRUE);
			break;
		}
	case GAME_EVENT_BASE_ACTIVITY_UPDATA:
		{
			vector<string> str= pEvent->m_vArg;
			if (str.size () > 0 )
			{
				if(str[0] == "rob")
					m_ShowLayer = EM_ROBWOOD_LAYER_SHOW;
				else if(str[0] == "Revenge")
					m_ShowLayer = EM_REVENGEWOOD_LAYER_SHOW;
			}
			this->UpData();
		}
		break;
	case GAME_EVENT_BASE_ACTIVITY_CLOSE:
		this->Show(XFALSE);
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

X_VOID	heroBaseActivityUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< heroBaseActivityUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	heroBaseActivityUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("heroBaseActivityUIView", heroBaseActivityUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("heroBaseActivity.ccbi");
    
    ccbReader->release();



}

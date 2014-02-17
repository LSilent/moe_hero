#include "./ui/cheeseActivityUI.h"
#include "./ui/cheeseActivityUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/DataPool.h"
#include "./game/SendPacket.h"

USING_NS_CC_EXT;

cheeseActivityUI::cheeseActivityUI()
{
	this->m_MutexGroup = 0;
	m_HuoDongIndex = 0;
	m_layerXueZhan = EM_XUEZHAN_ENTER_LAYER_SHOW;
	m_layerShake = EM_SHAKE_INTRODUCE_LAYER_SHOW;
	this->m_Name = "cheeseActivity";
}
cheeseActivityUI::~cheeseActivityUI()
{

}

X_VOID   cheeseActivityUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_CHEESE_SHOW);
	m_Event.push_back(GAME_EVENT_CHEESE_UPDATA);
	m_Event.push_back(GAME_EVENT_CHEESE_CLOSE);
	m_Event.push_back(GAME_EVENT_BLOODBATTLE_SHOW);
	m_Event.push_back(GAME_EVENT_BLOODBATTLE_UPDATA);
	m_Event.push_back(GAME_EVNET_GUIDE_SHOW);

	m_Event.push_back(GAME_EVENT_SHAKE_SHOW);
	m_Event.push_back(GAME_EVENT_SHAKE_UPDATA);
}
X_VOID	 cheeseActivityUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_CHEESE_SHOW:
		{
			vector<string> str= pEvent->m_vArg;
 
			if (str.size() > 0)
			{
				m_HuoDongIndex =  UtilTools::StringToInt(str[0].c_str());
			}
			if (str.size() > 1)
			{
				m_layerXueZhan =  (EM_XUEZHAN_LAYER)UtilTools::StringToInt(str[0].c_str());
			}
			if (m_HuoDongIndex  == EM_BLOODBATTLE)
			{
				 SendLogicPacket::StairEnterPacket();
			}
			this->Show(XTRUE);
		}
		break;
	case GAME_EVENT_CHEESE_UPDATA:
		{
 
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				if (str[0] == "normal")
				{
					HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
					if (pData->getShakeHuoDongEnable() && pData->canShake() )
					{
						m_HuoDongIndex = EM_SHAKE;
						m_layerShake =  (EM_SHAKE_LAYER) EM_SHAKE_INTRODUCE_LAYER_SHOW;
					}
				}
			}
			this->UpData();
		}
		break;
	case GAME_EVENT_CHEESE_CLOSE:
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
	case GAME_EVENT_BLOODBATTLE_SHOW:
		{
			m_layerXueZhan = EM_XUEZHAN_BATTLE_LAYER_SHOW;
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				m_layerXueZhan =  EM_XUEZHAN_LAYER(UtilTools::StringToInt(str[0].c_str()));
			}
			m_HuoDongIndex = EM_BLOODBATTLE;
			this->Show(XTRUE);
		}
		break;
	case GAME_EVENT_BLOODBATTLE_UPDATA:
		{
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				m_layerXueZhan =  EM_XUEZHAN_LAYER(UtilTools::StringToInt(str[0].c_str()));
			}
			m_HuoDongIndex = EM_BLOODBATTLE;
			this->UpData();
		}
		
		break;
	case GAME_EVENT_SHAKE_SHOW:
		{
			m_layerShake = EM_SHAKE_INTRODUCE_LAYER_SHOW;
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				m_layerShake =  EM_SHAKE_LAYER(UtilTools::StringToInt(str[0].c_str()));//EM_SHAKE_LAYER
			}
			m_HuoDongIndex = EM_SHAKE;
			this->Show(XTRUE);
		}
		break;
	case GAME_EVENT_SHAKE_UPDATA:
		{
			vector<string> str= pEvent->m_vArg;
			if (str.size() > 0)
			{
				m_layerShake =  EM_SHAKE_LAYER(UtilTools::StringToInt(str[0].c_str()));//EM_SHAKE_LAYER
			}
			m_HuoDongIndex = EM_SHAKE;
			this->UpData();
		}

		break;
	default:
		break;
	}  
}

X_VOID	cheeseActivityUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;

	static_cast< cheeseActivityUIView* >( m_pUi )->onDataUpdate( true );
}
 

X_VOID	cheeseActivityUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("cheeseActivityUIView", cheeseActivityUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("CheeseActivity.ccbi");
    
    ccbReader->release();
}

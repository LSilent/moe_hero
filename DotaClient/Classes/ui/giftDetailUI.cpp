#include "./ui/giftDetailUI.h"
#include "./ui/giftDetailUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

giftDetailUI::giftDetailUI()
{
	this->m_MutexGroup = 6;
	giftId = -1;
}
giftDetailUI::~giftDetailUI()
{

}

X_VOID   giftDetailUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_GIFTDETAIL_SHOW);
  
}
X_VOID	 giftDetailUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_GIFTDETAIL_SHOW:
		{
			if (pEvent->m_vArg.size() > 0)
			{
				if (pEvent->m_vArg.at(0) == "close")
				{
					this->Show(XFALSE);
				}else
				{
					giftId = UtilTools::StringToInt(pEvent->m_vArg.at(0).c_str());
					this->Show(XTRUE);
				}
			}else
			{
				this->Show(XTRUE);
			}
		}
		break;
	default:
		break;
	}  
}

X_VOID	giftDetailUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< giftDetailUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	giftDetailUI::OnCreate()
{
	if (m_pUi) return;
	giftDetailUIView *layer=  giftDetailUIView::create();
	m_pUi  = (cocos2d::CCNode*)layer;
	layer->setUserData(this);
	  
}

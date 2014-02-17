#include "./ui/placardUI.h"
#include "./ui/placardUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

placardUI::placardUI()
{
	this->m_MutexGroup = 9;
}
placardUI::~placardUI()
{

}

X_VOID   placardUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_PLACARD_SHOW);
  
}
X_VOID	 placardUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_PLACARD_SHOW:
		{
			if (pEvent->m_vArg.size() > 0)
			{
				this->Show(XFALSE);
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

X_VOID	placardUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< placardUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	placardUI::OnCreate()
{
	if (m_pUi) return;
	placardUIView *layer=  placardUIView::create();
	m_pUi  = (cocos2d::CCNode*)layer;
	layer->setUserData(this);
	  
}

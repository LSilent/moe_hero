#include "./ui/UpdataUi.h"
#include "./ui/UpdataView.h"
 

UpdataUi::UpdataUi()
{
	 
}
UpdataUi::~UpdataUi()
{
 
}

X_VOID   UpdataUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_UPDATAUI_SHOW);
	m_Event.push_back(GAME_EVENT_LOGIN_SHOW);
 
}
X_VOID		 UpdataUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_UPDATAUI_SHOW:
        {
			this->Show(XTRUE);
        }
		break;
	case GAME_EVENT_LOGIN_SHOW:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
	 
}
X_VOID	UpdataUi::OnCreate()
{
	if (m_pUi) return;
	 UpdataView *layer=  UpdataView::create();
	 m_pUi  = (cocos2d::CCNode*)layer;
	//layer->setUserData(this);
	 
}
 


#include "./ui/logoUi.h"
#include "./ui/logoView.h"
#include "./Game.h"
logoUi::logoUi()
{
	 
}
logoUi::~logoUi()
{
 
}

X_VOID   logoUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_LOGO_SHOW);
	m_Event.push_back(GAME_EVENT_LOGIN_SHOW);
	m_Event.push_back(GAME_EVENT_UPDATAUI_SHOW);
 
}

X_VOID		 logoUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_LOGO_SHOW:
		{
			this->Show(XTRUE);
		}
		break;
	case GAME_EVENT_LOGIN_SHOW:
	case GAME_EVENT_UPDATAUI_SHOW:
		
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
	 
}
X_VOID	logoUi::OnCreate()
{
	if (m_pUi) return;
	logoView *layer=  logoView::create();
	m_pUi  = (cocos2d::CCNode*)layer;
	layer->setUserData(this);
}
X_VOID	logoUi::OnShow()
{
	((logoView *)(m_pUi))->startschedule();

}
X_VOID	logoUi::connectServer()
{
	Game::Connect();
}
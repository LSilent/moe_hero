#include "./ui/TipUi.h"
#include "./ui/TipUiView.h"
 
X_VOID   TipUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_TIP_SHOW);
	m_Event.push_back(GAME_EVENT_TIP_UPDATA);
	m_tips.clear();

}
TipUi::TipUi()
{
	this->m_MutexGroup = 8;
	bHandleTouchEvent =false;
}
TipUi::~TipUi()
{


}
X_VOID		 TipUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	/*case GAME_EVENT_TIP_SHOW:
		{
			this->Show(XTRUE);
		}
		break;*/
	case GAME_EVENT_TIP_UPDATA:
		{
			m_tips =  pEvent->m_vArg;
			this->UpData();
		}
		break;
	default:
		break;
	}  

}
X_VOID	TipUi::OnCreate()
{
	TipView *layer=  TipView::create();
	m_pUi  = (cocos2d::CCNode*)layer;
	layer->setTouchEnabled(false);
	layer->setUserData(this);
}
X_VOID	TipUi::UpData()
{
	OnCreate();
	SceneManger::GetSingleton()->AddChildToScene(m_pUi,bHandleTouchEvent);
	static_cast< TipView* >( m_pUi )->onDataUpdate(m_tips);
}
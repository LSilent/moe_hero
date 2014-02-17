#include "./ui/NoticeUi.h"
#include "./ui/NoticeUIView.h"
 
X_VOID   NoticeUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_MAINPAGE_SHOW);
	// m_Event.push_back(GAME_EVENT_TIP_UPDATA);
	m_Event.push_back(GAME_EVENT_NOTICE_UPDATA);

	m_tips.clear();

}
NoticeUi::NoticeUi()
{
	this->m_MutexGroup = 8;
	bHandleTouchEvent = false;
}
NoticeUi::~NoticeUi()
{


}
X_VOID		 NoticeUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	//case GAME_EVENT_TIP_UPDATA:

	case GAME_EVENT_MAINPAGE_SHOW:
	case GAME_EVENT_NOTICE_UPDATA:
		{
			m_tips =  pEvent->m_vArg;
			this->UpData();
		}
		break;
	default:
		break;
	}  

}
X_VOID	NoticeUi::OnCreate()
{
	if (m_pUi) return;
	NoticeView *layer=  NoticeView::create();
	m_pUi  = (cocos2d::CCNode*)layer;

	layer->setTouchEnabled(false);
	layer->setUserData(this);
}
X_VOID	NoticeUi::UpData()
{
	if (m_bShow == XFALSE)
	{
		OnCreate();
		SceneManger::GetSingleton()->AddChildToScene(m_pUi,bHandleTouchEvent);
		m_bShow = true;
	}


	static_cast< NoticeView* >( m_pUi )->onDataUpdate(m_tips);
}
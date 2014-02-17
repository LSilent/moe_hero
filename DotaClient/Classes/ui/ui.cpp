#include "./ui/ui.h"
#include "./event/EventSystem.h"
#include "ui/UISystem.h"
 UI::UI()
 {
	 m_Event.clear();
	 m_pUi = NULL;
	 m_bShow = XFALSE;
	 m_MutexGroup = 0;
	 bHandleTouchEvent = true;
	 m_tipId =-1;
	 
 }
 UI::~UI()
 {
	 Release();
 }
 X_VOID			UI::Init()
 {
	 CareEvent();
	 RegisterGameEvent();
 }
 X_VOID			UI::Release()
{
	UnRegisterGameEvent();
	m_Event.clear();
	ReleaseUI();
	m_tipId = -1;
}

 X_VOID		UI::ReleaseUI()
 {
	 if (m_pUi)
	 { 
		 m_pUi = X_NULL; 
	 }
	 m_bShow = XFALSE;
 }

X_VOID	UI::Show(X_BOOL show)
{
	
	if (m_bShow && show)
	{
	#ifdef UI_SHOW_RECREAT
 
			UISystem::GetSingleton()->setLock(true);
			UISystem::GetSingleton()->onUIShowHide(this,XFALSE);
			this->ReleaseUI();
	 
	#else
		 UISystem::GetSingleton()->onFrontUI(this);
		 return;
	#endif  
 
	}
	UISystem::GetSingleton()->setLock(false);
	if (m_pUi == X_NULL)
	{
		if(show != XTRUE) return;
		this->OnCreate();
		//m_pUi->retain();
	}
	m_bShow = show;
	UISystem::GetSingleton()->onUIShowHide(this,show);
	if (show && !UISystem::GetSingleton()->CheckMutex(this))
	{
		m_bShow = false;
		return;
	}

}
X_VOID  UI::RegisterGameEvent()
{
	vector<GAME_EVENT_ID>::const_iterator iEnd = m_Event.end();
	for (vector<GAME_EVENT_ID>::const_iterator iter = m_Event.begin() ;iter!= iEnd ; ++iter)
	{
		RegisterGameEvent(*iter);
	}

}
 X_VOID  UI::RegisterGameEvent(GAME_EVENT_ID eventId,X_BOOL push)
 {
	 if (push == XTRUE)
	 {	
		 m_Event.push_back(eventId);
	 } 

	 EventSystem::GetSingleton()->RegisterEventFunctionHandle(eventId,UISystem::OnGameEvent,(X_UINT)(this));

 }
 X_VOID UI::UnRegisterGameEvent(GAME_EVENT_ID eventId) 
 {
	 EventSystem::GetSingleton()->UnRegisterEventFunctionHandle(eventId,UISystem::OnGameEvent,X_UINT(this));
 
 }
 X_VOID UI::UnRegisterGameEvent()
{
	vector<GAME_EVENT_ID>::const_iterator iEnd = m_Event.end();
	for (vector<GAME_EVENT_ID>::const_iterator iter = m_Event.begin() ;iter!= iEnd ; iter++)
	{
		UnRegisterGameEvent(*iter);
	}
}
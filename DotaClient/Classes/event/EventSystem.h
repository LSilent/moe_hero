 
#ifndef __EVENTSYSTEM_H__
#define __EVENTSYSTEM_H__
 
#include "./base/Global.h"

#include "./base/Singleton.h"
#include "./event/EventDefine.h"
#include <map>
using namespace std;
class EventSystem : public Singleton<EventSystem>
{

	DECLARE_SINGLETON(EventSystem);
public:
	EventSystem();
	virtual ~EventSystem();
	static const std::vector<string> NULL_EVENT_PARAM;
public:
	
	X_VOID			Initial();
	X_VOID			Tick(X_UINT nTime);
	X_VOID			Release();

	X_BOOL			RegisterEventFunctionHandle(GAME_EVENT_ID nEventID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData=X_NULL);
	X_BOOL			UnRegisterEventFunctionHandle(GAME_EVENT_ID nEventID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData=X_NULL);

	X_BOOL			RegisterEventFunctionHandle(const string& szEventStringID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData=X_NULL);
	X_BOOL			UnRegisterEventFunctionHandle(const string& szEventStringID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData=X_NULL);

	X_VOID			PushEvent(GAME_EVENT_ID nEventIntID, const std::vector<string>& vParam = NULL_EVENT_PARAM);
	X_VOID			PushEvent(const string& szEventStringID, const std::vector<string>& vParam = NULL_EVENT_PARAM);

	X_VOID			PushEventAndProcessNow(GAME_EVENT_ID nEventIntID, const std::vector<string>& vParam = NULL_EVENT_PARAM);
	X_VOID			PushEventAndProcessNow(const string& szEventStringID, const std::vector<string>& vParam = NULL_EVENT_PARAM);

	//static X_VOID		OnPushEvent(const X_CHAR* szEventStringID, const std::vector<X_CHAR*>& vParam);
	//static X_VOID		OnPushEvent(const string &szEventStringID, const std::vector<string>& vParam);
 
private:

	X_VOID			_PushEvent(const tGameEventData& event);
	X_VOID			_ProcessEvent(const tGameEventData& event);

private:
	std::list<tGameEventDefine>					m_EventDefineList;
	std::map<string, tGameEventDefine*>		m_EventDefineMapByStringID;
	std::map<GAME_EVENT_ID, tGameEventDefine*>	m_EventDefineMapByIntID;		
	std::list<tGameEventData>					m_EventQueue;							
 
};
#endif
 
#include "./event/EventSystem.h"
#include "./event/EventDefine.h"

IMPLEMENT_SINGLETON(EventSystem);

const std::vector<string> EventSystem::NULL_EVENT_PARAM;
EventSystem::EventSystem()
{
	
}

EventSystem::~EventSystem()
{
}

X_VOID EventSystem::Initial()
{
	m_EventDefineList.clear();
	m_EventDefineMapByIntID.clear();
	m_EventDefineMapByStringID.clear();
	m_EventQueue.clear();
	static tGameEventDefine GameEventDefine[] = {
			
		{GAME_EVENT_UPDATAUI_SHOW,						            "GAME_EVENT_UPDATAUI_SHOW"},
		{GAME_EVENT_INIT,						            "GAME_EVENT_INIT"},

		{GAME_EVENT_LOGO_SHOW,						        "GAME_EVENT_LOGO_SHOW"},
		{GAME_EVENT_LOGIN_SHOW,								"GAME_EVENT_LOGIN_SHOW"},
		{GAME_EVENT_MAINPAGE_SHOW,						    "GAME_EVENT_MAINPAGE_SHOW"},
		{GAME_EVENT_MAINPAGE_UPDATA,						 "GAME_EVENT_MAINPAGE_UPDATA"},

		
		{GAME_EVENT_BATTLE_SHOW,						    "GAME_EVENT_BATTLE_SHOW"},
		{GAME_EVENT_ACTIVITIES_SHOW,					    "GAME_EVENT_ACTIVITIES_SHOW"},
		{GAME_EVENT_LOGIN_CLOSE,						    "GAME_EVENT_LOGIN_CLOSE"},
		{GAME_EVENT_SELECTROLE_SHOW,						"GAME_EVENT_SELECTROLE_SHOW"},
		{GAME_EVENT_UPDATA_PACKET,							"GAME_EVENT_UPDATA_PACKET"},
		{GAME_EVENT_BATTLEFIELD_SHOW,						"GAME_EVENT_BATTLEFIELD_SHOW"},
		{GAME_EVENT_BATTLEFIELD_CLOSE,						"GAME_EVENT_BATTLEFIELD_CLOSE"},

		{GAME_EVENT_RECRUIT_SHOW,						    "GAME_EVENT_RECRUIT_SHOW"},
		{GAME_EVENT_RECRUIT_UPDATA,						    "GAME_EVENT_RECRUIT_UPDATA"},

		{GAME_EVENT_HEROBOOK_SHOW,						    "GAME_EVENT_HEROBOOK_SHOW"},
		{GAME_EVENT_HEROBOOK_UPDATA,						"GAME_EVENT_HEROBOOK_UPDATA"},

		{GAME_EVENT_SECRETSTORE_SHOW,						"GAME_EVENT_SECRETSTORE_SHOW"},
		{GAME_EVENT_SECRETSTORE_UPDATA,						"GAME_EVENT_SECRETSTORE_UPDATA"},

		{GAME_EVENT_LOADDISTRIBUTE_SHOW,					"GAME_EVENT_LOADDISTRIBUTE_SHOW"},
		{GAME_EVENT_LOADDISTRIBUTE_UPDATA,					"GAME_EVENT_LOADDISTRIBUTE_UPDATA"},
		{GAME_EVENT_LOADDISTRIBUTE_CLOSE,					"GAME_EVENT_LOADDISTRIBUTE_UPDATA"},
 
		{GAME_EVENT_HEROINFO_SHOW,					        "GAME_EVENT_HEROINFO_SHOW"},
		{GAME_EVENT_HEROINFO_UPDATA,					    "GAME_EVENT_HEROINFO_UPDATA"},
		{GAME_EVENT_HEROINFO_CLOSE,							"GAME_EVENT_HEROINFO_CLOSE"},

		

		{GAME_EVENT_HEROFIGHTCHOOSE_SHOW,					"GAME_EVENT_HEROFIGHTCHOOSE_SHOW"},
		{GAME_EVENT_HEROFIGHTCHOOSE_UPDATA,					"GAME_EVENT_HEROFIGHTCHOOSE_UPDATA"},
		{GAME_EVENT_HEROFIGHTCHOOSE_CLOSE,					"GAME_EVENT_HEROFIGHTCHOOSE_CLOSE"},
		

		{GAME_EVENT_BAGOWN_SHOW,					        "GAME_EVENT_BAGOWN_SHOW"},
		{GAME_EVENT_BAGOWN_UPDATA,					        "GAME_EVENT_BAGOWN_UPDATA"},

		{GAME_EVENT_TEAMLIST_SHOW,					        "GAME_EVENT_TEAMLIST_SHOW"},
		{GAME_EVENT_TEAMLIST_UPDATA,					    "GAME_EVENT_TEAMLIST_UPDATA"},

		{GAME_EVENT_EQUIPMENTINSPECT_SHOW,					"GAME_EVENT_EQUIPMENTINSPECT_SHOW"},
		{GAME_EVENT_EQUIPMENTINSPECT_UPDATA,				"GAME_EVENT_EQUIPMENTINSPECT_UPDATA"},
		{GAME_EVENT_EQUIPMENTINSPECT_CLOSE,				    "GAME_EVENT_EQUIPMENTINSPECT_CLOSE"},
	
		{GAME_EVENT_EQUIPMENTALL_SHOW,					    "GAME_EVENT_EQUIPMENTALL_SHOW"},
		{GAME_EVENT_EQUIPMENTALL_UPDATA,				    "GAME_EVENT_EQUIPMENTALL_UPDATA"},

		{GAME_EVENT_HEROEVOLVE_SHOW,					    "GAME_EVENT_HEROEVOLVE_SHOW"},
		{GAME_EVENT_HEROEVOLVE_UPDATA,				        "GAME_EVENT_HEROEVOLVE_UPDATA"},
		{GAME_EVENT_HEROEVOLVE_CLOSE,                       "GAME_EVENT_HEROEVOLVE_CLOSE"},

		{GAME_EVENT_HEROUPGRADE_SHOW,					    "GAME_EVENT_HEROUPGRADE_SHOW"},
		{GAME_EVENT_HEROUPGRADE_UPDATA,				        "GAME_EVENT_HEROUPGRADE_UPDATA"},
		{GAME_EVENT_HEROUPGRADE_CLOSE,                      "GAME_EVENT_HEROUPGRADE_CLOSE"},

		{GAME_EVENT_SKILLINSPECT_SHOW,					    "GAME_EVENT_SKILLINSPECT_SHOW"},
		{GAME_EVENT_SKILLINSPECT_UPDATA,				    "GAME_EVENT_SKILLINSPECT_UPDATA"},
		{GAME_EVENT_SKILLINSPECT_CLOSE,				        "GAME_EVENT_SKILLINSPECT_CLOSE"},

		{GAME_EVENT_SETTING_SHOW,					        "GAME_EVENT_SETTING_SHOW"},
		{GAME_EVENT_SETTING_UPDATA,				            "GAME_EVENT_SETTING_UPDATA"},

		{GAME_EVENT_LEVELLIST_SHOW,					        "GAME_EVENT_LEVELLIST_SHOW"},
		{GAME_EVENT_LEVELLIST_UPDATA,				        "GAME_EVENT_LEVELLIST_UPDATA"},
        
		{GAME_EVENT_MESSAGE_SHOW,					        "GAME_EVENT_MESSAGE_SHOW"},
		{GAME_EVENT_MESSAGE_UPDATA,				            "GAME_EVENT_MESSAGE_UPDATA"},

		{GAME_EVENT_RANKLIST_SHOW,					        "GAME_EVENT_RANKLIST_SHOW"},
		{GAME_EVENT_RANKLIST_UPDATA,				        "GAME_EVENT_RANKLIST_UPDATA"},

		{GAME_EVENT_ALTAR_SHOW,					            "GAME_EVENT_ALTAR_SHOW"},
		{GAME_EVENT_ALTAR_UPDATA,				            "GAME_EVENT_ALTAR_UPDATA"},
		{GAME_EVENT_ALTAR_CLOSE,				            "GAME_EVENT_ALTAR_CLOSE"},
		{GAME_EVENT_TIP_SHOW,				                "GAME_EVENT_TIP_SHOW"},
		{GAME_EVENT_TIP_UPDATA,							 	"GAME_EVENT_TIP_UPDATA"},
		 

		{GAME_EVENT_FIGHTRESULT_SHOW,					    "GAME_EVENT_FIGHTRESULT_SHOW"},
		{GAME_EVENT_FIGHTRESULT_UPDATA,				        "GAME_EVENT_FIGHTRESULT_UPDATA"},
		{GAME_EVENT_FIGHTRESULT_CLOSE,				        "GAME_EVENT_FIGHTRESULT_CLOSE"},
		{GAME_EVENT_TIPITEM_SHOW,							 "GAME_EVENT_TIPITEM_SHOW"},
		{GAME_EVENT_TIPITEM_CLOSE,							"GAME_EVENT_TIPITEM_CLOSE"},
  

		{GAME_EVENT_SKILLUPGRADE_EQU_SHOW,					"GAME_EVENT_SKILLUPGRADE_EQU_SHOW"},
		{GAME_EVENT_SKILLUPGRADE_EQU_UPDATA,				"GAME_EVENT_SKILLUPGRADE_EQU_UPDATA"},
		{GAME_EVENT_SKILLUPGRADE_EQU_CLOSE,					"GAME_EVENT_SKILLUPGRADE_EQU_CLOSE"},

		{GAME_EVENT_SKILLUPGRADE_STATUS_SUCCESS,            "GAME_EVENT_SKILLUPGRADE_STATUS_SUCCESS"},

		{GAME_EVENT_HERO_EQUI_SHOW,							"GAME_EVENT_HERO_EQUI_SHOW"},
		{GAME_EVENT_HERO_EQUI_UPDATA,						"GAME_EVENT_HERO_EQUI_UPDATA"},
		{GAME_EVENT_HERO_EQUI_CLOSE,						"GAME_EVENT_HERO_EQUI_CLOSE"},


		{GAME_EVENT_EQUIPMENT_SELL_SHOW,						"GAME_EVENT_EQUIPMENT_SELL_SHOW"},
		{GAME_EVENT_EQUIPMENT_SELL_UPDATA,						"GAME_EVENT_EQUIPMENT_SELL_UPDATA"},
		{GAME_EVENT_EQUIPMENT_SELL_CLOSE,						"GAME_EVENT_EQUIPMENT_SELL_CLOSE"},

		{GAME_EVENT_USER_INFO_SHOW,							"GAME_EVENT_USER_INFO_SHOW"},
		{GAME_EVENT_USER_INFO_UPDATA,						"GAME_EVENT_USER_INFO_UPDATA"},
		{GAME_EVENT_USER_INFO_CLOSE,						"GAME_EVENT_USER_INFO_CLOSE"},
		{GAME_EVENT_USER_INFO_BUY_ACTION,                   "GAME_EVENT_USER_INFO_BUY_ACTION"},

		{GAME_EVENT_CHEESE_SHOW,							"GAME_EVENT_CHEESE_SHOW"},
		{GAME_EVENT_CHEESE_UPDATA,						"GAME_EVENT_CHEESE_UPDATA"},
		{GAME_EVENT_CHEESE_CLOSE,						"GAME_EVENT_CHEESE_CLOSE"},

		{GAME_EVENT_NOTICE_UPDATA,						"GAME_EVENT_NOTICE_UPDATA"},
		
		{GAME_EVNET_LVL_UPGRADE_SHOW,							"GAME_EVNET_LVL_UPGRADE_SHOW"},
		{GAME_EVNET_LVL_UPGRADE_UPDATA,						"GAME_EVNET_LVL_UPGRADE_UPDATA"},
		{GAME_EVNET_LVL_UPGRADE_CLOSE,						"GAME_EVNET_LVL_UPGRADE_CLOSE"},

		{GAME_EVENT_RECHARGE_SHOW,						"GAME_EVENT_RECHARGE_SHOW"},
		{GAME_EVENT_RECHARGE_UPDATA,						"GAME_EVENT_RECHARGE_UPDATA"},

		{GAME_EVENT_CHATMESSAGE_SHOW,						"GAME_EVENT_CHATMESSAGE_SHOW"},
		{GAME_EVENT_CHATMESSAGE_UPDATA,						"GAME_EVENT_CHATMESSAGE_UPDATA"},

		{GAME_EVENT_ACHIEVE_SHOW,						"GAME_EVENT_ACHIEVE_SHOW"},
		{GAME_EVENT_ACHIEVE_UPDATA,						"GAME_EVENT_ACHIEVE_UPDATA"},
		{GAME_EVNET_GUIDE_SHOW,							"GAME_EVNET_GUIDE_SHOW"},

		{GAME_EVENT_TASKINFO_SHOW,						"GAME_EVENT_TASKINFO_SHOW"},
		{GAME_EVENT_TASKINFO_UPDATA,						"GAME_EVENT_TASKINFO_UPDATA"},
		
		{GAME_EVNET_USER_LOGIN_SHOW,						"GAME_EVNET_USER_LOGIN_SHOW"},
		{GAME_EVNET_USER_LOGIN_UPDATA,						"GAME_EVNET_USER_LOGIN_UPDATA"},
		{GAME_EVNET_USER_LOGIN_CLOSE,						"GAME_EVNET_USER_LOGIN_CLOSE"},

		{GAME_EVNET_USER_REG_FAILED,						"GAME_EVNET_USER_REG_FAILED"},
		{GAME_EVNET_USER_REG_SUCCESS,						"GAME_EVNET_USER_REG_SUCCESS"},
		{GAME_EVNET_USER_CHECK_FAILED,						"GAME_EVNET_USER_CHECK_FAILED"},
		{GAME_EVNET_USER_CHECK_SUCCESS,						"GAME_EVNET_USER_CHECK_SUCCESS"},

		{GAME_EVENT_BASE_ACTIVITY_SHOW,						"GAME_EVENT_BASE_ACTIVITY_SHOW"},
		{GAME_EVENT_BASE_ACTIVITY_UPDATA,						"GAME_EVENT_BASE_ACTIVITY_UPDATA"},
		{GAME_EVENT_BASE_ACTIVITY_CLOSE,						"GAME_EVENT_BASE_ACTIVITY_CLOSE"},

		{GAME_EVENT_HEROWOODFIGHTCHOOSE_SHOW,					"GAME_EVENT_HEROWOODFIGHTCHOOSE_SHOW"},
		{GAME_EVENT_HEROWOODFIGHTCHOOSE_UPDATA,					"GAME_EVENT_HEROWOODFIGHTCHOOSE_UPDATA"},
		{GAME_EVENT_HEROWOODFIGHTCHOOSE_CLOSE,					"GAME_EVENT_HEROWOODFIGHTCHOOSE_CLOSE"},
		 
		{GAME_EVENT_OTHERHEROINFO_SHOW,							"GAME_EVENT_OTHERHEROINFO_SHOW"},
		{GAME_EVENT_OTHERHEROINFO_UPDATA,						"GAME_EVENT_OTHERHEROINFO_UPDATA"},
		{GAME_EVENT_OTHERHEROINFO_CLOSE,						"GAME_EVENT_OTHERHEROINFO_CLOSE"},

		{GAME_EVENT_BLOODBATTLE_SHOW,						"GAME_EVENT_BLOODBATTLE_SHOW"},
		{GAME_EVENT_BLOODBATTLE_UPDATA,						"GAME_EVENT_BLOODBATTLE_UPDATA"},
		{GAME_EVENT_BLOODBATTLE_CLOSE,						"GAME_EVENT_BLOODBATTLE__CLOSE"},

		{GAME_EVNET_LVL_ESCORTWOOD_SHOW,						"GAME_EVNET_LVL_ESCORTWOOD_SHOW"},
		{GAME_EVNET_LVL_ESCORTWOOD_UPDATA,						"GAME_EVNET_LVL_ESCORTWOOD_UPDATA"},
		{GAME_EVNET_LVL_ESCORTWOOD_CLOSE,						"GAME_EVNET_LVL_ESCORTWOOD_CLOSE"},

		{GAME_EVNET_WOODSHIZHE_SHOW,						"GAME_EVNET_WOODSHIZHE_SHOW"},
		{GAME_EVNET_WOODSHIZHE_UPDATA,						"GAME_EVNET_WOODSHIZHE_UPDATA"},
		{GAME_EVNET_WOODSHIZHE_CLOSE,						"GAME_EVNET_WOODSHIZHE_CLOSE"},
		{GAME_EVENT_PLACARD_SHOW,							"GAME_EVENT_PLACARD_SHOW£¬"},
		{GAME_EVENT_GIFTDETAIL_SHOW,							"GAME_EVENT_GIFTDETAIL_SHOW"},
		
		{GAME_EVENT_SHAKE_SHOW,								"GAME_EVENT_SHAKE_SHOW"},
		{GAME_EVENT_SHAKE_UPDATA,							"GAME_EVENT_SHAKE_UPDATA£¬"},
	 
	 
	};
	X_INT nGameEventDefineCount = sizeof(GameEventDefine) / sizeof(tGameEventDefine);
	 
	for(X_INT i=0; i<nGameEventDefineCount; i++)
	{
		m_EventDefineList.push_back(GameEventDefine[i]);
		m_EventDefineMapByIntID[(GAME_EVENT_ID)(GameEventDefine[i].m_nEventIntID)] = &(m_EventDefineList.back());
		m_EventDefineMapByStringID[GameEventDefine[i].m_szEventStringID] = &(m_EventDefineList.back());
	}
}

X_VOID EventSystem::Tick(X_UINT nTime)
{
	std::list<tGameEventData>::iterator it;
	for(it=m_EventQueue.begin(); it!=m_EventQueue.end(); ++it)
	{
		_ProcessEvent(*it);
	}
	m_EventQueue.clear();
}


X_VOID EventSystem::Release()
{
	m_EventDefineList.clear();
	m_EventDefineMapByIntID.clear();
	m_EventDefineMapByStringID.clear();
	m_EventQueue.clear();
}

 
X_BOOL EventSystem::RegisterEventFunctionHandle(GAME_EVENT_ID nEventID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData)
{
	tGameEventDefine* pEventDefine = m_EventDefineMapByIntID[nEventID];
	if(!pEventDefine) 
	{
		return XFALSE;
	}
	pEventDefine->m_FunctionHandleList.push_back(std::make_pair(hFunctionHandle, uOwnerData));
	return XTRUE;
 
}

X_BOOL EventSystem::UnRegisterEventFunctionHandle(GAME_EVENT_ID nEventID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData)
{
	tGameEventDefine* pEventDefine = m_EventDefineMapByIntID[nEventID];
	if(!pEventDefine) 
	{
		return XFALSE;
	}
	pEventDefine->m_FunctionHandleList.remove(std::make_pair(hFunctionHandle, uOwnerData));
	return XTRUE;

}
X_BOOL EventSystem::RegisterEventFunctionHandle(const string& szEventStringID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData)
{
	tGameEventDefine* pEventDefine = m_EventDefineMapByStringID[szEventStringID];
	if(!pEventDefine) 
	{
		return XFALSE;
	}
	pEventDefine->m_FunctionHandleList.push_back(std::make_pair(hFunctionHandle, uOwnerData));
	return XTRUE;
 
}
 
X_BOOL EventSystem::UnRegisterEventFunctionHandle(const string& szEventStringID, EVENT_FUNCTION_HANDLE hFunctionHandle, X_UINT uOwnerData)
{
	tGameEventDefine* pEventDefine = m_EventDefineMapByStringID[szEventStringID];
	if(!pEventDefine) 
	{
		return XFALSE;
	}
	pEventDefine->m_FunctionHandleList.remove(std::make_pair(hFunctionHandle, uOwnerData));
	return XTRUE;
 
}

X_VOID EventSystem::PushEvent(GAME_EVENT_ID nEventIntID, const std::vector<string>& vParam)
{
	 
	std::map<GAME_EVENT_ID, tGameEventDefine*>::iterator it = m_EventDefineMapByIntID.find(nEventIntID);
 	if(m_EventDefineMapByIntID.end() == it)
 	{
 		return;
 	}
	tGameEventData gameEventData;
	gameEventData.m_pEventDef	= it->second;
	gameEventData.m_vArg		= vParam;
	if(!gameEventData.m_pEventDef)
		return;
	_PushEvent(gameEventData);
	 
}
X_VOID EventSystem::PushEvent(const string& szEventStringID, const std::vector<string>& vParam)
{
	std::map<string, tGameEventDefine*>	::iterator it = m_EventDefineMapByStringID.find(szEventStringID);
 	if(m_EventDefineMapByStringID.end() == it)
 	{
  		return;
 	}

	tGameEventData gameEventData;
	gameEventData.m_pEventDef	= it->second;
	gameEventData.m_vArg		= vParam;
	if(!gameEventData.m_pEventDef)
		return;
	_PushEvent(gameEventData);

}
X_VOID		EventSystem::PushEventAndProcessNow(const string& szEventStringID, const std::vector<string>& vParam)
{
	 
		tGameEventData gameEventData;
		gameEventData.m_pEventDef	= m_EventDefineMapByStringID[szEventStringID];
		gameEventData.m_vArg		= vParam;
		if(!gameEventData.m_pEventDef)
			return;
		_ProcessEvent(gameEventData);

}
X_VOID EventSystem::PushEventAndProcessNow(GAME_EVENT_ID nEventIntID, const std::vector<string>& vParam)
{
	 
	tGameEventData gameEventData;
	gameEventData.m_pEventDef	= m_EventDefineMapByIntID[nEventIntID];
	gameEventData.m_vArg		= vParam;

	if(!gameEventData.m_pEventDef)
		return;
	_ProcessEvent(gameEventData);
}

/*void EventSystem::OnPushEvent(const string &szEventStringID, const std::vector<string>& vParam)
{
	EventSystem* pEventSystem = EventSystem::GetSingleton();
	if(pEventSystem == X_NULL)
		return ;
	pEventSystem->PushEvent(szEventStringID, vParam);
}

X_VOID EventSystem::OnPushEvent( const X_CHAR* szEventStringID, const std::vector<X_CHAR*>& vParam )
{
	string eventID = szEventStringID;
	vector<string>	vParamVector;
	vParamVector.reserve(vParam.size());
	for(X_INT i = 0; i < static_cast<X_INT>(vParam.size()); ++i)
	{
		vParamVector.push_back(vParam[i]);
	}
	OnPushEvent(eventID, vParamVector);
}
*/
 
X_VOID EventSystem::_PushEvent(const tGameEventData& event)
{
	std::list<tGameEventData>::iterator iter = std::find(m_EventQueue.begin(), m_EventQueue.end(),event);  
	if (iter == m_EventQueue.end())
	{
		m_EventQueue.push_back(event);
	}
}

 
X_VOID EventSystem::_ProcessEvent(const tGameEventData& event)
{
	 
	tGameEventDefine* pEventDef = event.m_pEventDef;
	if(!pEventDef) 
		return;
 
	if(pEventDef->m_FunctionHandleList.empty())
		return;
 
	FUNCTIONHANDLELIST::iterator it;
	for(it=pEventDef->m_FunctionHandleList.begin(); it!=pEventDef->m_FunctionHandleList.end(); ++it)
	{
		if((*it).first)
			((*it).first)(&event, (*it).second);
	}
}
 
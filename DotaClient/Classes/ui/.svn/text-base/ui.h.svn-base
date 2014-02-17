#ifndef __UI_H__
#define __UI_H__
#include "./base/Global.h"

#include "./event/EventDefine.h"
#include <vector>
#include "cocos2d.h"
#include "./ui/SceneManger.h"

#include "./sound/SoundSystem.h"

using namespace std;
class CCNode;
 
class UI 
{
	friend class UISystem;
public:
	UI();
	virtual ~UI();
	 
protected:

	X_INT	m_Id;
	string	m_Name;	
	string	m_LayouFiletName; 
	string  m_OpenSoundName;
	X_BOOL  m_bShow;
	X_INT	m_MutexGroup;			// 互斥组
	bool    bHandleTouchEvent;
public:
	X_VOID				Init();
	X_VOID				Release();

	X_VOID				ReleaseUI();

	const X_INT         GetId()const { return m_Id;}				  
	const string		GetName()const{ return m_Name;}
	const string		GetLayoutName()const{ return m_LayouFiletName;}
	const string        GetOpenSoundName()const{ return m_OpenSoundName;}	
	X_BOOL				IsShow()const { return m_bShow;}
	X_VOID              Show(X_BOOL show);
	cocos2d::CCNode *   GetWindow()const { return m_pUi;}

	SceneManger::SCENE_STATUS		getSceneType()const { return m_InSceneType;}
	 
	const X_INT       GetMutexGroup()const { return m_MutexGroup;}	
	X_VOID            setTipId(X_INT id){m_tipId = id;}
	X_INT             getTipId( ){ return m_tipId;}
	 
	
public:
	X_VOID				RegisterGameEvent();
	X_VOID				RegisterGameEvent(GAME_EVENT_ID eventId,X_BOOL push = XFALSE);
	X_VOID				UnRegisterGameEvent(GAME_EVENT_ID eventId);
	X_VOID				UnRegisterGameEvent();
	
protected:
	virtual    X_VOID   CareEvent() = 0;
	virtual   X_VOID	OnGameEvent(const tGameEventData* pEvent) = 0;
	virtual   X_VOID	OnCreate() = 0;

	virtual   X_VOID	OnShow(){ m_pUi->setUserData(this);UpData();};
	virtual	  X_VOID	UpData(){}
	vector<GAME_EVENT_ID> m_Event;
	cocos2d::CCNode *			m_pUi;
	SceneManger::SCENE_STATUS   m_InSceneType;
	X_INT                m_tipId;
 

	// UI互斥组  
//			组内关系  同组 -1表示多开，可并存，0表示不允许多开。  
//			组间关系  组间根据EM_RULE_UIMUTEX规则  1表示本组界面显示时 ，禁止开始其他组
//												   2表示本组界面开启时 ，关闭其他组
//												   3表示本组界面开启时 ，不影响其他对应组	
enum	EM_RULE_UIMUTEX
	{
		EM_Mutex_Invalid = -1,
		EM_Mutex_Same,      // 属于同一组ui
		EM_Mutex_Forbid,     // 当前组打开时，禁止开启其他对应组
		EM_Mutex_Close,      // 当前组打开时，关闭其他对应组
		EM_Mutex_Keep,      // 当前组打开时，不影响其他对应组
		EM_Mutex_Max,
	};

	enum EM_LAYOUT_LEVEL
	{
		ELL_ZERO = 0,
		ELL_ONE ,
		ELL_TWO ,
		ELL_THREE ,
		ELL_FOUR ,
		ELL_FIVE ,
		ELL_SIX ,
		ELL_SEVEN ,
		ELL_EIGHT ,
		ELL_NINE,	
	};
};

#endif
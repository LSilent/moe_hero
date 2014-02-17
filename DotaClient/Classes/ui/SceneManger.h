#ifndef __SceneManger_h__
#define __SceneManger_h__
#include "./base/Global.h"
#include "./base/Singleton.h"
#include "cocos2d.h"
#include "./Game.h"
#include "./base/UtilTools.h"

enum EM_DEVICE_RESOLUTION_TYPE
{
  EM_DEVICE_RESOLUTION_NORMAL = 0,
  EM_DEVICE_RESOLUTION_640X1136 ,
  EM_DEVICE_RESOLUTION_640X960 ,
  EM_DEVICE_RESOLUTION_768X1024 ,  
  EM_DEVICE_RESOLUTION_1536X2048 , 
};

class  MainTick :public cocos2d::CCObject
{
public:
	virtual void update(float dt )
	{
	}

	void   updateLogic(float dt )
	{
		Game::Tick( X_UINT(dt*1000));
	}
};
//typedef void (CCObject::*SEL_SCHEDULE)(float);

class SceneManger :public Singleton<SceneManger>
{
	DECLARE_SINGLETON(SceneManger)
public:
	enum  SCENE_STATUS
	{
		EM_SS_UNKNOWN = -1,
		EM_SS_LOGIN = 0,
		EM_SS_MAIN ,
		EM_SS_BATTLE ,
		EM_SS_NUM ,
	};
		 

public:
	 SceneManger();
	 virtual~SceneManger();
public:
	X_VOID			Initial(X_UINT width = 640 ,X_UINT height = 960);
	X_VOID			Tick(X_UINT nTime);
	X_VOID			Release();
public:
	SCENE_STATUS     GetSceneStatus(){ return m_status;}
	X_VOID			 EnterScene(SCENE_STATUS ss);
	cocos2d::CCScene* GetCurrentScene();
	cocos2d::CCScene* GetScene(SCENE_STATUS ss);
	cocos2d::CCDirector* GetDirector(){ return pDirector;}

	X_VOID			AddChildToScene(cocos2d::CCNode * child,bool bHandleTouchEvent = true,bool onlyZorder = false);
	X_VOID          FrontChild(cocos2d::CCNode * child ,bool bHandleTouchEvent = true);

	X_VOID			RemoveChildFormScene(cocos2d::CCNode * child,bool cleanup = true);
	X_VOID			EndGame();
    EM_DEVICE_RESOLUTION_TYPE   getResolutionType()const{return m_resolutionType;}
    X_VOID			playGameIntroduce();

	 static bool ScreenShoot();  
		 
	  static string getScreenShoot();
protected:
	cocos2d::CCScene * __getScene(SCENE_STATUS ss);
	X_VOID			__playSceneMusic(); 			
protected:
	cocos2d::CCDirector *pDirector;
	cocos2d::CCScene* SM_SCENE[EM_SS_NUM];

	//static cocos2d::CCScene*  sm_loginScene;
	//static cocos2d::CCScene*  sm_mainScene;
	//static cocos2d::CCScene*  sm_battleScene;
	
	SCENE_STATUS     m_status;
    EM_DEVICE_RESOLUTION_TYPE m_resolutionType;
// cocos2d::CCScene *m_pScene;
	X_INT   m_zorder;

};

#endif
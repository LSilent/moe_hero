#include "./ui/SceneManger.h"
#include "AppMacros.h"
#include "./sound/SoundSystem.h"
#include "./ui/ui.h"
//cocos2d::CCScene*  SceneManger::sm_loginScene = X_NULL;
//cocos2d::CCScene*  SceneManger::sm_mainScene = X_NULL;
//cocos2d::CCScene*  SceneManger::sm_battleScene = X_NULL;
#include "./datapool/DataPool.h"
#include "./load/ResourceCheck.h"

IMPLEMENT_SINGLETON(SceneManger)
SceneManger::SceneManger()
{
	m_status = EM_SS_UNKNOWN;
	pDirector = X_NULL;

	for (X_INT i = 0 ;i< EM_SS_NUM;i++)
	{
		 SM_SCENE[i] = X_NULL;
	}
	//m_pScene =0;
	m_zorder = 0;
}
SceneManger::~SceneManger()
{
	
}

X_VOID		SceneManger::Initial(X_UINT width ,X_UINT height)
{
	 m_zorder = 0;
	 pDirector = cocos2d::CCDirector::sharedDirector();
	 cocos2d::CCEGLView* pEGLView = cocos2d::CCEGLView::sharedOpenGLView();
	 pDirector->setOpenGLView(pEGLView);
    
	 //pEGLView->setFrameSize(width,height);
	 //pEGLView->setDesignResolutionSize(width, height, kResolutionNoBorder);

#ifdef _WINDOWS_
  	  pEGLView->setFrameSize(640,1136);
 	  pEGLView->setFrameZoomFactor(0.7f);


 	   //pEGLView->setFrameSize(768,1024);
  	   //pEGLView->setFrameZoomFactor(0.7f);
	   //pEGLView->setFrameSize(width,height);
	 
	   //pEGLView->setFrameSize(320,480);
	   //pEGLView->setFrameZoomFactor(1.0f);
	   //pEGLView->setFrameSize(width,height);

	  pDirector->setDisplayStats(true);
#else
	  pDirector->setDisplayStats(false);

#endif // _WINDOWS_
 
	  pDirector->setAnimationInterval(1.0 / 60);

	  vector<string> searchPath;
	  searchPath.push_back(ResourceURI);
	  //searchPath.push_back(ResourceUiURI);
	  searchPath.push_back(ResourceConfig);
	  searchPath.push_back(ResourceMusicURI);
	  //searchPath.push_back(ResourceCCBURI);

	  //¡Ÿ ±…Ë÷√
	  searchPath.push_back("phone/Published-iOS");
	  searchPath.push_back("phone/Published-iOS/ccbResources");
      
	//pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
	cocos2d::CCSize frameSize = pEGLView->getFrameSize();

	/* if (frameSize.height > mediumResource.size.height)

	 {
         designResolutionSize = cocos2d::CCSizeMake(1280, 1920);
         pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

		 searchPath.push_back(largeResource.directory);
		 //pDirector->setContentScaleFactor(MIN(largeResource.size.height/designResolutionSize.height, largeResource.size.width/designResolutionSize.width));
	 }
	 else if (frameSize.height > smallResource.size.height)
	 {
         designResolutionSize = cocos2d::CCSizeMake(1280, 1920);
         pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);

		 searchPath.push_back(mediumResource.directory);
		 //pDirector->setContentScaleFactor(MIN(mediumResource.size.height/designResolutionSize.height, mediumResource.size.width/designResolutionSize.width));
	 }
	 else
	 {
		 designResolutionSize = cocos2d::CCSizeMake(640, 960);
         pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
         searchPath.push_back(smallResource.directory);
		 //pDirector->setContentScaleFactor(MIN(smallResource.size.height/designResolutionSize.height, smallResource.size.width/designResolutionSize.width));
	 }*/
    //designResolutionSize = cocos2d::CCSizeMake(640, 960);
   // pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionNoBorder);
    //cocos2d::CCSize _size = cocos2d::CCDirector::sharedDirector()->getWinSizeInPixels();
    
    m_resolutionType = EM_DEVICE_RESOLUTION_NORMAL;
     
    if (frameSize.height == 1136) {
        
        m_resolutionType = EM_DEVICE_RESOLUTION_640X1136;   
        designResolutionSize = cocos2d::CCSizeMake(640, 1136);
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
        
    }
	else if (frameSize.height > mediumResource.size.height)
    {
		m_resolutionType = EM_DEVICE_RESOLUTION_1536X2048;   
        designResolutionSize = cocos2d::CCSizeMake( 768, 1024);
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
    }
    else if (frameSize.height > smallResource.size.height)
    {
		m_resolutionType = EM_DEVICE_RESOLUTION_768X1024;   
        designResolutionSize = cocos2d::CCSizeMake(768,1024);
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
    }
    else
    {
		m_resolutionType = EM_DEVICE_RESOLUTION_640X960;   
        designResolutionSize = cocos2d::CCSizeMake(640, 960);
        pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
        
    }
    
    
   searchPath.push_back(smallResource.directory);
	vector<string>::iterator iter = searchPath.begin();
	searchPath.insert(iter, ResourceCheck::GetSingleton()->getResPath());
	cocos2d::CCFileUtils::sharedFileUtils()->setSearchPaths(searchPath);
 
 
}
X_VOID		SceneManger::Tick(X_UINT nTime)
{

}
X_VOID		SceneManger::Release()
{
	for (X_INT i = 0 ;i< EM_SS_NUM;i++)
	{
		SM_SCENE[i] = X_NULL;
	}
	pDirector = X_NULL;
}
cocos2d::CCScene * SceneManger::__getScene(SCENE_STATUS ss)
{
	if(ss <= EM_SS_UNKNOWN || ss >=EM_SS_NUM) return X_NULL;
	cocos2d::CCScene * pScene = X_NULL;
	pScene = cocos2d::CCScene::create();
	SM_SCENE[ss] = pScene;
	m_zorder = 0;

	return pScene;
}
cocos2d::CCScene* SceneManger::GetCurrentScene()
{ 
	return GetScene(m_status);
}
cocos2d::CCScene* SceneManger::GetScene(SCENE_STATUS ss)
{
	if(ss < EM_SS_LOGIN || m_status >=EM_SS_NUM) return X_NULL;
	return SM_SCENE[ss] ;
}
 
X_VOID	SceneManger::EnterScene(SCENE_STATUS ss)
{
	if(m_status < EM_SS_UNKNOWN || m_status >= EM_SS_NUM) return ;
	//if(m_status == ss) return;
	cocos2d::CCScene * pScene = __getScene(ss);
 
    //m_pScene = cocos2d::CCScene::create();
	//pScene = m_pScene;
	static bool bFirst = true;
	if (bFirst)
	{
		CCTextureCache::sharedTextureCache()->removeAllTextures(); 
		 
		pDirector->runWithScene(pScene);
		bFirst = false;
	}else
	{
		CCTextureCache::sharedTextureCache()->removeAllTextures(); 
		pDirector->replaceScene(pScene);
	}
	
	m_status = ss;
	__playSceneMusic();
}
X_VOID	SceneManger::__playSceneMusic()
{
	switch (m_status)
	{
	case SceneManger::EM_SS_UNKNOWN:
		break;
	case SceneManger::EM_SS_LOGIN:
		{
			//SoundSystem::GetSingleton()->playBackgroundMusic(("login" +SOUND_EXT).c_str());
		}
		break;
	case SceneManger::EM_SS_MAIN:
		{
			SoundSystem::GetSingleton()->playBackgroundMusic(("back" +SOUND_EXT).c_str());
		}
		break;
	case SceneManger::EM_SS_BATTLE:
		{
			SoundSystem::GetSingleton()->playBackgroundMusic(("battle" +SOUND_EXT).c_str());
		}
		break;
	case SceneManger::EM_SS_NUM:
		break;
	default:
		break;
	}
}
X_VOID			SceneManger::playGameIntroduce()
{
	 SoundSystem::GetSingleton()->pauseBackgroundMusic(true);
     SoundSystem::GetSingleton()->playBackgroundMusic(("gamein" + SOUND_EXT).c_str());
    
}
X_VOID          SceneManger::FrontChild(cocos2d::CCNode * child,bool bHandleTouchEvent)
{
	if(!child || !child->getParent())return;
	child->setZOrder(++m_zorder);
	if (bHandleTouchEvent)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->setHandlerUIRoot(child);
	}
}
X_VOID	SceneManger::AddChildToScene(cocos2d::CCNode * child,bool bHandleTouchEvent,bool onlyZorder)
{
	if(!child)
	{
		return;
	}
	cocos2d::CCScene * pScene = GetCurrentScene();
	if (!pScene) return;

	#ifdef UI_SHOW_RECREAT
		pScene->addChild(child);
	#else
		pScene->addChild(child,++m_zorder);
	#endif

	if (bHandleTouchEvent)
	{
		cocos2d::CCDirector::sharedDirector()->getTouchDispatcher()->setHandlerUIRoot(child);
	}
	return;
}
X_VOID	SceneManger::RemoveChildFormScene(cocos2d::CCNode * child,bool cleanup)
{
	if(!child)return;
	if (child->getParent())
	{
		child->removeFromParentAndCleanup(cleanup);
	}
}

X_VOID	SceneManger::EndGame()
{
	pDirector->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
 
bool SceneManger::ScreenShoot()  
{  
	CCSize size = CCDirector::sharedDirector()->getWinSize();    
	CCRenderTexture* pScreen = CCRenderTexture::create(size.width,size.height, kCCTexture2DPixelFormat_RGBA8888);    
	CCScene* pCurScene = CCDirector::sharedDirector()->getRunningScene();
	pScreen->begin();    
	pCurScene->visit();    
	pScreen->end();   
	string str =  "shoot.png";
	X_INT result = pScreen->saveToFile(str.c_str(), kCCImageFormatPNG);
	CCLog( "ScreenShoot %s %d   ",str.c_str(), result );     
	CC_SAFE_DELETE(pScreen);   

	return result == 1;
}
string SceneManger::getScreenShoot()
{
    return CCFileUtils::sharedFileUtils()->getWritablePath()+"shoot.png";

}
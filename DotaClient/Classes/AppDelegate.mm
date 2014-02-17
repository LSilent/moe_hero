#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "./sound/SoundSystem.h"
#include "Game.h"
#include "./game/MainGame.h"
#include "./net/NetworkSystem.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"
#include "./base/nine1.h"
#include "./base/Sdk_Handler.h"

using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
   //SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    //pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    //// turn on display FPS
    //pDirector->setDisplayStats(true);

    //// set FPS. the default value is 1.0/60 if you don't call this
    //pDirector->setAnimationInterval(1.0 / 60);

    //// create a scene. it's an autorelease object
    //CCScene *pScene = loginView::scene();

    //// run
    //pDirector->runWithScene(pScene);

	//CCSize designSize = CCSizeMake(320, 480);
	//CCSize resourceSize = CCSizeMake(320, 480);
	//CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();

	//std::vector<std::string> searchPaths;
	//std::vector<std::string> resDirOrders;

	//TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
	//if (platform == kTargetIphone || platform == kTargetIpad)
	//{
	//	searchPaths.push_back("Published-iOS"); // Resources/Published-iOS
	//	CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);

	//	if (screenSize.height > 768)
	//	{
	//		resourceSize = CCSizeMake(1536, 2048);
	//		resDirOrders.push_back("resources-ipadhd");
	//	}
	//	else if (screenSize.height > 640)
	//	{
	//		resourceSize = CCSizeMake(768, 1536);
	//		resDirOrders.push_back("resources-ipad");
	//	}else if (screenSize.height > 480)
	//	{
	//		resourceSize = CCSizeMake(640, 960);
	//		resDirOrders.push_back("resources-iphonehd");
	//	}
	//	else
	//	{
	//		resDirOrders.push_back("resources-iphone");
	//	}

	//	CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
	//}
	//else if (platform == kTargetAndroid || platform == kTargetWindows)
	//{

	//	if (screenSize.height > 960)
	//	{
	//		resourceSize = CCSizeMake(640, 960);
	//		resDirOrders.push_back("resources-large");
	//	}
	//	else if (screenSize.height > 480)
	//	{
	//		resourceSize = CCSizeMake(480, 720);
	//		resDirOrders.push_back("resources-medium");
	//	}
	//	else
	//	{
	//		resourceSize = CCSizeMake(320, 568);
	//		resDirOrders.push_back("resources-small");
	//	}

	//	CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders);
	//}
    
    
    
	pDirector->setContentScaleFactor(1.0f);
	
	//CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionShowAll);
	 
	Game::Initial();
    #if defined USE_SDK_91
    if( SoundSystem::GetSingleton())
    {
       SoundSystem::GetSingleton()->setBackgroundMusicVolume(0);
    }
    #endif
	Game::StartGame();
    
    

    
  
 
    return true;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
	SoundSystem::GetSingleton()->pauseBackgroundMusic(true);
 
	 SdkHandler::pauseGame();


	if(SettingData::Get(SettingData::BACKGROUND))
		return;
 
	Game::EnterBackground();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SoundSystem::GetSingleton()->pauseBackgroundMusic(false);
    
	if(SettingData::Get(SettingData::BACKGROUND))
		return;
	Game::EnterForeground();
}

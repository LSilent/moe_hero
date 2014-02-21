#include "./ui/logoView.h"
#include "./game/MainGame.h"
#include "./event/EventSystem.h"
using namespace cocos2d;


bool logoView::init()
{
    bool bRet = false;
    do 
    { 
		CC_BREAK_IF(! CCLayer::init());
		/*
		CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCSprite* pSprite = CCSprite::create("logo.jpg");
        CC_BREAK_IF(! pSprite); 
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite, 0);
         pSprite->setScaleX(SCALE_X);
        pSprite->setScaleY(SCALE_Y);
		*/
        bRet = true;
		cocos2d::CCLog("----------------------------------------logoView::init()");
		
    } while (0);

    return bRet;
}
void logoView::startschedule()
{

	getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&logoView::triggerLogin),this ,1,1);


	cocos2d::CCLog("----------------------------------------startschedule");
}
void logoView::triggerLogin(float dt )
{
	if(	LOGIN_CONNECT)
	{
		if (Game::CheckVersion())
		{
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_UPDATAUI_SHOW);
		}
		else 
			MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
		
	}
	else
	{
		( (logoUi*)getUserData())->connectServer();
	}

	this->unscheduleAllSelectors();


}
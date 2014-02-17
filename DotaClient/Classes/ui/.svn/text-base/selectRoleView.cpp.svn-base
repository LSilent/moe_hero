#include "./ui/selectRoleView.h"
#include "./ui/selectRoleUi.h"
 
#include "./CCControlExtension/CCScale9Sprite.h"
#include "./CCEditBox/CCEditBox.h"
#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./base/UtilTools.h"
using namespace cocos2d;
using namespace cocos2d::extension;

bool selectRoleView::init()
{
    bool bRet = false;
    do 
    { 
		 CC_BREAK_IF(! CCLayer::init());

        pCloseItem = CCMenuItemImage::create(
			 "loginenter.png",
			 "loginenterhover.png",
			 this,
			 menu_selector(selectRoleView::menuCloseCallback));
		 CC_BREAK_IF(! pCloseItem);
	
		 CCMenuItemImage *Back = CCMenuItemImage::create(
			 "back.png",
			 "back.png",
			 this,
			 menu_selector(selectRoleView::menuBackCallback));
		 CC_BREAK_IF(! Back);

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite *top_tileback =  CCSprite::create("top_tileback.png");
		top_tileback->setPosition(ccp(size.width/2 , size.height-70));

		this->addChild(top_tileback,1);	
		

		 CCSprite *Title =  CCSprite::create("title.png");
		 Title->setPosition(ccp(size.width/2 , size.height-70));
        
		 this->addChild(Title,2);	

        pCloseItem->setPosition(ccp(size.width/2, 180) );
		Back->setPosition(ccp(size.width/5, size.height-180) );
        
        //CCMenu* pMenu = CCMenu::create(pCloseItem,Back, NULL);
		CCMenu* pMenu = CCMenu::create(pCloseItem,0, NULL);
        pMenu->setPosition(ccp(0, 0) );
        CC_BREAK_IF(! pMenu);		 this->addChild(pMenu, 2);
#ifdef _WINDOWS_
        
        CCLabelTTF* pLabel = CCLabelTTF::create(DataPool::GetSingleton()->getLoginData()->getLoginName().c_str(), FONT_NAME_ARIAL_BOLD, 24);
		CC_BREAK_IF(! pLabel);
		CCSprite *rolename =  CCSprite::create("rolename.png");
        rolename->setPosition(ccp(size.width/2 , size.height/2));
        this->addChild(rolename,1);
		pLabel->setPosition(ccp(size.width / 2, size.height/2));
		this->addChild(pLabel, 1);
		pLabel->setFontName(FONT_NAME_ARIAL_BOLD);
		pLabel->setFontSize(FONT_SIZE_22);
		pLabel->setColor(ccGREEN);
        
       
#else
    
		 CCSize editBoxSize;
		 CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		 CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();
		 editBoxSize.setSize(490,105);
         m_pEditName = CCEditBox::create(editBoxSize, CCScale9Sprite::create("rolename.png"));
		 m_pEditName->setPosition(ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+size.height*0.65));
		 m_pEditName->setFontColor(ccBLACK);
		 m_pEditName->setPlaceHolder(UtilTools::GET_TEXT_FROM_LANG(734));
		 m_pEditName->setPlaceholderFontColor(CCCOLOR_RED);
		 m_pEditName->setPlaceholderFont(FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
		 m_pEditName->setMaxLength(12);
		 m_pEditName->setReturnType(kKeyboardReturnTypeDone);    
        addChild(m_pEditName,3);
#endif
	 
	    CCSprite* pSprite = CCSprite::create("n_background.png");
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        pSprite->setScaleX(SCALE_X);
        pSprite->setScaleY(SCALE_Y);
        this->addChild(pSprite, 0);
        bRet = true;
    } while (0);

    return bRet;
}

void selectRoleView::menuCloseCallback(CCObject* pSender)
{
    if(DataPool::GetSingleton() &&  DataPool::GetSingleton()->IsRoleCreateing())
    {
        return;
    }
#ifndef _WINDOWS_
    string str = m_pEditName->getText();
    
    
	bool fiter = UtilTools::Fiter(str.c_str());
	if (!fiter)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(569));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
    DataPool::GetSingleton()->getLoginData()->setLoginName(str);
#endif
    
  

	((selectRoleUi*)getUserData())->onEnterClick();
    
}
void selectRoleView::menuBackCallback(CCObject* pSender)
{
	//EventSystem::GetSingleton()->PushEvent();
}

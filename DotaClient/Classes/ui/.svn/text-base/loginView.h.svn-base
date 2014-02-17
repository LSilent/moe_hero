#ifndef __LOGINVIEW_SCENE_H__
#define __LOGINVIEW_SCENE_H__

#include "./ui/baseview.h"


namespace cocos2d {
	namespace extension {

		class CCScrollViewEx; 
	}
}


enum SERVER_ZONE_STATE
{
	SRV_ZONE_STATE_STOP = -1,
	SRV_ZONE_STATE_HOT,
	SRV_ZONE_STATE_RMD,

};


class loginView : public BaseView
{
public:
     
    virtual bool init();  
    void menuCloseCallback(CCObject* pSender);
	void menuSelServerCallback(CCObject* pSender);
	void menuComfireCallback(CCObject* pSender);
    CREATE_FUNC(loginView);

	
	void menuSelAccountCallback(CCObject* pSender);

	string getServerState(SERVER_ZONE_STATE state);
	cocos2d::ccColor3B getServerStateColor(SERVER_ZONE_STATE state);
	void loadAllServerZone();
	void   EnableEnter(float dt);
	void   showStartAction();
	void   endStartAction();
	void   updateRecentlySever();
private:
	cocos2d::CCLabelTTF *m_Version;
	cocos2d::CCLabelTTF *m_SelectSrvZone;
	cocos2d::CCLabelTTF *m_userAccount;
	cocos2d::CCSprite *spriteFlag;

	cocos2d::CCNode *m_content;
	cocos2d::extension::CCScrollViewEx *mScrollView;

	cocos2d::CCMenu* pMenu;
	cocos2d::CCMenuItemImage *selAccountItem;
	cocos2d::CCMenuItemImage *selItem;

	cocos2d::extension::CCScrollViewEx *mScrollViewRencentlySever;

	bool isOpenSelect;

	 cocos2d::CCMenuItemImage *pEnter; 
};

#endif
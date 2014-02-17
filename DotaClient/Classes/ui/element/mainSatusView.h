#ifndef __MAIN_STATUS_VIEW_H__
#define __MAIN_STATUS_VIEW_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class MainStatusView
	: public cocos2d::CCLayer
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainStatusView, create);

public:
	MainStatusView();
	virtual ~MainStatusView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	//void onMessage(cocos2d::CCObject * pSender);
	void onChart(cocos2d::CCObject * pSender);
	void onButtonAchieveShow(cocos2d::CCObject * pSender);
	//void onSetting(cocos2d::CCObject * pSender);
	void onButtonUserInfo(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

public:

	virtual bool init();  
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float dt);
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

public:
	cocos2d::CCLabelTTF* mTitle;
	cocos2d::CCLabelBMFont* mProcessText;
	cocos2d::CCLabelBMFont* mProcessExpText;
	cocos2d::CCLabelTTF* mVip;
	cocos2d::CCLabelBMFont* mCoinNum;
	cocos2d::CCLabelBMFont* mGemNum;
	cocos2d::CCLabelBMFont* mWoodNum;

	cocos2d::CCLabelBMFont* mLevel;

	cocos2d::extension::CCScale9Sprite* mProcessBar1;
	cocos2d::extension::CCScale9Sprite* mProcessBar2;


	cocos2d::CCSprite *mAchieveN;
	cocos2d::CCMenuItemImage *mAchieveIcon;
	cocos2d::CCMenuItemImage *mMessageIcon;

	cocos2d::CCLabelBMFont* mtime;
};

class MainStatusViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainStatusViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainStatusView);
};

#endif
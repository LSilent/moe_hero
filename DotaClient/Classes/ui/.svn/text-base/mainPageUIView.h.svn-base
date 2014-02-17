#ifndef __MAIN_SCENE_UI_VIEW_H__
#define __MAIN_SCENE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./base/Global.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/guidelinesLayer.h"



class MainStatusView;
class ObjectHero;
class HeroHeadIcon;


namespace cocos2d {
class LogicTouchItem;
class HeroHeadIcon;
}

class MainPageUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainPageUIView, create);

public:
	MainPageUIView();
	virtual ~MainPageUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
// 	void onButtonChangeHero(cocos2d::CCObject * pSender);
	void onButtonChangeHero(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void onButton1(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButton2(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButton3(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButton4(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButton5(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButton6(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

public:
	void heroItemTouchBeginHook(CCObject* pSender);
	void heroItemTouchMoveHook(CCObject* pSender);
	void heroItemTouchEndHook(CCObject* pSender);

	void heroNullTouchBeginHook(CCObject* pSender);
	void heroNullTouchMoveHook(CCObject* pSender);
	void heroNullTouchEndHook(CCObject* pSender);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	void updateChatMessageInfo();
	void hideMsg(float dt);
	void autoRoll(float dt );

	void onGuideCheeseActivity(CCObject* pSender);
	void onGuideRankList(CCObject* pSender);
	void onGuideHeroBase(CCObject* pSender);
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:
	
	MainStatusView* mMainStatus;

	cocos2d::CCNode *mPosPanel;

	cocos2d::CCSprite* mHeroDock[MAX_MATRIX_CELL_COUNT];
	
	cocos2d::LogicTouchItem* m_heroItems[MAX_MATRIX_CELL_COUNT];
	
	int mHerosDockIndex[MAX_MATRIX_CELL_COUNT];
	ObjectHero* mHeroObjArray[MAX_MATRIX_CELL_COUNT];

	bool mIsDragMove;

	cocos2d::CCSprite *mMsgNotice;
	cocos2d::CCLayer *mAction;
	cocos2d::CCLayer *mTopAction;

	guidelinesLayer *guideLayer;

 	cocos2d::CCLabelTTF *mChatMsgTip;
	cocos2d::CCSprite *mMessage;

 
};

class MainPageUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainPageUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainPageUIView);
};

#endif
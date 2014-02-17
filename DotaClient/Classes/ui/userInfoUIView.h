
#ifndef __USERINFOUIVIEW_H__
#define __USERINFOUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/ModalDialogView.h"

#define MAX_HERO_EQUIPMENT_NUM     6
#define MAX_HERO_SKILL_NUM         2

class ObjectHero;

class userInfoUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(userInfoUIView, create);

public:
	userInfoUIView();
	virtual ~userInfoUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
// 	void onButtonCancel(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonOK(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonPur(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonGift(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonClose(cocos2d::CCObject * pSender);

	void dialogDidClick(int itemIndex, ModalDialogView *pSender);
public:

	virtual bool init();  
// 	static cocos2d::CCScene* scene();

	void buyAction();

	void rankLevelUpdata();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:

	


	cocos2d::CCLabelTTF* mUserName;
	cocos2d::CCLabelTTF* mUserLvl;
	cocos2d::CCLabelTTF* mUserExp;
	cocos2d::CCLabelTTF* mUserHero;
	cocos2d::CCLabelTTF* mUserGem;
	cocos2d::CCLabelTTF* mUserCoin;
	cocos2d::CCLabelTTF* mUserWood;

	cocos2d::CCLabelTTF* mUserRank;
	cocos2d::CCLabelTTF* mUserAct;
	cocos2d::CCLabelTTF* mUserActTime;
	cocos2d::CCLabelTTF* mUserAllActTime;


};

class userInfoUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(userInfoUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(userInfoUIView);
};

#endif
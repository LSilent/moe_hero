#ifndef __FIGHT_RESULT_UI_VIEW_H__
#define __FIGHT_RESULT_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/guidelinesLayer.h"

#define MAX_DROP_ITEM_NUM     5

class FightResultUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(FightResultUIView, create);

public:
	FightResultUIView();
	virtual ~FightResultUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	void  onGuideBattleClose(cocos2d::CCObject * pSender);
	void  onGuideRobBattleClose(cocos2d::CCObject * pSender);
	void onButtonClose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonReplay(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void visibleOkButton();

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:

	cocos2d::CCSprite* mItemPos[MAX_DROP_ITEM_NUM];

	cocos2d::CCLabelTTF* mAwardText;

	cocos2d::CCSprite* mProcessBarFrame;

	cocos2d::CCNode* mContent;

	cocos2d::CCNode *mSuccessNode;
	cocos2d::CCNode *mFailNode;
	cocos2d::CCLabelTTF* mFailAwardText;

	cocos2d::extension::CCControlButton *mFightResultOkButton;

	guidelinesLayer *guideLayer;

};

class FightResultUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(FightResultUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(FightResultUIView);
};

#endif
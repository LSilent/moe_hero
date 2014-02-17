#ifndef __HERO_EVOLVE_UI_VIEW_H__
#define __HERO_EVOLVE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./base/Global.h"

#include "SimpleAudioEngine.h"

class MainStatusView;
class ObjectHero;
class EffectAnimation;

namespace cocos2d {
class LogicTouchItem;
}

class HeroEvolveUIView
	:public  BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroEvolveUIView, create);

public:
	HeroEvolveUIView();
	virtual ~HeroEvolveUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	void onButtonStartEvolve(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonReturn(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonSelectHero(cocos2d::CCObject * pSender);
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:

	const ObjectHero* mCurHero;
	
	MainStatusView* mMainStatus;

	cocos2d::CCMenuItemImage* mHeroPos1;
	cocos2d::CCSprite* mHeroPos2;

	cocos2d::CCSprite* mItemPos;

 
	cocos2d::CCLabelTTF* mItemNum;

	cocos2d::CCLabelBMFont *mMatNum;//²ÄÁÏ
	cocos2d::CCLabelBMFont *mNeedBear;
	cocos2d::CCSprite *mButtonStart;

	cocos2d::CCLabelBMFont *mBear[2];
	cocos2d::extension::CCControlButton *mStartEvolve;

	cocos2d::CCNode *mContent;

	EffectAnimation *effect;
	bool isUpgrading;

	cocos2d::CCSprite* mQualityColor1;
	cocos2d::CCSprite* mQualityColor2;

	//cocos2d::extension::CCScale9Sprite* mProcessBar1;
	//cocos2d::extension::CCScale9Sprite* mProcessBar2;
	//cocos2d::extension::CCScale9Sprite* mProcessBar21;
	//cocos2d::extension::CCScale9Sprite* mProcessBar22;

	cocos2d::CCSprite* mHeroLevelIconBack1;
	cocos2d::CCSprite* mHeroLevelIconBack2;
	

};

class HeroEvolveUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroEvolveUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroEvolveUIView);
};

#endif
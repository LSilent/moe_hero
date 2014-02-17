#ifndef __HERO_RECRUIT_UI_VIEW_H__
#define __HERO_RECRUIT_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"
#include "./ui/element/ModalDialogView.h"

#include "./ui/element/guidelinesLayer.h"

class MainStatusView;
class ObjectHero;

class HeroRecruitUIView
	:public  BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroRecruitUIView, create);

public:
	HeroRecruitUIView();
	virtual ~HeroRecruitUIView();

	virtual void onEnter();
	virtual void onExit();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void dialogDidClick(int itemIndex, ModalDialogView *pSender);

	void sendRecruitHero(int index);
public:
	void onButtonRecruitHero(cocos2d::CCObject * pSender);
	void onButtonStore(cocos2d::CCObject * pSender);
	void onButtonHeroBook(cocos2d::CCObject * pSender);
	void onButtonCharge(cocos2d::CCObject * pSender);
	
	void onButtonRecruit1(cocos2d::CCObject * pSender);
	void onButtonRecruit2(cocos2d::CCObject * pSender);
	void onButtonRecruit3(cocos2d::CCObject * pSender);

	void onButtonFresh(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void visibleHero();
	void changeBackSide();
	void changeFrontSide();

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void updateFreshTime(float time);

private:
	//
	cocos2d::CCSprite* mPos[MAX_HERO_RECRUIT_COUNT];

	cocos2d::CCMenuItemImage *mRecruitButton[MAX_HERO_RECRUIT_COUNT];
	
	cocos2d::CCSprite *mRecruitText[MAX_HERO_RECRUIT_COUNT];
	
private:
	
	MainStatusView* mMainStatus;
		
	cocos2d::CCSprite* mHeroSpriteList[MAX_HERO_RECRUIT_COUNT];

	ObjectHero *mHeroList[MAX_HERO_RECRUIT_COUNT];

	cocos2d::CCLabelTTF* mFreshInfo;

	unsigned int mFreshmilliSecond;

	cocos2d::CCMenuItemImage *mRecruitTab[3];
	cocos2d::CCSprite *mRecruitFreshText;

	cocos2d::CCLabelBMFont *mName[3];
	cocos2d::CCSprite *mRecruitTip;
	cocos2d::CCSprite *mNewFresh;
	guidelinesLayer *guideLayer;

	bool flagOfRecruiting;
	bool flagOfReEffect;
};

class HeroRecruitUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroRecruitUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroRecruitUIView);
};

#endif
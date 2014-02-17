#ifndef __SKILL_INSPECT_UI_VIEW_H__
#define __SKILL_INSPECT_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/ModalDialogView.h"

#include "./ui/element/guidelinesLayer.h"

class EffectAnimation;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class Item;

class SkillInspectUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	,ModalDialogDelegate

{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SkillInspectUIView, create);

public:
	SkillInspectUIView();
	virtual ~SkillInspectUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );

public:
	void onButtonUpgrade( cocos2d::CCObject * pSender);
	void onButtonReturn( cocos2d::CCObject * pSender );

	void onSkillButtonSelected( cocos2d::CCObject * pSender);

	bool judeSkillUpgrade();

	void skillUpgradeStatus(bool flag);
private:
	
	cocos2d::extension::CCScrollViewEx* mContent;

	cocos2d::CCNode* mContentNode;

	cocos2d::CCLabelBMFont* mSkillName;
	cocos2d::CCLabelTTF* mSkillThisLevel;
	cocos2d::CCLabelTTF* mSkillNextLevel;

	cocos2d::CCSprite* mSkillPos;

	std::vector<Item*> itemlistSelect;
	std::vector<int> itemlistStatus;

	cocos2d::CCMenuItemImage *mSkillButton[5];
	cocos2d::CCLabelBMFont *mSkillLvl;

	cocos2d::CCLabelBMFont *mSkillRate;

	cocos2d::CCLabelTTF *mSkillCD;
	cocos2d::CCLabelTTF *mSkillMP;

	cocos2d::CCMenuItemImage *mSkillButtonUp;
	cocos2d::CCSprite *mSkilltip;


	guidelinesLayer *guideLayer;

	EffectAnimation *effect;
};

class SkillInspectUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SkillInspectUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SkillInspectUIView);
};

#endif
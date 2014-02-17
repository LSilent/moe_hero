#ifndef __SkillUpgradeEquiUIView_H__
#define __SkillUpgradeEquiUIView_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/guidelinesLayer.h"

#include "./ui/element/ModalDialogView.h"


class MainStatusView;
class ObjectHero;
class ItemCommon;

namespace cocos2d {
	namespace extension {

		class CCScrollViewEx; 
	}
}

class SkillUpgradeEquiUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SkillUpgradeEquiUIView, create);

public:
	SkillUpgradeEquiUIView();
	virtual ~SkillUpgradeEquiUIView();

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

	void GetEquip(int type,int id,    SkillUpgradeEquiUIView *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );
	void itemChooseCallBack( cocos2d::CCObject* pSender );
	
	void getSkillItemCallBack( cocos2d::CCObject* pSender );
public:
	void onButtonOK(cocos2d::CCObject * pSender);
	void onButtonCancel(cocos2d::CCObject * pSender);

private:

	cocos2d::extension::CCScrollViewEx* mContent;

// 	cocos2d::CCLabelTTF* mLoadPointLeft;
	int mLoadPointLeftNum;

// 	std::vector< cocos2d::CCLabelTTF* > mLoadDistributeViewArray;
// 	std::vector< int > mLoadDistributeArray;

// 	std::vector< int > mCurLoadPoint;
// 	std::vector< int > mMaxLoadPoint;

// 	std::vector< cocos2d::CCLabelTTF* > mLoadViewArray;

// 	std::vector< ObjectHero* > mHeroArray;

	std::vector<cocos2d::CCSprite *> mCheckItems;
    std::vector<ItemCommon *> mSkillEquiItems;


	guidelinesLayer *guideLayer;
};

class SkillUpgradeEquiUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SkillUpgradeEquiUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SkillUpgradeEquiUIView);
};

#endif
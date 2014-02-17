#ifndef __BAG_OWN_UI_VIEW_H__
#define __BAG_OWN_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/ModalDialogView.h"
#include "./object/Item.h"

class MainStatusView;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class BagOwnUIView
	:public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(BagOwnUIView, create);

public:
	BagOwnUIView();
	virtual ~BagOwnUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	void useCallBack(cocos2d::CCObject* pSender);

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );
	void onTipResult();
public:
	void onButtonExperienceCard(cocos2d::CCObject * pSender);
	void onButtonSkillCard(cocos2d::CCObject * pSender);
	void onButtonTools(cocos2d::CCObject * pSender);
	
private:
	
	MainStatusView* mMainStatus;
 
	CommonItemType mItemCategory;

	cocos2d::extension::CCScrollViewEx* mContent;

	cocos2d::CCMenuItemImage *mItemImage[3];

	X_VOID __onSelectMessage(int type);
public:
	static bool itemCanUse(const Item *pItem1,const Item *pItem2);
};

class BagOwnUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BagOwnUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BagOwnUIView);
};

#endif
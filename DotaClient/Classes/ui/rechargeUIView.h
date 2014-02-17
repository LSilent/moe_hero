#ifndef __RECHARGEUIVIEW_H__
#define __RECHARGEUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/ModalDialogView.h"

class MainStatusView;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class rechargeUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(rechargeUIView, create);

public:
	rechargeUIView();
	virtual ~rechargeUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void dialogDidClick(int itemIndex, ModalDialogView *pSender);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );
	void buyCallBack( cocos2d::CCObject* pSender );
	void exChangeCallBack( cocos2d::CCObject* pSender );
	
public:
	void onButtonRecruitHero(cocos2d::CCObject * pSender);
	void onButtonStore(cocos2d::CCObject * pSender);
	void onButtonHeroBook(cocos2d::CCObject * pSender);
	void onButtonCharge(cocos2d::CCObject * pSender);
	
private:
	
	MainStatusView* mMainStatus;

	cocos2d::extension::CCScrollViewEx* mContent;

	enum  EM_BUY_EXCHAGE
	{
		EM_BUY,
		EM_EXCHANGE,

	};
	EM_BUY_EXCHAGE m_BuyStates;
};

class rechargeUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(rechargeUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(rechargeUIView);
};

#endif
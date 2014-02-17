#ifndef __LOAD_DISTRIBUTE_UI_VIEW_H__
#define __LOAD_DISTRIBUTE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class MainStatusView;
class ObjectHero;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class LoadDistributeUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LoadDistributeUIView, create);

public:
	LoadDistributeUIView();
	virtual ~LoadDistributeUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );

	void addCallBack( cocos2d::CCObject* pSender );
	void subCallBack( cocos2d::CCObject* pSender );

public:
	void onButtonOK(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonCancel(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	
	void checkEnablePoint(bool flag);
	void updataEnablePoint();

	static bool sortDistribute(const ObjectHero *pHero1,const ObjectHero *pHero2);

private:
	
	cocos2d::extension::CCScrollViewEx* mContent;

	cocos2d::CCLabelBMFont* mLoadPointLeft;
	int mLoadPointLeftNum;

	std::vector< cocos2d::CCLabelBMFont* > mLoadDistributeViewArray;
	std::vector< int > mLoadDistributeArray;

	std::vector< int > mCurLoadPoint;
	std::vector< int > mMaxLoadPoint;

	std::vector< cocos2d::CCLabelBMFont* > mLoadViewArray;

	std::vector< ObjectHero* > mHeroArray;

	std::vector<cocos2d::CCMenuItemImage *> mAddLabels;
	std::vector<cocos2d::CCMenuItemImage *> mSubLabels;
	std::vector<cocos2d::CCMenuItemImage *> mdisableItems;
	std::vector<cocos2d::CCMenuItemImage *> mSubdisableItems;
};

class LoadDistributeUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LoadDistributeUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LoadDistributeUIView);
};

#endif
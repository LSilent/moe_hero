#ifndef __RANKLIST_UI_VIEW_H__
#define __RANKLIST_UI_VIEW_H__

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

class RankListUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(RankListUIView, create);

public:
	RankListUIView();
	virtual ~RankListUIView();

	virtual void onEnter();
	virtual void onExit();

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

	void itemCallBack( cocos2d::CCObject* pSender );

	void updateTime(float time);
	void createMySelf(cocos2d::CCPoint itemDockPos, cocos2d::CCMenu *menu, cocos2d::CCLayer *layer);
	void  detailCallBack( cocos2d::CCObject* pSender );
private:
	
	cocos2d::CCLabelBMFont* mTiTle;
	cocos2d::CCLabelBMFont* mInfo;

	cocos2d::extension::CCScrollViewEx* mContent;

	unsigned int mFreshmilliSecond;

	cocos2d::CCLabelTTF* mTimeFresh;
};

class RankListUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(RankListUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(RankListUIView);
};

#endif
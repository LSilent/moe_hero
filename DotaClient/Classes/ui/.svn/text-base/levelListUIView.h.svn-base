#ifndef __LEVEL_LIST_UI_VIEW_H__
#define __LEVEL_LIST_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/ModalDialogView.h"
#include "./ui/element/guidelinesLayer.h"

class MainStatusView;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class CopySceneGroup;
class CopyScene;

class LevelListUIView
	:public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LevelListUIView, create);

public:
	LevelListUIView();
	virtual ~LevelListUIView();

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

	void titleCallBack( cocos2d::CCObject* pSender );
	void listCallBack( cocos2d::CCObject* pSender );
	void rushCallBack( cocos2d::CCObject* pSender );

private:
	
	MainStatusView* mMainStatus;

	cocos2d::extension::CCScrollViewEx* mContent_title;
	cocos2d::extension::CCScrollViewEx* mContent_list;

	cocos2d::CCNode* mContentNode;

	const CopySceneGroup* mCurGroupScene;
	const CopyScene*  mCurCopyScene;

	cocos2d::CCPoint offset_;
	cocos2d::CCPoint sceneOffset_;
	bool startFlag;


	guidelinesLayer *guideLayer;

};

class LevelListUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LevelListUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LevelListUIView);
};

#endif
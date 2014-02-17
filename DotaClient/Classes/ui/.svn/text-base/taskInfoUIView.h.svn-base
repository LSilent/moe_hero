#ifndef __TASKINFOUIVIEW_H__
#define __TASKINFOUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/ModalDialogView.h"
//#include "./ui/element/guidelinesLayer.h"

class MainStatusView;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class taskInfoUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(taskInfoUIView, create);

public:
	taskInfoUIView();
	virtual ~taskInfoUIView();

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
	void GetEquip(int type,int id,   taskInfoUIView  *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

public:


	void itemInfoCallBack( cocos2d::CCObject* pSender );
	
private:
	
	MainStatusView* mMainStatus;

	cocos2d::extension::CCScrollViewEx* mContent;

	//guidelinesLayer *guideLayer;
	//cocos2d::CCMenuItemImage *guideMenuItem;

};

class taskInfoUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(taskInfoUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(taskInfoUIView);
};


#endif
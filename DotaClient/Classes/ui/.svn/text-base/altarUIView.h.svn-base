#ifndef __ALTAR_UI_VIEW_H__
#define __ALTAR_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class AltarUIView
	:public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(AltarUIView, create);

public:
	AltarUIView();
	virtual ~AltarUIView();

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

	void itemCallBack( cocos2d::CCObject* pSender );

	void onAltar1(cocos2d::CCObject * pSender);
	void onAltar2(cocos2d::CCObject * pSender);
	void onAltar3(cocos2d::CCObject * pSender);
	void onAltar4(cocos2d::CCObject * pSender);
	void onAltar5(cocos2d::CCObject * pSender);

	void onClose(cocos2d::CCObject * pSender);

private:
	
	int mAltarIndex;

	cocos2d::CCLabelTTF* mTiTle;
	cocos2d::CCLabelTTF* mInfo;

	cocos2d::CCSprite* mAltarTitle;

	cocos2d::extension::CCScale9Sprite *m_process;

	cocos2d::CCSprite* mProcessGlow;

	cocos2d::CCLabelTTF* mDropText;

	cocos2d::CCSprite* mAltar;
};

class AltarUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(AltarUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(AltarUIView);
};

#endif
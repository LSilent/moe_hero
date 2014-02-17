#ifndef __SETTING_UI_VIEW_H__
#define __SETTING_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
 

#include "SimpleAudioEngine.h"

class MainStatusView;

using namespace cocos2d;
using namespace cocos2d::extension;


namespace cocos2d {
	namespace extension {
		class CCScrollViewEx;
	}
}
class SettingUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SettingUIView, create);

public:
	SettingUIView();
	virtual ~SettingUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();
	void   valueChanged( CCObject *sender, CCControlEvent controlEvent );
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemCallBack( cocos2d::CCObject* pSender );

	void onButtonSettingMusic( cocos2d::CCObject* pSender );
	void onButtonSettingAudio( cocos2d::CCObject* pSender );
	void onButtonSettingPPCenter( cocos2d::CCObject* pSender );
	void onButtonSettingAppReConn( cocos2d::CCObject* pSender );
private:
	
	MainStatusView* mMainStatus;

	//cocos2d::CCLabelTTF* mSettingName;
	//cocos2d::CCLabelTTF* mSettingLvl;
	//cocos2d::CCLabelTTF* mSettingGold;

	
	cocos2d::CCSprite *mSettingMusic;
	cocos2d::CCSprite *mSettingAudio;

	cocos2d::CCSprite *mSettingReconn;


	cocos2d::extension::CCScrollViewEx* mContent;
    
    cocos2d::CCSprite *mSettingPP;
    cocos2d::CCLabelTTF *mPPText;
    cocos2d::CCMenuItemImage *mSettingPPBtn;

	

};

class SettingUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SettingUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SettingUIView);
};

#endif
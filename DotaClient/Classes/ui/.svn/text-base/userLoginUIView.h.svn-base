
#ifndef __USERLOGINUIVIEW_H__
#define __USERLOGINUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/ModalDialogView.h"

#define MAX_HERO_EQUIPMENT_NUM     6
#define MAX_HERO_SKILL_NUM         2

class ObjectHero;

class userLoginUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, cocos2d::extension::CCEditBoxDelegate
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(userLoginUIView, create);

public:
	userLoginUIView();
	virtual ~userLoginUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	void onButtonReturn(cocos2d::CCObject * pSender);
	void onButtonLogin(cocos2d::CCObject * pSender);
	void onButtonRememberPwd(cocos2d::CCObject * pSender);
	void onButtonAutoLogin(cocos2d::CCObject * pSender);

	void onButtonRegister(cocos2d::CCObject * pSender);
	void onButtonReg(cocos2d::CCObject * pSender);

	void loadLoginNode();
	void loadRegisterNode();

	bool checkValite();
	void dialogDidClick(int itemIndex, ModalDialogView *pSender);
public:

	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);

	virtual bool init();  

	void registerResult(bool flag);


	void  EnableEnter(float dt);
	void  EnableRegister(float dt);
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:
	cocos2d::CCSprite *mCheckPwd;
//	cocos2d::CCSprite *mCheckLogin;

	cocos2d::CCSprite *mBackNode;
	cocos2d::CCNode *mLoginNode;
	cocos2d::CCNode *mRegisterNode;

	cocos2d::extension::CCEditBox *pRegEmail;
	cocos2d::extension::CCEditBox *pRegPwd1;
	cocos2d::extension::CCEditBox *pRegPwd2;

	cocos2d::extension::CCEditBox *pLoginEmail;
	cocos2d::extension::CCEditBox *pLoginPwd;

	cocos2d::CCMenuItem * m_pRegister;
	cocos2d::CCMenuItem * m_pEnter;

	bool isRegFromLogin;
};

class userLoginUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(userLoginUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(userLoginUIView);
};

#endif
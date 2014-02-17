#ifndef __WOODSHIZHE_UI_VIEW_H__
#define __WOODSHIZHE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./ui/element/ModalDialogView.h"
#include "SimpleAudioEngine.h"

#include "./base/Global.h"
class  ObjectHero;
 
namespace cocos2d {
	class LogicTouchItem;
	class HeroHeadIcon;
}

class WoodShiZheUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(WoodShiZheUIView, create);

public:
	WoodShiZheUIView();
	virtual ~WoodShiZheUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

 
public:
	
	void	onShiZheCancel(cocos2d::CCObject * pSender);
	void	onButtonGetJQR(cocos2d::CCObject * pSender);
	void	onButtonReFresh(cocos2d::CCObject * pSender);
	void	onButtonStartYaYun(cocos2d::CCObject * pSender);
	void	onButtonClose(cocos2d::CCObject * pSender);


	X_VOID	freshShizhe(bool btop =false);
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onExit();
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );


	X_VOID  showShiZheView(int id ,bool b);

	X_VOID  freshShiZhe(X_INT id);
	void dialogDidClick(int itemIndex, ModalDialogView *pSender);
	void MenuItemCallback(cocos2d::CCObject *pSender);
private:

	cocos2d::CCLabelTTF* mHuSongTip1;

	cocos2d::CCNode* mNodePos;
	cocos2d::CCLabelTTF* mWoodAward;
	cocos2d::CCLabelTTF* mExpward;
	cocos2d::CCLabelTTF* mHuSongTime;
 
	cocos2d::CCMenuItem* mButtoReFresh;
	cocos2d::CCMenuItem* mButtonGetJQR;
	cocos2d::CCMenuItem* mButtonStartYaYun;
  
	 cocos2d::CCNode* mNodeshiZheXinxi;
	 cocos2d::CCSprite* mShiZheColor;
	 cocos2d::CCSprite* mShiZheSprite;
	 cocos2d::CCLabelTTF* mShiZheName;
	 cocos2d::CCLabelTTF* mShiZheLevel;
	 cocos2d::CCLabelTTF* mShiZheTime;
	 cocos2d::CCLabelTTF* mShiZheJiangLi;
	 cocos2d::CCMenuItem* mShiZheCancel;
  
	 TouchButtonEx* mShiZheTouchSprites[5];
	 cocos2d::CCSprite* mShiZheSprites[5];
	 cocos2d::CCNode *mContent;
	void sel_Sprite(CCObject* pObject);
};

class WoodShiZheUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(WoodShiZheUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(WoodShiZheUIView);
};

#endif
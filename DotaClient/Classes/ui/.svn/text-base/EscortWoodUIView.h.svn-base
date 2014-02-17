#ifndef __ESCORT_WOODUI_VIEW_H__
#define __ESCORT_WOODUI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "./ui/element/ModalDialogView.h"
#include "./base/Global.h"
class  ObjectHero;
namespace cocos2d {
	class LogicTouchItem;
	class HeroHeadIcon;
	class TouchButtonEx;
}

class EscortWoodUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EscortWoodUIView, create);

public:
	EscortWoodUIView();
	virtual ~EscortWoodUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void	heroNullTouchBeginHook(CCObject* pSender);
	void	heroNullTouchMoveHook(CCObject* pSender);
	void	heroNullTouchEndHook(CCObject* pSender);

	void	heroItemTouchBeginHook(CCObject* pSender);
	void	heroItemTouchMoveHook(CCObject* pSender);
	void	heroItemTouchEndHook(CCObject* pSender);
public:
	
	void	onButtonBuzhen(cocos2d::CCObject * pSender);
	void	onButtonSpeedUp(cocos2d::CCObject * pSender);
	void	onButtonYaYun(cocos2d::CCObject * pSender);
	void	onButtonHideSprite(cocos2d::CCObject * pSender);
	void	onButtonFighter(cocos2d::CCObject * pSender);
	void	onShiZheLJBtn(cocos2d::CCObject * pSender);
	void	onShiZheLJCancel(cocos2d::CCObject * pSender);

	void	onButtonClose(cocos2d::CCObject * pSender);
	void    updateHuSongTime( float time );

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void onEnter();
	virtual void onExit();
	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );


	X_VOID  showBuZhenView(bool b);
	X_VOID  showShiZheView(bool b,X_CLIENT_GUID guid);
private:

	cocos2d::CCLabelTTF* mLJNum;
	cocos2d::CCLabelTTF* mHSTime;
	cocos2d::CCNode* mNodePos;
	cocos2d::CCMenuItem* mButtonSpeedUp;
	cocos2d::CCMenuItem* mButtonBuzhen;
	cocos2d::CCMenuItem* mButtonYaYun;
	cocos2d::CCMenuItem* mButtonHideSprite;
	cocos2d::CCNode* mSelfTipNode;
	
	cocos2d::CCNode* mNodeBuZhen;
	cocos2d::CCMenuItem* mButtonFighter;

	 cocos2d::CCNode* mNodeshiZheXinxi;
	 cocos2d::CCSprite* mShiZheSprite;
	 cocos2d::CCSprite* mShiZheColor;
	 
	 cocos2d::CCLabelTTF* mShiZheName;
	 cocos2d::CCLabelTTF* mShiZheLevel;
	 cocos2d::CCLabelTTF* mShiZheZhuRen;
	 cocos2d::CCLabelTTF* mShiZheTime;
	 cocos2d::CCLabelTTF* mShiZheJiangLi;
	 cocos2d::CCLabelTTF* mShiZheLJNum;
	 cocos2d::CCLabelTTF* mShiZheLJGet;
	 cocos2d::CCMenuItem* mShiZheLJBtn;
	 cocos2d::CCMenuItem* mShiZheLJCancel;

	cocos2d::CCNode *mContent;
	cocos2d::CCSprite* mHeroDock[MAX_MATRIX_CELL_COUNT];

	cocos2d::LogicTouchItem* m_heroItems[MAX_MATRIX_CELL_COUNT];
	int mHerosDockIndex[MAX_MATRIX_CELL_COUNT];
	ObjectHero* mHeroObjArray[MAX_MATRIX_CELL_COUNT];
	bool mIsDragMove;

	void  sel_Sprite(CCObject* pObject);
	cocos2d::CCNode *mSpriteContent;
	vector<cocos2d::TouchButtonEx* > m_Sprites;
 


	bool      m_visbleXJL;
};

class EscortWoodUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EscortWoodUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EscortWoodUIView);
};

#endif
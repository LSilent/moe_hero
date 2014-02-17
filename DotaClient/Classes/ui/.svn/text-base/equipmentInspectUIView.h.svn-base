#ifndef __EQUIPMENT_INSPECT_UI_VIEW_H__
#define __EQUIPMENT_INSPECT_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/CCScrollViewEx.h"
#include "./ui/element/ModalDialogView.h"

#define MAX_EQUIP_TEXT_SIZE  (9)

class Item;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 

}
}

class EquipmentInspectUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipmentInspectUIView, create);

public:
	EquipmentInspectUIView();
	virtual ~EquipmentInspectUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);

	void GetEquip(int type,int id,    EquipmentInspectUIView *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

public:
	void onButtonCompose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonGetEquip(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void onButtonClose( cocos2d::CCObject* pSender );

	void heroInfoCallBack( cocos2d::CCObject* pSender );
	void eQuipInfoCallBack( cocos2d::CCObject* pSender );
private:
	
	int iHeroNumPage;
	int iHeroNumTotal;

// 	cocos2d::extension::CCScrollViewEx* mContent;
	cocos2d::extension::CCScrollViewPage *mContent;
	cocos2d::extension::CCPageControll *mPageCtrl;

	cocos2d::CCNode* mContentNode;

	cocos2d::CCLabelTTF* mEquipmentName;
	cocos2d::CCLabelTTF* mEquipmentDesc;
// 	cocos2d::CCLabelTTF* mEquipmentParam;

	/*
	cocos2d::CCLabelTTF* mEquipAtta;
	cocos2d::CCLabelTTF* mEquipDef;
	cocos2d::CCLabelTTF* mEquipMP;

	cocos2d::CCLabelTTF* mEquipAgi;
	cocos2d::CCLabelTTF* mEquipInt;
	cocos2d::CCLabelTTF* mEquipHP;

	cocos2d::CCLabelTTF* mEquipStr;
	cocos2d::CCLabelTTF* mEquipGuard;
	cocos2d::CCLabelTTF* mEquipVal;
	*/

	cocos2d::CCLabelTTF *mEquipAttr[MAX_EQUIP_TEXT_SIZE];

	cocos2d::CCSprite* mEquipmentPos;

	cocos2d::CCSprite* mPartPos1;
	cocos2d::CCSprite* mPartPos2;
	cocos2d::CCSprite* mPartPos3;
	cocos2d::CCSprite* mPartPos4;
	cocos2d::CCSprite* mPartPos5;

	cocos2d::CCNode *mGetEquipNode;

	vector<Item *> materialsEq;

};

class EquipmentInspectUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipmentInspectUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipmentInspectUIView);
};

#endif
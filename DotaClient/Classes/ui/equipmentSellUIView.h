#ifndef __EQUIPMENTSELLUIVIEW_H__
#define __EQUIPMENTSELLUIVIEW_H__

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

class equipmentSellUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(equipmentSellUIView, create);

public:
	equipmentSellUIView();
	virtual ~equipmentSellUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);


public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	void onButtonEquip0(cocos2d::CCObject * pSender);

	void onButtonEquip1(cocos2d::CCObject * pSender);

	void onButtonEquip2(cocos2d::CCObject * pSender);

	void onButtonEquipSell(cocos2d::CCObject * pSender);

	void  addCallBack( cocos2d::CCObject* pSender );
	 
	void  subCallBack( cocos2d::CCObject* pSender );
	 
 
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );
	void sellCallBack( cocos2d::CCObject* pSender );
	void itemInfoCallBack( cocos2d::CCObject* pSender );

	

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);


	static bool sortSellEquip(Item *pItem1,Item *pItem2);

private:
	MainStatusView* mMainStatus;
	cocos2d::extension::CCScrollViewEx* mContent;

	vector<const Item *> mSellEquipItems;

	vector<Item*> mAllItemlist;
	vector<X_INT> mAllItemNum;

	map <X_INT, vector<Item*> > mAllTrueItemlist;


	std::vector<cocos2d::CCMenuItemImage *> mAdddisableItems;
	std::vector<cocos2d::CCMenuItemImage *> mSubdisableItems;
	std::vector<cocos2d::CCLabelBMFont *> mLables;
	std::vector< cocos2d::CCLabelTTF* > mSelectNumLables;
};

class equipmentSellUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(equipmentSellUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(equipmentSellUIView);
};

#endif
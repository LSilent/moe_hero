#ifndef __HEROEQUIPUIVIEW_H__
#define __HEROEQUIPUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./ui/element/CCScrollViewEx.h"
#include "SimpleAudioEngine.h"


#include "./ui/element/ModalDialogView.h"


#include "./ui/element/guidelinesLayer.h"

class MainStatusView;
class ObjectHero;
class Item;
class ItemEquip;

namespace cocos2d {
	namespace extension {

		class CCScrollViewEx; 
	}
}

class HeroEquipUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
	, public ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroEquipUIView, create);

public:
	HeroEquipUIView();
	virtual ~HeroEquipUIView();

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

	void itemInfoCallBack( cocos2d::CCObject* pSender );
	void changeCheck(cocos2d::CCObject* pSender);
	void dialogDidClick(int itemIndex, ModalDialogView *pSender);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemChooseCallBack( cocos2d::CCObject* pSender );
	void mButtonRmdEquip( cocos2d::CCObject* pSender );

	void checkEquipStatus();
	bool isChecked(Item *pItem);
	bool isUniqued(Item *pitem);
	void updateEquipInfo();
	void loadRecommendEquip();

public:
	void onButtonOK(cocos2d::CCObject * pSender);
	void onButtonCancel(cocos2d::CCObject * pSender);

	void onButtonChange(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
private:

/*	cocos2d::extension::CCScrollViewEx* mContent;*/

	cocos2d::extension::CCScrollViewPage* mContent;
	cocos2d::extension::CCPageControll *mPageCtrl;

	int mLoadPointLeftNum;
	
	cocos2d::CCLabelBMFont *mHeroName;
	cocos2d::CCLabelBMFont *mEquiNum;
	cocos2d::CCLabelBMFont *mEquiBear;

	vector<cocos2d::CCMenuItemImage *> mEquipItems;
	vector<const Item *> mSelectEqui;
	int mCurHeroTotal;
	int usedNum;
	int surplusBear;

	cocos2d::CCNode *mSelEquipNode;
	cocos2d::CCNode *mRecmdEquipNode;

	cocos2d::CCSprite *mChangeText;
	cocos2d::CCMenuItemImage *mRecmt[20];

	vector<Item*> itemRecmdEquips;
	bool recmdFlag;

	guidelinesLayer *guideLayer;

};

class HeroEquipUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroEquipUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroEquipUIView);
};

#endif
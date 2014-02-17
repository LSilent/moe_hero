#ifndef __HERO_UPGRADE_UI_VIEW_H__
#define __HERO_UPGRADE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/CCScrollViewEx.h"
// #include "./ui/element/ProgressView.h"
#include "./ui/element/ModalDialogView.h"

#include "./ui/element/guidelinesLayer.h"

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class MainStatusView;
class ObjectHero;
class Item;
class ProgressView;
class EffectAnimation; 



class HeroUpgradeUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroUpgradeUIView, create);

public:
	HeroUpgradeUIView();
	virtual ~HeroUpgradeUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	void heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr,float scale);


	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );

	void getTotalExp(int totalExp,int &tLvl,int &tExp);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );

public:
	void onButtonConfirm(cocos2d::CCObject * pSender);
	void onButtonCancel(cocos2d::CCObject * pSender);

private:
	
	MainStatusView* mMainStatus;

// 	cocos2d::extension::CCScrollViewEx* mContent;
	cocos2d::extension::CCScrollViewPage *mContent;
	cocos2d::extension::CCPageControll *mPageCtrl;

	cocos2d::CCNode* mContentNode;

	cocos2d::CCLabelBMFont* mHeroInfo;
	cocos2d::CCLabelBMFont* mAttackNum;
	cocos2d::CCLabelBMFont* mArmorNum;
	cocos2d::CCLabelBMFont* mSpeedNum;
	cocos2d::CCLabelBMFont* mLoadNum;
	cocos2d::CCLabelBMFont* mBloodNum;
	cocos2d::CCLabelBMFont* mMagicNum;

	cocos2d::CCLabelBMFont* _mHeroAttcAdd[5];

	cocos2d::CCSprite* mHeroIconPos;

	cocos2d::CCSprite *mProgressPos;

	ObjectHero * mCurHero;

	std::vector<Item*> itemlistSelect;
	std::vector<int> itemlistStatus;

	vector<Item*> itemlist;
	int itemListSize;

	ProgressView *mExpProgress;

	int mSelectTotalExp;
// 	int mPreExp;
	int mPreLvl;
	int uLvl ;
	int uExp ;
 
	guidelinesLayer *guideLayer;

	EffectAnimation *effect;

	bool isUpgrading;
	static bool _SortItemExperience(Item *pItem1,Item *pItem2);
};

class HeroUpgradeUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroUpgradeUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroUpgradeUIView);
};

#endif
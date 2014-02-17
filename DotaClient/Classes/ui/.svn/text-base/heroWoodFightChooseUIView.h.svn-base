#ifndef __HERO_WOOD_FIGHT_CHOOSE_UI_VIEW_H__
#define __HERO_WOOD_FIGHT_CHOOSE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./ui/element/CCScrollViewEx.h"
#include "./ui/element/guidelinesLayer.h"


class MainStatusView;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}
#define WOOD_HERO_SHOW_IN_CHOOSE 0
class HeroWoodFightChooseUIView
	:public  BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroWoodFightChooseUIView, create);

public:
	HeroWoodFightChooseUIView();
	virtual ~HeroWoodFightChooseUIView();

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

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void heroItemCallBack( cocos2d::CCObject* pSender );
	void guideHeroItemCallBack( cocos2d::CCObject* pSender );
public:
	void onButtonOK(cocos2d::CCObject * pSender);
	void onButtonCancel(cocos2d::CCObject * pSender);
	
private:
	
// 	cocos2d::extension::CCScrollViewEx* mContent;
	cocos2d::extension::CCScrollViewPage *mContent;
	cocos2d::extension::CCPageControll *mPageCtrl;

	std::vector< cocos2d::CCMenuItemImage * > mHeroItemArray;
	std::vector< cocos2d::CCSprite * > mHeroItemCheckArray;

	cocos2d::CCMenuItemImage* mButtonOK;
	cocos2d::CCSprite* mButtonOKText;

	cocos2d::CCLabelBMFont *mFightNum;
	//cocos2d::CCSprite *mHeroTotalNum1;
	//cocos2d::CCSprite *mHeroTotalNum2;

	int mCheckedCount; 
	int mCurHeroTotal;

	guidelinesLayer *guideLayer;
};

class HeroWoodFightChooseUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroWoodFightChooseUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroWoodFightChooseUIView);
};

#endif
#ifndef __OTHER_HERO_INFO_UI_VIEW_H__
#define __OTHER_HERO_INFO_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "./base/Global.h"
#include "./ui/element/CCScrollViewEx.h"
  
class ObjectHero;

class OherHeroInfoUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(OherHeroInfoUIView, create);

public:
	OherHeroInfoUIView();
	virtual ~OherHeroInfoUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	//close
	void  onButtonReturn(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	
	void onButtonLeft(cocos2d::CCObject * pSender);
	 
	void  onButtonRight(cocos2d::CCObject * pSender);
	 
	void  skillInfoCallBack( cocos2d::CCObject* pSender );

	void heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr,float scale);
	void heroEquipInfoCallBack(cocos2d::CCObject *pSender);
 
 
	void itemInfoCallBack( cocos2d::CCObject* pSender );
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );

public:
	virtual void onDataUpdate( bool isDataValid = true );

private:

	ObjectHero* mCurHero;
	cocos2d::extension::CCScrollViewPage* mContent;
	cocos2d::CCSprite* mEquipmentPos[MAX_HERO_EQUIPMENT_NUM];
	cocos2d::CCSprite* mSkillPos[MAX_HERO_SKILL_NUM];
	cocos2d::CCLabelBMFont* mSkillText[MAX_HERO_SKILL_NUM];

	cocos2d::CCLabelBMFont* mHeroDesc;
	cocos2d::CCLabelBMFont* mHeroHP;
	cocos2d::CCLabelBMFont* mHeroMP;
	cocos2d::CCLabelBMFont* mHeroAttc;
	cocos2d::CCLabelBMFont* mHeroV;
	cocos2d::CCLabelBMFont* mHeroDef;
	cocos2d::CCLabelBMFont* mHeroDist;

	cocos2d::CCLabelBMFont* _mHeroAttcAdd[5];
 
	cocos2d::CCSprite* mHeroImagePos;
	cocos2d::CCNode *mContentNode;
	cocos2d::CCNode *mContentNode__ ;
	cocos2d::CCLabelTTF *mHeroLevel;
 

	cocos2d::CCSprite *mHeroLevelIconBack;
	cocos2d::CCSprite *mHeroColor;

	cocos2d::extension::CCScale9Sprite* mProcessBar1;
	cocos2d::extension::CCScale9Sprite* mProcessBar2;

	cocos2d::CCLabelBMFont* mSkillLvLabel[2];

	X_VOID showHero(X_INT index,bool b = false);
	void createNavItem(X_INT size);
	X_INT  mNagItemSize;
	cocos2d::CCSprite *m_pQuality;
};

class OtherHeroInfoUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(OtherHeroInfoUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(OherHeroInfoUIView);
};

#endif
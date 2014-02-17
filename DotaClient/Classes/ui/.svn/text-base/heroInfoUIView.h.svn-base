#ifndef __HERO_INFO_UI_VIEW_H__
#define __HERO_INFO_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/guidelinesLayer.h"



class ObjectHero;

class HeroInfoUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(HeroInfoUIView, create);

public:
	HeroInfoUIView();
	virtual ~HeroInfoUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	void onButtonClose(cocos2d::CCObject * pSender);
	void onButtonShare(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonEquipmentChange(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonHeroPromote(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonHeroEvolve(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonEquipmentCompose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void onButtonAddLoad(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);
	void  skillInfoCallBack( cocos2d::CCObject* pSender );

	void changeEquip(cocos2d::CCObject* pSender);
	void heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr ,float scale);
	void heroEquipInfoCallBack(cocos2d::CCObject *pSender);


	void updateHero(cocos2d::CCObject * pSender);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

private:

	  ObjectHero* mCurHero;
	
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

 
	cocos2d::extension::CCControlButton* mbutton[5];

	cocos2d::CCLabelTTF *mHeroLevel;
	cocos2d::CCSprite *mHeroLevelIconBack;
    cocos2d::CCSprite *mHeroColor;
 
	cocos2d::extension::CCScale9Sprite* mProcessBar1;
	cocos2d::extension::CCScale9Sprite* mProcessBar2;
	cocos2d::CCSprite *mshare; 

	cocos2d::CCLabelBMFont* mSkillLvLabel[2];

	guidelinesLayer *guideLayer;
	CCSprite* m_pQuality;
};

class HeroInfoUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(HeroInfoUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(HeroInfoUIView);
};

#endif
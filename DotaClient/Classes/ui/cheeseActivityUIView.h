#ifndef __CHEESEACTIVITYUIVIEW_H__
#define __CHEESEACTIVITYUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/ModalDialogView.h"
#include "./ui/element/CCScrollViewEx.h"

#include "./datapool/HuoDong.h"
#include "./ui/element/guidelinesLayer.h"

#define MAX_HERO_EQUIPMENT_NUM     6
#define MAX_HERO_SKILL_NUM         2
 
class ObjectHero;
class HeroAltar;
class EffectAnimation; 

class  BloodBattleUIView;
class cheeseActivityUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
	, public ModalDialogDelegate
{
	friend class BloodBattleUIView;
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(cheeseActivityUIView, create);

public:
	cheeseActivityUIView();
	virtual ~cheeseActivityUIView();

	virtual void onEnter();
	virtual void onExit();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:
	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );
public:

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);

	void onButtonBag(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent);

	void onButtonLeft(cocos2d::CCObject * pSender);
	void onButtonRight(cocos2d::CCObject * pSender);

	void itemInfoCallBack( cocos2d::CCObject* pSender );
	void __onitemInfoCallBack(int index);
	/*cheese*/

	void onButtonCheese(cocos2d::CCObject * pSender);

	/*creeps*/
	void onButtonCreep(cocos2d::CCObject * pSender);


	/*road*/
	void onButtonFightShunt(cocos2d::CCObject * pSender);


	/*altar*/
	void onButtonAltar(cocos2d::CCObject * pSender);
	void onButtonAltarAwd(cocos2d::CCObject *pSender);
	void updateAltarTextData(HeroAltar *pAltar);

	void initAltarData();
	/*tower*/
	void onButtonTower(cocos2d::CCObject * pSender);
	void getActivityTitleInfo(EM_HUODONG_TYPE _type, string &_icon);

	/*bear*/
	void updateBearTextData();
	void onButtonBearStart(cocos2d::CCObject *pSender);
	void onButtonBear(cocos2d::CCObject *pSender);
	void onButtonYaYun(cocos2d::CCObject *pSender);
	void onButtonXueZhan(cocos2d::CCObject *pSender);
	void updateQujingTextData();


	void onButtonBlood(cocos2d::CCObject *pSender);
	void onButtonAttack(cocos2d::CCObject *pSender);
	void onButtonDefence(cocos2d::CCObject *pSender);

	void onButtonBattle1(cocos2d::CCObject *pSender);
	void onButtonBattle2(cocos2d::CCObject *pSender);
	void onButtonBattle3(cocos2d::CCObject *pSender);
	
	void onBattleEye1(cocos2d::CCObject *pSender);
	void onBattleEye2(cocos2d::CCObject *pSender);
	void onBattleEye3(cocos2d::CCObject *pSender);

	void onButtonGoddess1(cocos2d::CCObject *pSender);
	void onButtonGoddess2(cocos2d::CCObject *pSender);
	void onButtonShare(cocos2d::CCObject *pSender);
	void onButtonShakeShowResult(cocos2d::CCObject *pSender);

	void onButtonGotoShake(cocos2d::CCObject *pSender);
	void updateShakeData();
	void __updateShakeLayer();
	void __updateGoddessLayer();

	void __updateWaitLayer();

	void   updateFreshTime( float time );
	 
public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void updateActivityData(X_UINT actIndex);

	void DisableAllLayer();


	void createNavItem();
	void guideInfoCallBack1( cocos2d::CCObject* pSender );
	void guideInfoCallBack2( cocos2d::CCObject* pSender );
	void guideInfoCallBack3( cocos2d::CCObject* pSender );
protected:
 
	cocos2d::CCNode* mContentNode;
//	X_UINT curSelectActIndex;
	cocos2d::extension::CCScrollViewPage* mContent;

	map<EM_HUODONG_TYPE  ,vector<HuoDong *> > mActivityItems;
	vector<X_INT > mNagItems;

	cocos2d::CCNode *mNodePos;
	cocos2d::CCSprite *mYellowBackGround;

	/*cheese*/
	cocos2d::CCNode *mNodePosCheese;


	cocos2d::CCSprite *mCheeseStateText[3];
	cocos2d::CCNode *mCheeseNode[3];
	cocos2d::CCSprite *mStaCheese[3];
	cocos2d::CCMenuItemImage *mMenuItems[3];

	/*creeps*/
	cocos2d::CCNode *mNodePosCreep;

	cocos2d::CCSprite *mCreepSprites[3];
	cocos2d::CCLabelBMFont *mCreepLabelNum[3];

	cocos2d::CCMenuItemImage *mCreepBtn[3];
	cocos2d::CCSprite *mCreepText[3];
	cocos2d::CCLabelTTF *mCreepTime[3];
	/*road*/
	cocos2d::CCNode *mNodePosShunt;
	cocos2d::CCMenuItemImage *mShuntBtn[3];
	cocos2d::CCLabelTTF *mShuntLabelNum[3];
	cocos2d::CCNode *mRoadTextNode[3];
	cocos2d::CCLabelTTF *mRoadTime[3];
	/*altar*/
	cocos2d::CCNode *mNodePosAltar;
	cocos2d::CCSprite *mProgressPos;
	cocos2d::CCLabelTTF *mCurStoneNum;
	cocos2d::CCLabelTTF *mUseStoneNum;

	cocos2d::CCMenuItemImage *mHeroAltar[5];
	cocos2d::CCMenuItemImage *mAltarBigIcon;
	cocos2d::CCLabelTTF *mAltarEquip[4];

	cocos2d::CCNode *mAltarContentNode;

	int mLastIndex;
	/*tower*/
	cocos2d::CCNode *mNodePosTower;
	cocos2d::CCLabelBMFont *mGankNum[3];

	cocos2d::CCMenuItemImage *mTowerBtn[3];
	cocos2d::CCSprite *mTowerText[3];
	cocos2d::CCLabelTTF *mTowerTime[3];

	/*bear*/
	cocos2d::CCNode *mNodePosBear;
	cocos2d::CCLabelTTF *mBearValue;
	cocos2d::CCLabelTTF *mBearNum;
	cocos2d::CCLabelTTF *mBearCost[3];
	cocos2d::CCMenuItemImage *mBearBtn[3];
	cocos2d::CCSprite *mBearSprite[3];
	cocos2d::CCLabelTTF *mBearInfo[3];
	EffectAnimation *effect;
	bool isAltaring;

// 	cocos2d::CCLayerMultiplex *layerCont;

	void ShowAltaringEffect(X_INT id);


	//--------------取经
	cocos2d::CCSprite *mHero[5];
	cocos2d::CCSprite *mHeroIcon[5];
	cocos2d::CCLabelTTF *mLJTime;
	cocos2d::CCLabelTTF *mHSNum;
	cocos2d::CCLabelTTF *mHSTip;
	cocos2d::CCMenuItemImage *mYaYunBtn;
	cocos2d::CCNode *mNodePosQuJing;

	cocos2d::CCLabelTTF *mYaYunTime1;
	cocos2d::CCLabelTTF *mYaYunTime2;
	cocos2d::CCLabelTTF *mYaYunTime3;
	cocos2d::CCLabelTTF *mHSaAllHeroTip;
	//---------血战
	BloodBattleUIView*   m_pBloodBattleUI;

	//---------摇一摇 女神
	cocos2d::CCNode *mNodePosShake;
	cocos2d::CCNode *mGoddessInfo;
	cocos2d::CCSprite *mShakeSprite;
	cocos2d::CCNode *mShakeIntroduce;
 
	cocos2d::CCNode *mShakePopu;
	cocos2d::CCLabelTTF *mShakeMidLabel;



	//cocos2d::CCLabelBMFont *mShakeLastNum;
	cocos2d::CCLabelBMFont *mShakeTime;
	cocos2d::CCLabelBMFont *mShakeCount;

	cocos2d::CCSprite *mHeroImagePos;
	cocos2d::CCSprite *mHeroColor;
	cocos2d::extension::CCScale9Sprite* mProcessBar1;
	cocos2d::extension::CCScale9Sprite* mProcessBar2;
	cocos2d::CCSprite *mHeroLevelIconBack;
	cocos2d::CCLabelBMFont *mSkillText[2];
	cocos2d::CCLabelBMFont *mHeroDesc;
	cocos2d::CCLabelBMFont *mHeroHp;
	cocos2d::CCLabelBMFont *mHeroMp;
	cocos2d::CCSprite *mGoddessSkillPos[2];
	cocos2d::CCLabelTTF *mGoddessSkill[2];
	cocos2d::CCMenuItemImage *mShakeGoddess1;
	cocos2d::CCSprite* mShakeTitle;
	cocos2d::CCSprite* mGoddessJoin;
	cocos2d::CCSprite* mShakeStamp;
	cocos2d::CCMenuItemImage *mShakeGoddess2;
	cocos2d::CCMenuItemImage *mShakeShare;
	//GUIDE
	guidelinesLayer *guideLayer;
	
};

class BloodBattleUIView
	: public cocos2d::CCNode
	, public cocos2d::extension::CCBMemberVariableAssigner
{

	friend class cheeseActivityUIView;
public:
	BloodBattleUIView(cheeseActivityUIView*  pUIView);
	~BloodBattleUIView();
	virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
	void DisableAllLayer();
	void VisableLayer();

	//----------------

	void updateXueZhanTextData();

	//开始进入血战
	void onButtonXueZhan();
	//选择buffer
	void onButtonBlood();
	void onButtonAttack();
	void onButtonDefence();
	void onButtonBattle(X_INT index);
	void onBattleEye(X_INT index);
 
private:
	cheeseActivityUIView*		m_pBaseUIView;

	//挑战界面
	X_VOID _updateEnterUI();
	//	buffer界面
	X_VOID _updateBufferUI();
	//战斗
	X_VOID _updateBattleUI();
	
public:
	void onButtonChallenge(cocos2d::CCObject * pSender);
private:
	//进入界面
	cocos2d::CCNode *			mNodePosXueZhan;
	cocos2d::CCLabelTTF*	mXueZhanNum;
	cocos2d::CCLabelTTF*	mXueZhanEnterTip1;
	cocos2d::CCLabelTTF*	mXueZhanEnterTip2;
	cocos2d::CCMenuItemImage* mXueZhanBtn;

	//选择界面

	cocos2d::CCNode *			mNodePosXueZhanBuffer;
	cocos2d::CCLabelTTF*	mXueZhanJiFen;
 
	cocos2d::CCLabelTTF*	mXueZhanBufferRecord;

	cocos2d::CCLabelTTF*	mXueZhanCost[3];
	cocos2d::CCLabelTTF*	mXueZhanTip[3];
	cocos2d::CCLabelTTF*	mXueZhanBufferAddTip;

	cocos2d::CCMenuItemImage* mButtonBattleSelect[3];

	//-----------------战斗
	cocos2d::CCNode *			mNodePosXueZhanBattle;
	cocos2d::CCLabelTTF*	mXueZhanBattleJiFen;
	cocos2d::CCLabelTTF*	mXueZhanBattleAddTip;
	cocos2d::CCLabelTTF*	mXueZhanBattleRecord;
  
	cocos2d::CCSprite* mBattleAward[3];
	cocos2d::CCSprite* mBattleJifen[3];
	//cocos2d::CCMenuItemImage* mButtonBattle[3];

	cocos2d::CCMenuItemImage* mBattleEye[3];

	cocos2d::CCSprite* mbattleMonster[18];

public:
	void onButtonSelect(cocos2d::CCObject * pSender);
private:
	cocos2d::CCNode*			m_NodeReward;
};
class cheeseActivityUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(cheeseActivityUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(cheeseActivityUIView);
};

#endif

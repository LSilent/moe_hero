#include "./ui/cheeseActivityUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "./ui/element/CCMenuEx.h"
#include "./datapool/SportsData.h"

#include "./ui/element/ProgressView.h"
#include "./game/GameHelper.h"
#include "./ui/cheeseActivityUI.h"
#include "./ui/element/SkillAnimation.h"

#include "./ui/element/FightTips.h"
#include "./datapool/QuJingData.h"
#include "./datapool/BloodData.h"
#include "./game/GameHelper.h"
#include "./base/Sdk_Handler.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (256)
#define MAX_ACT_NUM				 (3)

#define CONTENT_POS_X            (0.100f)
#define CONTENT_POS_Y            (0.858f)//(0.455f)

#define CONTENT_VIEW_SIZE_X      (0.80f)
#define CONTENT_VIEW_SIZE_Y      (0.2f)

#define ITEM_SPACE_DELTA_X       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.115f)//(0.127f)//(0.130f)

#define ITEM_START_X			 (0.09f) //(0.111f)
#define ITEM_START_Y             (0.06f)//(0.45f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            1

#define  MAX_ALTAR_NUM			5 


#define DIALOG_TAG_CREEP_BEAR   500
#define DIALOG_TAG_ALT_CHARGE   501
#define DIALOG_TAG_COST_GOLD    502
#define DIALOG_TAG_NO_GOLD      503	
#define DIALOG_TAG_RESHAKE_GODDESS 504

#define PROGRESSBAR_START_X		(0.243f)
#define PROGRESSBAR_START_Y		(0.59f)

#define PROGRESSBAR_LABLE_OFFSET_X		(0.10f)
#define PROGRESSBAR_LABLE_OFFSET_Y		(0.02f)

#define MAX_ANIMATION_FRAMES         (32)

cheeseActivityUIView::cheeseActivityUIView()
: mNodePos(NULL)
, mNodePosCheese(NULL)
, mNodePosCreep(NULL)
, mNodePosShunt(NULL)
, mNodePosAltar(NULL)
, mProgressPos(NULL)
, mCurStoneNum(NULL)
, mUseStoneNum(NULL)
, mNodePosTower(NULL)
, mAltarBigIcon(NULL)
, mNodePosBear(NULL)
, mBearValue(NULL)
, mBearNum(NULL)
,mNodePosQuJing(NULL)
,mNodePosShake(NULL)
,mShakePopu(NULL)
,mShakeMidLabel(NULL)
,mYellowBackGround(NULL)
{
	 m_pBloodBattleUI		= new BloodBattleUIView(this);
	 
	mContentNode = NULL;
	mAltarContentNode = NULL;
	guideLayer = NULL;


	for (int i = 0; i < 3 ; i++)
	{
		mCreepSprites[i] = NULL;
		mCreepLabelNum[i] = NULL;
		mShuntLabelNum[i] = NULL;
		mCheeseStateText[i] = NULL;
		mCheeseNode[i] = NULL;
		mStaCheese[i] = NULL;
		mMenuItems[i] = NULL;
		mGankNum[i] = NULL;
		mTowerBtn[i] = NULL;
		mShuntBtn[i] = NULL;
		mCreepBtn[i] = NULL;
		mCreepText[i] = NULL;
		mCreepTime[i] = NULL;
		mRoadTextNode[i] = NULL;
		mRoadTime[i] = NULL;
		mTowerText[i] = NULL;
		mTowerTime[i] = NULL;
		mBearCost[i] = NULL;
		mBearSprite[i] = NULL;
		mBearBtn[i] = NULL;
		mBearInfo[i] = NULL;

	}

	mLJTime = NULL;
	mHSNum = NULL;
	mYaYunBtn = NULL;
	mHSTip = NULL;
	mYaYunTime1 = NULL;
	mYaYunTime2 = NULL;
	mYaYunTime3 = NULL;
	mHSaAllHeroTip = NULL;

	mShakeSprite = NULL;
	mGoddessInfo = NULL;
	//mShakeLastNum = NULL;
	mShakeIntroduce = NULL;
	mShakeTime = NULL;
	mShakeCount = NULL;
	mHeroImagePos = NULL;
	mHeroColor = NULL;
	mProcessBar1 = NULL;
	mProcessBar2 = NULL;
	mHeroLevelIconBack = NULL;
	mSkillText[0] = NULL;
	mSkillText[1] = NULL;
	mHeroDesc = NULL;
	mHeroHp = NULL;
	mHeroMp = NULL;
	mGoddessSkillPos[0] = NULL;
	mGoddessSkillPos[1] = NULL;
	mGoddessSkill[0] = NULL;
	mGoddessSkill[1] = NULL;
	mShakeGoddess1 = NULL;
	mShakeGoddess2 = NULL;
	mShakeTitle = NULL;
	mGoddessJoin = NULL;
	mShakeStamp = NULL;
	mShakeShare = NULL;
 
	for (int j = 0; j < 5 ; j++)
	{
		mHeroAltar[j] = NULL;
		mHero[j] = NULL;
		mHeroIcon[j] =NULL;
	}

	for (int i = 0;i < 4 ; i++)
	{
		mAltarEquip[i] = NULL;
	}
	
	effect = NULL;
	isAltaring = false;

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	if (!pUi)return;

	pUi->m_HuoDongIndex = 0 ;
 
	mLastIndex = -1;


	
}

cheeseActivityUIView::~cheeseActivityUIView()
{
	 
	CC_SAFE_RELEASE(mNodePos);
	CC_SAFE_RELEASE(mNodePosCheese);
	CC_SAFE_RELEASE(mNodePosCreep);
	CC_SAFE_RELEASE(mNodePosShunt);

	CC_SAFE_RELEASE(mAltarBigIcon);

	for (int i = 0; i < 3 ; i++)
	{
		CC_SAFE_RELEASE(mCreepSprites[i]);
		CC_SAFE_RELEASE(mCreepLabelNum[i]);
		CC_SAFE_RELEASE(mShuntLabelNum[i]);
		CC_SAFE_RELEASE(mCheeseStateText[i]);
		CC_SAFE_RELEASE(mCheeseNode[i]);
		CC_SAFE_RELEASE(mStaCheese[i]);
		CC_SAFE_RELEASE(mMenuItems[i]);
		CC_SAFE_RELEASE(mGankNum[i]);
		CC_SAFE_RELEASE(mTowerBtn[i]);
		CC_SAFE_RELEASE(mCreepBtn[i]);
		CC_SAFE_RELEASE(mShuntBtn[i]);
		CC_SAFE_RELEASE(mCreepText[i]);
		CC_SAFE_RELEASE(mCreepTime[i]);
		CC_SAFE_RELEASE(mRoadTextNode[i]);
		CC_SAFE_RELEASE(mRoadTime[i]);
		CC_SAFE_RELEASE(mTowerText[i]);
		CC_SAFE_RELEASE(mTowerTime[i]);
		CC_SAFE_RELEASE(mBearCost[i]);
		CC_SAFE_RELEASE(mBearSprite[i]);
		CC_SAFE_RELEASE(mBearBtn[i]);
		CC_SAFE_RELEASE(mBearInfo[i]);
 
	}

	CC_SAFE_RELEASE(mNodePosAltar);
	CC_SAFE_RELEASE(mProgressPos);
	CC_SAFE_RELEASE(mCurStoneNum);
	CC_SAFE_RELEASE(mUseStoneNum);

	CC_SAFE_RELEASE(mNodePosBear);
	CC_SAFE_RELEASE(mBearValue);
	CC_SAFE_RELEASE(mBearNum);

	CC_SAFE_RELEASE(mLJTime);
	CC_SAFE_RELEASE(mHSNum);
	CC_SAFE_RELEASE(mYaYunBtn);
	CC_SAFE_RELEASE(mNodePosQuJing);
	CC_SAFE_RELEASE(mYaYunTime1);
	CC_SAFE_RELEASE(mYaYunTime2);
	CC_SAFE_RELEASE(mYaYunTime3);
	CC_SAFE_RELEASE(mHSaAllHeroTip);

	CC_SAFE_RELEASE(mShakePopu);
	CC_SAFE_RELEASE(mShakeMidLabel);
 

	CC_SAFE_RELEASE(mNodePosShake);
	CC_SAFE_RELEASE(mShakeSprite);
	CC_SAFE_RELEASE(mGoddessInfo);
	CC_SAFE_RELEASE(mShakeIntroduce);
	//CC_SAFE_RELEASE(mShakeLastNum);
	CC_SAFE_RELEASE(mShakeTime);
	CC_SAFE_RELEASE(mShakeCount);
	CC_SAFE_RELEASE(mHeroImagePos);
	CC_SAFE_RELEASE(mHeroColor);
	CC_SAFE_RELEASE(mProcessBar1);
	CC_SAFE_RELEASE(mProcessBar2);
	CC_SAFE_RELEASE(mHeroLevelIconBack);
	CC_SAFE_RELEASE(mSkillText[0]);
	CC_SAFE_RELEASE(mSkillText[1]);
	CC_SAFE_RELEASE(mHeroDesc);
	CC_SAFE_RELEASE(mHeroHp);
	CC_SAFE_RELEASE(mHeroMp);
	CC_SAFE_RELEASE(mGoddessSkillPos[0]);
	CC_SAFE_RELEASE(mGoddessSkillPos[1]);
	CC_SAFE_RELEASE(mGoddessSkill[0]);
	CC_SAFE_RELEASE(mGoddessSkill[1]);
	CC_SAFE_RELEASE(mShakeGoddess1);
	CC_SAFE_RELEASE(mShakeGoddess2);
	CC_SAFE_RELEASE(mShakeTitle);
	CC_SAFE_RELEASE(mGoddessJoin);
	CC_SAFE_RELEASE(mShakeStamp);
	CC_SAFE_RELEASE(mShakeShare);

 
	for (int j = 0; j < 5 ; j++)
	{
		CC_SAFE_RELEASE(mHeroAltar[j]);
		CC_SAFE_RELEASE(mHero[j]);

	}

	for (int i = 0;i < 4 ; i++)
	{
		CC_SAFE_RELEASE(mAltarEquip[i]);
	}

	CC_SAFE_RELEASE(mNodePosTower);
	CC_SAFE_RELEASE(mHSTip);
	CC_SAFE_DELETE(m_pBloodBattleUI);

	CC_SAFE_RELEASE(mYellowBackGround);
	
}

void cheeseActivityUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	mBearBtn[0]->setUserData((void*)1);
	mBearBtn[1]->setUserData((void*)2);
	mBearBtn[2]->setUserData((void*)3);
}


SEL_MenuHandler cheeseActivityUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	 
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCheese", cheeseActivityUIView::onButtonCheese);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonTower", cheeseActivityUIView::onButtonTower);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCreep", cheeseActivityUIView::onButtonCreep);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonFightShunt", cheeseActivityUIView::onButtonFightShunt);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonLeft", cheeseActivityUIView::onButtonLeft);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRight", cheeseActivityUIView::onButtonRight);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAltar", cheeseActivityUIView::onButtonAltar);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAltarAwd", cheeseActivityUIView::onButtonAltarAwd);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBearStart", cheeseActivityUIView::onButtonBearStart);
	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBear", cheeseActivityUIView::onButtonBear);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonYaYun", cheeseActivityUIView::onButtonYaYun);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonXueZhan", cheeseActivityUIView::onButtonXueZhan);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBlood", cheeseActivityUIView::onButtonBlood);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAttack", cheeseActivityUIView::onButtonAttack);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonDefence", cheeseActivityUIView::onButtonDefence);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBattle1", cheeseActivityUIView::onButtonBattle1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBattle2", cheeseActivityUIView::onButtonBattle2);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBattle3", cheeseActivityUIView::onButtonBattle3);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattleEye1", cheeseActivityUIView::onBattleEye1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattleEye2", cheeseActivityUIView::onBattleEye2);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattleEye3", cheeseActivityUIView::onBattleEye3);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonGoddess1", cheeseActivityUIView::onButtonGoddess1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonGoddess2", cheeseActivityUIView::onButtonGoddess2);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonShare", cheeseActivityUIView::onButtonShare);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonGotoShake", cheeseActivityUIView::onButtonGotoShake);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonShakeShowResult", cheeseActivityUIView::onButtonShakeShowResult);

	return NULL;    
}

SEL_CCControlHandler cheeseActivityUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonBag", cheeseActivityUIView::onButtonBag);

	return NULL;
}

bool cheeseActivityUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
   
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMorningText", CCSprite *,mCheeseStateText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNoonText", CCSprite *,mCheeseStateText[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNightText", CCSprite *, mCheeseStateText[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeMorning", CCNode *, mCheeseNode[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeNoon", CCNode *, mCheeseNode[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeNight", CCNode *, mCheeseNode[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStaCheeseMorning", CCSprite *, mStaCheese[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStaCheeseNoon", CCSprite *, mStaCheese[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStaCheeseNight", CCSprite *, mStaCheese[2]);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePos", CCNode *, mNodePos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosCreep", CCNode *, mNodePosCreep);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosShunt", CCNode *, mNodePosShunt);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosCheese", CCNode *, mNodePosCheese);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosTower", CCNode *, mNodePosTower);
	

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreep1", CCSprite *, mCreepSprites[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreep2", CCSprite *, mCreepSprites[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreep3", CCSprite *, mCreepSprites[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepNum1", CCLabelBMFont *, mCreepLabelNum[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepNum2", CCLabelBMFont *, mCreepLabelNum[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepNum3", CCLabelBMFont *, mCreepLabelNum[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoad1", CCLabelTTF *, mShuntLabelNum[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoad2", CCLabelTTF *, mShuntLabelNum[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoad3", CCLabelTTF *, mShuntLabelNum[2]);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosAltar", CCNode *, mNodePosAltar);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProgressPos", CCSprite *, mProgressPos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCurStoneNum", CCLabelTTF *, mCurStoneNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUseStoneNum", CCLabelTTF *, mUseStoneNum);

	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarBigIcon", CCMenuItemImage *, mAltarBigIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAltar1", CCMenuItemImage *, mHeroAltar[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAltar2", CCMenuItemImage *, mHeroAltar[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAltar3", CCMenuItemImage *, mHeroAltar[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAltar4", CCMenuItemImage *, mHeroAltar[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAltar5", CCMenuItemImage *, mHeroAltar[4]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarEquip1", CCLabelTTF *, mAltarEquip[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarEquip2", CCLabelTTF *, mAltarEquip[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarEquip3", CCLabelTTF *, mAltarEquip[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarEquip4", CCLabelTTF *, mAltarEquip[3]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGank1", CCLabelBMFont *, mGankNum[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGank2", CCLabelBMFont *, mGankNum[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGank3", CCLabelBMFont *, mGankNum[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerBtn1", CCMenuItemImage *, mTowerBtn[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerBtn2", CCMenuItemImage *, mTowerBtn[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerBtn3", CCMenuItemImage *, mTowerBtn[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerText1", CCSprite *, mTowerText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerText2", CCSprite *, mTowerText[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerText3", CCSprite *, mTowerText[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerTime1", CCLabelTTF *, mTowerTime[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerTime2", CCLabelTTF *, mTowerTime[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTowerTime3", CCLabelTTF *, mTowerTime[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepBtn1", CCMenuItemImage *, mCreepBtn[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepBtn2", CCMenuItemImage *, mCreepBtn[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepBtn3", CCMenuItemImage *, mCreepBtn[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepText1", CCSprite *, mCreepText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepText2", CCSprite *, mCreepText[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepText3", CCSprite *, mCreepText[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepTime1", CCLabelTTF *, mCreepTime[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepTime2", CCLabelTTF *, mCreepTime[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCreepTime3", CCLabelTTF *, mCreepTime[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShuntBtn1", CCMenuItemImage *, mShuntBtn[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShuntBtn2", CCMenuItemImage *, mShuntBtn[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShuntBtn3", CCMenuItemImage *, mShuntBtn[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTextNode1", CCNode *, mRoadTextNode[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTextNode2", CCNode *, mRoadTextNode[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTextNode3", CCNode *, mRoadTextNode[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTime1", CCLabelTTF *, mRoadTime[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTime2", CCLabelTTF *, mRoadTime[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRoadTime3", CCLabelTTF *, mRoadTime[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuMorning", CCMenuItemImage *, mMenuItems[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuNoon", CCMenuItemImage *, mMenuItems[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMenuNight", CCMenuItemImage *, mMenuItems[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosBear", CCNode *, mNodePosBear);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearValue", CCLabelTTF *, mBearValue);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearNum", CCLabelTTF *, mBearNum);

	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCost1", CCLabelTTF *, mBearCost[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCost2", CCLabelTTF *, mBearCost[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCost3", CCLabelTTF *, mBearCost[2]);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearSprite1", CCSprite *, mBearSprite[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearSprite2", CCSprite *, mBearSprite[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearSprite3", CCSprite *, mBearSprite[2]);
	


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButton1", CCMenuItemImage *, mBearBtn[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButton2", CCMenuItemImage *, mBearBtn[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButton3", CCMenuItemImage *, mBearBtn[2]);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearInfo1", CCLabelTTF *, mBearInfo[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearInfo2", CCLabelTTF *, mBearInfo[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBearInfo3", CCLabelTTF *, mBearInfo[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHero1", CCSprite *, mHero[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHero2", CCSprite *, mHero[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHero3", CCSprite *, mHero[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHero4", CCSprite *, mHero[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHero5", CCSprite *, mHero[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLJTime", CCLabelTTF *, mLJTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHSNum", CCLabelTTF *, mHSNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHSTip", CCLabelTTF *, mHSTip);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mYaYunBtn", CCMenuItemImage *,mYaYunBtn);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosQuJing", CCNode *, mNodePosQuJing);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePosShake",CCNode*, mNodePosShake);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeSprite", CCSprite*, mShakeSprite);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessInfo", CCNode*, mGoddessInfo);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeLastNum", CCLabelBMFont*, mShakeLastNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeIntroduce", CCNode*, mShakeIntroduce);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakePopu",CCNode*, mShakePopu);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeMidLabel", CCLabelTTF*, mShakeMidLabel);
	  
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeTime", CCLabelBMFont*, mShakeTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeCount", CCLabelBMFont*, mShakeCount);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroImagePos", CCSprite*, mHeroImagePos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroColor", CCSprite*, mHeroColor);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar1", CCScale9Sprite*, mProcessBar1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar2", CCScale9Sprite*, mProcessBar2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroLevelIconBack", CCSprite*, mHeroLevelIconBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillText1", CCLabelBMFont*, mSkillText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillText2", CCLabelBMFont*, mSkillText[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroDesc", CCLabelBMFont*, mHeroDesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroHP", CCLabelBMFont*, mHeroHp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroMP", CCLabelBMFont*, mHeroMp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessSkillPos1", CCSprite*, mGoddessSkillPos[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessSkillPos2", CCSprite*, mGoddessSkillPos[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessSkill1", CCLabelTTF*, mGoddessSkill[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessSkill2", CCLabelTTF*, mGoddessSkill[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeGoddess1", CCMenuItemImage *, mShakeGoddess1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeGoddess2", CCMenuItemImage *, mShakeGoddess2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeTitle", CCSprite*, mShakeTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGoddessJoin", CCSprite*, mGoddessJoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeStamp", CCSprite*, mShakeStamp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShakeShare", CCMenuItemImage*, mShakeShare);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mYaYunTime1", CCLabelTTF *,mYaYunTime1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mYaYunTime2", CCLabelTTF *, mYaYunTime2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mYaYunTime3", CCLabelTTF *, mYaYunTime3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHSaAllHeroTip", CCLabelTTF *, mHSaAllHeroTip);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mYellowBackGround", CCSprite *, mYellowBackGround);
  

	m_pBloodBattleUI->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
 
	
    return false;
}

bool cheeseActivityUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

void cheeseActivityUIView::onButtonBag(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

// on "init" you need to initialize your instance
bool cheeseActivityUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

// void userInfoUIView::onButtonCancel(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
// {
// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_CLOSE);
// }


void cheeseActivityUIView::initAltarData()
{
	const vector<HeroAltar*> & AltarArray  = DataPool::GetSingleton()->getHeroAltarData()->getHeroAltar();
	ObjectSelf *pself = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData *pData = pself->playerData();

	X_INT sacID = pData->GetSacrificeID() ;
	X_INT sacDamage = pData->GetSacrificeDamage(); //up limit 1500

	for (int i = 0; i< MAX_ALTAR_NUM ;i ++)
	{
		HeroAltar *altar = AltarArray[i];
		if (altar->getOpenLevel() <= pData->GetLevel())
		{
			if (sacID == -1 && i == 0)
			{
				mHeroAltar[i]->selected();
				mLastIndex = i;
				//big icon
				char buffFileName[MAX_STRING_BUFF_SIZE] = {0};
				sprintf(buffFileName,"n_altar_big_%d.png",(i+1));
				mAltarBigIcon->setNormalImage(CCSprite::create(buffFileName));
                mAltarBigIcon->setUserData(altar);

				SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,altar->getID());

				updateAltarTextData(altar);
			}
			else if (sacID >= 0 && sacID == i)
			{
				mHeroAltar[sacID]->selected();
				mLastIndex = i;
				//big icon
				char buffFileName[MAX_STRING_BUFF_SIZE] = {0};
				sprintf(buffFileName,"n_altar_big_%d.png",(i+1));
				mAltarBigIcon->setNormalImage(CCSprite::create(buffFileName));
                mAltarBigIcon->setUserData(altar);

				updateAltarTextData(altar);
			}
			else
			{
				mHeroAltar[i]->unselected();
			}
			
		}
		else
		{
			mHeroAltar[i]->setEnabled(false);
		}
		mHeroAltar[i]->setUserData((void *)(i+1));
	}
	
}
//1-3
void cheeseActivityUIView::ShowAltaringEffect(X_INT id)
{
	CCSprite *spite =  mBearSprite[id-1];
	if (!spite)
	{
		return;
	}
	
	if (!isAltaring)
	{
		//return;
		//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		effect = EffectAnimation::createWith("xianji",23,5.0f,0.03f,true,false);
		//effect->setPosition(ccp(spite->getPositionX() , spite->getPositionY()+spite->getContentSize().height *0.5));
		//addChild(effect);
		effect->setAnchorPoint(CCPoint(0.5f,0.5f));
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		effect->setPosition(ccpAdd(spite->getPosition(),ccp(0, winSize.height * 0.30f)));
		this->addChild(effect);

		effect->playAnimation();
		effect->setUserData( (void*)id);
		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND4);

		isAltaring = true;
	}
}
void cheeseActivityUIView::onButtonBearStart(cocos2d::CCObject *pSender)
{
	 
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	ObjectManager *pManager = DataPool::GetSingleton()->getObjectManager();
	PlayerData* pData =   pManager->getSelf()->playerData();

	X_INT num = pData->GetBuyBearPointCount();

	X_INT canBuyNum =0;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_BEARPOINT_BUYNUM);
		if (pTableData)
		{
			canBuyNum = pTableData->m_value;
		}	
	}

	if (canBuyNum == num)
	{
		//提示达到购买次数上限
		string strTitle = UtilTools::GET_TEXT_FROM_LANG(720);
		ModalDialogView *dialog = ModalDialogView::createDialog(strTitle,this,DIALOG_MODEL_SINGLE);
		addChild(dialog,10);
	}
	else
	{

	 
		int id = (int)((CCNode *)pSender)->getUserData();
		X_INT level,bearpoint;X_UINT cost;
		bool bok = GameHelper::getBuyBearPointCost(id,cost,level,bearpoint);

		if (cost == 0)
		{
			//购买发送
			SendLogicPacket::BuyBearPoint(id);
			ShowAltaringEffect(id);
		}
		else if (pData->GetGold() >= cost)
		{
			char buff[MAX_STRING_BUFF_SIZE] = {0};
			sprintf(buff,UtilTools::GET_TEXT_FROM_LANG(578),cost);
			ModalDialogView *dialog = ModalDialogView::createDialog(buff,this);
			dialog->setTag(DIALOG_TAG_COST_GOLD);
			dialog->setDailogUserData((void*)id);
			addChild(dialog,10);
		}
		else
		{
			string strTitle = UtilTools::GET_TEXT_FROM_LANG(550);
			ModalDialogView *dialog = ModalDialogView::createDialog(strTitle,this);
			dialog->setTag(DIALOG_TAG_NO_GOLD);
			addChild(dialog,10);
		}
	}
	
}

void cheeseActivityUIView::onButtonBear(cocos2d::CCObject *pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void cheeseActivityUIView::onButtonYaYun(cocos2d::CCObject *pSender)
{ 
	QuJingData * pData = DataPool::GetSingleton()->GetQuJingData();

	X_INT needLevel = 0;
	if (!pData->IsCanQujingForLevel(needLevel))
	{
		vector<string> strV;strV.clear();

		char str[256] = {0};
		sprintf(str,UtilTools::GET_TEXT_FROM_LANG(703),needLevel);
		strV.push_back(str);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
	
 
	bool canQujing = pData->IsCanQujing();
	if (!canQujing)
	{
		 vector<string> strV;strV.clear();
		 strV.push_back(UtilTools::GET_TEXT_FROM_LANG(700));
		 EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		 return;
	}
 

	SendLogicPacket::OpenQuJingUi();
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void cheeseActivityUIView::onButtonXueZhan(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonXueZhan();
	}
}
void cheeseActivityUIView::onButtonBlood(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonBlood();
	}
}
void cheeseActivityUIView::onButtonAttack(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonAttack();
	}
}
void cheeseActivityUIView::onButtonDefence(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonDefence();
	}
}

void cheeseActivityUIView::onButtonBattle1(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonBattle(2);
	}
}
void cheeseActivityUIView::onButtonBattle2(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonBattle(1);
	}
}
void cheeseActivityUIView::onButtonBattle3(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onButtonBattle(0);
	}
}


void cheeseActivityUIView::onBattleEye1(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onBattleEye(2);
	}
	// 点击显示第一组 ，实际挑战的第3组怪物（3倍积分怪物）
}
void cheeseActivityUIView::onBattleEye2(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onBattleEye(1);
	}
}
void cheeseActivityUIView::onBattleEye3(cocos2d::CCObject *pSender)
{
	if (m_pBloodBattleUI)
	{
		m_pBloodBattleUI->onBattleEye(0);
	}
}

void cheeseActivityUIView::onButtonGoddess1(cocos2d::CCObject *pSender)
{
	//女神加入出战
	SendLogicPacket::SetGoddessMatrix();
	
}
void cheeseActivityUIView::onButtonGoddess2(cocos2d::CCObject *pSender)
{
	CCLOG("Goddess button2");

	//重摇
	//if ( DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetRockLeftTimes() > 0  )
	{
		ModalDialogView *dialog = ModalDialogView::createDialog( UtilTools::GET_TEXT_FROM_LANG(722),this);
		dialog->setTag(DIALOG_TAG_RESHAKE_GODDESS);
		addChild(dialog,10);
	}
}

void cheeseActivityUIView::onButtonGotoShake(cocos2d::CCObject *pSender)
{
  ((cheeseActivityUI*)(getUserData()))->m_layerShake =  EM_SHAKE_ENTER_LAYER_SHOW;	
	updateShakeData();
  	
}
void cheeseActivityUIView::onButtonShakeShowResult(cocos2d::CCObject *pSender)
{
	SendLogicPacket::RockHer(DataPool::GetSingleton()->getHuoDongData()->getShakeNum());
 
}
void cheeseActivityUIView::onButtonShare(cocos2d::CCObject *pSender)
{

	ObjectManager *pm = DataPool::GetSingleton()->getObjectManager();
	
	ObjectHero *phero = static_cast<ObjectHero*>(pm->FindInstance(OBJECT_TYPE_HERO,pm->getSelf()->playerData()->GetGoddessHeroGuid()));
	if (!phero)
	{
		return;
	}
	X_CHAR str[10240] = {0};
	string name = pm->getSelf()->playerData()->getName();
	sprintf(str,UtilTools::GET_TEXT_FROM_LANG(719),phero->GetName().c_str() ,Game::sm_SelectServer,Game::getSelectServerName().c_str(),name.c_str(),UtilTools::GET_TEXT_FROM_LANG(717));
	SdkHandler::shareInfo = str;
}
 
void cheeseActivityUIView::onButtonCheese(cocos2d::CCObject * pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();
	if (pObj == NULL)
	{
		return;
	}

	int curIndex = (int)pObj - 1;

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	if (!pUi)return;

	map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(pUi->m_HuoDongIndex));
	if (ifind == mActivityItems.end())
	{
		return;
	}

	vector<HuoDong *> hds = ifind->second;
	HuoDong *hd = hds[curIndex];

	int actLvl = hd->getLevelNeed();
	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();

	if (pData->GetLevel()>= actLvl)
	{
		SendLogicPacket::EnjoyHuoDong(hd);

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND8);
	}
	else
	{
		string strTip = UtilTools::GET_TEXT_FROM_LANG(1);
		ModalDialogView *dialogView = ModalDialogView::createDialog(strTip,this,DIALOG_MODEL_SINGLE);
		addChild(dialogView,1);
	}
	

	//onDataUpdate

}

void cheeseActivityUIView::onButtonTower(cocos2d::CCObject * pSender)
{

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();

	int curIndex = (int)pObj - 1;

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	if (!pUi)return;

	map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(pUi->m_HuoDongIndex));
	if (ifind == mActivityItems.end())
	{
		return;
	}

	vector<HuoDong *> hds = ifind->second;
	HuoDong *hd = hds[curIndex];

	string strTip;

	if (hd->getState() == EM_C_STATE_DONE)
	{
		if( hd->getNum() >= MAX_ACT_NUM)
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}
		else
		{

		}
	}else if (hd->getState() == EM_STATE_HUODONG_RUN)
	{
		if( hd->getNum() < MAX_ACT_NUM)
		{
			
			ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
			PlayerData* pData = pSelf->playerData();

			if (hd->getCopySceneNeedAction() > pData->GetActionPoint())
			{

				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(571),this);
				dialog->setTag(DIALOG_TAG_CREEP_BEAR);
				addChild(dialog,10);

				return;
			}
			else
			{
				int actLvl = hd->getLevelNeed();
				if (pData->GetLevel()>= actLvl)
				{
					DataPool::GetSingleton()->BattlyType = EM_BATTLETYPE_GANK;
					cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
					if (pUi)
					{ 
						pUi->m_HuoDongIndex  =EM_GANK;
					}
					SendLogicPacket::EnjoyHuoDong(hd);

					return;
				}
				else
				{
					strTip = UtilTools::GET_TEXT_FROM_LANG(1);
				}
			}
		}
		else
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}
		
	}
	
	/*if (hd->getState() == EM_STATE_HUODONG_INVALID || hd->getState() == EM_STATE_HUODONG_DIABLE)
	{
		strTip = UtilTools::GET_TEXT_FROM_LANG(546);
	}
	else if(hd->getState() == EM_STATE_HUODONG_END)
	{
		strTip = UtilTools::GET_TEXT_FROM_LANG(547);
	}*/

	ModalDialogView *dialogView = ModalDialogView::createDialog(strTip,this,DIALOG_MODEL_SINGLE);
	addChild(dialogView,1);

	
}


// void cheeseActivityUIView::onButtonNoon(cocos2d::CCObject * pSender)
// {
// 	// 	ModalDialogView *dialogPur = ModalDialogView::createDialog("aaaaaaaaa",this);
// 	// 	addChild(dialogPur,1);
// }
// 
// 
// void cheeseActivityUIView::onButtonNight(cocos2d::CCObject * pSender)
// {
// 	// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_USER_INFO_CLOSE);
// }

void cheeseActivityUIView::onButtonAltarAwd(cocos2d::CCObject *pSender)
	//点击祭坛进行献祭
{
	if (mLastIndex == -1)
	{
		return;
	}
    
	if (!isAltaring)
	{
		const vector<HeroAltar*> & AltarArray  = DataPool::GetSingleton()->getHeroAltarData()->getHeroAltar();
		HeroAltar *pAltar = AltarArray[mLastIndex];
		if(!pAltar) return;

		SelfBagData * pBgData = DataPool::GetSingleton()->getBagData();
		int stoneNum = pBgData->getItemNumByTableId(pAltar->getCostItem());
		int needNum = pAltar->getCostItemNum();

		ObjectSelf *pself = DataPool::GetSingleton()->getObjectManager()->getSelf();
		PlayerData *pData = pself->playerData();
		X_INT sacDamage = pData->GetSacrificeDamage(); //up limit 1500
		int DamageMax = pAltar->getLimit();

		if (stoneNum < needNum && sacDamage < DamageMax)
		{
			ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(576),this);
			dialog->setTag(DIALOG_TAG_ALT_CHARGE);
			addChild(dialog,10);

			return;
		}

		SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_PRAY,pAltar->getID());

		//effect
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		effect = EffectAnimation::createWith("xianji",23,5.0f,0.03f,true,false);
		effect->setPosition(ccp(winSize.width * 0.7f , winSize.height * 0.6f));
		addChild(effect);
		effect->playAnimation();

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND3);

		isAltaring = true;
	}

}

void cheeseActivityUIView::updateAltarTextData(HeroAltar *pAltar)
	//献祭的界面更新？
{

	if (mAltarContentNode)
	{
		mAltarContentNode->removeFromParentAndCleanup(true);
		mAltarContentNode = NULL;
	}

	if (isAltaring)
	{
 		effect->stopAnimation();
		effect = NULL;
		isAltaring = false;
	}
	
	mAltarContentNode = CCNode::create();
 
	mNodePosAltar->addChild(mAltarContentNode);


	ObjectSelf *pself = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData *pData = pself->playerData();
	X_INT sacDamage = pData->GetSacrificeDamage(); //up limit 1500
	//mProgressPos

	int DamageMax = pAltar->getLimit();
	ProgressView *progress = ProgressView::createProgress("n_xj_progress.png");
	float _value = ((float)sacDamage * 100)/(float)(DamageMax);
	progress->setProgressValue(_value,0,PROGRESS_ADD,false);
	progress->setAnchorPoint(ccp(0.5f, 05.f));
	progress->setTag(1);
	progress->setPositionY(mProgressPos->getContentSize().height*0.5f);
	 
	if (mProgressPos)
	{
		mProgressPos->removeAllChildrenWithCleanup(true);
	}
	
	mProgressPos->addChild(progress);

	char buff[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buff,"%d/%d",sacDamage,DamageMax);
	CCLabelBMFont *labelNum = CCLabelBMFont::create(buff,FNT_NAME_LARGEGREEN);
	labelNum->setAnchorPoint(ccp(0.5f,0.5f));
	labelNum->setTag(2);
	mProgressPos->addChild(labelNum);labelNum->setScale(SCALE_BMF);
	labelNum->setPosition( CCPoint(mProgressPos->getContentSize().width*0.5f,mProgressPos->getContentSize().height*0.5f));
	
	mUseStoneNum->setString(UtilTools::IntToString(pAltar->getCostItemNum()).c_str());

	SelfBagData * pBgData = DataPool::GetSingleton()->getBagData();
	int stoneNum = pBgData->getItemNumByTableId(pAltar->getCostItem());
	mCurStoneNum->setString(UtilTools::IntToString(stoneNum).c_str());

	X_INT itemId = -1;
	string name,color,icon;X_INT level;
	ObjectManager * pManger = DataPool::GetSingleton()->getObjectManager();
	for (X_INT i = 0 ;i< 4;i++)
	{
		itemId = pData->GetSacrificeAward(i);
		if (itemId <= 0)continue;

		if(pManger->getItemInfoById(itemId,name,color,icon,level))
		{
			mAltarEquip[i]->setString(name.c_str());
			ccColor3B _color;
			UtilTools::strToColor(color.c_str(),_color.r,_color.g,_color.b);
			mAltarEquip[i]->setColor(_color);
		}
	}

}

void cheeseActivityUIView::onButtonAltar(cocos2d::CCObject * pSender)
	//点击祭坛活动中下半部分的不同祭坛时
{
	CCMenuItemImage *pMenuItem = (CCMenuItemImage *)pSender;

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();
	int curIndex = (int)pObj - 1;

	if (curIndex == mLastIndex)
	{
		pMenuItem->selected();
		return;
	}
	
	pMenuItem->selected();

	if (mLastIndex != -1)
	{
		mHeroAltar[mLastIndex]->unselected();
	}
	mLastIndex = curIndex;
	

	for (int i = 0 ; i < 4; i++)
	{
		mAltarEquip[i]->setString(" ");
	}
	

	//info
	const vector<HeroAltar*> & AltarArray  = DataPool::GetSingleton()->getHeroAltarData()->getHeroAltar();
	HeroAltar *pAltar = AltarArray[curIndex];
	updateAltarTextData(pAltar);
    
    char buffFileName[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffFileName,"n_altar_big_%d.png",(curIndex+1));
	mAltarBigIcon->setNormalImage(CCSprite::create(buffFileName));
    mAltarBigIcon->setUserData(pAltar);

	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,pAltar->getID());

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

void cheeseActivityUIView::onButtonLeft(cocos2d::CCObject * pSender)
{
	mContent->scrollToPrePage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void cheeseActivityUIView::onButtonRight(cocos2d::CCObject * pSender)
{
	mContent->scrollToNextPage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	guideLayer = NULL;
}

/*creeps*/
void cheeseActivityUIView::onButtonCreep(cocos2d::CCObject * pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();

	int curIndex = (int)pObj - 1;

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	if (!pUi)return;

	map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(pUi->m_HuoDongIndex));
	if (ifind == mActivityItems.end())
	{
		return;
	}

	vector<HuoDong *> hds = ifind->second;
	HuoDong *hd = hds[curIndex];

	string strTip;

	if (hd->getState() == EM_C_STATE_DONE)
	{
		if( hd->getNum() >= MAX_ACT_NUM)
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}
		else
		{

		}
	}
	else if (hd->getState() == EM_STATE_HUODONG_RUN)
	{
		if( hd->getNum() < MAX_ACT_NUM)
		{
			ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
			PlayerData* pData = pSelf->playerData();

			if (hd->getCopySceneNeedAction() > pData->GetActionPoint())
			{

				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(571),this);
				dialog->setTag(DIALOG_TAG_CREEP_BEAR);
				addChild(dialog,10);

				return;
			}
			else
			{
				int actLvl = hd->getLevelNeed();

				if (pData->GetLevel()>= actLvl)
				{
					DataPool::GetSingleton()->BattlyType = EM_BATTLETYPE_FARM;
					cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
					if (pUi)
					{ 
						pUi->m_HuoDongIndex  =EM_FARM;
					}
					SendLogicPacket::EnjoyHuoDong(hd);
					return;
				}
				else
				{
					strTip = UtilTools::GET_TEXT_FROM_LANG(1);
				}
			}
		}
		else
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}

	}
	ModalDialogView *dialogView = ModalDialogView::createDialog(strTip,this,DIALOG_MODEL_SINGLE);
	addChild(dialogView,10);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}



void cheeseActivityUIView::onButtonFightShunt(cocos2d::CCObject * pSender)
{
	/*SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();

	int curIndex = (int)pObj - 1;

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	if (!pUi)return;

	vector<HuoDong *> hds = mActivityItems[pUi->m_HuoDongIndex];
	HuoDong *hd = hds[curIndex];
	
	string strTip;

	if (hd->getState() == EM_C_STATE_DONE)
	{
		if( hd->getNum() >= MAX_ACT_NUM)
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}
		else
		{

		}
	}
	else if (hd->getState() == EM_STATE_HUODONG_RUN)
	{
		if( hd->getNum() < MAX_ACT_NUM)
		{

			ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
			PlayerData* pData = pSelf->playerData();

			if (hd->getCopySceneNeedAction() > pData->GetActionPoint())
			{

				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(571),this);
				dialog->setTag(DIALOG_TAG_CREEP_BEAR);
				addChild(dialog,10);

				return;
			}
			else
			{
				int actLvl = hd->getLevelNeed();

				if (pData->GetLevel()>= actLvl)
				{
					DataPool::GetSingleton()->BattlyType = EM_BATTLETYPE_LINE;

					cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
					if (pUi)
					{ 
						pUi->m_HuoDongIndex  =EM_LINE;
					}
		 
					SendLogicPacket::EnjoyHuoDong(hd);
					return;
				}
				else
				{
					strTip = UtilTools::GET_TEXT_FROM_LANG(1);
				}
			}


		}
		else
		{
			strTip = UtilTools::GET_TEXT_FROM_LANG(548);
		}
	}

 

	ModalDialogView *dialogView = ModalDialogView::createDialog(strTip,this,DIALOG_MODEL_SINGLE);
	addChild(dialogView,1);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);*/
}

void cheeseActivityUIView::__onitemInfoCallBack(int index)
{
	guideLayer = NULL;

	DataPool::GetSingleton()->BattlyType  =EM_BATTLETYPE_INVALID;
	updateActivityData(index);
	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
	
	if (!pUi)return;

	 pUi->m_HuoDongIndex  = index;
	 if (index ==  EM_BLOODBATTLE   &&  pUi->m_layerXueZhan ==   EM_XUEZHAN_ENTER_LAYER_SHOW)
	 {
		 SendLogicPacket::StairEnterPacket();
	 }
}
void cheeseActivityUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	if (!pSender)
		return;
	EM_HUODONG_TYPE index = (EM_HUODONG_TYPE)(int)((CCNode *)pSender)->getUserData();
	__onitemInfoCallBack(index);
}

void cheeseActivityUIView::guideInfoCallBack1( cocos2d::CCObject* pSender )
{
	__onitemInfoCallBack(EM_ALTAR);
}
void cheeseActivityUIView::guideInfoCallBack2( cocos2d::CCObject* pSender )
{
	__onitemInfoCallBack(EM_ACTION);
}
void cheeseActivityUIView::guideInfoCallBack3( cocos2d::CCObject* pSender )
{
	__onitemInfoCallBack(EM_BLOODBATTLE);
}

void cheeseActivityUIView::updateActivityData(X_UINT actIndex)
{
	if (actIndex< 0 ||actIndex >= mNagItems.size())
	{
		 return;
	}
	X_INT type = mNagItems.at(actIndex);
	mYellowBackGround->setVisible(true);
	DisableAllLayer();

	switch (type)
	{
	case EM_EATCHEESE:
		{
			if (mActivityItems.empty())
			{
				return;
			}
			map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(type));
			if (ifind == mActivityItems.end())
			{
				return;
			}
			 
			vector<HuoDong *> hds = ifind->second;
			int num = hds.size();
			 
			mNodePosCheese->setVisible(true);
			mNodePosCheese->setPosition(mNodePos->getPosition());

			for (int i = 0;i < num; i ++)
			{
				mCheeseStateText[i]->setColor(ccWHITE);

				HuoDong *hd = hds[i];
				switch (hd->getState())
				{
				case EM_C_STATE_HUODONG_INVALID:
				case EM_C_STATE_HUODONG_DIABLE://未开启
					{
						mCheeseNode[i]->setVisible(true);
						mStaCheese[i]->setVisible(false);
						mMenuItems[i]->setUserData(NULL);

						CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("n_cheese_unk.png");
						mCheeseStateText[i]->setTexture(texture);

						if (mStaCheese[i]->getChildByTag(101))
						{
							mStaCheese[i]->removeChildByTag(101);
						}
						

						break;
					}
				case EM_C_STATE_HUODONG_RUN://进行中
					{
						mCheeseNode[i]->setVisible(false);
						mStaCheese[i]->setVisible(true);
						mMenuItems[i]->setUserData((void *)(i+1));

						CCSprite *onSprite = CCSprite::create("n_cheese_text2.png");
						onSprite->setPosition(ccp(mStaCheese[i]->getContentSize().width * 0.50f,  -mStaCheese[i]->getContentSize().height * 0.10f));
						mStaCheese[i]->addChild(onSprite);
						onSprite->setTag(101);


						break;
					}
					break;
				case EM_C_STATE_HUODONG_END://结束
					{
						mCheeseNode[i]->setVisible(true);
						mStaCheese[i]->setVisible(false);
						mMenuItems[i]->setUserData(NULL);

						CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("n_cheese_pass.png");
						mCheeseStateText[i]->setTexture(texture);

						if (mStaCheese[i]->getChildByTag(101))
						{
							mStaCheese[i]->removeChildByTag(101);
						}

						break;
					}
					
				case EM_C_STATE_DONE://已经完成
					{
						mCheeseNode[i]->setVisible(true);
						mStaCheese[i]->setVisible(false);
						if (mStaCheese[i]->getChildByTag(101))
						{
							mStaCheese[i]->removeChildByTag(101);
						}
						mMenuItems[i]->setUserData(NULL);

						CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("n_cheese_sel.png");
						mCheeseStateText[i]->setTexture(texture);

						mCheeseStateText[i]->setColor(ccGREEN);
						break;
					}
					
				default:
					break;
				}

			}

			break;
		}
	
	case EM_GANK:
		{
			mYellowBackGround->setVisible(false);
			if (mActivityItems.empty())
			{
				return;
			}

			map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(type));
			if (ifind == mActivityItems.end())
			{
				return;
			}
			vector<HuoDong *> hds = ifind->second;
			int num = hds.size();

			mNodePosTower->setVisible(true);
			mNodePosTower->setPosition(mNodePos->getPosition());

			for (int i = 0;i < num; i ++)
			{
				HuoDong *hd = hds[i];
				switch (hd->getState())
				{
				case EM_C_STATE_HUODONG_INVALID:
				case EM_C_STATE_HUODONG_END://结束
				case EM_C_STATE_HUODONG_DIABLE://未开启
					{


						mTowerBtn[i]->setVisible(false);
						mTowerText[i]->setVisible(false);
						mTowerTime[i]->setVisible(true);

						string bTime = hd->getTime();
						string eTime =  hd->getEndTime();

						string strResult = UtilTools::GET_TEXT_FROM_LANG(549);
						strResult += "\n";
						strResult +=bTime;
						strResult +="-";
						strResult +=eTime;
						mTowerTime[i]->setString(strResult.c_str());

						break;
					}
				case EM_C_STATE_DONE://已经完成
				case EM_C_STATE_HUODONG_RUN://进行中
					{

						mTowerBtn[i]->setVisible(true);
						mTowerText[i]->setVisible(true);
						mTowerTime[i]->setVisible(false);

						break;
					}

				}

 				mTowerBtn[i]->setUserData((void *)(i+1));
			
				
				string strNum;
				strNum = UtilTools::GET_TEXT_FROM_LANG(544);
				strNum += UtilTools::IntToString( hd->getNum());
				strNum += "/3";

				mGankNum[i]->setString(strNum.c_str());
			
			}

			break;
		}
		
	case EM_FARM:
		{
			mYellowBackGround->setVisible(false);
			if (mActivityItems.empty())
			{
				return;
			}
			map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(type));
			if (ifind == mActivityItems.end())
			{
				return;
			}

			vector<HuoDong *> hds = ifind->second;
			int num = hds.size();


			mNodePosCreep->setVisible(true);
			mNodePosCreep->setPosition(mNodePos->getPosition());

			//
			for (int i = 0;i < num; i ++)
			{
				HuoDong *hd = hds[i];
				switch (hd->getState())
				{
				case EM_C_STATE_HUODONG_INVALID:
				case EM_C_STATE_HUODONG_END://结束
				case EM_C_STATE_HUODONG_DIABLE://未开启
					{

						mCreepBtn[i]->setVisible(false);
						mCreepText[i]->setVisible(false);
						mCreepTime[i]->setVisible(true);

						string bTime = hd->getTime();
						string eTime =  hd->getEndTime();

						string strResult = UtilTools::GET_TEXT_FROM_LANG(549);
						strResult += "\n";
						strResult +=bTime;
						strResult +="-";
						strResult +=eTime;
						mCreepTime[i]->setString(strResult.c_str());

						break;
					}
				case EM_C_STATE_DONE://已经完成
				case EM_C_STATE_HUODONG_RUN://进行中
					{

						mCreepBtn[i]->setVisible(true);
						mCreepText[i]->setVisible(true);
						mCreepTime[i]->setVisible(false);


						break;
					}

				}

 				mCreepBtn[i]->setUserData((void *)(i+1));

				string strNum;
				strNum = UtilTools::GET_TEXT_FROM_LANG(544);
				strNum += UtilTools::IntToString( hd->getNum());
				strNum += "/3";

				mCreepLabelNum[i]->setString(strNum.c_str());

			}
			
			break;
		}
		
	/*case EM_LINE:
		{
			if (mActivityItems.empty())
			{
				return;
			}
			vector<HuoDong *> hds = mActivityItems[actIndex];
			int num = hds.size();


			mNodePosShunt->setVisible(true);
			mNodePosShunt->setPosition(mNodePos->getPosition());


			for (int i = 0;i < num; i ++)
			{
				HuoDong *hd = hds[i];
				switch (hd->getState())
				{
				case EM_C_STATE_HUODONG_INVALID:
				case EM_C_STATE_HUODONG_END://结束
				case EM_C_STATE_HUODONG_DIABLE://未开启
					{

						mShuntBtn[i]->setVisible(false);
						mRoadTextNode[i]->setVisible(false);
						mRoadTime[i]->setVisible(true);

						string bTime = hd->getTime();
						string eTime =  hd->getEndTime();

						string strResult = UtilTools::GET_TEXT_FROM_LANG(549);
						strResult += "\n";
						strResult +=bTime;
						strResult +="-";
						strResult +=eTime;
						mRoadTime[i]->setString(strResult.c_str());

						break;
					}
				case EM_C_STATE_DONE://已经完成
				case EM_C_STATE_HUODONG_RUN://进行中
					{
						mShuntBtn[i]->setVisible(true);
						mRoadTextNode[i]->setVisible(true);
						mRoadTime[i]->setVisible(false);

						break;
					}
				}

 				mShuntBtn[i]->setUserData((void *)(i+1));
		
				string strNum;
				strNum = UtilTools::GET_TEXT_FROM_LANG(544);
				strNum += UtilTools::IntToString( hd->getNum());
				strNum += "/3";

				mShuntLabelNum[i]->setString(strNum.c_str());

			}
			break;
		}*/

	case EM_ALTAR:
		{
			
			mNodePosAltar->setVisible(true);
			mNodePosAltar->setPosition(mNodePos->getPosition());

			initAltarData();

			break;
		}
	case EM_ACTION:
		{
			
			mNodePosBear->setVisible(true);
			mNodePosBear->setPosition(mNodePos->getPosition());
			updateBearTextData();

			break;
		}
	case EM_HUSONG_WOOD:
		{  
			
			mNodePosQuJing->setVisible(true);
			mNodePosQuJing->setPosition(mNodePos->getPosition());
			updateQujingTextData();
		}
		break;
	case EM_BLOODBATTLE:
		{  
			
			m_pBloodBattleUI->VisableLayer();
			m_pBloodBattleUI->updateXueZhanTextData();
		}
		break;
	case EM_SHAKE:
		{  
			if (mActivityItems.empty())
			{
				return;
			}
			map<EM_HUODONG_TYPE  ,vector<HuoDong *> >::iterator ifind = mActivityItems.find(EM_HUODONG_TYPE(type));
			if (ifind == mActivityItems.end())
			{
				return;
			}
			vector<HuoDong *> hds = ifind->second;
			int num = hds.size();
			for (int i = 0;i < num; i ++)
			{
				HuoDong *hd = hds[i];
				switch (hd->getState())
				{
				case EM_C_STATE_HUODONG_INVALID:
					{
						return;
					}
					break;
				case EM_C_STATE_HUODONG_DIABLE://未开启
				case EM_C_STATE_HUODONG_END://结束
				case EM_C_STATE_HUODONG_RUN://进行中
				case EM_C_STATE_DONE://已经完成
				break;
				}
			}
			updateShakeData();
		}
		break;
 
	default:
		break;
	}
}

void cheeseActivityUIView::onEnter()
{
	CCLayer::onEnter();

	schedule( schedule_selector(cheeseActivityUIView::updateFreshTime), 0.2f );
}

void cheeseActivityUIView::onExit()
{
	 HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	 if (pData)
	 {
		 pData->ShakeReady(XFALSE);
	 }
	unschedule( schedule_selector(cheeseActivityUIView::updateFreshTime) );

	BaseView::onExit();
}
void cheeseActivityUIView::updateFreshTime( float time )
{
	HuoDongData *pdata = DataPool::GetSingleton()->getHuoDongData();
	if (pdata->isShakeBegin())
	{
		  string timeStr   = UtilTools::ConvertMillisecondToTimeString( pdata->getShakeTime() );

		  if (timeStr.size() >= 6)
		  {
			  timeStr = timeStr.substr(3);
		  }
		  mShakeTime->setString(timeStr.c_str());
		 mShakeCount->setString(UtilTools::IntToString(pdata->getShakeNum()).c_str());
	}
}
void	cheeseActivityUIView::__updateShakeLayer()
{
	X_CHAR str[256] = {0};
	//ObjectManager* pM = DataPool::GetSingleton()->getObjectManager();
	//mShakeLastNum->setString(UtilTools::IntToString(pM->getSelf()->playerData()->GetRockLeftTimes()).c_str());

	HuoDongData *pdata = DataPool::GetSingleton()->getHuoDongData();
	string timeStr   = UtilTools::ConvertMillisecondToTimeString( pdata->getShakeTime() );
	if (timeStr.size() >= 6)
	{
		timeStr = timeStr.substr(3);
		mShakeTime->setString(timeStr.c_str());
	}
	mShakeCount->setString(UtilTools::IntToString(pdata->getShakeNum()).c_str());
}
void	cheeseActivityUIView::__updateGoddessLayer()
{
	ObjectManager* pM = DataPool::GetSingleton()->getObjectManager();
	Object *pObj = pM->CreateObject(OBJECT_TYPE_HERO,pM->getSelf()->playerData()->GetGoddessHeroGuid());
	ObjectHero* mCurHero = static_cast<ObjectHero*>(pObj);
    
    if(!mCurHero->IsDataReady())return;
	if( !mCurHero ) return;
	int qua = mCurHero->GetColor() - EM_HERO_COLOR_TYPE1;
	char* quastr[EM_HERO_COLOR_TYPE6 ] =
	{
		"hero_info_w.png",
		"hero_info_g.png",
		"hero_info_b.png",
		"hero_info_z.png",
		"hero_info_y.png",
		"hero_info_c.png",
	};

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(quastr[qua]);
	mHeroColor->setTexture(texture);

	//mHeroLevel->setString(UtilTools::IntToString(mCurHero->GetLevel()));

	//英雄形象以及英雄的等级
	CCSprite* mHeroImage = CCSprite::create( mCurHero->GetBody().c_str() );

	mHeroImage->setPosition(   CCPoint(mHeroImagePos->getPosition().x,mHeroImagePos->getPosition().y + mHeroImagePos->getContentSize().height*0.2f ));
	// mHeroImage->setScale(1.1f);
	mHeroImage->setZOrder(mHeroColor->getZOrder()-1);
	mGoddessInfo->addChild( mHeroImage, 10 );	


	mHeroDesc->setString(mCurHero->GetName().c_str());

	//HP......
	int curEquipHP = mCurHero->GetHP() - mCurHero->getEquipAddHP();
	char buffHP[MAX_STRING_BUFF_SIZE];
	sprintf(buffHP,"%d",curEquipHP);
	mHeroHp->setString(buffHP);

	//MP.....
	int curEquipMP = mCurHero->GetMP() - mCurHero->getEquipAddMP();
	char buffMP[MAX_STRING_BUFF_SIZE];
	sprintf(buffMP,"%d",curEquipMP);
	mHeroMp->setString(buffMP);

	//摇动次数
	CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0f, 2.0f),
                                              CCScaleTo::create(0.12f, 0.95f),
                                              CCScaleTo::create(0.08f, 1.03f),
                                              CCScaleTo::create(0.08f, 1.0f), NULL);
	mShakeStamp->runAction( popupLayer );
    
    CCLabelBMFont *mShakedTimesLabel ;
    if (!mShakeStamp->getChildByTag(1001)) {
        mShakedTimesLabel = CCLabelBMFont::create("123", FNT_NUM_LARGEWHITE);
        
        mShakedTimesLabel->setAnchorPoint(ccp(0.5f,0.5f));
        mShakedTimesLabel->setPosition( CCPoint(mShakeStamp->getContentSize().width*0.5f,mShakeStamp->getContentSize().height*0.5f));
        mShakeStamp->addChild(mShakedTimesLabel);
        mShakedTimesLabel->setTag(1001);
    }else{
        mShakedTimesLabel = (CCLabelBMFont*)mShakeStamp->getChildByTag(1001);
    }
	
	 
	mShakedTimesLabel->setString(UtilTools::IntToString(pM->getSelf()->playerData()->GetRockTimes()).c_str());
 

	//层级关系调整
	mHeroColor->setZOrder(mHeroImage->getZOrder()+1);

	mProcessBar1->setZOrder(mHeroColor->getZOrder()+1);
	mProcessBar2->setZOrder(mHeroColor->getZOrder()+1);
	mHeroHp->setZOrder(mHeroColor->getZOrder()+1);
	mHeroMp->setZOrder(mHeroColor->getZOrder()+1);
	mHeroDesc->setZOrder(mHeroColor->getZOrder()+1);

	ObjectSkill * pSkill ;
	for (X_INT i = 0; i < MAX_SKILL_NUM;i++)
	{
		pSkill =  mCurHero->GetSkill(i);
		if (!pSkill)
		{
			continue;
		}


		CCSprite *goddessSkillItem = CCSprite::create(pSkill->GetIcon());
		goddessSkillItem->setPosition(mGoddessSkillPos[i]->getPosition());
		goddessSkillItem->setUserData((void *)(pSkill));
		goddessSkillItem->setTag(10000+i);
		goddessSkillItem->setScale(0.80f);
		mGoddessInfo->addChild(goddessSkillItem);

		char buffSkill[MAX_STRING_BUFF_SIZE];
		sprintf(buffSkill,"%s",pSkill->GetName());
		mSkillText[i]->setString(buffSkill);

		sprintf(buffSkill,"%s",pSkill->GetDesc());
		mGoddessSkill[i]->setString(buffSkill);
	}
	HuoDongData* pdata = DataPool::GetSingleton()->getHuoDongData();
	if (pdata->canShake())
	{
		mShakeGoddess1->setEnabled(true);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("shake_jointeam.png");
		mGoddessJoin->setTexture(texture);
		mShakeGoddess2->setEnabled(true); 
	}
	else
	{
		mShakeGoddess1->setEnabled(false);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("shake_teaming.png");
		mGoddessJoin->setTexture(texture);
		mShakeGoddess2->setEnabled(false); 
	}

	//按钮动画

	char skillPlist[MAX_STRING_BUFF_SIZE];
	sprintf( skillPlist, "%s.plist", "shareBtnEffect" );

	char skillImage[MAX_STRING_BUFF_SIZE];
	sprintf( skillImage, "%s.png", "shareBtnEffect" );

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( skillPlist, skillImage );

	CCArray* animFrames = CCArray::createWithCapacity( MAX_ANIMATION_FRAMES );

	for( int i = 0; i < MAX_ANIMATION_FRAMES; i++ ) 
	{
		sprintf( skillPlist, "%s_%05d.png", "shareBtnEffect", i );
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( skillPlist );
		if( frame )
			animFrames->addObject( frame );
		else
			break;
	}


	CCSprite *shareEffect = CCSprite::create("shake_shareBtn.png");

	CCAnimate *animate= CCAnimate::create( CCAnimation::createWithSpriteFrames( animFrames, 0.1f ) );
	CCAction *action = CCRepeatForever::create(animate);
	shareEffect->runAction(action);	

	shareEffect->setPosition( mShakeShare->getPosition());
}
 
void cheeseActivityUIView::__updateWaitLayer()
{
	HuoDongData *pdata = DataPool::GetSingleton()->getHuoDongData();
	char str[256] = {0};
 
	X_INT time = 60;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_SHAKE_TIME_OVER);
		if (pTableData)
		{
			 time = pTableData->m_value;
		}	
	}

	sprintf(str,UtilTools::GET_TEXT_FROM_LANG(737),time,pdata->getShakeNum());
 
	mShakeMidLabel->setString(str);
}
void cheeseActivityUIView::updateShakeData()
{
	 mYellowBackGround->setVisible(true);
	 mNodePosShake->setPosition(mNodePos->getPosition());

	 HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();

	EM_SHAKE_LAYER layer = ( EM_SHAKE_LAYER) ((cheeseActivityUI*)(getUserData()))->m_layerShake;	

	if (pData->canShake() == XFALSE)
	{
		 ((cheeseActivityUI*)(getUserData()))->m_layerShake =    EM_SHAKE_GODDESS_LAYER_SHOW;
	}
	if (DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetGoddessHeroGuid()==INVALID_ID)
	{
		if (layer == EM_SHAKE_GODDESS_LAYER_SHOW )
		{
			((cheeseActivityUI*)(getUserData()))->m_layerShake =   EM_SHAKE_INTRODUCE_LAYER_SHOW;
		} 
	}
	layer = ( EM_SHAKE_LAYER) ((cheeseActivityUI*)(getUserData()))->m_layerShake;	
	 switch(layer)
	 {
 case 	EM_SHAKE_INTRODUCE_LAYER_SHOW:
	 {
		 mShakeIntroduce->setVisible(true);
		 mShakeSprite->setVisible(false);
		 mGoddessInfo->setVisible(false);
		 mShakePopu->setVisible(false);
	 }
		 break;
	 case 	EM_SHAKE_ENTER_LAYER_SHOW:
		 {
			pData->ShakeReady(XTRUE);
			mShakeSprite->setVisible(true);
			mGoddessInfo->setVisible(false);
			mShakeIntroduce->setVisible(false);
			mShakePopu->setVisible(false);
			CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("shake_GoddessShake.png"); 
			mShakeTitle->setTexture(texture);
			__updateShakeLayer();
		 }
		 break;
	case EM_SHAKE_WAITE_LAYER_SHOW:
		{
			mShakeSprite->setVisible(false);
			mShakeIntroduce->setVisible(false);
			mGoddessInfo->setVisible(false);
			mShakePopu->setVisible(true);
			__updateWaitLayer();
		}
		 break;
	 case 	EM_SHAKE_GODDESS_LAYER_SHOW:
		 {
			 pData->ShakeReady(XFALSE);
			 mShakeSprite->setVisible(false);
			 mShakeIntroduce->setVisible(false);
			 mShakePopu->setVisible(false);
			 mGoddessInfo->setVisible(true);
			 CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("shake_GoddessInfoText.png"); 
			 mShakeTitle->setTexture(texture);
			 __updateGoddessLayer();
		 }
		 break;
	 }
	 	mNodePosShake->setVisible(true);
}

void cheeseActivityUIView::updateQujingTextData()
{
	

	mYaYunTime1->setVisible(false);
	mYaYunTime2->setVisible(false);
	mYaYunTime3->setVisible(false);
	mHSaAllHeroTip->setString("");
	mHSNum->setString("");
	mLJTime->setString("");
	mHSNum->setString("");
	mHSTip->setString("");
	for (X_INT i =0;i< MAX_MATRIX_CELL_COUNT-1 ;i++ )
	{
			mHero[i]->setVisible(false);
			if (mHeroIcon[i])
			{
				mNodePosQuJing->removeChild(mHeroIcon[i]);
			}
			
	}
	mYaYunBtn->setVisible(false);
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}

	/*bool canQujing = pData->IsCanQujing();
	if (!canQujing)
	{
		mHSaAllHeroTip->setString(UtilTools::GET_TEXT_FROM_LANG(684));
		return;
	}*/

	mYaYunTime1->setVisible(true);
	mYaYunTime2->setVisible(true);
	mYaYunTime3->setVisible(true);

	const  DataBase* pDataFileQujing  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_QUJING);
	const stDBC_FILE_QUJING	* m_pTableDataQujing =(const stDBC_FILE_QUJING*)pDataFileQujing->GetFieldsByIndexKey(1);
	string times ="";
	if (m_pTableDataQujing)
	{
		string str1 = m_pTableDataQujing->time1;
		string str2 = m_pTableDataQujing->time2;
		string str3 = m_pTableDataQujing->time3;

		vector<X_INT>  vec;
		vec.clear();

		if (str1 !="-1")
		{
			UtilTools::ConvertStringToIntVector(str1.c_str(),vec,"|");
			if (vec.size() >=2)
			{
				times = UtilTools::getDateHourMinstr(vec[0]);
				times+="-";
				times +=UtilTools::getDateHourMinstr(vec[1]);
			}
		}

		if (str2 !="-1")
		{
			vec.clear();
			UtilTools::ConvertStringToIntVector(str2.c_str(),vec,"|");
			if (vec.size() >=2)
			{   times+=",";
			times += UtilTools::getDateHourMinstr(vec[0]);
			times+="-";
			times +=UtilTools::getDateHourMinstr(vec[1]);
			}
		}

		if (str3 !="-1")
		{
			vec.clear();
			UtilTools::ConvertStringToIntVector(str3.c_str(),vec,"|");
			if (vec.size() >=2)
			{   times+=",";
			times += UtilTools::getDateHourMinstr(vec[0]);
			times+="-";
			times +=UtilTools::getDateHourMinstr(vec[1]);
			}
		}
	}

	if (times.size() > 0)
	{
		X_CHAR temp[256] = {0};
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(689),times.c_str());
		mYaYunTime1->setString(temp);
	}
	 

	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(653),pData->GetRobTimes());
	mLJTime->setString(temp);
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(663),pData->GetHuSongTimes());
	mHSNum->setString(temp);

 

	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	const X_INT*	tablid = pData->GetHeroTableID();
  
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
	if (!pDataFile)
	{
		return;
	}
	const stDBC_FILE_HERO_ATTR	* m_pTableData =X_NULL;
	const ObjectHero *pHero = X_NULL;

	for (X_INT i =0;i< MAX_MATRIX_CELL_COUNT-1 ;i++ )
	{
		mHero[i]->setVisible(true);
		pHero = pSelf->getHeroWithTableid( tablid[i]);
		if (pHero)
		{
			CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage( GameHelper::GetHeroColorById(pHero->GetColor()).c_str());
			mHero[i]->setTexture(texture);
			mHeroIcon[i] = CCSprite::create(pHero->GetHeadIcon().c_str());

		}else
		{
			CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("n_pos_white.png");
			mHero[i]->setTexture(texture);
			m_pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByIndexKey( tablid[i] );
			if (m_pTableData)
			{
				string str  = "zhf_";
				str += m_pTableData->_icon;
				mHeroIcon[i] = CCSprite::create(str.c_str());
			} 
		}

		if (mHeroIcon[i])
		{
			mNodePosQuJing->addChild(mHeroIcon[i]);
			mHeroIcon[i]->setPosition(mHero[i]->getPosition());
			mHeroIcon[i]->setScale(0.605f);
			mHeroIcon[i]->setAnchorPoint(CCPoint(0.5f,0.5f));
		}
	}
	bool b = pData->isQuJingHeroGet();
	if(b)
	{
		mHSTip->setString(UtilTools::GET_TEXT_FROM_LANG(665));
		mHSTip->setColor(ccGREEN);
		mYaYunBtn->setEnabled(true);
		pData->autoHeroMatrix();
	}else
	{
		mHSTip->setString(UtilTools::GET_TEXT_FROM_LANG(664));
		mHSTip->setColor(CCCOLOR_YELLOW);
		mYaYunBtn->setEnabled(false);
	}
 	mYaYunBtn->setVisible(true);
}
void cheeseActivityUIView::updateBearTextData()
{
	//todo bear
  
	ObjectManager *pManager = DataPool::GetSingleton()->getObjectManager();
	PlayerData* pData =   pManager->getSelf()->playerData();
	X_INT num = pData->GetBuyBearPointCount();//购买次数


	X_INT canBuyNum =0;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_BEARPOINT_BUYNUM);
		if (pTableData)
		{
			canBuyNum = pTableData->m_value;
		}	
	}

	char buff[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buff,"%d/%d",num,canBuyNum);
	mBearNum->setString(buff);

	X_INT  level,bearpoint;X_UINT cost;
	
	//1--------3
	for (X_INT i = 1;i<=3;i++)
	{
		bool bok = GameHelper::getBuyBearPointCost(i,cost,level,bearpoint);
		if (bok)
		{
			string str = "";
			X_CHAR info[256] = {0};
			sprintf(info,UtilTools::GET_TEXT_FROM_LANG(651),bearpoint);
			mBearCost[i-1]->setString(UtilTools::IntToString(cost).c_str());
			mBearInfo[i-1]->setString(info);
		}else
		{
			mBearCost[i-1]->setString("");
			mBearInfo[i-1]->setString("");
		}
	}
	mBearValue->setString(UtilTools::IntToString(pData->GetBearPoint()).c_str());

	if (isAltaring)
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		X_INT id = (X_INT)(effect->getUserData());
		bearpoint = 0;
		bool bok = GameHelper::getBuyBearPointCost(id,cost,level,bearpoint);
		if (bok)
		{
			bearpoint *= -1;
		}

		FightTips *tip = FightTips::createWith(FightTips::TIPS_MAGIC_NUM,bearpoint);
		tip->setPosition(ccp(winSize.width * 0.33f , winSize.height * 0.6f));
		addChild(tip);
		

		effect->stopAnimation();
		effect = NULL;
		isAltaring = false;
	}
	
}

void cheeseActivityUIView::createNavItem()
{
	mNagItems.clear();
	for (int i = EM_INVALID_HUODONG_TYPE +1 ; i < EM_HOUDONG_TYPE_NUM; i++)
	{
		if (i == EM_SHAKE)
		{
			HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
			if (pData->getShakeHuoDongEnable())
			{
				mNagItems.push_back(i);
			}

		}else
		{
			mNagItems.push_back(i);
		}
	}
	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	mContentNode = CCNode::create();
	addChild( mContentNode );

	unsigned int size = mNagItems.size();

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y);
	mContent = CCScrollViewPage::create();
	mContent->createContainer(this,totalPage,viewSize); 

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentOffset(CCPointZero);
	mContent->setDirection( kCCScrollViewDirectionHorizontal );
	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContentNode->addChild( mContent );


}


void cheeseActivityUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		//clear();

		return;
	}
	createNavItem();

	cheeseActivityUI *pUi =  (cheeseActivityUI*) (getUserData());
    if (!pUi)return;
 
	 
	mActivityItems.clear();
	HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	vector<HuoDong*> hds = pData->getHuoDong();
	HuoDong* hd;
	pData->ShakeReady(XFALSE);
	vector<HuoDong *> subHDCheese,subHDShunt,subHDCreep,subHDAltar,subHDTower,subHDShake;
	subHDCheese.clear();
	subHDShunt.clear();
	subHDCreep.clear();
	subHDAltar.clear();
	subHDTower.clear();
	subHDShake.clear();

	for (unsigned int i = 0 ;i < hds.size();i ++)
	{
		hd = hds[i];
		if (!hd)
		{
			continue;
		}
		switch (hd->GetType())
		{
		case EM_EATCHEESE:
			subHDCheese.push_back(hd);
			break;
		case EM_GANK:
			subHDTower.push_back(hd);
			break;
		case EM_FARM:
			subHDCreep.push_back(hd);
			break;
		//case EM_LINE:
		//	subHDShunt.push_back(hd);
		//	break;
 		case  EM_SHAKE:
 			subHDShake.push_back(hd);
 			break;
		default:
			break;
		}
	}

	if (subHDCheese.size() > 0)
	{
		mActivityItems[EM_EATCHEESE] = (subHDCheese);
		
	}
	if (subHDTower.size() > 0)
	{
		mActivityItems[EM_GANK] = (subHDTower);
		
	}
	if (subHDCreep.size() > 0)
	{
		mActivityItems[EM_FARM] = (subHDCreep);
		
	}
	/*if (subHDShunt.size() > 0)
	{
		mActivityItems[EM_LINE] = (subHDShunt)
	}*/
 	if (subHDShake.size() > 0)
 	{
 		mActivityItems[EM_SHAKE] = (subHDShake);
 	}
	 
	updateActivityData(pUi->m_HuoDongIndex);

	if (pUi->m_HuoDongIndex >EM_ALTAR)
	{
		mContent->scrollToPage(1);
	}
	 
	X_INT tipId = ((cheeseActivityUI *)this->getUserData())->getTipId();

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;
	if (tipId != -1)
	{
		if (!guideLayer)
		{
			switch (tipId)
			{
			case 30:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(cheeseActivityUIView::guideInfoCallBack1),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 31:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(cheeseActivityUIView::onButtonRight),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 32:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(cheeseActivityUIView::guideInfoCallBack2),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 33:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(cheeseActivityUIView::guideInfoCallBack3),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 34:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(cheeseActivityUIView::onButtonXueZhan),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				break;
			}
		}
	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
}

// void cheeseActivityUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
// {
// 	pSender->closeDialogView();
// }


void cheeseActivityUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void cheeseActivityUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

bool cheeseActivityUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{

	 
	int size = mNagItems.size();

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	int lineIndex = 0;
	int columnIndex = 0;

	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		X_INT type = mNagItems[i];
		string titleIcon;
		getActivityTitleInfo((EM_HUODONG_TYPE)type,titleIcon);
		CCMenuItemImage *menuItem = CCMenuItemImage::create( titleIcon.c_str(),titleIcon.c_str(), this, menu_selector(cheeseActivityUIView::itemInfoCallBack) );  
		// 		CCPoint itemPos = CCPointMake( winSize.width * ( ITEM_START_X + pageIndex * ITEM_SPACE_DELTA_X * ITEM_COLUMN_NUM + ITEM_SPACE_DELTA_X * columnIndex), winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ) );
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 
		menuItem->setScale(0.80f);
		menuItem->setUserData( (void *)(type));

		menu->addChild( menuItem );

		columnIndex ++;
		if( columnIndex >= ITEM_COLUMN_NUM )
		{
			columnIndex = 0;
			lineIndex ++;

			if( lineIndex >= ITEM_LINE_NUM )
			{
				lineIndex = 0;
			}
		}
	}

	menu->setPosition( CCPointZero );
	pPage->addChild(menu);
	

	return true;
}

void cheeseActivityUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void cheeseActivityUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	
}

void cheeseActivityUIView::getActivityTitleInfo(EM_HUODONG_TYPE _type, string &_icon)
	//各项活动的题头
{
	switch (_type)
	{
	case EM_EATCHEESE:
		_icon = "n_cheese_icon.png";
		break;
	case EM_GANK:
		_icon = "n_tower_icon.png";
		break;
	case EM_FARM:
		_icon = "n_creep_icon.png";
		break;
	//case EM_LINE:
	//	_icon = "n_line_icon.png";
	//	break;
	case EM_ALTAR:
		_icon = "n_xj_icon.png";
		break;
	case EM_ACTION:
		_icon = "n_bear_icon.png";
		break;
	case EM_HUSONG_WOOD:
		_icon = "n_qujing_icon.png";
		break;
	case EM_BLOODBATTLE:
		_icon = "n_xuezhan_icon.png";
		break;
	case EM_SHAKE:
		_icon = "n_shake_icon.png";
		break;
		
	default:
		break;
	}
}


void cheeseActivityUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	int iTag = pSender->getTag();

	switch (iTag)
	{
	case DIALOG_TAG_CREEP_BEAR:
		{
			EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_USER_INFO_SHOW);
			break;
		}
 	case DIALOG_TAG_ALT_CHARGE:
 		{
            
            EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_SECRETSTORE_SHOW);
 			break;
 		}
	case DIALOG_TAG_COST_GOLD:
		{	
			void*  data = pSender->getDailogUserData();
			if (!data)
			{
				return;
			}
			int id = int(data);
			//购买发送
			SendLogicPacket::BuyBearPoint(id);
			ShowAltaringEffect(id);
			break;
		}
	case DIALOG_TAG_NO_GOLD:
		{
			EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
			break;
		}
	case DIALOG_TAG_RESHAKE_GODDESS:
		{
			((cheeseActivityUI*)(getUserData()))->m_layerShake =   EM_SHAKE_INTRODUCE_LAYER_SHOW;
			//SdkHandler::shakeBegin();
			HuoDongData * pData = DataPool::GetSingleton()->getHuoDongData();
			pData->resetShakeTime();
			pData->setShakeNum(0);
			updateShakeData();
			break;
		}
	default:
		break;
	}

	pSender->closeDialogView();
}

void cheeseActivityUIView::DisableAllLayer()
{
	mNodePosCheese->setVisible(false);
	mNodePosTower->setVisible(false);
	mNodePosCreep->setVisible(false);
	mNodePosShunt->setVisible(false);
	mNodePosAltar->setVisible(false);
	mNodePosBear->setVisible(false);
	mNodePosQuJing->setVisible(false);
	m_pBloodBattleUI->DisableAllLayer();
	mNodePosShake->setVisible(false);
}
 
BloodBattleUIView::BloodBattleUIView( cheeseActivityUIView* pUIView )
	: m_pBaseUIView(pUIView)
	, mNodePosXueZhan(NULL)
	, m_NodeReward(NULL)
{

 
	 mXueZhanNum = NULL;
	 mXueZhanEnterTip1 = NULL;
	 mXueZhanEnterTip2 = NULL;
	 mXueZhanBtn = NULL;


	 //-----------------------------
	 mNodePosXueZhanBuffer = NULL;
	  mXueZhanJiFen = NULL;
	 
	 mXueZhanBufferRecord = NULL;

	 for (X_INT i=0;i<3;i++)
	 {
		 mXueZhanCost[i] = NULL;
		 mXueZhanTip[i] = NULL;
		 mButtonBattleSelect[i] = NULL;
	 }
	 mXueZhanBufferAddTip = NULL;
	// ----------------------------------
	 mNodePosXueZhanBattle = NULL;
	 mXueZhanBattleJiFen = NULL;
	 mXueZhanBattleAddTip = NULL;
     mXueZhanBattleRecord = NULL;
 
	 for (X_INT i=0;i<3;i++)
	 {
		 mBattleEye[i] = NULL;
		 mBattleAward[i] = NULL;
		 mBattleJifen[i] = NULL;
	 }
	  for (X_INT i=0;i<18;i++)
	  {
		  mbattleMonster[i] = NULL;
	  }

 


}

BloodBattleUIView::~BloodBattleUIView()
{
	CC_SAFE_RELEASE(mNodePosXueZhan);
	CC_SAFE_RELEASE(mXueZhanNum);
	CC_SAFE_RELEASE(mXueZhanEnterTip1);
	CC_SAFE_RELEASE(mXueZhanEnterTip2);
	CC_SAFE_RELEASE(mXueZhanBtn);
	

	CC_SAFE_RELEASE(mNodePosXueZhanBuffer);
	CC_SAFE_RELEASE(mXueZhanJiFen);
	 
	CC_SAFE_RELEASE(mXueZhanBufferRecord);
	for (X_INT i=0;i<3;i++)
	{
		CC_SAFE_RELEASE(mXueZhanCost[i]);
		CC_SAFE_RELEASE(mXueZhanTip[i]);
		CC_SAFE_RELEASE(mButtonBattleSelect[i]);
	}

	CC_SAFE_RELEASE(mXueZhanBufferAddTip);
	//--------------------

	CC_SAFE_RELEASE(mNodePosXueZhanBattle);
	CC_SAFE_RELEASE(mXueZhanBattleJiFen);
	CC_SAFE_RELEASE(mXueZhanBattleAddTip);
	CC_SAFE_RELEASE(mXueZhanBattleRecord);

	for (X_INT i=0;i<3;i++)
	{
		CC_SAFE_RELEASE(mBattleEye[i]);
		CC_SAFE_RELEASE(mBattleAward[i]);
		CC_SAFE_RELEASE(mBattleJifen[i]);
	}
	for (X_INT i=0;i<18;i++)
	{
		CC_SAFE_RELEASE(mbattleMonster[i]);
	}
}

bool BloodBattleUIView::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{

	//----------------------------------------------------------------------------------------------
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mNodePosXueZhan",	CCNode *,mNodePosXueZhan);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanEnterTip1",  CCLabelTTF *,mXueZhanEnterTip1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanEnterTip2",  CCLabelTTF *,mXueZhanEnterTip2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanNum",  CCLabelTTF *,mXueZhanNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBtn",  CCMenuItemImage *,mXueZhanBtn);

	//----------------------------------------------------------------------------------------------------
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mNodePosXueZhanBuffer",	CCNode *,mNodePosXueZhanBuffer);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanJiFen",  CCLabelTTF *,mXueZhanJiFen);
	 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBufferRecord",  CCLabelTTF *,mXueZhanBufferRecord);

 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanCost1",  CCLabelTTF *,mXueZhanCost[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanCost2",  CCLabelTTF *,mXueZhanCost[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanCost3",  CCLabelTTF *,mXueZhanCost[2]);
 

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanTip1",  CCLabelTTF *,mXueZhanTip[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanTip2",  CCLabelTTF *,mXueZhanTip[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanTip3",  CCLabelTTF *,mXueZhanTip[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBufferAddTip",  CCLabelTTF *,mXueZhanBufferAddTip);

	 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mButtonAttack",  CCMenuItemImage *,mButtonBattleSelect[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mButtonDefence",  CCMenuItemImage *,mButtonBattleSelect[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mButtonBlood",  CCMenuItemImage *,mButtonBattleSelect[2]);
	
	
	//-------------------------------------------------------------------------------------------
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mNodePosXueZhanBattle",	CCNode *,mNodePosXueZhanBattle);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBattleJiFen",  CCLabelTTF *,mXueZhanBattleJiFen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBattleAddTip",  CCLabelTTF *,mXueZhanBattleAddTip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mXueZhanBattleRecord",  CCLabelTTF *,mXueZhanBattleRecord);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleEye1",  CCMenuItemImage *,mBattleEye[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleEye2",  CCMenuItemImage *,mBattleEye[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleEye3",  CCMenuItemImage *,mBattleEye[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleAward1",  CCSprite *,mBattleAward[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleAward2",  CCSprite *,mBattleAward[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleAward3",  CCSprite *,mBattleAward[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleJifen1",  CCSprite *,mBattleJifen[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleJifen2",  CCSprite *,mBattleJifen[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, "mBattleJifen3",  CCSprite *,mBattleJifen[2]);

	for(X_INT i =0 ;i<3;i++)
	{
		string strADD = UtilTools::IntToString(i+1);
		
		for(X_INT j =0 ;j<6;j++)
		{
			string str = "mbattleMonster" + strADD;
			str += UtilTools::IntToString(j+1);

			CCB_MEMBERVARIABLEASSIGNER_GLUE(m_pBaseUIView, str.c_str(),  CCSprite *,mbattleMonster[i*6 + j]);
		}
 
	}
	//-----------------------------------------------------------------------------------------------
  

	return false;
}

void BloodBattleUIView::DisableAllLayer()
{
	mNodePosXueZhan->setVisible(false);
	mNodePosXueZhanBuffer->setVisible(false);
	mNodePosXueZhanBattle->setVisible(false);
}
void BloodBattleUIView::VisableLayer( )
{
	DisableAllLayer();
	CCPoint Pos = m_pBaseUIView->mNodePos->getPosition();
	CCNode*  LayoutLayer = NULL;

	switch (((cheeseActivityUI*)(m_pBaseUIView->getUserData()))->m_layerXueZhan)
	{
	case  EM_XUEZHAN_ENTER_LAYER_SHOW:
		{
			LayoutLayer = mNodePosXueZhan;
		}
		break;
	case  EM_XUEZHAN_BUFFER_LAYER_SHOW:
		{
			LayoutLayer = mNodePosXueZhanBuffer;
		}
		break;
	 case   EM_XUEZHAN_BATTLE_LAYER_SHOW:
		 {
			 LayoutLayer = mNodePosXueZhanBattle;
		 }
		 break;
	}
	if (!LayoutLayer)
	{
		return;
	}
	LayoutLayer->setVisible(true);
	LayoutLayer->setPosition(Pos);
}

void BloodBattleUIView::onButtonChallenge( cocos2d::CCObject * pSender )
{

}

void BloodBattleUIView::onButtonSelect( cocos2d::CCObject * pSender )
{

}
void BloodBattleUIView::updateXueZhanTextData()
{
	 
	  EM_XUEZHAN_LAYER layer = ( EM_XUEZHAN_LAYER) ((cheeseActivityUI*)(m_pBaseUIView->getUserData()))->m_layerXueZhan ;

	 switch (layer)
	 {
	 case   EM_XUEZHAN_ENTER_LAYER_SHOW:
		 _updateEnterUI(); 
		 break;
	 case  EM_XUEZHAN_BUFFER_LAYER_SHOW:
		 _updateBufferUI();
		 break;
	 case  EM_XUEZHAN_BATTLE_LAYER_SHOW:
		 _updateBattleUI();
		 break;
	 }

}
X_VOID BloodBattleUIView::_updateEnterUI()
{
	mXueZhanNum->setString(""); 
	mXueZhanEnterTip1->setString("");
	mXueZhanEnterTip2->setString("");

	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData)
	{
		return;
	}
	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(673),pData->GetTimes(),pData->GetLeftTimes());
	mXueZhanNum->setString(temp);

	memset(temp,0,sizeof(temp));
	X_INT layer = pData->GetLayer();
	if (layer>=1)
	{
		layer -=1;
	}
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(674),layer);
	mXueZhanEnterTip1->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(675),pData->GetMaxPassLayers(),pData->GetMaxTotalStar());
 	mXueZhanEnterTip2->setString(temp);
}
X_VOID BloodBattleUIView::_updateBufferUI()
{
	mXueZhanJiFen->setString("");
    mXueZhanJiFen->setColor(CCCOLOR_RED);
	mXueZhanBufferRecord->setString("");
    mXueZhanBufferRecord->setColor(CCCOLOR_RED);
	mXueZhanBufferAddTip->setString("");
    mXueZhanBufferAddTip->setColor(CCCOLOR_RED);
	for (X_INT i = 0;i<3;i++)
	{
		mXueZhanCost[i]->setString(""); 
		mXueZhanTip[i]->setString(""); 
	}
	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData)
	{
		return;
	}
	X_BOOL begin = pData->isBegin();
	 
	X_INT *cost =	pData->getCostStar();//0-2 攻防血
	X_INT *plus =	pData->getBufferPlus(); 

	BattleLayer * pLayerMonster =  pData->getLayerMonster();
	if (!pLayerMonster)
	{
		return;
	}
	X_CHAR temp[256] = {0};
	bool alldisble = true;
	for (X_INT i = 0;i<STAIR_PLUS_COUNT;i++)
	{
		if (!begin)
		{
			memset(temp,0,sizeof(temp));
			sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(676),cost[i]);
			mXueZhanTip[i]->setString(temp); 
		}

		memset(temp,0,sizeof(temp));
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(677),plus[i]);
		mXueZhanCost[i]->setString(temp); 


		if (cost[i] <= pLayerMonster->m_CurStar )
		{
			mButtonBattleSelect[i]->setEnabled(true);
			alldisble = false;
		}else
		{
			mButtonBattleSelect[i]->setEnabled(false);
		} 
	}

	if (alldisble)
	{
		for (X_INT i = 0;i<STAIR_PLUS_COUNT;i++)
		{
			mButtonBattleSelect[i]->setEnabled(true);
		}
		
	}
	if (!begin)
	{
		//memset(temp,0,sizeof(temp));
		//sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(679),pLayerMonster->m_PlusAtt, pLayerMonster->m_PlusDef, pLayerMonster->m_PlusHp);
		//mXueZhanBufferAddTip->setString(temp); 

		memset(temp,0,sizeof(temp));
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(683),pLayerMonster->m_Layer, pLayerMonster->m_AccStar, pLayerMonster->m_CurStar);
		mXueZhanJiFen->setString(temp); 

		memset(temp,0,sizeof(temp));
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(681),pLayerMonster->m_MaxPassLayers, pLayerMonster->m_MaxTotalStar);
		mXueZhanBufferRecord->setString(temp); 
	}
}

X_VOID BloodBattleUIView::_updateBattleUI()
{
    mXueZhanBattleJiFen->setString("");
    mXueZhanBattleJiFen->setColor(CCCOLOR_RED);
    mXueZhanBattleAddTip->setString("");
    mXueZhanBattleAddTip->setColor(CCCOLOR_RED);
    mXueZhanBattleRecord->setString("");
    mXueZhanBattleRecord->setColor(CCCOLOR_RED);
 
	 BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	 if (!pData)
	 {
		 return;
	 }
	BattleLayer * pLayerMonster =  pData->getLayerMonster();
	if (!pLayerMonster)
	{
		return;
	}

	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(678),pLayerMonster->m_Layer, pLayerMonster->m_AccStar, pLayerMonster->m_CurStar,pLayerMonster->m_NextPlusLayers);
	mXueZhanBattleJiFen->setString(temp); 

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(679),pLayerMonster->m_PlusAtt, pLayerMonster->m_PlusDef, pLayerMonster->m_PlusHp);
	mXueZhanBattleAddTip->setString(temp); 
	
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(681),pLayerMonster->m_MaxPassLayers, pLayerMonster->m_MaxTotalStar);
	mXueZhanBattleRecord->setString(temp); 
	 
	StairMonster* pMonster = pLayerMonster->m_MonsterGroup;

	for (X_INT i = 0;i< MAX_STAIR_MONSER_GROUP;i++)
	{
		StairMonster  Monster = pMonster[i];

		if (mBattleAward[i]->getChildrenCount() >0)
		{
			mBattleAward[i]->removeAllChildrenWithCleanup(true);
		}
		
		if (Monster.m_ItemID == -1 )
		{
			CCTexture2D *tx = CCTextureCache::sharedTextureCache()->addImage("n_xuezhan_jifen.png");
			mBattleAward[i]->setTexture(tx);
			string str = "n_xuezhan_1.png";
			if (Monster.m_StarParam ==1)
			{
				str = "n_xuezhan_1.png";
			}else if (Monster.m_StarParam ==2)
			{
				str = "n_xuezhan_2.png";
			}else if (Monster.m_StarParam ==3)
			{
				str = "n_xuezhan_3.png";
			}
			tx = CCTextureCache::sharedTextureCache()->addImage(str.c_str());
			mBattleJifen[i]->setTexture(tx);
			mBattleJifen[i]->setVisible(true);
		}
		else
		{
			X_INT itemId = Monster.m_ItemID;
			string name,color,icon;X_INT level;
			DataPool::GetSingleton()->getObjectManager()->getItemInfoById(itemId,name,color,icon,level);
			//CCTexture2D *tx = CCTextureCache::sharedTextureCache()->addImage(icon.c_str());
			//mBattleAward[i]->setTexture(tx);
			CCSprite *item = CCSprite::create(icon.c_str());item->setScale(0.82f);
			CCSprite *equipBG =CCSprite::create("equipmentBK.png" );item->setPosition(CCPoint(equipBG->getContentSize().width*0.5f,equipBG->getContentSize().height*0.5f));
			equipBG->addChild(item);
		    mBattleAward[i]->addChild(equipBG);equipBG->setPosition(CCPoint(mBattleAward[i]->getContentSize().width*0.5f,mBattleAward[i]->getContentSize().height*0.5f));
			CCSprite *pLevel = GameHelper::getSpriteLevel(level); 
			if (pLevel)
			{
				//mBattleAward[i]->addChild(pLevel);
				item->addChild(pLevel);
				pLevel->setZOrder(100);
				pLevel->setPosition( CCPoint(item->getContentSize().width*0.5f,item->getContentSize().height*0.5f)); 
			} 
			mBattleJifen[i]->setVisible(false);
		}
		bool bHide = false;
		for (X_INT j = 0;j  < MAX_MATRIX_CELL_COUNT;j++)
		{
			CCSprite* monsteSprite =  mbattleMonster[i*MAX_MATRIX_CELL_COUNT +j ];
			if (monsteSprite->getChildrenCount() > 0)
			{
				monsteSprite->removeAllChildrenWithCleanup(true);
			}
			bool hide = Monster.m_bHide[j] == XTRUE;
		    string monsteIcon = "n_xuezhan_x.png";
		
			X_FLOAT scale =0.4f;
			if (!hide)
			{
				
				X_INT monsterId = Monster.m_MonsterID[j];
				if (monsterId<=0)
				{
					continue;
				}else
				{
					const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_FIGHTMONSTER);
					const stDBC_FILE_FIGHTMONSTER	* m_pTableData = (const stDBC_FILE_FIGHTMONSTER*)pDataFile->GetFieldsByIndexKey(monsterId);
					if (!m_pTableData)
					{
						continue;
					}
			 
					string str1  = "zhf_";
					str1 += m_pTableData->_icon;;
					monsteIcon =  str1.substr(0,str1.length() - 3) +"png";
 
				}
			}
			else
			{
				bHide = true;
				monsteIcon = "n_xuezhan_x.png";
				scale = 1.0f;
			}
			 CCSprite *head = CCSprite::create(monsteIcon.c_str());
			 monsteSprite->addChild(head);
			 head->setScale(scale);	
			 head->setPosition(CCPoint(monsteSprite->getContentSize().width*0.5f,monsteSprite->getContentSize().height*0.5f));
		}

		if (bHide)
		{
			mBattleEye[i]->setEnabled(true);
		}else
		{
			mBattleEye[i]->setEnabled(false);
		}
 
	}
 
}
 
void BloodBattleUIView::onButtonXueZhan()
{
	// ((cheeseActivityUI*)(m_pBaseUIView->getUserData()))->m_layer = cheeseActivityUI::EM_XUEZHAN_BUFFER_LAYER_SHOW;
	//VisableLayer();

 
	SendLogicPacket::StairStartPacket();
}
void  BloodBattleUIView::onButtonBlood()
{
	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData)
	{
		return;
	}
  
	SendLogicPacket::StairAddBufferPacket(2);
	pData->HanlderBufferSelect();
}
void  BloodBattleUIView::onButtonAttack()
{
	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData)
	{
		return;
	}
	SendLogicPacket::StairAddBufferPacket(0);
	pData->HanlderBufferSelect();
}
void  BloodBattleUIView::onButtonDefence()
{
	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData)
	{
		return;
	}
	SendLogicPacket::StairAddBufferPacket(1);
	pData->HanlderBufferSelect();
}
void  BloodBattleUIView::onButtonBattle(X_INT index)
{

	BloodData *pData = DataPool::GetSingleton()->GetBloodData();
	if (!pData||!pData->isBattleNextOk())
	{
		return;
	}

	DataPool::GetSingleton()->BattlyType = EM_BATTLETYPE_BLOODBATTLE;
	if(SendLogicPacket::StairMonsterPacket(index))
	{
		pData->setBattleNextOk(false);
	}
}
void  BloodBattleUIView::onBattleEye(X_INT index)
{
	
	SendLogicPacket::StairShowMonsterPacket(index);
}
 
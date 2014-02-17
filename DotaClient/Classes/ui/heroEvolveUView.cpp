#include "./ui/heroEvolveUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/LogicTouchItem.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/HeroOperator.h"
#include "./ui/element/SkillAnimation.h"
#include "./game/GameHelper.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)


HeroEvolveUIView::HeroEvolveUIView()
: mMainStatus(NULL)
, mHeroPos1(NULL)
, mHeroPos2(NULL)
, mItemPos(NULL)
, mItemNum(NULL)
, mMatNum(NULL)
, mNeedBear(NULL)
, mButtonStart(NULL)
, mStartEvolve(NULL)
, mQualityColor1(NULL)
, mQualityColor2(NULL)
//,mProcessBar1(NULL)
//,mProcessBar2(NULL)
//,mProcessBar22(NULL)
//,mProcessBar21(NULL)
,mHeroLevelIconBack1(NULL)
,mHeroLevelIconBack2(NULL)
{
	mCurHero = NULL;

	for (int i =0;i <2 ; i++)
	{
		mBear[i] = NULL;
	}
	mContent = NULL;

	effect = NULL;
	isUpgrading = false;
}

HeroEvolveUIView::~HeroEvolveUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
	CC_SAFE_RELEASE(mHeroPos1);
	CC_SAFE_RELEASE(mHeroPos2);
	CC_SAFE_RELEASE(mItemPos);
	CC_SAFE_RELEASE(mItemNum);

	CC_SAFE_RELEASE(mMatNum);
	CC_SAFE_RELEASE(mNeedBear);
	CC_SAFE_RELEASE(mButtonStart);

	CC_SAFE_RELEASE(mStartEvolve);

	//CC_SAFE_RELEASE(mProcessBar1);
	//CC_SAFE_RELEASE(mProcessBar2);
	//CC_SAFE_RELEASE(mProcessBar21);
	//CC_SAFE_RELEASE(mProcessBar22);

	CC_SAFE_RELEASE(mHeroLevelIconBack1);
	CC_SAFE_RELEASE(mHeroLevelIconBack2);

	for (int i =0;i <2 ; i++)
	{
		CC_SAFE_RELEASE(mBear[i]);
	}

}


void HeroEvolveUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
  
	onDataUpdate( false );
}


SEL_MenuHandler HeroEvolveUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSelectHero", HeroEvolveUIView::onButtonSelectHero);

   return NULL;    
}

SEL_CCControlHandler HeroEvolveUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonStartEvolve", HeroEvolveUIView::onButtonStartEvolve);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonReturn", HeroEvolveUIView::onButtonReturn);
	
	
	return NULL;
}

void HeroEvolveUIView::onButtonSelectHero(cocos2d::CCObject * pSender)
{

}

void HeroEvolveUIView::onButtonStartEvolve(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	X_INT need = HeroUpgrade::getUpgradeNeedBearPoint(mCurHero);
	if (mCurHero->GetBearPoint() < need )
	{
		vector<string> strV;strV.clear();

		X_CHAR tip[256] = {0};
		sprintf(tip,UtilTools::GET_TEXT_FROM_LANG(652),need);
		strV.push_back(tip);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}

	stMaterialItem MaterialItem;
	HeroUpgrade::getUpgradeItem(mCurHero,MaterialItem);
	SendLogicPacket::ImproveHero(mCurHero);

	if (MaterialItem.m_nums >= MaterialItem.m_num)
	{
		if (!isUpgrading)		
		{
			//effect
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			effect = EffectAnimation::createWith("evolve",23,4.2f,0.04f,true,false);
			CCPoint pos =  mHeroPos1->getParent()->convertToWorldSpace(mHeroPos1->getPosition());//world pos
			pos =  this->convertToNodeSpace(pos);
			effect->setPosition(pos);
			effect->setScaleX(1.3f * SCALE_X);
			effect->setScaleY(1.3f * SCALE_Y);
			addChild(effect);
			effect->playAnimation();

			SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND5);

			isUpgrading = true;
		}
	}

}

void HeroEvolveUIView::onButtonReturn(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROEVOLVE_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool HeroEvolveUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroPos1", CCMenuItemImage *, mHeroPos1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroPos2", CCSprite *, mHeroPos2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos", CCSprite *, mItemPos);
 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemNum", CCLabelTTF *, mItemNum);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMatNum", CCLabelBMFont *, mMatNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNeedBear", CCLabelBMFont *, mNeedBear);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonStart", CCSprite *, mButtonStart);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBear1", CCLabelBMFont *, mBear[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBear2", CCLabelBMFont *, mBear[1]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mStartEvolve", CCControlButton *, mStartEvolve);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroColorPos1", CCSprite *, mQualityColor1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroColorPos2", CCSprite *, mQualityColor2);

	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar1", CCScale9Sprite *, this->mProcessBar1);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar2", CCScale9Sprite *, this->mProcessBar2);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar21", CCScale9Sprite *, this->mProcessBar21);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar22", CCScale9Sprite *, this->mProcessBar22);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroLevelIconBack1", CCSprite *, this->mHeroLevelIconBack1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroLevelIconBack2", CCSprite *, this->mHeroLevelIconBack2);

    return false;
}

bool HeroEvolveUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
	return bRet;
}

// on "init" you need to initialize your instance
bool HeroEvolveUIView::init()
{
    bool bRet = true;  

    return bRet;
}

void HeroEvolveUIView::onDataUpdate( bool isDataValid )
{
	
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}


	if (mContent)
	{
		mContent->removeFromParentAndCleanup(true);
		mContent = NULL;
	}

	mContent = CCNode::create();
	addChild(mContent);

	if (isUpgrading)
	{
		effect->setZOrder(mContent->getZOrder()+1);
		effect->stopAnimation();
		effect = NULL;
		isUpgrading = false;
	}

	/*const char *recruitItems[6] = {"Recruit_bg_1.png",
		"Recruit_bg_2.png",
		"Recruit_bg_3.png",
		"Recruit_bg_4.png",
		"Recruit_bg_5.png",
		"Recruit_bg_6.png",
	};*/

	const char *qualityItems[6] = {
		"F.png",
		"E.png",
		"D.png",
		"C.png",
		"B.png",
		"A.png"
	};
	float posY = 0.f;
	mCurHero = DataPool::GetSingleton()->GetSelectHero();

	if( mCurHero )
	{
		
		EM_HERO_COLOR_TYPE	mcolor = mCurHero->GetColor();

		CCTexture2D *txQualityColor = CCTextureCache::sharedTextureCache()->addImage(GameHelper::GetHeroEvolveColorById(mcolor).c_str());
		mQualityColor1->setTexture(txQualityColor);
		mQualityColor2->setTexture(txQualityColor);
		
		if (mcolor >= EM_HERO_COLOR_TYPE1 && mcolor <= EM_HERO_COLOR_TYPE6){
			//CCSprite *pSprite = CCSprite::create(recruitItems[mcolor-1]);
			//mHeroPos1->setNormalImage(pSprite);
			//CCTexture2D *Hero2Texture = CCTextureCache::sharedTextureCache()->addImage(recruitItems[mcolor-1]);
			//mHeroPos2->setTexture(Hero2Texture);
		}	

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCSprite *hero1 = CCSprite::create( mCurHero->GetBody().c_str() );
		hero1->setScale(0.8f);
		posY = mHeroPos2->getPosition().y +  mHeroPos2->getContentSize().height *0.18f;
		hero1->setPosition( ccp(winSize.width * 0.266, posY) );
		mContent->addChild( hero1 );

		char buffHeroLv[MAX_STRING_BUFF_SIZE];
		sprintf(buffHeroLv, "%d", mCurHero->GetLevel());
		CCLabelBMFont *heroLvLabel = CCLabelBMFont::create(buffHeroLv, FNT_NAME_HEROLEVEL);
		heroLvLabel->setPosition(mHeroLevelIconBack1->getContentSize().width/2.0f, mHeroLevelIconBack1->getContentSize().height/2.0f);
		mHeroLevelIconBack1->addChild(heroLvLabel);
		mHeroLevelIconBack1->setZOrder(100);
		heroLvLabel->setZOrder(101);

		char buffBear1[MAX_STRING_BUFF_SIZE]={0};
		sprintf(buffBear1,"%d/%d",mCurHero->GetBearPoint(),mCurHero->GetMaxBearPoint());
		mBear[0]->setString(buffBear1);
		

		EM_HERO_QUALITY_TYPE heroQua = mCurHero->GetQuality();//a-e
		CCSprite* pQuality = CCSprite::create(qualityItems[heroQua-1]);
		pQuality->setAnchorPoint(cocos2d::CCPoint(0.5f, 0.5f));
		pQuality->setPosition(cocos2d::CCPoint(mQualityColor1->getContentSize().width*0.5f,mQualityColor1->getContentSize().height*0.67f));
		if (mQualityColor1->getChildrenCount()>0)
		{
			mQualityColor1->removeAllChildrenWithCleanup(true);
		}

		mQualityColor1->addChild(pQuality);


		if (heroQua+1 <= EM_HERO_QUALITY_TYPE6)
		{
			mStartEvolve->setEnabled(true);
			mStartEvolve->setColor(ccWHITE);
			CCSprite* pQuality = CCSprite::create(qualityItems[heroQua]);
			pQuality->setPosition(cocos2d::CCPoint(mQualityColor2->getContentSize().width*0.5f,mQualityColor2->getContentSize().height*0.67f));
			if (mQualityColor2->getChildrenCount()>0)
			{
				mQualityColor2->removeAllChildrenWithCleanup(true);
			}
			mQualityColor2->addChild(pQuality);
		}
		else
		{
			mStartEvolve->setEnabled(false);
			mStartEvolve->setColor(ccGRAY);
		 
			if (mQualityColor2->getChildrenCount()>0)
			{
				mQualityColor2->removeAllChildrenWithCleanup(true);
			}
			/*	CCSprite* pQuality = CCSprite::create(qualityItems[EM_HERO_QUALITY_TYPE6-1]);
			pQuality->setPosition(cocos2d::CCPoint(mQualityColor2->getContentSize().width*0.5f,mQualityColor2->getContentSize().height*0.6f));
			if (mQualityColor2->getChildrenCount()>0)
			{
				mQualityColor2->removeAllChildrenWithCleanup(true);
			}
			mQualityColor2->addChild(pQuality);
			*/
		}
		

		if (heroQua <   EM_HERO_QUALITY_TYPE6)
		{
			CCSprite *hero2 = CCSprite::create( mCurHero->GetBody().c_str() );
			hero2->setPosition(  CCPoint(mHeroPos2->getPosition().x, posY)  );
			hero2->setScale(0.8f);
			mContent->addChild( hero2 );

			char buffHeroLv[MAX_STRING_BUFF_SIZE];
			sprintf(buffHeroLv, "%d", mCurHero->GetLevel());
			CCLabelBMFont *heroLvLabel = CCLabelBMFont::create(buffHeroLv, FNT_NAME_HEROLEVEL);
			heroLvLabel->setPosition(mHeroLevelIconBack2->getContentSize().width/2.0f, mHeroLevelIconBack2->getContentSize().height/2.0f);
			mHeroLevelIconBack2->addChild(heroLvLabel);
			mHeroLevelIconBack2->setZOrder(100);
			heroLvLabel->setZOrder(101);

			X_INT upgradeBear,upgradeMaxBear;
			HeroUpgrade::getUpgradeInfo(mCurHero,upgradeMaxBear,upgradeBear);

			mBear[1]->setVisible(true);

			int useBear2 = mCurHero->GetBearPoint() + upgradeBear;
			char buffBear2[MAX_STRING_BUFF_SIZE]={0};
			sprintf(buffBear2,"%d/%d",useBear2,upgradeMaxBear);
			mBear[1]->setString(buffBear2);
		}
		else
		{
			CCSprite *hero2 = CCSprite::create("n_evolve_lvl_top_text.png");
			hero2->setPosition( mHeroPos2->getPosition() );
			hero2->setScale(0.8f);
			mContent->addChild( hero2 );

			mBear[1]->setVisible(false);
		}
		mQualityColor1->setZOrder(100);
		mQualityColor2->setZOrder(100);
		//各種進度條
		/*float hpPercent = (float) mCurHero->GetHP() / (float) mCurHero->GetHP();

		mProcessBar1->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar1->setInsetLeft(36);
		mProcessBar1->setInsetRight(5);
		mProcessBar1->setInsetTop(5);
		mProcessBar1->setInsetBottom(5);

		mProcessBar1->setPreferredSize(CCSizeMake(hpPercent * 195, 50));

		float mpPercent = (float) mCurHero->GetHP() / (float) mCurHero->GetHP();
		mProcessBar2->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar2->setInsetLeft(36);
		mProcessBar2->setInsetRight(5);
		mProcessBar2->setInsetTop(5);
		mProcessBar2->setInsetBottom(5);

		mProcessBar2->setPreferredSize(CCSizeMake(mpPercent * 195, 50));


		float hpPercent2 = (float) mCurHero->GetHP() / (float) mCurHero->GetHP();

		mProcessBar21->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar21->setInsetLeft(36);
		mProcessBar21->setInsetRight(5);
		mProcessBar21->setInsetTop(5);
		mProcessBar21->setInsetBottom(5);

		mProcessBar21->setPreferredSize(CCSizeMake(hpPercent2 * 195, 50));

		float mpPercent2 = (float) mCurHero->GetMP() / (float) mCurHero->GetMP();
		mProcessBar22->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar22->setInsetLeft(36);
		mProcessBar22->setInsetRight(5);
		mProcessBar22->setInsetTop(5);
		mProcessBar22->setInsetBottom(5);

		mProcessBar22->setPreferredSize(CCSizeMake(mpPercent2 * 195, 50));*/


		
		//......	

	}

	
	//进化需要的道具数量
	stMaterialItem MaterialItem;
	HeroUpgrade::getUpgradeItem(mCurHero,MaterialItem);
	const Item* pItem = MaterialItem.m_pItem;
	X_INT num = MaterialItem.m_num;//需要数量
	if (pItem)
	{
		CCSprite *p_S_Item = CCSprite::create( pItem->GetIcon() );
		p_S_Item->setPosition( mItemPos->getPosition() );
		mContent->addChild( p_S_Item );

		CCSprite *p_S_ItemBg = CCSprite::create("equipmentBK.png");
		p_S_ItemBg->setPosition (mItemPos->getPosition());
		//p_S_ItemBg->setScale( p_S_Item->getContentSize().width / p_S_ItemBg->getContentSize().width);
		p_S_ItemBg->setScale(1.10f);
		mContent->addChild( p_S_ItemBg );

		char tipNum[20]= {0};
		sprintf(tipNum,"x%d",MaterialItem.m_num);
		mItemNum->setString(tipNum);
 		mMatNum->setZOrder(p_S_Item->getZOrder()+1);
		mMatNum->setString(UtilTools::IntToString(MaterialItem.m_nums).c_str());
	}

	X_INT need = HeroUpgrade::getUpgradeNeedBearPoint(mCurHero);
	char needBearBuff[MAX_STRING_BUFF_SIZE];
	sprintf(needBearBuff,"%d",need);
	mNeedBear->setString(needBearBuff);
	mNeedBear->setZOrder(100);

	
}
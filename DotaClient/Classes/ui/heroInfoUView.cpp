#include "./ui/heroInfoUIView.h"
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

#include "./ui/heroInfoUI.h"
#include "./game/GameHelper.h"
#include "./base/Sdk_Handler.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define HEROLVLABLE_OFFSET_X	(0.17f)
#define HEROLVLABLE_OFFSET_Y	(0.935f)

HeroInfoUIView::HeroInfoUIView()
: mHeroHP(NULL)
, mHeroMP(NULL)
, mHeroAttc(NULL)
, mHeroV(NULL)
, mHeroDef(NULL)
, mHeroDist(NULL)
, mHeroDesc(NULL)
, mHeroImagePos(NULL)
, mHeroLevel(NULL)
, mHeroLevelIconBack(NULL)
, mHeroColor(NULL)
, mProcessBar1(NULL)
, mProcessBar2(NULL)
, mshare(NULL)
{
	for (X_INT i = 0;i< 5;i++)
	{
		_mHeroAttcAdd[i]  = NULL;
	}
	for (X_INT i = 0;i< 5;i++)
	{
		mbutton[i]  = NULL;
	}
	

	for( int i = 0; i < MAX_HERO_EQUIPMENT_NUM; i++ )
	{
		mEquipmentPos[i] = NULL;
	}

	for( int i = 0; i < MAX_HERO_SKILL_NUM; i++ )
	{
		mSkillPos[i] = NULL;
		mSkillText[i] = NULL;
		mSkillLvLabel[i] = NULL;
	}
 
	mContentNode = NULL;

	guideLayer = NULL;
	m_pQuality = NULL;
}

HeroInfoUIView::~HeroInfoUIView()
{
	for( int i = 0; i < MAX_HERO_EQUIPMENT_NUM; i++ )
	{
		CC_SAFE_RELEASE(mEquipmentPos[i]);
	}

	for( int i = 0; i < MAX_HERO_SKILL_NUM; i++ )
	{
		CC_SAFE_RELEASE(mSkillPos[i]);
		CC_SAFE_RELEASE(mSkillText[i]);

	}

// 	CC_SAFE_RELEASE(mSkillText1);
// 	CC_SAFE_RELEASE(mSkillText2);
// 	CC_SAFE_RELEASE(mHeroParam);

	CC_SAFE_RELEASE(mHeroHP);
	CC_SAFE_RELEASE(mHeroMP);
	CC_SAFE_RELEASE(mHeroAttc);
	CC_SAFE_RELEASE(mHeroV);
	CC_SAFE_RELEASE(mHeroDef);
	CC_SAFE_RELEASE(mHeroDist);

	CC_SAFE_RELEASE(mHeroDesc);
// 	CC_SAFE_RELEASE(mHeroImagePos);
  
	CC_SAFE_RELEASE(mHeroLevelIconBack);
	CC_SAFE_RELEASE(mHeroColor);

	CC_SAFE_RELEASE(mProcessBar1);
	CC_SAFE_RELEASE(mProcessBar2);

	for (X_INT i = 0;i< 5;i++)
	{
		CC_SAFE_RELEASE(mbutton[i]);
	}

	CC_SAFE_RELEASE(mshare);

	 
}

void HeroInfoUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
	mshare->runAction(CCRepeat::create(
		CCSequence::create(
		CCScaleTo::create(0.8f, 1.2f),
		CCScaleTo::create(0.8f, 1.0f),
		NULL
		),
		kCCRepeatForever
		));
}


SEL_MenuHandler HeroInfoUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", HeroInfoUIView::onButtonClose);
 
	return NULL;    
}

SEL_CCControlHandler HeroInfoUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonEquipmentChange", HeroInfoUIView::onButtonEquipmentChange);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonHeroPromote", HeroInfoUIView::onButtonHeroPromote);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonHeroEvolve", HeroInfoUIView::onButtonHeroEvolve);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonEquipmentCompose", HeroInfoUIView::onButtonEquipmentCompose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonAddLoad", HeroInfoUIView::onButtonAddLoad);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonShare", HeroInfoUIView::onButtonShare);
	return NULL;
}

void HeroInfoUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	//
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

 
void HeroInfoUIView::onButtonShare(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	X_CHAR str[10240] = {0};
	string name = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->getName();
	sprintf(str,UtilTools::GET_TEXT_FROM_LANG(718),Game::sm_SelectServer,Game::getSelectServerName().c_str(),name.c_str(),UtilTools::GET_TEXT_FROM_LANG(717));

	SdkHandler::shareInfo = str;

	
//	sprintf(str,UtilTools::GET_TEXT_FROM_LANG(719),DataPool::GetSingleton()->GetSelectHero()->GetName().c_str() ,Game::sm_SelectServer,Game::getSelectServerName().c_str(),name.c_str(),UtilTools::GET_TEXT_FROM_LANG(717));
//	SdkHandler::shareInfo = str;

}


void HeroInfoUIView::onButtonEquipmentChange(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	//SendLogicPacket::InfoHero(EM_Info_HERO_SINGLE, mHeroList[0]);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
    
    
}

void HeroInfoUIView::onButtonHeroPromote(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	assert( mCurHero );
	DataPool::GetSingleton()->SetSelectHero( mCurHero );
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroInfoUIView::onButtonHeroEvolve(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	assert( mCurHero );
	DataPool::GetSingleton()->SetSelectHero( mCurHero );
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROEVOLVE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroInfoUIView::onButtonEquipmentCompose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_SHOW);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroInfoUIView::onButtonAddLoad(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	//SendLogicPacket::InfoHero(EM_Info_HERO_FRESH);

	/*mHeroParam->setString("a:1100\nb:200");
	mSkillText2->setString("abc  12");*/

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool HeroInfoUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos1", CCSprite *, mEquipmentPos[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos2", CCSprite *, mEquipmentPos[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos3", CCSprite *, mEquipmentPos[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos4", CCSprite *, mEquipmentPos[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos5", CCSprite *, mEquipmentPos[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos6", CCSprite *, mEquipmentPos[5]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillPos1", CCSprite *, mSkillPos[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillPos2", CCSprite *, mSkillPos[1]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillText1", CCLabelBMFont *, mSkillText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillText2", CCLabelBMFont *, mSkillText[1]);

 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroDesc", CCLabelBMFont *, mHeroDesc);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroHP", CCLabelBMFont *, mHeroHP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroMP", CCLabelBMFont *, mHeroMP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroAttc", CCLabelBMFont *, mHeroAttc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroV", CCLabelBMFont *, mHeroV);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroDef", CCLabelBMFont *, mHeroDef);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroDist", CCLabelBMFont *, mHeroDist);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroImagePos", CCSprite *, mHeroImagePos);

 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroLevelIconBack", CCSprite *, mHeroLevelIconBack);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroColor", CCSprite *, mHeroColor);
 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar1", CCScale9Sprite *, mProcessBar1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar2", CCScale9Sprite *, mProcessBar2);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mbutton0", CCControlButton *, mbutton[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mbutton1", CCControlButton *, mbutton[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mbutton2", CCControlButton *, mbutton[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mbutton3", CCControlButton *, mbutton[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mbutton4", CCControlButton *, mbutton[4]);
	 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mshare", CCSprite *, mshare);

	

    return false;
}

bool HeroInfoUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool HeroInfoUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}
void HeroInfoUIView::skillInfoCallBack( cocos2d::CCObject* pSender )
{
	const ObjectSkill * pSkill = static_cast<const ObjectSkill*> (((CCNode *)pSender)->getUserData());
	if (pSkill)
	{
		DataPool::GetSingleton()->SetSelectSkill(pSkill);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_SHOW);

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
	}

	guideLayer = NULL;
}

void HeroInfoUIView::heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr,float scale)
{
	if (_mHeroAttcAdd[attr])
	{
		removeChild(_mHeroAttcAdd[attr]);_mHeroAttcAdd[attr] = X_NULL;
	}
	if (iValue <=0)
	{
		return;
	}

	char buffEX[MAX_STRING_BUFF_SIZE];
	sprintf(buffEX,"+%d",iValue);
	_mHeroAttcAdd[attr] = CCLabelBMFont::create(buffEX,FNT_NAME_LARGEGREEN);
	_mHeroAttcAdd[attr]->setPosition(pos);
	_mHeroAttcAdd[attr]->setAnchorPoint(ccp(0,0.5));
	 addChild(_mHeroAttcAdd[attr]);
	_mHeroAttcAdd[attr]->setScale(scale);
 
}

void HeroInfoUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		//clear();

		return;
	}
	 
	mCurHero = const_cast<ObjectHero*>(DataPool::GetSingleton()->GetSelectHero());

	if( !mCurHero ) return;
	 

	if (mContentNode)
	{
		mContentNode->removeFromParentAndCleanup(true);
		mContentNode = NULL;
	}
	
	mContentNode = CCNode::create();
	addChild(mContentNode);

 
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
	
	const char *qualityItems[6] = {
		"F.png",
		"E.png",
		"D.png",
		"C.png",
		"B.png",
		"A.png"
	};

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(quastr[qua]);
	mHeroColor->setTexture(texture);
 
 
	//mHeroLevel->setString(UtilTools::IntToString(mCurHero->GetLevel()));

	//英雄形象以及英雄的等级
	CCSprite* mHeroImage = CCSprite::create( mCurHero->GetBody().c_str() );

	mHeroImage->setPosition(   CCPoint(mHeroImagePos->getPosition().x,mHeroImagePos->getPosition().y + mHeroImagePos->getContentSize().height*0.2f ));
	// mHeroImage->setScale(1.1f);
	mHeroImage->setZOrder(mHeroColor->getZOrder()-1);
	mContentNode->addChild( mHeroImage, 10 );	

	char buffHeroLv[MAX_STRING_BUFF_SIZE];
	sprintf(buffHeroLv, "%d", mCurHero->GetLevel());
	CCLabelBMFont *heroLvLabel;
	if (mHeroLevelIconBack->getChildByTag(1001))
	{
		mHeroLevelIconBack->removeChildByTag(1001);
	}
	heroLvLabel = CCLabelBMFont::create(buffHeroLv, FNT_NAME_HEROLEVEL);
	heroLvLabel->setPosition(ccp(mHeroLevelIconBack->getContentSize().width/2.0f, mHeroLevelIconBack->getContentSize().height/2.0f));
	heroLvLabel->setTag(1001);
	mHeroLevelIconBack->addChild(heroLvLabel);

	mHeroDesc->setString(mCurHero->GetName().c_str());
	if (m_pQuality)
	{
		removeChild(m_pQuality);
	}
	 
	EM_HERO_QUALITY_TYPE heroQua = mCurHero->GetQuality();//a-e
	m_pQuality = CCSprite::create(qualityItems[heroQua-1]);
	m_pQuality->setAnchorPoint(CCPoint(0.f,0.5f));
	m_pQuality->setPosition(cocos2d::CCPoint(mHeroDesc->getPosition().x + mHeroDesc->getContentSize().width*0.5f*mHeroDesc->getScale() ,mHeroDesc->getPosition().y));
	mHeroDesc->getParent()->addChild(m_pQuality);


	 
	//HP......
	int curEquipHP = mCurHero->GetHP() - mCurHero->getEquipAddHP();
	char buffHP[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffHP,"%d",curEquipHP);
	mHeroHP->setString(buffHP);

	CCPoint posHP = ccp(mHeroHP->getPosition().x + mHeroHP->getContentSize().width*mHeroHP->getScaleX() , mHeroHP->getPosition().y );
	heroAdditionalValue(mCurHero->getEquipAddHP(), posHP,0,mHeroHP->getScale());

	

	float hpPercent = (float) mCurHero->GetHP() / (float) mCurHero->GetHP();

	mProcessBar1->setAnchorPoint( ccp( 0, 0.5f ));

	mProcessBar1->setInsetLeft(36);
	mProcessBar1->setInsetRight(5);
	mProcessBar1->setInsetTop(5);
	mProcessBar1->setInsetBottom(5);

	mProcessBar1->setPreferredSize(CCSizeMake(hpPercent * 195, 50));



	//MP.....
	int curEquipMP = mCurHero->GetMP() - mCurHero->getEquipAddMP();
	char buffMP[MAX_STRING_BUFF_SIZE];
	sprintf(buffMP,"%d",curEquipMP);
	mHeroMP->setString(buffMP);

	CCPoint posMP = ccp(mHeroMP->getPosition().x + mHeroMP->getContentSize().width *mHeroMP->getScaleX(), mHeroMP->getPosition().y );
	heroAdditionalValue(mCurHero->getEquipAddMP(), posMP,1,mHeroMP->getScale());

	float mpPercent = (float) mCurHero->GetMP() / (float) mCurHero->GetMP();

	mProcessBar2->setAnchorPoint( ccp( 0, 0.5f ));

	mProcessBar2->setInsetLeft(36);
	mProcessBar2->setInsetRight(5);
	mProcessBar2->setInsetTop(5);
	mProcessBar2->setInsetBottom(5);

	mProcessBar2->setPreferredSize(CCSizeMake(mpPercent * 195, 50));

	//攻击力
	int curEquipAttc = mCurHero->GetPhysicAttack() - mCurHero->getEquipAddAttack();
	char buffAttc[MAX_STRING_BUFF_SIZE];
	sprintf(buffAttc,"%d",curEquipAttc);
	mHeroAttc->setString(buffAttc);

	CCPoint posAttc = ccp(mHeroAttc->getPosition().x  , mHeroAttc->getPosition().y- mHeroAttc->getContentSize().height);
	heroAdditionalValue(mCurHero->getEquipAddAttack(), posAttc,2,mHeroAttc->getScale());


	int curEquipDef = mCurHero->GetPhysicDefence() - mCurHero->getEquipAddDefense();
	char buffDef[MAX_STRING_BUFF_SIZE];
	sprintf(buffDef,"%d",curEquipDef);
	mHeroDef->setString(buffDef);

	CCPoint posDef = ccp(mHeroDef->getPosition().x  , mHeroDef->getPosition().y- mHeroDef->getContentSize().height);
	heroAdditionalValue(mCurHero->getEquipAddDefense(), posDef,3,mHeroDef->getScale());


	char buffV[MAX_STRING_BUFF_SIZE];
	sprintf(buffV,"%d",mCurHero->getTableData()->_attackSpeed);
	mHeroV->setString(buffV);

	CCPoint posV = ccp(mHeroV->getPosition().x  , mHeroV->getPosition().y- mHeroV->getContentSize().height);
	heroAdditionalValue(mCurHero->getEquipAddSpeed(), posV,4,mHeroV->getScale());

	char buffDist[MAX_STRING_BUFF_SIZE];
	sprintf(buffDist,"%d/%d",mCurHero->GetEquipUsedBearPoint(), mCurHero->GetBearPoint());
	mHeroDist->setString(buffDist);


	//层级关系调整

	mHeroColor->setZOrder(mHeroImage->getZOrder()+1);


	mProcessBar1->setZOrder(mHeroColor->getZOrder()+1);
	mProcessBar2->setZOrder(mHeroColor->getZOrder()+1);
	mHeroHP->setZOrder(mHeroColor->getZOrder()+1);
	mHeroMP->setZOrder(mHeroColor->getZOrder()+1);
	mHeroDesc->setZOrder(mHeroColor->getZOrder()+1);
	for (X_INT i =0;i<5;i++)
	{
		if(_mHeroAttcAdd[i])
			_mHeroAttcAdd[i]->setZOrder(mHeroColor->getZOrder()+1 );
	}
	m_pQuality->setZOrder(mHeroColor->getZOrder()+1 );
	mHeroLevelIconBack->setZOrder(mHeroColor->getZOrder()+1 );
	
	//--------------------------------

	const ItemEquip * pEquip = NULL;
	CCMenuPEx *menu = CCMenuPEx::create(); 

	menu->setPosition( CCPointZero );  
	mContentNode->addChild( menu );

	

	CCSprite *p_S_Equip = NULL;
	for (X_INT i = 0; i < MAX_EQUIP_NUM_PER_HERO;i++)
	{
		 pEquip =   mCurHero->GetEquip(i);


		 CCMenuItemImage *EquipImage = CCMenuItemImage::create("equipmentBK.png", "equipmentBK.png", this, menu_selector(HeroInfoUIView::heroEquipInfoCallBack) );  
		 EquipImage->setPosition( mEquipmentPos[i]->getPosition()); 
		 EquipImage->setUserData( (void *)(pEquip));
		 menu->addChild( EquipImage );
 
		 if (!pEquip) 
		 {
			 continue;
		 }
		 p_S_Equip = CCSprite::create(pEquip->GetIcon()) ;
		 p_S_Equip->setPosition(mEquipmentPos[i]->getPosition());
		 p_S_Equip->setScale(0.80f);
		 mContentNode->addChild(p_S_Equip);

		 menu->setZOrder(p_S_Equip->getZOrder()+1);


		 CCSprite *pLevel = GameHelper::getSpriteLevel(pEquip);
		 if (pLevel)
		 {
			 pLevel->setPosition( p_S_Equip->getPosition()); 
			 mContentNode->addChild(pLevel);
			 pLevel->setZOrder(100);
			 pLevel->setScale(p_S_Equip->getScale());
		 } 
	}



	ObjectSkill * pSkill ;
	for (X_INT i = 0; i < MAX_SKILL_NUM;i++)
	{
		pSkill =  mCurHero->GetSkill(i);
		if (!pSkill)
		{
			continue;
		}
		CCMenuItemImage *menuItem = CCMenuItemImage::create(pSkill->GetIcon(), pSkill->GetIcon(), this, menu_selector(HeroInfoUIView::skillInfoCallBack) );  
		menuItem->setPosition( mSkillPos[i]->getPosition()); 
		menuItem->setUserData( (void *)(pSkill));
		menuItem->setTag(10000+i);
		menuItem->setScale(0.80f);
		menu->addChild( menuItem );

		char buffSkill[MAX_STRING_BUFF_SIZE];
		sprintf(buffSkill,"%s",pSkill->GetName());
		mSkillText[i]->setString(buffSkill);

		sprintf(buffSkill,"%d",pSkill->GetLevel());
		if (mSkillLvLabel[i])
		{
			mSkillLvLabel[i]->setString(buffSkill);
		}
		else
		{
			mSkillLvLabel[i] = CCLabelBMFont::create(buffSkill,FNT_NAME_LARGEGREEN);
			mSkillLvLabel[i]->setAnchorPoint(ccp(0.5f, 0.5f));
			CCPoint pos =  menuItem->getParent()->convertToWorldSpace(menuItem->getPosition());//world pos
			pos =  this->convertToNodeSpace(pos);
			pos.x += menuItem->getContentSize().width * 0.4f;
			pos.y -= menuItem->getContentSize().height * 0.4f;
			mSkillLvLabel[i]->setPosition(pos);
			mSkillLvLabel[i]->setZOrder(menu->getZOrder()+1);
			mSkillLvLabel[i]->setScale(SCALE_BMF);
			addChild(mSkillLvLabel[i]);
		}
		mSkillLvLabel[i]->setVisible(true);

		if ( i == 1)
		{
			bool disableSkill2 = (mCurHero->GetLevel() <6);
			if (disableSkill2)
			{
				menuItem->setColor(ccGRAY);
				mSkillText[i]->setString(UtilTools::GET_TEXT_FROM_LANG(687));
				mSkillLvLabel[i]->setVisible(false);
			}else
			{
				menuItem->setColor(ccWHITE);
			}
		}
	}

	X_INT tipId = ((HeroInfoUI *)this->getUserData())->getTipId();
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
			case 11:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroInfoUIView::changeEquip),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 15:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroInfoUIView::updateHero),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 20:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroInfoUIView::skillInfoCallBack),menu->getChildByTag(10000));
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
	if (mCurHero->GetContainerType() != EM_HERO_CONTAINER_BAG)
	{
		for (X_INT i = 0;i< 5;i++)
		{
			mbutton[i]->setEnabled(false);

		}
	}
}

void HeroInfoUIView::heroEquipInfoCallBack(cocos2d::CCObject *pSender)
{


	const ObjectHero *mCurHero = DataPool::GetSingleton()->GetSelectHero();
	if (!mCurHero|| mCurHero->GetContainerType() != EM_HERO_CONTAINER_BAG)
		return;

	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();

	if (pObj)
	{
// 		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_SHOW);
		const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
		DataPool::GetSingleton()->SetSelectItem(pItem);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_SHOW);
	}
	else
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_SHOW);
	}
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
}

void HeroInfoUIView::changeEquip(cocos2d::CCObject* pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_SHOW);

	guideLayer = NULL;
}

void HeroInfoUIView::updateHero(cocos2d::CCObject * pSender)
{
	DataPool::GetSingleton()->SetSelectHero( mCurHero );
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_SHOW);

	guideLayer = NULL;

}


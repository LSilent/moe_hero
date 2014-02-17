#include "./ui/otherheroInfoUView.h"
//#include "./ui/element/mainSatusView.h"
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

#include "./ui/OtherheroInfoUI.h"
#include "./game/GameHelper.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define CONTENT_POS_X            (0.130f)
#define CONTENT_POS_Y            (0.858f)//(0.455f)

#define CONTENT_VIEW_SIZE_X      (0.70f)
#define CONTENT_VIEW_SIZE_Y      (0.2f)
#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            1
#define ITEM_START_X			 (0.09f) //(0.111f)
#define ITEM_START_Y             (0.05f)//(0.45f)

#define ITEM_SPACE_DELTA_X       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.115f)//(0.127f)//(0.130f)


OherHeroInfoUIView::OherHeroInfoUIView()
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
{
	for (X_INT i = 0;i< 5;i++)
	{
		_mHeroAttcAdd[i]  = NULL;
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
		mContentNode__ = NULL;
		m_pQuality = NULL;
}

OherHeroInfoUIView::~OherHeroInfoUIView()
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
	CC_SAFE_RELEASE(mHeroHP);
	CC_SAFE_RELEASE(mHeroMP);
	CC_SAFE_RELEASE(mHeroAttc);
	CC_SAFE_RELEASE(mHeroV);
	CC_SAFE_RELEASE(mHeroDef);
	CC_SAFE_RELEASE(mHeroDist);
	CC_SAFE_RELEASE(mHeroDesc);
	CC_SAFE_RELEASE(mHeroLevel);
	CC_SAFE_RELEASE(mHeroLevelIconBack);
	CC_SAFE_RELEASE(mHeroColor);
	CC_SAFE_RELEASE(mProcessBar1);
	CC_SAFE_RELEASE(mProcessBar2);

}

void OherHeroInfoUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler OherHeroInfoUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonLeft",    OherHeroInfoUIView::onButtonLeft);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRight", OherHeroInfoUIView::onButtonRight);
	return NULL;    
}

SEL_CCControlHandler OherHeroInfoUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	

    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonReturn", OherHeroInfoUIView::onButtonReturn);
	return NULL;
}

void OherHeroInfoUIView::onButtonReturn(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_OTHERHEROINFO_CLOSE);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void OherHeroInfoUIView::onButtonLeft(cocos2d::CCObject * pSender)
{
	mContent->scrollToPrePage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void OherHeroInfoUIView::onButtonRight(cocos2d::CCObject * pSender)
{
	mContent->scrollToNextPage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool OherHeroInfoUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   
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
	

    return false;
}

bool OherHeroInfoUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

bool OherHeroInfoUIView::init()
{
    bool bRet = true;

    return bRet;
}
void OherHeroInfoUIView::skillInfoCallBack( cocos2d::CCObject* pSender )
{
	return;
	const ObjectSkill * pSkill = static_cast<const ObjectSkill*> (((CCNode *)pSender)->getUserData());
	if (pSkill)
	{
		DataPool::GetSingleton()->SetSelectSkill(pSkill);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_SHOW);
		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
	}
}

void OherHeroInfoUIView::heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr,float scale)
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
	_mHeroAttcAdd[attr]->setZOrder(100);
}

void OherHeroInfoUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		//clear();
		return;
	}
	const ObjectPlayer* pPlayer = DataPool::GetSingleton()->GetSelectPlayer();
	X_INT size = pPlayer->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	
	showHero(0,true);
}

void OherHeroInfoUIView::heroEquipInfoCallBack(cocos2d::CCObject *pSender)
{
	return;
	CCObject *pObj = (CCObject *)((CCNode *)pSender)->getUserData();

	if (pObj)
	{
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
X_VOID OherHeroInfoUIView::showHero(X_INT index,bool b)
{

	const ObjectPlayer* pPlayer = DataPool::GetSingleton()->GetSelectPlayer();
	if (!pPlayer)
	{
		return;
	}
	if (b)
	{
		createNavItem(pPlayer->getHeroNum(EM_HERO_CONTAINER_BAG));
	}
	mCurHero = pPlayer->getHero(index,EM_HERO_CONTAINER_BAG);
	if( !mCurHero ) return;

	if (mContentNode__)
	{
		mContentNode__->removeFromParentAndCleanup(true);
		mContentNode__ = NULL;
	}

	mContentNode__ = CCNode::create();
	mContentNode->addChild(mContentNode__);


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

  
	CCSprite* mHeroImage = CCSprite::create( mCurHero->GetBody().c_str() );

	mHeroImage->setScale(0.9f);
	mHeroImage->setPosition(  CCPoint(mHeroImagePos->getPosition().x, mHeroImagePos->getPosition().y + mHeroImagePos->getContentSize().height*0.1f) );
	 

	mContentNode__->addChild( mHeroImage, 10 );	

	mHeroDesc->setString(mCurHero->GetName().c_str());



	if (m_pQuality)
	{
		removeChild(m_pQuality);
	}

	EM_HERO_QUALITY_TYPE heroQua = mCurHero->GetQuality();//a-e
	m_pQuality = CCSprite::create(qualityItems[heroQua-1]);
	m_pQuality->setAnchorPoint(CCPoint(0.f,0.5f));
	m_pQuality->setPosition(cocos2d::CCPoint(mHeroDesc->getPosition().x + mHeroDesc->getContentSize().width*0.5f *mHeroDesc->getScale(),mHeroDesc->getPosition().y));
	mHeroDesc->getParent()->addChild(m_pQuality);

	 

	char buffHeroLv[MAX_STRING_BUFF_SIZE];
	sprintf(buffHeroLv, "%d", mCurHero->GetLevel());
	CCLabelBMFont *heroLvLabel;
	if (mHeroLevelIconBack->getChildByTag(1001))
	{
		heroLvLabel = (CCLabelBMFont *)mHeroLevelIconBack->getChildByTag(1001);
		heroLvLabel->setString(buffHeroLv);
	}
	else
	{
		heroLvLabel = CCLabelBMFont::create(buffHeroLv, FNT_NAME_HEROLEVEL);
		heroLvLabel->setPosition(ccp(mHeroLevelIconBack->getContentSize().width/2.0f, mHeroLevelIconBack->getContentSize().height/2.0f));
		mHeroLevelIconBack->addChild(heroLvLabel,mHeroLevelIconBack->getZOrder()+1, 1001);
	}
	
	
	

	//HP......
	int curEquipHP = mCurHero->GetHP() - mCurHero->getEquipAddHP();
	char buffHP[MAX_STRING_BUFF_SIZE];
	sprintf(buffHP,"%d",curEquipHP);
	mHeroHP->setString(buffHP);

	CCPoint posHP = ccp(mHeroHP->getPosition().x + mHeroHP->getContentSize().width*mHeroHP->getScaleX(), mHeroHP->getPosition().y  );
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

	CCPoint posMP = ccp(mHeroMP->getPosition().x + mHeroMP->getContentSize().width *mHeroMP->getScaleX() , mHeroMP->getPosition().y);
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

	CCPoint posDef = ccp(mHeroDef->getPosition().x  , mHeroDef->getPosition().y - mHeroDef->getContentSize().height);
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
	mContentNode__->addChild( menu );

	CCSprite *p_S_Equip = NULL;
	for (X_INT i = 0; i < MAX_EQUIP_NUM_PER_HERO;i++)
	{
		pEquip =   mCurHero->GetEquip(i);

		CCMenuItemImage *EquipImage = CCMenuItemImage::create("equipmentBK.png", "equipmentBK.png", this, menu_selector(OherHeroInfoUIView::heroEquipInfoCallBack) );  
		EquipImage->setPosition( mEquipmentPos[i]->getPosition()); 
		EquipImage->setUserData( (void *)(pEquip));
		menu->addChild( EquipImage );

		if (!pEquip) continue;
		p_S_Equip = CCSprite::create(pEquip->GetIcon()) ;
		p_S_Equip->setPosition(mEquipmentPos[i]->getPosition());
		p_S_Equip->setScale(0.80f);
		mContentNode__->addChild(p_S_Equip);

		menu->setZOrder(p_S_Equip->getZOrder()+1);


		CCSprite *pLevel = GameHelper::getSpriteLevel(pEquip);
		if (pLevel)
		{
			pLevel->setPosition( EquipImage->getPosition() ); 
			mContentNode__->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(p_S_Equip->getScale());
		} 

	}


	ObjectSkill * pSkill  = NULL;

	for (X_INT i = 0; i < MAX_SKILL_NUM;i++)
	{
		pSkill =  mCurHero->GetSkill(i);
		if (!pSkill)
		{
			mSkillText[i]->setVisible(false);
			continue;
		}
		CCMenuItemImage *menuItem = CCMenuItemImage::create(pSkill->GetIcon(), pSkill->GetIcon(), this, menu_selector(OherHeroInfoUIView::skillInfoCallBack) );  
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
		mSkillText[i]->setVisible(true);
	}


} 
void OherHeroInfoUIView::createNavItem(X_INT size)
{
	mNagItemSize = size;
 
	 
	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	mContentNode = CCNode::create();
	addChild( mContentNode );

 
	int pageNum = 4;
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
void OherHeroInfoUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void OherHeroInfoUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

bool OherHeroInfoUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	int size = mNagItemSize;

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenuPEx *menu = CCMenuPEx::create();
	int lineIndex = 0;
	int columnIndex = 0;
	const ObjectPlayer* pPlayer = DataPool::GetSingleton()->GetSelectPlayer();
 
	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		const ObjectHero* pHero =  pPlayer->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}
	 
		string titleIcon = pHero->GetHeadIcon() ;
		CCSprite *heroFrame = CCSprite::create(GameHelper::GetHeroColorById(pHero->GetColor()).c_str());
		heroFrame->setAnchorPoint(CCPointZero);
 
		CCMenuItemImage *menuItem = CCMenuItemImage::create( titleIcon.c_str(),titleIcon.c_str(), this, menu_selector(OherHeroInfoUIView::itemInfoCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		
		menuItem->setScale(0.65f);
		heroFrame->setPosition( CCPointMake(-5.0f, -5.0f) );
		heroFrame->setScale(menuItem->getContentSize().width / heroFrame->getContentSize().width + 0.1f);
		menuItem->addChild(heroFrame);
		menuItem->setPosition( itemPos ); 
		
		menuItem->setUserData( (void *)(i));
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

void OherHeroInfoUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
}
void OherHeroInfoUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	
}
void OherHeroInfoUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	int index = (int)((CCNode *)pSender)->getUserData();
	showHero(index);
}
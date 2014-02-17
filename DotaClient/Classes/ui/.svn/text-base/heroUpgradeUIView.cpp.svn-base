#include "./ui/HeroUpgradeUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/EquipOperator.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/ProgressView.h"
#include "./object/ItemCommon.h"
#include "./game/GameHelper.h"

#include "./ui/heroUpgradeUI.h"

#include "./ui/element/SkillAnimation.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.140f)
#define CONTENT_POS_Y            (0.238f)

#define CONTENT_VIEW_SIZE_X      (0.700f)
#define CONTENT_VIEW_SIZE_Y      (0.35f)

#define ITEM_SPACE_DELTA_X       (0.138f)
#define ITEM_SPACE_DELTA_Y       (0.110f)

#define ITEM_START_X             (0.070f)
#define ITEM_START_Y             (0.185f)

#define ITEM_COLUMN_NUM          5
#define ITEM_LINE_NUM            2


HeroUpgradeUIView::HeroUpgradeUIView()
: mHeroInfo(NULL)
, mAttackNum(NULL)
, mArmorNum(NULL)
, mSpeedNum(NULL)
, mLoadNum(NULL)
, mBloodNum(NULL)
, mMagicNum(NULL)
, mHeroIconPos(NULL)
, mMainStatus(NULL)
, mProgressPos(NULL)

{
	mContentNode = NULL;
	mPageCtrl = NULL;

 	mSelectTotalExp = 0;

	ObjectHero *pHero= const_cast<ObjectHero*>(DataPool::GetSingleton()->GetSelectHero());
	int curHeroLvl = pHero->GetLevel();

	uLvl = pHero->GetLevel();
	uExp = pHero->GetExp();

	mPreLvl = uLvl;

	guideLayer = NULL;
	effect = NULL;

	isUpgrading = false;
	for (X_INT i = 0;i< 5;i++)
	{
		_mHeroAttcAdd[i]  = NULL;
	}

}

HeroUpgradeUIView::~HeroUpgradeUIView()
{
	CC_SAFE_RELEASE(mHeroInfo);
	CC_SAFE_RELEASE(mAttackNum);
	CC_SAFE_RELEASE(mArmorNum);
	CC_SAFE_RELEASE(mSpeedNum);
	CC_SAFE_RELEASE(mLoadNum);
	CC_SAFE_RELEASE(mBloodNum);
	CC_SAFE_RELEASE(mMagicNum);
	CC_SAFE_RELEASE(mHeroIconPos);
	CC_SAFE_RELEASE(mMainStatus);
	CC_SAFE_RELEASE(mProgressPos);

}


void HeroUpgradeUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler HeroUpgradeUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonConfirm", HeroUpgradeUIView::onButtonConfirm);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCancel", HeroUpgradeUIView::onButtonCancel);
	return NULL;    
}

SEL_CCControlHandler HeroUpgradeUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	

	return NULL;
}

void HeroUpgradeUIView::onButtonConfirm(cocos2d::CCObject * pSender)
{

	if (itemlistSelect.size() == 0)
	{
		return;
	}
	

	if (!isUpgrading)
	{
		 vector<const Item*> itemUsed;
		 vector<int> itemUsedCount;

		 for( unsigned int i = 0; i < itemlistSelect.size(); i ++ )
		 {

				 if( itemUsed.empty() || itemUsed.back()->GetTableID() != itemlistSelect[i]->GetTableID() )
				 {
					 itemUsed.push_back( itemlistSelect[i] );
					 itemUsedCount.push_back( 1 );
				 }
				 else
				 {
					 itemUsedCount.back() ++;
				 }
		 }

		 // TODO
		 SendLogicPacket::UseItem(itemUsed,itemUsedCount,mCurHero);

 		 mSelectTotalExp = 0;
	// 	 mPreLvl = 0;

		 guideLayer = NULL;

		//effect
		effect = EffectAnimation::createWith("levelup",30,2.2f,0.03f,true,false);
		effect->setPosition(mHeroIconPos->getPosition());
		addChild(effect);
		effect->playAnimation();

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND6);

		isUpgrading = true;
	}

}

void HeroUpgradeUIView::onButtonCancel(cocos2d::CCObject * pSender)
{
	 EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_CLOSE);

	 guideLayer = NULL;

	 SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	
}

bool HeroUpgradeUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroInfo", CCLabelBMFont *, this->mHeroInfo);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAttackNum", CCLabelBMFont *, this->mAttackNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mArmorNum", CCLabelBMFont *, this->mArmorNum);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSpeedNum", CCLabelBMFont *, this->mSpeedNum);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLoadNum", CCLabelBMFont *, this->mLoadNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBloodNum", CCLabelBMFont *, this->mBloodNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMagicNum", CCLabelBMFont *, this->mMagicNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroIconPos", CCSprite *, this->mHeroIconPos);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProgressPos", CCSprite *, this->mProgressPos);

	


	return false;
}

bool HeroUpgradeUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
    return bRet;
}

// on "init" you need to initialize your instance
bool HeroUpgradeUIView::init()
{
    bool bRet = true;

    return bRet;
}

void HeroUpgradeUIView::heroAdditionalValue(int iValue, cocos2d::CCPoint pos,X_INT attr,float scale)
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
bool HeroUpgradeUIView::_SortItemExperience(Item *pItem1,Item *pItem2)
{
	if (!pItem1 || !pItem2)
	{
		return false;
	}
	return pItem1->GetTableID() > pItem2->GetTableID();

}
void HeroUpgradeUIView::onDataUpdate( bool isDataValid )
{

	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}

	if (isUpgrading) 
	{
		if (mContentNode)
		{
			effect->setZOrder(mContentNode->getZOrder()+1);
		}
		
		effect->stopAnimation();
		effect = NULL;
		isUpgrading = false;
	}
	
	X_INT tipId = ((HeroUpgradeUI *)this->getUserData())->getTipId();

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;
	if (tipId != -1)
	{
  
		if (!guideLayer)
		{
			if (tipId == 17)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroUpgradeUIView::onButtonConfirm),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer,LAYER_MAX_ZORDER);

				return;
			}
			else if (tipId == 18)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroUpgradeUIView::onButtonCancel),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer,LAYER_MAX_ZORDER);

				return;
			}
		}
	}



	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	if (mPageCtrl)
	{
		mPageCtrl->removeFromParentAndCleanup( true );
		mPageCtrl = NULL;
	}
	
	 
	mContentNode = CCNode::create();
	addChild( mContentNode );



	mCurHero = const_cast<ObjectHero*>(DataPool::GetSingleton()->GetSelectHero());

	 

	mExpProgress = ProgressView::createProgress("n_xj_progress.png");
	mExpProgress->setScaleX(mProgressPos->getScaleX());
	mExpProgress->setAnchorPoint(ccp(0.5,0.5));
	mExpProgress->setPosition(mProgressPos->getPosition());
	float _value = ((float)mCurHero->GetExp() * 100)/(float)(mCurHero->GetMaxExpWithLevel());
	mExpProgress->setProgressValue(_value,1,PROGRESS_ADD,false);
	mContentNode->addChild(mExpProgress);

	CCSprite *itemSpriteIconBack = CCSprite::create( "n_pos_back_.png" );
	itemSpriteIconBack->setPosition( mHeroIconPos->getPosition() );
	mContentNode->addChild( itemSpriteIconBack );

	CCSprite *itemSprite = CCSprite::create( mCurHero->GetHeadIcon().c_str() );
	itemSprite->setPosition( mHeroIconPos->getPosition() );
	mContentNode->addChild( itemSprite );

	CCSprite *itemSpriteBG = CCSprite::create(mCurHero->getHeroColor().c_str() );
	itemSpriteBG->setPosition( mHeroIconPos->getPosition() );
	mContentNode->addChild( itemSpriteBG );

 

	string sHeroInfo;
	sHeroInfo = UtilTools::GET_TEXT_FROM_LANG(525);
	sHeroInfo += " ";
	sHeroInfo += UtilTools::IntToString(mCurHero->GetLevel());
	sHeroInfo += " ";
	sHeroInfo += mCurHero->GetName();



	mHeroInfo->setString(sHeroInfo.c_str());
	mHeroInfo->setZOrder(mProgressPos->getZOrder()+1);
 
	int curEquipHP = mCurHero->GetHP() - mCurHero->getEquipAddHP();
	mBloodNum->setString(UtilTools::IntToString(curEquipHP).c_str());
	CCPoint posHP = ccp(mBloodNum->getPosition().x + mBloodNum->getContentSize().width*mBloodNum->getScaleX() , mBloodNum->getPosition().y);
	heroAdditionalValue(mCurHero->getEquipAddHP(), posHP,0,mBloodNum->getScale());

	int curEquipMP = mCurHero->GetMP() - mCurHero->getEquipAddMP();
	mMagicNum->setString(UtilTools::IntToString(curEquipMP).c_str());
	CCPoint posMP = ccp(mMagicNum->getPosition().x + mMagicNum->getContentSize().width*mMagicNum->getScaleX() , mMagicNum->getPosition().y );
	heroAdditionalValue(mCurHero->getEquipAddMP(), posMP,1,mMagicNum->getScale());

	int curEquipAttc = mCurHero->GetPhysicAttack() - mCurHero->getEquipAddAttack();
	mAttackNum->setString(UtilTools::IntToString(curEquipAttc).c_str());
	CCPoint posAttack = ccp(mAttackNum->getPosition().x  , mAttackNum->getPosition().y- mAttackNum->getContentSize().height);
	heroAdditionalValue(mCurHero->getEquipAddAttack(), posAttack,2,mAttackNum->getScale());

	int curEquipDef = mCurHero->GetPhysicDefence() - mCurHero->getEquipAddDefense();
	mArmorNum->setString(UtilTools::IntToString(curEquipDef).c_str());
	CCPoint posArmor = ccp(mArmorNum->getPosition().x  , mArmorNum->getPosition().y - mArmorNum->getContentSize().height);
	heroAdditionalValue(mCurHero->getEquipAddDefense(), posArmor,3,mArmorNum->getScale());

	mSpeedNum->setString(UtilTools::IntToString(mCurHero->getTableData()->_attackSpeed).c_str());
	CCPoint posSpeed = ccp(mSpeedNum->getPosition().x , mSpeedNum->getPosition().y- mSpeedNum->getContentSize().height );
	heroAdditionalValue(mCurHero->getEquipAddSpeed(), posSpeed,4,mSpeedNum->getScale());

	string sLoad;
	sLoad = UtilTools::IntToString(mCurHero->GetBearPoint());
	sLoad += "/";
	sLoad += UtilTools::IntToString(mCurHero->GetMaxBearPoint());
	mLoadNum->setString(sLoad.c_str());

	 
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
    SelfBagData*  pBag =    DataPool::GetSingleton()->getBagData();
	X_UINT size = pBag->GetBagSize(EM_ITEM_CONTAINER_BAG);

	itemlist.clear();
	Item *pItem;
	for (X_UINT i = 0 ; i< size ;i++)
	{
		pItem = pBag->getItem(i,EM_ITEM_CONTAINER_BAG);
		if (pItem && pItem->GetTableType() == ITEM_EXPERIENCE)
		{
			for (int j=0;j<pItem->GetCount();j++)
			{
				itemlist.push_back(pItem);
			}
		}
	}

	sort(itemlist.begin(),itemlist.end(),_SortItemExperience);
	size = itemlist.size();
	itemListSize = size;

	// clear record
	itemlistSelect.clear();
	itemlistStatus.clear();
 


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

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * 0.063f));
	addChild(mPageCtrl);

 
}


void HeroUpgradeUIView::getTotalExp(int totalExp,int &tLvl,int &tExp)
{
	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();
	int curSelfLvl = pData->GetLevel();

	ObjectHero *pHero= const_cast<ObjectHero*>(DataPool::GetSingleton()->GetSelectHero());
	int curHeroLvl = pHero->GetLevel();

	if (totalExp == 0)
	{
		tLvl = pHero->GetLevel();
		tExp = pHero->GetExp();

		return;
	}
	//2 3
	int mLvl = curSelfLvl + 5 - curHeroLvl;
	int maxExp = GameHelper::GetHeroExpByLevel(curHeroLvl) - pHero->GetExp();

	if (maxExp >= totalExp)
	{
		tLvl = pHero->GetLevel();
		tExp = pHero->GetExp() + totalExp;

		return;
	}
	

	int i = curHeroLvl + 1;
	for (;i < mLvl + curHeroLvl;i++)
	{
		int cExp = GameHelper::GetHeroExpByLevel(i);
		maxExp += cExp;
		if (maxExp > totalExp)
		{
			tLvl = i;
			tExp = abs(cExp - (maxExp - totalExp));

			break;
		}
	}

	if (totalExp > maxExp)
	{
		tLvl = mLvl + curHeroLvl;
		tExp = GameHelper::GetHeroExpByLevel(tLvl);
	}
	

}

void HeroUpgradeUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
// 	if( mContent->mIsMoved )
// 		return;
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	CCSprite *checkSprite = (CCSprite *)(((CCNode *)(pSender))->getUserData());

	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();
	int curSelfLvl = pData->GetLevel();

	int useLvl = max(0,curSelfLvl + 5 - uLvl);

	if (useLvl ==0 && !checkSprite->isVisible())
	{

		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(563),this,DIALOG_MODEL_SINGLE);
		addChild(dialog , 10);
		return;
	}
	

	checkSprite->setVisible(!checkSprite->isVisible());
	Item *pItem = (Item *)checkSprite->getUserData();

	int selExp =  ((ItemCommon *)pItem)->getTableData()->_exp;

	ProgressIdenType type_;

	if (checkSprite->isVisible())
	{
		itemlistSelect.push_back(pItem);

 		mSelectTotalExp += ((ItemCommon *)pItem)->getTableData()->_exp;
		
		type_ = PROGRESS_ADD;
	}
	else
	{
		vector<Item *>::iterator iter = itemlistSelect.begin();
		for (;iter!=itemlistSelect.end();iter++)
		{
			if ((*iter)->GetGuid() == pItem->GetGuid())
			{
 				mSelectTotalExp -= ((ItemCommon *)pItem)->getTableData()->_exp;
				
				itemlistSelect.erase(iter);
				break;
			}
			
		}
		type_ = PROGRESS_SUB;
	}

	getTotalExp(mSelectTotalExp,uLvl,uExp);


	float _value;
	int heroMaxLvl = GameHelper::GetHeroExpByLevel(uLvl);
	_value = ((float)uExp * 100)/(float)(heroMaxLvl);

		
	mExpProgress->setProgressValue(_value,((type_ == PROGRESS_ADD)? (uLvl-mPreLvl) : (mPreLvl - uLvl)),type_,true);

	mPreLvl = uLvl;

	string sHeroInfo;
	sHeroInfo = UtilTools::GET_TEXT_FROM_LANG(525);
	sHeroInfo += " ";
	sHeroInfo += UtilTools::IntToString(uLvl);
	sHeroInfo += " ";
	sHeroInfo += mCurHero->GetName();

	mHeroInfo->setString(sHeroInfo.c_str());

	guideLayer =  NULL;
}

void HeroUpgradeUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void HeroUpgradeUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool HeroUpgradeUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
 
 
	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = itemListSize / pageNum + (((itemListSize % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(itemListSize - nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	int lineIndex = 0;
	int columnIndex = 0;

	Item *pItem;

	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		pItem = itemlist[i];
		if (!pItem)
		{
			continue;
		}

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pItem->GetIcon(), pItem->GetIcon(), this, menu_selector(HeroUpgradeUIView::itemInfoCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM+1);

		//CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		CCPoint itemPos = CCPointMake(winSize.width *(ITEM_START_X + columnIndex * ITEM_SPACE_DELTA_X) ,
			winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));

		menuItem->setPosition( itemPos ); 
	
		menu->addChild( menuItem );

		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(menuItem->getPosition());
		equipBG->setScale(1.15f);
		equipBG->setZOrder(menu->getZOrder() + 1);
		pPage->addChild(equipBG);

		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setPosition( itemPos );		
		checkItem->setUserData( pItem );
		checkItem->setVisible(false);
		checkItem->setScale(0.70f);
		pPage->addChild( checkItem, 10 );

		menuItem->setUserData( checkItem );

		//
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
		X_INT tipId = ((HeroUpgradeUI *)this->getUserData())->getTipId();
 
		if (guideLayer)
		{
			guideLayer->removeFromParentAndCleanup(true);
		}

		guideLayer = X_NULL;
		if (tipId != -1)
		{   
 
			//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();

			if (!guideLayer)
			{
				if (tipId == 16 && i == 0)
				{
					guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroUpgradeUIView::itemInfoCallBack),menuItem);
					guideLayer->setPosition(getPosition());
					addChild(guideLayer);
				}
			}
		}

	}

	menu->setPosition( CCPointZero );
	pPage->addChild(menu);


	if (nPage == totalPage - 1)
	{
		if (guideLayer)
		{
			guideLayer->setZOrder(LAYER_MAX_ZORDER);
		}
	}
	


	return true;
}
void HeroUpgradeUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void HeroUpgradeUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
}

void HeroUpgradeUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	pSender->closeDialogView();
}
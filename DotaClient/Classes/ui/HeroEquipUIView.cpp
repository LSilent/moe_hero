#include "./ui/HeroEquipUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./object/ItemEquip.h"
#include "./datapool/HeroOperator.h"

#include "./ui/HeroEquipUI.h"
#include "./game/GameHelper.h"

using namespace cocos2d;
USING_NS_CC_EXT;

// #define MAX_STRING_BUFF_SIZE     (128)
// 
// #define CONTENT_POS_X            (0.05f)
// #define CONTENT_POS_Y            (0.25f)
// 
// #define CONTENT_VIEW_SIZE_X      (0.89f)
// #define CONTENT_VIEW_SIZE_Y      (0.65f)
// 
// #define ITEM_DOCK_X              (0.455f)
// #define ITEM_SPACE_DELTA_Y       (0.17f)
// #define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)
// 
// #define ITEM_IMAGE_OFFSET_X      (-0.30f)
// #define ITEM_IMAGE_OFFSET_Y      (0.00f)
// 
// #define ITEM_NAME_OFFSET_X       (-0.20f)
// #define ITEM_NAME_OFFSET_Y       (0.030f)
// 
// #define ITEM_LOAD_OFFSET_X       (-0.17f)
// #define ITEM_LOAD_OFFSET_Y       (-0.030f)
// 
// #define ITEM_ADD_OFFSET_X        (0.10f)
// #define ITEM_ADD_OFFSET_Y        (0)
// 
// #define ITEM_POINT_OFFSET_X      (0.20f)
// #define ITEM_POINT_OFFSET_Y      (0)
// 
// #define ITEM_SUB_OFFSET_X        (0.30f)
// #define ITEM_SUB_OFFSET_Y        (0)

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.150f)
#define CONTENT_POS_Y            (0.243f)//(0.245f)

#define CONTENT_VIEW_SIZE_X      (0.68f)
#define CONTENT_VIEW_SIZE_Y      (0.55f)

#define ITEM_SPACE_DELTA_X       (0.150f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.100f)//(0.130f)

#define ITEM_START_X			 (0.087f) //(0.111f)
#define ITEM_START_Y             (0.45f)//(0.45f)

#define ITEM_COLUMN_NUM          5
#define ITEM_LINE_NUM            4

#define EQUIP_MAX_NUM			6

#define BIND_SPRITE_TAG			1000

#define DIALOG_EQUIP_BIND        100
#define DIALOG_EQUIP_NOT_BEAR_GOTOBUY	 101
#define DIALOG_EQUIP_ONLY        102
#define DIALOG_EQUIP_NUM_MAX	 103
#define DIALOG_EQUIP_NOT_BEAR_GOTODIS	 104

HeroEquipUIView::HeroEquipUIView()
	:mHeroName(NULL)
	,mEquiNum(NULL)
	,mEquiBear(NULL)
	,mSelEquipNode(NULL)
	,mRecmdEquipNode(NULL)
	,mChangeText(NULL)
{


	for (int i = 0;i <20 ; i++)
	{
		mRecmt[i] = NULL;


	}
	

	mPageCtrl = NULL;
	mContent = NULL;
	mCurHeroTotal = 0;
	usedNum = 0;

	recmdFlag = false;

	guideLayer = NULL;

}

HeroEquipUIView::~HeroEquipUIView()
{
	CC_SAFE_RELEASE(mHeroName);
	CC_SAFE_RELEASE(mEquiNum);
	CC_SAFE_RELEASE(mEquiBear);

	CC_SAFE_RELEASE(mSelEquipNode);
	CC_SAFE_RELEASE(mRecmdEquipNode);
	CC_SAFE_RELEASE(mChangeText);

	for (int i = 0;i < 20 ; i++)
	{
		CC_SAFE_RELEASE(mRecmt[i]);


	}
}


void HeroEquipUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler HeroEquipUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "mButtonRmdEquip", HeroEquipUIView::mButtonRmdEquip);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonOK", HeroEquipUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCancel", HeroEquipUIView::onButtonCancel);
	
	return NULL;    
}

SEL_CCControlHandler HeroEquipUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	
	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonChange", HeroEquipUIView::onButtonChange);
	
	return NULL;
}

void HeroEquipUIView::onButtonOK(cocos2d::CCObject * pSender)
{
//  	SendLogicPacket::DistribHeroBearpoint(mHeroArray,mLoadDistributeArray);

// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLUPGRADE_EQU_CLOSE);
// 	DataPool::GetSingleton()->SetSelectEqui(mSkillEquiItems);
// 
// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_UPDATA);
	


	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	vector<int > mSelectNum(mSelectEqui.size(),1);
	SendLogicPacket::UseItem(mSelectEqui,mSelectNum,pHero);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_CLOSE);


	guideLayer = NULL;
}


void HeroEquipUIView::onButtonCancel(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HERO_EQUI_CLOSE);
}

void HeroEquipUIView::loadRecommendEquip()
{
	//MAX_EQUIP_RECOMMEND
	//出门装  ， 基本装， 中期装， 神装
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();

	const Item *pItem;
	X_UINT size = itemRecmdEquips.size();
	for (X_UINT i = 0;i<size;++i)
	{
		pItem = itemRecmdEquips[i];
		if (!pItem)
		{
			continue;
		}
		else
		{
			CCSprite *pSprite = CCSprite::create(pItem->GetIcon());
			pSprite->setScale(0.80f);
			pSprite->setPosition(mRecmt[i]->getPosition());
			mRecmt[i]->setUserData((void *)pItem);
			mRecmdEquipNode->addChild(pSprite);
 
			CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
			if (pLevel)
			{
				pLevel->setPosition( pSprite->getPosition() ); 
				mRecmdEquipNode->addChild(pLevel);
				pLevel->setZOrder(100);
				pLevel->setScale(pSprite->getScale());
			} 
 
			if (!pHero->ISEquipedByTableID((ItemEquip *)pItem))
			{
				pSprite->setColor(ICON_COLOR_GRAY);
			}
			

		}

	}

	recmdFlag = true;

}

void HeroEquipUIView::onButtonChange(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	if (!mRecmdEquipNode->isVisible())
	{
		mRecmdEquipNode->setVisible(true);
		mSelEquipNode->setVisible(false);
		mContent->setVisible(false);
		mPageCtrl->setVisible(false);

		CCTexture2D *texture2D = CCTextureCache::sharedTextureCache()->addImage("n_equip_back.png");
		mChangeText->setTexture(texture2D);

		//todo load data
		if(!recmdFlag)
			loadRecommendEquip();

	}
	else
	{
		mRecmdEquipNode->setVisible(false);
		mSelEquipNode->setVisible(true);
		mContent->setVisible(true);
		mPageCtrl->setVisible(true);

		CCTexture2D *texture2D = CCTextureCache::sharedTextureCache()->addImage("n_equip_remd.png");
		mChangeText->setTexture(texture2D);
	}
}

bool HeroEquipUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
// 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLoadPointLeft", CCLabelTTF *, this->mLoadPointLeft);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroName", CCLabelBMFont *, this->mHeroName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquiNum", CCLabelBMFont *, this->mEquiNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquiBear", CCLabelBMFont *, this->mEquiBear);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelEquipNode", CCNode *, this->mSelEquipNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmdEquipNode", CCNode *, this->mRecmdEquipNode);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mChangeText", CCSprite *, this->mChangeText);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt0", CCMenuItemImage *, this->mRecmt[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt1", CCMenuItemImage *, this->mRecmt[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt2", CCMenuItemImage *, this->mRecmt[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt3", CCMenuItemImage *, this->mRecmt[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt4", CCMenuItemImage *, this->mRecmt[4]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt5", CCMenuItemImage *, this->mRecmt[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt6", CCMenuItemImage *, this->mRecmt[6]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt7", CCMenuItemImage *, this->mRecmt[7]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt8", CCMenuItemImage *, this->mRecmt[8]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt9", CCMenuItemImage *, this->mRecmt[9]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt10", CCMenuItemImage *, this->mRecmt[10]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt11", CCMenuItemImage *, this->mRecmt[11]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt12", CCMenuItemImage *, this->mRecmt[12]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt13", CCMenuItemImage *, this->mRecmt[13]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt14", CCMenuItemImage *, this->mRecmt[14]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt15", CCMenuItemImage *, this->mRecmt[15]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt16", CCMenuItemImage *, this->mRecmt[16]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt17", CCMenuItemImage *, this->mRecmt[17]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt18", CCMenuItemImage *, this->mRecmt[18]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecmt19", CCMenuItemImage *, this->mRecmt[19]);


	return false;
}

bool HeroEquipUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;

	return bRet;
}

// on "init" you need to initialize your instance
bool HeroEquipUIView::init()
{
	bool bRet = true;



	return bRet;
}



void HeroEquipUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}

	X_INT tipId = ((HeroEquipUI *)this->getUserData())->getTipId();
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
			if (tipId == 13)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroEquipUIView::onButtonOK),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer,LAYER_MAX_ZORDER);

				return;
			}
		}
	}


	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}

	if (mPageCtrl)
	{
		mPageCtrl->removeFromParentAndCleanup(true);
		mPageCtrl = NULL;
	}
	
	itemRecmdEquips.clear();
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	HeroUpgrade::getRecommendItem(pHero,itemRecmdEquips);

	
	mEquipItems.clear();

	mHeroName->setString(pHero->GetName().c_str());
	mHeroName->setColor(ccGREEN);

	string sBear = UtilTools::GET_TEXT_FROM_LANG(524);
	sBear+=":";
	sBear += UtilTools::IntToString(0);
	sBear+="/";
	sBear+= UtilTools::IntToString(pHero->GetBearPoint());
	mEquiBear->setString(sBear.c_str());


	mSelectEqui.clear();
	vector<const Item*>  itemlist;
	DataPool::GetSingleton()->getObjectManager()->getHeroCanUseEquips(pHero,itemlist);
	mCurHeroTotal = itemlist.size();

	for (int i = mCurHeroTotal -1; i >=  0; i--)
	{
		const Item *pItem = itemlist[i];
		if (pHero->ISEquiped((ItemEquip *)pItem))
		{
			usedNum++;
			mSelectEqui.push_back(pItem);
		}
		
	}

	string sNum;
	sNum = UtilTools::IntToString(usedNum);
	sNum +="/";
	sNum+=UtilTools::IntToString(EQUIP_MAX_NUM);
	mEquiNum->setString(sNum.c_str());
	

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = mCurHeroTotal / pageNum + (((mCurHeroTotal % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y);
	mContent = CCScrollViewPage::create();
	mContent->createContainer(this,totalPage,viewSize); 


	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentOffset(CCPointZero);
	mContent->setDirection( kCCScrollViewDirectionHorizontal );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	addChild( mContent );

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * -0.020));
	addChild(mPageCtrl);


	mRecmdEquipNode->setVisible(false);
	mSelEquipNode->setVisible(true);

}

void HeroEquipUIView::checkEquipStatus()
{
	int curBear = 0;
	for (unsigned int i = 0;i < mSelectEqui.size(); i++)
	{
		 ItemEquip *pItem = (ItemEquip *)mSelectEqui[i];
		 curBear +=pItem->m_pTableData->_weight;
	}
	
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	int maxBear = pHero->GetBearPoint();
	if (curBear > maxBear) return;
	surplusBear = maxBear - curBear;

	// 	bool bUnique = pItem->Rule(EM_UNIQUE);
	// 	pItem->m_pTableData->_weight;
	// 	pItem->Rule(EM_USEBIND)

	for (unsigned int j = 0; j < mEquipItems.size(); j++)
	{
		const ItemEquip *pItem = (ItemEquip *)((CCSprite *)mEquipItems[j]->getUserData())->getUserData();
		CCSprite *bSprite = (CCSprite *)((CCSprite *)mEquipItems[j]->getUserData())->getParent()->getChildByTag(j+BIND_SPRITE_TAG);

		if (isChecked((Item *)pItem))
		{
			continue;
		}
		else
		{
			if ((pItem->m_pTableData->_weight) <= surplusBear)
			{
				if ( pItem->Rule(EM_UNIQUE) && isUniqued((Item *)pItem))
				{
// 					mEquipItems[j]->setEnabled(false);
					mEquipItems[j]->setColor(ICON_COLOR_GRAY);//80
					((CCSprite *)mEquipItems[j]->getUserData())->setVisible(false);

					if (bSprite)
						bSprite->setColor(ICON_COLOR_GRAY);
					
				}
				else
				{
// 					mEquipItems[j]->setEnabled(true);
					mEquipItems[j]->setColor(ccWHITE);

					if (bSprite)
						bSprite->setColor(ccWHITE);
				}
				
			}
			else
			{
// 				mEquipItems[j]->setEnabled(false);
				mEquipItems[j]->setColor(ICON_COLOR_GRAY);//80
				((CCSprite *)mEquipItems[j]->getUserData())->setVisible(false);
				if (bSprite)
					bSprite->setColor(ICON_COLOR_GRAY);
			}
			
		}
		
	}

	updateEquipInfo();

}

bool HeroEquipUIView::isChecked(Item *pItem)
{
	bool flag = false;
	vector<const Item *>::iterator iter = mSelectEqui.begin();
	for (;iter!=mSelectEqui.end();iter++)
	{
		if ((*iter)->GetGuid() == pItem->GetGuid())
		{
			flag = true;
			break;
		}
	}

	return flag;
}

bool HeroEquipUIView::isUniqued(Item *pItem)
{
	bool flag = false;
	vector<const Item *>::iterator iter = mSelectEqui.begin();
	for (;iter!=mSelectEqui.end();iter++)
	{
		if ((*iter)->Rule(EM_UNIQUE) && (*iter)->GetTableID() == pItem->GetTableID())
		{
			flag = true;
			break;
		}
	}

	return flag;
}

void HeroEquipUIView::updateEquipInfo()
{
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();

  
	int maxBear = pHero->GetBearPoint();
	string sBear = UtilTools::GET_TEXT_FROM_LANG(524);
	sBear+=":";
	sBear += UtilTools::IntToString(maxBear -surplusBear);
	sBear+="/";
	sBear+= UtilTools::IntToString(maxBear);
	mEquiBear->setString(sBear.c_str());

	string sNum;
	sNum = UtilTools::IntToString(usedNum);
	sNum +="/";
	sNum+=UtilTools::IntToString(EQUIP_MAX_NUM);
	mEquiNum->setString(sNum.c_str());
}

void HeroEquipUIView::changeCheck(CCObject* pSender)
{

	CCSprite *checkItem = (CCSprite *)(((CCNode *)pSender)->getUserData());

	const ItemEquip *pItem = (ItemEquip *)checkItem->getUserData();

	checkItem->setVisible( !checkItem->isVisible() );

	if( checkItem->isVisible() )
		usedNum ++;
	else
		usedNum --; 

	string sNum;
	sNum = UtilTools::IntToString(usedNum);
	sNum +="/";
	sNum+=UtilTools::IntToString(mCurHeroTotal);
	mEquiNum->setString(sNum.c_str());


	bool flag = false;
	vector<const Item *>::iterator iter = mSelectEqui.begin();
	for (;iter!=mSelectEqui.end();iter++)
	{
		if ((*iter)->GetGuid() == pItem->GetGuid())
		{
			flag = true;
			mSelectEqui.erase(iter);
			break;
		}
	}

	if (!flag)
		mSelectEqui.push_back(pItem);

	checkEquipStatus();
}

void HeroEquipUIView::mButtonRmdEquip( cocos2d::CCObject* pSender )
{
	Item *sItem = (Item *)((CCNode *)pSender)->getUserData();
	if (!sItem)
	{
		return;
	}
	
	DataPool::GetSingleton()->SetSelectItem(sItem);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_SHOW);

}


void HeroEquipUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	CCSprite *checkItem = (CCSprite *)(((CCNode *)pSender)->getUserData());
	const ItemEquip *pItem = (ItemEquip *)checkItem->getUserData();

// 	bool bUnique = pItem->Rule(EM_UNIQUE);
// 	pItem->m_pTableData->_weight;
// 	pItem->Rule(EM_USEBIND)

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	if (usedNum == 6 && !checkItem->isVisible())
	{
		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(557), this , DIALOG_MODEL_SINGLE);
		dialog->setTag(DIALOG_EQUIP_NUM_MAX);
		addChild(dialog,10);

		return;
	}
	else
	{
		if (pItem->m_pTableData->_weight > surplusBear && !checkItem->isVisible())
		{

			if (DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetBearPoint() > 0)
			{
				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(721), this , DIALOG_MODEL_DOUBLE);
				dialog->setTag(DIALOG_EQUIP_NOT_BEAR_GOTODIS);
				addChild(dialog,10);
			}else
			{
				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(558), this , DIALOG_MODEL_DOUBLE);
				dialog->setTag(DIALOG_EQUIP_NOT_BEAR_GOTOBUY);
				addChild(dialog,10);
			}

			return;
		}
		else if(isUniqued((Item *)pItem) && !checkItem->isVisible())
		{
			char buff[MAX_STRING_BUFF_SIZE] = {0};
			sprintf(buff,UtilTools::GET_TEXT_FROM_LANG(559),pItem->GetName());
			ModalDialogView *dialog = ModalDialogView::createDialog(buff, this , DIALOG_MODEL_SINGLE);
			dialog->setTag(DIALOG_EQUIP_ONLY);
			addChild(dialog,10);

			return;
		}
		
	}

	if(!pItem->isBindEquip() &&pItem->Rule(EM_USEBIND) && !checkItem->isVisible())
	{
		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(535), this);
		dialog->setDailogUserData(pSender);
		dialog->setTag(DIALOG_EQUIP_BIND);
		addChild(dialog,10);
	}
	else
	{
		changeCheck(pSender);
	}

	guideLayer = NULL;


}

void HeroEquipUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void HeroEquipUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

bool HeroEquipUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	vector<const Item*>  itemlist;
	DataPool::GetSingleton()->getObjectManager()->getHeroCanUseEquips(pHero,itemlist);
	int size = itemlist.size();


	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();
	
	int lineIndex = 0;
	int columnIndex = 0;

	const Item *pItem;
 
	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{

		pItem = itemlist[size - 1 - i];
		if (!pItem)
		{
			continue;
		}

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pItem->GetIcon(), pItem->GetIcon(), this, menu_selector(HeroEquipUIView::itemInfoCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 
		menuItem->setScale(0.850f);

		//CCSprite *itemBg = CCSprite::create("equipmentBK.png");
		//itemBg->setScale(1.15f);
		//itemBg->setPosition(ccp(menuItem->getContentSize().width * 0.5f, menuItem->getContentSize().height * 0.5f));
		//menuItem->addChild(itemBg);
		 
		CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemPos ); 
			pPage->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(menuItem->getScale());
		} 


		if (pItem->isBindEquip())
		{
			CCSprite *bindSprite = CCSprite::create("n_equip_bind.png");
			CCPoint bPos = cocos2d::ccpAdd(itemPos,ccp(-menuItem->getContentSize().width *0.4,menuItem->getContentSize().height*0.4));
			bindSprite->setPosition(bPos);
			bindSprite->setTag(i+BIND_SPRITE_TAG);
			pPage->addChild(bindSprite,menu->getZOrder()+1);
		}
		
		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setPosition( itemPos );		
		checkItem->setUserData( (void *)(pItem) );
		checkItem->setVisible(pHero->ISEquiped((ItemEquip *)pItem));
		checkItem->setScale(0.70f);

		pPage->addChild( checkItem, menu->getZOrder()+1);


		menuItem->setUserData(checkItem);
		mEquipItems.push_back(menuItem);

		menu->addChild( menuItem );

		//剛進入英雄出裝的裝備的框
		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(menuItem->getPosition());
		//equipBG->setScale(1.15f);
		equipBG->setZOrder(menu->getZOrder()+1);
		pPage->addChild(equipBG);

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

	if (nPage == totalPage -1)
	{
		checkEquipStatus();
		 guideLayer = X_NULL;



		 X_INT tipId = ((HeroEquipUI *)this->getUserData())->getTipId();
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
				if (tipId == 12)
				{
					int index = 0;
					int iSize = mEquipItems.size();
					if (iSize ==0) { return true;}

					guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroEquipUIView::itemInfoCallBack),mEquipItems[index]);
					guideLayer->setPosition(getPosition());
					addChild(guideLayer);
				}
			}
		}


		if (guideLayer)
		{
			guideLayer->setZOrder(LAYER_MAX_ZORDER);
		}

	}
	

	return true;
}
void HeroEquipUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void HeroEquipUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
}

void HeroEquipUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	int iTag = pSender->getTag();

	switch (iTag)
	{
	case DIALOG_EQUIP_BIND:
		{
			CCNode *pObj = (CCNode *)pSender->getDailogUserData();

			changeCheck(pObj);
			pSender->closeDialogView();

			break;
		}
	case DIALOG_EQUIP_NOT_BEAR_GOTOBUY:
		{
			vector<string> str;str.clear();
			str.push_back(UtilTools::IntToString(EM_ACTION));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_SHOW,str);
			pSender->closeDialogView();
		}
		break;
	case DIALOG_EQUIP_NOT_BEAR_GOTODIS:
		{ 
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_SHOW);
			pSender->closeDialogView();
		}
		break;
	case DIALOG_EQUIP_ONLY:
	case DIALOG_EQUIP_NUM_MAX:
		{
			pSender->closeDialogView();
			break;
		}
	default:
		break;
	}
		
	
}
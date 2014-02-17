#include "./ui/equipmentSellUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h" 
#include "./object/Item.h"
#include "./object/ItemEquip.h"
#include "./base/UtilTools.h"
#include "./game/GameHelper.h"
#include "./ui/element/CCMenuEx.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.050f)
#define CONTENT_POS_Y            (0.190f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.54f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.28f)
#define ITEM_IMAGE_OFFSET_Y      (0.000f)

#define ITEM_NAME_OFFSET_X       (-0.20f)
#define ITEM_NAME_OFFSET_Y       (0.045f)

#define ITEM_DESC_OFFSET_X       (-0.20f)//(-0.20f)
#define ITEM_DESC_OFFSET_Y       (-0.030f)

#define ITEM_COUNT_OFFSET_X      (-0.20f)//(0.25f)
#define ITEM_COUNT_OFFSET_Y      (-0.05)//(0.045f)

#define ITEM_TEXT_SIZE_X         (0.68f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

const static  ccColor3B ccCOLOR_YELLOW={247,206,0}; //»ÆÉ«
const static  ccColor3B ccCOLOR_GREEN={166,196,23};  //ÂÌÉ«
const static  ccColor3B ccCOLOR_WHITE= {255,255,255}; //°×É«

equipmentSellUIView::equipmentSellUIView()
{
	mContent = NULL;
	
}

equipmentSellUIView::~equipmentSellUIView()
{
}

void equipmentSellUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler equipmentSellUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip0", equipmentSellUIView::onButtonEquip0);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip1", equipmentSellUIView::onButtonEquip1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip2", equipmentSellUIView::onButtonEquip2);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquipSell", equipmentSellUIView::onButtonEquipSell);
 
	
    return NULL;    
}

SEL_CCControlHandler equipmentSellUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void equipmentSellUIView::onButtonEquip0(cocos2d::CCObject * pSender)
{
	vector<string> str;
	str.clear();
	str.push_back("0");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_SHOW,str);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void equipmentSellUIView::onButtonEquip1(cocos2d::CCObject * pSender)
{
	vector<string> str;
	str.clear();
	str.push_back("1");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_SHOW,str);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void equipmentSellUIView::onButtonEquip2(cocos2d::CCObject * pSender)
{
	vector<string> str;
	str.clear();
	str.push_back("2");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_SHOW,str);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
 

 
void equipmentSellUIView::onButtonEquipSell( cocos2d::CCObject* pSender )
{
	mSellEquipItems.clear();
	X_INT num = mAllItemNum.size();
	X_INT equipNum = 0;
	for (X_INT i =0;i<num;i++)
	{
		equipNum = mAllItemNum[i];
		if (equipNum<=0) continue;

		ItemEquip * pEquip = static_cast< ItemEquip*> (mAllItemlist[i]);
		if (!pEquip)
		{
			continue;
		}
		X_INT size = mAllTrueItemlist[pEquip->GetTableID()].size();
		equipNum = equipNum > size ?size:equipNum;
		for (X_INT k =0;k<equipNum;k++)
		{
			 mSellEquipItems.push_back(mAllTrueItemlist[pEquip->GetTableID()][k]);
		}
	
	}

	if (mSellEquipItems.empty())
	{
		char buff[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buff,UtilTools::GET_TEXT_FROM_LANG(594));
		ModalDialogView *dialog = ModalDialogView::createDialog(buff,this,DIALOG_MODEL_SINGLE);
		addChild(dialog,10);
	}
	else
	{
		X_INT totalGold = 0;
		for (X_UINT i = 0; i < mSellEquipItems.size(); i ++)
		{
			const Item *pItem = mSellEquipItems.at(i);
			if(pItem)
				totalGold += pItem->GetSalePrice();
		}
		

		char buff[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buff,UtilTools::GET_TEXT_FROM_LANG(593),totalGold);
		ModalDialogView *dialog = ModalDialogView::createDialog(buff,this);
		addChild(dialog,10);
	}
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	
}

bool equipmentSellUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	return false;
}

bool equipmentSellUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

// on "init" you need to initialize your instance
bool equipmentSellUIView::init()
{
    bool bRet = true;

    return bRet;
}

void equipmentSellUIView::onDataUpdate( bool isDataValid )
{

	
	if( !isDataValid )
	{
		//clear();
		return;
	}

	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	SelfBagData*  pBag =    DataPool::GetSingleton()->getBagData();
	X_UINT size = pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);

	mAllItemlist.clear();
	mAllItemNum.clear();
	mSellEquipItems.clear();
	mAllTrueItemlist.clear();
	ItemEquip *pItem;


	for (X_UINT i = 0 ; i< size ;i++)
	{
		pItem = (ItemEquip*)(pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP));
		if (pItem&&!pItem->isEquiped())
		{
			vector<Item*>::iterator ifind  =  find_if( mAllItemlist.begin(),mAllItemlist.end(),TableId_Equal<Item>(pItem));
			if(ifind == mAllItemlist.end())
			{
				mAllItemlist.push_back(pItem);
			} 
			mAllTrueItemlist[pItem->GetTableID()].push_back(pItem);
		}
	}
	size = mAllItemlist.size();

	sort(mAllItemlist.begin(),mAllItemlist.end(),sortSellEquip);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 

	CCMenuHoldEx *menu = CCMenuHoldEx::create();CCMenuHoldEx::mTime = 0.1f;
	menu->setPosition(CCPointZero);
	// 	layer->addChild(menu);

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	mAdddisableItems.resize(size,0);
	mSubdisableItems.resize(size,0);
	mLables.resize(size,0);
	mSelectNumLables.resize(size,0);
	for( X_UINT i = 0; i < size; i++ )
	{
		pItem = static_cast<ItemEquip*> (mAllItemlist[i]);
		mAllItemNum.push_back(0);
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		itemBackGround->setPosition( itemDockPos );
		layer->addChild( itemBackGround );
 

		CCSprite *Item = CCSprite::create( pItem->GetIcon() );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		Item->setPosition( itemImagePos ); 
		Item->setUserData( (void *)pItem );
		layer->addChild( Item );

		CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemImagePos ); 
			layer->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(Item->getScale());
		} 

		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(Item->getPosition());
		equipBG->setScale(1.15f);
		layer->addChild(equipBG);
 
		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * (ITEM_NAME_OFFSET_Y - 0.001)) );
		mName->setPosition( itemNamePos );
		mName->setColor(ccCOLOR_GREEN);

// 		ccColor3B color3;
// 		UtilTools::strToColor(pItem->GetColor(),color3.r,color3.g,color3.b);
// 		mName->setColor(color3);

		layer->addChild( mName );

	/*	

 		//CCLabelTTF* mbindDes = CCLabelTTF::create( "aaaaa", FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		CCLabelTTF* mbindDes = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(532),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		mbindDes->setAnchorPoint( ccp( 0, 0.5f ) );
		mbindDes->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemBindDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (ITEM_DESC_OFFSET_Y + 0.03)) );
		mbindDes->setPosition( itemBindDescPos );
		mbindDes->setColor(ccCOLOR_YELLOW);
		layer->addChild( mbindDes );

		 	string str = "" ;
		 	if(pItem->isBindEquip())
		 	{
		 		ObjectHero * pHero =(ObjectHero *) DataPool::GetSingleton()->getObjectManager()->FindInstance(OBJECT_TYPE_HERO,pItem->GetItemOwnerGUID());
		 		if (pHero)
		 		{
		 			str = pHero->GetName();
		 		}
		 	 
		 	}else
		 	{
				str = UtilTools::GET_TEXT_FROM_LANG(534);
		 	}


		CCLabelTTF* mbind = CCLabelTTF::create(str.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24 );
		mbind->setAnchorPoint( ccp( 0, 0.5f ) );
		mbind->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemBindPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (-0.020), winSize.height * (ITEM_DESC_OFFSET_Y + 0.03)) ) ;
		mbind->setPosition( itemBindPos );
		layer->addChild( mbind );*/


		CCLabelTTF* mNumDes = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(723),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		mNumDes->setAnchorPoint( ccp( 0, 0.5f ) );
		mNumDes->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemNumDesPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (ITEM_DESC_OFFSET_Y + 0.03)) );
		mNumDes->setPosition( itemNumDesPos );
		mNumDes->setColor(ccCOLOR_YELLOW);
		layer->addChild( mNumDes );
  
		X_CHAR num[24] = {0};
		sprintf(num,"%d/%d",0,mAllTrueItemlist[pItem->GetTableID()].size());
		
		CCLabelBMFont* mNum = CCLabelBMFont::create( num, FNT_NAME_LARGEGREEN );//CCLabelTTF::create(num,FONT_NAME_ARIAL_BOLD,FONT_SIZE_24 );
		mNum->setAnchorPoint( ccp( 0, 0.5f ) );
		//mNum->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemmNumPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (-0.060), winSize.height * (ITEM_DESC_OFFSET_Y + 0.03)) ) ;
		mNum->setPosition( itemmNumPos );
		mNum->setScale(SCALE_BMF);
		layer->addChild( mNum );
		mLables[i] = mNum;

		CCLabelTTF* mDesc = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(533), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (ITEM_DESC_OFFSET_Y - 0.039)) );
		mDesc->setPosition( itemDescPos );
		mDesc->setColor(ccCOLOR_YELLOW);
		layer->addChild( mDesc );

		CCSprite *glod = CCSprite::create("goldCoin.png");
		glod->setPosition(ccpAdd( itemDockPos, CCPointMake( winSize.width * (-0.02), winSize.height * (ITEM_DESC_OFFSET_Y - 0.014)) ));
		layer->addChild(glod);

		CCLabelTTF* mCoin = CCLabelTTF::create(UtilTools::IntToString(pItem->GetSalePrice()).c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24 );
		mCoin->setAnchorPoint( ccp( 0, 0.5f ) );
		mCoin->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemCoinPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (0.01), winSize.height * (ITEM_DESC_OFFSET_Y - 0.013)) ) ;
		mCoin->setPosition( itemCoinPos );
		mCoin->setColor(ccCOLOR_YELLOW);
		layer->addChild( mCoin );

	 
		/*CCMenuItemImage *menuItemUse = CCMenuItemImage::create( "n_choose_bg.png", "n_choose_bg.png", this, menu_selector(equipmentSellUIView::sellCallBack) );  
		CCPoint itemEvolvePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.26, winSize.height * ITEM_IMAGE_OFFSET_Y ) );//(-0.0075)
		menuItemUse->setPosition( itemEvolvePos ); 
		menu->addChild( menuItemUse );

		CCSprite *itemUseText = CCSprite::create( "n_choose_ok.png" );
		itemUseText->setPosition( menuItemUse->getPosition());
		layer->addChild( itemUseText,menu->getZOrder()+1);
		itemUseText->setVisible(false);

		itemUseText->setUserData(pItem);
		menuItemUse->setUserData(itemUseText);
		*/


		CCMenuItemImage *menuItemAdd = CCMenuItemImage::create( "n_add_button.png", "n_add_button.png", this, menu_selector(equipmentSellUIView::addCallBack) );  
		CCPoint itemAddPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.30, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItemAdd->setPosition( itemAddPos ); 
		menuItemAdd->setUserData( (void *)i );
		menu->addChild( menuItemAdd );

		CCLabelTTF* textBuyNum = CCLabelTTF::create( "0",FONT_NAME_ARIAL_BOLD,FONT_SIZE_24 );
		textBuyNum->setAnchorPoint( ccp( 0.5, 0.5f ) );
		textBuyNum->setHorizontalAlignment(kCCTextAlignmentLeft);
		CCPoint itemBuyNumPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.21, winSize.height * ITEM_IMAGE_OFFSET_Y) ) ;
		textBuyNum->setPosition( itemBuyNumPos );
		textBuyNum->setColor(ccCOLOR_YELLOW);
		layer->addChild( textBuyNum );
		mSelectNumLables[i] = textBuyNum;

		CCMenuItemImage *menuItemSub = CCMenuItemImage::create( "n_sub_button.png", "n_sub_button.png", this, menu_selector(equipmentSellUIView::subCallBack) );  
		CCPoint itemSubPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.12, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItemSub->setPosition( itemSubPos ); 
		menuItemSub->setUserData( (void *)i );
		menu->addChild( menuItemSub );
		menuItemSub->setEnabled(false);
		menuItemSub->setColor(ICON_COLOR_GRAY);
		mAdddisableItems[i] = menuItemAdd;
		mSubdisableItems[i] = menuItemSub;
	}

	layer->addChild(menu);

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * (CONTENT_VIEW_SIZE_Y + 0.075)) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * (CONTENT_POS_X + 0.01), winSize.height * (CONTENT_POS_Y + 0.001)) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	addChild( mContent );

	
}
void equipmentSellUIView::addCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;
	 int index = (int)(((CCNode *)pSender)->getUserData());
	 ItemEquip * pEquip = static_cast< ItemEquip*> (mAllItemlist[index]);
	 X_INT nums =  mAllTrueItemlist[pEquip->GetTableID()].size();
	if (mAllItemNum[index] < nums)
	{
		mAllItemNum[index] += 1;
		if (mAllItemNum[index] == 1)
		{
			mSubdisableItems[index]->setEnabled(true);
			mSubdisableItems[index]->setColor(ccWHITE);
		}
		if (mAllItemNum[index] == nums)
		{
			((CCMenuItemImage *)pSender)->setEnabled(false);
			((CCMenuItemImage *)pSender)->setColor(ICON_COLOR_GRAY);
		}
	} 

	X_CHAR num[24] = {0};
	sprintf(num,"%d/%d",mAllItemNum[index],nums);
	mLables[index]->setString(num);
	sprintf(num,"%d",mAllItemNum[index]);
	mSelectNumLables[index]->setString(num);

}
void equipmentSellUIView::subCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;

	int index = (int)(((CCNode *)pSender)->getUserData());
	ItemEquip * pEquip = static_cast< ItemEquip*> (mAllItemlist[index]);
	 X_INT nums =  mAllTrueItemlist[pEquip->GetTableID()].size();
	if (mAllItemNum[index]  >  0 )
	{
		mAllItemNum[index] -= 1;
		if (mAllItemNum[index] == nums -1)
		{
			mAdddisableItems[index]->setEnabled(true);
			mAdddisableItems[index]->setColor(ccWHITE);
		}
		if (mAllItemNum[index] == 0)
		{
			((CCMenuItemImage *)pSender)->setEnabled(false);
			((CCMenuItemImage *)pSender)->setColor(ICON_COLOR_GRAY);
		}
	} 
	X_CHAR num[24] = {0};
	sprintf(num,"%d/%d",mAllItemNum[index],nums);
	mLables[index]->setString(num);
	sprintf(num,"%d",mAllItemNum[index]);
	mSelectNumLables[index]->setString(num);
}
bool equipmentSellUIView::sortSellEquip(Item *pItem1,Item *pItem2)
{
	return pItem1->GetSalePrice() < pItem2->GetSalePrice();
}

void equipmentSellUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
// 	if( mContent->mIsMoved )
// 		return;
}

void equipmentSellUIView::sellCallBack( cocos2d::CCObject* pSender )
{
 
	if( mContent->mIsMoved )
	 		return;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	CCSprite *checkSprite = (CCSprite *)(((CCNode *)pSender)->getUserData());
	Item *pItem = static_cast<Item*> (checkSprite->getUserData());

	if (!checkSprite->isVisible())
	{
		mSellEquipItems.push_back(pItem);
	}
	else
	{
		vector<const Item *>::iterator iter;
		iter = std::find(mSellEquipItems.begin(),mSellEquipItems.end(),pItem);
		if (iter != mSellEquipItems.end())
		{
			mSellEquipItems.erase(iter);
		}
	}

	checkSprite->setVisible(!checkSprite->isVisible());
 
}

void equipmentSellUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	if (mSellEquipItems.empty())
	{
		pSender->closeDialogView();
		return;
	}
	SendLogicPacket::SaleEquip(mSellEquipItems);
	pSender->closeDialogView();
}
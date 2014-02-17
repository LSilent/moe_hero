#include "./ui/secretStoreUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h" 
#include "./object/Item.h"
#include "./base/UtilTools.h"
#include "./game/GameHelper.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.060f)
#define CONTENT_POS_Y            (0.166f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.52f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.175f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.270f)//(-0.33f)
#define ITEM_IMAGE_OFFSET_Y      (-0.003f)//(0.024f)

#define ITEM_BUY_OFFSET_X        (0.225f)
#define ITEM_BUY_OFFSET_Y        (-0.040f)

#define ITEM_NAME_OFFSET_X       (-0.18f)
#define ITEM_NAME_OFFSET_Y       (0.055f)

#define ITEM_DESC_OFFSET_X       (-0.18f)
#define ITEM_DESC_OFFSET_Y       (-0.010f)

#define ITEM_COIN_OFFSET_X       (-0.15f)
#define ITEM_COIN_OFFSET_Y       (-0.04f)

#define ITEM_PRICE_OFFSET_X      (-0.115f)
#define ITEM_PRICE_OFFSET_Y      (-0.042f)

#define ITEM_TEXT_SIZE_X         (0.50f)
#define ITEM_TEXT_SIZE_Y         (0.08f)


#define  DIALOG_TAG_ITEM_NUM	 3000
#define  DIALOG_TAG_ITEM_GOLD	 3001



//for test
typedef struct {
	int id;
	std::string name;
	std::string desc;
	std::string image;

	int price;
} itemInfo;

SecretStoreUIView::SecretStoreUIView()
: mMainStatus(NULL)
{
	mContent = NULL;
}

SecretStoreUIView::~SecretStoreUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
}


void SecretStoreUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler SecretStoreUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruitHero", SecretStoreUIView::onButtonRecruitHero);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStore", SecretStoreUIView::onButtonStore);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHeroBook", SecretStoreUIView::onButtonHeroBook);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCharge", SecretStoreUIView::onButtonCharge);

    return NULL;    
}

SEL_CCControlHandler SecretStoreUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void SecretStoreUIView::onButtonRecruitHero(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SecretStoreUIView::onButtonStore(cocos2d::CCObject * pSender)
{
	// ignore
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SecretStoreUIView::onButtonHeroBook(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROBOOK_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SecretStoreUIView::onButtonCharge(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool SecretStoreUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool SecretStoreUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   /* if (pTarget == this)
    {
        if (0 == strcmp(pMemberVariableName, "mCustomPropertyInt"))
        {
            this->mCustomPropertyInt = pCCBValue->getIntValue();
            CCLog("mCustomPropertyInt = %d", mCustomPropertyInt);
            bRet = true;
        }
        else if ( 0 == strcmp(pMemberVariableName, "mCustomPropertyFloat"))
        {
            this->mCustomPropertyFloat = pCCBValue->getFloatValue();
            CCLog("mCustomPropertyFloat = %f", mCustomPropertyFloat);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyBoolean"))
        {
            this->mCustomPropertyBoolean = pCCBValue->getBoolValue();
            CCLog("mCustomPropertyBoolean = %d", mCustomPropertyBoolean);
            bRet = true;
        }
        else if ( 0  == strcmp(pMemberVariableName, "mCustomPropertyString"))
        {
            this->mCustomPropertyString = pCCBValue->getStringValue();
            CCLog("mCustomPropertyString = %s", mCustomPropertyString.c_str());
            bRet = true;
        }
        
    }*/

    return bRet;
}

// on "init" you need to initialize your instance
bool SecretStoreUIView::init()
{
    bool bRet = true;

   

    return bRet;
}
 void SecretStoreUIView::UpdateStates()
 {
	 mMainStatus->onDataUpdate(true);
 }
void SecretStoreUIView::onDataUpdate( bool isDataValid )
{
	
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
    ShopData*  pShop =    DataPool::GetSingleton()->getShopData();
	X_INT size = pShop->GetShopSize(EM_SHOP_ID_NORMAL);
	if (size <= 0)
	{
		return;
	}
	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create();
	CCMenuEx *menu = CCMenuEx::create(); 
	

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	Item *pItem = X_NULL;

	for( X_INT i = 0; i < size; i++ )
	{
		pItem = pShop->getItem(EM_SHOP_ID_NORMAL,i);
		if (!pItem)continue;
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pItem->GetIcon(), pItem->GetIcon(), this, menu_selector(SecretStoreUIView::itemInfoCallBack) );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItem->setPosition( itemImagePos ); 
		menuItem->setUserData( (void *)pItem );
		menu->addChild( menuItem );



		CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemImagePos); 
			layer->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(menuItem->getScale());
		} 


		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(menuItem->getPosition());
		layer->addChild(equipBG);
		equipBG->setZOrder(menu->getZOrder()+1);
		equipBG->setScale(1.15f);

		CCMenuItemImage *menuItemBuy = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(SecretStoreUIView::buyCallBack) );  
		CCPoint itemBuyPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUY_OFFSET_X, winSize.height * ITEM_BUY_OFFSET_Y ) );
		menuItemBuy->setPosition( itemBuyPos ); 
		menuItemBuy->setUserData( (void *)pItem );
		menuItemBuy->setScale(0.7f);
		menu->addChild( menuItemBuy );

		CCSprite *pBuyText = CCSprite::create("n_pur_text.png");//n_pur_text.png
		pBuyText->setPosition(itemBuyPos);
		layer->addChild(pBuyText,1);

		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL_BOLD, 24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		layer->addChild( mName );
		//ccColor3B Color = ccWHITE;
  		//UtilTools::strToColor(pItem->GetColor(),Color.r,Color.g,Color.b);
		mName->setColor(CCCOLOR_YELLOW);

		CCLabelTTF* mDesc = CCLabelTTF::create(pItem->GetInfo(), FONT_NAME_ARIAL_BOLD, 20, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		mDesc->setColor(ccWHITE);
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		mDesc->setColor(CCCOLOR_GREEN);
		layer->addChild( mDesc );

		

		CCSprite *itemCoin = CCSprite::create( "goldCoin.png" );
		CCPoint itemCoinPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_COIN_OFFSET_X, winSize.height * ITEM_COIN_OFFSET_Y ) );
		itemCoin->setPosition( itemCoinPos );
		layer->addChild( itemCoin );

		char buff[MAX_STRING_BUFF_SIZE];
		
		sprintf( buff, UtilTools::GET_TEXT_FROM_LANG(713), pItem->GetPrice() );
		CCLabelTTF* mPrice = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		mPrice->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemPricePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_PRICE_OFFSET_X, winSize.height * ITEM_PRICE_OFFSET_Y ) );
		mPrice->setPosition( itemPricePos );
		mPrice->setColor(CCCOLOR_WHITE);
		layer->addChild( mPrice );
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero );  
	layer->addChild( menu );

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	addChild( mContent );
}

void SecretStoreUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	 const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	int i = 0;
}

void SecretStoreUIView::buyCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	
	
	Item * pItem = static_cast<Item*> (((CCNode *)pSender)->getUserData());
// 	 SendLogicPacket::BuyItem(pItem);

	DialogBuyView *dailogBuy = DialogBuyView::createDialog(pItem,this);
	dailogBuy->setTag(DIALOG_TAG_ITEM_NUM);
	dailogBuy->setDailogUserData(pItem);
	addChild(dailogBuy,10);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

void SecretStoreUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	DialogBuyView *dialogBuy = (DialogBuyView *)pSender;

	int iTag = dialogBuy->getTag();

	if (iTag == DIALOG_TAG_ITEM_NUM)
	{
		ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
		PlayerData* pData = pSelf->playerData();

		Item * pItem = (Item *)dialogBuy->getDailogUserData();

		int gold_ = dialogBuy->getMatNum() *pItem->GetPrice() ;
		if (gold_ > pData->GetGold())
		{
			ModalDialogView *dailog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(550),this);
			dailog->setTag(DIALOG_TAG_ITEM_GOLD);
			addChild(dailog,11);
		}
		else
		{
			SendLogicPacket::BuyItem(EM_SHOP_ID_NORMAL, dialogBuy->getItem(),dialogBuy->getMatNum());
		}
	}
	else if(iTag == DIALOG_TAG_ITEM_GOLD)
	{
		EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
	}

	pSender->closeDialogView();
}
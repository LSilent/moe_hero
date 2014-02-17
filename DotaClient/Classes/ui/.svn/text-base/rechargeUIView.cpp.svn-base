#include "./ui/rechargeUIView.h"
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
#include "./base/Sdk_Handler.h"
#include "./datapool/DataPool.h"
#include "./datapool/WoodData.h"


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

#define ITEM_IMAGE_OFFSET_X      (-0.265f)//(-0.33f)
#define ITEM_IMAGE_OFFSET_Y      (-0.0015f)//(0.024f)

#define ITEM_BUY_OFFSET_X        (0.25f)
#define ITEM_BUY_OFFSET_Y        (-0.030f)//(-0.050f)

#define ITEM_NAME_OFFSET_X       (-0.20f)
#define ITEM_NAME_OFFSET_Y       (0.060f)

#define ITEM_DESC_OFFSET_X       (-0.18f)
#define ITEM_DESC_OFFSET_Y       (0.03f)

#define ITEM_COIN_OFFSET_X       (-0.18f)
#define ITEM_COIN_OFFSET_Y       (-0.050f)

#define ITEM_PRICE_OFFSET_X      (-0.13f)
#define ITEM_PRICE_OFFSET_Y      (-0.052f)

#define ITEM_TEXT_SIZE_X         (0.60f)
#define ITEM_TEXT_SIZE_Y         (0.03f)



//for test
typedef struct {
	int id;
	std::string name;
	std::string desc;
	std::string image;

	int price;
} itemInfo;

rechargeUIView::rechargeUIView()
: mMainStatus(NULL)
{
	mContent = NULL;
}

rechargeUIView::~rechargeUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
}


void rechargeUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler rechargeUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruitHero", rechargeUIView::onButtonRecruitHero);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStore", rechargeUIView::onButtonStore);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHeroBook", rechargeUIView::onButtonHeroBook);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCharge", rechargeUIView::onButtonCharge);

    return NULL;    
}

SEL_CCControlHandler rechargeUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void rechargeUIView::onButtonRecruitHero(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void rechargeUIView::onButtonStore(cocos2d::CCObject * pSender)
{
	// ignore
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SECRETSTORE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void rechargeUIView::onButtonHeroBook(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROBOOK_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void rechargeUIView::onButtonCharge(cocos2d::CCObject * pSender)
{
	//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SECRETSTORE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool rechargeUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool rechargeUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
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
bool rechargeUIView::init()
{
    bool bRet = true;

   

    return bRet;
}

void rechargeUIView::onDataUpdate( bool isDataValid )
{
	
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}
 

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CHARGE);

	const stDBC_FILE_CHARGE	*m_pTableData = X_NULL;

	X_INT sizeNum = pDataFile->GetRecordsNum();


	const  DataBase* pDataFileExchange  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EXCHANGE);
	const stDBC_FILE_EXCHANGE	*m_pTableDataEx = X_NULL;
	X_INT sizeNumEx = pDataFileExchange->GetRecordsNum();
	if (sizeNum <= 0)
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
	

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * (sizeNum + sizeNumEx) * ITEM_SPACE_DELTA_Y );


	for (X_INT i =0;i<sizeNum;i++)
	{
		m_pTableData = (const stDBC_FILE_CHARGE*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData)
		{
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		CCSprite *equipBG = CCSprite::create(m_pTableData->icon);
		equipBG->setPosition(itemImagePos);
		layer->addChild(equipBG);

		CCMenuItemImage *menuItemBuy = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(rechargeUIView::buyCallBack) );  
		CCPoint itemBuyPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUY_OFFSET_X, winSize.height * ITEM_BUY_OFFSET_Y ) );
		menuItemBuy->setPosition( itemBuyPos ); 
		menuItemBuy->setUserData((void *)m_pTableData);
		menuItemBuy->setScale(0.7f);
		menu->addChild( menuItemBuy );

		CCSprite *pBuyText = CCSprite::create("n_recharge_text.png");//n_pur_text.png
		pBuyText->setPosition(itemBuyPos);
		layer->addChild(pBuyText,1);
 
		CCLabelTTF* mDesc = CCLabelTTF::create(m_pTableData->name, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		mDesc->setColor(CCCOLOR_GREEN);
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		layer->addChild( mDesc );

        char buffGold[256] ={0};
		string getMoneyName1 = SdkHandler::getMoneyName1();
        sprintf(buffGold,getMoneyName1.c_str(),m_pTableData->costMoney);


		CCLabelTTF* mGold = CCLabelTTF::create(buffGold, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentRight );
		mGold->setAnchorPoint( ccp( 1, 0.5f ) );
		CCPoint itemGoldPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.33f, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mGold->setPosition( itemGoldPos );
		layer->addChild( mGold );
		string strDes = m_pTableData->des;
		if (strDes != "-1")
		{
			CCPoint itemCoinPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_COIN_OFFSET_Y ) );

			CCLabelTTF* mPrice = CCLabelTTF::create( m_pTableData->des, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 ,CCSizeMake( winSize.width * (0.35f), winSize.height * 0.1 ), kCCTextAlignmentLeft );
			mPrice->setAnchorPoint( ccp( 0, 0.5f ) );
			mPrice->setColor(CCCOLOR_YELLOW);
			mPrice->setPosition( itemCoinPos );
			layer->addChild( mPrice );
		}

		}
	}
	for (X_INT i =0;i< sizeNumEx;i++)
	{
		m_pTableDataEx = (const stDBC_FILE_EXCHANGE*)pDataFileExchange->GetFieldsByLineNum(i);
		if (m_pTableDataEx)
		{
			CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
			CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - (sizeNum+i) * ITEM_SPACE_DELTA_Y ) + contentSize.height );
			itemBackGround->setPosition( itemDockPos );
			itemBackGround->setScaleX(SCALE_X);
			itemBackGround->setScaleY(SCALE_Y);
			layer->addChild( itemBackGround );
			CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
			string str = m_pTableDataEx->icon;
//			string str = "n_recharge_wood.png";
// 			if (m_pTableDataEx->type == 1)
// 			{
// 				str = "n_recharge_gold.png";
// 			}
			CCSprite *equipBG = CCSprite::create(str.c_str());
			equipBG->setPosition(itemImagePos);
			layer->addChild(equipBG);

			CCMenuItemImage *menuItemBuy = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(rechargeUIView::exChangeCallBack) );  
			CCPoint itemBuyPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUY_OFFSET_X, winSize.height * ITEM_BUY_OFFSET_Y ) );
			menuItemBuy->setPosition( itemBuyPos ); 
			menuItemBuy->setUserData((void *)m_pTableDataEx);
			menuItemBuy->setScale(0.7f);
			menu->addChild( menuItemBuy );

			CCSprite *pBuyText = CCSprite::create("n_recharge_text.png");//n_pur_text.png
			pBuyText->setPosition(itemBuyPos);
			layer->addChild(pBuyText,1);

			CCLabelTTF* mDesc = CCLabelTTF::create(m_pTableDataEx->name, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
			mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
			CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
			mDesc->setPosition( itemDescPos );
			mDesc->setColor(CCCOLOR_GREEN);
			layer->addChild( mDesc );

			char buffGold[MAX_STRING_BUFF_SIZE]={0};
			sprintf(buffGold,UtilTools::GET_TEXT_FROM_LANG(619),m_pTableDataEx->costGem);
			CCLabelTTF* mGold = CCLabelTTF::create(buffGold, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentRight );
			mGold->setAnchorPoint( ccp( 1, 0.5f ) );
			CCPoint itemGoldPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.33f, winSize.height * ITEM_DESC_OFFSET_Y ) );
			mGold->setPosition( itemGoldPos );
			layer->addChild( mGold );
			string strDes = m_pTableDataEx->desc;
			if (strDes != "-1")
			{
				CCPoint itemCoinPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_COIN_OFFSET_Y ) );

				CCLabelTTF* mPrice = CCLabelTTF::create( m_pTableDataEx->desc, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 ,CCSizeMake( winSize.width * (0.38f), winSize.height * 0.1 ), kCCTextAlignmentLeft );
				mPrice->setAnchorPoint( ccp( 0, 0.5f ) );
				mPrice->setColor(CCCOLOR_YELLOW);
				mPrice->setPosition( itemCoinPos );
				layer->addChild( mPrice );
			}

		}
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

void rechargeUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	// const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	//int i = 0;
}
void rechargeUIView::exChangeCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;


	const stDBC_FILE_EXCHANGE* data = static_cast<stDBC_FILE_EXCHANGE*> (((CCNode *)pSender)->getUserData());
	if (data)
	{
		char str[256] = {0};
		string str1;
		if (data->type == 1)
		{
			sprintf(str,UtilTools::GET_TEXT_FROM_LANG(643),data->costGem,data->num,UtilTools::GET_TEXT_FROM_LANG(517));
			str1 = str;
		}else
		{
			sprintf(str,UtilTools::GET_TEXT_FROM_LANG(643),data->costGem,data->num,UtilTools::GET_TEXT_FROM_LANG(644));
			str1 = str;
			WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
			if (pWoodData)
			{
				 SelfWoodData *pSelf = pWoodData->GetSelfWoodData();
				if (pSelf)
				{
				     bool b = (data->num +  pSelf->m_WoodData.m_WoodNum) > pSelf->m_WoodCapacity ;
					 if ( b )
					 {
						 str1 += UtilTools::GET_TEXT_FROM_LANG(712);
					 }
				}
			}
		}
		m_BuyStates = EM_EXCHANGE;
		ModalDialogView * pView = ModalDialogView::createDialog(str1.c_str(),this);
		pView->setDailogUserData((void*)data);
		addChild(pView);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void rechargeUIView::buyCallBack( cocos2d::CCObject* pSender )
{
  
    // ignore if moved
	if( mContent->mIsMoved )
		return;
	
    
	const stDBC_FILE_CHARGE* data = static_cast<stDBC_FILE_CHARGE*> (((CCNode *)pSender)->getUserData());
	if (data)
	{
		char str[256] = {0};
		string moneyName = SdkHandler::getMoneyName();
        sprintf(str,moneyName.c_str(),data->costMoney,data->gold);
        m_BuyStates = EM_BUY;
        
        
		ModalDialogView * pView = ModalDialogView::createDialog(str,this);
		pView->setDailogUserData((void*)data);
		addChild(pView);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void rechargeUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
   if (m_BuyStates == EM_BUY)
   {
    const stDBC_FILE_CHARGE*  pdata = (const stDBC_FILE_CHARGE *)pSender->getDailogUserData();
		if (!pdata)
		{
			return;
		}
   
    
		//appStorePurchase::startBuyProductWithID(pdata->Productid);
		//appStorePurchase::getProductListInfo();
		SendLogicPacket::Charge(pdata->id);
		
   }else  if (m_BuyStates == EM_EXCHANGE)
   {
	   const stDBC_FILE_EXCHANGE*  pdata = (const stDBC_FILE_EXCHANGE *)pSender->getDailogUserData();
	   if (!pdata)
	   {
		   return;
	   }
	   
		SendLogicPacket::ExChange(pdata->id);
   }




    pSender->closeDialogView();
}
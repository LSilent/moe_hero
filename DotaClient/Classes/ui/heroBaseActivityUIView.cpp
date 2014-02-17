#include "./ui/heroBaseActivityUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./ui/element/CCMenuEx.h"
#include "./datapool/SportsData.h"

#include "./game/GameHelper.h"
#include "element/LogicTouchItem.h"
#include "element/FightTips.h"
#include "./Packets/Wood/CGWoodAskPacket.h"
#include "heroBaseActivityUI.h"
#include "./GameResult.h"
#include "./object/ObjectSkill.h"

#include "./ui/element/CCScrollViewEx.h"
#include "./datapool/EquipOperator.h"
#include "./ui/element/ModalDialogView.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_ACT_NUM				 (3)

#define CONTENT_POS_X_1            (0.100f)
#define CONTENT_POS_Y_1            (0.858f)//(0.455f)

#define CONTENT_VIEW_SIZE_X_1      (0.80f)
#define CONTENT_VIEW_SIZE_Y_1      (0.2f)

#define ITEM_SPACE_DELTA_X_1       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y_1      (0.10f)

#define ITEM_START_X_1			 (0.09f) //(0.111f)
#define ITEM_START_Y_1             (0.06f)//(0.45f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            1



#define CONTENT_POS_X            (0.050f)
#define CONTENT_POS_Y            (0.02f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.60f)

#define ITEM_DOCK_X              (0.45f)
#define ITEM_SPACE_DELTA_Y       (0.20f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.25f)//(-0.33f)
#define ITEM_IMAGE_OFFSET_Y      (-0.005f)//(0.024f)

#define ITEM_SKILL_OFFSET_X       (0.25f)
#define ITEM_SKILL_OFFSET_Y      (-0.005f)

#define ITEM_NAME_OFFSET_X       (0.10f)
#define ITEM_NAME_OFFSET_Y       (0.035f)

#define ITEM_DESC_OFFSET_X       (0.10f)
#define ITEM_DESC_OFFSET_Y       (-0.032f)

#define ITEM_COIN_OFFSET_X       (-0.18f)
#define ITEM_COIN_OFFSET_Y       (-0.050f)

#define ITEM_PRICE_OFFSET_X      (-0.13f)
#define ITEM_PRICE_OFFSET_Y      (-0.052f)

#define ITEM_TEXT_SIZE_X         (0.50f)
#define ITEM_TEXT_SIZE_Y         (0.00f)

#define MAX_STRING_BUFF_SIZE     (128)

#define SHOP_ITEM_DOCK_X              (0.44f)
#define SHOP_ITEM_SPACE_DELTA_Y       (0.175f)
#define SHOP_ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define SHOP_ITEM_IMAGE_OFFSET_X      (-0.270f)//(-0.33f)
#define SHOP_ITEM_IMAGE_OFFSET_Y      (-0.003f)//(0.024f)

#define SHOP_ITEM_BUY_OFFSET_X        (0.225f)
#define SHOP_ITEM_BUY_OFFSET_Y        (-0.040f)

#define SHOP_ITEM_NAME_OFFSET_X       (-0.18f)
#define SHOP_ITEM_NAME_OFFSET_Y       (0.055f)

#define SHOP_ITEM_DESC_OFFSET_X       (-0.18f)
#define SHOP_ITEM_DESC_OFFSET_Y       (-0.010f)

#define SHOP_ITEM_COIN_OFFSET_X       (-0.15f)
#define SHOP_ITEM_COIN_OFFSET_Y       (-0.04f)

#define SHOP_ITEM_PRICE_OFFSET_X      (-0.115f)
#define SHOP_ITEM_PRICE_OFFSET_Y      (-0.042f)

#define SHOP_ITEM_TEXT_SIZE_X         (0.50f)
#define SHOP_ITEM_TEXT_SIZE_Y         (0.08f)

 #define  DIALOG_TAG_ITEM_NUM	 3000
#define  DIALOG_TAG_ITEM_GOLD	 3001

heroBaseActivityUIView::heroBaseActivityUIView()
{
	m_ContentNode = 0;
	m_NavContent = 0;
	mLayerSelect =0;
	mContent = 0;
	m_pWoodPVPHandler		= new HeroWoodPVPUIViewHandle(this);
	m_pMasterSchoolHandler	= new HeroMasterSchoolUIViewHandle(this);
	m_pIronsmithHandler = new HeroIronsmithUIViewHandle(this);
	m_pWoodShopHandler = new WoodShopUIViewHandle(this);
	
	guideLayer = NULL;
}

heroBaseActivityUIView::~heroBaseActivityUIView()
{
	CC_SAFE_RELEASE(m_ContentNode);
	CC_SAFE_RELEASE(mLayerSelect);
	CC_SAFE_DELETE(m_pWoodPVPHandler);
	CC_SAFE_DELETE(m_pMasterSchoolHandler);
	CC_SAFE_RELEASE(m_pIronsmithHandler);
	CC_SAFE_RELEASE(m_pWoodShopHandler);
}

void heroBaseActivityUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader)
{
   CreateNavItem();
}


SEL_MenuHandler heroBaseActivityUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonLeft", heroBaseActivityUIView::onButtonLeft);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRight", heroBaseActivityUIView::onButtonRight);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonWoodUpgrade", heroBaseActivityUIView::onButtonWoodUpgrade);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStart", heroBaseActivityUIView::onButtonGotoRob);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRematch", heroBaseActivityUIView::onButtonRematch);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRob", heroBaseActivityUIView::onButtonRob);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRevenge", heroBaseActivityUIView::onButtonRevenge);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHeroChange", heroBaseActivityUIView::onButtonHeroChange);


	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSkillLevelup", heroBaseActivityUIView::onButtonSkillLeveUp);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquipLevelup", heroBaseActivityUIView::onButtonEquipLeveUp);

	

	return NULL;    
}

SEL_CCControlHandler heroBaseActivityUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool heroBaseActivityUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode)
{
   
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePos",	CCNode *,m_ContentNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerSelect",	CCLayer *,mLayerSelect);
 
	
	m_pMasterSchoolHandler->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
	m_pWoodPVPHandler->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
	m_pIronsmithHandler->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
	m_pWoodShopHandler->onAssignCCBMemberVariable(pTarget,pMemberVariableName,pNode);
    return false;
}

bool heroBaseActivityUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}


// on "init" you need to initialize your instance
bool heroBaseActivityUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

void heroBaseActivityUIView::onButtonLeft(cocos2d::CCObject * pSender)
{
	m_NavContent->scrollToPrePage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void heroBaseActivityUIView::onButtonRight(cocos2d::CCObject * pSender)
{
	m_NavContent->scrollToNextPage();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void heroBaseActivityUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		return;
	}
	heroBaseActivityUI *pUi =  (heroBaseActivityUI*) (getUserData());
	if (!pUi)return;


	X_INT tipId = ((heroBaseActivityUI *)this->getUserData())->getTipId();
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
			case 37:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(heroBaseActivityUIView::onButtonGotoRob),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				HeroBaseActivityDataUpdate(pUi->m_BuilderIndex);
				break;
			case 38:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(heroBaseActivityUIView::onButtonRob),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				HeroBaseActivityDataUpdate(pUi->m_BuilderIndex);
				break;
			case 40:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(heroBaseActivityUIView::onButtonHeroChange),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				HeroBaseActivityDataUpdate(pUi->m_BuilderIndex);
				break;
			case 43:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(heroBaseActivityUIView::guideNavIronsmith),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 44:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(heroBaseActivityUIView::guideNavMasterSchool),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		HeroBaseActivityDataUpdate(pUi->m_BuilderIndex);
	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
}

void heroBaseActivityUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void heroBaseActivityUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}

bool heroBaseActivityUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	int size = EM_HEROBASE_TYPE_NUM;
	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	int lineIndex = 0;
	int columnIndex = 0;

	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{

		string titleIcon;
		switch (i)
		{
		case EM_HEROBASE_WOOD:
			titleIcon = "n_wood_icon.png";
			break;
		case EM_HEROBASE_MASTERSCHOOL:
			titleIcon = "n_masterschool_icon.png";
			break;
		case EM_HEROBASE_IRONSMITH:
			titleIcon = "n_ironsmith_icon.png";
			break;
		case EM_WOOD_SHOP:
			titleIcon = "n_shop_icon.png";
			break;
		default:
			break;
		}
	
		CCMenuItemImage *menuItem = CCMenuItemImage::create( titleIcon.c_str(),titleIcon.c_str(), this, menu_selector(heroBaseActivityUIView::NavItemCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X_1 - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y_1 - lineIndex * ITEM_SPACE_DELTA_Y_1 ));
		menuItem->setPosition( itemPos ); 
		menuItem->setScale(0.80f);
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

void heroBaseActivityUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void heroBaseActivityUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	
}
void heroBaseActivityUIView::NavItemCallBack( cocos2d::CCObject* pSender )
{
	heroBaseActivityUI *pUi =  (heroBaseActivityUI*) (getUserData());
	if (!pUi)return;

	pUi->m_BuilderIndex = (int)((CCNode *)pSender)->getUserData();
	switch (pUi->m_BuilderIndex)
	{
	case EM_HEROBASE_WOOD:
		SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_ENTER);
		break;
	case EM_HEROBASE_MASTERSCHOOL:

		break;
	case EM_HEROBASE_IRONSMITH:
		break;
	case EM_WOOD_SHOP:
		break;
	default:
		break;
	}
	HeroBaseActivityDataUpdate(	pUi->m_BuilderIndex);
}

void heroBaseActivityUIView::guideNavIronsmith( cocos2d::CCObject* pSender )
{
	guideLayer = NULL;
	HeroBaseActivityDataUpdate(EM_HEROBASE_IRONSMITH);
}
void heroBaseActivityUIView::guideNavMasterSchool( cocos2d::CCObject* pSender )
{
	guideLayer = NULL;
	HeroBaseActivityDataUpdate(	EM_HEROBASE_MASTERSCHOOL);
}

void heroBaseActivityUIView::CreateNavItem()
{
	unsigned int size = EM_HEROBASE_TYPE_NUM;

	mNagItems.clear();
	mNagItems.resize(size);

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X_1, winSize.height * CONTENT_VIEW_SIZE_Y_1);
	m_NavContent = CCScrollViewPage::create();
	m_NavContent->createContainer(this,totalPage,viewSize); 

	m_NavContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X_1, winSize.height * CONTENT_VIEW_SIZE_Y_1) );
	m_NavContent->setContentOffset(CCPointZero);
	m_NavContent->setDirection( kCCScrollViewDirectionHorizontal );
	m_NavContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X_1, winSize.height * CONTENT_POS_Y_1 ) );

	addChild( m_NavContent );

}

void heroBaseActivityUIView::HeroBaseActivityDataUpdate( X_INT type )
{
	SetAllLayerDisable();
	switch (type)
	{
	case EM_HEROBASE_WOOD:
		assert(m_pWoodPVPHandler != NULL);
		m_pWoodPVPHandler->HeroPVPDataUpdate();
		break;
	case EM_HEROBASE_MASTERSCHOOL:
		assert( m_pMasterSchoolHandler != NULL);
		m_pMasterSchoolHandler->MasterSchoolUpdate();
		break;
	case EM_HEROBASE_IRONSMITH:
		m_pIronsmithHandler->IronsmithUpdate();
		break;
	case EM_WOOD_SHOP:
		m_pWoodShopHandler->ShopUpdate();
		break;

	default:
		break;
	}
}


void heroBaseActivityUIView::onEnter()
{
	CCLayer::onEnter();

	schedule( schedule_selector(heroBaseActivityUIView::OnTick), 1.f );
}
void heroBaseActivityUIView::onExit()
{
	DataPool::GetSingleton()->SetSelectSkill(0);
	DataPool::GetSingleton()->SetSelectItem(0);
	unschedule( schedule_selector(heroBaseActivityUIView::OnTick) );

	BaseView::onExit();
}

void heroBaseActivityUIView::SetAllLayerDisable()
{
	m_pWoodPVPHandler->SetLayerDisable();
	m_pMasterSchoolHandler->SetLayerDisable();
	m_pIronsmithHandler->SetLayerDisable();
	m_pWoodShopHandler->SetLayerDisable();
	mLayerSelect->setVisible(false);
}

void heroBaseActivityUIView::onButtonWoodUpgrade(cocos2d::CCObject * pSender)
{
	m_pWoodPVPHandler->onButtonWoodUpgrade();
}
void heroBaseActivityUIView::onButtonGotoRob(cocos2d::CCObject * pSender)
{
	guideLayer = NULL;
	m_pWoodPVPHandler->onButtonGotoRob();
}
void heroBaseActivityUIView::onButtonRematch(cocos2d::CCObject * pSender)
{
	m_pWoodPVPHandler->onButtonRematch();
}
void heroBaseActivityUIView::onButtonRob(cocos2d::CCObject * pSender)
{
	guideLayer = NULL;
	m_pWoodPVPHandler->onButtonRob();
}
void heroBaseActivityUIView::onButtonRevenge(cocos2d::CCObject * pSender)
{
	m_pWoodPVPHandler->onButtonRevenge();
}
void heroBaseActivityUIView::OnTick( float time )
{
	m_pWoodPVPHandler->updateWoodLevelUpTime(time);
}

void heroBaseActivityUIView::onButtonHeroChange( cocos2d::CCObject * pSender )
{
	guideLayer = NULL;
	m_pWoodPVPHandler->onButtonChangeHero();
}

void heroBaseActivityUIView::onButtonSkillLeveUp( cocos2d::CCObject * pSender )
{
	m_pMasterSchoolHandler->onButtonSkillLeveUp();
}
void heroBaseActivityUIView::onButtonEquipLeveUp( cocos2d::CCObject * pSender )
{
	m_pIronsmithHandler->onButtonEquipLeveUp();
}

WoodShopUIViewHandle::WoodShopUIViewHandle( heroBaseActivityUIView* pUIView )
	: HeroBaseActivityUIViewHandle(pUIView)
	, m_ShopLayer(NULL)
{
	mContent = NULL;
}
WoodShopUIViewHandle::~WoodShopUIViewHandle()
{
	CC_SAFE_RELEASE(m_ShopLayer);
	 
}
void WoodShopUIViewHandle::SetLayerDisable()
{
	m_ShopLayer->setVisible(false);
}
 
	 
bool WoodShopUIViewHandle::onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode)
{

		CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerShop",	CCLayer *,m_ShopLayer);
	return false;
}
void WoodShopUIViewHandle::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	int i = 0;
}
void WoodShopUIViewHandle::buyCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;


	Item * pItem = static_cast<Item*> (((CCNode *)pSender)->getUserData());
	// 	 SendLogicPacket::BuyItem(pItem);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	DialogBuyView *dailogBuy = DialogBuyView::createDialog(pItem,this,EM_SHOP_MONEY_WOOD);
	dailogBuy->setTag(DIALOG_TAG_ITEM_NUM);
	dailogBuy->setDailogUserData(pItem);
	dailogBuy->setPositionY(-m_ShopLayer->getContentSize().height*0.25f);
	m_ShopLayer->addChild(dailogBuy,100);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}
void WoodShopUIViewHandle::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	DialogBuyView *dialogBuy = (DialogBuyView *)pSender;

	int iTag = dialogBuy->getTag();

	if (iTag == DIALOG_TAG_ITEM_NUM)
	{
		ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
		PlayerData* pData = pSelf->playerData();

		Item * pItem = (Item *)dialogBuy->getDailogUserData();

		int gold_ = dialogBuy->getMatNum() *pItem->GetPrice() ;
		if (gold_ > pData->GetWood())
		{
			ModalDialogView *dailog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(699),this);
			dailog->setTag(DIALOG_TAG_ITEM_GOLD);
			dailog->setPositionY(-m_ShopLayer->getContentSize().height*0.25f);
			m_ShopLayer->addChild(dailog,11);
		}
		else
		{
			SendLogicPacket::BuyItem(EM_SHOP_ID_WOOD,dialogBuy->getItem(),dialogBuy->getMatNum());
		}
	}
	else if(iTag == DIALOG_TAG_ITEM_GOLD)
	{
		EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
	}

	pSender->closeDialogView();
}
void	WoodShopUIViewHandle::ShopUpdate()
{

	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	m_ShopLayer->setVisible(true);
	m_ShopLayer->setPosition(Pos);

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	ShopData*  pShop =    DataPool::GetSingleton()->getShopData();
	X_INT size = pShop->GetShopSize(EM_SHOP_ID_WOOD);
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


	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * SHOP_ITEM_SPACE_DELTA_Y );

	Item *pItem = X_NULL;

	for( X_INT i = 0; i < size; i++ )
	{
		pItem = pShop->getItem(EM_SHOP_ID_WOOD,i);
		if (!pItem)continue;
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * SHOP_ITEM_DOCK_X, winSize.height * ( SHOP_ITEM_START_Y - i * SHOP_ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
		itemBackGround->setScaleX(SCALE_X);
		itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pItem->GetIcon(), pItem->GetIcon(), this, menu_selector(WoodShopUIViewHandle::itemInfoCallBack) );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_IMAGE_OFFSET_X, winSize.height * SHOP_ITEM_IMAGE_OFFSET_Y ) );
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

		CCMenuItemImage *menuItemBuy = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(WoodShopUIViewHandle::buyCallBack) );  
		CCPoint itemBuyPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_BUY_OFFSET_X, winSize.height * SHOP_ITEM_BUY_OFFSET_Y ) );
		menuItemBuy->setPosition( itemBuyPos ); 
		menuItemBuy->setUserData( (void *)pItem );
		menuItemBuy->setScale(0.7f);
		menu->addChild( menuItemBuy );

		CCSprite *pBuyText = CCSprite::create("n_pur_text.png");//n_pur_text.png
		pBuyText->setPosition(itemBuyPos);
		layer->addChild(pBuyText,1);

		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL_BOLD, 24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_NAME_OFFSET_X, winSize.height * SHOP_ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		layer->addChild( mName );
		//ccColor3B Color = ccWHITE;
		//UtilTools::strToColor(pItem->GetColor(),Color.r,Color.g,Color.b);
		mName->setColor(CCCOLOR_YELLOW);

		CCLabelTTF* mDesc = CCLabelTTF::create(pItem->GetInfo(), FONT_NAME_ARIAL_BOLD, 20, CCSizeMake( winSize.width * SHOP_ITEM_TEXT_SIZE_X, winSize.height * SHOP_ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		mDesc->setColor(ccWHITE);
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_DESC_OFFSET_X, winSize.height * SHOP_ITEM_DESC_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		mDesc->setColor(CCCOLOR_GREEN);
		layer->addChild( mDesc );



		CCSprite *itemCoin = CCSprite::create( "wood.png" );
		CCPoint itemCoinPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_COIN_OFFSET_X, winSize.height * SHOP_ITEM_COIN_OFFSET_Y ) );
		itemCoin->setPosition( itemCoinPos );
		layer->addChild( itemCoin );

		char buff[MAX_STRING_BUFF_SIZE];
		sprintf( buff, "%d", pItem->GetPrice() );
		CCLabelTTF* mPrice = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		mPrice->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemPricePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * SHOP_ITEM_PRICE_OFFSET_X, winSize.height * SHOP_ITEM_PRICE_OFFSET_Y ) );
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

	m_ShopLayer->addChild( mContent );

}
 
HeroMasterSchoolUIViewHandle::HeroMasterSchoolUIViewHandle( heroBaseActivityUIView* pUIView )
	: HeroBaseActivityUIViewHandle(pUIView)
	, m_MasterSchoolLayer(NULL)
{
	mSkilldesc = 0;
	mSkillNextdesc = 0;
	mSkillWood = 0;
	mSkillPos = 0;
	mSkillPosNext =0;
	for (int i = 0; i < MAX_MATERIAL_NUM; i++)
	{
		mSkillButton[i] = NULL;
		pIcon[i] = NULL;
		mpLevel[i] =0;
	}
	mbGetAllMatrial = true;
}


HeroMasterSchoolUIViewHandle::~HeroMasterSchoolUIViewHandle()
{
	CC_SAFE_RELEASE(m_MasterSchoolLayer);
	CC_SAFE_RELEASE(mSkilldesc);
	CC_SAFE_RELEASE(mSkillNextdesc);
	CC_SAFE_RELEASE(mSkillWood);
	CC_SAFE_RELEASE(mSkillPos);
	CC_SAFE_RELEASE(mSkillPosNext);
	for (int i = 0; i < MAX_MATERIAL_NUM; i++)
	{
		CC_SAFE_RELEASE(mSkillButton[i]);
	}

 
}
void HeroMasterSchoolUIViewHandle::MasterSchoolUpdate()
{
	mbGetAllMatrial = true;
	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	m_MasterSchoolLayer->setVisible(true);
	m_MasterSchoolLayer->setPosition(Pos);

	CCMenuPEx *menu = CCMenuPEx::create(); 
	CCMenuItemImage *menuItem = CCMenuItemImage::create("base_selskill.png", "base_selskill.png", this, menu_selector(HeroMasterSchoolUIViewHandle::skillInfoCallBack) );  
	menuItem->setPosition( mSkillPos->getPosition()); 
	menu->setPosition( CCPointZero );  
	m_MasterSchoolLayer->addChild( menu );
	menu->addChild(menuItem);
	CCMenuItemImage *menuItemNext = CCMenuItemImage::create("equipmentBK.png", "equipmentBK.png", this, 0);  
	menuItemNext->setPosition( mSkillPosNext->getPosition()); 
    menu->addChild(menuItemNext);

	//mSkilldesc->setString("");
	mSkillNextdesc->setString("");
	mSkillWood->setString("");

	for (X_UINT i =0;i <MAX_MATERIAL_NUM;i++)
	{
		if (pIcon[i] )
		{
			m_MasterSchoolLayer->removeChild(pIcon[i]);
			pIcon[i] =NULL;
		}
		if (mpLevel[i])
		{
			m_MasterSchoolLayer->removeChild(mpLevel[i]);
			mpLevel[i] =NULL;
		}
	}

	 


	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();
	if (!pSkill)return;
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(pSkill->GetIcon());
	mSkillPos->setTexture(texture);
	mSkillPos->setZOrder(100);
	mSkillPosNext->setZOrder(99);
	mSkillPos->setScale(0.8f);
	mSkillPosNext->setScale(0.8f);
	mSkillPosNext->setTexture(texture);
	mSkilldesc->setString(pSkill->GetDesc());
 
	if (pSkill->GetLevel() < MAX_SKILL_LEVEL)
	{
		mSkillNextdesc->setString(Skill::GetDesc(pSkill->GetTableId()+1).c_str());
	}
	else
	{
		 mSkillNextdesc->setString(UtilTools::GET_TEXT_FROM_LANG(564));
	}

  
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL * pTableSkill = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId()+1);
	if (!pTableSkill)
	{
		return;
	}
	
	 vector<int> vRet,vRetNum;
	 vRet.clear();vRetNum.clear();
	if (pTableSkill->items!= "-1" )
	{
		
		UtilTools::ConvertStringToIntVector(pTableSkill->items,vRet,"|");
		UtilTools::ConvertStringToIntVector(pTableSkill->itemsnum,vRetNum,"|");
	}
	if (pTableSkill->_costwood  <= 0 )
	{
		mSkillWood->setString("");
	}else
	{
		X_CHAR temp[256] ={0};
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(669),pTableSkill->_costwood);
		mSkillWood->setString(temp);
	}
	X_UINT size = vRet.size() > MAX_MATERIAL_NUM ? MAX_MATERIAL_NUM:vRet.size();
	for (X_UINT i =0;i < size;i++)
	{
		if (pIcon[i] )
		{
			m_MasterSchoolLayer->removeChild(pIcon[i]);
			pIcon[i] =NULL;
		}

		string  name,color,icon ;X_INT level;
		X_BOOL b =  DataPool::GetSingleton()->getObjectManager()->getItemInfoById(vRet[i],  name, color, icon,level );
		if (!b)
		{

			continue;
		}

 
		pIcon[i] = CCSprite::create(icon.c_str());
		pIcon[i] ->setPosition(mSkillButton[i]->getPosition());
		pIcon[i]->setScale(0.8f);
		m_MasterSchoolLayer->addChild(pIcon[i] );


		X_INT num = 	DataPool::GetSingleton()->getBagData()->getItemNumByTableId(vRet[i]);
		if (num < vRetNum[i])
		{
			mbGetAllMatrial = false;
			pIcon[i]->setColor(ccGRAY);
		}else
		{
			pIcon[i]->setColor(ccWHITE);
		}
		mpLevel[i] = GameHelper::getSpriteLevel(level);
		if (mpLevel[i] )
		{
			mpLevel[i] ->setPosition( pIcon[i]->getPosition()); 
			m_MasterSchoolLayer->addChild(mpLevel[i] );
			mpLevel[i] ->setZOrder(100);
			mpLevel[i] ->setScale(0.8f);
		} 


	}

}
void HeroMasterSchoolUIViewHandle::skillInfoCallBack(cocos2d::CCObject *pSender)
{
	ShowSelectLayer();
}
void HeroMasterSchoolUIViewHandle::onButtonSkillLeveUp()
{

	if (mbGetAllMatrial == false)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(672);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}
		return;
	}

	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();

	if (pSkill&&pSkill->GetLevel()< MAX_SKILL_LEVEL)
	{
		ObjectHero *pHero = (ObjectHero *)(pSkill->getUserData());
		if (!pHero)
		{ return;
		}

		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
		const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId() + 1);

		if (m_pTableData)
		{
			int nextLvl = m_pTableData->_heroLevel;
			if (nextLvl > pHero->GetLevel())
			{
				static char buffLvl[MAX_STRING_BUFF_SIZE] = {0};
				memset(buffLvl,0,sizeof(buffLvl));
				sprintf(buffLvl,UtilTools::GET_TEXT_FROM_LANG(572),nextLvl);
				ModalDialogView *dialog = ModalDialogView::createDialog(buffLvl,0,DIALOG_MODEL_SINGLE);
				addChild(dialog);
				return ;
			}
		}
		vector<Item*> itemUsed;itemUsed.clear();
		vector<int> itemUsedCount;itemUsedCount.clear();
		
		SendLogicPacket::SkillUpgrade(pHero,pSkill->GetTableId(),itemUsed,itemUsedCount);
	}else
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(564);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}
		return;
	}
	
}
void HeroMasterSchoolUIViewHandle::SetLayerDisable()
{
	m_MasterSchoolLayer->setVisible(false);
}
void HeroMasterSchoolUIViewHandle::itemInfoCallBack(cocos2d::CCObject *pSender)
{
	if( m_BaseUIView->mContent->mIsMoved )
		return;
	const ObjectSkill * pSkill = static_cast<const ObjectSkill*> (((CCNode *)pSender)->getUserData());

	DataPool::GetSingleton()->SetSelectSkill(pSkill);
	m_BaseUIView->HeroBaseActivityDataUpdate( heroBaseActivityUIView::EM_HEROBASE_MASTERSCHOOL );
	
}
void HeroMasterSchoolUIViewHandle::ShowSelectLayer()
{
	 m_BaseUIView->SetAllLayerDisable();
	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	m_BaseUIView->mLayerSelect->setVisible(true);
	m_BaseUIView->mLayerSelect->setPosition(Pos);
	if( m_BaseUIView->mContent )
	{
		m_BaseUIView->mContent->removeFromParentAndCleanup( true );
		m_BaseUIView->mContent = NULL;
	}

	vector<ObjectHero*> hero;
	GameHelper::getMasterSchoolHero(hero);
	X_UINT size = hero.size();
	if (size <= 0)
	{
		return;
	}
	 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_BaseUIView->mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create();
	CCMenuEx *menu = CCMenuEx::create(); 

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	ObjectHero *pHero = X_NULL;
	ObjectSkill *pSkill = X_NULL;
	for( X_INT i = 0; i < size; i++ )
	{
		pHero = hero[i];
		if (!pHero)continue;
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
		itemBackGround->setScaleX(SCALE_X);
		itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		 CCSprite *heroicon = CCSprite::create( pHero->GetHeadIcon().c_str() );  
		 CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		 heroicon->setPosition( itemImagePos ); 
		layer->addChild( heroicon );
		heroicon->setScale(0.75f);

		CCSprite *heroIconBg = CCSprite::create(GameHelper::GetHeroColorById(pHero->GetColor()).c_str());
		heroIconBg->setPosition(ccp(heroicon->getContentSize().width * 0.5f, heroicon->getContentSize().height * 0.5f));
		//heroIconBg->setPosition(itemImagePos);
		heroicon->addChild(heroIconBg);

		 X_INT skillNum = pHero->GetSkillCount();
		 for (X_INT j =0;j<skillNum;j++)
		 {
			pSkill =  pHero->GetSkill(j);
			if (!pSkill)continue;

			CCSprite *sprtite = CCSprite::create("equipmentBK.png" );  

			CCMenuItemImage *menuItem = CCMenuItemImage::create( pSkill->GetIcon(), pSkill->GetIcon(), this, menu_selector(HeroMasterSchoolUIViewHandle::itemInfoCallBack) );  
			CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_SKILL_OFFSET_X *j, winSize.height * ITEM_SKILL_OFFSET_Y ) );
			menuItem->setPosition( itemImagePos ); 
			sprtite->setPosition( itemImagePos);
			menuItem->setScale(0.8f);
			menuItem->setUserData( (void *)pSkill );
			if (pSkill->GetLevel() >= MAX_NORMAL_SKILL_LEVEL)
			{
				menuItem->setEnabled(true);
				menuItem->setColor(ccWHITE);
			}
			else
			{
				menuItem->setEnabled(false);
				menuItem->setColor(ccGRAY);
			}
			
			layer->addChild( sprtite );
			menu->addChild( menuItem );
		 }
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 
	menu->setPosition( CCPointZero );  
	layer->addChild( menu );
	m_BaseUIView->mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	m_BaseUIView->mContent->setContentSize( contentSize ); 
	m_BaseUIView->mContent->setContainer( layer );
	m_BaseUIView->mContent->setDirection( kCCScrollViewDirectionVertical );
	m_BaseUIView->mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );
	m_BaseUIView->mContent->setContentOffset( m_BaseUIView->mContent->minContainerOffset() );
	m_BaseUIView->mLayerSelect->addChild( m_BaseUIView->mContent );

}
bool HeroMasterSchoolUIViewHandle::onAssignCCBMemberVariable( cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerSkill",	CCLayer *,m_MasterSchoolLayer);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkilldesc",    CCLabelTTF *,mSkilldesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillNextdesc",    CCLabelTTF *,mSkillNextdesc);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillWood",  CCLabelTTF *,mSkillWood);
	  
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillPos",  CCSprite *,mSkillPos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillPosNext",  CCSprite *,mSkillPosNext);
 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillButton1", CCSprite *, this->mSkillButton[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillButton2", CCSprite *, this->mSkillButton[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillButton3", CCSprite *, this->mSkillButton[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillButton4", CCSprite *, this->mSkillButton[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mSkillButton5", CCSprite *, this->mSkillButton[4]);
	
	return false;
}



HeroIronsmithUIViewHandle::HeroIronsmithUIViewHandle( heroBaseActivityUIView* pUIView )
	: HeroBaseActivityUIViewHandle(pUIView)
	, m_IronsmithLayer(NULL)
{
	 
	mEquipWood = 0;
	mEquipPos = 0;
	mEquipPosNext =0;
	for (int i = 0; i < MAX_MATERIAL_NUM; i++)
	{
		mEquipButton[i] = NULL;
		pIcon[i] = NULL;
		mpLevel[i] =0;
		pIconNum[i] = NULL;
	}
	for (int i = 0; i < 9; i++)
	{
		mEquipAttr[i] = NULL;
		mEquipAttrNext[i] = NULL;
	}
	mbGetAllMatrial = true;
	pLevelItem =NULL;
	pLevelNext =NULL;
 
}

HeroIronsmithUIViewHandle::~HeroIronsmithUIViewHandle()
{
	CC_SAFE_RELEASE(m_IronsmithLayer);
 ;
 
	CC_SAFE_RELEASE(mEquipWood);
	CC_SAFE_RELEASE(mEquipPos);
	CC_SAFE_RELEASE(mEquipPosNext);
	for (int i = 0; i < MAX_MATERIAL_NUM; i++)
	{
		CC_SAFE_RELEASE(mEquipButton[i]);
	}
	for (int i = 0; i < 9; i++)
	{
		CC_SAFE_RELEASE(mEquipAttr[i]);
		CC_SAFE_RELEASE(mEquipAttrNext[i]);
		
	}

}
void HeroIronsmithUIViewHandle::IronsmithUpdate()
{
	mbGetAllMatrial = true;
	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	m_IronsmithLayer->setVisible(true);
	m_IronsmithLayer->setPosition(Pos);

	CCMenuPEx *menu = CCMenuPEx::create(); 
	CCMenuItemImage *menuItem = CCMenuItemImage::create("base_selequp.png", "base_selequp.png", this, menu_selector(HeroIronsmithUIViewHandle::skillInfoCallBack) );  
	menuItem->setPosition( mEquipPos->getPosition()); 
	menu->setPosition( CCPointZero );  
	m_IronsmithLayer->addChild( menu );
	menu->addChild(menuItem);
	CCMenuItemImage *menuItemNext = CCMenuItemImage::create("equipmentBK.png", "equipmentBK.png", this, 0);  
	menuItemNext->setPosition( mEquipPosNext->getPosition()); 
	menu->addChild(menuItemNext);

 
	if (pLevelItem)
	{
		m_IronsmithLayer->removeChild(pLevelItem);
		pLevelItem =NULL;
	}
	if (pLevelNext)
	{
		m_IronsmithLayer->removeChild(pLevelNext);
		pLevelNext =NULL;
	}
	 
	for (unsigned int j = 0 ; j < 9 ; j++)
	{
			mEquipAttr[j]->setString("");
			mEquipAttrNext[j]->setString("");
	}
	mEquipWood->setString("");
	for (X_UINT i =0;i < MAX_MATERIAL_NUM;i++)
	{
		if (pIcon[i] )
		{
			m_IronsmithLayer->removeChild(pIcon[i]);
			pIcon[i] =NULL;
		}
		if (mpLevel[i])
		{
			m_IronsmithLayer->removeChild(mpLevel[i]);
			mpLevel[i] =NULL;
		}
		
	}
 
	mEquipPos->setVisible(false);
	mEquipPosNext->setVisible(false);


	const ItemEquip *pItem = (ItemEquip* )(DataPool::GetSingleton()->GetSelectItem());
	if (!pItem)return;
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(pItem->GetIcon());
	mEquipPos->setTexture(texture);
	mEquipPos->setZOrder(100);
	mEquipPos->setScale(0.8f);
	mEquipPos->setVisible(true);
	mEquipPosNext->setVisible(true);
	pLevelItem = GameHelper::getSpriteLevel(pItem);
	if (pLevelItem)
	{
		pLevelItem->setPosition( mEquipPos->getPosition()); 
		m_IronsmithLayer->addChild(pLevelItem);
		pLevelItem->setZOrder(100);
		pLevelItem->setScale(mEquipPos->getScale());
	} 

 
	vector<string> attr = pItem->getAddAttr();
	unsigned int equipSize = attr.size();
	for (unsigned int j = 0 ; j < 9 ; j++)
	{
		if(j < equipSize)
		{
			mEquipAttr[j]->setString(attr[j].c_str());
		}
	}

	
	X_INT productId = 	EquipMaker::__FindEquipWithMaterialId(pItem->GetTableID());
	const ItemEquip *pNextItem = X_NULL;

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);
	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData  = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByIndexKey(productId);
	if (!m_pTableData)return;
			pNextItem = (ItemEquip *)( DataPool::GetSingleton()->getObjectManager()->FindFakeItem( m_pTableData->itemID));
	if (!pNextItem)
	{
		return;
	} 

	attr = pNextItem->getAddAttr();
	equipSize = attr.size();
	for (unsigned int j = 0 ; j < 9 ; j++)
	{
		if(j < equipSize)
		{
			mEquipAttrNext[j]->setString(attr[j].c_str());
		}
	}
 
	if (m_pTableData->wood  <= 0 )
	{
		mEquipWood->setString("");
	}else
	{
		X_CHAR temp[256] ={0};
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(669),m_pTableData->wood );
		mEquipWood->setString(temp);
	}
	
	for(X_INT k= 0;k < MAX_MATERIAL_NUM;k++)
	{
		if (pIcon[k] )
		{
			m_IronsmithLayer->removeChild(pIcon[k]);
			pIcon[k] =NULL;
		}
		if (pIconNum[k] )
		{
			m_IronsmithLayer->removeChild(pIconNum[k]);
			pIconNum[k] =NULL;
		}
 
			if (m_pTableData->items[k].id <=0)
			{
				continue;
			}
		string  name,color,icon ;X_INT level;
		X_BOOL b =  DataPool::GetSingleton()->getObjectManager()->getItemInfoById(m_pTableData->items[k].id,  name, color, icon,level );
		if (!b)
		{
			continue;
		}
		X_INT num = 	DataPool::GetSingleton()->getBagData()->getItemNumByTableId(m_pTableData->items[k].id);

		pIcon[k] = CCSprite::create(icon.c_str());
		pIcon[k] ->setPosition(mEquipButton[k]->getPosition());
		pIcon[k]->setScale(0.8f);

		if (m_pTableData->items[k].num >1)
		{
			pIconNum[k] =  CCLabelBMFont::create( UtilTools::IntToString(m_pTableData->items[k].num).c_str(), FNT_NAME_SUMMONERLEVEL);

			CCPoint point = mEquipButton[k]->getPosition();
			point.x +=  (pIcon[k]->getContentSize().width *0.45f);//-pIconNum[k]->getContentSize().width);
			point.y -= (pIcon[k]->getContentSize().height *0.45f);//-pIconNum[k]->getContentSize().height);

			pIconNum[k] ->setPosition(point);
			 
		}
	 
		mpLevel[k] = GameHelper::getSpriteLevel(level);
		if (mpLevel[k])
		{
			mpLevel[k]->setPosition( pIcon[k]->getPosition()); 
			m_IronsmithLayer->addChild(mpLevel[k]);
			mpLevel[k]->setZOrder(100);
			mpLevel[k]->setScale(0.8f);
				 
		} 
		if (num <  m_pTableData->items[k].num)
		{
			mbGetAllMatrial =false;
			pIcon[k]->setColor(ccGRAY);
		}else
		{
			pIcon[k]->setColor(ccWHITE);
		}
		m_IronsmithLayer->addChild(pIcon[k] );
		if (pIconNum[k])
		{
			m_IronsmithLayer->addChild(pIconNum[k] );
		}
		
		
	}
	CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage(pNextItem->GetIcon());
	mEquipPosNext->setZOrder(99);
	mEquipPosNext->setScale(0.8f);
	mEquipPosNext->setTexture(texture1);

	pLevelNext = GameHelper::getSpriteLevel(pNextItem);
	if (pLevelNext)
	{
		pLevelNext->setPosition( mEquipPosNext->getPosition()); 
		m_IronsmithLayer->addChild(pLevelNext);
		pLevelNext->setZOrder(100);
		pLevelNext->setScale(mEquipPosNext->getScale());
	} 
	 
}
void HeroIronsmithUIViewHandle::skillInfoCallBack(cocos2d::CCObject *pSender)
{
	ShowSelectLayer();
}
void HeroIronsmithUIViewHandle::onButtonEquipLeveUp()
{
	if (mbGetAllMatrial == false)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(672);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}
		return;
	}
	const ItemEquip *pItem = (ItemEquip*)(DataPool::GetSingleton()->GetSelectItem());
	if (pItem)
	{
		if(SendLogicPacket::EquipMakerFrom(pItem))
		{
			DataPool::GetSingleton()->SetSelectItem(0);
		}
	}

}
void HeroIronsmithUIViewHandle::SetLayerDisable()
{
	m_IronsmithLayer->setVisible(false);
}
void HeroIronsmithUIViewHandle::itemInfoCallBack(cocos2d::CCObject *pSender)
{
	if( m_BaseUIView->mContent->mIsMoved )
		return;
	const ItemEquip * pSkill = static_cast<const ItemEquip*> (((CCNode *)pSender)->getUserData());

	DataPool::GetSingleton()->SetSelectItem(pSkill);
	m_BaseUIView->HeroBaseActivityDataUpdate( heroBaseActivityUIView::EM_HEROBASE_IRONSMITH );

}
void HeroIronsmithUIViewHandle::ShowSelectLayer()
{
	m_BaseUIView->SetAllLayerDisable();
	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	m_BaseUIView->mLayerSelect->setVisible(true);
	m_BaseUIView->mLayerSelect->setPosition(Pos);
	if( m_BaseUIView->mContent )
	{
		m_BaseUIView->mContent->removeFromParentAndCleanup( true );
		m_BaseUIView->mContent = NULL;
	}

	vector<ItemEquip*> equips;
	EquipMaker::getIronsmithEquip(equips);
 
	X_UINT size = equips.size();
	if (size <= 0)
	{
		return;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_BaseUIView->mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create();
	CCMenuEx *menu = CCMenuEx::create(); 

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	ItemEquip *pItem = X_NULL;
	layer->addChild( menu );
	for( X_INT i = 0; i < size; i++ )
	{
		pItem = (ItemEquip*)equips[i];
		if (!pItem)continue;
		CCMenuItemImage *itemBackGround = CCMenuItemImage::create( "levelFrame.png","levelFrame.png", this, menu_selector(HeroIronsmithUIViewHandle::itemInfoCallBack));
		itemBackGround->setUserData( (void *)pItem );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
		itemBackGround->setScaleX(SCALE_X);
		itemBackGround->setScaleY(SCALE_Y);
		menu->addChild( itemBackGround );
 

		CCSprite *heroicon = CCSprite::create( pItem->GetIcon() );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		heroicon->setPosition( itemImagePos ); 
		layer->addChild( heroicon );  
		if (equips[i]->GetItemVectorType() == EM_ITEM_CONTAINER_EQUIP)
		{
			itemBackGround->setEnabled(true);
			itemBackGround->setColor(ccWHITE);
			heroicon->setColor(ccWHITE);
		}else
		{
			itemBackGround->setEnabled(false);
			itemBackGround->setColor(ccGRAY);
			heroicon->setColor(ccGRAY);
		}

		CCSprite *heroIconBg = CCSprite::create("equipmentBK.png");
		heroIconBg->setPosition(ccp(heroicon->getContentSize().width * 0.5f, heroicon->getContentSize().height * 0.5f));
		heroIconBg->setScale(1.15f);
		heroicon->addChild(heroIconBg);


		
		CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemImagePos); 
			layer->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(heroicon->getScale());
		} 


		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL, FONT_SIZE_22, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemImagePos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y  ) );
		mName->setPosition( itemNamePos );
		mName->setColor(ccGREEN);
		layer->addChild( mName );
		  

		CCLabelTTF* mDesc = CCLabelTTF::create( pItem->GetInfo(), FONT_NAME_ARIAL, FONT_SIZE_22, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemImagePos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X,winSize.height * ITEM_DESC_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		layer->addChild( mDesc );	 
	}
		
	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 
	menu->setPosition( CCPointZero );  

 
	m_BaseUIView->mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	m_BaseUIView->mContent->setContentSize( contentSize ); 
	m_BaseUIView->mContent->setContainer( layer );
	m_BaseUIView->mContent->setDirection( kCCScrollViewDirectionVertical );
	m_BaseUIView->mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );
	m_BaseUIView->mContent->setContentOffset( m_BaseUIView->mContent->minContainerOffset() );
	m_BaseUIView->mLayerSelect->addChild( m_BaseUIView->mContent );
}
bool HeroIronsmithUIViewHandle::onAssignCCBMemberVariable( cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode )
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerEquip",	CCLayer *,m_IronsmithLayer);

 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipWood",    CCLabelTTF *,mEquipWood);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipPos",  CCSprite *,mEquipPos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipPosNext",  CCSprite *,mEquipPosNext);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipButton1", CCSprite *, this->mEquipButton[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipButton2", CCSprite *, this->mEquipButton[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipButton3", CCSprite *, this->mEquipButton[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipButton4", CCSprite *, this->mEquipButton[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipButton5", CCSprite *, this->mEquipButton[4]);
 
 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc1", CCLabelTTF *, this->mEquipAttr[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc2", CCLabelTTF *, this->mEquipAttr[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc3", CCLabelTTF *, this->mEquipAttr[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc4", CCLabelTTF *, this->mEquipAttr[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc5", CCLabelTTF *, this->mEquipAttr[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc6", CCLabelTTF *, this->mEquipAttr[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc7", CCLabelTTF *, this->mEquipAttr[6]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc8", CCLabelTTF *, this->mEquipAttr[7]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc9", CCLabelTTF *, this->mEquipAttr[8]);
	 

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc11", CCLabelTTF *, this->mEquipAttrNext[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc21", CCLabelTTF *, this->mEquipAttrNext[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc31", CCLabelTTF *, this->mEquipAttrNext[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc41", CCLabelTTF *, this->mEquipAttrNext[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc51", CCLabelTTF *, this->mEquipAttrNext[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc61", CCLabelTTF *, this->mEquipAttrNext[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc71", CCLabelTTF *, this->mEquipAttrNext[6]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc81", CCLabelTTF *, this->mEquipAttrNext[7]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mEquipDesc91", CCLabelTTF *, this->mEquipAttrNext[8]);
	

	return false;
}

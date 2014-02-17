#include "./ui/bagOwnUIView.h"
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

#include "./base/UtilTools.h"
#include "./ui/bagOwnUI.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.050f)
#define CONTENT_POS_Y            (0.182f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.52f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.175f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.28f)
#define ITEM_IMAGE_OFFSET_Y      (0.000f)

#define ITEM_NAME_OFFSET_X       (-0.18f)
#define ITEM_NAME_OFFSET_Y       (0.045f)

#define ITEM_DESC_OFFSET_X       (-0.18f)
#define ITEM_DESC_OFFSET_Y       (-0.030f)

#define ITEM_COUNT_OFFSET_X      (-0.18f)//(0.25f)
#define ITEM_COUNT_OFFSET_Y      (-0.05)//(0.045f)

#define ITEM_TEXT_SIZE_X         (0.53f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

#define USE_ITEM_OFFSET_X		(0.28f)
#define USE_ITEM_OFFSET_Y		(-0.04f)
 
BagOwnUIView::BagOwnUIView()
: mMainStatus(NULL)
{
	mContent = NULL;

	for (int i = 0 ; i<3 ; i++)
	{
		mItemImage[i] = NULL;
	}
	

	mItemCategory = ITEM_TOOLS;
}

BagOwnUIView::~BagOwnUIView()
{
    CC_SAFE_RELEASE(mMainStatus);

	for (int i = 0 ; i<3 ; i++)
	{
		CC_SAFE_RELEASE(mItemImage[i]);
	}
}


void BagOwnUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	
}


SEL_MenuHandler BagOwnUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonExperienceCard", BagOwnUIView::onButtonExperienceCard);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSkillCard", BagOwnUIView::onButtonSkillCard);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonTools", BagOwnUIView::onButtonTools);

    return NULL;    
}

SEL_CCControlHandler BagOwnUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void BagOwnUIView::onButtonExperienceCard(cocos2d::CCObject * pSender)
{
	if( mItemCategory != ITEM_EXPERIENCE )
	{
		mItemCategory = ITEM_EXPERIENCE;
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_UPDATA);
	}
	

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	onDataUpdate(true);
}

void BagOwnUIView::onButtonSkillCard(cocos2d::CCObject * pSender)
{
	if( mItemCategory != ITEM_SKILL )
	{
		mItemCategory = ITEM_SKILL;
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_UPDATA);
	}
	BagOwnUI* pUi = static_cast<BagOwnUI*>(getUserData());
	if (pUi)
	{
		pUi->nPage = 0;
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	onDataUpdate(true);
}

void BagOwnUIView::onButtonTools(cocos2d::CCObject * pSender)
{
	if( mItemCategory != ITEM_TOOLS )
	{
		mItemCategory = ITEM_TOOLS;
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_UPDATA);
	}
	BagOwnUI* pUi = static_cast<BagOwnUI*>(getUserData());
	if (pUi)
	{
		pUi->nPage = 0;
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	onDataUpdate(true);
}

bool BagOwnUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);
	

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExperienceCard", cocos2d::CCMenuItemImage *, this->mItemImage[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillCard", cocos2d::CCMenuItemImage *, this->mItemImage[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTools", cocos2d::CCMenuItemImage *, this->mItemImage[2]);

	return false;
}

X_VOID BagOwnUIView::__onSelectMessage(int type)
{

	for (int  i = ITEM_EXPERIENCE ; i<=  ITEM_TOOLS;i++ )
	{
		if (i == type)
		{
			mItemImage[i-2]->setNormalImage(CCSprite::create("n_button_seledBig.png"));
		}else
		{
			mItemImage[i-2]->setNormalImage(CCSprite::create("n_home_button.png"));
		}
	}


}

bool BagOwnUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}
 
bool BagOwnUIView::itemCanUse(const Item *pItem1,const Item *pItem2)
{
	if (!pItem1 ||!pItem2)
	{
		return false;
	}
	X_BOOL x  =  pItem1->Rule(EM_USE);
	X_BOOL y  =  pItem2->Rule(EM_USE);

	if (x==y)
	{
		return false;
	}
 
	return x == X_TRUE;
	 

}
// on "init" you need to initialize your instance
bool BagOwnUIView::init()
{
    bool bRet = true;


    return bRet;
}

void BagOwnUIView::onDataUpdate( bool isDataValid )
{
	
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();
		return;
	}


	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
    SelfBagData*  pBag =    DataPool::GetSingleton()->getBagData();
	X_UINT size = pBag->GetBagSize(EM_ITEM_CONTAINER_BAG);

	vector<Item*> itemlist;
	itemlist.clear();
	Item *pItem;
	for (X_UINT i = 0 ; i< size ;i++)
	{
		pItem = pBag->getItem(i,EM_ITEM_CONTAINER_BAG);
		if (pItem && pItem->GetTableType() == mItemCategory)
		{
			itemlist.push_back(pItem);
		}
	}

	std::sort(itemlist.begin(),itemlist.end(), itemCanUse);
 
	size = itemlist.size();
	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}

	__onSelectMessage(mItemCategory);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 

	CCMenuEx *menu = CCMenuEx::create();
	menu->setPosition(CCPointZero);
// 	layer->addChild(menu);

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	for( X_UINT i = 0; i < size; i++ )
	{
		pItem = itemlist[i];

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCSprite *Item = CCSprite::create( pItem->GetIcon() );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		Item->setPosition( itemImagePos ); 
		Item->setUserData( (void *)pItem );
		

	

		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(Item->getPosition());
		equipBG->setScale(Item->getContentSize().width / equipBG->getContentSize().width  + 0.20f);
		

		layer->addChild( Item );
		layer->addChild(equipBG);

		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL_BOLD, 24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		mName->setColor(CCCOLOR_GREEN);

		layer->addChild( mName );

		CCLabelTTF* mDesc = CCLabelTTF::create( pItem->GetInfo(), FONT_NAME_ARIAL_BOLD, 20, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		mDesc->setColor(CCCOLOR_WHITE);
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (ITEM_DESC_OFFSET_Y + 0.01)) );
		mDesc->setPosition( itemDescPos );
		layer->addChild( mDesc );


		string s;
		s = UtilTools::GET_TEXT_FROM_LANG(523);
		s += ": ";
		s += UtilTools::IntToString(pItem->GetCount());
		 
		CCLabelTTF* mPrice = CCLabelTTF::create(s.c_str(), FONT_NAME_ARIAL_BOLD, 24 );
		mPrice->setAnchorPoint( ccp( 0, 0.5f ) );
		mPrice->setColor(CCCOLOR_YELLOW);
		CCPoint itemPricePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_COUNT_OFFSET_X, winSize.height * ITEM_COUNT_OFFSET_Y ) );
		mPrice->setPosition( itemPricePos );
		layer->addChild( mPrice );


		if (mItemCategory == ITEM_TOOLS &&pItem->Rule(EM_USE))
		{

			CCMenuItemImage *menuItemUse = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(BagOwnUIView::useCallBack) );  
			CCPoint itemEvolvePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * USE_ITEM_OFFSET_X	, winSize.height * USE_ITEM_OFFSET_Y ) );
			menuItemUse->setPosition( itemEvolvePos ); 
			menuItemUse->setUserData(pItem);
			menuItemUse->setScale(0.65f);
			menu->addChild( menuItemUse );
 

			CCSprite *itemUseText = CCSprite::create( "n_use_text.png" );
			itemUseText->setPosition( menuItemUse->getPosition());
			layer->addChild( itemUseText,menu->getZOrder()+1);

		}
	
	}

	layer->addChild(menu);

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	addChild( mContent );
	BagOwnUI* pUi = static_cast<BagOwnUI*>(getUserData());
	if (pUi)
	{
		 
		 
	}
}


void BagOwnUIView::useCallBack(CCObject* pSender)
{
	const Item *pItem =  static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	if (pItem && pItem->GetTableType() == ITEM_TOOLS &&pItem->Rule(EM_USE))
	{
		SendLogicPacket::UseItem(pItem);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void BagOwnUIView::onTipResult()
{

	vector<tipItem> vecTips =  DataPool::GetSingleton()->getTipItems();

	string strResult = UtilTools::GET_TEXT_FROM_LANG(545);
	string name,icon ,color;X_INT level;
	for (X_UINT i = 0;i<vecTips.size();i++)
	{
		DataPool::GetSingleton()->getObjectManager()->getItemInfoById(vecTips[i].itemID,name,color,icon,level);
		strResult += name;
		strResult +=" ";
	}

	ModalDialogView *dialogView = ModalDialogView::createDialog(strResult,this,DIALOG_MODEL_SINGLE);
	addChild(dialogView,1);
}

void BagOwnUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	pSender->closeDialogView();
}
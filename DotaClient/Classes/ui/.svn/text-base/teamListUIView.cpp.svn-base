#include "./ui/teamListUIView.h"
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

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (512)

#define CONTENT_POS_X            (0.050f)
#define CONTENT_POS_Y            (0.170f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.600f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.25f)
#define ITEM_IMAGE_OFFSET_Y      (0.0011f)

#define ITEM_UPGRADE_OFFSET_X    (0.25f)
#define ITEM_UPGRADE_OFFSET_Y    (0.032f)//(0.030f)

#define ITEM_EVOLVE_OFFSET_X     (0.25f)
#define ITEM_EVOLVE_OFFSET_Y     (-0.030f)

#define ITEM_DESC_OFFSET_X       (-0.16f)
#define ITEM_DESC_OFFSET_Y       (0.040f)//(-0.000f)
#define ITEM_LV_OFFSET_Y		(0.00f)
#define ITEM_EXP_OFFSET_X		(-0.06f)
#define ITEM_EXP_OFFSET_Y		(0.00f)
#define  ITEM_DIS_OFFSET_Y		(-0.038f)

#define ITEM_TEXT_SIZE_X         (0.40f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

#define ITEM_ICON_OFFSET_X		(0.20f)
#define ITEM_ICON_OFFSET_Y		(0.20f)

#define  ITEM_ICON_SCALE		(0.80f)

 


TeamListUIView::TeamListUIView()
: mMainStatus(NULL)
{
	mContent = NULL;
}

TeamListUIView::~TeamListUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
}


void TeamListUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	
}

SEL_MenuHandler TeamListUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler TeamListUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void TeamListUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	DataPool::GetSingleton()->SetSelectHero( (ObjectHero *)(((CCNode *)pSender)->getUserData()) );
    
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_SHOW);
}

void TeamListUIView::onButtonEvolve(cocos2d::CCObject * pSender)
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	ObjectHero *pHero = (ObjectHero *)(((CCNode *)pSender)->getUserData());
	DataPool::GetSingleton()->SetSelectHero(pHero);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROEVOLVE_SHOW);
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

void TeamListUIView::onButtonUpgrade(cocos2d::CCObject * pSender)
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	ObjectHero *pHero = (ObjectHero *)(((CCNode *)pSender)->getUserData());
	DataPool::GetSingleton()->SetSelectHero(pHero);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void TeamListUIView::onButtonRescruit(cocos2d::CCObject * pSender)
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool TeamListUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool TeamListUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

// on "init" you need to initialize your instance
bool TeamListUIView::init()
{
    bool bRet = true;

    return bRet;
}

void TeamListUIView::onDataUpdate( bool isDataValid )
{
	mMainStatus->onDataUpdate( isDataValid );

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

	X_INT size = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	ObjectHero *pHero;

	// rearrange hero list
	std::vector< ObjectHero * > heroList;
	heroList.reserve( size );

	for( int j = 0; j < size; j++ )
	{
		pHero = pSelf->getHero(j, EM_HERO_CONTAINER_BAG);

		if( !pHero )
			continue;

		heroList.push_back( pHero );
	}

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx *menu = CCMenuEx::create(); 

	

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * ( heroList.size() + 1 ) * ITEM_SPACE_DELTA_Y );


	//ÕÐÄ¼ÀºÓ¢ÐÛ
	unsigned int i = 0;
	for( ; i < heroList.size(); i++ )
	{
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		//Í·Ïñµ×°å
		//CCMenuItemImage *menuItem = CCMenuItemImage::create( heroList[i]->GetHeadIcon().c_str(), heroList[i]->GetHeadIcon().c_str(), this, menu_selector(TeamListUIView::itemInfoCallBack) );  
		CCMenuItemImage *menuItem = CCMenuItemImage::create( "n_pos_back_.png", "n_pos_back_.png", this, menu_selector(TeamListUIView::itemInfoCallBack) );
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItem->setPosition( itemImagePos ); 
		menuItem->setScale( ITEM_ICON_SCALE );
		menuItem->setUserData( (void *)heroList[i] );
		menu->addChild( menuItem );


		//±ß¿ò
		CCSprite *heroIconBG = CCSprite::create( heroList[i]->getHeroColor().c_str());
		//CCPoint heroIconPos = ccpAdd(itemImagePos,ccp(winSize.width * ITEM_ICON_OFFSET_X, winSize.height * ITEM_ICON_OFFSET_Y));
		heroIconBG->setPosition( itemImagePos );
		heroIconBG->setScale( ITEM_ICON_SCALE );
		layer->addChild(heroIconBG,menu->getZOrder()+2);

		//Í·Ïñ
		CCSprite *heroIconHead = CCSprite::create(heroList[i]->GetHeadIcon().c_str());
		heroIconHead->setPosition( itemImagePos );
		heroIconHead->setScale( ITEM_ICON_SCALE );
		layer->addChild(heroIconHead,menu->getZOrder()+1);

		//button
		CCMenuItemImage *menuItemEvolve = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(TeamListUIView::onButtonEvolve) );  
		CCPoint itemEvolvePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_EVOLVE_OFFSET_X, winSize.height * ITEM_EVOLVE_OFFSET_Y ) );
		menuItemEvolve->setPosition( itemEvolvePos ); 
		menuItemEvolve->setScale( 0.75f ); //0.65f
		menuItemEvolve->setUserData( (void *)heroList[i] );
		menu->addChild( menuItemEvolve );

		CCSprite *evolveText = CCSprite::create( "main_jinhua.png" );
		evolveText->setPosition( itemEvolvePos );
		evolveText->setScale(0.75f);
		layer->addChild( evolveText, 10 );

 
		if (heroList[i]->GetQuality() == EM_HERO_QUALITY_TYPE6)
		{
			menuItemEvolve->setEnabled(false);
			/*
			CCSprite *pGraySprite = CCSprite::create("n_button_gray.png");
			pGraySprite->setScaleX(0.55f);
			pGraySprite->setScaleY(0.80f);
			menuItemEvolve->setPosition(evolveText->getPosition());
			menuItemEvolve->setNormalImage(pGraySprite);
			*/

			menuItemEvolve->setColor(ICON_COLOR_GRAY);//150
			evolveText->setColor(ICON_COLOR_GRAY);//
		}

		CCMenuItemImage *menuItemUpgrade = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(TeamListUIView::onButtonUpgrade) );  
		CCPoint itemUpgradePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_UPGRADE_OFFSET_X, winSize.height * ITEM_UPGRADE_OFFSET_Y ) );
		menuItemUpgrade->setPosition( itemUpgradePos ); 
		menuItemUpgrade->setScale(0.75f);
		menuItemUpgrade->setUserData( (void *)heroList[i] );
		menu->addChild( menuItemUpgrade );

		CCSprite *upgradeText = CCSprite::create( "upgradeText.png" );
		upgradeText->setPosition( itemUpgradePos );
		upgradeText->setScale(0.75f);
		layer->addChild( upgradeText, 10 );

		char buff[MAX_STRING_BUFF_SIZE];
		sprintf( buff, "%s", heroList[i]->GetName().c_str() );
		CCLabelBMFont *mDesc = CCLabelBMFont::create(buff, FNT_HERO_NAME_GREEN);
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		mDesc->setScale(SCALE_BMF);
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		layer->addChild( mDesc );

		string sLvl;
		sLvl = UtilTools::GET_TEXT_FROM_LANG(514);
		string strLvl(UtilTools::IntToString(heroList[i]->GetLevel()));
		strLvl += sLvl;

		CCLabelBMFont *mLvl = CCLabelBMFont::create(strLvl.c_str(),FNT_HERO_NAME_GREEN);
		mLvl->setScale(SCALE_BMF);
		mLvl->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemlvlPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_LV_OFFSET_Y ) );
		mLvl->setPosition( itemlvlPos );
		layer->addChild( mLvl );

// 		string sExp;
// 		sExp = UtilTools::IntToString(heroList[i]->GetExp());
// 		sExp += "/";
// 		sExp += UtilTools::IntToString(heroList[i]->GetMaxExpWithLevel());
// 		CCLabelBMFont *mExp = CCLabelBMFont::create(sExp.c_str(),FNT_NAME_LARGEGREEN);
// 		mExp->setScale(SCALE_BMF);
// 		mExp->setAnchorPoint( ccp( 0, 0.5f ) );
// 		CCPoint itemExpPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_EXP_OFFSET_X, winSize.height * ITEM_EXP_OFFSET_Y ) );
// 		mExp->setPosition( itemExpPos );
// 		layer->addChild( mExp );

		string sDis;
		sDis = UtilTools::GET_TEXT_FROM_LANG(524);
		sDis += ":";
		sDis += UtilTools::IntToString(heroList[i]->GetBearPoint());
		CCLabelBMFont *mDis = CCLabelBMFont::create(sDis.c_str(),FNT_NAME_LARGEGREEN);
		mDis->setScale(SCALE_BMF);
		mDis->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDisPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DIS_OFFSET_Y ) );
		mDis->setPosition( itemDisPos );
		layer->addChild( mDis );
	}

	CCMenuItemImage *menuRecruit = CCMenuItemImage::create( "n_user_up_btn.PNG", "n_user_up_btn.PNG", this, menu_selector(TeamListUIView::onButtonRescruit) );  
	CCPoint menuRecruitPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
	menuRecruit->setPosition( menuRecruitPos ); 
	menu->addChild( menuRecruit );
	
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

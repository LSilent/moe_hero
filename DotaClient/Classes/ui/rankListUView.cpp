#include "./ui/ranklistUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./game/GameHelper.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.045f)
#define CONTENT_POS_Y            (0.225f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.600f)

#define ITEM_DOCK_X              (0.455f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.310f)//(-0.325f)//(-0.33f)//
#define ITEM_IMAGE_OFFSET_Y      (-0.015f)

#define ITEM_IMAGE_DELTA_X       (0.106f)//(0.09f)

#define ITEM_RANK_OFFSET_X       (-0.36f)
#define ITEM_RANK_OFFSET_Y       (0.050f)

#define ITEM_LEVEL_OFFSET_X      (-0.13f)
#define ITEM_LEVEL_OFFSET_Y      (0.050f)

#define ITEM_LEVEL_NUM_OFFSET_X  (-0.09f)
#define ITEM_LEVEL_NUM_OFFSET_Y  (0.050f)

#define ITEM_NAME_OFFSET_X       (0.07f)
#define ITEM_NAME_OFFSET_Y       (0.050f)

#define ITEM_DETAIL_OFFSET_X       (0.25f)
#define ITEM_DETAIL_OFFSET_Y        (-0.015f)

#define ITEM_BUTTON_OFFSET_X     (0.265f)//(0.32f)
#define ITEM_BUTTON_OFFSET_Y     (-0.00f)

#define ITEM_BUTTON_2_OFFSET_X   (0.30f)
#define ITEM_BUTTON_2_OFFSET_Y   (-0.00f)

#define ITEM_AWARD_OFFSET_X      (0.005f)//(-0.11f)
#define ITEM_AWARD_OFFSET_Y      (-0.0f)

#define ITEM_TIME_OFFSET_X       (-0.01f)//(-0.11f)
#define ITEM_TIME_OFFSET_Y       (-0.05f)
//

#define MAX_CHALLENGE_GOLD		20

#define DIALOG_MODEL_TAG_NUM   1000
#define DIALOG_MODEL_TAG_GOLD  1001

#define BUTTON_SCALE_X (0.700f)
#define BUTTON_SCALE_Y (0.700f)
#define BUTTON_SCALE (0.700f)

 

RankListUIView::RankListUIView()
: mTiTle(NULL)
, mInfo(NULL)
{
	mContent = NULL;

	mTimeFresh = 0;

}

RankListUIView::~RankListUIView()
{
	CC_SAFE_RELEASE(mTiTle);
	CC_SAFE_RELEASE(mInfo);
}

void RankListUIView::onEnter()
{
	CCLayer::onEnter();

	schedule( schedule_selector(RankListUIView::updateTime), 0.2f );
}

void RankListUIView::onExit()
{
	unschedule( schedule_selector(RankListUIView::updateTime) );

	BaseView::onExit();
}

void RankListUIView::updateTime( float time )
{
	// Ë¢ÐÂÊ±¼ä
	if( mTimeFresh )
	{
		SportsData * sportData = DataPool::GetSingleton()->getSportsData();
		X_INT  time = sportData->GetWelfareCD();

		string timeStr = UtilTools::ConvertMillisecondToTimeString( time );
		timeStr  = UtilTools::GET_TEXT_FROM_LANG(515) + timeStr;
		mTimeFresh->setString( timeStr.c_str() );
	}
}

void RankListUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler RankListUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler RankListUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool RankListUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTiTle", CCLabelBMFont *, this->mTiTle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInfo", CCLabelBMFont *, this->mInfo);
	
	return false;
}

bool RankListUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool RankListUIView::init()
{
    bool bRet = true;

	return bRet;
}

void RankListUIView::detailCallBack( cocos2d::CCObject* pSender )
{
	Competitor * cometitorTop10 = (Competitor*)(((CCNode *)pSender)->getUserData());
	SendLogicPacket::AskArenaDetail(cometitorTop10->getGuid());
}
void RankListUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}
	DataPool::GetSingleton()->BattlyType = EM_SPORT;
	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}

	char buff[MAX_STRING_BUFF_SIZE];

	SportsData * sportData = DataPool::GetSingleton()->getSportsData();

	sprintf( buff, "%s%d", UtilTools::GET_TEXT_FROM_LANG(511),sportData->GetRank() );
	mTiTle->setString( buff );

	sprintf( buff, "%s%d", UtilTools::GET_TEXT_FROM_LANG(512),sportData->GetChallengeCountRemain() );
	mInfo->setString(buff);

	const vector<Competitor*> & cometitorTop10 = sportData->getTop10();

	const vector<Competitor*> & cometitor = sportData->getCompetitor();

	int itemSize = cometitorTop10.size() + cometitor.size() + 1;

	// get window size
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	mContent = CCScrollViewEx::create();  
    CCLayer *layer = CCLayer::create(); 

	CCMenuEx *menu = CCMenuEx::create(); 

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * itemSize * ITEM_SPACE_DELTA_Y );
	
	// top 10
	unsigned int i = 0;
	
	for ( ;i< cometitorTop10.size(); i++)
	{
		CCMenuEx *menuTitle = CCMenuEx::create(); 
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );
 

		sprintf( buff, "%s%d", UtilTools::GET_TEXT_FROM_LANG(513),cometitorTop10[i]->getRank() );
	    CCLabelTTF* rank = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		rank->setAnchorPoint( ccp( 0, 0.5f ) );
		rank->setColor(CCCOLOR_YELLOW);
		CCPoint itemRankPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_RANK_OFFSET_X, winSize.height * ITEM_RANK_OFFSET_Y ) );
		rank->setPosition( itemRankPos );
		layer->addChild( rank );


		sprintf( buff, "lv.%d%s", cometitorTop10[i]->getLevel(),UtilTools::GET_TEXT_FROM_LANG(514) );
	    CCLabelTTF* level = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		level->setAnchorPoint( ccp( 0, 0.5f ) );
		level->setColor(CCCOLOR_WHITE);
		CCPoint levelPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_LEVEL_OFFSET_X, winSize.height * ITEM_LEVEL_NUM_OFFSET_Y ) );
		level->setPosition( levelPos );
		layer->addChild( level );

		CCLabelTTF* name = CCLabelTTF::create( cometitorTop10[i]->getName(), FONT_NAME_ARIAL_BOLD, 24 );
		name->setAnchorPoint( ccp( 0, 0.5f ) );
		name->setColor(CCCOLOR_GREEN);
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		name->setPosition( itemNamePos );
		layer->addChild( name );

		const vector<CompetitorHero> & herosArray = cometitorTop10[i]->getHeros();
		for( unsigned int j = 0; j < herosArray.size(); j++ )
		{

			CCSprite *hero = CCSprite::create( ObjectHero::getIconById( herosArray[j].tableId ).c_str() );
			if (!hero)
			{
				continue;
			}
			
			CCPoint heroPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (ITEM_IMAGE_OFFSET_X + ITEM_IMAGE_DELTA_X * j), winSize.height * ITEM_IMAGE_OFFSET_Y ) );
			hero->setPosition( heroPos );
// 			hero->setScale( 0.65f );
			hero->setScale( 0.5f );

			CCSprite *heroBg = CCSprite::create("n_pos_back_.png");
			heroBg->setPosition( heroPos );
			heroBg->setScale(0.5f);

			layer->addChild(heroBg);
			layer->addChild( hero, 10 );

			CCSprite *heroFrame = CCSprite::create(   GameHelper::GetHeroColorById(herosArray[j].color).c_str() );
			heroFrame->setPosition( heroPos );
			heroFrame->setScale(0.5f);
			layer->addChild( heroFrame, 10 );			

		}
		ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
		if(cometitorTop10[i]->getGuid() != pSelf->GetGuid())
		{
			CCMenuItemImage *menuItem = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(RankListUIView::detailCallBack) );  
			CCPoint itemPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (ITEM_DETAIL_OFFSET_X + 0.015), winSize.height * ITEM_DETAIL_OFFSET_Y ) );
			menuItem->setPosition( itemPos ); 
			menuItem->setUserData( (void *)cometitorTop10[i] );
	
			menuItem->setScale(BUTTON_SCALE);
			CCSprite *buttonText = CCSprite::create( "HeroInfoText.png" );
			buttonText->setPosition( itemPos );
			buttonText->setScale(0.5);
			
   
			menuTitle->addChild( menuItem );
			menuTitle->setPosition( CCPointZero );  
			layer->addChild( menuTitle );
			layer->addChild( buttonText );
		}
		

	}

	 
	// cometitor

	int curIndex = 0;

	bool flag = false;
	for (unsigned int j = 0; j < cometitor.size(); i++, j++)
	{
		
		if (cometitor[j]->getRank() >= sportData->GetRank() && !flag)
		{
			curIndex = i;
			// myself
			CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
			createMySelf(itemDockPos,menu,layer);
			j--;
			flag = true;
		}
		else
		{

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		itemBackGround->setPosition( itemDockPos );
		layer->addChild( itemBackGround );

		CCMenuItemImage *menuItem = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(RankListUIView::itemCallBack) );  
        CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUTTON_OFFSET_X, winSize.height * ITEM_BUTTON_OFFSET_Y ) );
		menuItem->setPosition( itemImagePos ); 
		menuItem ->setScaleX( BUTTON_SCALE );
		menuItem->setScaleY( BUTTON_SCALE );
		menuItem->setUserData( (void *)cometitor[j] );
		menu->addChild( menuItem );

		CCSprite *buttonText = CCSprite::create( "challengeText.png" );
		buttonText->setPosition( itemImagePos );
		layer->addChild( buttonText, 10 );

		sprintf( buff, "%s%d",UtilTools::GET_TEXT_FROM_LANG(513), cometitor[j]->getRank() );
	    CCLabelTTF* rank = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		rank->setAnchorPoint( ccp( 0, 0.5f ) );
		rank->setColor(CCCOLOR_YELLOW);
		CCPoint itemRankPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_RANK_OFFSET_X, winSize.height * ITEM_RANK_OFFSET_Y ) );
		rank->setPosition( itemRankPos );
		layer->addChild( rank );

 
		sprintf( buff, "lv.%d%s", cometitor[j]->getLevel() ,UtilTools::GET_TEXT_FROM_LANG(514) );
	    CCLabelTTF* level = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
		level->setColor(CCCOLOR_WHITE);
		level->setAnchorPoint( ccp( 0, 0.5f ) );
 
		CCPoint levelPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_LEVEL_OFFSET_X, winSize.height * ITEM_LEVEL_NUM_OFFSET_Y ) );
		level->setPosition( levelPos );
		layer->addChild( level );

		CCLabelTTF* name = CCLabelTTF::create( cometitor[j]->getName(), FONT_NAME_ARIAL_BOLD, 24 );
		name->setAnchorPoint( ccp( 0, 0.5f ) );
		name->setColor(CCCOLOR_GREEN);
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		name->setPosition( itemNamePos );
		layer->addChild( name );

		const vector<CompetitorHero> & herosArray = cometitor[j]->getHeros();
		for( unsigned int j = 0; j < herosArray.size(); j++ )
		{
			
			CCSprite *hero = CCSprite::create( ObjectHero::getIconById( herosArray[j].tableId ).c_str() );
			if (!hero)
			{
				continue;
			}
			
			CCPoint heroPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (ITEM_IMAGE_OFFSET_X + ITEM_IMAGE_DELTA_X * j), winSize.height * ITEM_IMAGE_OFFSET_Y ) );
			hero->setPosition( heroPos );
			hero->setScale( 0.5f );


			CCSprite *heroBg = CCSprite::create("n_pos_back_.png");
			heroBg->setPosition( heroPos );
			heroBg->setScale(0.5f);

			layer->addChild(heroBg);
			layer->addChild( hero, 10 );

			CCSprite *heroFrame = CCSprite::create( GameHelper::GetHeroColorById(herosArray[j].color).c_str());
			heroFrame->setPosition( heroPos );
			heroFrame->setScale( 0.5f );
			layer->addChild( heroFrame, 10 );			
		}
		}
	}



	if (!flag)
	{
		// myself
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		createMySelf(itemDockPos,menu,layer);

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

	if (flag)
	{
		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		mContent->setContentOffset( ccp(0, -(winSize.height * ( ITEM_START_Y - curIndex * ITEM_SPACE_DELTA_Y ) + contentSize.height - itemBackGround->getContentSize().height* 0.5 * 3) ));

	}
	
	addChild( mContent );
}

void RankListUIView::createMySelf(cocos2d::CCPoint itemDockPos, cocos2d::CCMenu *menu, cocos2d::CCLayer *layer)
{
	// myself

	char buff[MAX_STRING_BUFF_SIZE];
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	SportsData * sportData = DataPool::GetSingleton()->getSportsData();
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	CCSprite *itemBackGround = CCSprite::create( "level_list.png" );
    if (winSize.width > 640)
    {
        itemBackGround->setScaleX(SCALE_X - 0.04);
        itemBackGround->setScaleY(SCALE_Y + 0.05);
    }
    else
    {
        itemBackGround->setScaleX( 0.96f );
        itemBackGround->setScaleY( 1.05f );
    }

	itemBackGround->setPosition( itemDockPos );
	layer->addChild( itemBackGround );

 

	sprintf( buff, "%s%d", UtilTools::GET_TEXT_FROM_LANG(513),sportData->GetRank());
	CCLabelTTF* rank = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
	rank->setAnchorPoint( ccp( 0, 0.5f ) );
	rank->setColor(CCCOLOR_YELLOW);
	CCPoint itemRankPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_RANK_OFFSET_X, winSize.height * ITEM_RANK_OFFSET_Y ) );
	rank->setPosition( itemRankPos );
	layer->addChild( rank );

 

	sprintf( buff, "lv.%d%s", pSelf->playerData()->GetLevel(),UtilTools::GET_TEXT_FROM_LANG(514) );
	CCLabelTTF* level = CCLabelTTF::create( buff, FONT_NAME_ARIAL_BOLD, 24 );
	level->setAnchorPoint( ccp( 0, 0.5f ) );
	// 	CCPoint levelPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_LEVEL_NUM_OFFSET_X, winSize.height * ITEM_LEVEL_NUM_OFFSET_Y ) );
	CCPoint levelPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_LEVEL_OFFSET_X, winSize.height * ITEM_LEVEL_NUM_OFFSET_Y ) );
	level->setPosition( levelPos );
	level->setColor(CCCOLOR_YELLOW);
	layer->addChild( level );

	CCLabelTTF* name = CCLabelTTF::create( pSelf->playerData()->getName().c_str(), FONT_NAME_ARIAL_BOLD, 24 );
	name->setAnchorPoint( ccp( 0, 0.5f ) );
	CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
	name->setPosition( itemNamePos );
	name->setColor(CCCOLOR_YELLOW);
	layer->addChild( name );

	CCSprite *awardFrame = CCSprite::create( "info_frame.png" );
	CCPoint itemAwardPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_AWARD_OFFSET_X, winSize.height * ITEM_AWARD_OFFSET_Y ) );
	awardFrame->setScaleX( 1.10f );//0.90
	awardFrame->setPosition( itemAwardPos );
	layer->addChild( awardFrame );


	CCLabelTTF* award = CCLabelTTF::create( sportData->GetAwards().c_str(), FONT_NAME_ARIAL_BOLD, 24 );	
	award->setColor(ccGREEN);
	award->setPosition( itemAwardPos );
	layer->addChild( award );
	
	string timeStr = UtilTools::ConvertMillisecondToTimeString( sportData->GetWelfareCD() );
	timeStr  = UtilTools::GET_TEXT_FROM_LANG(515) + timeStr;
	mTimeFresh = CCLabelTTF::create( timeStr.c_str(), FONT_NAME_ARIAL_BOLD, 24 );
	CCPoint itemTimePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_TIME_OFFSET_X, winSize.height * ITEM_TIME_OFFSET_Y ) );
	mTimeFresh->setPosition( itemTimePos );
	mTimeFresh->setColor(CCCOLOR_YELLOW);
	layer->addChild( mTimeFresh );

	mContent->setContentOffset(CCPointMake( 0, itemDockPos.y));
}

void RankListUIView::itemCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	SportsData * sportData = DataPool::GetSingleton()->getSportsData();
	int challengeNum = sportData->GetChallengeCountRemain();

	Competitor* pCompetitor = (Competitor *)(((CCNode *)pSender)->getUserData());
	if (challengeNum > 0)
	{
		if( pCompetitor )
		{
			SendLogicPacket::ChallengeArena(pCompetitor->getGuid());
		}
	}
	else
	{
		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(560),this);
		dialog->setDailogUserData(pCompetitor);
		dialog->setTag(DIALOG_MODEL_TAG_NUM);
		addChild(dialog,10);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void RankListUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	//todo 

	

	int iTag = pSender->getTag();
	if (iTag == DIALOG_MODEL_TAG_NUM)
	{
		ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
		PlayerData* pData = pSelf->playerData();

		if(pData->GetGold() > MAX_CHALLENGE_GOLD)
		{
			Competitor* pCompetit = (Competitor*)pSender->getDailogUserData();
			SendLogicPacket::ChallengeArena(pCompetit->getGuid());
		}
		else
		{
			ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(550),this);
			dialog->setTag(DIALOG_MODEL_TAG_GOLD);
			addChild(dialog,11);
		}
	}
	else if(iTag == DIALOG_MODEL_TAG_GOLD)
	{
		EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
	}

	pSender->closeDialogView();
	
}
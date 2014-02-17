#include "./ui/placardUIView.h"
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
#include "./DataBase/DataBaseSystem.h"

#define CONTENT_POS_X            (0.060f)
#define CONTENT_POS_Y            (0.250f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.41f)

#define ITEM_DOCK_X              (0.45f)
#define ITEM_SPACE_DELTA_Y       (0.1f)
#define ITEM_START_Y             (0.1f)

using namespace cocos2d;
USING_NS_CC_EXT;
 
placardUIView::placardUIView()
 
{ 
	mContent = NULL;
	baseLayer = NULL;
}

placardUIView::~placardUIView()
{ 
}
void placardUIView::closeInfoCallBack(cocos2d::CCObject *pSender)
{

	CCAction* popupLayer = CCSequence::create(
		CCScaleTo::create(0.12f, 1.05f),
		CCScaleTo::create(0.16f, 0.95f),
		CCScaleTo::create(0.16f, 0.0f),CCCallFunc::create(this,callfunc_selector(placardUIView::closeCallFunc)), NULL);
	baseLayer->runAction( popupLayer );
}

void placardUIView::closeCallFunc()
{
	vector<string> str;
	str.clear();
	str.push_back("close the newsPage");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_PLACARD_SHOW,str);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool placardUIView::init()
{
	

    bool bRet = true;

	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if (baseLayer)
	{
		baseLayer->removeFromParentAndCleanup(true);
		baseLayer = NULL;
	}

	CCLayerColor *colorLayer = CCLayerColor::create(ccc4(0,0,0,200),winSize.width, winSize.height);
	addChild(colorLayer);
	
	baseLayer = CCLayer::create();
	baseLayer->setContentSize(winSize);
	addChild(baseLayer);

	
	
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create();
	CCMenuEx *menu = CCMenuEx::create(); 
	

	//公告背景图
	CCSprite *newsBgSprite = CCSprite::create("n_newsBg.png");
	newsBgSprite->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.58f));
	newsBgSprite->setScaleY(SCALE_Y);
	newsBgSprite->setScaleX(SCALE_X);
	baseLayer->addChild(newsBgSprite);

	//关闭窗口的按钮
	CCMenuItemImage *closeBtn = CCMenuItemImage::create("close.png", "close.png",this, menu_selector(placardUIView::closeInfoCallBack));
	CCPoint closeBtnPos = ccp(newsBgSprite->getContentSize().width, newsBgSprite->getContentSize().height * 0.82f);
	closeBtn->setPosition( closeBtnPos);
	menu->addChild( closeBtn );

	menu->setPosition( CCPointZero );  
	newsBgSprite->addChild( menu );

	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_PLACARD);
	 const stDBC_FILE_PLACARD	*  pTableData = X_NULL;
	 X_INT num = pDataFile->GetRecordsNum();

	 CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * ITEM_SPACE_DELTA_Y * num );
	 float lblHeight = 5.0f;
	 float lastPicHeight = 0;
	 CCPoint itemDockPos;
	for (X_UINT i = 0;i< num ;i++)
	{
		pTableData = (const stDBC_FILE_PLACARD*)pDataFile->GetFieldsByLineNum(i);
		if (!pTableData)
		{
			continue;
		}
		CCSprite *itemBackGround = CCSprite::create( pTableData->img );
		
		lblHeight += itemBackGround->getContentSize().height;
		lastPicHeight = itemBackGround->getContentSize().height;

// 		if (i == 0)
// 		{
			itemDockPos = CCPointMake( layer->getContentSize().width * 0.45f, winSize.height * ( ITEM_START_Y + i * ITEM_SPACE_DELTA_Y ) + lblHeight );
// 		}
// 		else
// 		{
// 			itemDockPos.y += lastPicHeight;
// 		}
		

		itemBackGround->setAnchorPoint(ccp(0.5f, 1.0f));
		itemBackGround->setPosition( itemDockPos );
		layer->addChild( itemBackGround );

		
	}
	contentSize.height+= lblHeight;

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	baseLayer->addChild( mContent );

	//动画效果
	baseLayer->setScale(0.1f);
	CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0f, 0.5f),
		                                          CCScaleTo::create(0.12f, 1.1f),
		                                          CCScaleTo::create(0.16f, 0.90f),
	                                          CCScaleTo::create(0.16f, 1.0f), NULL);
	baseLayer->runAction( popupLayer );


	return bRet;
}

 
void placardUIView::onDataUpdate( bool isDataValid )
{
	 
}


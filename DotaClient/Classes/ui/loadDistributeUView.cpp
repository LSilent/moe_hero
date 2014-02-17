#include "./ui/loadDistributeUIView.h"
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



using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.05f)
#define CONTENT_POS_Y            (0.25f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.60f)

#define ITEM_DOCK_X              (0.455f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.265f)
#define ITEM_IMAGE_OFFSET_Y      (0.002f)

#define ITEM_NAME_OFFSET_X       (-0.18f)
#define ITEM_NAME_OFFSET_Y       (0.022f)

#define ITEM_LOAD_OFFSET_X       (-0.18f)
#define ITEM_LOAD_OFFSET_Y       (-0.038f)

#define ITEM_ADD_OFFSET_X        (0.30f)
#define ITEM_ADD_OFFSET_Y        (0)

#define ITEM_POINT_OFFSET_X      (0.20f)
#define ITEM_POINT_OFFSET_Y      (0)

#define ITEM_SUB_OFFSET_X        (0.10f)
#define ITEM_SUB_OFFSET_Y        (0)

static const ccColor3B ccCOLOR1={247,206,0};
static const ccColor3B ccCOLOR2={128,255,64};

LoadDistributeUIView::LoadDistributeUIView()
: mLoadPointLeft(NULL)
{
	mContent = NULL;
}

LoadDistributeUIView::~LoadDistributeUIView()
{
	CC_SAFE_RELEASE(mLoadPointLeft);


}


void LoadDistributeUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler LoadDistributeUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler LoadDistributeUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonOK", LoadDistributeUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonCancel", LoadDistributeUIView::onButtonCancel);

	return NULL;
}

void LoadDistributeUIView::onButtonOK(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	SendLogicPacket::DistribHeroBearpoint(mHeroArray,mLoadDistributeArray);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void LoadDistributeUIView::onButtonCancel(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool LoadDistributeUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLoadPointLeft", CCLabelBMFont *, this->mLoadPointLeft);
	
	return false;
}

bool LoadDistributeUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
    return bRet;
}

// on "init" you need to initialize your instance
bool LoadDistributeUIView::init()
{
    bool bRet = true;

   

    return bRet;
}



void LoadDistributeUIView::onDataUpdate( bool isDataValid )
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

	char buff[MAX_STRING_BUFF_SIZE];
	
	// get heros
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	// set left point
	mLoadPointLeftNum = pSelf->playerData()->GetBearPoint();
	sprintf( buff, "%s%d",UtilTools::GET_TEXT_FROM_LANG(552) ,mLoadPointLeftNum );
	mLoadPointLeft->setString( buff);
	//mLoadPointLeft->setColor(ccCOLOR1);
	mLoadPointLeft->setColor(ccYELLOW);

	X_INT size = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	ObjectHero *pHero;
	
	mAddLabels.clear();
	mdisableItems.clear();
	mSubLabels.clear();
	mSubdisableItems.clear();
	mLoadDistributeArray.clear();
	mLoadDistributeArray.resize( size, 0 );
	mCurLoadPoint.clear();
    mCurLoadPoint.resize( size, 0 );
	mMaxLoadPoint.clear();
	mMaxLoadPoint.resize( size, 0 );

	mLoadDistributeViewArray.clear();
	mLoadDistributeViewArray.resize( size, 0 );
	mLoadViewArray.clear();
	mLoadViewArray.resize( size, 0 );
	mHeroArray.clear();
	mHeroArray.resize( size, 0 );


	vector<ObjectHero *> bagHeros;
	bagHeros.clear();

	// get window size
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	mContent = CCScrollViewEx::create();  
    CCLayer *layer = CCLayer::create(); 

	CCMenuHoldEx *menu = CCMenuHoldEx::create(); 
	 CCMenuHoldEx::mTime = 0.1f;
	int curHeroCount = 0;
	for (X_INT i = 0 ;i< size;i++)
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);

		if( !pHero )
			continue;

		curHeroCount++;
		bagHeros.push_back(pHero);
		
	}

	sort(bagHeros.begin(),bagHeros.end(),sortDistribute);


	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height  * curHeroCount * ITEM_SPACE_DELTA_Y );
	
	//Ã¿¸öÓ¢ÐÛ
	for (X_INT i = 0 ;i< curHeroCount;i++)
	{
		pHero = bagHeros.at(i);//pSelf->getHero(i,EM_HERO_CONTAINER_BAG);

		if( !pHero )
			continue;

		mHeroArray[i] = pHero;

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHero->GetHeadIcon().c_str(), pHero->GetHeadIcon().c_str(), this, menu_selector(LoadDistributeUIView::itemInfoCallBack) );  
        CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItem->setPosition( itemImagePos ); 
		menuItem->setUserData( (void *)i );
		menuItem->setScale(0.75);
		menu->addChild( menuItem );

		CCSprite *headBg = CCSprite::create(pHero->getHeroColor().c_str());
		headBg->setPosition(menuItem->getPosition());
		headBg->setScale(0.75);
		layer->addChild(headBg,1);

		CCMenuItemImage *menuItemAdd = CCMenuItemImage::create( "n_add_button.png", "n_add_button.png", this, menu_selector(LoadDistributeUIView::addCallBack) );  
        CCPoint itemAddPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_ADD_OFFSET_X, winSize.height * ITEM_ADD_OFFSET_Y ) );
		menuItemAdd->setPosition( itemAddPos ); 
		menuItemAdd->setUserData( (void *)i );
 
		menu->addChild( menuItemAdd );
 
		mAddLabels.push_back(menuItemAdd);

		CCMenuItemImage *menuItemSub = CCMenuItemImage::create( "n_sub_button.png", "n_sub_button.png", this, menu_selector(LoadDistributeUIView::subCallBack) );  
        CCPoint itemSubPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_SUB_OFFSET_X, winSize.height * ITEM_SUB_OFFSET_Y ) );
		menuItemSub->setPosition( itemSubPos ); 
		menuItemSub->setUserData( (void *)i );
		menu->addChild( menuItemSub );
 
		mSubLabels.push_back(menuItemSub);
 

		CCLabelBMFont* mName = CCLabelBMFont::create( pHero->GetName().c_str(), FNT_HERO_NAME_GREEN );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		mName->setColor(ccCOLOR2);
		layer->addChild( mName );
		mName->setScale(SCALE_BMF);

		// set load point
		mCurLoadPoint[i] = pHero->GetBearPoint();
		mMaxLoadPoint[i] = pHero->GetMaxBearPoint();
		sprintf( buff, "%d / %d", mCurLoadPoint[i], mMaxLoadPoint[i] );
		mLoadViewArray[i] = CCLabelBMFont::create( buff, FNT_NAME_LARGEGREEN );
		mLoadViewArray[i]->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemLoadInfoPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_LOAD_OFFSET_X, winSize.height * ITEM_LOAD_OFFSET_Y ) );
		mLoadViewArray[i]->setPosition( itemLoadInfoPos );
		layer->addChild( mLoadViewArray[i] );

		mLoadViewArray[i]->setScale(SCALE_BMF);


		sprintf( buff, "%d", mLoadDistributeArray[i] );
		mLoadDistributeViewArray[i] = CCLabelBMFont::create( buff, FNT_NAME_LARGEGREEN );
		mLoadDistributeViewArray[i]->setAnchorPoint( ccp( 0.5, 0.5f ) );
		CCPoint itemPointPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_POINT_OFFSET_X, winSize.height * ITEM_POINT_OFFSET_Y ) );
		mLoadDistributeViewArray[i]->setPosition( itemPointPos );
		layer->addChild( mLoadDistributeViewArray[i] );		
		mLoadDistributeViewArray[i]->setScale(SCALE_BMF);
		if (mCurLoadPoint[i] == mMaxLoadPoint[i])
		{
			 
			menuItemAdd->setEnabled(false);
			menuItemAdd->setColor(ICON_COLOR_GRAY);

			mdisableItems.push_back(menuItemAdd);

		 
			menuItemSub->setEnabled(false);
			menuItemSub->setColor(ICON_COLOR_GRAY);
			mSubdisableItems.push_back(menuItemSub);
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
	updataEnablePoint();
}


bool LoadDistributeUIView::sortDistribute(const ObjectHero *pHero1,const ObjectHero *pHero2)
{

	if (pHero1->GetQuality() == pHero2->GetQuality())
	{
		if (pHero1->GetLevel() == pHero2->GetLevel())
		{
			if (pHero1->GetBearPoint() == pHero2->GetBearPoint())
			{
				return pHero1->GetTableID() < pHero2->GetTableID();
				
			}
			else
			{
				return pHero1->GetBearPoint() > pHero2->GetBearPoint();
			}
		}
		else
		{
			return pHero1->GetLevel() > pHero2->GetLevel();
		}
	}
	else
	{
		return pHero1->GetQuality() > pHero2->GetQuality();
	}
}


void LoadDistributeUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	
	int index = (int)(((CCNode *)pSender)->getUserData());

	//TODO
}

void LoadDistributeUIView::addCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	
	int index = (int)(((CCNode *)pSender)->getUserData());
	((CCMenuItemImage *)pSender)->setEnabled(true);
	((CCMenuItemImage *)pSender)->setColor(ccWHITE);

	char buff[MAX_STRING_BUFF_SIZE];

	if( mLoadPointLeftNum > 0 && mCurLoadPoint[index] < mMaxLoadPoint[index] )
	{
		mLoadPointLeftNum -=1;
		mLoadDistributeArray[index] +=1;
		mCurLoadPoint[index] += 1;
		
		sprintf( buff, "%s%d", UtilTools::GET_TEXT_FROM_LANG(552) ,mLoadPointLeftNum );
		mLoadPointLeft->setString( buff );

		sprintf( buff, "%d", mLoadDistributeArray[index] );
		mLoadDistributeViewArray[index]->setString( buff );

		sprintf( buff, "%d / %d", mCurLoadPoint[index], mMaxLoadPoint[index] );
		mLoadViewArray[index]->setString( buff );
		CCLOG(buff);
	}

	if (mLoadPointLeftNum == 0)
	{
		checkEnablePoint(false);
	}
	updataEnablePoint();
	if(mCurLoadPoint[index] == mMaxLoadPoint[index])
	{
		((CCMenuItemImage *)pSender)->setEnabled(false);
		((CCMenuItemImage *)pSender)->setColor(ICON_COLOR_GRAY);


		mdisableItems.push_back(((CCMenuItemImage *)pSender));
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void LoadDistributeUIView::subCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	
	int index = (int)(((CCNode *)pSender)->getUserData());

	char buff[MAX_STRING_BUFF_SIZE];

	if( mLoadDistributeArray[index] > 0 )
	{
		mLoadPointLeftNum +=1;
		mLoadDistributeArray[index]-=1;
		mCurLoadPoint[index] -=1;
		
		sprintf( buff, "%s%d",UtilTools::GET_TEXT_FROM_LANG(552), mLoadPointLeftNum );
		mLoadPointLeft->setString( buff );

		sprintf( buff, "%d", mLoadDistributeArray[index] );
		mLoadDistributeViewArray[index]->setString( buff );

		sprintf( buff, "%d / %d", mCurLoadPoint[index], mMaxLoadPoint[index] );
		mLoadViewArray[index]->setString( buff );
	}

	if (mLoadPointLeftNum == 1)
	{
		checkEnablePoint(true);
	}
	if( mLoadDistributeArray[index] <= 0 )
	{
		updataEnablePoint();
	}
 
	if (mCurLoadPoint[index] == mMaxLoadPoint[index]-1)
	{
		CCMenuItemImage *menuItem = mAddLabels[index];
 
		menuItem->setEnabled(true);
		menuItem->setColor(ccWHITE);

		vector<CCMenuItemImage *>::iterator iter = find(mdisableItems.begin(),mdisableItems.end(),menuItem);
		if (iter != mdisableItems.end())
		{
			mdisableItems.erase(iter);
		}
		
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	
}
void LoadDistributeUIView::updataEnablePoint()
{
	int num = mSubLabels.size();
	for (int i = 0;i < num; i ++)
	{
		CCMenuItemImage *subItem  = mSubLabels[i];
		 
		if (!subItem)
		{
			continue;
		}
		
		if (mLoadDistributeArray[i] <= 0)
		{
			 
			subItem->setEnabled(false);
			subItem->setColor(ICON_COLOR_GRAY);
			vector<CCMenuItemImage *>::iterator iter = find(mSubdisableItems.begin(),mSubdisableItems.end(),subItem);
			if (iter == mSubdisableItems.end())
			{
				 	mSubdisableItems.push_back(subItem);
			}
		}
		else
		{
			vector<CCMenuItemImage *>::iterator iter = find(mSubdisableItems.begin(),mSubdisableItems.end(),subItem);
			if (iter == mSubdisableItems.end())
			{
				continue;
			}
			mSubdisableItems.erase(iter);
			 
			subItem->setEnabled(true);
			subItem->setColor(ccWHITE);
		}
	}
}
void LoadDistributeUIView::checkEnablePoint(bool flag)
{
	int num = mAddLabels.size();
	for (int i = 0;i < num; i ++)
	{
		CCMenuItemImage *addItem= mAddLabels[i];
	 
		if (!flag)
		{
	 
			addItem->setEnabled(false);
			addItem->setColor(ICON_COLOR_GRAY);
			vector<CCMenuItemImage *>::iterator iter = find(mdisableItems.begin(),mdisableItems.end(),addItem);
			if (iter == mdisableItems.end())
			{
				 	mdisableItems.push_back(addItem);
			}
		}
		else
		{
			vector<CCMenuItemImage *>::iterator iter = find(mdisableItems.begin(),mdisableItems.end(),addItem);
			if (iter == mdisableItems.end())
			{
				continue;
			}
			mdisableItems.erase(iter);
			addItem->setEnabled(true);
			addItem->setColor(ccWHITE);
		}
		
	}
	
}
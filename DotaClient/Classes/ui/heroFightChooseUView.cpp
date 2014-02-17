#include "./ui/heroFightChooseUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"

#include "./ui/heroFightChooseUI.h"
#include "./datapool/WoodData.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.080f)
#define CONTENT_POS_Y            (0.300f)

#define CONTENT_VIEW_SIZE_X      (0.84f)
#define CONTENT_VIEW_SIZE_Y      (0.60f)

#define ITEM_SPACE_DELTA_X       (0.220f)
#define ITEM_SPACE_DELTA_Y       (0.180f)

#define ITEM_START_X             (0.09f)
#define ITEM_START_Y             (0.45f)

#define ITEM_COLUMN_NUM          3
#define ITEM_LINE_NUM            3

HeroFightChooseUIView::HeroFightChooseUIView()
: mButtonOK(NULL)
, mButtonOKText(NULL)
//, mHeroTotalNum1(NULL)
//, mHeroTotalNum2(NULL)
, mFightNum(NULL)
{
	mContent = NULL;
	mPageCtrl = NULL;

	mCheckedCount = 0;
	mCurHeroTotal = 0;

	guideLayer = NULL;
}

HeroFightChooseUIView::~HeroFightChooseUIView()
{
	CC_SAFE_RELEASE(mButtonOK);
	CC_SAFE_RELEASE(mButtonOKText);

	CC_SAFE_RELEASE(mFightNum);
	//CC_SAFE_RELEASE(mHeroTotalNum1);
	//CC_SAFE_RELEASE(mHeroTotalNum2);
}


void HeroFightChooseUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler HeroFightChooseUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonOK", HeroFightChooseUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCancel", HeroFightChooseUIView::onButtonCancel);
	return NULL;    
}

SEL_CCControlHandler HeroFightChooseUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	

	return NULL;
}

void HeroFightChooseUIView::onButtonOK(cocos2d::CCObject * pSender)
{
	X_INT  size = mHeroItemCheckArray.size();
	vector<ObjectHero*>  Heroes;
	Heroes.clear();
	ObjectHero* pHero;
	for (X_INT i = 0;i<size;i++)
	{
		pHero = X_NULL;
		if (!mHeroItemCheckArray[i])continue;
		if (mHeroItemCheckArray[i]->isVisible())
		{
			pHero = static_cast<ObjectHero*>(mHeroItemCheckArray[i]->getUserData());
			if (!pHero)continue;
			Heroes.push_back(pHero);
		}
	}
	if (Heroes.size() <= MAX_MATRIX_CELL_COUNT)
	{
		SendLogicPacket::SetMatrixHeros(Heroes);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROFIGHTCHOOSE_CLOSE);
	}

	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroFightChooseUIView::onButtonCancel(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROFIGHTCHOOSE_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool HeroFightChooseUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonOK", CCMenuItemImage *, this->mButtonOK);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonOKText", CCSprite *, this->mButtonOKText);
	

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFightNum", CCLabelBMFont *, this->mFightNum);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroTotalNum1", CCSprite *, this->mHeroTotalNum1);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroTotalNum2", CCSprite *, this->mHeroTotalNum2);

	return false;
}

bool HeroFightChooseUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool HeroFightChooseUIView::init()
{
    bool bRet = true;

	return bRet;
}

char *numText[10]={"1.png","2.png","3.png","4.png","5.png","6.png","7.png","8.png","9.png","0.png"};

void HeroFightChooseUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}

	X_INT tipId = ((HeroFightChooseUI *)this->getUserData())->getTipId();

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
			if (tipId == 9)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroFightChooseUIView::onButtonOK),NULL);
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

	mHeroItemArray.clear();
	mHeroItemCheckArray.clear();

	mCheckedCount = 0;
	mCurHeroTotal = 0;

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	int size  = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);

	
	for( int i = 0; i < size; i++ )
	{
		const ObjectHero* pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}
		mCurHeroTotal++;

		if( pSelf->HeroIsBattle(pHero) )
			mCheckedCount ++;
	}

	
 
	char buffHeroNum[MAX_STRING_BUFF_SIZE];

	X_INT matrix_max_hero =0;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_MATRIX_MAX_HERO);
		if (pTableData)
		{
			matrix_max_hero = pTableData->m_value;
		}	
	}
	sprintf(buffHeroNum, "%d/%d", mCheckedCount, matrix_max_hero);//mCurHeroTotal
	mFightNum->setString(buffHeroNum);


// 	mFightTotalNum->setString(UtilTools::IntToString(mCurHeroTotal));
// 	mFightNum->setString(UtilTools::IntToString(mCheckedCount));

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = mCurHeroTotal / pageNum + (((mCurHeroTotal % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y);
	mContent = CCScrollViewPage::create();
	mContent->createContainer(this,totalPage,viewSize); 
	 
  /*
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx *menu = CCMenuEx::create(); 
	CCSize contentSize( 0, 0 );

	int pageIndex = 0;
	int lineIndex = 0;
	int columnIndex = 0;
	const ObjectHero* pHero = X_NULL;
	for( int i = 0; i < size; i++ )
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}
		
		if( pSelf->HeroIsBattle(pHero) )
			mCheckedCount ++;

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHero->GetHeadIcon().c_str(), pHero->GetHeadIcon().c_str(), this, menu_selector(HeroFightChooseUIView::heroItemCallBack) );  
		CCPoint itemPos = CCPointMake( winSize.width * ( ITEM_START_X + pageIndex * ITEM_SPACE_DELTA_X * ITEM_COLUMN_NUM + ITEM_SPACE_DELTA_X * columnIndex), winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ) );
		menuItem->setPosition( itemPos ); 

		CCSprite *headBg = CCSprite::create(chooseQuality[pHero->GetQuality()-1]);
		headBg->setPosition(menuItem->getPosition());
		layer->addChild(headBg);
		
		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setPosition( itemPos );		
  	    checkItem->setUserData( (void *)(pHero) );
		checkItem->setVisible(pSelf->HeroIsBattle(pHero));
		layer->addChild( checkItem, 10 );

		mHeroItemArray.push_back( menuItem );
		mHeroItemCheckArray.push_back( checkItem );

		menuItem->setUserData( (void *)(checkItem) );

		contentSize.width = max( contentSize.width, itemPos.x - winSize.width * ITEM_START_X + winSize.width * ITEM_SPACE_DELTA_X );
		contentSize.height = max( contentSize.height, winSize.height * ITEM_START_Y - itemPos.y + winSize.height * ITEM_SPACE_DELTA_Y );

		menu->addChild( menuItem );

		columnIndex ++;
		if( columnIndex >= ITEM_COLUMN_NUM )
		{
			columnIndex = 0;
			lineIndex ++;

			if( lineIndex >= ITEM_LINE_NUM )
			{
				lineIndex = 0;
				pageIndex ++;
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
	*/

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentOffset(CCPointZero);
	mContent->setDirection( kCCScrollViewDirectionHorizontal );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	addChild( mContent );

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * -0.050));
	addChild(mPageCtrl);








}

void HeroFightChooseUIView::heroItemCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
// 	if( mContent->mIsMoved )
// 		return;

	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	CCNode *checkItem = (CCNode *)(((CCNode *)pSender)->getUserData());

	checkItem->setVisible( !checkItem->isVisible() );

	if( checkItem->isVisible() )
		mCheckedCount ++;
	else
		mCheckedCount --; 

	// avoid choose null
	if( mCheckedCount == 0 )
	{
		mButtonOK->setEnabled( false );
		mButtonOKText->setColor( ccGRAY );
	}
	else
	{
		mButtonOK->setEnabled( true );
		mButtonOKText->setColor( ccWHITE );
	}

	assert( mHeroItemArray.size() == mHeroItemCheckArray.size() );
	if( mCheckedCount >= MAX_MATRIX_CELL_COUNT - 1 )
	{
		for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
		{
			if( !mHeroItemCheckArray[i]->isVisible() )
			{
				mHeroItemArray[i]->setEnabled( false );
				mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);//80
			}
		}
	}
	else
	{
		for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
		{
			if( !mHeroItemCheckArray[i]->isVisible() )
			{
				mHeroItemArray[i]->setEnabled( true );
				mHeroItemArray[i]->setColor( ccWHITE );
			}
		}
	}

	//ÅÅ³ý·¥Ä¾³¡Ó¢ÐÛ
	WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
	for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
	{
		CCNode*  menuItem = (CCNode*)((mHeroItemArray[i])->getUserData());
		const ObjectHero* pHero = (const ObjectHero*)(menuItem->getUserData());
		if (pWoodData->GetSelfWoodData()->HeroIsDefWood(pHero) && !mHeroItemCheckArray[i]->isVisible())
		{
			mHeroItemArray[i]->setEnabled( false );
			mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);
		}
	}

	X_INT matrix_max_hero =0;
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_MATRIX_MAX_HERO);
		if (pTableData)
		{
			matrix_max_hero = pTableData->m_value;
		}	
	}
	char buffHeroNum[MAX_STRING_BUFF_SIZE];
	sprintf(buffHeroNum, "%d/%d", mCheckedCount, matrix_max_hero );//mCurHeroTotal
	mFightNum->setString(buffHeroNum);



	guideLayer = NULL;

}

void HeroFightChooseUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void HeroFightChooseUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool HeroFightChooseUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	 

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
/*	int size  = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);*/


	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = mCurHeroTotal / pageNum + (((mCurHeroTotal % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(mCurHeroTotal-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	menu->setPosition( CCPointZero );
	pPage->addChild(menu);

	int lineIndex = 0;
	int columnIndex = 0;
	const ObjectHero* pHero = X_NULL;
	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}

		CCSprite *headBg = CCSprite::create( pHero->getHeroColor().c_str());

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHero->GetHeadIcon().c_str(), pHero->GetHeadIcon().c_str(), this, menu_selector(HeroFightChooseUIView::heroItemCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - headBg->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM+1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+headBg->getContentSize().width/2 + columnIndex * headBg->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 

		headBg->setPosition(menuItem->getPosition());
		headBg->setZOrder(2);
		
		CCSprite *heroIcon = CCSprite::create("n_pos_back_.png");
		heroIcon->setPosition(menuItem->getPosition());
		heroIcon->setZOrder(0);
		pPage->addChild(heroIcon);

		pPage->addChild(headBg);

		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setScaleY(1.18f);
		checkItem->setPosition( itemPos );		
		checkItem->setUserData( (void *)(pHero) );
		checkItem->setVisible(pSelf->HeroIsBattle(pHero));
		pPage->addChild( checkItem, 10 );


		mHeroItemArray.push_back( menuItem );
		mHeroItemCheckArray.push_back( checkItem );

		menuItem->setUserData( (void *)(checkItem) );

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


		menu->setZOrder(1);

	}

	if (nPage == totalPage-1)
	{
		//ÅÅ³ý·¥Ä¾³¡Ó¢ÐÛ
		WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
		for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
		{
			CCNode*  menuItem = (CCNode*)((mHeroItemArray[i])->getUserData());
			const ObjectHero* pHero = (const ObjectHero*)(menuItem->getUserData());
			if (pWoodData->GetSelfWoodData()->HeroIsDefWood(pHero) && !mHeroItemCheckArray[i]->isVisible())
			{
				mHeroItemArray[i]->setEnabled( false );
				mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);
			}
		}
		if (mCheckedCount == 5)
		{
			for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
			{

				if( !mHeroItemCheckArray[i]->isVisible() )
				{
					mHeroItemArray[i]->setEnabled( false );
					mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);//
				}
			}
		}

		X_INT tipId = ((HeroFightChooseUI *)this->getUserData())->getTipId();

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
				if (tipId == 8)
				{
					int index = 1;
					int iSize = mHeroItemArray.size();
					if (iSize < 2) {return true;}
					//if (iSize <= 1) {index = iSize - 1;}
					
					guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroFightChooseUIView::heroItemCallBack),mHeroItemArray[index]);
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
void HeroFightChooseUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void HeroFightChooseUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
}
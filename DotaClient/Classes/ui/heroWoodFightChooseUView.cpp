#include "./ui/heroWoodFightChooseUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/WoodData.h"
#include "./ui/heroWoodFightChooseUI.h"


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

HeroWoodFightChooseUIView::HeroWoodFightChooseUIView()
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

HeroWoodFightChooseUIView::~HeroWoodFightChooseUIView()
{
	CC_SAFE_RELEASE(mButtonOK);
	CC_SAFE_RELEASE(mButtonOKText);

	CC_SAFE_RELEASE(mFightNum);
	//CC_SAFE_RELEASE(mHeroTotalNum1);
	//CC_SAFE_RELEASE(mHeroTotalNum2);
}


void HeroWoodFightChooseUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{

}


SEL_MenuHandler HeroWoodFightChooseUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonOK", HeroWoodFightChooseUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCancel", HeroWoodFightChooseUIView::onButtonCancel);
	return NULL;    
}

SEL_CCControlHandler HeroWoodFightChooseUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void HeroWoodFightChooseUIView::onButtonOK(cocos2d::CCObject * pSender)
{
	guideLayer = NULL;
	X_UINT  size = mHeroItemCheckArray.size();
	vector<ObjectHero*>  Heroes;
	
	for (X_UINT i = 0;i < size;i++)
	{
		if (!mHeroItemCheckArray[i])continue;
		if (mHeroItemCheckArray[i]->isVisible())
		{
			ObjectHero* pHero = static_cast<ObjectHero*>(mHeroItemCheckArray[i]->getUserData());
			if (!pHero)continue;
			Heroes.push_back(pHero);
		}
	}
#if  (WOOD_HERO_SHOW_IN_CHOOSE == 1 )
#else
	WoodsData* pWoodData = DataPool::GetSingleton()->GetWoodData();
	Heroes.push_back(pWoodData->GetSelfWoodData()->GetSelfDefHero());
#endif
	if (Heroes.size() <= MAX_MATRIX_CELL_COUNT )
	{
		X_GUID  GuidHero[MAX_MATRIX_CELL_COUNT];
		for (X_UINT i = 0; i< Heroes.size();++i)
		{
			GuidHero[i] = Heroes[i]->GetGuid();
		}	
	

		SendLogicPacket::SetWoodMatrixHeros(GuidHero);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROWOODFIGHTCHOOSE_CLOSE);
		
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroWoodFightChooseUIView::onButtonCancel(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROWOODFIGHTCHOOSE_CLOSE);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool HeroWoodFightChooseUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonOK", CCMenuItemImage *, this->mButtonOK);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonOKText", CCSprite *, this->mButtonOKText);
	

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFightNum", CCLabelBMFont *, this->mFightNum);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroTotalNum1", CCSprite *, this->mHeroTotalNum1);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHeroTotalNum2", CCSprite *, this->mHeroTotalNum2);

	return false;
}

bool HeroWoodFightChooseUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool HeroWoodFightChooseUIView::init()
{
    bool bRet = true;

	return bRet;
}

static char *numText[10]={"1.png","2.png","3.png","4.png","5.png","6.png","7.png","8.png","9.png","0.png"};

void HeroWoodFightChooseUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{

		return;
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



	WoodsData* pWoodData = DataPool::GetSingleton()->GetWoodData();
	for( int i = 0; i < size; i++ )
	{
		const ObjectHero* pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}
		mCurHeroTotal++;

		if( pWoodData->GetSelfWoodData()->HeroIsDefWood(pHero) )
			mCheckedCount ++;
	}

	//加入伐木场英雄
	if (pWoodData->GetSelfWoodData()->GetSelfDefHero() != NULL)
	{
		mCheckedCount ++;
		mCurHeroTotal++;
	}
	 

	char buffHeroNum[MAX_STRING_BUFF_SIZE];
	sprintf(buffHeroNum, "%d/%d", mCheckedCount,MAX_MATRIX_CELL_COUNT );//mCurHeroTotal
	mFightNum->setString(buffHeroNum);
 
	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = mCurHeroTotal / pageNum + (((mCurHeroTotal % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y);
	mContent = CCScrollViewPage::create();
	mContent->createContainer(this,totalPage,viewSize); 
	 
  
	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentOffset(CCPointZero);
	mContent->setDirection( kCCScrollViewDirectionHorizontal );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	addChild( mContent );

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * -0.050f));
	addChild(mPageCtrl);

	X_INT tipId = ((HeroWoodFightChooseUI *)this->getUserData())->getTipId();
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
			case 41:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(HeroWoodFightChooseUIView::guideHeroItemCallBack),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 42:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(HeroWoodFightChooseUIView::onButtonOK),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				break;
			}
		}
	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}

}
void HeroWoodFightChooseUIView::guideHeroItemCallBack( cocos2d::CCObject* pSender )
{
	guideLayer = NULL;
}

void HeroWoodFightChooseUIView::heroItemCallBack( cocos2d::CCObject* pSender )
{
	guideLayer = NULL;
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	CCNode*  menuItem = (CCNode*)(((CCNode*)pSender)->getUserData());
	const ObjectHero* pHero = (const ObjectHero*)(menuItem->getUserData());
	WoodsData* pWoodData = DataPool::GetSingleton()->GetWoodData();
	//伐木场英雄不能取消
	if (pHero->GetGuid() == pWoodData->GetSelfWoodData()->m_DefenceHeroID)
	{

		vector<string> strV(1,UtilTools::GET_TEXT_FROM_LANG(646));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return ;
	}
	 
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
	if( mCheckedCount >= MAX_MATRIX_CELL_COUNT  )
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


	//排除出战英雄
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	for( unsigned int i = 0; i < mHeroItemArray.size(); i++ )
	{
		CCNode*  menuItem = (CCNode*)((mHeroItemArray[i])->getUserData());
		const ObjectHero* pHero = (const ObjectHero*)(menuItem->getUserData());
		if (pSelf->HeroIsBattle(pHero) && !mHeroItemCheckArray[i]->isVisible())
		{
			mHeroItemArray[i]->setEnabled( false );
			mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);
		}
	}

	char buffHeroNum[MAX_STRING_BUFF_SIZE];
	sprintf(buffHeroNum, "%d/%d", mCheckedCount, MAX_MATRIX_CELL_COUNT);//mCurHeroTotal
	mFightNum->setString(buffHeroNum);

}

void HeroWoodFightChooseUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void HeroWoodFightChooseUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool HeroWoodFightChooseUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	 

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();



	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = mCurHeroTotal / pageNum + (((mCurHeroTotal % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(mCurHeroTotal-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	menu->setPosition( CCPointZero );
	pPage->addChild(menu);

	int lineIndex = 0;
	int columnIndex = 0;

	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		const ObjectHero* pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)
		{
			continue;
		}
		

		CCSprite *headBg = CCSprite::create( pHero->getHeroColor().c_str());

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHero->GetHeadIcon().c_str(), pHero->GetHeadIcon().c_str(), this, menu_selector(HeroWoodFightChooseUIView::heroItemCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - headBg->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM+1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+headBg->getContentSize().width/2 + columnIndex * headBg->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos );

		headBg->setPosition(menuItem->getPosition());
		pPage->addChild(headBg);

		CCSprite *heroIcon = CCSprite::create("n_pos_back_.png");
		heroIcon->setPosition(menuItem->getPosition());
		heroIcon->setZOrder(0);
		pPage->addChild(heroIcon);

		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setScaleY(1.18f);
		checkItem->setPosition( itemPos );		
		checkItem->setUserData( (void *)(pHero) );

		checkItem->setVisible(DataPool::GetSingleton()->GetWoodData()->GetSelfWoodData()->HeroIsDefWood(pHero)==XTRUE);
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
	//加入伐木场英雄
#if  (WOOD_HERO_SHOW_IN_CHOOSE == 1 )
	 
	const ObjectHero* pHero = DataPool::GetSingleton()->GetWoodData()->GetSelfWoodData()->GetSelfDefHero();
	if (pHero != NULL &&nPage == totalPage - 1)
	{
		CCSprite *headBg = CCSprite::create( pHero->getHeroColor().c_str());

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHero->GetHeadIcon().c_str(), pHero->GetHeadIcon().c_str(), this, menu_selector(HeroWoodFightChooseUIView::heroItemCallBack) );  
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - headBg->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM+1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+headBg->getContentSize().width/2 + columnIndex * headBg->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 

		headBg->setPosition(menuItem->getPosition());
		pPage->addChild(headBg);

		CCSprite *checkItem = CCSprite::create( "check.png" );
		checkItem->setPosition( itemPos );		
		checkItem->setUserData( (void *)(pHero) );

		checkItem->setVisible(DataPool::GetSingleton()->GetWoodData()->GetSelfWoodData()->HeroIsDefWood(pHero)==XTRUE);
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
	}
#endif
	//处理不可选择的英雄
	if (nPage == totalPage-1)
	{
		ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
		X_UINT size =  mHeroItemArray.size();
		for (X_UINT i = 0; i < size ; ++i)
		{
			CCNode*  menuItem = (CCNode*)((mHeroItemArray[i])->getUserData());
			const ObjectHero* pHero = (const ObjectHero*)(menuItem->getUserData());
			if (pSelf->HeroIsBattle(pHero) && !mHeroItemCheckArray[i]->isVisible())
			{
				mHeroItemArray[i]->setEnabled( false );
				mHeroItemArray[i]->setColor(ICON_COLOR_GRAY);
			}
		}
		if (mCheckedCount == MAX_MATRIX_CELL_COUNT)
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
	}
	return true;
}
void HeroWoodFightChooseUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void HeroWoodFightChooseUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
}
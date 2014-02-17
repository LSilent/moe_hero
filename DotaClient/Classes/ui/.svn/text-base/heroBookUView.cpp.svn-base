#include "./ui/heroBookUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./ui/heroBookUI.h"
#include "./game/SendPacket.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.148f)
#define CONTENT_POS_Y            (0.208f)

#define CONTENT_VIEW_SIZE_X      (0.71f)
#define CONTENT_VIEW_SIZE_Y      (0.45f)

#define CONTENT_VIEW_SPACE_SIZE1      (0.72f)
#define CONTENT_VIEW_SPACE_SIZE2      (0.040f)

#define ITEM_SPACE_DELTA_X       (0.176f)
#define ITEM_SPACE_DELTA_Y       (0.140f)//0.14

#define ITEM_START_X             (0.09f)
#define ITEM_START_Y             (0.380f)//0.37

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            3

HeroBookUIView::HeroBookUIView()
: mMainStatus(NULL)
{
	 mContent = NULL;
	 mPageCtrl = NULL;
}

HeroBookUIView::~HeroBookUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
}


void HeroBookUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler HeroBookUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruitHero", HeroBookUIView::onButtonRecruitHero);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStore", HeroBookUIView::onButtonStore);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHeroBook", HeroBookUIView::onButtonHeroBook);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCharge", HeroBookUIView::onButtonCharge);

    return NULL;    
}

SEL_CCControlHandler HeroBookUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	
	return NULL;
}

void HeroBookUIView::onButtonRecruitHero(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroBookUIView::onButtonStore(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SECRETSTORE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroBookUIView::onButtonHeroBook(cocos2d::CCObject * pSender)
{
	// ignore

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroBookUIView::onButtonCharge(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool HeroBookUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool HeroBookUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
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
bool HeroBookUIView::init()
{
    bool bRet = true;

   

    return bRet;
}



void HeroBookUIView::onDataUpdate( bool isDataValid )
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

	if (mPageCtrl)
	{
		mPageCtrl->removeFromParentAndCleanup(true);
		mPageCtrl = NULL;
	}

	const vector<const ObjectHero*>  heroItems = DataPool::GetSingleton()->getObjectManager()->getGameHeroes();
	int size = heroItems.size();

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);

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
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * -0.015));
	addChild(mPageCtrl);

	HeroBookUI* pUi = static_cast<HeroBookUI*>(getUserData());
	if (!pUi)
	{
		return;
	}
	mContent->directToPage(pUi->nPage);
	mPageCtrl->setPageNum(pUi->nPage);
}

void HeroBookUIView::heroInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
// 	if( mContent->mIsMoved )
// 		return;

	const ObjectHero* pHero = static_cast<const ObjectHero*> (((CCNode *)pSender)->getUserData());
	DataPool::GetSingleton()->SetSelectHero( pHero);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

}

void HeroBookUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void HeroBookUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool HeroBookUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	 

	const vector<const ObjectHero*>  pHeros = DataPool::GetSingleton()->getObjectManager()->getGameHeroes();
	int size = pHeros.size();

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();
	menu->setPosition(CCPointZero);
	pPage->addChild(menu);

	int lineIndex = 0;
	int columnIndex = 0;
	
	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		if (!pHeros[i])
		{
			continue;
		}
		
	//	CCMenuItemImage *menuItem = CCMenuItemImage::create( "n_pos_back_.png", "n_pos_back_.png", this, menu_selector(HeroBookUIView::heroInfoCallBack) );  
		CCMenuItemImage *menuItem = CCMenuItemImage::create( pHeros[i]->GetHeadIcon().c_str(), pHeros[i]->GetHeadIcon().c_str(), this, menu_selector(HeroBookUIView::heroInfoCallBack) );  

		CCPoint itemPos = CCPointMake(winSize.width *(ITEM_START_X + columnIndex * ITEM_SPACE_DELTA_X) ,
				winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		
		menuItem->setPosition( itemPos ); 
		menuItem->setScale(0.78f);
		menuItem->setUserData( (void *)(pHeros[i]) );
		menu->addChild( menuItem );

		CCSprite *headIconBg = CCSprite::create("n_pos_back_.png");
		headIconBg -> setPosition(menuItem->getPosition());
		headIconBg->setScale(0.78f);
		pPage->addChild(headIconBg);
		menu->setZOrder(headIconBg->getZOrder() + 1);

		CCSprite *headBg = CCSprite::create(pHeros[i]->getHeroColor().c_str());
		headBg->setPosition(menuItem->getPosition());
		headBg->setScale(0.78f);
		pPage->addChild(headBg,menu->getVertexZ()+2);

		if (!DataPool::GetSingleton()->getObjectManager()->HasGotHero(pHeros[i]))
		{
			menuItem->setColor(ICON_COLOR_GRAY);
			headBg->setColor(ICON_COLOR_GRAY);
		}

		



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
	
	

	return true;
}
void HeroBookUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void HeroBookUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);

	HeroBookUI* pUi = static_cast<HeroBookUI*>(getUserData());
	if (!pUi)
	{
		return;
	}
	pUi->nPage = nPage;

}
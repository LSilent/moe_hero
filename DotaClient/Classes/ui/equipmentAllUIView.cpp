#include "./ui/EquipmentAllUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h" 
#include "./object/Item.h"
#include "./object/ItemEquip.h"
#include "./base/UtilTools.h"
#include "./game/GameHelper.h"
#include "./ui/equipmentAllUI.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.150f)
#define CONTENT_POS_Y            (0.270f)

#define CONTENT_VIEW_SIZE_X      (0.70f)
#define CONTENT_VIEW_SIZE_Y      (0.55f)

#define ITEM_SPACE_DELTA_X       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.100f)//(0.130f)

#define ITEM_START_X			 (0.087f) //(0.111f)
#define ITEM_START_Y             (0.46f)//(0.45f)

#define ITEM_COLUMN_NUM          5
#define ITEM_LINE_NUM            5

EquipmentAllUIView::EquipmentAllUIView()
{
	mContent = NULL;
	mPageCtrl = NULL;
	itemlist.clear();
}

EquipmentAllUIView::~EquipmentAllUIView()
{
	itemlist.clear();
}

void EquipmentAllUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler EquipmentAllUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip0", EquipmentAllUIView::onButtonEquip0);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip1", EquipmentAllUIView::onButtonEquip1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquip2", EquipmentAllUIView::onButtonEquip2);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonEquipSell", EquipmentAllUIView::onButtonEquipSell);



    return NULL;    
}

SEL_CCControlHandler EquipmentAllUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void EquipmentAllUIView::onButtonEquip0(cocos2d::CCObject * pSender)
{
 
	 __onChangeSubClass(EM_NORMAL);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


void EquipmentAllUIView::onButtonEquip1(cocos2d::CCObject * pSender)
{
	 
	 __onChangeSubClass(EM_MATERIAL);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void EquipmentAllUIView::onButtonEquip2(cocos2d::CCObject * pSender)
{
	 __onChangeSubClass(EM_FINALE);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
X_VOID EquipmentAllUIView::__onChangeSubClass(X_INT nPage)
{
	EquipmentAllUI* pUi = static_cast<EquipmentAllUI*>(getUserData());
	if (!pUi)
	{
		return;
	}
	if (pUi->nTablePage  == nPage)
	{
		return;
	}
	pUi->nTablePage = nPage;
	pUi->nPage = 0;
	onDataUpdate(true);
}
void EquipmentAllUIView::onButtonEquipSell(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENT_SELL_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool EquipmentAllUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	return false;
}

bool EquipmentAllUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

// on "init" you need to initialize your instance
bool EquipmentAllUIView::init()
{
    bool bRet = true;

    return bRet;
}

void EquipmentAllUIView::onDataUpdate( bool isDataValid )
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

	if (mPageCtrl)
	{
		mPageCtrl->removeFromParentAndCleanup(true);
		mPageCtrl = NULL;
	}

	EquipmentAllUI* pUi = static_cast<EquipmentAllUI*>(getUserData());
	if (!pUi)
	{
		return;
	}
	

	itemlist.clear();
	itemlist = DataPool::GetSingleton()->getObjectManager()->getGameEquipsWithType(pUi->nTablePage);
 
	int size = itemlist.size();

	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y);
	mContent = CCScrollViewPage::create();
	mContent->createContainer(this,totalPage,viewSize); 
 
	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentOffset( CCPointZero ); 
 
	mContent->setDirection( kCCScrollViewDirectionHorizontal );
	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	addChild( mContent );

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y - winSize.height * CONTENT_VIEW_SIZE_Y/2.0f - 55.0f));
	mContent->directToPage(pUi->nPage);
	mPageCtrl->setPageNum(pUi->nPage);
	addChild(mPageCtrl);
}

void EquipmentAllUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
// 	if( mContent->mIsMoved )
// 		return;
	
	const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	DataPool::GetSingleton()->SetSelectItem(pItem);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

}

void EquipmentAllUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void EquipmentAllUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool EquipmentAllUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
	 
	int size = itemlist.size();
  
	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	int lineIndex = 0;
	int columnIndex = 0;

	ItemEquip *pItem;

	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{

		pItem = (ItemEquip *) itemlist[i];
		if (!pItem)
		{
			continue;
		}

		CCMenuItemImage *menuItem = CCMenuItemImage::create("equipmentBK.png" , "equipmentBK.png", this, menu_selector(EquipmentAllUIView::itemInfoCallBack) );  
// 		CCPoint itemPos = CCPointMake( winSize.width * ( ITEM_START_X + pageIndex * ITEM_SPACE_DELTA_X * ITEM_COLUMN_NUM + ITEM_SPACE_DELTA_X * columnIndex), winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ) );
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 
		menuItem->setUserData( (void *)(pItem));

		menu->addChild( menuItem );

		CCSprite *equipBG = CCSprite::create(pItem->GetIcon());
		equipBG->setPosition(menuItem->getPosition());
		equipBG->setScale(0.850f);
		pPage->addChild(equipBG);
 
		CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemPos ); 
			pPage->addChild(pLevel);
			pLevel->setScale(equipBG->getScale());
			pLevel->setZOrder(100);
		}

		if (pItem->isVirtual())
		{
			menuItem->setColor(ICON_COLOR_GRAY);
			equipBG->setColor(ICON_COLOR_GRAY);
		}
		else
		{
			char buffNum[MAX_STRING_BUFF_SIZE];
			sprintf(buffNum,"%d",pItem->GetCounterNum());
			//CCLabelTTF *labelNum = CCLabelTTF::create(buffNum,FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
			CCLabelBMFont *labelNum = CCLabelBMFont::create(buffNum, FNT_NAME_SUMMONERLEVEL);
			labelNum->setPosition(ccp(menuItem->getPosition().x + menuItem->getContentSize().width * 0.415f, menuItem->getPosition().y - menuItem ->getContentSize().height * 0.415f));
			pPage->addChild(labelNum,101);
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

	menu->setPosition( CCPointZero );
	pPage->addChild(menu);


	return true;
}
void EquipmentAllUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void EquipmentAllUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
	EquipmentAllUI* pUi = static_cast<EquipmentAllUI*>(getUserData());
	if (!pUi)
	{
		return;
	}
	pUi->nPage = nPage;
}
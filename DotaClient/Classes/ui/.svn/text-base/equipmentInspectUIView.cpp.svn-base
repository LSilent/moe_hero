#include "./ui/equipmentInspectUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/EquipOperator.h"
#include "./game/GameHelper.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.160f)
#define CONTENT_POS_Y            (0.150f)

#define CONTENT_VIEW_SIZE_X      (0.685f)
#define CONTENT_VIEW_SIZE_Y      (0.20f)

#define ITEM_SPACE_DELTA_X       (0.200f)
#define ITEM_SPACE_DELTA_Y       (0.140f)

#define ITEM_START_X             (0.107f)
#define ITEM_START_Y             (0.095f)//(0.10f)

#define ITEM_COLUMN_NUM          5
#define ITEM_LINE_NUM            1


EquipmentInspectUIView::EquipmentInspectUIView()
: mEquipmentName(NULL)
, mEquipmentDesc(NULL)
// , mEquipmentParam(NULL)
, mEquipmentPos(NULL)
, mPartPos1(NULL)
, mPartPos2(NULL)
, mPartPos3(NULL)
, mPartPos4(NULL)
, mPartPos5(NULL)
/*
, mEquipAtta(NULL)
, mEquipDef(NULL)
, mEquipMP(NULL)
, mEquipAgi(NULL)
, mEquipInt(NULL)
, mEquipHP(NULL)
, mEquipStr(NULL)
, mEquipGuard(NULL)
, mEquipVal(NULL)
*/
{


	mContentNode = NULL;
	mPageCtrl = NULL;
	mGetEquipNode = NULL;

	for(int i = 0; i<MAX_EQUIP_TEXT_SIZE; i++)
	{
		mEquipAttr[i] = NULL;
	}
}

EquipmentInspectUIView::~EquipmentInspectUIView()
{
	CC_SAFE_RELEASE(mEquipmentName);
	CC_SAFE_RELEASE(mEquipmentDesc);
// 	CC_SAFE_RELEASE(mEquipmentParam);
	CC_SAFE_RELEASE(mEquipmentPos);
	CC_SAFE_RELEASE(mPartPos1);
	CC_SAFE_RELEASE(mPartPos2);
	CC_SAFE_RELEASE(mPartPos3);
	CC_SAFE_RELEASE(mPartPos4);
	CC_SAFE_RELEASE(mPartPos5);

	CC_SAFE_RELEASE(mGetEquipNode);

	for(int i = 0; i<MAX_EQUIP_TEXT_SIZE; i++)
	{
		CC_SAFE_RELEASE(mEquipAttr[i]);
	}

	/*
	CC_SAFE_RELEASE(mEquipAtta);
	CC_SAFE_RELEASE(mEquipDef);
	CC_SAFE_RELEASE(mEquipMP);

	CC_SAFE_RELEASE(mEquipAgi);
	CC_SAFE_RELEASE(mEquipInt);
	CC_SAFE_RELEASE(mEquipHP);

	CC_SAFE_RELEASE(mEquipStr);
	CC_SAFE_RELEASE(mEquipGuard);
	CC_SAFE_RELEASE(mEquipVal);
	*/
}


void EquipmentInspectUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler EquipmentInspectUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", EquipmentInspectUIView::onButtonClose);
	return NULL;    
}

SEL_CCControlHandler EquipmentInspectUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonCompose", EquipmentInspectUIView::onButtonCompose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonGetEquip", EquipmentInspectUIView::onButtonGetEquip);

	
	return NULL;
}

void EquipmentInspectUIView::onButtonCompose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{

	ItemEquip *pEquip = (ItemEquip *)(DataPool::GetSingleton()->GetSelectItem());

	if (pEquip)
	{
		const stDBC_FILE_EQUIP_MANUFACTURE	* pData = EquipMaker::getProductTableData(pEquip->GetTableID());
		if (!pData)return;
		 if (pData->type == 0)
		 {
			 SendLogicPacket::EquipMaker(DataPool::GetSingleton()->GetSelectItem());
		 }else
		 {
			 ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(670),this,DIALOG_MODEL_SINGLE);
			 addChild(dialog);
		 }
	}
	 SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND2);
}

void EquipmentInspectUIView::GetEquip(int type,int id,   EquipmentInspectUIView  *pSender)
{
	if (pSender == X_NULL)return;
	 
	switch (type)
	{
	case DROP_TYPE_INVALID:
		break;
	case DROP_TYPE_ALTAR:
		{
			//id Ϊ 0-4
			if (id < 0|| id >4)
			{
				return;
			}
			ObjectSelf *pself = DataPool::GetSingleton()->getObjectManager()->getSelf();
			PlayerData *pData = pself->playerData();
			pData->SetSacrificeID(id);
			vector<string> str;str.clear();
			str.push_back(UtilTools::IntToString(EM_ALTAR));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_SHOW,str);
		}
		break;
	case DROP_TYPE_COPYSCNE:
		{
			CopySceneGroup *pGroup;
			CopySceneManager *pm= 	DataPool::GetSingleton()->getCopySceneManager();

			CopyScene* ps =  pm->findCopySceneByID(id,pGroup);
			if (ps&&pGroup)
			{


				if (pGroup->isEnable() )
				{
					EM_COPYSCENE_STATUS state = ps->getStatus();
					if ( state!=EM_COPYSCENE_STATUS_CLOSE)
					{
						pm->setCurSceneGroup(pGroup);
						pm->setCurScene(ps);
						EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_SHOW);
					}else
					{
						if ( pGroup->isAsked())
						{
							ModalDialogView *dailog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(579),pSender,DIALOG_MODEL_SINGLE);
							pSender->addChild(dailog,10);
						}else
						{
							// SendLogicPacket::askSceneList(pGroup->getGroupID());
						}
					}

				}else
				{
					ModalDialogView *dailog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(579),pSender,DIALOG_MODEL_SINGLE);
					pSender->addChild(dailog,10);
				}
			}
		}
		break;
	default:
		break;
	}
}

void EquipmentInspectUIView::onButtonGetEquip(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	//SendLogicPacket::EquipMaker(DataPool::GetSingleton()->GetSelectItem());
	//TODO: get equip

	const Item* pitem = DataPool::GetSingleton()->GetSelectItem();
	if (pitem->GetClass() != EM_ITEM_CLASS_EQUIP )return;
	const ItemEquip* pEquip = static_cast<const ItemEquip*>(pitem);

	DROP_TYPE  type;X_INT id;
	pEquip->getDropInfo(type,id);
	GetEquip(type, id, this);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
 

void EquipmentInspectUIView::onButtonClose( cocos2d::CCObject* pSender )
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool EquipmentInspectUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentName", CCLabelTTF *, this->mEquipmentName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentDesc", CCLabelTTF *, this->mEquipmentDesc);
// 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentParam", CCLabelTTF *, this->mEquipmentParam);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipmentPos", CCSprite *, this->mEquipmentPos);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPartPos1", CCSprite *, this->mPartPos1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPartPos2", CCSprite *, this->mPartPos2);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPartPos3", CCSprite *, this->mPartPos3);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPartPos4", CCSprite *, this->mPartPos4);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPartPos5", CCSprite *, this->mPartPos5);

	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipAtta", CCLabelTTF *, this->mEquipAttr[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipDef", CCLabelTTF *, this->mEquipAttr[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipMP", CCLabelTTF *, this->mEquipAttr[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipAgi", CCLabelTTF *, this->mEquipAttr[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipInt", CCLabelTTF *, this->mEquipAttr[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipHP", CCLabelTTF *, this->mEquipAttr[5]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipStr", CCLabelTTF *, this->mEquipAttr[6]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipGuard", CCLabelTTF *, this->mEquipAttr[7]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEquipVal", CCLabelTTF *, this->mEquipAttr[8]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGetEquipNode", CCNode *, this->mGetEquipNode);
	

	return false;
}

bool EquipmentInspectUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
    return bRet;
}

// on "init" you need to initialize your instance
bool EquipmentInspectUIView::init()
{
    bool bRet = true;

    return bRet;
}



void EquipmentInspectUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}

	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	if (mPageCtrl)
	{
		mPageCtrl->removeFromParentAndCleanup(true);
		mPageCtrl = NULL;
	}
	

	mContentNode = CCNode::create();
	addChild( mContentNode );

	//char buff[MAX_STRING_BUFF_SIZE];
	const ItemEquip * pItem = 	(const ItemEquip *) DataPool::GetSingleton()->GetSelectItem();
	if (!pItem)return;

 
	DROP_TYPE  type;X_INT id;
	pItem->getDropInfo(type,id);
	if (id == -1)
	{
		mGetEquipNode->setVisible(false);
	}
	else
	{
		if (DROP_TYPE_COPYSCNE == type)
		{
			CopySceneGroup *pGroup;
			CopySceneManager *pm = 	DataPool::GetSingleton()->getCopySceneManager();
			if (pm)
			{
				CopyScene* ps =  pm->findCopySceneByID(id,pGroup);
				if (pGroup)
					SendLogicPacket::askSceneList(pGroup->getGroupID()); 
			}
		}
		mGetEquipNode->setVisible(true);
	}
	
	vector<stMaterialItem> materials;X_INT wood;
	EquipMaker::getMaterial(pItem,materials,wood);
	X_UINT materialsSize = 	materials.size();

	if (mEquipmentPos)
	{
		mEquipmentPos->removeAllChildrenWithCleanup(true);
	}
	
	CCSprite *itemSprite = CCSprite::create( pItem->GetIcon() );
	itemSprite->setPosition( ccp(mEquipmentPos->getContentSize().width/2.0f, mEquipmentPos->getContentSize().height/2.0f) );
	itemSprite->setScale(0.75f);
	mEquipmentPos->addChild( itemSprite );
 
	CCSprite *pLevel = GameHelper::getSpriteLevel(pItem);
	if (pLevel)
	{
		pLevel->setPosition( itemSprite->getPosition() ); 
		mEquipmentPos->addChild(pLevel);
		pLevel->setZOrder(100);
		pLevel->setScale(itemSprite->getScale());
	} 



	mEquipmentName->setString(pItem->GetName());
	mEquipmentName->setColor(CCCOLOR_YELLOW);
    CCSize winSIze = CCDirector::sharedDirector()->getWinSize();
    mEquipmentName->setDimensions(CCSizeMake(winSIze.width * 0.24f, 0.0f));
	mEquipmentDesc->setString(pItem->GetInfo());
	mEquipmentDesc->setColor(CCCOLOR_RED);

	CCMenuEx *menuM = CCMenuEx::create();

	vector<string> attr = pItem->getAddAttr();
	unsigned int equipSize = attr.size();
	for (unsigned int j = 0 ; j < 9 ; j++)
	{
		if(j < equipSize)
		{
			mEquipAttr[j]->setString(attr[j].c_str());
            mEquipAttr[j]->setColor(CCCOLOR_RED);
		}
		else
		{
			mEquipAttr[j]->setString(" ");
		}
	}

	//--------------------------------

	std::vector< CCSprite* > materialPosArray;
	materialPosArray.push_back( mPartPos1 );
	materialPosArray.push_back( mPartPos2 );
	materialPosArray.push_back( mPartPos3 );
	materialPosArray.push_back( mPartPos4 );
	materialPosArray.push_back( mPartPos5 );

	for( unsigned int i = 0; i < materialsSize; i++ )
	{
		CCMenuItemImage *itemImage = CCMenuItemImage::create( materials[i].m_pItem->GetIcon(),materials[i].m_pItem->GetIcon(),this, menu_selector(EquipmentInspectUIView::eQuipInfoCallBack) );
		itemImage->setPosition( materialPosArray[i]->getPosition() );
		itemImage->setUserData(materials[i].m_pItem);
		itemImage->setScale( 0.75f );
		
		CCSprite *pLevel = GameHelper::getSpriteLevel(materials[i].m_pItem);
		if (pLevel)
		{
			pLevel->setPosition( itemImage->getPosition() ); 
			mContentNode->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(itemImage->getScale());
		} 
 
		if( !materials[i].bEnough )
		{
			itemImage->setColor(ICON_COLOR_GRAY);
 			//materialPosArray[i]->setColor(ICON_COLOR_GRAY);
		}
		menuM->addChild( itemImage );
	}

	menuM->setPosition(CCPointZero);
	mContentNode->addChild(menuM);

// 	const vector<const ObjectHero*>  pHeros = DataPool::GetSingleton()->getObjectManager()->getSelf()->getHeroWithEquip(pItem->GetTableID());
	
	materialsEq.clear();
	EquipMaker::getProduct(pItem,materialsEq);
	int size = materialsEq.size();

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

	mContentNode->addChild( mContent );

	mPageCtrl = CCPageControll::create(string("n_page_selected.png"),string("n_page_unselect.png"),totalPage,viewSize);
	mPageCtrl->setAnchorPoint(ccp(0.5,0));
	mPageCtrl->setPosition(ccp(winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y - winSize.height * CONTENT_VIEW_SIZE_Y/2.0f + 18.0f));
	addChild(mPageCtrl);

}

void EquipmentInspectUIView::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{

}
void EquipmentInspectUIView::scrollViewDidZoom( cocos2d::extension::CCScrollView* view )
{

}
bool EquipmentInspectUIView::scrollViewInitPage( cocos2d::CCNode* pPage,int nPage )
{
 
// 	const ItemEquip * pItem = 	(const ItemEquip *) DataPool::GetSingleton()->GetSelectItem();
// 	const vector<const ObjectHero*>  pHeros = DataPool::GetSingleton()->getObjectManager()->getSelf()->getHeroWithEquip(pItem->GetTableID());
// 	int size = pHeros.size();

// 	const ItemEquip * pItem = 	(const ItemEquip *) DataPool::GetSingleton()->GetSelectItem();
// 	vector<Item *> materials;
// 	EquipMaker::getProduct(pItem,materials);
	int size = materialsEq.size();


	int pageNum = ITEM_COLUMN_NUM * ITEM_LINE_NUM;
	int totalPage = size / pageNum + (((size % pageNum) == 0) ? 0 : 1);
	int curNum = nPage<(totalPage-1) ? pageNum : abs(size-nPage*pageNum);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCMenuPEx *menu = CCMenuPEx::create();

	int lineIndex = 0;
	int columnIndex = 0;

	Item *pEItem;
	for( int i = nPage * pageNum; i < nPage * pageNum + curNum; i++ )
	{
		pEItem = materialsEq[i];
		if (!pEItem)
		{
			continue;
		}

		CCMenuItemImage *menuItem = CCMenuItemImage::create(pEItem->GetIcon(),pEItem->GetIcon(), this, menu_selector(EquipmentInspectUIView::eQuipInfoCallBack) );  
		// 		CCPoint itemPos = CCPointMake( winSize.width * ( ITEM_START_X + pageIndex * ITEM_SPACE_DELTA_X * ITEM_COLUMN_NUM + ITEM_SPACE_DELTA_X * columnIndex), winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ) );
		float space =  (winSize.width * CONTENT_VIEW_SIZE_X - menuItem->getContentSize().width * ITEM_COLUMN_NUM)/(ITEM_COLUMN_NUM + 1);
		CCPoint itemPos = CCPointMake(space * (columnIndex+1)+menuItem->getContentSize().width/2 + columnIndex * menuItem->getContentSize().width ,winSize.height * ( ITEM_START_Y - lineIndex * ITEM_SPACE_DELTA_Y ));
		menuItem->setPosition( itemPos ); 
		menuItem->setScale(0.75f);
		menuItem->setUserData( (void *)(pEItem));
 
		menu->addChild( menuItem );

		CCSprite *pLevel = GameHelper::getSpriteLevel(pEItem);
		if (pLevel)
		{
			pLevel->setPosition( itemPos ); 
			pPage->addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(menuItem->getScale());
		} 

		CCSprite *heroQuaBg = CCSprite::create("equipmentBK.png");
		heroQuaBg->setPosition(ccp(menuItem->getContentSize().width/2.0f, menuItem->getContentSize().height/2.0f));
		heroQuaBg->setScale(1.15f);
		menuItem->addChild(heroQuaBg);

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

void EquipmentInspectUIView::heroInfoCallBack( cocos2d::CCObject* pSender )
{
	//
}

void EquipmentInspectUIView::eQuipInfoCallBack( cocos2d::CCObject* pSender )
{
	const Item * pItem = static_cast<const Item*> (((CCNode *)pSender)->getUserData());
	DataPool::GetSingleton()->SetSelectItem(pItem);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_UPDATA);

}


void EquipmentInspectUIView::scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )
{
	//ignore
}
void EquipmentInspectUIView::scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage )
{
	mPageCtrl->setPageNum(nPage);
}

 
void EquipmentInspectUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

}

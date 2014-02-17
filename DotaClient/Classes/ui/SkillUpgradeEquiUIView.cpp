#include "./ui/SkillUpgradeEquiUIView.h"
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
#include "./object/ItemCommon.h"

#include "./ui/SkillUpgradeEquiUI.h"
#include "./ui/equipmentInspectUIView.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.05f)
#define CONTENT_POS_Y            (0.23f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.63f)

#define ITEM_DOCK_X              (0.455f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.27f)
#define ITEM_IMAGE_OFFSET_Y      (0.00f)

#define ITEM_NAME_OFFSET_X       (-0.18f)
#define ITEM_NAME_OFFSET_Y       (0.030f)

#define ITEM_LOAD_OFFSET_X       (-0.17f)
#define ITEM_LOAD_OFFSET_Y       (-0.030f)

#define ITEM_ADD_OFFSET_X        (0.10f)
#define ITEM_ADD_OFFSET_Y        (0)

#define ITEM_POINT_OFFSET_X      (0.20f)
#define ITEM_POINT_OFFSET_Y      (0)

#define ITEM_SUB_OFFSET_X        (0.30f)
#define ITEM_SUB_OFFSET_Y        (0)

SkillUpgradeEquiUIView::SkillUpgradeEquiUIView()
{

	guideLayer = NULL;
	mContent = NULL;
}

SkillUpgradeEquiUIView::~SkillUpgradeEquiUIView()
{
	
}


void SkillUpgradeEquiUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler SkillUpgradeEquiUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonOK", SkillUpgradeEquiUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCancel", SkillUpgradeEquiUIView::onButtonCancel);

	return NULL;    
}

SEL_CCControlHandler SkillUpgradeEquiUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	

	return NULL;
}

void SkillUpgradeEquiUIView::onButtonOK(cocos2d::CCObject * pSender)
{
// 	SendLogicPacket::DistribHeroBearpoint(mHeroArray,mLoadDistributeArray);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLUPGRADE_EQU_CLOSE);
	DataPool::GetSingleton()->SetSelectEqui(mSkillEquiItems);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_UPDATA);
	
	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SkillUpgradeEquiUIView::onButtonCancel(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLUPGRADE_EQU_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool SkillUpgradeEquiUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
// 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLoadPointLeft", CCLabelTTF *, this->mLoadPointLeft);

	return false;
}

bool SkillUpgradeEquiUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
	bool bRet = false;

	return bRet;
}

// on "init" you need to initialize your instance
bool SkillUpgradeEquiUIView::init()
{
	bool bRet = true;



	return bRet;
}



void SkillUpgradeEquiUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}
	X_INT tipId = ((SkillUpgradeEquiUI *)this->getUserData())->getTipId();
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
			if (tipId == 23)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(SkillUpgradeEquiUIView::onButtonOK),NULL);
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


	 //X_INT id =  100107;100610;101007;101807  
	SendLogicPacket::askSceneList(2); 
	SendLogicPacket::askSceneList(7); 
	SendLogicPacket::askSceneList(11); 
	SendLogicPacket::askSceneList(19); 
	

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	SelfBagData*  pBag =    DataPool::GetSingleton()->getBagData();
	X_UINT size = pBag->GetBagSize(EM_ITEM_CONTAINER_BAG);

	vector<ItemCommon*> itemlist;
	itemlist.clear();

	ItemCommon *pTItem;
	for (X_UINT i = 0 ; i< size ;i++)
	{
		pTItem =  (ItemCommon *)(pBag->getItem(i,EM_ITEM_CONTAINER_BAG));

		if (pTItem && pTItem->GetTableType() == ITEM_SKILL)
		{
			for (int i = 0; i < pTItem->GetCount();i++)
			{
				itemlist.push_back(pTItem);
			}
			
		}
	}


	// get window size
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	X_INT iNum = itemlist.size();

	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 

	CCMenuEx *menu = CCMenuEx::create(); 

	mSkillEquiItems.clear();
	mSkillEquiItems = DataPool::GetSingleton()->GetSelectEqui();


	mCheckItems.clear();

	vector<ItemCommon *> checkSelect(mSkillEquiItems);
 
	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height  * (iNum + 2.8) * ITEM_SPACE_DELTA_Y );
	ItemCommon *pItem;

	X_INT i = 0;
	for ( ;i< iNum;i++)
	{
		pItem = itemlist[i];
		if (!pItem)
		{
			continue;
		}
		

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCMenuItemImage *menuItem = CCMenuItemImage::create( pItem->GetIcon(),  pItem->GetIcon(), this, menu_selector(SkillUpgradeEquiUIView::itemInfoCallBack) );  
		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItem->setPosition( itemImagePos ); 
		menuItem->setUserData( (void *)i );
		menu->addChild( menuItem );

		CCSprite *headBg = CCSprite::create("equipmentBK.png");
		headBg->setPosition(menuItem->getPosition());
		headBg->setScale(1.15f);
		headBg->setZOrder( menu->getZOrder()+1 );
		layer->addChild(headBg);



		CCLabelTTF* mName = CCLabelTTF::create( pItem->GetName(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		mName->setColor(CCCOLOR_GREEN);
		layer->addChild( mName );

		CCLabelTTF* mType = CCLabelTTF::create( pItem->GetType(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		mType->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemTypePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_LOAD_OFFSET_Y ) );
		mType->setPosition( itemTypePos );
		mType->setColor(CCCOLOR_YELLOW);
		layer->addChild( mType );

		//n_choose_bg
		//n_choose_ok

		CCMenuItemImage *menuItemChoose = CCMenuItemImage::create( "n_choose_bg.png",  "n_choose_bg.png", this, menu_selector(SkillUpgradeEquiUIView::itemChooseCallBack) );  
		CCPoint itemImageChoosePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * 0.26, winSize.height * ITEM_IMAGE_OFFSET_Y ) );
		menuItemChoose->setPosition( itemImageChoosePos ); 
		menuItemChoose->setUserData( (void *)i );
		menu->addChild( menuItemChoose );

		CCSprite *skillOK = CCSprite::create("n_choose_ok.png");
		skillOK->setPosition(itemImageChoosePos);
		skillOK->setAnchorPoint(ccp(0.35,0.35));
		skillOK->setUserData(pItem);
		skillOK->setVisible(false);
		layer->addChild(skillOK,1);

		vector<ItemCommon *>::iterator iter;
		for (iter = checkSelect.begin();iter!= checkSelect.end();)
		{
			if ((*iter)->GetGuid() == pItem->GetGuid())
			{
				skillOK->setVisible(true);
				iter = checkSelect.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
			
		}

		mCheckItems.push_back(skillOK);

		X_INT tipId = ((SkillUpgradeEquiUI *)this->getUserData())->getTipId();

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
				if (tipId == 22 && i == 0)
				{
					guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(SkillUpgradeEquiUIView::itemChooseCallBack),menuItemChoose);
					guideLayer->setPosition(getPosition());
					addChild(guideLayer);
				}
			}
		}
		
		
	}

	CCPoint menuSkillPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( (-0.015) - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
	for (int k = 1;k <=4 ; k++)
	{
		char buffSkill[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffSkill,"n_skill_go_%d.png",k);
		CCMenuItemImage *menuSkill = CCMenuItemImage::create(buffSkill, buffSkill, this, menu_selector(SkillUpgradeEquiUIView::getSkillItemCallBack) );  
		menuSkillPos = ccpAdd(ccp(0,- winSize.height * 0.1),menuSkillPos);
			//CCPointMake( winSize.width * 0.45, winSize.height * (-0.085 - i * 0.162) + contentSize.height );
		menuSkill->setPosition( menuSkillPos ); 
		menuSkill->setUserData((void *)(k));
		menuSkill->setScale(0.82f); 
		menu->addChild( menuSkill );
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



	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
	
	
}


void SkillUpgradeEquiUIView::GetEquip(int type,int id,   SkillUpgradeEquiUIView  *pSender)
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


void SkillUpgradeEquiUIView::getSkillItemCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	//1-4
	int index = (int)(((CCNode *)pSender)->getUserData());

	if (index > 0 && index < 5)
	{

// 		1级奥义 12030000
// 			2级奥义 12031000
// 			3级奥义 12031001
// 			4级奥义 12031002
		//TODO

		int skillItems[4] = {12030000,12031000,12031001,12031002};

		DROP_TYPE  type;X_INT id;
		ItemCommon::getDropInfo(skillItems[index - 1],type,id);
		GetEquip(type, id,this);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SkillUpgradeEquiUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	int index = (int)(((CCNode *)pSender)->getUserData());

	//TODO
}

void SkillUpgradeEquiUIView::itemChooseCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved

	if( mContent->mIsMoved )
		return;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

// 	vector<Item *> mSkillEquiItems = DataPool::GetSingleton()->GetSelectEqui();

	if (mSkillEquiItems.size()<= 5)
	{
		int index = (int)((CCNode *)pSender)->getUserData();
		cocos2d::CCSprite * checkItem = mCheckItems[index];
		ItemCommon *pItem = (ItemCommon *)checkItem->getUserData();
		if (checkItem->isVisible())
		{
			checkItem->setVisible(false);
			vector<ItemCommon *>::iterator iter = mSkillEquiItems.begin();
			for (;iter!=mSkillEquiItems.end();iter++)
			{
				if ((*iter)->GetGuid() == pItem->GetGuid())
				{
					mSkillEquiItems.erase(iter);
					break;
				}
				
			}
			
		}
		else
		{
			if (mSkillEquiItems.size() !=5)
			{
				checkItem->setVisible(true);
				mSkillEquiItems.push_back(pItem);
			}
		}
	}
	

	guideLayer = NULL;

}


void SkillUpgradeEquiUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

}
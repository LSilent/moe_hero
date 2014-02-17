#include "./ui/taskInfoUIView.h"
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
#define CONTENT_POS_Y            (0.198f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.552f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_IMAGE_OFFSET_X      (-0.26f)//(-0.30f)
#define ITEM_IMAGE_OFFSET_Y      (0.0011f)

#define ITEM_UPGRADE_OFFSET_X    (0.30f)
#define ITEM_UPGRADE_OFFSET_Y    (0.032f)//(0.030f)

#define ITEM_EVOLVE_OFFSET_X     (0.25f)
#define ITEM_EVOLVE_OFFSET_Y     (-0.0005f)//(-0.005f)

#define ITEM_DESC_OFFSET_X       (-0.14f)
#define ITEM_DESC_OFFSET_Y       (0.01f)//(-0.000f)

#define ITEM_TEXT_SIZE_X         (0.40f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

taskInfoUIView::taskInfoUIView()
: mMainStatus(NULL)
{
	mContent = NULL;

	//guideMenuItem = NULL;

}

taskInfoUIView::~taskInfoUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
}


void taskInfoUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	
}

SEL_MenuHandler taskInfoUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler taskInfoUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

void taskInfoUIView::GetEquip(int type,int id,   taskInfoUIView  *pSender)
{
	if (pSender == X_NULL)return;

	switch (type)
	{
	case DROP_TYPE_INVALID:
		break;
	case DROP_TYPE_ALTAR:
		{
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

void taskInfoUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	Quest *pQue = (Quest *)((CCNode *)pSender)->getUserData();

	switch (pQue->getStatus())
	{
	case MISSION_STATUS_NOT_ACCEPT:
	case MISSION_STATUS_NOT_COMPLETE:		

		GetEquip(DROP_TYPE_COPYSCNE,pQue->getCopySceneId(), this);

		break;
	case MISSION_STATUS_NOT_SUBMIT:
		SendLogicPacket::SubmitQuest(pQue->getId());
		break;
	default:
		break;
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}



bool taskInfoUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool taskInfoUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

// on "init" you need to initialize your instance
bool taskInfoUIView::init()
{
    bool bRet = true;
	
    return bRet;
}

void taskInfoUIView::onDataUpdate( bool isDataValid )
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




	vector<Quest*> pTaskItems = DataPool::GetSingleton()->getQuestData()->getQuest();
	X_UINT size = pTaskItems.size();
	if(size == 0) return;


    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx *menu = CCMenuEx::create(); 

	

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );
	
	CCMenuItemImage *menuItemGet_tip = NULL;
	Quest *pQuest = NULL;
	X_UINT i = 0;
	for( ; i < size; i++ )
	{
		pQuest = pTaskItems.at(i);
		if (!pQuest)
		{
			continue;
		}
		
		//ask scene
		CopySceneGroup *pGroup;
		CopySceneManager *pm = 	DataPool::GetSingleton()->getCopySceneManager();
		if (pm)
		{
			CopyScene* ps =  pm->findCopySceneByID(pQuest->getCopySceneId(),pGroup);
			if (pGroup)
				SendLogicPacket::askSceneList(pGroup->getGroupID()); 
		}

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
        itemBackGround->setScaleX(SCALE_X);
        itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );

		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );


// 		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
// 		equipBG->setPosition(itemImagePos);
// 		layer->addChild(equipBG);

		CCSprite *acIconBG = CCSprite::create(pQuest->getIcon());
		acIconBG->setScale(0.75f);
		acIconBG->setPosition(itemImagePos);
		layer->addChild(acIconBG);

		CCSprite *acIconPos = CCSprite::create("n_pos_gray.png");
		acIconPos->setScale(0.75f);
		acIconPos->setPosition(itemImagePos);
		layer->addChild(acIconPos);
				
		CCPoint itemEvolvePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_EVOLVE_OFFSET_X, winSize.height * ITEM_EVOLVE_OFFSET_Y ) );
 		
		/*MISSION_STATUS_INVALID= -1,		//=-1 无效
			MISSION_STATUS_NOT_ACCEPT,		//=0  未接
			MISSION_STATUS_NOT_COMPLETE,	//=1  已接未完成
			MISSION_STATUS_NOT_SUBMIT,		//=2  完成未交
			MISSION_STATUS_FAIL,			//=3  失败
			MISSION_STATUS_DONE,			//=4  完成已交
			MISSION_STATUS_NUMBER,*/
		if (pQuest->getStatus() != MISSION_STATUS_INVALID)
		{
			if (pQuest->getStatus() != MISSION_STATUS_DONE)
			{
				CCMenuItemImage * menuItemGet = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(taskInfoUIView::itemInfoCallBack) );  
				menuItemGet->setPosition( itemEvolvePos ); 
				menuItemGet->setScale(0.75f); //0.65f
				menuItemGet->setUserData(pQuest);
				menu->addChild( menuItemGet );

				char *sFileName;
				switch (pQuest->getStatus())
				{
				case MISSION_STATUS_NOT_ACCEPT:
				case MISSION_STATUS_NOT_COMPLETE:
					sFileName = "n_task_go.png";
					break;
				case MISSION_STATUS_NOT_SUBMIT:
					sFileName = "n_task_get.png";
					break;
				default:
					break;
				}

				CCSprite *getText = CCSprite::create(sFileName );
				getText->setPosition( itemEvolvePos );
				layer->addChild( getText, 10 );

			}
			else if(MISSION_STATUS_DONE == pQuest->getStatus())
			{
				//n_task_get - n_task_go
				CCSprite *acRun = CCSprite::create("n_task_finish.png");
				acRun->setPosition(itemEvolvePos);
				layer->addChild(acRun);
			}
		}
		
		
		


		CCLabelTTF* mName = CCLabelTTF::create( pQuest->getDesc(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mName->setPosition( itemDescPos );
		mName->setColor(CCCOLOR_GREEN);
		layer->addChild( mName );

		string sNum = UtilTools::GET_TEXT_FROM_LANG(584);
		sNum += UtilTools::IntToString(pQuest->getDoneNum());
		sNum += "/";
		sNum += UtilTools::IntToString(pQuest->getNum());
		CCLabelTTF* mNum = CCLabelTTF::create(sNum.c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mNum->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemExpPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (-0.028f) ) );
		mNum->setPosition( itemExpPos );
		mNum->setColor(CCCOLOR_WHITE);
		layer->addChild( mNum );

		char buffDesc[MAX_STRING_BUFF_SIZE] = {0};
		if (pQuest->getAwardgold() != -1)
		{
			sprintf(buffDesc,"%s:%s%d",UtilTools::GET_TEXT_FROM_LANG(592),UtilTools::GET_TEXT_FROM_LANG(517),pQuest->getAwardgold());
		}
		else if(pQuest->getAwardAction() != -1)
		{
			sprintf(buffDesc,"%s:%s%d",UtilTools::GET_TEXT_FROM_LANG(592),UtilTools::GET_TEXT_FROM_LANG(591),pQuest->getAwardAction());
		}
		else
		{
			vector<int > eItems , eItemsNum;
			pQuest->GetDropItems(eItems,eItemsNum);

			int itemID = eItems.front();
			int itemCount = eItemsNum.front();

			string name,color,icon;X_INT level;
			if (!eItems.empty())
			{
				DataPool::GetSingleton()->getObjectManager()->getItemInfoById(itemID,name,color,icon,level);
			}
			sprintf(buffDesc,"%s:%s x%d",UtilTools::GET_TEXT_FROM_LANG(592),name.c_str(),itemCount);

		}


		CCLabelTTF* mDesc = CCLabelTTF::create(buffDesc, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 ,CCSizeMake( winSize.width * (0.6f), winSize.height * 0.1 ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemlvlPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (-0.076f) ) );
		mDesc->setPosition( itemlvlPos );
		mDesc->setColor(CCCOLOR_YELLOW);
		layer->addChild( mDesc );


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

}

void taskInfoUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

}
#include "./ui/MainPageUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/LogicTouchItem.h"
#include "cocos-ext.h"
#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./ui/mainPageUI.h"
#include "../Wood/CGWoodAskPacket.h"



using namespace cocos2d;
USING_NS_CC_EXT;

#define HERO_ITEM_0    ((void*)1)
#define HERO_ITEM_1    ((void*)2)
#define HERO_ITEM_2    ((void*)3)
#define HERO_ITEM_3    ((void*)4)
#define HERO_ITEM_4    ((void*)5)
#define HERO_ITEM_5    ((void*)6)

#define MAX_STRING_BUFF_SIZE    (128)

MainPageUIView::MainPageUIView()
: mMainStatus(NULL)
, mPosPanel(NULL)
,mAction(NULL)
,mTopAction(NULL)
, mIsDragMove(false)
, mMsgNotice(NULL)
{
	for( int i = 0; i < MAX_MATRIX_CELL_COUNT; i++ )
	{
	    m_heroItems[i] = 0;
		mHeroDock[i] = 0;


		mHeroObjArray[i] = 0;
		mHerosDockIndex[i] = -1;
	}

	guideLayer = NULL;
	mChatMsgTip = NULL;
	mMessage = NULL;
}

MainPageUIView::~MainPageUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
	CC_SAFE_RELEASE(mPosPanel);
	CC_SAFE_RELEASE(mAction);
	CC_SAFE_RELEASE(mTopAction);

	for( int i = 0; i < MAX_MATRIX_CELL_COUNT; i++ )
	{
	    CC_SAFE_RELEASE(mHeroDock[i]);
	}

	CC_SAFE_RELEASE(mMsgNotice);
	CC_SAFE_RELEASE(mMessage);
}


void MainPageUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   /* CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);*/

	// for NULL pos response
	for (int i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		cocos2d::LogicTouchItem* nullItem = cocos2d::LogicTouchItem::createWithFile( "n_pos_gray.png", this, callfuncO_selector(MainPageUIView::heroNullTouchBeginHook), 
																								      callfuncO_selector(MainPageUIView::heroNullTouchMoveHook),
																									  callfuncO_selector(MainPageUIView::heroNullTouchEndHook),
																									  false, 20 );

		nullItem->setPosition( mHeroDock[i]->getPosition() );
		nullItem->setUserData( ((void*)i) );
		mHeroDock[i]->getParent()->addChild( nullItem );
		
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	
	
	CCPoint targetPos = mAction->getPosition();
	CCPoint movePos = ccpAdd(targetPos, ccp(0, winSize.height * 0.05f));
	CCActionInterval *seq = (CCActionInterval *) (CCSequence::create(CCPlace::create( ccp( 0, winSize.height * 0.9f )),
										CCEaseIn::create(CCMoveTo::create(0.25f, movePos),1.0f) ,
										CCEaseElasticOut::create( CCMoveTo::create( 0.5f, targetPos ), 0.3f ),NULL ));
    mAction->runAction( seq );

	CCPoint targetTopPos = mTopAction->getPosition();
	CCActionInterval *seqTop = (CCActionInterval *) (CCSequence::create(CCPlace::create( ccp( targetTopPos.x, winSize.height * 0.9f + mAction->getContentSize().height * 0.5f)),
																		CCEaseIn::create(CCMoveTo::create(0.25f, targetTopPos),1.0f) ,NULL ));
	mTopAction->runAction(seqTop);

	
	//0.28 0.07
	onDataUpdate( false );


	updateChatMessageInfo();



}

SEL_MenuHandler MainPageUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
//     CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonChangeHero", MainPageUIView::onButtonChangeHero);


	
	return NULL;    
}

SEL_CCControlHandler MainPageUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton1", MainPageUIView::onButton1);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton2", MainPageUIView::onButton2);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton3", MainPageUIView::onButton3);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton4", MainPageUIView::onButton4);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton5", MainPageUIView::onButton5);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButton6", MainPageUIView::onButton6);

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonChangeHero", MainPageUIView::onButtonChangeHero);

	return NULL;
}

// void MainPageUIView::onButtonChangeHero(cocos2d::CCObject * pSender)
void MainPageUIView::onButtonChangeHero(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
}

void MainPageUIView::updateChatMessageInfo()
{
	Record red;
	X_INT	num = DataPool::GetSingleton()->GetChatData()->GetMsgNumber(All_Channel);
	if (num == 0) return;
	DataPool::GetSingleton()->GetChatData()->GetChatMsg(All_Channel, red,num-1);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	string strMsg = red.m_strName.c_str();
	strMsg += ":";
	strMsg += red.m_strContex.c_str();

	string buffTip = strMsg;

	X_INT sizeNum = (winSize.width)/18;
	X_INT msgSize = strMsg.size();
	if (msgSize >= sizeNum)
	{
		buffTip = strMsg.substr(0, msgSize -3 > 0 ? msgSize-3: msgSize);
		buffTip += "...";
	}

	CCLOG("%f-%d-%s",winSize.width/18,sizeNum,buffTip.c_str());

	if (mChatMsgTip == NULL)
	{
	 
		mChatMsgTip = CCLabelTTF::create();
		mChatMsgTip->setFontName(FONT_NAME_ARIAL_BOLD);
		mChatMsgTip->setFontSize(FONT_SIZE_24);
		mChatMsgTip->setColor(ccGREEN);
		mChatMsgTip->setDimensions(CCSizeMake(mMessage->getContentSize().width * 0.9f, mMessage->getContentSize().height));
		mChatMsgTip->setAnchorPoint(ccp(0,0.5));
		mChatMsgTip->setPosition(ccp(mMessage->getContentSize().width * 0.1f,mMessage->getContentSize().height*0.5f -5 ));
		//mChatMsgTip->setScaleX(SCALE_X);
	 
		mMessage->addChild(mChatMsgTip);
	}
	
	mChatMsgTip->setString(buffTip.c_str());
 
}

/*
void  MainPageUIView::autoRoll(float dt )
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int x = mChatMsgTip->getPositionX() - 5;
	int width =  mChatMsgTip->getContentSize().width;
	if (x + width >= 0)
	{
		mChatMsgTip->setPosition( CCPoint(x,mChatMsgTip->getPositionY()));
	}
	else
	{
		mChatMsgTip->setVisible(false);
		unschedule(SEL_SCHEDULE(&MainPageUIView::autoRoll));
	}

}*/


void MainPageUIView::onButton1(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TEAMLIST_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

void MainPageUIView::onButton2(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainPageUIView::onButton3(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHATMESSAGE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainPageUIView::onButton4(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	
}

void MainPageUIView::onButton5(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	/*SendLogicPacket::OpenMailBox();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MESSAGE_SHOW);*/
	SendLogicPacket::AskQuest();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TASKINFO_SHOW);
    
    DataPool::GetSingleton()->getQuestData()->setNewFlag(false);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
    
}

void MainPageUIView::onButton6(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SETTING_SHOW);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainPageUIView::heroItemTouchBeginHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch begin", (int)(((CCNode *)pSender)->getUserData()) );

	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() + 10 );

	mIsDragMove = false;
}

void MainPageUIView::heroItemTouchMoveHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch move", (int)(((CCNode *)pSender)->getUserData()) );

	mIsDragMove = true;
}

void MainPageUIView::heroItemTouchEndHook(CCObject* pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() - 10 );

	int heroIndex = (int)(((CCNode *)pSender)->getUserData());

	if( !mIsDragMove )
	{
		if( mHeroObjArray[heroIndex])
		{
			if ( mHeroObjArray[heroIndex]->GetGuid()!= DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetGoddessHeroGuid())
			{

				DataPool::GetSingleton()->SetSelectHero( mHeroObjArray[heroIndex] );
				EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_SHOW);
			}else
			{
				EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROFIGHTCHOOSE_SHOW);
			}
			
		}
	}
	else
	{
		int oriDockIndex = mHerosDockIndex[heroIndex];
		assert( oriDockIndex >= 0 );

		CCPoint dropPos = ((CCNode *)pSender)->getPosition();

		int i = 0;
		for( ; i < MAX_MATRIX_CELL_COUNT; i++ )
		{
			if( i !=  oriDockIndex &&
				mHeroDock[i]->boundingBox().containsPoint( ((CCNode *)pSender)->getPosition() ) )
			{
				int j = 0;
				for( ; j < MAX_MATRIX_CELL_COUNT; j++ )
				{
					if( mHerosDockIndex[j] == i )
						break;
				}

				if( j < MAX_MATRIX_CELL_COUNT )
				{
					// swap
					((CCNode *)pSender)->setPosition( mHeroDock[i]->getPosition() );
					mHerosDockIndex[heroIndex] = i;

					m_heroItems[j]->setPosition( mHeroDock[oriDockIndex]->getPosition() );
					mHerosDockIndex[j] = oriDockIndex;
				}
				else
				{
					// move to
					((CCNode *)pSender)->setPosition( mHeroDock[i]->getPosition() );
					mHerosDockIndex[heroIndex] = i;
				}

				// inform the pos info
				std::vector<ObjectHero*>  Heroes;
				Heroes.clear();
				Heroes.resize(MAX_MATRIX_CELL_COUNT, 0);
               
				for (X_INT i = 0;i<MAX_MATRIX_CELL_COUNT;i++)
				{
					if( mHerosDockIndex[i] >= 0 )
					{
						Heroes[mHerosDockIndex[i]] = mHeroObjArray[i];
					}
				}
				SendLogicPacket::SetMatrixHeros(Heroes);
				
				break;
			}		
		}

		// reset position
		if( i >= MAX_MATRIX_CELL_COUNT )
		{
			((CCNode *)pSender)->setPosition( mHeroDock[oriDockIndex]->getPosition() );
		}
	}

	guideLayer = NULL;

}

void MainPageUIView::heroNullTouchBeginHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch begin", (int)(((CCNode *)pSender)->getUserData()) );
}

void MainPageUIView::heroNullTouchMoveHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch move", (int)(((CCNode *)pSender)->getUserData()) );
}

	
void MainPageUIView::heroNullTouchEndHook(CCObject* pSender)
{
	//DataPool::GetSingleton()->SetSelectHero( mHeroObjArray[heroIndex] );
    
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROFIGHTCHOOSE_SHOW);

	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
}

bool MainPageUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPosPanel", CCNode *, this->mPosPanel);

	  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAction", CCLayer *, this->mAction);
	  CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTopAction", CCLayer *, this->mTopAction);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos1", CCSprite *, this->mHeroDock[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos2", CCSprite *, this->mHeroDock[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos3", CCSprite *, this->mHeroDock[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos4", CCSprite *, this->mHeroDock[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos5", CCSprite *, this->mHeroDock[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos6", CCSprite *, this->mHeroDock[5]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMsgNotice", CCSprite *, this->mMsgNotice);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMessage", CCSprite *, this->mMessage);
	
    return false;
}

bool MainPageUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
	return bRet;
}

// on "init" you need to initialize your instance
bool MainPageUIView::init()
{
    bool bRet = true;

   

    return bRet;
}

void MainPageUIView::onGuideCheeseActivity(CCObject* pSender)
{
	guideLayer = NULL;
	SendLogicPacket::AskHuoDong();
//	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void MainPageUIView::onGuideRankList(CCObject* pSender)
{
	guideLayer = NULL;
	SendLogicPacket::EnterArena();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RANKLIST_SHOW);
//	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainPageUIView::onGuideHeroBase(CCObject* pSender)
{
	guideLayer = NULL;
	SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_ENTER);
	//	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


void MainPageUIView::onDataUpdate( bool isDataValid )
{
	 

	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}


	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	const vector<ObjectHero*> pHeros = pSelf->playerData()->GetFightHero();
	ObjectHero *pHero = X_NULL;
	
	for (X_INT i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{


		if( m_heroItems[i] )
		{
			m_heroItems[i]->removeFromParentAndCleanup( true );
			m_heroItems[i] = NULL;
		}

		pHero = pHeros[i];

		if( !pHero || !pHero->IsDataReady())
		{
			mHeroObjArray[i] = 0;
		    mHerosDockIndex[i] = -1;
			continue;
		}

		mHeroObjArray[i] = pHero;

		mHerosDockIndex[i] = i;
 

		m_heroItems[i] = cocos2d::HeroHeadIcon::createWithFile( pHero->GetHeadIcon().c_str(), this, callfuncO_selector(MainPageUIView::heroItemTouchBeginHook), 
		 																								      callfuncO_selector(MainPageUIView::heroItemTouchMoveHook),
		 																									  callfuncO_selector(MainPageUIView::heroItemTouchEndHook),
																											  pHero->GetColor(),
		 																									  true,10,pHero->GetLevel() );
		m_heroItems[i]->setPosition( mHeroDock[mHerosDockIndex[i]]->getPosition() );
		m_heroItems[i]->setUserData( ((void*)i) );
		mHeroDock[mHerosDockIndex[i]]->getParent()->addChild( m_heroItems[i], mHeroDock[mHerosDockIndex[i]]->getZOrder() + 1 );		
  
	}
	 
	mMsgNotice->setVisible(DataPool::GetSingleton()->getQuestData()->getNewFlag());


	X_INT tipId = ((MainPageUI *)this->getUserData())->getTipId();

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
			case 1:
			case 4:
				guideLayer = guidelinesLayer::createLayer(tipId,this);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 7:
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(MainPageUIView::heroNullTouchEndHook),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 14:
			case 19:
			case 10:
				if (!pHeros.at(0)){break;}
				
				guideLayer = guidelinesLayer::createLayer(tipId,this,callfuncO_selector(MainPageUIView::heroItemTouchEndHook),m_heroItems[0]);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 26:
			case 29:
				guideLayer = guidelinesLayer::createLayer(tipId,this, callfuncO_selector(MainPageUIView::onGuideCheeseActivity),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 35:
				guideLayer = guidelinesLayer::createLayer(tipId,this, callfuncO_selector(MainPageUIView::onGuideRankList),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 36:
				guideLayer = guidelinesLayer::createLayer(tipId,this, callfuncO_selector(MainPageUIView::onGuideHeroBase),NULL);
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


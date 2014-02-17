#include "./ui/fightResultUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "./ui/element/CCMenuEx.h"

#include "./ui/fightResultUI.h"
#include "./datapool/WoodData.h"
#include "./datapool/QuJingData.h"
#include "./game/GameHelper.h"
#include "./datapool/BloodData.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define LOGO_POS_X              (0.5f)
#define LOGO_POS_Y              (0.745f)

#define STAR_POS_START_X        (0.35f)
#define STAR_POS_DELTA_X        (0.08f)
#define STAR_POS_Y              (0.57f)

FightResultUIView::FightResultUIView()
:  mAwardText(NULL)
, mProcessBarFrame(NULL)
{
	for( int i = 0; i < MAX_DROP_ITEM_NUM; i++ )
	{
		mItemPos[i] = NULL;
	}

	mContent = 0;

	mSuccessNode = NULL;
	mFailNode = NULL;
	mFailAwardText = NULL;
	mFightResultOkButton = NULL;
	guideLayer = NULL;
	;
}

FightResultUIView::~FightResultUIView()
{
	for( int i = 0; i < MAX_DROP_ITEM_NUM; i++ )
	{
		CC_SAFE_RELEASE(mItemPos[i]);
	}

	CC_SAFE_RELEASE(mAwardText);
	CC_SAFE_RELEASE(mProcessBarFrame);

	CC_SAFE_RELEASE(mSuccessNode);
	CC_SAFE_RELEASE(mFailNode);
	CC_SAFE_RELEASE(mFailAwardText);
	
	CC_SAFE_RELEASE(mFightResultOkButton);
}

void FightResultUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler FightResultUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
    return NULL;    
}

SEL_CCControlHandler FightResultUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonClose", FightResultUIView::onButtonClose);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonReplay", FightResultUIView::onButtonReplay);

	return NULL;
}
void FightResultUIView::onGuideBattleClose(cocos2d::CCObject * pSender)
{
	guideLayer = NULL;
	MainGame::GetSingleton()->EndBattle(DataPool::GetSingleton()->GetBattleData()->isWin());
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void FightResultUIView::onGuideRobBattleClose(cocos2d::CCObject * pSender)
{
	guideLayer = NULL;
	MainGame::GetSingleton()->EndBattle(DataPool::GetSingleton()->GetBattleData()->isWin());
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void FightResultUIView::onButtonClose(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
 
	MainGame::GetSingleton()->EndBattle(DataPool::GetSingleton()->GetBattleData()->isWin());
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
 
}

void FightResultUIView::onButtonReplay(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	pBattle->ResetRound();

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_FIGHTRESULT_CLOSE);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BATTLEFIELD_CLOSE);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BATTLEFIELD_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void FightResultUIView::visibleOkButton()
{

	mFightResultOkButton->setEnabled(true);
}

bool FightResultUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos1", CCSprite *, mItemPos[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos2", CCSprite *, mItemPos[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos3", CCSprite *, mItemPos[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos4", CCSprite *, mItemPos[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mItemPos5", CCSprite *, mItemPos[4]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBarFrame", CCSprite *, mProcessBarFrame);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAwardText", CCLabelTTF *, mAwardText);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSuccessNode", CCNode *, mSuccessNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFailNode", CCNode *, mFailNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFailAwardText", CCLabelTTF *, mFailAwardText);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFightResultOkButton", CCControlButton *, mFightResultOkButton);
	

    return false;
}

bool FightResultUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool FightResultUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

void FightResultUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		//clear();

		return;
	}

	if( mContent )
		mContent->removeFromParentAndCleanup( true );

	mContent = CCNode::create();
	addChild( mContent );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *logo;


	X_INT tipId = ((FightResultUI *)this->getUserData())->getTipId();

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;
	if (tipId != -1)
	{

		if (!guideLayer)
		{
			//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();
			switch (tipId)
			{
			case 3:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(FightResultUIView::onGuideBattleClose),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 39:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(FightResultUIView::onGuideRobBattleClose),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				guideLayer = guidelinesLayer::createLayer(tipId,this);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			}
		}


	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}


	if( DataPool::GetSingleton()->GetBattleData()->isWin() )
	{
	    logo = CCSprite::create( "n_bat_result_top.png" );
		mSuccessNode->setVisible(true);
		mFailNode->setVisible(false);

		for (int i=0;i<5;i++)
		{
			mItemPos[i]->setVisible(true);
		}
	}
	else
	{
	

		logo = CCSprite::create( "fightFail.png" );
		logo->setPosition( ccp(winSize.width * LOGO_POS_X, winSize.height * LOGO_POS_Y) );
		mContent->addChild( logo );
		mSuccessNode->setVisible(false);
		mFailNode->setVisible(true);
		mFailAwardText->setString("");

		for (int i=0;i<5;i++)
		{
			mItemPos[i]->setVisible(false);
		}

		if(DataPool::GetSingleton()->BattlyType == EM_SPORT) 
		{
			SportsData * pData =  DataPool::GetSingleton()->getSportsData();
			char buff[MAX_STRING_BUFF_SIZE] = {0};
			sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 531 ), pData->exp, pData->gold  );
			mFailAwardText->setString( buff );
			return;
		}
		else if(DataPool::GetSingleton()->BattlyType == EM_BATTLETYPE_BLOODBATTLE) 
		{

		}else if (DataPool::GetSingleton()->BattlyType == EM_WOODPVP)
		{
			WoodsData* pWoodData = DataPool::GetSingleton()->GetWoodData();

			X_INT wood = pWoodData->GetPriceWood();
			if (wood>0)
			{

				char buff[MAX_STRING_BUFF_SIZE] = "";
				sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 647 ),wood);
				mFailAwardText->setString(buff);
			}
		}
		return;
	}

	logo->setPosition( ccp(winSize.width * LOGO_POS_X, winSize.height * LOGO_POS_Y) );
	mContent->addChild( logo );
	 
 
	if(DataPool::GetSingleton()->BattlyType == EM_SPORT) 
	{
		SportsData * pData =  DataPool::GetSingleton()->getSportsData();
 
		char buff[MAX_STRING_BUFF_SIZE] = {0};
		sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 531 ), pData->exp, pData->gold  );
		mAwardText->setString( buff );

		return;
	}
	else if (DataPool::GetSingleton()->BattlyType == EM_WOODPVP)
	{
		WoodsData* pWoodData = DataPool::GetSingleton()->GetWoodData();
		char buff[MAX_STRING_BUFF_SIZE] = "";
		sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 647 ),pWoodData->GetPriceWood()  );
		mAwardText->setString(buff);
	}
	else if(DataPool::GetSingleton()->BattlyType == EM_BATTLETYPE_BLOODBATTLE)
	{
		BloodData* pBloodData = DataPool::GetSingleton()->GetBloodData();
		char buff[MAX_STRING_BUFF_SIZE] = {0};
		sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 680 ), pBloodData->GetStar(),pBloodData->GetExp());
		mAwardText->setString( buff );
		X_INT   id = pBloodData->GetItemID();
		if (id >0)
		{
			string itemName, itemIcon ,itemColor; 
			X_INT   level;
			X_BOOL bok = DataPool::GetSingleton()->getObjectManager()->getItemInfoById(id,itemName,itemColor,itemIcon,level);
			if (bok)
			{
				CCSprite *item = CCSprite::create( itemIcon.c_str() );
				item->setPosition(mItemPos[0]->getPosition());
				mSuccessNode->addChild( item );	
				item->setScale(0.8f); 

				CCSprite *itemBg = CCSprite::create("equipmentBK.png");
				itemBg->setPosition(item->getPosition());
				mSuccessNode->addChild(itemBg);

				CCSprite *pLevel = GameHelper::getSpriteLevel(level);
				if (pLevel)
				{
					pLevel->setPosition( item->getPosition() ); 
					mSuccessNode->addChild(pLevel);
					pLevel->setZOrder(100);
					pLevel->setScale(0.8f);
				}  
			}	
			
		}
		
	}
	else if(DataPool::GetSingleton()->BattlyType == EM_BATTLETYPE_QUJING)
	{
		QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
		if (!pData)
		{
			return;
		}
		
		char buff[MAX_STRING_BUFF_SIZE] = {0};
		sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 667 ),pData->GetTotalWood() ,pData->GetTotalExp() );
		mAwardText->setString(buff);
	}
	else
	{
		    const CopyScene*  curScene = DataPool::GetSingleton()->getCopySceneManager()->getAwardScene();

			if (!curScene)
			{
				return;
			}
			mFightResultOkButton->setEnabled(false);
			int starNum = curScene->getStar();
			for( int i = 0; i < 5; i++ )
			{
				CCSprite *star;
				CCArray *actionsArray = CCArray::create(CCFadeOut::create(0),CCFadeIn::create(0),CCScaleTo::create(0.0f, 5.0f),
					CCScaleTo::create(0.12f, 0.95f),
					CCScaleTo::create(0.08f, 1.03f),
					CCScaleTo::create(0.08f, 1.0f), NULL);
				actionsArray->insertObject(CCDelayTime::create(i * 0.2f),1);

				CCSprite *starBg = CCSprite::create( "star_null.png" );
				starBg->setPosition( ccp(winSize.width * (STAR_POS_START_X + i * STAR_POS_DELTA_X), winSize.height * STAR_POS_Y) );
				mContent->addChild( starBg );
				
				if (i < starNum)
				{
					star = CCSprite::create( "star.png" );

					if (i == starNum - 1)
					{
						actionsArray->addObject(CCCallFunc::create(this, callfunc_selector(FightResultUIView::visibleOkButton)));
					}
					

					CCAction* popupLayer = CCSequence::create( actionsArray);
					
					star->setPosition( ccp(winSize.width * (STAR_POS_START_X + i * STAR_POS_DELTA_X), winSize.height * STAR_POS_Y) );
					mContent->addChild( star );
					star->runAction(popupLayer);
				}
				else
				{
			//		star = CCSprite::create( "star_null.png" );
				}
				
				 
				

			}

			

			char buff[MAX_STRING_BUFF_SIZE] = {0};
			sprintf( buff, UtilTools::GET_TEXT_FROM_LANG( 531 ), curScene->GetAwardHumanExp(), curScene->GetAwardGold() );
			mAwardText->setString( buff );
 
			X_INT num = min( curScene->GetItemCount(), MAX_DROP_ITEM_NUM );
			string itemName, itemIcon ,itemColor; 
			X_INT itemNum,level;
			for (X_INT i = 0; i< num ; i ++)
			{
				curScene->GetAwardItem(i,itemName,itemIcon,itemColor,itemNum,level);

				CCSprite *item = CCSprite::create( itemIcon.c_str() );
				item->setPosition(mItemPos[i]->getPosition());
				item->setScale(0.8f);
				mSuccessNode->addChild( item );	


				CCSprite *itemBg = CCSprite::create("equipmentBK.png");
				itemBg->setPosition(item->getPosition());
				mSuccessNode->addChild(itemBg);
				

				CCSprite *pLevel = GameHelper::getSpriteLevel(level);
				if (pLevel)
				{

					pLevel->setPosition( item->getPosition() ); 
					mSuccessNode->addChild(pLevel);
					pLevel->setZOrder(100);
					pLevel->setScale(0.8f);
				} 
			}
	}
	 



}
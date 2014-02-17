#include "./ui/heroRecruitUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"

#include "./ui/heroRecruitUI.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define TAG_FRESH_HERO (100)
#define TAG_RECRUIT_HERO_1 (101)
#define TAG_RECRUIT_HERO_2 (102)
#define TAG_RECRUIT_HERO_3 (103)
#define TAG_NOT_GLOD (104)

HeroRecruitUIView::HeroRecruitUIView()
: mMainStatus(NULL)
, mFreshInfo(NULL)
, mRecruitTip(NULL)
, mNewFresh(NULL)
{
	for( int i = 0; i < MAX_HERO_RECRUIT_COUNT; i++ )
	{
		mPos[i] = NULL;
		mRecruitButton[i] = NULL;
		mRecruitText[i] = NULL;

		mHeroSpriteList[i] = NULL;
		mHeroList[i] = NULL;
	}

	for (int j = 0; j < 3 ; j++)
	{
		mRecruitTab[j] = NULL;
		mName[j] = NULL;
	}

	mRecruitFreshText = NULL;

	// set to invalid
	mFreshmilliSecond = -1;

	guideLayer = NULL;
	flagOfRecruiting = false;
	flagOfReEffect = true;
}

HeroRecruitUIView::~HeroRecruitUIView()
{
    CC_SAFE_RELEASE(mMainStatus);

	for( int i = 0; i < MAX_HERO_RECRUIT_COUNT; i++ )
	{
		CC_SAFE_RELEASE(mPos[i]);
		CC_SAFE_RELEASE(mRecruitButton[i]);
		CC_SAFE_RELEASE(mRecruitText[i]);
	}

	for (int j = 0; j < 3 ; j++)
	{
		CC_SAFE_RELEASE(mRecruitTab[j]);
		CC_SAFE_RELEASE(mName[j]);
	}
	
	CC_SAFE_RELEASE(mRecruitFreshText);
	CC_SAFE_RELEASE(mFreshInfo);

	CC_SAFE_RELEASE(mRecruitTip);
	CC_SAFE_RELEASE(mNewFresh);
}

void HeroRecruitUIView::onEnter()
{
	CCLayer::onEnter();

	schedule( schedule_selector(HeroRecruitUIView::updateFreshTime), 0.2f );
}

void HeroRecruitUIView::onExit()
{
	unschedule( schedule_selector(HeroRecruitUIView::updateFreshTime) );

	BaseView::onExit();
}


void HeroRecruitUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler HeroRecruitUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruitHero", HeroRecruitUIView::onButtonRecruitHero);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStore", HeroRecruitUIView::onButtonStore);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHeroBook", HeroRecruitUIView::onButtonHeroBook);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonCharge", HeroRecruitUIView::onButtonCharge);


	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruit1", HeroRecruitUIView::onButtonRecruit1);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruit2", HeroRecruitUIView::onButtonRecruit2);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruit3", HeroRecruitUIView::onButtonRecruit3);
	
	return NULL;    
}

SEL_CCControlHandler HeroRecruitUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
// 	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonRecruit1", HeroRecruitUIView::onButtonRecruit1);
// 	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonRecruit2", HeroRecruitUIView::onButtonRecruit2);
// 	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonRecruit3", HeroRecruitUIView::onButtonRecruit3);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonFresh", HeroRecruitUIView::onButtonFresh);

	return NULL;
}

void HeroRecruitUIView::onButtonRecruitHero(cocos2d::CCObject * pSender)
{
	// ignore

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroRecruitUIView::onButtonStore(cocos2d::CCObject * pSender)
{

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SECRETSTORE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroRecruitUIView::onButtonHeroBook(cocos2d::CCObject * pSender)
{

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROBOOK_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroRecruitUIView::onButtonCharge(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);
	//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroRecruitUIView::onButtonRecruit1(cocos2d::CCObject * pSender)
{
// 	SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[0]);

	sendRecruitHero(0);
	flagOfRecruiting = 1;
	guideLayer = NULL;



}

void HeroRecruitUIView::onButtonRecruit2(cocos2d::CCObject * pSender)
{
	sendRecruitHero(1);
	flagOfRecruiting = 1;
	guideLayer = NULL;
}

void HeroRecruitUIView::onButtonRecruit3(cocos2d::CCObject * pSender)
{
// 	SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[2]);
	sendRecruitHero(2);
	flagOfRecruiting = 1;
	guideLayer = NULL;
}

void HeroRecruitUIView::sendRecruitHero(int index)
{
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	string timeStr = "";
	int glodCost;
	bool flag = pSelf->getRecruitHeroCostGold(glodCost);

	ObjectManager *pManager = DataPool::GetSingleton()->getObjectManager();
	PlayerData* pData =   pManager->getSelf()->playerData();

	int selfGlod = pData->GetGold();

	if (flag)
	{

		if( glodCost > 0 )
		{
			if (selfGlod >= glodCost)
			{
				timeStr = UtilTools::GET_TEXT_FROM_LANG(519) + string(UtilTools::IntToString(glodCost)) + UtilTools::GET_TEXT_FROM_LANG(520);

				ModalDialogView *dialog =  ModalDialogView::createDialog(timeStr, this);
				dialog->setTag(TAG_RECRUIT_HERO_1 + index);
				addChild(dialog,1);
			}
			else
			{
				timeStr = UtilTools::GET_TEXT_FROM_LANG(550);
				ModalDialogView *dialog = ModalDialogView::createDialog(timeStr, this);
				dialog->setTag(TAG_NOT_GLOD);
				addChild(dialog,1);
			}
			
		}
		else
		{
			SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[index]);
		}

	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void HeroRecruitUIView::onButtonFresh(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	string timeStr = "";
	int glodCost = pSelf->getFreshHeroMoney();
	X_INT num =  (pSelf->playerData()->GetFreeRefreshNum());
	if (num>0)
	{
		glodCost =0;
	}
	

	ObjectManager *pManager = DataPool::GetSingleton()->getObjectManager();
	PlayerData* pData =   pManager->getSelf()->playerData();

	int selfGlod = pData->GetGold();
 
		//if( mFreshmilliSecond > 0 &&glodCost > 0)//时间不需要了
		if( glodCost > 0)
		{
			if(selfGlod >= glodCost)
			{
				char buffFresh[MAX_STRING_BUFF_SIZE] = {0};
				sprintf(buffFresh,UtilTools::GET_TEXT_FROM_LANG(551),glodCost);
// 				timeStr = UtilTools::GET_TEXT_FROM_LANG(519) + string(UtilTools::IntToString(glodCost)) + UtilTools::GET_TEXT_FROM_LANG(520);
				timeStr = buffFresh;

				ModalDialogView *dialog = ModalDialogView::createDialog(timeStr, this);
				dialog->setTag(TAG_FRESH_HERO);
				addChild(dialog,1);
			}
			else
			{
				timeStr = UtilTools::GET_TEXT_FROM_LANG(550);
				ModalDialogView *dialog = ModalDialogView::createDialog(timeStr, this);
				dialog->setTag(TAG_NOT_GLOD);
				addChild(dialog,1);
			}

		}
		else
		{
		 	SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_FRESH);
		}

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

bool HeroRecruitUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos1", CCSprite *, mPos[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos2", CCSprite *, mPos[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos3", CCSprite *, mPos[2]);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFreshInfo", CCLabelTTF *, mFreshInfo);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitButton1", CCMenuItemImage *, mRecruitButton[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitButton2", CCMenuItemImage *, mRecruitButton[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitButton3", CCMenuItemImage *, mRecruitButton[2]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitText1", CCSprite *, mRecruitText[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitText2", CCSprite *, mRecruitText[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitText3", CCSprite *, mRecruitText[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName1", CCLabelBMFont *, mName[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName2", CCLabelBMFont *, mName[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mName3", CCLabelBMFont *, mName[2]);
	

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitTab1", CCMenuItemImage *, mRecruitTab[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitTab2", CCMenuItemImage *, mRecruitTab[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitTab3", CCMenuItemImage *, mRecruitTab[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitFreshText", CCSprite *, mRecruitFreshText);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRecruitTip", CCSprite *, mRecruitTip);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNewFresh", CCSprite *, mNewFresh);
	

    return false;
}

bool HeroRecruitUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool HeroRecruitUIView::init()
{
    bool bRet = true;

    //   
// 	mRecruitTab[0]->selected();

    return bRet;
}

void HeroRecruitUIView::updateFreshTime( float time )
{
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	string timeStr = "";
	int glodCost;
	bool flag = pSelf->getRecruitHeroCostGold(glodCost);

	if (flag)
	{
		timeStr = UtilTools::GET_TEXT_FROM_LANG(519) + string(UtilTools::IntToString(glodCost)) + UtilTools::GET_TEXT_FROM_LANG(520);
	}else
	{
		timeStr = UtilTools::GET_TEXT_FROM_LANG(522);
	}
	/*
	mFreshmilliSecond =  (pSelf->playerData()->GetRecruitRefreshLefttime());
	if( mFreshmilliSecond > 0 )
	{
		timeStr += "  ";
        timeStr += UtilTools::ConvertMillisecondToTimeString( mFreshmilliSecond );

		mFreshInfo->setString( timeStr.c_str());

	}else
	{
		string des;
		if (flag)
		{
			des = timeStr;
		}
		else
		{
			des = UtilTools::GET_TEXT_FROM_LANG(521);
		}

		mFreshInfo->setString(des.c_str());

	}*/

	X_INT num =  (pSelf->playerData()->GetFreeRefreshNum());
	if (num > 0)
	{
		X_CHAR tip[256] = {0};
		sprintf(tip,UtilTools::GET_TEXT_FROM_LANG(530),num); 
		timeStr += tip;
		mNewFresh->setVisible(true);
	}else
	{
		X_CHAR tip[256] = {0};
		sprintf(tip,UtilTools::GET_TEXT_FROM_LANG(529),pSelf->getFreshHeroMoney()); 
		timeStr += tip;
		mNewFresh->setVisible(false);
	}
	
	mFreshInfo->setString( timeStr.c_str());

}



void HeroRecruitUIView::onDataUpdate( bool isDataValid )
{	
	mMainStatus->onDataUpdate( isDataValid );
	if( !isDataValid )
	{
		return;
	}

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData* pData = pSelf->playerData();
	if (pData->GetLevel() < 5)
	{
		//mRecruitTip->setVisible(true);
		//mRecruitTip->setString(UtilTools::GET_TEXT_FROM_LANG(596));

	}else if(pData->GetLevel() >= 5 && pData->GetLevel() < 9)
	{
		//mRecruitTip->setVisible(true);
		//mRecruitTip->setString(UtilTools::GET_TEXT_FROM_LANG(597));
	}
	else
	{
		//mRecruitTip->setVisible(false);
		CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage("Recruit_all_heros.png");
		mRecruitTip->setTexture(texture2D1);
	}

	X_INT size = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_RECRUIT);
	ObjectHero *pHero;
	X_INT    tipHeroId = -1;
	//招募篮英雄
	for (X_INT i = 0 ;i< size;i++)
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_RECRUIT);

		if( !pHero ||!pHero->IsDataReady() )
			continue;

		mHeroList[i] = pHero;

		if( mHeroSpriteList[i] )
			mHeroSpriteList[i]->removeFromParentAndCleanup( true );

        mHeroSpriteList[i] = CCSprite::create( pHero->GetRecruitIcon().c_str() );
		mHeroSpriteList[i]->setPosition( mPos[i]->getPosition() );
		mHeroSpriteList[i]->setScale(0.55f);
		mHeroSpriteList[i]->setOpacity(0);
		addChild( mHeroSpriteList[i] );

	

		//char buffQua[MAX_STRING_BUFF_SIZE] = {0};
		//sprintf(buffQua,"Recruit_bg_%d.png",pHero->GetQuality());
		//CCTexture2D *texture2D = CCTextureCache::sharedTextureCache()->addImage(buffQua);
		//mPos[i]->setTexture(texture2D);

		mName[i]->setString(pHero->GetName().c_str());
		mName[i]->setZOrder(mHeroSpriteList[i]->getZOrder()+1);
		mName[i]->setOpacity(0);	
		//是否可以招募
		if( pHero->HeroCanRecruit() )
		{
			mRecruitButton[i]->setEnabled( true );
			mRecruitButton[i]->setColor( ccWHITE );
			mRecruitText[i]->setColor( ccWHITE );

			//是否魂魄
			if( pHero->HeroIsSprite() )
			{
				CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage( "n_sprite_text.png" );
				mRecruitText[i]->setTexture( pTexture );
			}
			else
			{
				CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage( "recruitText.png" );
				mRecruitText[i]->setTexture( pTexture );
				if (tipHeroId ==-1)
				{
					tipHeroId = i;
				}
			}
		}
		
		else
		{
			mRecruitButton[i]->setEnabled( false );
		//	mRecruitButton[i]->setColor(ICON_COLOR_GRAY);//150
			CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage( "n_recruited_text.png" );
			mRecruitText[i]->setTexture( pTexture );
		}
	}
	
	/*mFreshmilliSecond =  (pSelf->playerData()->GetRecruitRefreshLefttime());
	if( mFreshmilliSecond > 0 )
	{
		CCTexture2D *texture2D = CCTextureCache::sharedTextureCache()->addImage("frashText.png");
		mRecruitFreshText->setTexture(texture2D);
	}
	else
	{
		CCTexture2D *texture2D = CCTextureCache::sharedTextureCache()->addImage("n_free_fresh_text.png");
		mRecruitFreshText->setTexture(texture2D);
	}*/

    updateFreshTime( 0 );
	 
	X_INT tipId = ((HeroRecruitUI *)this->getUserData())->getTipId();

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
			if (tipId == 5)
			{
				 
				if ( 0 <= tipHeroId &&tipHeroId<=2 )
				{
					CCSize wSize = CCDirector::sharedDirector()->getWinSize();
					if (tipHeroId == 0)
					{
						guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroRecruitUIView::onButtonRecruit1),NULL);

					}else if (tipHeroId == 1)
					{
						guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroRecruitUIView::onButtonRecruit2),NULL);
						guideLayer->setGuidePos(ccpAdd(ccp(wSize.width * 0.3,0),guideLayer->getGuidePos()));

					}if (tipHeroId == 2)
					{
						guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(HeroRecruitUIView::onButtonRecruit3),NULL);
						guideLayer->setGuidePos(ccpAdd(ccp(wSize.width * 0.6,0),guideLayer->getGuidePos()));

					}

					guideLayer->setPosition(getPosition());
					addChild(guideLayer);
				}
			}
			else if (tipId == 6)
			{
				guideLayer = guidelinesLayer::createLayer(tipId,this);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
			}
		}
	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
	
	if (flagOfRecruiting)
	{
		flagOfRecruiting = 0;
		for (int i =0; i< 3; i++)
		{
			mName[i]->setOpacity(255);
			mHeroSpriteList[i]->setOpacity(255);
		}
	}
	else
	{
		for (int i =0; i< 3; i++)
		{
			CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("cardBg.png");
			mPos[i]->setTexture(texture);
		}
		//翻牌动画效果
		for (int i =0; i< 3; i++)
		{
			/*CCOrbitCamera::create(0.3f, 1,0,0,90,0,0), 
			CCCallFunc::create(this, callfunc_selector(HeroRecruitUIView::changeBackSide)),
			CCOrbitCamera::create(0.6f, 1,0,-90,180,0,0), */
			CCArray *actionsArray = CCArray::create(
				CCOrbitCamera::create(0.3f, 1,0,0,90,0,0),
				CCCallFunc::create(this, callfunc_selector(HeroRecruitUIView::changeFrontSide)),
				CCOrbitCamera::create(0.3f, 1,0,-90,90,0,0),
				CCCallFunc::create(this, callfunc_selector(HeroRecruitUIView::visibleHero)), NULL);

			actionsArray->insertObject(CCDelayTime::create(i * 0.2f),0);
// 			if (i == 2)
// 			{
// 				actionsArray->addObject(CCCallFunc::create(this, callfunc_selector(HeroRecruitUIView::visibleHero)));
// 			}
			CCAction *action = CCSequence::create(actionsArray);
			mPos[i]->runAction(action);
		}
		flagOfReEffect = true;
	}

}

void HeroRecruitUIView::changeBackSide()
{
 	static int i = 0;
	
 	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("cardBg.png");
	mPos[i]->setTexture(texture);
	i++;
	if (i == 3)
	{
		i = 0;
	}
	//mPos[0]->setTexture(texture);
}
void HeroRecruitUIView::changeFrontSide()
{
	static int i = 0;

 	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("main_zm_back.png");
	mPos[i]->setTexture(texture);
	i++;
	if (i == 3)
	{
		i = 0;
	}
	//mPos[0]->setTexture(texture);
}

void HeroRecruitUIView::visibleHero()
{
// 	for (int i =0; i< 3; i++)
// 	{
// 		CCAction *action = CCFadeIn::create(0.5);
// 		mHeroSpriteList[i]->runAction(action);
// 		CCAction *action1 = CCFadeIn::create(0.5);
// 		mName[i]->runAction(action1);
// 	}
	static int i = 0;
	if (flagOfReEffect)
	{
		i = 0;
		flagOfReEffect = false;
	}

	CCAction *action = CCFadeIn::create(0.5);
	mHeroSpriteList[i]->runAction(action);
 	CCAction *action1 = CCFadeIn::create(0.5);
 	mName[i]->runAction(action1);
	i++;
	if (i == 3)
	{
		i = 0;
	}
}

void HeroRecruitUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	switch (pSender->getTag())
	{
	case TAG_FRESH_HERO:
		SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_FRESH);
		break;
	case TAG_RECRUIT_HERO_1:
		SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[0]);
		break;
	case TAG_RECRUIT_HERO_2:
		SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[1]);
		break;
	case TAG_RECRUIT_HERO_3:
		SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_SINGLE, mHeroList[2]);
		break;
	case TAG_NOT_GLOD:
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);
		break;
	default:
		break;
	}

	pSender->closeDialogView();
	
}
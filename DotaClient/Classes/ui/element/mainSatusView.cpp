#include "mainSatusView.h"
#include "../../Game.h"

#include "cocos-ext.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"

#include "./event/EventSystem.h"
#include "./ui/UISystem.h"
#include "./base/pp.h"

#include "./game/SendPacket.h"
#include "./timer/SystemTimer.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

//progress
#define MAX_PROGRESS_WIDTH_RATE		(0.468)
#define MAX_PROGRESS_HEIGHT_RATE    (0.017)


#define PROCESSBAR_FULL_WIDTH	(0.485f)

#define SCREEN_SIZE CCDirector::sharedDirector()->getWinSize()
#define SCALE_SHININGSPRITE  (SCREEN_SIZE.width / 640)

MainStatusView::MainStatusView()
: mTitle(NULL),
  mProcessText(NULL),
  mProcessExpText(NULL),
  mVip(NULL),
  mCoinNum(NULL),
  mGemNum(NULL),
  mWoodNum(NULL),
  mProcessBar1(NULL),
  mProcessBar2(NULL),
  mLevel(NULL),
  mAchieveN(NULL),
  mAchieveIcon(NULL),
  mMessageIcon(NULL)
{
  mtime = 0;
}

MainStatusView::~MainStatusView()
{
	CC_SAFE_RELEASE(mTitle);
	CC_SAFE_RELEASE(mProcessText);
	CC_SAFE_RELEASE(mProcessExpText);
	CC_SAFE_RELEASE(mVip);
	CC_SAFE_RELEASE(mCoinNum);
	CC_SAFE_RELEASE(mGemNum);
	CC_SAFE_RELEASE(mWoodNum);
	CC_SAFE_RELEASE(mProcessBar1);
	CC_SAFE_RELEASE(mProcessBar2);

	CC_SAFE_RELEASE(mLevel);

	CC_SAFE_RELEASE(mAchieveN);
	CC_SAFE_RELEASE(mAchieveIcon);

	CC_SAFE_RELEASE(mMessageIcon);
	CC_SAFE_RELEASE(mtime);
}


void MainStatusView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
	onDataUpdate( false );
	
}
void MainStatusView::onEnter()
{
	CCLayer::onEnter();	
	getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&MainStatusView::update),this,1,kCCRepeatForever,0,XFALSE);
	 
}
void MainStatusView::onExit()
{
	CCLayer::onExit();	
	unscheduleAllSelectors();
}
void MainStatusView::update(float dt)
{
	if (!mtime)
	{
		return;
	}
	tm* tm = SystemTimer::GetSingleton()->GetServerDate();
	

	char buff[64] = {0};

	sprintf(buff, "%02d:%02d:%02d", tm->tm_hour, tm->tm_min ,tm->tm_sec);

	mtime->setString(buff);
	

}
SEL_MenuHandler MainStatusView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onMessage", MainStatusView::onMessage);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onChart", MainStatusView::onChart);
    //CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSetting", MainStatusView::onSetting);
	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAchieveShow", MainStatusView::onButtonAchieveShow);

	return NULL;    
}


SEL_CCControlHandler MainStatusView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {

	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonUserInfo", MainStatusView::onButtonUserInfo);

    return NULL;
}

bool MainStatusView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTitle", CCLabelTTF *, this->mTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessText", CCLabelBMFont *, this->mProcessText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessExpText", CCLabelBMFont *, this ->mProcessExpText);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mVip", CCLabelTTF *, this->mVip);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCoinNum", CCLabelBMFont *, this->mCoinNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGemNum", CCLabelBMFont *, this->mGemNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWoodNum", CCLabelBMFont *, this->mWoodNum);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar1", CCScale9Sprite *, this->mProcessBar1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessBar2", CCScale9Sprite *, this->mProcessBar2);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLevel", CCLabelBMFont *, this->mLevel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAchieveN", CCSprite *, this->mAchieveN);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAchieveIcon", CCMenuItemImage *, this->mAchieveIcon);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMessageIcon", CCMenuItemImage *, this->mMessageIcon);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mtime", CCLabelBMFont *, this->mtime);
	
    return false;
}

bool MainStatusView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
 

    return bRet;
}

// on "init" you need to initialize your instance
bool MainStatusView::init()
{
    bool bRet = true;

    return bRet;
}
 

void MainStatusView::onChart(cocos2d::CCObject * pSender)
{
	
	//EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
	CCSprite *spriteMessage = (CCSprite *)getChildByTag(1001);
	spriteMessage->setVisible(false);
	spriteMessage->stopAllActions();

	SendLogicPacket::OpenMailBox();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MESSAGE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainStatusView::onButtonAchieveShow(cocos2d::CCObject * pSender)
{
	CCSprite *spriteAchieve = (CCSprite *)getChildByTag(1002);
	spriteAchieve->setVisible(false);
	spriteAchieve->stopAllActions();

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_ACHIEVE_SHOW);
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainStatusView::onButtonUserInfo(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	if (UISystem::GetSingleton()->IsLayoutShow("main"))
	{

		EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_USER_INFO_SHOW);

		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	}
	
}
 

void MainStatusView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}

	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	if (!pSelf)
	{
		return;
	}
	
	PlayerData* pData = pSelf->playerData();

	ObjectHero* pHero; 
	for (int i = 0; i < MAX_HERO_RECRUIT_COUNT; i++)
	{
		pHero =  pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
	}

	char buff[MAX_STRING_BUFF_SIZE];
	sprintf( buff, "%d", pData->GetLevel() );
 	mLevel->setString( buff );

	mTitle->setString( pData->getName().c_str() );

// 	sprintf( buff, "VIP%d", pData->GetVipLevel() );
// 	mVip->setString( buff );

	sprintf( buff, "%d", pData->GetGold() );
	mCoinNum->setString( buff );
	sprintf( buff, "%d", pData->GetGem());
	mGemNum->setString(buff);
	sprintf( buff, "%d", pData->GetWood());
	mWoodNum->setString(buff);

	CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();

	float curExp = pData->GetExp();
	float maxExp = pData ->GetMaxExpWithLevel();
	float expPercent = (float)curExp / (float)maxExp;

	if (expPercent == 0)
	{
		mProcessBar1->setVisible(false);
	}
	else
	{
		mProcessBar1->setVisible(true);

		if (expPercent <= 0.05 && expPercent > 0)
		{
			expPercent = 0.05f;
		}

		if (expPercent >= 1)
		{
			expPercent = 1.0f;
		}
		

		//reset anchorPoint
		mProcessBar1->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar1->setInsetLeft(36);
		mProcessBar1->setInsetRight(5);
		mProcessBar1->setInsetTop(5);
		mProcessBar1->setInsetBottom(5);

		//mProcessBar1->setPreferredSize(CCSizeMake(PROCESSBAR_FULL_WIDTH * winSize.width * expPercent, 50));
		mProcessBar1->setPreferredSize(CCSizeMake(315.0f * expPercent, 50));
	}

	int curAction = pData->GetActionPoint();
	//for test
	float actPercent = (float)curAction / (float)pData->GetMaxActionPoint();

	//show text
	char aText[MAX_STRING_BUFF_SIZE];
	sprintf( aText, "%d/%d", curAction,pData->GetMaxActionPoint());
	mProcessText->setString(aText);
	


	
	sprintf(aText, "%d/%d", X_INT(curExp), X_INT(maxExp));
	mProcessExpText->setString(aText);

	if (curAction == 0)
	{
		mProcessBar2->setVisible(false);
	}
	else
	{
		mProcessBar2->setVisible(true);

		if (actPercent <= 0.05 && actPercent > 0)
		{
			actPercent = 0.05f;
		}

		if (actPercent >= 1)
		{
			actPercent = 1.0f;
		}
		

		//reset anchorPoint
		mProcessBar2->setAnchorPoint( ccp( 0, 0.5f ));

		mProcessBar2->setInsetLeft(36);
		mProcessBar2->setInsetRight(5);
		mProcessBar2->setInsetTop(5);
		mProcessBar2->setInsetBottom(5);

		//mProcessBar2->setPreferredSize(CCSizeMake(PROCESSBAR_FULL_WIDTH * winSize.width * actPercent, 50));
		mProcessBar2->setPreferredSize(CCSizeMake(315.0f * actPercent, 50));
	}
	
	//achieve
	//礼包标志闪烁
	CCSprite *spriteAchieve;
	CCSequence *sequenceAchieve;
	if (getChildByTag(1002))
	{
		spriteAchieve = (CCSprite *) getChildByTag(1002);
	}
	else
	{
		spriteAchieve = CCSprite::create("get_achievement1.png");
		if (spriteAchieve)
		{
			CCPoint pos =  mAchieveIcon->getParent()->convertToWorldSpace(mAchieveIcon->getPosition());//world pos
			pos =  this->convertToNodeSpace(pos);
			spriteAchieve->setPosition(pos);
			spriteAchieve->setScaleX(SCALE_SHININGSPRITE);
			addChild(spriteAchieve);
			spriteAchieve->setTag(1002);
		}
	}
	{
		CCSize sizeOfSprite = spriteAchieve->getContentSize();
		CCTexture2D *texture0 = CCTextureCache::sharedTextureCache()->addImage("get_achievement1.png");
		CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage("get_achievement2.png");
		CCTexture2D *texture2 = CCTextureCache::sharedTextureCache()->addImage("get_achievement3.png");
		CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture0,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture1,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture2,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture1,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture2,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));


		CCArray *aniArray = CCArray::createWithCapacity(4);

		aniArray->addObject(frame0);
		aniArray->addObject(frame1);
		aniArray->addObject(frame2);
		aniArray->addObject(frame3);
		aniArray->addObject(frame4);
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniArray,0.25f);
		CCAnimate *animate = CCAnimate::create(animation);
		CCAction *action = CCRepeat::create(animate, 2);
		CCArray *actionArray = CCArray::createWithCapacity(4);
		actionArray->addObject(action);
		actionArray->addObject(CCDelayTime::create(1.0f));
		actionArray->addObject(action);
		actionArray->addObject(CCDelayTime::create(10.0f));
		sequenceAchieve = CCSequence::create(actionArray);
	}
	

	
	//邮件标志闪烁
	CCSprite *spriteMessage;
	CCSequence *sequenceMessage;
	if (getChildByTag(1001))
	{
		spriteMessage = (CCSprite *) getChildByTag(1001);
	}
	else
	{
		spriteMessage = CCSprite::create("m_guide_mask.png");
		if (spriteMessage)
		{
			CCPoint pos =  mMessageIcon->getParent()->convertToWorldSpace(mMessageIcon->getPosition());//world pos
			pos =  this->convertToNodeSpace(pos);
			spriteMessage->setPosition(pos);
			spriteMessage->setScaleX(SCALE_SHININGSPRITE);
			addChild(spriteMessage);
			spriteMessage->setTag(1001);
		}
	}
	{
		CCSize sizeOfSprite = spriteMessage->getContentSize();
		CCTexture2D *texture0 = CCTextureCache::sharedTextureCache()->addImage("get_message0.png");
		CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage("get_message1.png");
		CCTexture2D *texture2 = CCTextureCache::sharedTextureCache()->addImage("get_message2.png");
		CCTexture2D *texture3 = CCTextureCache::sharedTextureCache()->addImage("get_message3.png");
		CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture0,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture1,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture2,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture3,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture2,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCSpriteFrame *frame5 = CCSpriteFrame::createWithTexture(texture1,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCArray *aniArray = CCArray::createWithCapacity(6);

		aniArray->addObject(frame0);
		aniArray->addObject(frame1);
		aniArray->addObject(frame2);
		aniArray->addObject(frame3);
		aniArray->addObject(frame4);
		aniArray->addObject(frame5);
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniArray,0.05f);
		CCAnimate *animate = CCAnimate::create(animation);
		CCAction *action = CCRepeat::create(animate, 2);
		CCArray *actionArray = CCArray::createWithCapacity(4);
		actionArray->addObject(action);
		actionArray->addObject(CCDelayTime::create(1.0f));
		actionArray->addObject(action);
		actionArray->addObject(CCDelayTime::create(10.0f));
		sequenceMessage = CCSequence::create(actionArray);
	}
	
	
	
	if (DataPool::GetSingleton()->getAchievementData()->HasAchievementDone())
	{
		//mAchieveN->setVisible(true);
		spriteAchieve->setVisible(true);
		if (spriteAchieve->getActionByTag(1004))
		{
		}
		else
		{
			CCAction *action = CCRepeatForever::create(sequenceAchieve);
			action->setTag(1004);
			spriteAchieve->runAction(action);
		}
		mAchieveIcon->setNormalImage(CCSprite::create("get_achievement1.png"));
		mAchieveIcon->setSelectedImage(CCSprite::create("get_achievement1.png"));
		mAchieveIcon->setDisabledImage(CCSprite::create("get_achievement1.png"));
	}
	else
	{
		
		//mAchieveN->setVisible(false);
		spriteAchieve->setVisible(false);
		spriteAchieve->stopAllActions();
		mAchieveIcon->setNormalImage(CCSprite::create("get_achievement0.png"));
		mAchieveIcon->setSelectedImage(CCSprite::create("get_achievement1.png"));
		mAchieveIcon->setDisabledImage(CCSprite::create("get_achievement0.png"));
	}
	
	//message
	

	if (DataPool::GetSingleton()->getMailData()->getNotifyMail())
	{

		spriteMessage->setVisible(true);
		if (spriteMessage->getActionByTag(1003))
		{
		}
		else
		{
			CCAction *action = CCRepeatForever::create(sequenceMessage);
			action->setTag(1003);
			spriteMessage->runAction(action);
		}
		
		
		mMessageIcon->setNormalImage(CCSprite::create("m_guide_mask.png"));
		mMessageIcon->setSelectedImage(CCSprite::create("m_guide_mask.png"));
		mMessageIcon->setDisabledImage(CCSprite::create("m_guide_mask.png"));
	}
	else
	{
		 
		spriteMessage->setVisible(false);
		spriteMessage->stopAllActions();
		mMessageIcon->setNormalImage(CCSprite::create("get_message0.png"));
		mMessageIcon->setSelectedImage(CCSprite::create("get_message1.png"));
		mMessageIcon->setDisabledImage(CCSprite::create("get_message1.png"));
	 
	}
	//層級關係調整
	mProcessText->setZOrder(mProcessBar2->getZOrder()+1);
	mProcessExpText->setZOrder(mProcessBar1->getZOrder()+1);

	if (mtime)
	{
		mtime->setScale(1.03f);
		mtime->setZOrder(spriteMessage->getZOrder()+1);
	}
}

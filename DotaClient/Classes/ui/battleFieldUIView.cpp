#include "./ui/BattleFieldUIView.h"
#include "./ui/element/SkillAnimation.h"
#include "./ui/element/FightTips.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./sound/SoundSystem.h"
#include "./game/GameHelper.h"
#include "./object/ObjectManager.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./ui/battleFieldUI.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define STEP_BAR_RELA_MIN      (0.010f)
#define STEP_BAR_RELA_MAX      (0.960f)

#define STEP_BAR_RELA_Y        (0.5f)
#define STEP_ICON_OFFSET       (0.05f)

#define POSITION_RESET_DELAY         (0.3f)

#define POSITION_TARGET_OFFSET_Y     (0.1f)

#define SKILL_Z_ORDER                (5)
#define TIPS_Z_ORDER                 (10)

#define STATUS_FRAME_OFFSET_Y        (-0.057f)
#define STATUS_BLOOD_OFFSET_X        (-0.09f)
#define STATUS_BLOOD_OFFSET_Y        (-0.082f)
#define STATUS_MAGIC_OFFSET_X        (-0.09f)
#define STATUS_MAGIC_OFFSET_Y        (-0.088f)

#define STATUS_BLOOD_OFFSET_X_IPAD   (-0.09f + 0.016f)

#define STATUS_PREFER_SIZE_X         (0.18f)
#define STATUS_PREFER_SIZE_Y         (0.008f)

#define TIP_DELAY_DELTA              (0.25f)

#define MAX_ANIMATION_FRAMES         (32)

#define CARD_SCALE                  ( (0.40f)*SCALE_X)
#define CARD_SCALE_SHITI              ( CARD_SCALE *2.3f)

#define BATTLE_MAX_NUM					 120

#define BLOOD_TIPS_OFFSET            (0.05f)

static float s_battle_pos_up[6][2] =
{
	0.20f, 0.69f, 0.5f, 0.69f, 0.80f, 0.69f,
	0.20f, 0.89f, 0.5f, 0.89f, 0.80f, 0.89f
};

static float s_battle_pos_down[6][2] =
{
	0.20f, 0.32f, 0.5f, 0.32f, 0.80f, 0.32f,
	0.20f, 0.12f, 0.5f, 0.12f, 0.80f, 0.12f
};

static float s_battle_pos_up_column[6][2] =
{
	0.20f, 0.4f, 0.5f, 0.4f, 0.80f, 0.4f,
	0.20f, 0.4f, 0.5f, 0.4f, 0.80f, 0.4f
};

static float s_battle_pos_down_column[6][2] =
{
	0.20f, 0.6f, 0.5f, 0.6f, 0.80f, 0.6f,
	0.20f, 0.6f, 0.5f, 0.6f, 0.80f, 0.6f	
};
 
// the return CCArray* should be insert to scene, and release auto
static CCArray* GetAnimFrames( const char *name )
{
	char skillPlist[MAX_STRING_BUFF_SIZE];
	sprintf( skillPlist, "%s.plist", name );

	char skillImage[MAX_STRING_BUFF_SIZE];
	sprintf( skillImage, "%s.png", name );
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( skillPlist, skillImage );
		
	CCArray* animFrames = CCArray::createWithCapacity( MAX_ANIMATION_FRAMES );
        
	for( int i = 0; i < MAX_ANIMATION_FRAMES; i++ ) 
    {
        sprintf( skillPlist, "%s_%05d.png", name, i );
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( skillPlist );
		if( frame )
            animFrames->addObject( frame );
		else
			break;
    }

	return animFrames;
}

BattleFieldUIView::BattleFieldUIView()
{
	setRoundDelay( 0.3f );

	mIsRoundPlay = false;

	mBattleNum = NULL;
	bShowBreakoutBattle = false;
	bShowBreakoutBattleOfOutTime = false;
	bShowBreakoutBattleLevelCheck = false;
	mAccelerate = 1.0f;
	mpAccelerate = NULL;
	AccelerateMaxLevel = 1;
	mpAccelerateEx = 0;
}

BattleFieldUIView::~BattleFieldUIView()
{
}
void BattleFieldUIView::addLevelIcon(cocos2d::CCNode* pNode,cocos2d::CCSprite* heroFrame, X_INT level )
{
	if (!pNode ||!heroFrame  )
	{
		return;
	}
	
	CCSprite *mLevelBack = CCSprite::create("hero_level_icon.png");
	mLevelBack->setAnchorPoint(CCPoint(0.5f,0.5f)) ;
 
	CCPoint pos = heroFrame->getPosition();

	pos.x  -= heroFrame->getContentSize().width *0.40f *heroFrame->getScale();
	pos.y  += heroFrame->getContentSize().height *0.40f*heroFrame->getScale();

	mLevelBack->setPosition(pos);mLevelBack->setScale(0.7f);
	pNode->addChild(mLevelBack); 

	char aText[MAX_STRING_BUFF_SIZE];
	sprintf( aText, "%d", level);
	CCLabelBMFont *mLevelLable = CCLabelBMFont::create(aText, FNT_NAME_HEROLEVEL);
	mLevelLable -> setAnchorPoint(ccp(0.5f, 0.5f));
	mLevelLable -> setPosition(CCPoint(mLevelBack->getContentSize().width/2.0f,mLevelBack->getContentSize().height/2.0f));
	mLevelBack -> addChild(mLevelLable);
}




bool BattleFieldUIView::init()
{
	CCLayer::init();

	mDebutDelay = 0;

	// 
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	pBattle->tickRound();


	const vector<BattleObject*> attacker = pBattle->getAttack();
    const vector<BattleObject*> defender = pBattle->getDefense();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	string backImg = "battleField_1.png";
	if(DataPool::GetSingleton()->BattlyType == EM_SPORT) 
	{
		 
	}else
	{
		const CopyScene*  curScene = DataPool::GetSingleton()->getCopySceneManager()->getFightScene();
		if (curScene)
		{
			string img = curScene->getImg();
			if (img != "-1" &&img.length() > 0 )
			{
				backImg = img;
			} 
		}
	}

	if (mBattleNum)
	{
		mBattleNum->removeFromParentAndCleanup(true);
		mBattleNum = NULL;
	}
	
	CCSprite *spriteBK = CCSprite::create( backImg.c_str() );
    spriteBK->setPosition( ccp( winSize.width / 2, winSize.height / 2 ) );
    spriteBK->setScaleX(SCALE_X);
    spriteBK->setScaleY(SCALE_Y);
    addChild( spriteBK );

	mStepBar = CCSprite::create( "fightProcessBar.png" );
	mStepBar->setAnchorPoint( ccp( 0.5f, 0.5f ) );	
	mStepBar->setPosition( ccp( winSize.width * 0.5f, winSize.height * STEP_BAR_RELA_Y ) );
	addChild( mStepBar );

	mStatusPreferSize.width = winSize.width * STATUS_PREFER_SIZE_X;
	mStatusPreferSize.height = winSize.width * STATUS_PREFER_SIZE_Y;


    
	for( X_UINT i = 0; i < attacker.size(); i ++ )
	{
		CCNode *heroNode = CCNode::create();
		heroNode->setPosition( ccp( winSize.width * s_battle_pos_down[attacker[i]->GetPosition()][0], winSize.height * s_battle_pos_down[attacker[i]->GetPosition()][1] ) );

		CCSprite *sprite = CCSprite::create( attacker[i]->GetBody().c_str() );
		sprite->setScale( CARD_SCALE );
		heroNode->addChild( sprite );
		sprite->setPosition(CCPoint(0.f,CARD_SCALE*sprite->getContentSize().height*0.1f));
		
		CCSprite *heroFrame = CCSprite::create( GameHelper::GetHeroFighterColorById(attacker[i]->GetColor()).c_str());
		heroNode->addChild( heroFrame, -1 );

		addLevelIcon(heroNode,heroFrame,attacker[i]->GetLevel() );
	 

		CCSprite *statusFrame = CCSprite::create( "statusBarFrame.png" );
		statusFrame->setPosition( ccp( 0, winSize.height * STATUS_FRAME_OFFSET_Y ) );
		heroNode->addChild( statusFrame );

       
        float scale = statusFrame->getScale();
		StatusBar* bloodBar = StatusBar::createWith( "bloodBar.png" );
		bloodBar->setAnchorPoint(CCPoint(0.f,0.5f));
		bloodBar->setPosition( CCPoint(statusFrame->getContentSize().width*0.14f*scale, statusFrame->getContentSize().height*0.61f*scale) );
		statusFrame->addChild( bloodBar );
		mAttackMemberBloodBar.push_back( bloodBar );

		
		StatusBar* magicBar = StatusBar::createWith( "magicBar.png" );
		magicBar->setPosition( CCPoint(statusFrame->getContentSize().width*0.14f*scale, statusFrame->getContentSize().height*0.38f*scale) );
		magicBar->setAnchorPoint(CCPoint(0.f,0.5f));
		statusFrame->addChild( magicBar );
		mAttackMemberMagicBar.push_back( magicBar );

		mAttackMember.push_back( heroNode );
		addChild( heroNode );

		CCNode *logoNode = CCNode::create();

		sprite = CCSprite::create( "teamLogo_s.png" );
		logoNode->addChild( sprite );

// 		sprite = CCSprite::create( "n_bat_small_icon.png" );//n_bat_small_icon.png   heroProcessFrame
// 		sprite->setPosition( ccp( 0, -winSize.height * STEP_ICON_OFFSET ) );
// 		sprite->setFlipY( true );
// 		logoNode->addChild( sprite );

		sprite = CCSprite::create( attacker[i]->GetSmallIcon().c_str() );
		sprite->setPosition( ccp( 0, -winSize.height * STEP_ICON_OFFSET ) );
		logoNode->addChild( sprite );

	    logoNode->setPosition( getStepBarPos( 0 ) );
		addChild( logoNode );

		mAttackMemberStep.push_back( logoNode );

		mAttackMemberBloodMax.push_back( attacker[i]->GetMaxHP() );
		mAttackMemberBlood.push_back( attacker[i]->GetHP() );

		mAttackMemberMagicMax.push_back( attacker[i]->GetMaxMP() );
		mAttackMemberMagic.push_back( attacker[i]->GetMP() );

		//mDebutDelay = max( mDebutDelay, debut( heroNode, attacker[i]->GetPosition(), true, DEBUT_TYPE_TRANS ) );
	}

	for( X_UINT i = 0; i < defender.size(); i ++ )
	{
		CCNode *heroNode = CCNode::create();
		heroNode->setPosition( ccp( winSize.width * s_battle_pos_up[defender[i]->GetPosition()][0], winSize.height * s_battle_pos_up[defender[i]->GetPosition()][1] ) );

		CCSprite *sprite = CCSprite::create( defender[i]->GetBody().c_str() );
		sprite->setScale( CARD_SCALE ); 
		heroNode->addChild( sprite );
		sprite->setPosition(CCPoint(0.f,CARD_SCALE*sprite->getContentSize().height*0.1f));

		
		CCSprite *heroFrame = CCSprite::create( GameHelper::GetHeroFighterColorById(defender[i]->GetColor()).c_str() );
		heroNode->addChild( heroFrame, -1 );

		addLevelIcon(heroNode,heroFrame,defender[i]->GetLevel() );
  

		CCSprite *statusFrame = CCSprite::create( "statusBarFrame.png" );
		statusFrame->setPosition( ccp( 0, winSize.height * STATUS_FRAME_OFFSET_Y ) );
		heroNode->addChild( statusFrame );

		float scale = statusFrame->getScale();
		StatusBar* bloodBar = StatusBar::createWith( "bloodBar.png" );
		bloodBar->setPosition( CCPoint(statusFrame->getContentSize().width*0.14f*scale, statusFrame->getContentSize().height*0.61f*scale) );
		bloodBar->setAnchorPoint(CCPoint(0.f,0.5f));
		statusFrame->addChild( bloodBar );
		mDefendMemberBloodBar.push_back( bloodBar );

		
		StatusBar* magicBar = StatusBar::createWith( "magicBar.png" );
		magicBar->setPosition( CCPoint(statusFrame->getContentSize().width*0.14f*scale, statusFrame->getContentSize().height*0.38f*scale) );
		magicBar->setAnchorPoint(CCPoint(0.f,0.5f));
		statusFrame->addChild( magicBar );
		mDefendMemberMagicBar.push_back( magicBar );

		mDefendMember.push_back( heroNode );
		addChild( heroNode );

		CCNode *logoNode = CCNode::create();

		sprite = CCSprite::create( "enemyLogo_s.png" );
		logoNode->addChild( sprite );

// 		sprite = CCSprite::create( "n_bat_small_icon.png" );
// 		sprite->setPosition( ccp( 0, winSize.height * STEP_ICON_OFFSET ) );
// 		logoNode->addChild( sprite );

		sprite = CCSprite::create( defender[i]->GetSmallIcon().c_str() );
		sprite->setPosition( ccp( 0, winSize.height * STEP_ICON_OFFSET ) );
		logoNode->addChild( sprite );

	    logoNode->setPosition( getStepBarPos( 0 ) );
		addChild( logoNode );

		mDefendMemberStep.push_back( logoNode );

		mDefendMemberBloodMax.push_back( defender[i]->GetMaxHP() );
		mDefendMemberBlood.push_back( defender[i]->GetHP() );

		mDefendMemberMagicMax.push_back( defender[i]->GetMaxMP() );
		mDefendMemberMagic.push_back( defender[i]->GetMP() );

		//mDebutDelay = max( mDebutDelay, debut( heroNode, defender[i]->GetPosition(), false, DEBUT_TYPE_TRANS ) );
	}

	mIsRoundPlay = false;
	mStepTimer = mRoundDelay;
	mRoundAttackCount = -1;
	mAttackActionStep = ATTACK_STEP_START;
	mAttackSkillCount = -1;
	mBuffTimer = -1;

	char buffNum[MAX_STRING_BUFF_SIZE]={0};
	sprintf(buffNum,UtilTools::GET_TEXT_FROM_LANG(574),0);
	mBattleNum = CCLabelTTF::create(buffNum,FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
	mBattleNum->setPosition(ccp(winSize.width * 0.97f, winSize.height));
	mBattleNum->setAnchorPoint(ccp(1,1));
	addChild(mBattleNum,20);



	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	if (pDataFile)
	{
		const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_BATTLE_BREAK_OUTLEVEL);
		if (pTableData)
		{

			X_INT level = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetLevel();
			if (level >= pTableData->m_value)
			{
				bShowBreakoutBattleLevelCheck = true;
			}else
			{
				bShowBreakoutBattleLevelCheck = false;
			}    
		}	
	}
	calcAccelerateLevel();
 
	/*if(DataPool::GetSingleton()->BattlyType == EM_COPY_SCENE)
	{
		bShowBreakoutBattleOfOutTime = false;

		const CopyScene*  curScene = DataPool::GetSingleton()->getCopySceneManager()->getAwardScene();
		if (curScene&&curScene->getStar() >= 5) 
		{
				bShowBreakoutBattle = true;
				AddBattle_breakMenu();
			
		}
	}else
	{
		bShowBreakoutBattleOfOutTime  = true;
	}*/




 
    return true;
}

void BattleFieldUIView::onEnter()
{
	AddBattle_AccelerateMenu();
	BaseView::onEnter();	
	scheduleUpdate();
	//this->getScheduler()->setTimeScale(mAccelerate);
}

void BattleFieldUIView::onExit()
{
	unscheduleUpdate();
	this->getScheduler()->setTimeScale(1.0f);
	BaseView::onExit();
}

float BattleFieldUIView:: debut( cocos2d::CCNode *node, int posIndex, bool isAttacker, int type )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	switch( type )
	{
	/*case DEBUT_TYPE_TRANS:
		{
		    CCArray* framesArray = GetAnimFrames( "zjz_chuansong" );
			SkillAnimation *effect = SkillAnimation::createWith( framesArray, 2.0f, 0.1f, false, false, 0 );
			effect->playAnimation();	
			effect->setPosition( node->getPosition() );
			addChild( effect, SKILL_Z_ORDER );

			node->setVisible( false );
			CCActionInterval *seq = (CCActionInterval*)( CCSequence::create( CCDelayTime::create( effect->getPlayTime() * 0.5f ), CCShow::create(), NULL ) );
	
			node->runAction( seq );

			return effect->getPlayTime();
		}
		break;*/
	case DEBUT_TYPE_JUMP:
		{
			CCPoint offsetPos;
			
			switch( posIndex ) 
			{
			case 0:
			case 3:
				offsetPos = ccp( winSize.width * 0.25f, 0 );
				break;
			case 1:
			case 4:
				offsetPos = ccp( 0, winSize.width * (isAttacker?0.25f:-0.25f) );
				break;
			case 2:
			case 5:
				offsetPos = ccp( winSize.width * -0.25f, 0 );
				break;
			default :
				break;
			}

			node->setPosition( ccpSub( node->getPosition(), offsetPos ) );

			CCActionInterval *seq = (CCActionInterval*)( CCSequence::create( CCJumpBy::create( 1.0f, offsetPos, winSize.height * 0.10f, 2), NULL ) );
	
			node->runAction( seq );

			return 1.0f;
		}
		break;
	case DEBUT_TYPE_BLINK:
		{
			CCArray* framesArray = GetAnimFrames( "zjz_shijianjiejie" );
			SkillAnimation *effect = SkillAnimation::createWith( framesArray, 0.6f, 0.2f, false, false, 0 );
			effect->playAnimation();	
			effect->setPosition( node->getPosition() );
			addChild( effect, SKILL_Z_ORDER );

			node->setVisible( false );
			CCActionInterval *seq = (CCActionInterval*)( CCSequence::create( CCDelayTime::create( effect->getPlayTime() * 0.5f ), CCShow::create(), NULL ) );
	
			node->runAction( seq );

			return effect->getPlayTime();
		}
		break;
	case DEBUT_TYPE_RUSH:
		{

		}
		break;
	case DEBUT_TYPE_PUSH:
		{
		}
		break;
	case DEBUT_TYPE_CRUSH:
		{
		}
		break;
	default :
	    break;
	}

	return 0;
}
 
void   BattleFieldUIView::menuBattle_AccelerateCallback(CCObject* pSender)
{

		BattleFieldUI *pUi =  (BattleFieldUI*)(getUserData());
		if (!pUi)return;


	 pUi->AccelerateCurlLevel++;
	 
	  if ( pUi->AccelerateCurlLevel   > AccelerateMaxLevel)
	  { 
		   pUi->AccelerateCurlLevel = 1;
	  } 
	  const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACCELERATE);
	  const stDBC_FILE_ACCELERATE	*  pTableData = X_NULL;
	  if (AccelerateMaxLevel == 1)
	  {
		  pTableData = (const stDBC_FILE_ACCELERATE*)pDataFile->GetFieldsByIndexKey(AccelerateMaxLevel+1);
		  if (!pTableData)
		  {
			  return;
		  }
		  vector<string> strV;strV.clear();

		  X_CHAR str[256] = {0};
		  sprintf(str,UtilTools::GET_TEXT_FROM_LANG(714),pTableData->openLevel);
		  strV.push_back(str);
		  EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		  return;
	  } 
	  pTableData = (const stDBC_FILE_ACCELERATE*)pDataFile->GetFieldsByIndexKey( pUi->AccelerateCurlLevel);
	  if (!pTableData)
	  {
		  return;
	  }
	  CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage( pTableData->icon);

	  mpAccelerateEx->setTexture(texture);
	  this->getScheduler()->setTimeScale(pTableData->speed);

	  X_FLOAT scale = 1 + 0.9 *( pUi->AccelerateCurlLevel-1 )/5; 
	  //mpAccelerateEx->setScale(scale);
	  CCSequence *seq = CCSequence::create(CCScaleTo::create(0.2f, scale),CCScaleTo::create(0.3f, (scale+1)*0.5f),NULL);
	  mpAccelerateEx->runAction(seq);
	 

} 
void   BattleFieldUIView::calcAccelerateLevel()
{
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	X_INT level = pSelf->playerData()->GetLevel();
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACCELERATE);
	const stDBC_FILE_ACCELERATE	*  pTableData = X_NULL;
	X_UINT num = pDataFile->GetRecordsNum();
	for (X_UINT i = 0;i< num ;i++)
	{
		pTableData = (const stDBC_FILE_ACCELERATE*)pDataFile->GetFieldsByLineNum(i);
		if (!pTableData)continue;
		if (level >= pTableData->openLevel  )
		{
			AccelerateMaxLevel = pTableData->Id;
		}
	}
}
void   BattleFieldUIView::AddBattle_AccelerateMenu()
{
	 
	   BattleFieldUI *pUi =  (BattleFieldUI*)(getUserData());
	   if (!pUi)return;
	   const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACCELERATE);
	   const stDBC_FILE_ACCELERATE	*  pTableData = X_NULL;
	   if ( pUi->AccelerateCurlLevel > AccelerateMaxLevel )
	   {
		    pUi->AccelerateCurlLevel = AccelerateMaxLevel ;
	   }

	   pTableData = (const stDBC_FILE_ACCELERATE*)pDataFile->GetFieldsByIndexKey( pUi->AccelerateCurlLevel);
	   if (!pTableData)
	   {
		   return;
	   }
	this->getScheduler()->setTimeScale(pTableData->speed);

	mpAccelerateEx = TouchButtonEx::create(pTableData->icon,this,callfuncO_selector(BattleFieldUIView::menuBattle_AccelerateCallback));
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	mpAccelerateEx->setPosition(ccp(size.width-45, size.height *0.5f +5) );
	this->addChild(mpAccelerateEx, 0);

	if (AccelerateMaxLevel == 1)
	{
		mpAccelerateEx->setColor(ccGRAY);
	} 
}
void   BattleFieldUIView::AddBattle_breakMenu()
{
	 
	 CCMenuItemImage *pbattle_break = CCMenuItemImage::create(
		"m_guide_mask.png",
		"m_guide_mask.png",
		this,
		menu_selector(BattleFieldUIView::menuBattle_breakCallback));

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	pbattle_break->setPosition(ccp(size.width-50, size.height *0.5f-10) );
	CCMenu* pMenu = CCMenu::create(pbattle_break,0, NULL);
	pMenu->setPosition(ccp(0, 0) );
	this->addChild(pMenu, 0);

 
	CCSprite *spriteBreak = CCSprite::create("battle_break0.png");
	if (spriteBreak)
	{
		CCPoint pos =  pbattle_break->getParent()->convertToWorldSpace(pbattle_break->getPosition());//world pos
		pos =  this->convertToNodeSpace(pos);
		CCSize sizeOfSprite = spriteBreak->getContentSize();
		CCTexture2D *texture0 = CCTextureCache::sharedTextureCache()->addImage("battle_break0.png");
		CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture0,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCTexture2D *texture1 = CCTextureCache::sharedTextureCache()->addImage("battle_break1.png");
		CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture1,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCTexture2D *texture2 = CCTextureCache::sharedTextureCache()->addImage("battle_break2.png");
		CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture2,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCTexture2D *texture3 = CCTextureCache::sharedTextureCache()->addImage("m_guide_mask.png");
		CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture3,CCRectMake(0,0,sizeOfSprite.width,sizeOfSprite.height));
		CCArray *aniArray = CCArray::createWithCapacity(4);

		if (!bShowBreakoutBattleLevelCheck)
		{
			
		}
		CCGLProgram* program = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor);
		texture0->setShaderProgram(program);
		aniArray->addObject(frame0);
		aniArray->addObject(frame1);
		aniArray->addObject(frame2);
		aniArray->addObject(frame3);
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(aniArray,0.3f);
		CCAnimate *animate = CCAnimate::create(animation);
		spriteBreak->setPosition(pos);
		spriteBreak->setTag(1002);
		addChild(spriteBreak);

		spriteBreak->runAction(CCRepeatForever::create(animate));
	}
}
void   BattleFieldUIView::menuBattle_breakCallback(CCObject* pSender)
{
	if (!bShowBreakoutBattleLevelCheck)
	{
		vector<string> strV;strV.clear();

		char str[256] = {0};

		X_INT level = 11;
		const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
		if (pDataFile)
		{
			const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_BATTLE_BREAK_OUTLEVEL);
			if (pTableData)
			{
				level = pTableData->m_value;
			}	
		}
		sprintf(str,UtilTools::GET_TEXT_FROM_LANG(696),level);
		strV.push_back(str);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
	unscheduleUpdate();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_FIGHTRESULT_SHOW);

}
void BattleFieldUIView::update( float dt )
{
	if( mDebutDelay > 0 )
		mDebutDelay -= dt;
	else
		battleUpdate( dt );

	/*if (!bShowBreakoutBattle  && bShowBreakoutBattleOfOutTime  )
	{
		static float battletime = 0.f;
		battletime += dt;

		X_INT outTime = 5;
		const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
		if (pDataFile)
		{
			const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(BATTLE_BREAK_OUT);
			if (pTableData)
			{
				outTime = pTableData->m_value;
			}	
		}
		if (battletime >= outTime)
		{
			bShowBreakoutBattle = true;
			battletime = 0;
			AddBattle_breakMenu();
		}
	}*/

 

}

void BattleFieldUIView::battleUpdate( float dt )
{
	
	
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	const vector<BattleObject*> attacker = pBattle->getAttack();
    const vector<BattleObject*> defender = pBattle->getDefense();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	mStepTimer -= dt;

	

	X_INT curRound = pBattle->GetcurRound();
	//X_INT round = pBattle->GetRound();
	char buffNum[MAX_STRING_BUFF_SIZE]={0};
	sprintf(buffNum,UtilTools::GET_TEXT_FROM_LANG(574),curRound );
	mBattleNum->setString(buffNum);


	if( mIsRoundPlay )
	{
		if( mRoundAttackCount < 0 )
		{
			if( buffUpdate( dt ) )
			{

				mBuffTimer = -1;
				mRoundAttackCount = 0;
			}
		}
		else if( mRoundAttackCount < (int)(pBattle->getRoundAttackData().size()) )
		{
			if( attackUpdate( dt ) )
			{

				mRoundAttackCount ++;
				mAttackSkillCount = -1;
			}
		}
		else
		{
			mStepTimer = mRoundDelay;
			mIsRoundPlay = false;

			if( !pBattle->tickRound() )
			{
				unscheduleUpdate();
				this->getScheduler()->setTimeScale(1.0f);
				EventSystem::GetSingleton()->PushEvent(GAME_EVENT_FIGHTRESULT_SHOW);
				return;
			}
 
		}
	}
	else
	{
		if( mStepTimer <= 0 )
		{
			mRoundAttackCount = -1;
			mAttackActionStep = ATTACK_STEP_START;
			mAttackSkillCount = -1;
			mIsRoundPlay = true;

			// update status value
			mAttackMemberBlood.clear();
			mAttackMemberBloodMax.clear();
			mAttackMemberMagic.clear();
			mAttackMemberMagicMax.clear();
			for( X_UINT i = 0; i < attacker.size(); i ++ )
			{
				mAttackMemberBlood.push_back( attacker[i]->GetHP() );
				mAttackMemberBloodMax.push_back( attacker[i]->GetMaxHP() );
				mAttackMemberMagic.push_back( attacker[i]->GetMP() );
				mAttackMemberMagicMax.push_back( attacker[i]->GetMaxMP() );

				// death check
				if( attacker[i]->GetHP() < 1  && !attacker[i]->bCreateDeadFlag)
				{
					attacker[i]->bCreateDeadFlag = true;
					mAttackMemberStep[i]->setVisible( false );
					mAttackMember[i]->setVisible( false );

					CCSprite *spriteDeath = CCSprite::create( "zhp_shiti.png" );
					spriteDeath->setScale( CARD_SCALE_SHITI );
					spriteDeath->setPosition( mAttackMember[i]->getPosition() );

					addChild( spriteDeath );


				}
			}

			mDefendMemberBlood.clear();
			mDefendMemberBloodMax.clear();
			mDefendMemberMagic.clear();
			mDefendMemberMagicMax.clear();
			for( X_UINT i = 0; i < defender.size(); i ++ )
			{
				mDefendMemberBlood.push_back( defender[i]->GetHP() );
				mDefendMemberBloodMax.push_back( defender[i]->GetMaxHP() );
				mDefendMemberMagic.push_back( defender[i]->GetMP() );
				mDefendMemberMagicMax.push_back( defender[i]->GetMaxMP() );

				// death check
				if( defender[i]->GetHP() < 1 &&!defender[i]->bCreateDeadFlag )
				{
					defender[i]->bCreateDeadFlag = true;
					mDefendMemberStep[i]->setVisible( false );
			        mDefendMember[i]->setVisible( false );

					CCSprite *spriteDeath = CCSprite::create( "zhp_shiti.png" );
					spriteDeath->setScale( CARD_SCALE_SHITI );
					spriteDeath->setPosition( mDefendMember[i]->getPosition() );

					addChild( spriteDeath );

				}
			}

			// fast skip
			if( pBattle->getRoundAttackData().empty() )
			{
				// update buff
				buffUpdate( dt );			
				mBuffTimer = -1;

				mStepTimer = mRoundDelay;
				mIsRoundPlay = false;

				if( !pBattle->tickRound() )
				{
					unscheduleUpdate();

					EventSystem::GetSingleton()->PushEvent(GAME_EVENT_FIGHTRESULT_SHOW);





					return;
				}			
			}
		}
		else
		{
			for( unsigned int i = 0; i < attacker.size(); i ++ )
			{
				float lastPos = attacker[i]->GetFightDistance();

				float curPos = lastPos + attacker[i]->GetAttackSpeed() * (mRoundDelay - mStepTimer) / mRoundDelay;
				float percentPos = curPos / pBattle->GetMaxFightDistance();
				if( percentPos > 1.0f )
					percentPos = 1.0f;

				mAttackMemberStep[i]->setPosition( getStepBarPos( percentPos ) );
			}

			for( unsigned int i = 0; i < defender.size(); i ++ )
			{
				float lastPos = defender[i]->GetFightDistance();

				float curPos = lastPos + defender[i]->GetAttackSpeed() * (mRoundDelay - mStepTimer) / mRoundDelay;
				float percentPos = curPos / pBattle->GetMaxFightDistance();
				if( percentPos > 1.0f )
					percentPos = 1.0f;

				mDefendMemberStep[i]->setPosition( getStepBarPos( percentPos ) );
			}
		}
	}

}

// buff impact
bool BattleFieldUIView::buffUpdate( float dt )
{
	if( mBuffTimer < 0 )
	{
		mBuffTimer = 0;

		BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	
		const vector<BattleObject*> attacker = pBattle->getAttack();
		const vector<BattleObject*> defender = pBattle->getDefense();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		// remove the impact timeout
		for( unsigned int i = 0; i < mLastRoundImapct.size(); i++ )
		{
			mLastRoundImapct[i]->removeFromParentAndCleanup( true );
		}
		for( unsigned int i = 0; i < attacker.size(); i++ )
			mAttackMember[i]->setScale( 1.0f );
		for( unsigned int i = 0; i < defender.size(); i++ )
			mDefendMember[i]->setScale( 1.0f );

		mLastRoundImapct.clear();

		bool isAttackGlobalImpact = false;
		bool isDefendGlobalImpact = false;
		unsigned int   attacker_size = attacker.size();

		for( unsigned int i = 0; i < attacker_size; i++ )
		{
			const vector<Impact *>& impactList = attacker[i]->GetImpact();
			const vector<int>& impactHurt = attacker[i]->GetImpactHurt();
			const vector<int>& magicDelta = attacker[i]->GetMagicDelta();

			float buffDelayTimer = 0;
			for( unsigned int j = 0; j < impactList.size(); j++ )
			{
				if( isAttackGlobalImpact && impactList[j]->GetType() == IMPACT_TYPE_1 )
					continue;

				if( impactList[j]->GetEffect() != "-1" )
				{
					float scale, offsetX, offsetY;

					CCArray* framesArray = GetAnimFrames( impactList[j]->GetEffect().c_str() );

					impactList[j]->GetEffectParam( scale, offsetX, offsetY );

					SkillAnimation *buff = SkillAnimation::createWith( framesArray, scale, impactList[j]->GetEffectPlaySpeed(), true/*!impactList[j]->isPlayOnce()*/, true, 0 );
					buff->playAnimation();	

					if( impactList[j]->GetType() == IMPACT_TYPE_1 )
					{

						buff->setPosition( ccp( winSize.width * (s_battle_pos_down[1][0] + s_battle_pos_down[4][0]) * 0.5f, winSize.height * (s_battle_pos_down[1][1] + s_battle_pos_down[4][1]) * 0.5f ) );

						addChild( buff, SKILL_Z_ORDER );

						isAttackGlobalImpact = true;
					}
					else
					{
						buff->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );

						mAttackMember[i]->addChild( buff, SKILL_Z_ORDER );

						if( impactList[j]->GetType() == IMPACT_TYPE_2 )
						{
							CCSprite *spriteBK = CCSprite::create( "zhp_qingwa.png" );
							spriteBK->setScale( CARD_SCALE * 10 );
							buff->addChild( spriteBK );

							mAttackMember[i]->setScale( 0.1f );
						}
					}

	
						if( impactList[j]->GetEffectSound() != "-1" )
							// 							CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( impactList[j]->GetEffectSound().c_str() );
								SoundSystem::GetSingleton()->playEffect( impactList[j]->GetEffectSound().c_str() );
					
						


					mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );
				}

				if( impactList[j]->GetHitEffect() != "-1" )
				{
					float scale, offsetX, offsetY;

					CCArray* framesArray = GetAnimFrames( impactList[j]->GetHitEffect().c_str() );

					impactList[j]->GetHitEffectParam( scale, offsetX, offsetY );

					SkillAnimation *buff = SkillAnimation::createWith( framesArray, scale, impactList[j]->GetHitEffectPlaySpeed(), false/*!impactList[j]->isPlayOnce()*/, true, buffDelayTimer );
					buff->playAnimation();	

					buff->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );

					mAttackMember[i]->addChild( buff, SKILL_Z_ORDER );

				
						SoundSystem::GetSingleton()->playEffect(impactList[j]->GetHitEffectSound().c_str());
					

					if( j < impactHurt.size() )
					{
						bloodTips( true, i, impactHurt[j], buffDelayTimer );
					}

					if( j < magicDelta.size() )
					{
						magicTips( true, i, magicDelta[j], buffDelayTimer );
					}

					buffDelayTimer += buff->getPlayTime();

					if( impactList[j]->isPlayOnce() )
					    mBuffTimer = max( mBuffTimer, buffDelayTimer );

					mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );
				}
			}
		}
		 unsigned int defender_size = defender.size();
		for( unsigned int i = 0; i < defender_size; i++ )
		{
			const vector<Impact *>& impactList = defender[i]->GetImpact();
			const vector<int>& impactHurt = defender[i]->GetImpactHurt();
			const vector<int>& magicDelta = defender[i]->GetMagicDelta();

			float buffDelayTimer = 0;
			for( unsigned int j = 0; j < impactList.size(); j++ )
			{
				if( isDefendGlobalImpact && impactList[j]->GetType() == IMPACT_TYPE_1 )
					continue;

				if( impactList[j]->GetEffect() != "-1" )
				{
					float scale, offsetX, offsetY;

					CCArray* framesArray = GetAnimFrames( impactList[j]->GetEffect().c_str() );

					impactList[j]->GetEffectParam( scale, offsetX, offsetY );

					SkillAnimation *buff = SkillAnimation::createWith( framesArray, scale, impactList[j]->GetEffectPlaySpeed(), true/*!impactList[j]->isPlayOnce()*/, true, 0 );
					buff->playAnimation();	

					if( impactList[j]->GetType() == IMPACT_TYPE_1 )
					{
						buff->setPosition( ccp( winSize.width * (s_battle_pos_up[1][0] + s_battle_pos_up[4][0]) * 0.5f, winSize.height * (s_battle_pos_up[1][1] + s_battle_pos_up[4][1]) * 0.5f ) );

						addChild( buff, SKILL_Z_ORDER );

						isDefendGlobalImpact = true;
					}
					else
					{
						buff->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );

						mDefendMember[i]->addChild( buff, SKILL_Z_ORDER );

						if( impactList[j]->GetType() == IMPACT_TYPE_2 )
						{
							CCSprite *spriteBK = CCSprite::create( "zhp_qingwa.png" );
							spriteBK->setScale( CARD_SCALE * 10 );
							buff->addChild( spriteBK );

							mDefendMember[i]->setScale( 0.1f );
						}
					}

					
						if( impactList[j]->GetEffectSound() != "-1" )
							//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( impactList[j]->GetEffectSound().c_str() );
								SoundSystem::GetSingleton()->playEffect( impactList[j]->GetEffectSound().c_str() );
					
						

					mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );
				}

				if( impactList[j]->GetHitEffect() != "-1" )
				{
					float scale, offsetX, offsetY;

					CCArray* framesArray = GetAnimFrames( impactList[j]->GetHitEffect().c_str() );

					impactList[j]->GetHitEffectParam( scale, offsetX, offsetY );

					SkillAnimation *buff = SkillAnimation::createWith( framesArray, scale, impactList[j]->GetHitEffectPlaySpeed(), false/*!impactList[j]->isPlayOnce()*/, true, buffDelayTimer );
					buff->playAnimation();	

					buff->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );

					mDefendMember[i]->addChild( buff, SKILL_Z_ORDER );

					
						if( impactList[j]->GetHitEffectSound() != "-1" )
							//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( impactList[j]->GetHitEffectSound().c_str() );
								SoundSystem::GetSingleton()->playEffect( impactList[j]->GetHitEffectSound().c_str() );
					
						
					

					if( j < impactHurt.size() )
					{
						bloodTips( false, i, impactHurt[j], buffDelayTimer );
					}

					if( j < magicDelta.size() )
					{
						magicTips( false, i, magicDelta[j], buffDelayTimer );
					}

					buffDelayTimer += buff->getPlayTime();

					if( impactList[j]->isPlayOnce() )
					    mBuffTimer = max( mBuffTimer, buffDelayTimer );

					mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );
				}
			}
		}
	}
	else
	{
		mBuffTimer -= dt;

		if( mBuffTimer < 0 )
			return true;
	}

    return false;
}

// one hero attack
bool BattleFieldUIView::attackUpdate( float dt )
{
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	const vector<BattleObject*> attacker = pBattle->getAttack();
	const vector<BattleObject*> defender = pBattle->getDefense();

	const cAttackInfo & attackInfo = *(pBattle->getRoundAttackData()[mRoundAttackCount]);

	if( mAttackSkillCount < 0 )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		mCasterNode = 0;
		mTargetNode = 0;
		unsigned int attacker_size = attacker.size();
		for( X_UINT i = 0; i < attacker_size; i++ )
		{
			if( attackInfo.m_CastGuid == attacker[i]->m_Guid )
			{
				mCasterNode = (CCNode*)(mAttackMember[i]);
			}

			if( attacker[i]->m_Guid == (attackInfo.m_bSkilled ? attackInfo.m_SkillAttack[0].m_SkillTarget.GetValue() : (attackInfo.m_SkillTarget.GetValue() != INVALID_INDEX ? attackInfo.m_SkillTarget.GetValue():attackInfo.m_SkillAttack[0].m_SkillTarget.GetValue() )) )
			{
				mTargetNode = (CCNode*)(mAttackMember[i]);

				mTargetCenterPos = ccp( winSize.width * (s_battle_pos_down[1][0] + s_battle_pos_down[4][0]) * 0.5f, winSize.height * (s_battle_pos_down[1][1] + s_battle_pos_down[4][1]) * 0.5f );
				mTargetColumnPos = ccp( winSize.width * s_battle_pos_down_column[attacker[i]->GetPosition()][0], winSize.height * s_battle_pos_down_column[attacker[i]->GetPosition()][1] );
			}
		}
		unsigned int defender_size = defender.size();
		for( unsigned int i = 0; i < defender_size; i++ )
		{
			if( attackInfo.m_CastGuid == defender[i]->m_Guid )
			{
				mCasterNode = (CCNode*)(mDefendMember[i]);
			}

			if( defender[i]->m_Guid == (attackInfo.m_bSkilled ? attackInfo.m_SkillAttack[0].m_SkillTarget.GetValue() : (attackInfo.m_SkillTarget.GetValue() != INVALID_INDEX ? attackInfo.m_SkillTarget.GetValue():attackInfo.m_SkillAttack[0].m_SkillTarget.GetValue() )) )
			{
				mTargetNode = (CCNode*)(mDefendMember[i]);

				mTargetCenterPos = ccp( winSize.width * (s_battle_pos_up[1][0] + s_battle_pos_up[4][0]) * 0.5f, winSize.height * (s_battle_pos_up[1][1] + s_battle_pos_up[4][1]) * 0.5f );
				mTargetColumnPos = ccp( winSize.width * s_battle_pos_up_column[defender[i]->GetPosition()][0], winSize.height * s_battle_pos_up_column[defender[i]->GetPosition()][1] );
			}
		}
		
		if( !mCasterNode || !mTargetNode )
		{
			return true;
		}

		mCasterPosOri = mCasterNode->getPosition();
		mTargetPosOri = mTargetNode->getPosition();
		mTargetMovePos = mTargetPosOri;
		if( mCasterPosOri.y > mTargetPosOri.y )
			mTargetMovePos.y += winSize.height * POSITION_TARGET_OFFSET_Y;
		else
			mTargetMovePos.y -= winSize.height * POSITION_TARGET_OFFSET_Y;
	    
	    mAttackSkillCount = 0;
		mAttackActionStep = ATTACK_STEP_START;
		
		for( unsigned int i = 0; i < MAX_EQUIP_NUM_PER_HERO; i++ )
		{
		    mSkillActionStep[i] = ATTACK_STEP_START;
		}
	}

	if( mAttackSkillCount == 0 )
	{
		if( skillUpdate( dt ) )
		{
			mAttackSkillCount ++;
			mAttackActionStep = ATTACK_STEP_START;
		}
		
		return false;
	}
	else
	{
		if( attackInfo.m_bSkilled )
			return true;
		else
			return normalHitUpdate( dt );
	}
}

// one skill attack
bool BattleFieldUIView::skillUpdate( float dt )
{
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	const vector<BattleObject*> attacker = pBattle->getAttack();
    const vector<BattleObject*> defender = pBattle->getDefense();

	const cAttackInfo & attackInfo = *(pBattle->getRoundAttackData()[mRoundAttackCount]);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int skillsDoneCount = 0;

	for( int skillIndex = 0; skillIndex < attackInfo.m_SkillAttackCount; skillIndex++ )
	{
		const cSkillAttack & skillAttackInfo = attackInfo.m_SkillAttack[skillIndex];

		mSkillStepTimer[skillIndex] -= dt;

		mCasterNode->setZOrder(mCasterNode->getParent()->getZOrder()+1);

		switch( mSkillActionStep[skillIndex] ) 
		{
			case ATTACK_STEP_START :
				
				// do move
				mSkillActionStep[skillIndex] = ATTACK_STEP_IN_MOVE;
				mSkillStepTimer[skillIndex] = 0.3f;					

				switch( Skill::GetCastPostion( skillAttackInfo.m_SkillID )  )
				{
					case ATTACK_MOVE_COLUMN :
						// overlap
						mCasterNode->getParent()->reorderChild( mCasterNode, mCasterNode->getZOrder() + 1 );

						mCasterNode->setPosition( mTargetColumnPos );
						break;
					case ATTACK_MOVE_TARGET :
						// overlap
						mCasterNode->getParent()->reorderChild( mCasterNode, mCasterNode->getZOrder() + 1 );
							
						mCasterNode->setPosition( mTargetMovePos );
						break;
					case ATTACK_MOVE_CENTER :
						// overlap
						mCasterNode->getParent()->reorderChild( mCasterNode, mCasterNode->getZOrder() + 1 );

						mCasterNode->setPosition( mTargetCenterPos );
						break;
					default:
						// overlap
						mCasterNode->getParent()->reorderChild( mCasterNode, mCasterNode->getZOrder() + 1 );

						mSkillStepTimer[skillIndex] = 0;	
						break;
				}				

				break;

			case ATTACK_STEP_IN_MOVE :
					
				if( mSkillStepTimer[skillIndex] <= 0 )
				{
					// do next
					mSkillActionStep[skillIndex] = ATTACK_STEP_IN_LAUNCH;

				   BattleObject* pBattleObj=  pBattle->FindFighterByGUID( attackInfo.m_CastGuid );
				   if (pBattleObj)
				   {
					   skillAttack( pBattleObj->isAttacker(), skillAttackInfo.m_SkillID, mCasterNode );

				   }
				   
					mSkillStepTimer[skillIndex] = 0;

					bool isConAtt = false;
					for( int i = 0; i < skillAttackInfo.m_ImpactCount; i++ )
					{
						if( skillAttackInfo.m_Impact[i].m_ConAttTimes > 0 )
						{
							isConAtt = true;
					        break;
						}
					}

					if( skillAttackInfo.m_ImpactCount && isConAtt )
					{
						FightTips *fightTips = FightTips::createWith( FightTips::TIPS_CONTINUE_ATTACK, 0 );

						fightTips->setPosition( mCasterNode->getPosition() );
	
						addChild( fightTips, TIPS_Z_ORDER );
					}

					if( skillAttackInfo.m_CostMp )
					{
						   BattleObject* pBattleObj=  pBattle->FindFighterByGUID( attackInfo.m_CastGuid );
						   if (pBattleObj)
						   {
							   magicUpdate( pBattleObj->isAttacker(), pBattleObj->GetIndex(), skillAttackInfo.m_CostMp );
						   }
						   
						
					}
				}

				break;

			case ATTACK_STEP_IN_LAUNCH : 
					
				if( mSkillStepTimer[skillIndex] <= 0 )
				{
					// do next
					mSkillActionStep[skillIndex] = ATTACK_STEP_IN_FLY;

					// update position
					CCPoint casterPos = mCasterNode->getPosition();
					CCPoint targetPos = mTargetNode->getPosition();
				
					int skillMode = Skill::GetEffectType( skillAttackInfo.m_SkillID );
					
					//CCLOG("++++++++++++ %d - (106704) %d", skillMode ,skillAttackInfo.m_SkillID );

					// get skill target list
					std::multiset< cocos2d::CCNode* > targetNodeSet;
					for( int i = 0; i < skillAttackInfo.m_ImpactCount; i++ )
					{
						for( int j = 0; j < skillAttackInfo.m_Impact[i].m_TargetCount; j++ )
						{
							BattleObject* pBattleobj = pBattle->FindFighterByGUID( skillAttackInfo.m_Impact[i].m_TargetList[j] );
							if (!pBattleobj)
							{
								continue;
							}
							
							int posIndex =pBattleobj->GetIndex();

							CCNode* targetNode;
							
							if( pBattle->FindFighterByGUID( skillAttackInfo.m_Impact[i].m_TargetList[j] )->isAttacker() )
								targetNode = (CCNode*)(mAttackMember[posIndex]);
							else
								targetNode = (CCNode*)(mDefendMember[posIndex]);

							//if( targetNodeSet.find( targetNode ) == targetNodeSet.end() )
							{
								targetNodeSet.insert( targetNode );
							}
						}
					}

					mSkillStepTimer[skillIndex] = 0;
					mSkillTargetHitTimer[skillIndex].clear();
					//if( Skill::GetEffect( skillAttackInfo.m_SkillID ) != "-1" ) 
					{
			
							float scale, offsetX, offsetY;
							Skill::GetEffectParam( skillAttackInfo.m_SkillID, scale, offsetX, offsetY );
							SoundSystem::GetSingleton()->playEffect(Skill::GetEffectSound( skillAttackInfo.m_SkillID ).c_str());

						for( std::set< cocos2d::CCNode* >::iterator it = targetNodeSet.begin(); it != targetNodeSet.end(); ++it )
						{
							targetPos = (*it)->getPosition();

							if( skillMode == ATTACK_SKILL_LINE )
							{
								CCArray* framesArray = GetAnimFrames( Skill::GetEffect( skillAttackInfo.m_SkillID ).c_str() );
								SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetEffectPlaySpeed( skillAttackInfo.m_SkillID ), true, false );
								skill->playAnimation();	

								SkillLine *line = SkillLine::createWith( targetPos, casterPos, skill, skill->getPlayTime(), CC_DEGREES_TO_RADIANS(90) );
								line->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );
								addChild( line, SKILL_Z_ORDER );

								mSkillStepTimer[skillIndex] = 0;
								mSkillTargetHitTimer[skillIndex].insert( std::multimap<cocos2d::CCNode*, float>::value_type( (*it), 0 ) );
							}
							else if( skillMode == ATTACK_SKILL_BULLET )
							{
								CCArray* framesArray = GetAnimFrames( Skill::GetEffect( skillAttackInfo.m_SkillID ).c_str() );
								SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetEffectPlaySpeed( skillAttackInfo.m_SkillID ), true, false );
								skill->playAnimation();	

								SkillBullet *bullet = SkillBullet::createWith( casterPos, targetPos,
																			   Skill::GetEffectSpeed( skillAttackInfo.m_SkillID ) * winSize.height, skill, CC_DEGREES_TO_RADIANS(90), skillAttackInfo.m_SkillID );
								addChild( bullet, SKILL_Z_ORDER );

								mSkillStepTimer[skillIndex] = 0;

								mSkillTargetHitTimer[skillIndex].insert( std::multimap<cocos2d::CCNode*, float>::value_type( (*it), bullet->getPlayTime() ) );
							}
							else if( skillMode == ATTACK_SKILL_THROUGH )
							{
								// Only one fly through instance
								if( mSkillTargetHitTimer[skillIndex].empty() )
								{
									CCPoint targetThroughPos = targetPos;
									if( targetPos.y > casterPos.y )
										targetThroughPos.y = winSize.height;
									else
										targetThroughPos.y = 0;

									CCArray* framesArray = GetAnimFrames( Skill::GetEffect( skillAttackInfo.m_SkillID ).c_str() );
									SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetEffectPlaySpeed( skillAttackInfo.m_SkillID ), true, false );
									skill->playAnimation();	

									SkillBullet *bullet = SkillBullet::createWith( casterPos, targetThroughPos,
										                                           Skill::GetEffectSpeed( skillAttackInfo.m_SkillID ) * winSize.height, skill, CC_DEGREES_TO_RADIANS(90), skillAttackInfo.m_SkillID );
									addChild( bullet, SKILL_Z_ORDER );

									mSkillStepTimer[skillIndex] = 0;

									float sss = bullet->getPlayTime();

									int a = 0;
								}

								mSkillTargetHitTimer[skillIndex].insert( std::multimap<cocos2d::CCNode*, float>::value_type( (*it), ccpLength( ccpSub( targetPos, casterPos ) ) / (Skill::GetEffectSpeed( skillAttackInfo.m_SkillID ) * winSize.height) ) );
							}
							else
								mSkillTargetHitTimer[skillIndex].insert( std::multimap<cocos2d::CCNode*, float>::value_type( (*it), 0 ) );
						}
					}
				}

				break;

			case ATTACK_STEP_IN_FLY : 
                    
				if( mSkillStepTimer[skillIndex] <= 0 )
				{
					// do next
					mSkillActionStep[skillIndex] = ATTACK_STEP_IN_HIT;
					mSkillStepTimer[skillIndex] = 0;
				}

				break;

			case ATTACK_STEP_IN_HIT : 
					
				if( mSkillStepTimer[skillIndex] <= 0 )
				{
						std::multimap<cocos2d::CCNode*, float>::iterator it = mSkillTargetHitTimer[skillIndex].begin();
						std::multimap<cocos2d::CCNode*, float>::iterator iend = mSkillTargetHitTimer[skillIndex].end();
					for( ; it != iend ; ++it )
					{
						(*it).second -= dt;
					}

					float hitDelayTime = 0;

					// get skill target list
					for( int i = 0; i < skillAttackInfo.m_ImpactCount; i++ )
					{
						for( int j = 0; j < skillAttackInfo.m_Impact[i].m_TargetCount; j++ )
						{

							 BattleObject* pBattleObj=  pBattle->FindFighterByGUID(  skillAttackInfo.m_Impact[i].m_TargetList[j] );
							 if (!pBattleObj)
							 {
								 continue;
							 }
							 
							int posIndex =pBattleObj->GetIndex();

							CCNode* targetNode;
							
							bool isAttacker = pBattleObj->isAttacker();
							if( isAttacker )
								targetNode = (CCNode*)(mAttackMember[posIndex]);
							else
								targetNode = (CCNode*)(mDefendMember[posIndex]);

                            std::multimap<cocos2d::CCNode*, float>::iterator it = mSkillTargetHitTimer[skillIndex].find( targetNode );
							
							if( it == mSkillTargetHitTimer[skillIndex].end() || (*it).second > 0 )
								continue;
							else
								mSkillTargetHitTimer[skillIndex].erase( it );

							// buff active
							if( Impact::GetEffect( skillAttackInfo.m_Impact[i].m_ImpactID ) != "-1" )
							{
								float scale, offsetX, offsetY;
								Impact::GetEffectParam( skillAttackInfo.m_Impact[i].m_ImpactID, scale, offsetX, offsetY );

								CCArray* framesArray = GetAnimFrames( Impact::GetEffect( skillAttackInfo.m_Impact[i].m_ImpactID ).c_str() );
								SkillAnimation *buff = SkillAnimation::createWith( framesArray, scale, Impact::GetEffectPlaySpeed( skillAttackInfo.m_Impact[i].m_ImpactID ), !Impact::isPlayOnce( skillAttackInfo.m_Impact[i].m_ImpactID ), true );
								buff->playAnimation();	

								if( Impact::GetType( skillAttackInfo.m_Impact[i].m_ImpactID ) == IMPACT_TYPE_1 )
								{
									buff->setPosition( mTargetCenterPos );

									addChild( buff, SKILL_Z_ORDER );

									mSkillTargetHitTimer[skillIndex].clear();

									mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );

									break;
								}
								else
								{
								    buff->setPosition( ccp( winSize.width * offsetX, winSize.height * offsetY ) );

									if( isAttacker )
										mAttackMember[posIndex]->addChild( buff, SKILL_Z_ORDER );
									else
										mDefendMember[posIndex]->addChild( buff, SKILL_Z_ORDER );

									if( Impact::GetType( skillAttackInfo.m_Impact[i].m_ImpactID ) == IMPACT_TYPE_2 )
									{
										CCSprite *spriteBK = CCSprite::create( "zhp_qingwa.png" );
										spriteBK->setScale( CARD_SCALE * 10 );
										buff->addChild( spriteBK );

										if( isAttacker )
											mAttackMember[posIndex]->setScale( 0.1f );
										else
											mDefendMember[posIndex]->setScale( 0.1f );
									}
								}

						
									if( Impact::GetEffectSound( skillAttackInfo.m_Impact[i].m_ImpactID ) != "-1" )
										//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( Impact::GetEffectSound( skillAttackInfo.m_Impact[i].m_ImpactID ).c_str() );
											SoundSystem::GetSingleton()->playEffect( Impact::GetEffectSound( skillAttackInfo.m_Impact[i].m_ImpactID ).c_str() );

								
								mLastRoundImapct.push_back( (cocos2d::CCNode*)(buff) );
							}

							// blood tips
							for( int k = 0; k < skillAttackInfo.m_Impact[i].m_ConAttTimes + 1; k++ )
							{
								if( isAttacker )
									bloodTips( true, posIndex, skillAttackInfo.m_Impact[i].m_Hurts[j][k], TIP_DELAY_DELTA * k );
								else
									bloodTips( false, posIndex, skillAttackInfo.m_Impact[i].m_Hurts[j][k], TIP_DELAY_DELTA * k );	
							}

							// magic tips
							if( isAttacker )
								magicTips( true, posIndex, skillAttackInfo.m_Impact[i].m_Mp[j], 0 );
							else
								magicTips( false, posIndex, skillAttackInfo.m_Impact[i].m_Mp[j], 0 );	
							
							// hit effect
							hitDelayTime = skillBeHit( skillAttackInfo.m_SkillID, targetNode );
						}
					}

					if( mSkillTargetHitTimer[skillIndex].empty() )
					{
						// do next
					    mSkillActionStep[skillIndex] = ATTACK_STEP_DONE;

						mSkillStepTimer[skillIndex] = hitDelayTime;
					
						// caster position reset
						{
							CCActionInterval *seq = (CCActionInterval*)CCSequence::create(CCDelayTime::create( POSITION_RESET_DELAY ),
																							CCPlace::create( mCasterPosOri ),
																							NULL);

							

							mCasterNode->runAction( seq );
						}
					}
				}

				break;		

			case ATTACK_STEP_DONE : 

				if( mTargetNode->numberOfRunningActions() ||
					mCasterNode->numberOfRunningActions() )
					break;
				//CCLOG("ATTACK_STEP_DONE ----------------------------- %d-%f-%d",skillIndex,mSkillStepTimer[skillIndex],mCasterNode->getZOrder());
				if( mSkillStepTimer[skillIndex] <= 0 )
				{
					// restore order
					mCasterNode->getParent()->reorderChild( mCasterNode, mCasterNode->getZOrder() -1 );
					
					skillsDoneCount ++;						
				}

				break;

			default:
				assert( 0 );
				break;
		}
	}

	if( skillsDoneCount == attackInfo.m_SkillAttackCount )
		return true;  // finish this action
	else
		return false; // continue this action
}

// one normal attack
bool BattleFieldUIView::normalHitUpdate( float dt )
{
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	const vector<BattleObject*> attacker = pBattle->getAttack();
    const vector<BattleObject*> defender = pBattle->getDefense();

	const cAttackInfo & attackInfo = *(pBattle->getRoundAttackData()[mRoundAttackCount]);

	int skillID = pBattle->FindFighterByGUID( attackInfo.m_CastGuid )->GetProfession();

	
	X_CLIENT_GUID guid =  attackInfo.m_SkillTarget.GetValue() ;
	if (guid == INVALID_INDEX)
	{
		guid =  attackInfo.m_SkillAttack[0].m_SkillTarget.GetValue(); 
	}
	int counterSkillID = pBattle->FindFighterByGUID(guid )->GetProfession();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	switch( mAttackActionStep ) 
	{
		case ATTACK_STEP_START :
			// do move
			mAttackActionStep = ATTACK_STEP_IN_MOVE;
			mStepTimer = 0;					

			break;

		case ATTACK_STEP_IN_MOVE :
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_LAUNCH;
				 BattleObject* pBattleObj=  pBattle->FindFighterByGUID( attackInfo.m_CastGuid );
				if (pBattleObj)
				{
					 skillAttack( pBattleObj->isAttacker(), skillID, mCasterNode );
				}
				
				
				mStepTimer = 0;

				if( attackInfo.m_bStrike )
				{
					FightTips *fightTips = FightTips::createWith( FightTips::TIPS_STRIKE, 0 );

					fightTips->setPosition( mCasterNode->getPosition() );
	
					addChild( fightTips, TIPS_Z_ORDER );
				}
			}

			break;

		case ATTACK_STEP_IN_LAUNCH : 
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_FLY;

				// update position
				CCPoint casterPos = mCasterNode->getPosition();
				CCPoint targetPos = mTargetNode->getPosition();
					
				int skillMode = Skill::GetEffectType( skillID );
				if( skillMode == ATTACK_SKILL_BULLET && Skill::GetEffect( skillID ) != "-1" )
				{

					float scale, offsetX, offsetY;
					Skill::GetEffectParam( skillID, scale, offsetX, offsetY );
					SoundSystem::GetSingleton()->playEffect(Skill::GetEffectSound( skillID ).c_str());

					CCArray* framesArray = GetAnimFrames( Skill::GetEffect( skillID ).c_str() );
					SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetEffectPlaySpeed( skillID ), true, false );
	                skill->playAnimation();	

					SkillBullet *bullet = SkillBullet::createWith( casterPos, targetPos,
																   Skill::GetEffectSpeed( skillID ) * winSize.height, skill, CC_DEGREES_TO_RADIANS(90), skillID );

					addChild( bullet, SKILL_Z_ORDER );

					mStepTimer = bullet->getPlayTime();
				}
				else
				{
					mStepTimer = 0;
				}
			}

			break;

		case ATTACK_STEP_IN_FLY : 
                    
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_HIT;
				mStepTimer = 0;
			}

			break;

		case ATTACK_STEP_IN_HIT : 
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_COUNTER;

				mStepTimer = skillBeHit( skillID, mTargetNode );

				if( !attackInfo.m_bHit )
				{
					FightTips *fightTips = FightTips::createWith( FightTips::TIPS_DODGE, 0 );

					fightTips->setPosition( mTargetNode->getPosition() );
	
					addChild( fightTips, TIPS_Z_ORDER );
				}
				BattleObject* pBattleObj =  pBattle->FindFighterByGUID( guid );
				if (pBattleObj)
				{
					bloodTips( pBattleObj->isAttacker(), pBattleObj->GetIndex(), attackInfo.m_Hurt, 0 );
				}
				
				
			}

			break;

		case ATTACK_STEP_IN_COUNTER : 

			if( mTargetNode->numberOfRunningActions() )
				break;

			if( mStepTimer <= 0 )
			{
				// do next
				if( attackInfo.m_bBackAttack )
				{

					BattleObject* pBattleObj= pBattle->FindFighterByGUID( attackInfo.m_CastGuid );
					if (pBattleObj)
					{
						mStepTimer = skillAttack( !pBattleObj->isAttacker(), counterSkillID, mTargetNode );

						mAttackActionStep = ATTACK_STEP_IN_COUNTER_LAUNCH;

						FightTips *fightTips = FightTips::createWith( FightTips::TIPS_FIGHT_BACK, 0 );

						fightTips->setPosition( mTargetNode->getPosition() );
	
						addChild( fightTips, TIPS_Z_ORDER );

					}
		 
					
				}
				else
				{
					mAttackActionStep = ATTACK_STEP_DONE;
					mStepTimer = 0;
				}						
			}
					
			break;

		case ATTACK_STEP_IN_COUNTER_LAUNCH : 
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_COUNTER_FLY;

				// update position
				CCPoint casterPos = mCasterNode->getPosition();
				CCPoint targetPos = mTargetNode->getPosition();

				int counterSkillMode = Skill::GetEffectType( counterSkillID );

				if( counterSkillMode == ATTACK_SKILL_BULLET && Skill::GetEffect( skillID ) != "-1" )
				{
					float scale, offsetX, offsetY;
					Skill::GetEffectParam( skillID, scale, offsetX, offsetY );
					SoundSystem::GetSingleton()->playEffect(Skill::GetEffectSound( skillID ).c_str());

					CCArray* framesArray = GetAnimFrames( Skill::GetEffect( counterSkillID ).c_str() );
					SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetEffectPlaySpeed( counterSkillID ), true, false );
	                skill->playAnimation();	

					SkillBullet *bullet = SkillBullet::createWith( casterPos, targetPos,
						                                           Skill::GetEffectSpeed( skillID ) * winSize.height, skill, CC_DEGREES_TO_RADIANS(90), counterSkillID );
					
					addChild( bullet, SKILL_Z_ORDER );

					mStepTimer = bullet->getPlayTime();
				}
				else
				{
					mStepTimer = 0;
				}
			}

			break;

		case ATTACK_STEP_IN_COUNTER_FLY : 
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_IN_COUNTER_HIT;
				mStepTimer = 0;
			}

			break;

		case ATTACK_STEP_IN_COUNTER_HIT : 
					
			if( mStepTimer <= 0 )
			{
				// do next
				mAttackActionStep = ATTACK_STEP_DONE;
					
				mStepTimer = skillBeHit( counterSkillID, mCasterNode );
				BattleObject* pBattleObj= pBattle->FindFighterByGUID( attackInfo.m_CastGuid );
			 
				if (pBattleObj)
				{
					bloodTips( pBattleObj->isAttacker(), pBattleObj->GetIndex(), attackInfo.m_BackAttackHurt, 0 );

				}
				
			}

			break;

		case ATTACK_STEP_DONE : 

			if( mTargetNode->numberOfRunningActions() ||
				mCasterNode->numberOfRunningActions() )
				break;

			if( mStepTimer <= 0 )
			{
				// reset
				mAttackActionStep = ATTACK_STEP_START;
						
				return true; // finish this action
			}

			break;

		default:
			assert( 0 );
			break;
	}

	return false; // continue this action
}

cocos2d::CCPoint BattleFieldUIView::getStepBarPos( float percentStep )
{
	CCRect rect = mStepBar->boundingBox();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	return ccp( rect.getMinX() + ( rect.getMaxX() - rect.getMinX() ) * ( percentStep * (STEP_BAR_RELA_MAX - STEP_BAR_RELA_MIN) + STEP_BAR_RELA_MIN ), rect.getMidY() );
}

float BattleFieldUIView::actionAttack( X_INT actionID,  cocos2d::CCNode *node )
{
	assert( node );

	//node->setScale( 1.0f );
	node->setRotation( 0 );

	CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCScaleBy::create( 0.15f, 1.25f ),
		                                                            CCDelayTime::create( 0.3f ),
		                                                            CCScaleBy::create( 0.15f, 1.0f / 1.25f ),
																	NULL ));

	node->runAction( seq );

	return 0.5f;
}

float BattleFieldUIView::actionBeHit( X_INT actionID, cocos2d::CCNode *node )
{
	assert( node );

	//node->setScale( 1.0f );
	node->setRotation( 0 );

	CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCRotateBy::create( 0.10f, 10.0f ),
		                                                            CCRotateBy::create( 0.10f, -10.0f ),
																	CCRotateBy::create( 0.07f, 5.0f ),
																	CCRotateBy::create( 0.07f, -5.0f ),
																	NULL ));

	node->runAction( seq );

	return 0.5f;	
}

float BattleFieldUIView::skillAttack( bool isAttacker, X_INT skillID,  cocos2d::CCNode *node )
{
	assert( node );

	if( ( Skill::GetEffectLogicType( skillID ) == 1 || Skill::GetEffectLogicType( skillID ) == 3 ) 
		&& Skill::GetBeHurtEffect( skillID ) == "-1" )
		return 0;

	float actionTime = actionAttack( Skill::GetCastAction( skillID ), node );

	std::string skillName = Skill::GetCastEffect( skillID );
	if( skillName == "-1" )
		return actionTime;
	
	CCArray* framesArray = GetAnimFrames( skillName.c_str() );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float scale, offsetX, offsetY;
	Skill::GetShotEffectParam( skillID, scale, offsetX, offsetY );
	if( Skill::GetShotEffectSound( skillID ) != "-1" )
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( Skill::GetShotEffectSound( skillID ).c_str() );
		SoundSystem::GetSingleton()->playEffect(Skill::GetShotEffectSound( skillID ).c_str() );

	SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetShotEffectPlaySpeed( skillID ), false, false );

	if( !isAttacker )
	{
		offsetY = -offsetY;
		skill->setRotation( 180 );
	}

	skill->setPosition( ccpAdd( node->getPosition(), ccp( winSize.width * offsetX, winSize.height * offsetY ) ) );
	addChild( skill, SKILL_Z_ORDER );

	skill->playAnimation();	

	//CCLOG("skill attack : %f-%f" , actionTime , skill->getPlayTime());

	return max( skill->getPlayTime(), actionTime );
}

float BattleFieldUIView::skillBeHit( X_INT skillID, cocos2d::CCNode *node )
{
	assert( node );

	if( ( Skill::GetEffectLogicType( skillID ) == 1 || Skill::GetEffectLogicType( skillID ) == 3 ) 
		&& Skill::GetBeHurtEffect( skillID ) == "-1" )
		return 0;

	float actionTime = actionBeHit( Skill::GetBeHurtAction( skillID ), node );

	std::string skillName = Skill::GetBeHurtEffect( skillID );
	if( skillName == "-1" )
		return actionTime;

	CCArray* framesArray = GetAnimFrames( skillName.c_str() );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float scale, offsetX, offsetY;
	Skill::GetHitEffectParam( skillID, scale, offsetX, offsetY );
	if( Skill::GetHitEffectSound( skillID ) != "-1" )
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect( Skill::GetHitEffectSound( skillID ).c_str() );
			SoundSystem::GetSingleton()->playEffect(Skill::GetHitEffectSound( skillID ).c_str() );

	SkillAnimation *skill = SkillAnimation::createWith( framesArray, scale, Skill::GetHitEffectPlaySpeed( skillID ), false, false );
	skill->setPosition( ccpAdd( node->getPosition(), ccp( winSize.width * offsetX, winSize.height * offsetY ) ) );
	addChild( skill, SKILL_Z_ORDER );

	skill->playAnimation();	

	return max( skill->getPlayTime(), actionTime);
}

void BattleFieldUIView::bloodTips( bool isAttacker, int index, int bloodDelta, float delayTime )
{
	if( bloodDelta == 0 )
		return;

	CCNode *ownerNode;
	
	int maxBlood;
	int *pCurBlood;

	StatusBar *bloodBar;



	if( isAttacker )
	{
		ownerNode = mAttackMember[index];
		maxBlood = mAttackMemberBloodMax[index];
		pCurBlood = &(mAttackMemberBlood[index]);

		bloodBar = mAttackMemberBloodBar[index];
	}
	else
	{
		ownerNode = mDefendMember[index];
		maxBlood = mDefendMemberBloodMax[index];
		pCurBlood = &(mDefendMemberBlood[index]);

		bloodBar = mDefendMemberBloodBar[index];
	}

	*pCurBlood -= bloodDelta;


	if( *pCurBlood < 1 )
	{

		BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
		const vector<BattleObject*> attacker = pBattle->getAttack();
		const vector<BattleObject*> defender = pBattle->getDefense();

		bloodBar->setVisible( false );

		// death check
		if( isAttacker )
		{
// 			if (!attacker[index]->bCreateDeadFlag)
// 			{
// 
// 				attacker[index]->bCreateDeadFlag = true;

				mAttackMemberStep[index]->setVisible( false );
				mAttackMember[index]->setVisible( false );

				CCSprite *spriteDeath = CCSprite::create( "zhp_shiti.png" );
				spriteDeath->setScale( CARD_SCALE_SHITI );
				spriteDeath->setPosition( mAttackMember[index]->getPosition() );

				addChild( spriteDeath );
// 			}
		}
		else
		{
// 			if (!defender[index]->bCreateDeadFlag)
// 			{
// 
// 				defender[index]->bCreateDeadFlag = true;

				mDefendMemberStep[index]->setVisible( false );
				mDefendMember[index]->setVisible( false );

				CCSprite *spriteDeath = CCSprite::create( "zhp_shiti.png" );
				spriteDeath->setScale( CARD_SCALE_SHITI );
				spriteDeath->setPosition( mDefendMember[index]->getPosition() );

				addChild( spriteDeath );
// 			}
		}

	}
	else
	{
		// update bloodBar
		bloodBar->setUpdateLen( (float)(*pCurBlood) / maxBlood );
	}

    FightTips *fightTips = FightTips::createWith( FightTips::TIPS_BLOOD_NUM, bloodDelta, delayTime );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	fightTips->setPosition( ccpAdd( ownerNode->getPosition(), ccp( 0, BLOOD_TIPS_OFFSET * winSize.height ) ) );
	
	addChild( fightTips, TIPS_Z_ORDER );
}

void BattleFieldUIView::magicTips( bool isAttacker, int index, int magicDelta, float delayTime )
{
	if( magicDelta == 0 )
		return;

	CCNode *ownerNode;
	
	if( isAttacker )
		ownerNode = mAttackMember[index];
	else
		ownerNode = mDefendMember[index];

	FightTips *fightTips = FightTips::createWith( FightTips::TIPS_MAGIC_NUM, magicDelta, delayTime );

	fightTips->setPosition( ownerNode->getPosition() );
	
	addChild( fightTips, TIPS_Z_ORDER );

	magicUpdate( isAttacker, index, magicDelta );
}

void BattleFieldUIView::magicUpdate( bool isAttacker, int index, int magicDelta )
{
	if( magicDelta == 0 )
		return;

	CCNode *ownerNode;
	
	int maxMagic;
	int *pCurMagic;

	StatusBar *magicBar;

	if( isAttacker )
	{
		ownerNode = mAttackMember[index];
		maxMagic = mAttackMemberMagicMax[index];
		pCurMagic = &(mAttackMemberMagic[index]);

		magicBar = mAttackMemberMagicBar[index];
	}
	else
	{
		ownerNode = mDefendMember[index];
		maxMagic = mDefendMemberMagicMax[index];
		pCurMagic = &(mDefendMemberMagic[index]);

		magicBar = mDefendMemberMagicBar[index];
	}

	*pCurMagic -= magicDelta;

	if( *pCurMagic < 1 )
	{
		magicBar->setVisible( false );
	}
	else
	{
		// update magicBar
		magicBar->setUpdateLen( (float)(*pCurMagic) / maxMagic );
	}
}

void BattleFieldUIView::draw()
{
	//
}

BattleFieldUIView* BattleFieldUIView::create( struct cFightInfo *pFightInfo )
{
	BattleFieldUIView *p = new BattleFieldUIView();
	if( p )
	{
		p->mFightInfo = pFightInfo;

		p->init();
		
		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}

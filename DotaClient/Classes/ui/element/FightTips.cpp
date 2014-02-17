#include "FightTips.h"
#include "./base/Global.h"
using namespace cocos2d;
USING_NS_CC_EXT;

#define TIPS_MOVE_DISTANCE   (0.1f)
#define TIPS_MOVE_TIME       (0.8f)

#define STATUS_BAR_UPDATE_SPEED  (0.08f)

FightTips::FightTips()
{
}

FightTips::~FightTips()
{
}

void FightTips::onEnter()
{
	CCNode::onEnter();
		
	scheduleUpdate();
}

void FightTips::onExit()
{
	unscheduleUpdate();

	CCNode::onExit();
}

void FightTips::update( float dt )
{
	mDisplayTime -= dt;
	mDelayTime -= dt;

	if( mDelayTime < 0 && !isVisible() )
		setVisible( true );

	if( mDisplayTime < 0 )
	{
		unscheduleUpdate();

		removeFromParentAndCleanup(true);
	}
}

FightTips* FightTips::createWith( int tipId, int num, float delayTime )
{
	FightTips *p = new FightTips();
	if( p )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		if( tipId == TIPS_BLOOD_NUM )
		{
			char buff[32];
			sprintf( buff, "%+d", -num );
			CCLabelBMFont *tips ;
			//tips->setScale( 1.0f );
			
			if( num < 0 )
			{
				tips = CCLabelBMFont::create( buff, FNT_NAME_GREEN );
			}
			else
			{
			    //tips->setColor( ccRED );
				tips = CCLabelBMFont::create( buff, FNT_NAME_RED );
			}
		    
			p->addChild( tips );

// 			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
// 		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
// 																	        NULL ));
	
			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
														CCScaleBy::create(0.09f,2.2f),CCDelayTime::create(0.03f),
														CCScaleTo::create(0.09f,1.0f),NULL ));

			tips->runAction( seq );
		}
		else if( tipId == TIPS_MAGIC_NUM )
		{
			char buff[32];
			sprintf( buff, "%+d", -num );
			CCLabelBMFont *tips = CCLabelBMFont::create( buff, FNT_NAME_BLUE);
	 
			p->addChild( tips );

// 			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
// 		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
// 																	        NULL ));

			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
														CCScaleBy::create(0.09f,2.2f),CCDelayTime::create(0.03f),
														CCScaleTo::create(0.09f,1.0f),NULL ));
	
			tips->runAction( seq );
		}
		else if( tipId == TIPS_STRIKE )
		{
			CCSprite *tips = CCSprite::create( "bigAttack.png" );
			
			p->addChild( tips );

			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
																	        NULL ));
	
			tips->runAction( seq );
		}
		else if( tipId == TIPS_DODGE )
		{
			CCSprite *tips = CCSprite::create( "dodgeText.png" );
			
			p->addChild( tips );

			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
																	        NULL ));
	
			tips->runAction( seq );
		}
		else if( tipId == TIPS_CONTINUE_ATTACK )
		{
			CCSprite *tips = CCSprite::create( "doubleAttack.png" );
			
			p->addChild( tips );

			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
																	        NULL ));
	
			tips->runAction( seq );
		}
		else if( tipId == TIPS_FIGHT_BACK )
		{
			CCSprite *tips = CCSprite::create( "fightBack.png" );
			
			p->addChild( tips );

			CCActionInterval *seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( delayTime ),
		                                                                    CCMoveBy::create( TIPS_MOVE_TIME, ccp( 0, winSize.height * TIPS_MOVE_DISTANCE ) ),
																	        NULL ));
	
			tips->runAction( seq );
		}

		p->setVisible( false );

		p->mDelayTime = delayTime;
		p->mDisplayTime = TIPS_MOVE_TIME + delayTime;
		
		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}


void StatusBar::onEnter()
{
	CCNode::onEnter();
}

void StatusBar::onExit()
{
	unscheduleUpdate();

	CCNode::onExit();
}

void StatusBar::update( float dt )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float curLen = mBar->getPreferredSize().width;

	float targetLen = mPreferSize.width * mTargetLenRela;

	float deltaLen = dt * STATUS_BAR_UPDATE_SPEED * winSize.width;
	
	if( curLen > targetLen )
	{
   	    curLen -= deltaLen;
		if( curLen < targetLen )
		{
			curLen = targetLen;
			unscheduleUpdate();
		}
	}
	else
	{
		curLen += deltaLen;
		if( curLen > targetLen )
		{
			curLen = targetLen;
			unscheduleUpdate();
		}
	}

	CCSize curSize = mPreferSize;
	curSize.width = curLen;

	mBar->setPreferredSize( curSize );
}

void StatusBar::setUpdateLen( float len )
{
	mTargetLenRela = _____min( 1, _____max( 0, len ) );

	unscheduleUpdate();
	scheduleUpdate();
}

StatusBar* StatusBar::createWith( char* imageName )
{
	StatusBar *p = new StatusBar();
	if( p )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		// for CCScale9Sprite setInsetLeft bug fix
		CCTexture2D *bloodBarTexture = CCTextureCache::sharedTextureCache()->addImage( imageName );
		CCSize barSize = bloodBarTexture->getContentSize();
		CCRect capInsets( 1, 1, barSize.width - 2, barSize.height - 2);

		CCScale9Sprite *bar = CCScale9Sprite::create( capInsets, imageName );
		
		bar->setAnchorPoint( ccp( 0, 0.5f ) );
		bar->setPreferredSize( barSize );
		
		p->addChild( bar );

		p->mBar = bar;

		p->mPreferSize = barSize;

		p->mTargetLenRela = 1;
		
		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}

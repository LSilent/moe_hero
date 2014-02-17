#include "SkillAnimation.h"

#include "./datapool/DataPool.h"

using namespace cocos2d;

#define MAX_REPEAT_NUM  (1000)
#define MAX_STRING_BUFF_SIZE     (128)

SkillAnimation::SkillAnimation()
{
}

SkillAnimation::~SkillAnimation()
{
}

void SkillAnimation::onEnter()
{
	CCLayer::onEnter();
		
	scheduleUpdate();
}

void SkillAnimation::onExit()
{
	unscheduleUpdate();

	CCLayer::onExit();
}

void SkillAnimation::update( float dt )
{
	mTimer += dt;

	if( !mIsRepeat && mTimer >= mDisplayTime )
	{
		unscheduleUpdate();

		if( mIsAutoHide )
		{
			stopAllActions();
			setVisible( false );
		}
		else
		{
			CCLOG("------------ remove skill layer");

			removeFromParentAndCleanup( true );
		}
	}
}

void SkillAnimation::playAnimation()
{
	mSprite->stopAllActions();

	CCActionInterval *seq;

	if( mIsRepeat )
		seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( mDelayTime ),
		                                              CCRepeat::create( mAnimate, MAX_REPEAT_NUM ),
													  NULL ));
	else
	    seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( mDelayTime ),
		                                              mAnimate,
													  NULL ));

	mSprite->runAction( seq );

	mTimer = 0;
}

SkillAnimation* SkillAnimation::createWith( cocos2d::CCArray* animationFrames, float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime )
{
	SkillAnimation *p = new SkillAnimation();
	
	if( p )
	{
		assert( animationFrames->count() > 0 );

		p->mSprite = CCSprite::createWithSpriteFrame( (CCSpriteFrame *)animationFrames->objectAtIndex( 0 ) );
		p->mSprite->setScale( scale );
		p->addChild( p->mSprite );

		//FIXME :
		CCSize textureSize = p->mSprite->getTextureRect().size;
		textureSize.width *= scale;
		textureSize.height *= scale;
		p->setContentSize( textureSize );

		p->setAnchorPoint( CCPointZero );

		p->mAnimate = CCAnimate::create( CCAnimation::createWithSpriteFrames( animationFrames, frameDelay ) );
		
		p->mDelayTime = delayTime;
		p->mDisplayTime = animationFrames->count() * frameDelay + delayTime;

		p->mIsRepeat = isRepeat;
		p->mIsAutoHide = isAutoHide;

		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}	

SkillLine::SkillLine()
{
}

SkillLine::~SkillLine()
{
}

void SkillLine::onEnter()
{
	CCLayer::onEnter();
		
	scheduleUpdate();
}

void SkillLine::onExit()
{
	unscheduleUpdate();

	CCLayer::onExit();
}

void SkillLine::update( float dt )
{
	mTimer += dt;

	if( mTimer >= mDisplayTime )
	{
		unscheduleUpdate();

		removeFromParentAndCleanup(true);
	}
}

SkillLine* SkillLine::createWith( const cocos2d::CCPoint &beginPoint, const cocos2d::CCPoint &endPoint, cocos2d::CCNode *line, float playTime, float oriAngle )
{
	SkillLine *p = new SkillLine();
	if( p )
	{
		float length = ccpLength( ccpSub( beginPoint, endPoint ) );
		CCPoint centerPoint = ccpMidpoint( beginPoint, endPoint );

		p->mDisplayTime = playTime;

		p->mLine = line;
		p->mLine->setPosition( centerPoint );

		CCSize lineSize = line->boundingBox().size;

		if( lineSize.width > lineSize.height )
		    p->mLine->setScaleX( length / lineSize.width );
		else
			p->mLine->setScaleY( length / lineSize.height );

		float angle = atan2f( endPoint.y - beginPoint.y, endPoint.x - beginPoint.x );
		float rotateAngle = angle - oriAngle;

		p->mLine->setRotation( CC_RADIANS_TO_DEGREES( -rotateAngle ) );

		p->addChild( p->mLine );

		p->mTimer = 0;

		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}	

SkillBullet::SkillBullet()
{
}

SkillBullet::~SkillBullet()
{
}

void SkillBullet::onEnter()
{
	CCLayer::onEnter();
		
	scheduleUpdate();
}

void SkillBullet::onExit()
{
	unscheduleUpdate();

	CCLayer::onExit();
}

void SkillBullet::update( float dt )
{
	CCPoint pos = mBullet->getPosition();

	pos.x += mSpeed.x * dt;
	pos.y += mSpeed.y * dt;

	if( mSpeed.x * (pos.x - mTargetPos.x) + mSpeed.y * (pos.y - mTargetPos.y) > 0 )
	{
		unscheduleUpdate();

		removeFromParentAndCleanup(true);
	}
	else
	{
		mBullet->setPosition( pos );
	}
}

SkillBullet* SkillBullet::createWith( const cocos2d::CCPoint &beginPoint, const cocos2d::CCPoint &endPoint, float speed, cocos2d::CCNode *bullet, float oriAngle, int skillID )
{
	SkillBullet *p = new SkillBullet();
	if( p )
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCPoint flyVector = ccpSub( endPoint, beginPoint );
		CCPoint flyVectorNormal = ccpNormalize( flyVector );

		p->mSpeed = ccpMult( flyVectorNormal, speed );

		float scale, offsetX, offsetY;
		Skill::GetEffectParam( skillID, scale, offsetX, offsetY );

		flyVectorNormal = ccpMult( flyVectorNormal, offsetY * winSize.height );

        p->mTargetPos = ccpSub( endPoint, flyVectorNormal );
		
		p->mBullet = bullet;
		
		p->mBullet->setPosition( beginPoint );

		float flyAngle = ccpToAngle( ccpSub( p->mTargetPos, beginPoint ) );
		float rotateAngle = flyAngle - oriAngle;

		p->mBullet->setRotation( CC_RADIANS_TO_DEGREES( -rotateAngle ) );

		p->mDisplayTime = (ccpLength( flyVector ) - offsetY * winSize.height) / speed;

		p->addChild( p->mBullet );

		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}	

//----------------------------------------------

EffectAnimation::EffectAnimation()
{
}

EffectAnimation::~EffectAnimation()
{
}

void EffectAnimation::onEnter()
{
	CCLayer::onEnter();

	scheduleUpdate();
}

void EffectAnimation::onExit()
{
	unscheduleUpdate();

	CCLayer::onExit();
}

void EffectAnimation::update( float dt )
{
	mTimer += dt;

	if( !mIsRepeat && mTimer >= mDisplayTime )
	{
		unscheduleUpdate();

		if( mIsAutoHide )
		{
			stopAllActions();
			setVisible( false );
		}
		else
			removeFromParentAndCleanup( true );
	}
	else
	{
		if ( mIsStopAnimate && mTimer >= mDisplayTime )
		{
			unscheduleUpdate();

			mSprite->stopAllActions();
			this->stopAllActions();
			this->removeFromParentAndCleanup(true);

			CCLOG("-------------------------  animation removeFromParentAndCleanup");
		}

		/*if ( mIsStopAnimate && mTimer >= (mDisplayTime * mPlayNum ))
		{
			unscheduleUpdate();

			mSprite->stopAllActions();
			this->stopAllActions();
			this->removeFromParentAndCleanup(true);

			CCLOG("-------------------------  animation removeFromParentAndCleanup");
		}

		if (mTimer >= mDisplayTime * mPlayNum)
		{
			++mPlayNum;
		}*/
	}
}

void EffectAnimation::playAnimation()
{
	mSprite->stopAllActions();

	CCActionInterval *seq;

	if( mIsRepeat )
		seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( mDelayTime ),
		CCRepeat::create( mAnimate, MAX_REPEAT_NUM ),
		NULL ));
	else
		seq = (CCActionInterval*)(CCSequence::create( CCDelayTime::create( mDelayTime ),
		mAnimate,
		NULL ));

	mSprite->runAction( seq );

	mTimer = 0;
}

void EffectAnimation::stopAnimation()
{
	mIsStopAnimate = true;
}

CCArray *EffectAnimation::getAnimationFramesArray(const char * fileName , int frameSize)
{

	char buffFrames[MAX_STRING_BUFF_SIZE]={0};
	sprintf(buffFrames,"%s.plist",fileName);

	char buffFramesPng[MAX_STRING_BUFF_SIZE]={0};
	sprintf(buffFramesPng,"%s.png",fileName);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(buffFrames,buffFramesPng); 

	CCArray* animFrames = CCArray::createWithCapacity( frameSize );

	char skillPlist[MAX_STRING_BUFF_SIZE] = {0};
	for( int i = 0; i < frameSize; i++ ) 
	{
		sprintf( skillPlist, "%s%d.png",fileName,i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( skillPlist );
		if( frame )
			animFrames->addObject( frame );
		else
			break;
	}

	return animFrames;
}



EffectAnimation* EffectAnimation::createWith( const char * fileName, int frameNum , float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime)
{
	EffectAnimation *p = new EffectAnimation();

	if( p )
	{
		//assert( animationFrames->count() > 0 );

		CCArray* animationFrames = p->getAnimationFramesArray(fileName,frameNum);

		p->mSprite = CCSprite::createWithSpriteFrame( (CCSpriteFrame *)animationFrames->objectAtIndex( 0 ) );
		p->mSprite->setScale( scale );
		p->addChild( p->mSprite );

		//FIXME :
		CCSize textureSize = p->mSprite->getTextureRect().size;
		textureSize.width *= scale;
		textureSize.height *= scale;
		p->setContentSize( textureSize );

		p->setAnchorPoint( CCPointZero );

		p->mAnimate = CCAnimate::create( CCAnimation::createWithSpriteFrames( animationFrames, frameDelay ) );

		p->mDelayTime = delayTime;
		p->mDisplayTime = animationFrames->count() * frameDelay + delayTime;

		p->mIsRepeat = isRepeat;
		p->mIsAutoHide = isAutoHide;

		p->mIsStopAnimate = false;
		p->mPlayNum = 1;

		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}

EffectAnimation* EffectAnimation::createWith( cocos2d::CCArray* animationFrames, float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime )
{
	EffectAnimation *p = new EffectAnimation();

	if( p )
	{
		assert( animationFrames->count() > 0 );

		p->mSprite = CCSprite::createWithSpriteFrame( (CCSpriteFrame *)animationFrames->objectAtIndex( 0 ) );
		p->mSprite->setScale( scale );
		p->addChild( p->mSprite );

		//FIXME :
		CCSize textureSize = p->mSprite->getTextureRect().size;
		textureSize.width *= scale;
		textureSize.height *= scale;
		p->setContentSize( textureSize );

		p->setAnchorPoint( CCPointZero );

		p->mAnimate = CCAnimate::create( CCAnimation::createWithSpriteFrames( animationFrames, frameDelay ) );

		p->mDelayTime = delayTime;
		p->mDisplayTime = animationFrames->count() * frameDelay + delayTime;

		p->mIsRepeat = isRepeat;
		p->mIsAutoHide = isAutoHide;

		p->mIsStopAnimate = false;

		p->autorelease();

		return p;
	}

	CC_SAFE_DELETE(p);
	return NULL;
}	
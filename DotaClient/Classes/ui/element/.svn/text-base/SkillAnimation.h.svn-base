#ifndef __SKILL_ANIMATION_H__
#define __SKILL_ANIMATION_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class SkillAnimation : public cocos2d::CCLayer
{
public:
	SkillAnimation();
	~SkillAnimation();

public:
	virtual void onEnter();
	virtual void onExit();

	void playAnimation();

	float getPlayTime() { return mDisplayTime - mDelayTime; }

	static SkillAnimation* createWith( cocos2d::CCArray* animationFrames, float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime = 0 );

protected:
	// update
	virtual void update(float dt);			
	
private:

	float mDelayTime;
	float mDisplayTime;
	float mTimer;

	cocos2d::CCSprite *mSprite;

	cocos2d::CCAnimate* mAnimate;

	bool mIsRepeat;

	// if !mIsRepeat, timeout to hide or suiside
	bool mIsAutoHide;
};

class SkillBullet : public cocos2d::CCLayer
{
public:
	SkillBullet();
	~SkillBullet();

public:
	virtual void onEnter();
	virtual void onExit();

	float getPlayTime() { return mDisplayTime; }

	static SkillBullet* createWith( const cocos2d::CCPoint &beginPoint, const cocos2d::CCPoint &endPoint, float speed, cocos2d::CCNode *bullet, float oriAngle, int skillID );
protected:
	// update
	virtual void update(float dt);			
	
private:
	cocos2d::CCPoint mSpeed;
	cocos2d::CCPoint mTargetPos;

	cocos2d::CCNode *mBullet;

	float mDisplayTime;
};


class SkillLine : public cocos2d::CCLayer
{
public:
	SkillLine();
	~SkillLine();

public:
	virtual void onEnter();
	virtual void onExit();

	float getPlayTime() { return mDisplayTime; }

	static SkillLine* createWith( const cocos2d::CCPoint &beginPoint, const cocos2d::CCPoint &endPoint, cocos2d::CCNode *line, float playTime, float oriAngle );
protected:
	// update
	virtual void update(float dt);			
	
private:
	cocos2d::CCNode *mLine;

	float mDisplayTime;
	float mTimer;
};

//party effect
class EffectAnimation : public cocos2d::CCLayer
{
public:
	EffectAnimation();
	~EffectAnimation();

public:
	virtual void onEnter();
	virtual void onExit();

	void playAnimation();
	void stopAnimation();

	float getPlayTime() { return mDisplayTime - mDelayTime; }

	cocos2d::CCArray *getAnimationFramesArray(const char * fileName , int frameSize);

	static EffectAnimation* createWith( cocos2d::CCArray* animationFrames, float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime = 0 );
	static EffectAnimation* createWith( const char * fileName, int frameNum , float scale, float frameDelay, bool isRepeat, bool isAutoHide, float delayTime = 0 );
protected:
	// update
	virtual void update(float dt);			

private:

	float mDelayTime;
	float mDisplayTime;
	float mTimer;

	cocos2d::CCSprite *mSprite;

	cocos2d::CCAnimate* mAnimate;

	bool mIsRepeat;

	// if !mIsRepeat, timeout to hide or suiside
	bool mIsAutoHide;

	bool mIsPlayOnce;
	bool mIsStopAnimate;

	int mPlayNum;

};


#endif

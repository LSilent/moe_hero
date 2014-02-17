#ifndef __SKILL_LINE_H__
#define __SKILL_LINE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

class FightTips : public cocos2d::CCNode
{
public:
	FightTips();
	~FightTips();

public:
	virtual void onEnter();
	virtual void onExit();

	enum {
		TIPS_BLOOD_NUM       = 0,
		TIPS_MAGIC_NUM       = 1,
		TIPS_STRIKE          = 2,
		TIPS_DODGE           = 3,
		TIPS_CONTINUE_ATTACK = 4,
		TIPS_FIGHT_BACK      = 5
	};

	static FightTips* createWith( int tipId, int num, float delayTime = 0 );
protected:
	// update
	virtual void update(float dt);			
	
private:
	
	float mDelayTime;
	float mDisplayTime;
};

class StatusBar : public cocos2d::CCNode
{

public:
	virtual void onEnter();
	virtual void onExit();

	void setUpdateLen( float len );

	static StatusBar* createWith( char* imageName );
protected:
	// update
	virtual void update(float dt);			
	
private:

	// [0, 1]
	float mTargetLenRela;

	cocos2d::extension::CCScale9Sprite *mBar;
	
	cocos2d::CCSize mPreferSize;
};

#endif

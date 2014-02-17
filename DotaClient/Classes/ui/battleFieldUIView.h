#ifndef __BATTLE_FIELD_UI_VIEW_H__
#define __BATTLE_FIELD_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./ui/element/CCMenuEx.h"
#include "SimpleAudioEngine.h"



class StatusBar;

class BattleFieldUIView : public BaseView
{
public:
	BattleFieldUIView();
	virtual ~BattleFieldUIView();

public:
	virtual bool init();
	void   addLevelIcon(cocos2d::CCNode* pNode,cocos2d::CCSprite* heroFrame, X_INT level );
public:
	virtual void draw();

	virtual void onEnter();
	virtual void onExit();

	static BattleFieldUIView* create( struct cFightInfo *pFightInfo );

	void setRoundDelay( float delay ) {  mRoundDelay = delay; }

protected:
	enum {
		DEBUT_TYPE_TRANS = 0,
		DEBUT_TYPE_JUMP  = 1,
		DEBUT_TYPE_BLINK = 2,
		DEBUT_TYPE_RUSH  = 3,
		DEBUT_TYPE_PUSH  = 4,
		DEBUT_TYPE_CRUSH = 5
	};

	enum {
		IMPACT_TYPE_0 = 0,
		IMPACT_TYPE_1 = 1,
		IMPACT_TYPE_2 = 2
	};

	float debut( cocos2d::CCNode *node, int posIndex, bool isAttacker, int type );

	// update
	virtual void update(float dt);

    cocos2d::CCPoint getStepBarPos( float percentStep );

	float skillAttack( bool isAttacker, X_INT skillID, cocos2d::CCNode *node );
	float skillBeHit( X_INT skillID, cocos2d::CCNode *node );

	float actionAttack( X_INT actionID,  cocos2d::CCNode *node );
	float actionBeHit( X_INT actionID, cocos2d::CCNode *node );

	void bloodTips( bool isAttacker, int index, int bloodDelta, float delayTime );

	void magicTips( bool isAttacker, int index, int magicDelta, float delayTime );

	void magicUpdate( bool isAttacker, int index, int magicDelta );

	void fightTips( bool isAttacker, int index, int tipId );

	void battleUpdate( float dt );

	bool buffUpdate( float dt );

	// one hero attack
	bool attackUpdate( float dt );

	bool skillUpdate( float dt );

	bool normalHitUpdate( float dt );

private:
	
	struct cFightInfo *mFightInfo;

	cocos2d::CCSprite *mStepBar;
	
	std::vector< cocos2d::CCNode* > mLastRoundImapct;

	std::vector< cocos2d::CCNode* > mAttackMember;
	std::vector< cocos2d::CCNode* > mAttackMemberStep;

	std::vector< StatusBar* > mAttackMemberBloodBar;
	std::vector< StatusBar* > mAttackMemberMagicBar;

	std::vector< cocos2d::CCNode* > mDefendMember;
	std::vector< cocos2d::CCNode* > mDefendMemberStep;

	std::vector< StatusBar* > mDefendMemberBloodBar;
	std::vector< StatusBar* > mDefendMemberMagicBar;

	std::vector< int > mAttackMemberBlood;
	std::vector< int > mDefendMemberBlood;
	std::vector< int > mAttackMemberBloodMax;
	std::vector< int > mDefendMemberBloodMax;

	std::vector< int > mAttackMemberMagic;
	std::vector< int > mDefendMemberMagic;
	std::vector< int > mAttackMemberMagicMax;
	std::vector< int > mDefendMemberMagicMax;

    cocos2d::CCSize mStatusPreferSize;

	float mRoundDelay;
	
	int mRoundAttackCount;

	enum {
		ATTACK_STEP_START             = 0,
		ATTACK_STEP_IN_MOVE           = 1,
		ATTACK_STEP_IN_LAUNCH         = 2,
		ATTACK_STEP_IN_FLY            = 3,
		ATTACK_STEP_IN_HIT            = 4,
		ATTACK_STEP_IN_COUNTER        = 5,
		ATTACK_STEP_IN_COUNTER_LAUNCH = 6,
		ATTACK_STEP_IN_COUNTER_FLY    = 7,
		ATTACK_STEP_IN_COUNTER_HIT    = 8,
		ATTACK_STEP_DONE              = 9,
	};
	int mAttackActionStep;
	int mSkillActionStep[MAX_EQUIP_NUM_PER_HERO];

	int mAttackSkillCount;
	
	float mStepTimer;
	float mSkillStepTimer[MAX_EQUIP_NUM_PER_HERO];

	float mDebutDelay;

	std::multimap <cocos2d::CCNode*, float>  mSkillTargetHitTimer[MAX_EQUIP_NUM_PER_HERO];
	
	float mBuffTimer;
	float m_Accelerate;
	
	enum {
		ATTACK_MOVE_NONE   = 0,
		ATTACK_MOVE_COLUMN = 1,
		ATTACK_MOVE_TARGET = 2,
		ATTACK_MOVE_CENTER = 3,
		ATTACK_MOVE_NUM    = 4,
	};

	enum {
		ATTACK_SKILL_NONE    = 0,
		ATTACK_SKILL_LINE    = 1,
		ATTACK_SKILL_BULLET  = 2,
		ATTACK_SKILL_THROUGH = 3,
		ATTACK_SKILL_CENTER  = 4,
		ATTACK_SKILL_NUM     = 5,
	};

	bool mIsRoundPlay;
	
	// for attack play
	cocos2d::CCNode* mCasterNode;
	cocos2d::CCNode* mTargetNode;

	cocos2d::CCPoint mCasterPosOri;
	cocos2d::CCPoint mTargetPosOri;
	cocos2d::CCPoint mTargetMovePos;

	cocos2d::CCPoint mTargetColumnPos;
	cocos2d::CCPoint mTargetCenterPos;

	//
	cocos2d::CCLabelTTF *mBattleNum;
	bool bShowBreakoutBattle;
	bool bShowBreakoutBattleOfOutTime;
	bool bShowBreakoutBattleLevelCheck;

	void   menuBattle_breakCallback(CCObject* pSender);
	void   AddBattle_breakMenu();

	void   menuBattle_AccelerateCallback(CCObject* pSender);
	void   AddBattle_AccelerateMenu();

	void   calcAccelerateLevel();

	float mAccelerate;
	cocos2d::CCMenuItemImage *mpAccelerate ;
	cocos2d::TouchButtonEx *mpAccelerateEx;
	//X_INT Accelerate;
	X_INT AccelerateMaxLevel;//º”ÀŸid

};

#endif

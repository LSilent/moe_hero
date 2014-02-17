#ifndef __GAMEHELPER_H__
#define __GAMEHELPER_H__

#include "./base/Global.h"
#include "./object/Item.h"
#include "./object/ItemCommon.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "cocos2d.h"
using namespace cocos2d;

class GameHelper
{
public:
 
	static  X_INT  GetHeroExpByLevel(X_INT level);

	static bool   getBuyBearPointCost(X_INT id,X_UINT &cost,X_INT& level,X_INT& bearPoint);

	static X_INT  getSkillLevelRate(const  ObjectSkill* pSkill , const vector<ItemCommon*>& items);

	static  string  GetHeroColorById(X_INT id);
	static  string  GetHeroFrameColorById(X_INT id);
	static  string  GetHeroFighterColorById(X_INT id);
	static  string  GetHeroEvolveColorById(X_INT id);
 
	static  X_INT  GetHeroColorByBear(X_INT bear);	

	static X_INT   getMasterSchoolHero(vector<ObjectHero*>& heros);

	static cocos2d::CCSprite* getSpriteLevel(const Item *pEquip);
	static cocos2d::CCSprite* getSpriteLevel(X_INT level);
};

 



#endif
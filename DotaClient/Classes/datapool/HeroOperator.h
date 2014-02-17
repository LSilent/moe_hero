#ifndef __HEROOPERATOR_H__
#define __HEROOPERATOR_H__

#include "./base/Global.h"
#include "./object/ObjectHero.h"
#include "./datapool/DataPool.h"  


 
class HeroUpgrade
{
public:
	/*Ó¢ÐÛÆ·ÖÊ
	enum EM_HERO_QUALITY_TYPE
	{
		EM_HERO_QUALITY_TYPE1=1,	//1=°×
		EM_HERO_QUALITY_TYPE2,		//2=ÂÌ
		EM_HERO_QUALITY_TYPE3,		//3=À¶
		EM_HERO_QUALITY_TYPE4,		//4=×Ï
		EM_HERO_QUALITY_TYPE5,		//5=½ð
	};*/



	static  X_VOID  getUpgradeItem(const ObjectHero* pHero,stMaterialItem & Material);
	static  X_VOID  Release();

	static X_VOID	getUpgradeInfo(const ObjectHero* pHero,X_INT &BearPointLimit,X_INT &BearPoint);
	static X_INT	getUpgradeNeedBearPoint(const ObjectHero* pHero);
		
	static  X_VOID  getRecommendItem(const ObjectHero* pHero,vector<Item*>& RecommendItems);
	static const X_UINT RECOMMEND_ITEM = 4;
private:

	static vector<Item* > m_Items;
	static  Item *  _FindItemByTableID(X_INT tableId);
	
};

 

class  SkillUpgrade
{
public:
	
	X_INT 	getAddSucessRate(const ObjectSkill* pSkill,const Item* pItem);
	const stDBC_FILE_SKILL *	getUpgradeInfo(const ObjectSkill* pSkill);

private:

	 
};
 

#endif // !__HEROOPERATOR_H__

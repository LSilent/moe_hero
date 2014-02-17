#ifndef __OBJECTSELF_H__
#define __OBJECTSELF_H__
 
#include "./object/ObjectPlayer.h"
#include "./object/PlayerData.h"
#include "./object/ObjectHero.h"

class ObjectFactory;
class ObjectSelf  :public ObjectPlayer
{

public:

	static ObjectFactory * __getFactory(); 

	PlayerData*  playerData()
	{
		return m_pData;
	}
	virtual X_VOID Release();
	virtual	X_VOID Tick(X_UINT nTime);

	virtual X_VOID  Add_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,ObjectHero *pHeros,X_BOOL bDestroy = XFALSE);
	virtual X_VOID  Del_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,X_BOOL bDestroy = XFALSE);
	virtual X_BOOL	SwapHero(X_UINT nPos1, EM_HERO_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_HERO_CONTAINER_TYPE nPosType2);
	virtual X_VOID  SetHeroVectorSize(X_UINT size, EM_HERO_CONTAINER_TYPE vector);
	virtual ObjectHero *     getHero(X_UINT nClientPos, EM_HERO_CONTAINER_TYPE nPosType)const;
	virtual X_UINT  GetHeroVectorSize(EM_HERO_CONTAINER_TYPE vector)const;
	virtual X_INT	getHeroNum(EM_HERO_CONTAINER_TYPE nPosType)const;
 
	bool     HeroIsBattle(const ObjectHero *pHero);
 	 
	vector<const ObjectHero*>        getHeroWithEquip(X_INT tableId);


	const ObjectHero *         getHeroWithTableid(X_INT tableId);

	bool  getRecruitHeroCostGold(X_INT & cost);
	X_INT	getFreshHeroMoney();
	 

protected:
	ObjectSelf(X_CLIENT_GUID guid);
	virtual ~ObjectSelf();
	class Factory;

protected:
	
	vector<ObjectHero*>        m_RecruitHeroes;
	X_UINT					   m_RecruitHeroVectorSize;
 
};

 


#endif //__OBJECTPLAYER_H__
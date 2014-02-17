#ifndef __OBJECTPLAYER_H__
#define __OBJECTPLAYER_H__
 
#include "./object/Object.h"
#include "./object/PlayerData.h"
#include "./object/ObjectHero.h"

class ObjectFactory;
class ObjectPlayer  :public Object
{

public:

	static ObjectFactory * __getFactory(); 

	PlayerData*  playerData()
	{
		return m_pData;
	}
	virtual X_VOID  Add_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,ObjectHero *pHeros,X_BOOL bDestroy = XFALSE);
	virtual X_VOID  Del_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,X_BOOL bDestroy = XFALSE);
	virtual X_VOID  Release();

	virtual X_VOID  SetHeroVectorSize(X_UINT size, EM_HERO_CONTAINER_TYPE vector);

	virtual X_UINT  GetHeroVectorSize(EM_HERO_CONTAINER_TYPE vector)const;
	virtual X_BOOL	SwapHero(X_UINT nPos1, EM_HERO_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_HERO_CONTAINER_TYPE nPosType2);

	virtual ObjectHero *     getHero(X_UINT nClientPos, EM_HERO_CONTAINER_TYPE nPosType)const;
	virtual X_INT			 getHeroNum(EM_HERO_CONTAINER_TYPE nPosType)const;


protected:
	ObjectPlayer(X_CLIENT_GUID guid);
	virtual ~ObjectPlayer();
	class Factory;

protected:
	PlayerData*  m_pData;
	vector<ObjectHero*>        m_Heroes;
	X_UINT			m_HeroVectorSize;

};

 


#endif //__OBJECTPLAYER_H__
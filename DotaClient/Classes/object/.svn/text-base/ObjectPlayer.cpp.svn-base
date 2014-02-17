#include "./object/ObjectPlayer.h"
#include "./object/ObjectFactory.h"
#include "./datapool/DataPool.h"
#include "./datapool//QuJingData.h"
class ObjectPlayer::Factory : public ObjectFactory
{
	public:
	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_PLAYER;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectPlayer(guid);
	}

};
ObjectFactory * ObjectPlayer::__getFactory()
{
	static Factory factory;
	return &factory;
}


ObjectPlayer::ObjectPlayer(X_CLIENT_GUID guid)
{
	m_Guid = guid;

	m_pData = new PlayerData();
	m_pData->Initial();
	m_HeroVectorSize = 0;
	m_Heroes.resize(MAX_HERO_NUM,X_NULL);

}
ObjectPlayer::~ObjectPlayer()
{
	 
}
X_VOID  ObjectPlayer::Release()
{
	if (m_pData)
	{
		m_pData->Release();
		SAFE_DELETE(m_pData);
	}
	vector<ObjectHero*>::iterator it = m_Heroes.begin();

	for (;it != m_Heroes.end();it++)
	{
		if (*it)
		{
			DataPool::GetSingleton()->getObjectManager()->DestroyObject(*it);
		}
	}
	m_Heroes.clear();
}
X_VOID  ObjectPlayer::Add_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,ObjectHero *pHeros,X_BOOL bDestroy)
{
	if (vector != EM_HERO_CONTAINER_BAG) return;
	if (pos >=  MAX_HERO_NUM  || pos < 0)return;
	ObjectHero*  pOldHero = m_Heroes[pos];
	if (bDestroy)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyObject(pOldHero);
	}

	m_Heroes[pos] = pHeros;
	if(pHeros)
	{
		pHeros->SetContainerType(vector);
		pHeros->SetPos(pos);
		QuJingData* pData =    DataPool::GetSingleton()->GetQuJingData();
		if (pData)
		{
			pData->HandlerNewHero(pHeros);
		}
	}
 
}
X_VOID  ObjectPlayer::Del_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,X_BOOL bDestroy)
{
	if (vector != EM_HERO_CONTAINER_BAG) return;
	if (pos >=  MAX_HERO_NUM  || pos < 0)return;
	ObjectHero*  pHero = m_Heroes[pos];
	if(bDestroy)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyObject(pHero); 
	}
	m_Heroes[pos] = X_NULL;
}
X_BOOL	ObjectPlayer::SwapHero(X_UINT nPos1, EM_HERO_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_HERO_CONTAINER_TYPE nPosType2)
{
	// do nothing
	return XTRUE;
}
ObjectHero *     ObjectPlayer::getHero(X_UINT nClientPos, EM_HERO_CONTAINER_TYPE nPosType)const
{
	if (nPosType != EM_HERO_CONTAINER_BAG) return X_NULL;
	if (nClientPos <0 ||nClientPos>GetHeroVectorSize(nPosType) )
	{
		return X_NULL;
	}
	return m_Heroes[nClientPos];
}
X_INT	ObjectPlayer::getHeroNum(EM_HERO_CONTAINER_TYPE nPosType)const
{
	if (nPosType != EM_HERO_CONTAINER_BAG) return 0;
	X_UINT size = GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	X_INT num = 0;
	for (X_UINT i=0;i<size;i++)
	{
		if(getHero(i,EM_HERO_CONTAINER_BAG))
		{
			num++;
		}

	}
	return num;
}

X_VOID  ObjectPlayer::SetHeroVectorSize(X_UINT size, EM_HERO_CONTAINER_TYPE vector)
{
	if (vector != EM_HERO_CONTAINER_BAG) return;
	m_HeroVectorSize = size > MAX_HERO_NUM ?MAX_HERO_NUM : size;
}
X_UINT  ObjectPlayer::GetHeroVectorSize(EM_HERO_CONTAINER_TYPE vector)const
{
	if (vector != EM_HERO_CONTAINER_BAG) return 0;
	return m_HeroVectorSize;
}

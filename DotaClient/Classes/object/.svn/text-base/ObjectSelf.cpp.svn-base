#include "./object/ObjectSelf.h"
#include "./object/ObjectFactory.h"
#include "./datapool/DataPool.h"
#include "./object/ItemEquip.h"
#include "./database/DataBaseSystem.h"
class ObjectSelf::Factory : public ObjectFactory
{
	public:

	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_SELF;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectSelf(guid);
	}
 
	
};
ObjectFactory * ObjectSelf::__getFactory()
{
	static Factory factory;
	return &factory;
}


ObjectSelf::ObjectSelf(X_CLIENT_GUID guid):ObjectPlayer(guid)
{
	 m_RecruitHeroVectorSize = 0;
	 m_RecruitHeroes.resize(MAX_HERO_RECRUIT_COUNT,X_NULL);
}
ObjectSelf::~ObjectSelf()
{ 
	
}
X_VOID ObjectSelf::Release()
{
	ObjectPlayer::Release();
	vector<ObjectHero*>::iterator it = m_RecruitHeroes.begin();

	for (;it != m_RecruitHeroes.end();it++)
	{
		if (*it)
		{
			DataPool::GetSingleton()->getObjectManager()->DestroyObject(*it);
		}
	}
	m_RecruitHeroes.clear();
}

X_VOID  ObjectSelf::Add_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,ObjectHero *pHeros,X_BOOL bDestroy)
{
	ObjectPlayer::Add_Hero(pos,vector,pHeros,bDestroy);

	if (vector != EM_HERO_CONTAINER_RECRUIT) return;
	if (pos >=  MAX_HERO_RECRUIT_COUNT  || pos < 0)return;
	ObjectHero*  pOldHero = m_RecruitHeroes[pos];
	if(bDestroy)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyObject(pOldHero);
	}
	m_RecruitHeroes[pos] = pHeros;
	if(pHeros)
	{
		pHeros->SetContainerType(vector);
		pHeros->SetPos(pos);
	}
}
X_VOID  ObjectSelf::Del_Hero(X_INT pos, EM_HERO_CONTAINER_TYPE vector,X_BOOL bDestroy)
{
	ObjectPlayer::Del_Hero(pos,vector,bDestroy);
	if (vector != EM_HERO_CONTAINER_RECRUIT) return;
	if (pos >=  MAX_HERO_RECRUIT_COUNT  || pos < 0)return;
	ObjectHero*  pHero = m_RecruitHeroes[pos];
	if(bDestroy)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyObject(pHero);
	}
	m_RecruitHeroes[pos] = X_NULL;
}
X_BOOL	ObjectSelf::SwapHero(X_UINT nPos1, EM_HERO_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_HERO_CONTAINER_TYPE nPosType2)
{
	if(nPosType1 <=  EM_HERO_CONTAINER_INVALID || nPosType1 >= EM_HERO_CONTAINER_NUMBER) return XFALSE;
	if(nPosType2 <=  EM_HERO_CONTAINER_INVALID || nPosType2 >= EM_HERO_CONTAINER_NUMBER) return XFALSE;

    if( nPos1 < 0||nPos1 >GetHeroVectorSize(nPosType1)) return XFALSE;
	if( nPos2 < 0||nPos2 >GetHeroVectorSize(nPosType2)) return XFALSE;
	 
	ObjectHero *pHero1 =  getHero(nPos1,nPosType1);
	ObjectHero *pHero2 =  getHero(nPos2,nPosType2);

	Del_Hero(nPos1,nPosType1);
	Del_Hero(nPos2,nPosType2);
	Add_Hero(nPos1,nPosType1,pHero2);
	Add_Hero(nPos2,nPosType2,pHero1);

	 return XTRUE;
}
 ObjectHero *     ObjectSelf::getHero(X_UINT nClientPos, EM_HERO_CONTAINER_TYPE nPosType)const
{
	if (nPosType == EM_HERO_CONTAINER_BAG)  return ObjectPlayer::getHero(nClientPos,nPosType);

	if (nPosType != EM_HERO_CONTAINER_RECRUIT) return X_NULL;
	if (nClientPos <0 ||nClientPos>GetHeroVectorSize(nPosType) )
	{
		return X_NULL;
	}
	return m_RecruitHeroes[nClientPos];
}
X_VOID  ObjectSelf::SetHeroVectorSize(X_UINT size, EM_HERO_CONTAINER_TYPE vector)
{
	ObjectPlayer::SetHeroVectorSize(size,vector);
	if (vector != EM_HERO_CONTAINER_RECRUIT) return;
	m_RecruitHeroVectorSize = size > MAX_HERO_RECRUIT_COUNT ?MAX_HERO_RECRUIT_COUNT : size;
}
X_UINT  ObjectSelf::GetHeroVectorSize(EM_HERO_CONTAINER_TYPE vector)const
{
	if (vector == EM_HERO_CONTAINER_BAG)
		return ObjectPlayer::GetHeroVectorSize(vector);

	if (vector != EM_HERO_CONTAINER_RECRUIT) return 0;
	return m_RecruitHeroVectorSize;
}
X_VOID ObjectSelf::Tick(X_UINT nTime)
{
	if (m_pData)
	{
		m_pData->SetRecruitRefreshLefttime( (m_pData->GetRecruitRefreshLefttime()- nTime));
	}
}
 
bool    ObjectSelf::HeroIsBattle(const ObjectHero *pHero)
{
	if(pHero == X_NULL) return false;
	if (m_pData == X_NULL) return false;
	 
	const vector<ObjectHero*> pHeroes = m_pData->GetFightHero();
	return   find(pHeroes.begin(),pHeroes.end(),pHero) != pHeroes.end();

}
vector<const ObjectHero*>        ObjectSelf::getHeroWithEquip(X_INT tableId)
{

	vector<const ObjectHero*>    hero;hero.clear();
	X_UINT size  = GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	const ObjectHero *   pHero = X_NULL;
	for (X_UINT i = 0;i<size;i++)
	{
		pHero = getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)continue;
		ItemEquip *pEquip = X_NULL;
		for (X_UINT j = 0 ;j< MAX_EQUIP_NUM_PER_HERO;j++)
		{
			pEquip = pHero->GetEquip(j);
			if (pEquip && pEquip->GetTableID() == tableId)
			{
				hero.push_back(pHero);
				break;
			}
		}
	}
	return hero;
}
 
bool  ObjectSelf::getRecruitHeroCostGold(X_INT & cost)
{
	cost = 0;
	if (m_pData->GetRecruitHeroCount() == MAX_HERO_RECRUIT_COUNT)
	{
		return false;
	}
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_RECRUIT);
	const stDBC_FILE_HERO_RECRUIT *pData =  (const stDBC_FILE_HERO_RECRUIT *) pDataFile->GetFieldsByIndexKey(m_pData->GetRecruitHeroCount() + 1);
	if (pData)
	{
		cost =  pData->_costValue;
		return true;
	}
	return false;

}
X_INT	ObjectSelf::getFreshHeroMoney()
{
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	const stDBC_FILE_CONFIG *pData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_Fresh_Hero_Cost);
	if (pData)
	{
		 return  pData->m_value;
	}
	return 0;
}
X_INT	ObjectSelf::getHeroNum(EM_HERO_CONTAINER_TYPE nPosType)const
{
	if (nPosType == EM_HERO_CONTAINER_BAG) return  ObjectPlayer::getHeroNum(EM_HERO_CONTAINER_BAG);
	X_UINT size = GetHeroVectorSize(EM_HERO_CONTAINER_RECRUIT);
	X_INT num = 0;
	for (X_UINT i=0;i<size;i++)
	{
		if(getHero(i,EM_HERO_CONTAINER_RECRUIT))
		{
			num++;
		}

	}
	return num;
}
 const ObjectHero *         ObjectSelf::getHeroWithTableid(X_INT tableId)
 {
	 X_UINT size  = GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	 const ObjectHero *   pHero = X_NULL;
	 for (X_UINT i = 0;i<size;i++)
	 {
		 pHero = getHero(i,EM_HERO_CONTAINER_BAG);
		 if (!pHero || pHero->GetTableID() != tableId)continue;
		return pHero;	
	 }
	 return 0;
 }
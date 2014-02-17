#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "./object/Object.h"
#include "./object/ObjectFactoryManager.h"
#include "./object/Item.h"

class Item;
class ObjectSelf;
class ObjectHero;
 

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
 

	X_VOID Initial();
	X_VOID Tick(X_UINT nTime);
	X_VOID Release();

	Object*	CreateObject(OBJECT_TYPE nObjectType,  X_CLIENT_GUID guid);
	Object* FindInstance(OBJECT_TYPE nObjectType,  X_CLIENT_GUID  guid);
	X_VOID	DestroyObject(Object* pObject);
 
	 Item*   CreateItem(X_INT  nTableId, X_CLIENT_GUID guid);
	 Item*   FindItem(X_CLIENT_GUID guid);
	 Item*   FindItem(X_UINT index);
	 X_VOID  DestroyItem(Item* item);
	 X_VOID  DestroyItem(X_UINT index);


	 ObjectHero* CreateFakeHero(X_UINT table);
	 ObjectHero* FindFakeHero(X_UINT table);
	 X_VOID	 DestroyFakeHero(ObjectHero* pObject);

	 const vector<const ObjectHero*> &  getGameHeroes();
	 const vector<const Item*> &  getGameEquips();

	 const vector<const Item*> & getGameEquipsWithType(X_INT type);

	typedef map< X_CLIENT_GUID,Object*> Object_Map;
	typedef Object_Map::iterator  Object_Map_Iter;

	typedef map< X_UINT,Item*> Item_Map;
	typedef Item_Map::iterator Item_Map_Iter;
	typedef map< X_UINT,ObjectHero*> FakeHero_Map;

	Item* CreateFakeItem(X_UINT table);
	Item* FindFakeItem(X_UINT table);
	 
	ObjectSelf* getSelf();
 
	X_VOID cleanObjectMap();

	X_VOID cleanPlayerMap();


	X_BOOL    HasGotHero(const ObjectHero *pHero);

	X_BOOL    HasGotEquip(const Item *pEquip);
	X_BOOL    getItemInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT&level );

	X_VOID    getHeroCanUseEquips( const ObjectHero *pHero ,vector<const Item*>&vec );

	X_BOOL    isHeroEquip( const ObjectHero *pHero ,const Item *pEquip );

	X_BOOL    isThisHeroEquip( const ObjectHero *pHero ,const Item *pEquip );
protected:
	ObjectFactoryManager *m_pFactoryManager;
	Object_Map m_PlayerMap;
	Object_Map m_MonsterMap;
	Object_Map m_HerosMap;
	ObjectSelf*  m_self;
	Item_Map m_ItemMap;
	Object_Map m_SkillMap;
	Object_Map m_FarmMap;
	FakeHero_Map m_FakeHero;
	Item_Map	m_FakeEquip;
	//Í¼¼ø
	vector<const ObjectHero*>    m_Heros;
	//×°±¸Í¼¼ø
	//vector<const Item*>    m_Equips;

	map<X_INT, vector<const Item*> >    m_mapEquips;

	static	 X_BOOL	 __heroSort(const ObjectHero *Hero1,const ObjectHero *pHero2);
	static	 X_BOOL	 __equipSort(const Item *Equip1,const Item *Equip2);
	static	 X_BOOL	 __equipSortByNum(const Item *Equip1,const Item *Equip2);

	static	 X_BOOL	 __equipSort1(const Item *Equip1,const Item *Equip2);

	static	 X_BOOL	 __equipSortNormal(const Item *Equip1,const Item *Equip2);
	static	 X_BOOL	 __equipSortMatral(const Item *Equip1,const Item *Equip2);
	static	 X_BOOL	 __equipSortJinjie(const Item *Equip1,const Item *Equip2);
};
 template <class T>
class  TableId_Equal
{
public:

	TableId_Equal(const T * pObj) {m_pObj = pObj;}
	bool operator () (const T *pObj)
	{
		return m_pObj->GetTableID() == pObj->GetTableID();
	}
public:
	const  T * m_pObj;
};
 
#endif
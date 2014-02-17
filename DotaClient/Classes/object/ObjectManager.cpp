#include "./object/ObjectManager.h"
#include "./object/ObjectFactory.h"
#include "./object/Item.h"
#include "./object/ObjectPlayer.h"
#include "./object/ObjectMonster.h"
#include "./object/ItemEquip.h"
#include "./object/ItemCommon.h"
#include "./object/ItemGem.h"
#include "./object/ItemTask.h"
#include "./object/ObjectSelf.h"
#include "./object/ObjectHero.h"
#include "./object/ObjectSkill.h"
#include "./object/ObjectFarm.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"


ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}
X_VOID ObjectManager::Initial()
{
	m_pFactoryManager = new ObjectFactoryManager();
	m_pFactoryManager->RegisterFactory(ObjectPlayer::__getFactory());
	m_pFactoryManager->RegisterFactory(ObjectMonster::__getFactory());
	m_pFactoryManager->RegisterFactory(ObjectSelf::__getFactory());
	m_pFactoryManager->RegisterFactory(ObjectHero::__getFactory());
	m_pFactoryManager->RegisterFactory(ObjectSkill::__getFactory());
	m_pFactoryManager->RegisterFactory(ObjectFarm::__getFactory());
	m_self = X_NULL;
	m_PlayerMap.clear();
	m_Heros.clear();
	//m_Equips.clear();
	m_mapEquips.clear();

}
X_VOID ObjectManager::Tick(X_UINT nTime)
{
	if (m_self)
	{
		m_self->Tick(nTime);
	}
}
X_VOID ObjectManager::Release()
{
	  cleanObjectMap();

	  SAFE_DELETE(m_pFactoryManager);
 
}
X_VOID ObjectManager::cleanObjectMap()
{
	FakeHero_Map::iterator in = m_FakeHero.begin();
	for (;in != m_FakeHero.end();++in)
	{
		(in->second)->Release();
		SAFE_DELETE(in->second);
	}
	m_FakeHero.clear();
	Item_Map::iterator inItem = m_FakeEquip.begin();
	for (;inItem != m_FakeEquip.end();++inItem)
	{
		(inItem->second)->Release();
		SAFE_DELETE(inItem->second);
	}
	m_FakeEquip.clear();
 
	Object_Map_Iter ib = m_PlayerMap.begin();
	for (;ib != m_PlayerMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_PlayerMap.clear();

	ib = m_MonsterMap.begin();
	for (;ib != m_MonsterMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_MonsterMap.clear();
	
	ib = m_HerosMap.begin();
	for (;ib != m_HerosMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_HerosMap.clear();

	
	ib = m_SkillMap.begin();
	for (;ib != m_SkillMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_SkillMap.clear();
	
	ib = m_FarmMap.begin();
	for (;ib != m_FarmMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_FarmMap.clear();
 
	Item_Map_Iter it = m_ItemMap.begin();
	for (;it != m_ItemMap.end();++it)
	{
		(it->second)->Release();
		SAFE_DELETE(it->second);
	}
	m_ItemMap.clear();

	DestroyObject(m_self);

}
X_VOID ObjectManager::cleanPlayerMap()
{
	Object_Map_Iter ib = m_PlayerMap.begin();
	for (;ib != m_PlayerMap.end();++ib)
	{
		m_pFactoryManager->DestroyInstance(ib->second);
	}
	m_PlayerMap.clear();
}
ObjectSelf* ObjectManager::getSelf()
{
	return m_self;
}
ObjectHero* ObjectManager::CreateFakeHero(X_UINT table)
{

	ObjectHero* pHero = FindFakeHero(table);
	if (pHero != X_NULL)
	{
		return pHero;
	}
	pHero = new ObjectHero(INVALID_INDEX);
	pHero->SetTableID(table);
	m_FakeHero.insert(FakeHero_Map::value_type(table,pHero));
	return pHero;
}
Item* ObjectManager::CreateFakeItem(X_UINT table)
{
	Item* pItem = FindFakeItem(table);
	if (pItem != X_NULL)
	{
		return pItem;
	}
	pItem = new ItemEquip(INVALID_INDEX);
	pItem->SetTableId(table);
	pItem->SetVirtual(true);
	m_FakeEquip.insert(Item_Map::value_type(table,pItem));
	return pItem;
}
 
ObjectHero* ObjectManager::FindFakeHero(X_UINT table)
{
	FakeHero_Map::iterator iFind = m_FakeHero.find(table);
	if (iFind == m_FakeHero.end())
	{
		return X_NULL;
	}
	return iFind->second;
}
Item* ObjectManager::FindFakeItem(X_UINT table)
{
	Item_Map::iterator iFind = m_FakeEquip.find(table);
	if (iFind == m_FakeEquip.end())
	{
		return X_NULL;
	}
	return iFind->second;
}

X_VOID	 ObjectManager::DestroyFakeHero(ObjectHero* pObject)
{
	if (pObject == X_NULL)
	{
		return;
	}
	FakeHero_Map::iterator iFind = m_FakeHero.find(pObject->GetTableID());
	if (iFind == m_FakeHero.end())
	{
		 m_FakeHero.erase(iFind);
	}
	pObject->Release();
	SAFE_DELETE(pObject);
}
Object*	ObjectManager::CreateObject(OBJECT_TYPE nObjectType, X_CLIENT_GUID  guid)
{
	Object* pObject = FindInstance(nObjectType,guid);
	if (pObject != X_NULL)
	{
		return pObject;
	}
	pObject =  m_pFactoryManager->CreateInstance(nObjectType,guid);
	if (pObject != X_NULL)
	{
		pObject->SetObjectType(nObjectType);
		switch (nObjectType)
		{
			case OBJECT_TYPE_INVALID:
			case OBJECT_TYPE_MAXNUM:
				break;
			case OBJECT_TYPE_PLAYER:
				{
					   m_PlayerMap.insert(Object_Map::value_type(guid,pObject));
				}
				break;
			case OBJECT_TYPE_SELF:
				{
					m_self = static_cast<ObjectSelf*>(pObject);
				}
				break;
			case OBJECT_TYPE_MONSTER:
				{
					    m_MonsterMap.insert(Object_Map::value_type(guid,pObject));
				}
				break;
			case OBJECT_TYPE_HERO:
				{
					m_HerosMap.insert(Object_Map::value_type(guid,pObject));
				}
				break;
			case OBJECT_TYPE_SKILL:
				{
					static X_UINT skillId = 0;
					m_SkillMap.insert(Object_Map::value_type(skillId,pObject));
					((ObjectSkill*)pObject)->SetSkillIndex(skillId);
					skillId++;
				}
				break;
			case OBJECT_TYPE_FARM:
				{
					static X_UINT sFarmId = 0;
					m_FarmMap.insert(Object_Map::value_type(sFarmId,pObject));
					((ObjectFarm*)pObject)->SetFarmIndex(sFarmId);
					sFarmId++;
				}
				break;
				
		}
	}
	return pObject;
}
Object* ObjectManager::FindInstance(OBJECT_TYPE nObjectType, X_CLIENT_GUID  guid)
{
	switch (nObjectType)
	{
		case OBJECT_TYPE_INVALID:
			{
				return X_NULL;
			}
			break;
		case OBJECT_TYPE_PLAYER:
			{
				Object_Map_Iter iFind = m_PlayerMap.find(guid);
				if (iFind == m_PlayerMap.end())
				{
					return X_NULL;
				}
				return iFind->second;
			}
			break;
		case OBJECT_TYPE_SELF:
			{
				return m_self;
			}
			break;
		case OBJECT_TYPE_MONSTER:
			{
				Object_Map_Iter iFind = m_MonsterMap.find(guid);
				if (iFind == m_MonsterMap.end())
				{
					return X_NULL;
				}
				return iFind->second;
			}
			break;
 
		case OBJECT_TYPE_HERO:
			{
				Object_Map_Iter iFind = m_HerosMap.find(guid);
				if (iFind == m_HerosMap.end())
				{
					return X_NULL;
				}
				return iFind->second;
			}
			break;

		case OBJECT_TYPE_SKILL:
			{
				Object_Map_Iter iFind = m_SkillMap.find(guid);
				if (iFind == m_SkillMap.end())
				{
					return X_NULL;
				}
				return iFind->second;
			}
			break;
		case OBJECT_TYPE_FARM:
			{
				Object_Map_Iter iFind = m_FarmMap.find(guid);
				if (iFind == m_FarmMap.end())
				{
					return X_NULL;
				}
				return iFind->second;
			}
			break;
		case OBJECT_TYPE_MAXNUM:
			{
				return X_NULL;
			}
			break;
	}
	return X_NULL;
}
X_VOID	ObjectManager::DestroyObject( Object* pObject)
{
	if(pObject == X_NULL || m_pFactoryManager == X_NULL) return;

	switch (pObject->GetType())
	{
	case OBJECT_TYPE_PLAYER:
		{
			Object_Map_Iter iFind = m_PlayerMap.find(pObject->GetGuid());
			if (iFind != m_PlayerMap.end())
			{
				 m_PlayerMap.erase(iFind);
			}
		}
		break;
	case OBJECT_TYPE_SELF:
		{
			m_self = X_NULL;
		}
		break;
	case OBJECT_TYPE_MONSTER:
		{
			Object_Map_Iter iFind = m_MonsterMap.find(pObject->GetGuid());
			if (iFind != m_MonsterMap.end())
			{
				m_MonsterMap.erase(iFind);
			}
		}
		break;

	case OBJECT_TYPE_HERO:
		{
			Object_Map_Iter iFind = m_HerosMap.find(pObject->GetGuid());
			if (iFind != m_HerosMap.end())
			{
				m_HerosMap.erase(iFind);
			}
		}
		break;

	case OBJECT_TYPE_SKILL:
		{
			
			Object_Map_Iter iFind = m_SkillMap.find( ((ObjectSkill*)pObject)->GetSkillIndex());
			if (iFind != m_SkillMap.end())
			{
				m_SkillMap.erase(iFind);
			}
		}
		break;
	case OBJECT_TYPE_FARM:
		{
			Object_Map_Iter iFind = m_FarmMap.find( ((ObjectFarm*)pObject)->GetFarmIndex());
			if (iFind != m_FarmMap.end())
			{
				m_FarmMap.erase(iFind);
			}
		}
		break;
 
	m_pFactoryManager->DestroyInstance(pObject);
 }
}
Item*   ObjectManager:: CreateItem(X_INT  nTableId, X_CLIENT_GUID guid)
{
	Item *pItem = X_NULL;
	static X_UINT index = 0;
	EM_ITEM_CLASS item_class = EM_ITEM_CLASS (GETITEMCLASS(nTableId));
	switch (item_class)
	{
	case EM_ITEM_CLASS_INVALID:
	case EM_ITEM_CLASS_NUMBER:
		{
			return X_NULL;
		}
	case EM_ITEM_CLASS_EQUIP:
		{
			pItem = new ItemEquip(guid);
		}
		break;
	case EM_ITEM_CLASS_COMMON:
		{
			pItem = new ItemCommon(guid);
		}
		break;
	case EM_ITEM_CLASS_GEM:
		{
			pItem = new ItemGem(guid);
		}
		break;
	case EM_ITEM_CLASS_QUESTITEM:
		{
			pItem = new ItemTask(guid);
		}
		break;
	}
	if (pItem)
	{
		pItem->SetItemIndex(index);
		pItem->SetTableId(nTableId);
		m_ItemMap.insert(Item_Map::value_type(index,pItem));
		index++;
	}
	

	return pItem;
}
X_VOID ObjectManager::DestroyItem( Item* item)
{
	if (item == X_NULL)
	{
		return;
	}
	m_ItemMap.erase(item->GetItemIndex());
	item->Release();
	SAFE_DELETE(item);
}
Item*  ObjectManager::FindItem(X_CLIENT_GUID guid)
{
	Item_Map_Iter it = m_ItemMap.begin();
	Item *pItem = X_NULL;
	for (;it != m_ItemMap.end();++it)
	{
		pItem = it->second;
		 if ( pItem == X_NULL) continue;
		  
		 if (pItem->GetGuid() ==guid )
		 {
			 return pItem;
		 }
	}
	return X_NULL;
}
 Item*  ObjectManager::FindItem(X_UINT index)
 {
	 Item_Map_Iter it = m_ItemMap.find(index);
	 if (it != m_ItemMap.end())
	 {
		return it->second;
	 }
	 return X_NULL;
 }
 X_VOID  ObjectManager::DestroyItem(X_UINT index)
 {
	 Item* pItem = FindItem(index);
	 DestroyItem(pItem);
 }
X_BOOL    ObjectManager::HasGotHero(const ObjectHero *pHero)
{
	if (pHero == X_NULL) return XFALSE;
	 ObjectHero * pPlayerHero = X_NULL;

	 X_INT size = m_self->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	 for (X_INT i = 0; i< size ;i++)
	 {
		 pPlayerHero = m_self->getHero(i,EM_HERO_CONTAINER_BAG);
		 if (pPlayerHero == X_NULL) continue;
		 if (pHero->GetTableID() == pPlayerHero->GetTableID())
			 return XTRUE;
	 }
	 return XFALSE;
}
X_BOOL    ObjectManager::HasGotEquip(const Item *pEquip)
{
	if (pEquip == X_NULL) return XFALSE;
	Item * pPlayerEquip = X_NULL;
	 SelfBagData *pBag= DataPool::GetSingleton()->getBagData();
	 X_INT size =  pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);
	for (X_INT i = 0; i< size ;i++)
	{
		pPlayerEquip = pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP);
		if (pPlayerEquip == X_NULL) continue;
		if (pPlayerEquip->GetTableID() == pEquip->GetTableID())
			return XTRUE;
	}
	return XFALSE;
}
X_BOOL    ObjectManager::isHeroEquip( const ObjectHero *pHero ,const Item *pEquip )
{
	if (pEquip == X_NULL) return XFALSE;

	X_INT size = m_self->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	const ObjectHero * potherHero = X_NULL;
	ItemEquip*	 pHeroEquip =X_NULL;
	for (X_INT i = 0; i< size ;i++)
	{
		potherHero = m_self->getHero(i,EM_HERO_CONTAINER_BAG);
		if(!potherHero || potherHero == pHero)continue;
		for (X_INT j = 0;j<MAX_EQUIP_NUM_PER_HERO;j++)
		{
			pHeroEquip = potherHero->GetEquip(j);
			if (pHeroEquip==pEquip)
			{
				return XTRUE;
			}
		}
	}
	return XFALSE;
}
X_BOOL    ObjectManager::isThisHeroEquip( const ObjectHero *pHero ,const Item *pEquip )
{
	if (pHero == NULL ||pEquip == X_NULL) return XFALSE;
		ItemEquip*	 pHeroEquip =X_NULL;
		for (X_INT j = 0;j<MAX_EQUIP_NUM_PER_HERO;j++)
		{
			pHeroEquip = pHero->GetEquip(j);
			if (pHeroEquip == pEquip)
			{
				return XTRUE;
			}
		}
	return XFALSE;
}
const vector<const ObjectHero*> &  ObjectManager::getGameHeroes()
{
	m_Heros.clear();

	vector<const ObjectHero*> vc;vc.clear();
	X_INT size = m_self->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	const ObjectHero * pHero = X_NULL;
	for (X_INT i = 0; i< size ;i++)
	{
		pHero = m_self->getHero(i,EM_HERO_CONTAINER_BAG);
		if (pHero)
		{
			vc.push_back(pHero);
		}
	}

	FakeHero_Map::iterator ib = m_FakeHero.begin();
	vector<const ObjectHero*>::iterator ifind;
	for ( ; ib != m_FakeHero.end(); ++ib)
	{
		pHero = ib->second ;
		if (pHero == X_NULL) continue;

		 
		ifind =  find_if(vc.begin(),vc.end(),TableId_Equal<ObjectHero>(pHero));
		if(ifind == vc.end())
		{
			m_Heros.push_back(pHero);
		}
		/*if(HasGotHero(pHero) == XFALSE)
		{
			m_Heros.push_back(pHero);
		}*/
	}

	sort(m_Heros.begin(),m_Heros.end(),__heroSort);
	sort(vc.begin(),vc.end(),__heroSort);
	size = vc.size();
	for (X_INT i = size -1; i >= 0 ;i--)
	{
		pHero = vc[i];
		if (pHero)
		{
			 m_Heros.insert(m_Heros.begin(),pHero);
		}
	}
	return m_Heros;
}
 X_BOOL	  ObjectManager::__heroSort(const ObjectHero *pHero1,const ObjectHero *pHero2)
{
		return pHero1->GetTableID() < pHero2->GetTableID();

}
 const vector<const Item*> &  ObjectManager::getGameEquipsWithType(X_INT type)
 {

	 m_mapEquips[type].clear();
	 SelfBagData *pBag= DataPool::GetSingleton()->getBagData();
	 X_INT size =  pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);
	 ItemEquip *  pEquip =X_NULL;
	 vector<const Item*>::iterator ifind;
	 for (X_INT i = 0; i< size ;i++)
	 {
		 pEquip = (ItemEquip *)(pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP));
		 if (pEquip == X_NULL || pEquip->GetSubClass() != type) continue;

		 ifind =  find_if( m_mapEquips[type].begin(), m_mapEquips[type].end(),TableId_Equal<Item>(pEquip));
		 if(ifind == m_mapEquips[type].end())
		 {
			  m_mapEquips[type].push_back(pEquip);
			 ((ItemEquip*)(pEquip))->SetCounterNum(1);

		 } else
		 {
			 ((ItemEquip*)(*ifind))->SetCounterNum(((ItemEquip*)(*ifind))->GetCounterNum()+1);

		 }
	 }

	 Item_Map::iterator ib = m_FakeEquip.begin();
	 for ( ; ib != m_FakeEquip.end(); ++ib)
	 {
		 pEquip = (ItemEquip *)(ib->second );
		 if (pEquip == X_NULL||pEquip->GetSubClass() != type) continue;

		 ifind =  find_if(m_mapEquips[type].begin(),m_mapEquips[type].end(),TableId_Equal<Item>(pEquip));
		 if(ifind == m_mapEquips[type].end())
		 {
			 m_mapEquips[type].push_back(pEquip);
		 }
	 }
		switch (type)
		{
			case EM_NORMAL:

				sort(m_mapEquips[type].begin() ,m_mapEquips[type].end(),__equipSortNormal);
				break;
			case EM_MATERIAL:

				sort(m_mapEquips[type].begin() ,m_mapEquips[type].end(),__equipSortMatral);
				break;
			case EM_FINALE:

				sort(m_mapEquips[type].begin() ,m_mapEquips[type].end(),__equipSortJinjie);
				break;
		}


	 return m_mapEquips[type];

 }
/*const vector<const Item*> &  ObjectManager::getGameEquips()
{
	m_Equips.clear();

	SelfBagData *pBag= DataPool::GetSingleton()->getBagData();
	X_INT size =  pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);
	Item *  pEquip =X_NULL;
	vector<const Item*>::iterator ifind;
	for (X_INT i = 0; i< size ;i++)
	{
		pEquip = pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP);
		if (pEquip == X_NULL) continue;
		ifind =  find_if(m_Equips.begin(),m_Equips.end(),TableId_Equal<Item>(pEquip));
		if(ifind == m_Equips.end())
		{
			m_Equips.push_back(pEquip);
			((ItemEquip*)(pEquip))->SetCounterNum(1);

		} else
		{
			((ItemEquip*)(*ifind))->SetCounterNum(((ItemEquip*)(*ifind))->GetCounterNum()+1);

		}
		
	}
	sort(m_Equips.begin() ,m_Equips.end(),__equipSortByNum);
	size = m_Equips.size();
	Item_Map::iterator ib = m_FakeEquip.begin();
 
	for ( ; ib != m_FakeEquip.end(); ++ib)
	{
		pEquip = ib->second ;
		if (pEquip == X_NULL) continue;

		ifind =  find_if(m_Equips.begin(),m_Equips.end(),TableId_Equal<Item>(pEquip));
		if(ifind == m_Equips.end())
		{
			m_Equips.push_back(pEquip);
		}
	}
	sort(m_Equips.begin()+ size ,m_Equips.end(),__equipSort);
	return m_Equips;
}
*/
 X_BOOL	 ObjectManager::__equipSort(const Item *Equip1,const Item *Equip2)
 {
	 return Equip1->GetTableID() < Equip2->GetTableID();
 }
X_BOOL	ObjectManager::__equipSort1(const Item *Equip1,const Item *Equip2)
{

	X_INT b1 =  ((ItemEquip *)(Equip1))->m_pTableData->_weight;
	X_INT b2 =  ((ItemEquip *)(Equip2))->m_pTableData->_weight;
 
	return  b1 < b2;
}
X_BOOL	 ObjectManager::__equipSortNormal(const Item *Equip1,const Item *Equip2)
{

	EM_ITEM_CONTAINER_TYPE  type1  = Equip1->GetItemVectorType() ;
	EM_ITEM_CONTAINER_TYPE  type2  = Equip2->GetItemVectorType() ;

	if (type1 == type2)
	{
			return ((ItemEquip*)Equip1)->m_pTableData->_weight  > ((ItemEquip*)Equip2)->m_pTableData->_weight;
	}else
	{
		 return type1 == EM_ITEM_CONTAINER_EQUIP;
		  

	}
	 return  X_TRUE;    
}
 X_BOOL	 ObjectManager::__equipSortMatral(const Item *Equip1,const Item *Equip2)
 {
	 EM_ITEM_CONTAINER_TYPE  type1  = Equip1->GetItemVectorType() ;
	 EM_ITEM_CONTAINER_TYPE  type2  = Equip2->GetItemVectorType() ;

	 if (type1 == type2)
	 {
		 return  Equip1->GetLevel()  <  Equip2->GetLevel();

	 }else
	 { 
		 return type1 == EM_ITEM_CONTAINER_EQUIP;
	 }
	 return  X_TRUE;     //按等级“-4”“-3”“-2”由前到后进行显示。

 }
 X_BOOL	 ObjectManager::__equipSortJinjie(const Item *Equip1,const Item *Equip2)
 {
	 EM_ITEM_CONTAINER_TYPE  type1  = Equip1->GetItemVectorType() ;
	 EM_ITEM_CONTAINER_TYPE  type2  = Equip2->GetItemVectorType() ;

	 if (type1 == type2)
	 {
		 return  Equip1->GetLevel()  <  Equip2->GetLevel();

	 }else
	 { 
		 return type1 == EM_ITEM_CONTAINER_EQUIP;
	 }
	 return  X_TRUE;           //按等级“2”“3”“4”“5”由前到后进行显示
	  
 }
 X_BOOL	 ObjectManager::__equipSortByNum(const Item *Equip1,const Item *Equip2)
 {
	  return  ((ItemEquip*)Equip1)->GetCounterNum()>((ItemEquip*)Equip2)->GetCounterNum();
 }
 
 X_BOOL    ObjectManager::getItemInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT &level )
 {
	 level = 0;
	 EM_ITEM_CLASS item_class = EM_ITEM_CLASS (GETITEMCLASS(nTableId));
	 switch (item_class)
	 {
	 case EM_ITEM_CLASS_INVALID:
	 case EM_ITEM_CLASS_NUMBER:
		 {
			 return XFALSE;
		 }
	 case EM_ITEM_CLASS_EQUIP:
		 {
			  return Item::getEquipInfoById(nTableId,name,color,icon,level);
		 }
		 break;
	 case EM_ITEM_CLASS_COMMON:
		 {
			   return Item::getCommonItemInfoById(nTableId,name,color,icon,level);
		 }
		 break;
	 case EM_ITEM_CLASS_GEM:
		 {
			  return Item::getGemItemInfoById(nTableId,name,color,icon,level);
		 }
		 break;
	 case EM_ITEM_CLASS_QUESTITEM:
		 {
			   return Item::getQuestItemInfoById(nTableId,name,color,icon,level);
		 }
		 break;
	 }
	 return XFALSE;
 }

 X_VOID    ObjectManager::getHeroCanUseEquips( const ObjectHero *pHero ,vector<const Item*>&vec )
 {
	 vec.clear();
	 if (pHero == X_NULL)return;
	
	const ItemEquip*	pEquip = X_NULL; 
	SelfBagData* pBag = DataPool::GetSingleton()->getBagData();
	X_UINT size  = pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);
	for (X_UINT i = 0; i < size;i++)
	{
		pEquip = (ItemEquip*)(pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP));
		if (!pEquip || pEquip->isMaterial() )continue;
		if (pEquip->isEquiped())
		{
			continue;
		}
		if ( pEquip->isBindEquip()&& !pEquip->isHeroBindEquip(pHero))
		{
			 continue;
		}
		//if(isHeroEquip(pHero,pEquip))continue;
		vec.push_back(pEquip);
	}

	sort(vec.begin(),vec.end(),__equipSort1);

	vector<const ItemEquip*> tmpvec;
	for (X_INT i = 0;i< MAX_EQUIP_NUM_PER_HERO;i++)
	{
		pEquip =  pHero->GetEquip(i);
		if (pEquip)
		{
			tmpvec.push_back(pEquip);
		}
	}
	sort(tmpvec.begin(),tmpvec.end(),__equipSort1);
	for (X_INT i = tmpvec.size() -1;i >= 0 ;i--)
	{
		vec.push_back( tmpvec[i]);
	}
 }
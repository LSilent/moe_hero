#include "./datapool/EquipOperator.h"


vector<Item* > EquipMaker::m_Items ;

 X_VOID EquipMaker::getMaterial(const Item* pSourceItem,vector<stMaterialItem>& MaterialItems,X_INT &woodnum)
 {
	 MaterialItems.clear();woodnum = 0;
	 X_INT tableId = pSourceItem->GetTableID();
	X_INT index =  __FindEquipWithId(tableId);
	if (index == -1)
	{
		return;
	}
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);
	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByIndexKey(index);
	if (!m_pTableData)
	{
		return;
	}
	woodnum = m_pTableData->wood;
	if (woodnum < 0)
	{
		woodnum = 0;
	}
	Item *pItem = X_NULL;
	const ItemMaterial *pItemMaterial = X_NULL;
	SelfBagData* pbag = DataPool::GetSingleton()->getBagData(); 

	for (X_INT i = 0 ;i < MAX_MATERIAL_NUM;i++ )
	{
		pItemMaterial = &m_pTableData->items[i];
		if (pItemMaterial->id ==-1)continue;
		pItem = _FindItemByTableID(pItemMaterial->id);
		if (!pItem)
		{
			pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(pItemMaterial->id,INVALID_INDEX);
			if (pItem)
			{
				pItem->SetVirtual(true);
				m_Items.push_back(pItem);
			}
		}
		if (pItem)
		{
			stMaterialItem ma;
			ma.m_pItem = pItem;
			ma.m_num = pItemMaterial->num;

			X_INT selfBagItemNum = pbag->getItemNumByTableId(pItemMaterial->id);
			ma.m_nums = selfBagItemNum;
				for (X_UINT i = 0; i<MaterialItems.size();i++)
				{
					if (MaterialItems[i].m_pItem->GetTableID() == pItemMaterial->id)
					{
						selfBagItemNum -=  MaterialItems[i].m_num;
					}
				}
				if( selfBagItemNum >= ma.m_num) ma.bEnough = true;
				 MaterialItems.push_back(ma);
			}
		} 
 }
X_VOID EquipMaker::getProduct(const Item* pSourceItem,vector<Item*>& Products)
{
	Products.clear();

	X_INT tableId = pSourceItem->GetTableID();
	X_INT index =  __FindProductEquipWithId(tableId);
	if (index == -1)
	{
		return;
	}
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIPGUIDE);
	const stDBC_FILE_EQUIPGUIDE	* m_pTableData = (const stDBC_FILE_EQUIPGUIDE*)pDataFile->GetFieldsByIndexKey(index);
	if (!m_pTableData)
	{
		return;
	}
	X_INT tableid =-1;
	Item * pItem = X_NULL;
	for (X_INT i = 0;i< MAX_EQUIP_FIND;i++)
	{
		tableid = m_pTableData->equip[i];
		if (tableid == -1)continue;
		pItem = _FindItemByTableID(tableid);
		if (!pItem)
		{
			pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(tableid,INVALID_INDEX);
			if (pItem)
			{
				pItem->SetVirtual(true);
				m_Items.push_back(pItem);
			}
		}
		if (pItem)
		{
			Products.push_back(pItem);
		}
	}
}
Item *  EquipMaker::_FindItemByTableID(X_INT tableId)
{
	 vector< Item* >::iterator ifind;
	 ifind =  find_if(m_Items.begin(),m_Items.end(),TableIdEqual(tableId));
	 if (ifind != m_Items.end())
	 {
		  return  *ifind;
	 }
	return X_NULL;
}
X_VOID  EquipMaker::Release()
 {
	 X_UINT size = m_Items.size();
	 for (X_UINT i = 0; i<size ;i++)
	 {
		 DataPool::GetSingleton()->getObjectManager()->DestroyItem( m_Items[i]);
	 }
	 m_Items.clear();
 }
X_INT EquipMaker::__FindProductEquipWithId(X_INT tableId)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIPGUIDE);

	const stDBC_FILE_EQUIPGUIDE	* m_pTableData = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableData = (const stDBC_FILE_EQUIPGUIDE*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData == X_NULL) continue;
		if (m_pTableData->id == tableId)
		{
			return m_pTableData->id;
		}
	}
	return -1;

}
X_INT EquipMaker::__FindEquipWithId(X_INT tableId)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);

	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData == X_NULL) continue;
		 if (m_pTableData->itemID == tableId)
		 {
			 return m_pTableData->id;
		 }
	}
	return -1;
}
const stDBC_FILE_EQUIP_MANUFACTURE	* EquipMaker::getProductTableData(X_INT tableId)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);

	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData == X_NULL) continue;
		if (m_pTableData->itemID == tableId)
		{
			return m_pTableData;
		}
	}
	return 0;
}
X_VOID EquipMaker::getIronsmithEquip( vector<ItemEquip*>& equips)
{
	equips.clear();

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	SelfBagData *pBag = DataPool::GetSingleton()->getBagData();

	X_UINT size = pBag->GetBagSize(EM_ITEM_CONTAINER_EQUIP);
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);
	ItemEquip* pItem = X_NULL;
	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = X_NULL;
	for (X_UINT i =0;i< size;i++)
	{
		pItem = (ItemEquip*)(pBag->getItem(i,EM_ITEM_CONTAINER_EQUIP));
		if (!pItem ||!(pItem->CanLevelUp()))continue;
		X_INT tableid = pItem->GetTableID();
		X_INT id = 	__FindEquipWithMaterialId(tableid);
		if (id !=-1)
		{
			m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByIndexKey(id);
			if (m_pTableData == X_NULL ||m_pTableData->type == 0) continue;

			bool bFind = false;
			for (X_UINT j = 0;j< equips.size();j++)
			{
				if(equips[j]->GetTableID() == tableid)
				{
					bFind = true;
					break;
				}
			}
			if (!bFind)
			{
				equips.push_back(pItem);
			}
		}
	}
/*	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);
	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = X_NULL;
	pItem = X_NULL;
	for (X_UINT k = 0;k< pDataFile->GetRecordsNum();k++)
	{
		m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByLineNum(k);
		if (m_pTableData == X_NULL ||m_pTableData->type == 0) continue;
		 
		for (X_INT i =0;i< MAX_MATERIAL_NUM;i++)
		{
			if (m_pTableData->items[i].id <= 0) continue;
			bool bFind = false;
			for (X_UINT j = 0;j< equips.size();j++)
			{
				if(equips[j]->GetTableID() == m_pTableData->items[i].id)
				{
					bFind = true;
					break;
				}
			}
			if (bFind)continue;
			pItem =(ItemEquip*) (_FindItemByTableID(m_pTableData->items[i].id));
			if (!pItem)
			{
				pItem = (ItemEquip*)(DataPool::GetSingleton()->getObjectManager()->CreateItem(m_pTableData->items[i].id,INVALID_INDEX));
				if (pItem)
				{
					if(pItem->CanLevelUp())
					{
						pItem->SetVirtual(true);
						m_Items.push_back(pItem);
					}
				}
			}
			equips.push_back( pItem);
		}
	}*/
 

}
X_INT EquipMaker::__FindEquipWithMaterialId(X_INT tableId)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);

	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableData = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData == X_NULL) continue;
		 
		for (X_INT i =0;i<MAX_MATERIAL_NUM;i++)
		{
			if( m_pTableData->items[i].id == tableId)
				return m_pTableData->id;
		}
	}
	return -1;
}
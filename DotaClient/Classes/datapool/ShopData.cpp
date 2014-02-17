#include "./datapool/ShopData.h"
#include "./object/Item.h"
#include "./datapool/DataPool.h"
#include "./DataBase/DataBaseSystem.h"

ShopData::ShopData()
{

	Initial();
}

ShopData::~ShopData()
{


}

X_VOID ShopData::Initial()
{
	 map< EM_SHOP_IDTYPE, vector<Item *> > ::iterator ib = m_pItems.begin();
	for (;ib != m_pItems.end();ib++)
	{

		ib->second.clear();
	}

	m_pItems.clear();

	vector< Item *> tempVec;
	for(int type = EM_SHOP_ID_NORMAL ;type < EM_SHOP_NUM;type++)
	{
		tempVec.clear();
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SHOP);
		const stDBC_FILE_SHOP* pDefine = (const stDBC_FILE_SHOP*)pDataFile->GetFieldsByIndexKey( type);
		if (pDefine)
		{
			Item *pItem = NULL;
			const stSHOP_ITEM * item = X_NULL;

			for (X_INT i = 0; i< MAX_SHOP_ITEM;i++)
			{
				item = &(pDefine->items[i]);
				if (item->id <=-1)
				{
					continue;
				}
				pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(item->id,INVALID_INDEX);
				if (!pItem)continue;
				pItem->SetPrice(item->price);
                
				pItem->SetFloatPrice(item->floatPrice);
				pItem->SetShopFloatPriceTime(pDefine->floatPricetimeBegin,pDefine->floatPricetimeBeginEnd);
				tempVec.push_back(pItem);

			}
			m_pItems[ (EM_SHOP_IDTYPE)type]= tempVec;
		} 
	}
	
}
X_BOOL		ShopData::AddItem(EM_SHOP_IDTYPE type ,X_UINT nClientPos,Item *pItem)
{ 
	map< EM_SHOP_IDTYPE, vector<Item *> > ::iterator ib = m_pItems.find(type);
	if (ib == m_pItems.end())
	{
		return false;
	}

	vector<Item *> pItemsVec =  m_pItems[type];
	X_UINT size = pItemsVec.size();
	if (nClientPos < 0 || nClientPos >= size)
	{
		return XFALSE;
	}
	Item *pOldItem = X_NULL;
	pOldItem = pItemsVec[nClientPos];
	if (pOldItem)
		DataPool::GetSingleton()->getObjectManager()->DestroyItem(pOldItem);
	pItemsVec[nClientPos] = pItem;
	return XTRUE;
}
X_VOID		ShopData::Clear( )
{
	EM_SHOP_IDTYPE i ;
	for(int type = EM_SHOP_ID_NORMAL ;type < EM_SHOP_NUM;type++)
	{
		i = EM_SHOP_IDTYPE(type);
		 vector<Item *> pItemsVec =  m_pItems[i];
		X_UINT size =pItemsVec.size();
 
		Item *pItem = X_NULL;
		for (X_UINT i = 0 ;i < size ;i++)
		{
			pItem = pItemsVec[i];
			if (!pItem)continue;
			DataPool::GetSingleton()->getObjectManager()->DestroyItem(pItem);
			pItemsVec[i] = X_NULL;
		}
	}


	 
}
Item *     ShopData:: getItem(EM_SHOP_IDTYPE type ,X_UINT nClientPos)
{
	 map< EM_SHOP_IDTYPE, vector<Item *> > ::iterator ib = m_pItems.find(type);
	 if (ib == m_pItems.end())
	 {
		 return 0;
	 }
 
 
	X_UINT size = m_pItems[type].size();
	if (nClientPos < 0 || nClientPos >= size)
	{
		return X_NULL;
	}
	return m_pItems[type].at(nClientPos);
}
X_INT       ShopData::GetShopSize(EM_SHOP_IDTYPE type )
{
	map< EM_SHOP_IDTYPE, vector<Item *> > ::iterator ib = m_pItems.find(type);
	if (ib == m_pItems.end())
	{
		return 0;
	}
	return m_pItems[type].size();
}
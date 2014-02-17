#include "./datapool/HeroAltarData.h"
#include "./object/Item.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"

X_INT HeroAltar::getID()const
{
	return m_pTableData->id;
}
X_INT HeroAltar::getOpenLevel()const
{
	return m_pTableData->openLevel;
}
X_INT HeroAltar::getLimit()const
{
	return m_pTableData->effectsill;
}
/*X_INT HeroAltar::getCostgold()const
{
	return m_pTableData->costgold;
}*/
X_INT HeroAltar::getCostItem()const
{
	return m_pTableData->costItem;
}
X_INT HeroAltar::getCostItemNum()const
{
	return m_pTableData->constItemNum;
}
string HeroAltar::getCostItemName()const
{
	string name,color,icon;X_INT level;
	ObjectManager * pManger = DataPool::GetSingleton()->getObjectManager();
	pManger->getItemInfoById(m_pTableData->costItem,name,color,icon,level);
	return name;
}
//可能的掉落物品
vector<string> HeroAltar::getAwardItems(bool Apparitions)
{
	vector<string> items;
	items.clear();
	vector<X_INT> itemIds;

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILR_SACRIFICE_AWARD);
	const stDBC_FILR_SACRIFICE_AWARD	* pTableData = X_NULL;

	X_INT tableID = m_pTableData->award0;
	if (Apparitions)
	{
		tableID = m_pTableData->award1;
	}
		
	pTableData = (const stDBC_FILR_SACRIFICE_AWARD*)pDataFile->GetFieldsByLineNum(tableID);
	if (pTableData == X_NULL) return items;
 
	string name,color,icon;X_INT level;
	ObjectManager * pManger = DataPool::GetSingleton()->getObjectManager();

	const SACRIFICE_ITEM* item;
	for (X_INT i = 0;i<MAX_AWARD_SACRIFICE_ITEM;i++)
	{
		itemIds.clear();
		item = &pTableData->awards[i];
		if (!item)continue;
		if (item->items == "-1")continue;
		UtilTools::ConvertStringToIntVector(item->items,itemIds,"|");
		X_UINT size = itemIds.size();

		for (X_UINT j = 0 ; j < size ;j++)
		{
			if(pManger->getItemInfoById(itemIds[j],name,color,icon,level))
			{
				items.push_back(name);
			} 
		}
	}
	return items;
}
X_VOID HeroAltarData::Initial()
{
	m_HeroAltars.clear();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILR_SACRIFICE);

	const stDBC_FILR_SACRIFICE	* pTableData = X_NULL;
	HeroAltar * pHeroAltar = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		pTableData = (const stDBC_FILR_SACRIFICE*)pDataFile->GetFieldsByLineNum(i);
		if (pTableData == X_NULL) continue;
		 pHeroAltar = new HeroAltar();
		 pHeroAltar->m_pTableData = pTableData;
		 m_HeroAltars.push_back(pHeroAltar);
	}
}
X_VOID HeroAltarData::Release()
{
	X_UINT size = m_HeroAltars.size();

	for (X_UINT i = 0;i<size;i++)
	{
		SAFE_DELETE(m_HeroAltars[i]);
	}
	m_HeroAltars.clear();
}
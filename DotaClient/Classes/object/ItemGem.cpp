#include "./object/ItemGem.h"
 
ItemGem::ItemGem(X_CLIENT_GUID guid):Item(guid)
{
 
}
ItemGem::~ItemGem()
{


}
X_VOID	ItemGem::SetItemData(const ItemData*	pData)
{
	Item::SetItemData(pData);

	if (pData == X_NULL)
	{
		return;
	}
	SetCount(pData->GetGemData()->m_nCount);
}
X_VOID ItemGem::SetTableId(X_INT nTableID)
{
	Item::SetTableId(nTableID);
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GEM_ITEM);
	if (pDataFile)
		m_pTableData = (const stDBC_FILE_GEM_ITEM *)pDataFile->GetFieldsByIndexKey(m_TableId);
	if (m_pTableData)
	{
		SetRule(m_pTableData->_rule);
		SetPrice(m_pTableData->_buyPrice);
	}
}
X_CHAR * ItemGem::GetIcon()const
{
	if (m_pTableData)
		return m_pTableData->_icon;
	return "";
}
X_INT ItemGem::GetMaxCount()const
{
	if (m_pTableData)
		return m_pTableData->_layerNum;
	return -1;
}
X_CHAR * ItemGem::GetName()const
{
	if (m_pTableData)
		return m_pTableData->_name;
	return "";
}
X_CHAR * ItemGem::GetColor()const
{
	if (m_pTableData)
		return m_pTableData->_color;
	return "";
}
X_CHAR * ItemGem::GetType()const
{
	if (m_pTableData)
		return m_pTableData->_typeTip;
	return "";
}
X_CHAR * ItemGem::GetInfo()const
{
	if (m_pTableData)
		return m_pTableData->_infoTip;
	return "";
}
X_INT ItemGem::GetSalePrice()const
{
	if (m_pTableData)
		return m_pTableData->_salePrice;
	return 0;
}
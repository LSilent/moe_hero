#include "./object/ItemCommon.h"
 
ItemCommon::ItemCommon(X_CLIENT_GUID guid):Item(guid)
{
 
}
ItemCommon::~ItemCommon()
{


}
X_VOID	ItemCommon::SetItemData(const ItemData*	pData)
{
	 Item::SetItemData(pData);

	 if (pData == X_NULL)
	 {
		 return;
	 }
	SetCount(pData->GetCommonItemData()->m_nCount);
}
X_VOID ItemCommon::SetTableId(X_INT nTableID)
{
	Item::SetTableId(nTableID);
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_COMMON_ITEM);
	if (pDataFile)
		m_pTableData = (const stDBC_FILE_COMMON_ITEM*)pDataFile->GetFieldsByIndexKey(m_TableId);
	if (m_pTableData)
	{
		SetRule(m_pTableData->_rule);
		SetPrice(m_pTableData->_buyPrice);
	}
	
}
X_CHAR * ItemCommon::GetIcon()const
{
	if (m_pTableData)
		return m_pTableData->_icon;
	return "";
}
X_INT ItemCommon::GetMaxCount()const
{
	if (m_pTableData)
		return m_pTableData->_layerNum;
	return -1;
}
X_CHAR * ItemCommon::GetName()const
{
	if (m_pTableData)
		return m_pTableData->_name;
	return "";
}
 X_CHAR * ItemCommon::GetColor()const
{
	if (m_pTableData)
		return m_pTableData->_color;
	return "";
}
X_CHAR * ItemCommon::GetType()const
 {
	 if (m_pTableData)
		 return m_pTableData->_typeTip;
	 return "";
 }
X_CHAR * ItemCommon::GetInfo()const
{
	if (m_pTableData)
		return m_pTableData->_infoTip;
	return "";
}
X_INT ItemCommon::GetSalePrice()const
{
	if (m_pTableData)
		return m_pTableData->_salePrice;
	return 0;
}
X_INT ItemCommon::getSkillRate()
{
	return m_pTableData->_skillLevelUpRate == -1 ? 0 : m_pTableData->_skillLevelUpRate;
}
X_INT ItemCommon::getSkillDoubleGroup()
{
	return m_pTableData->_skillDoubleGroup;
}
X_VOID  ItemCommon::getDropInfo(X_INT Itemid,DROP_TYPE &type,X_INT &id)
{
	type = DROP_TYPE_INVALID;
	id = -1;
	switch (Itemid)
	{
	case 12030000:
		{
			type = DROP_TYPE_COPYSCNE;
			id = 100107;
		}
		break;
	case 12031000:
		{
			type = DROP_TYPE_COPYSCNE;
			id = 100610;
		}
		break;
	case 12031001:
		{
			type = DROP_TYPE_COPYSCNE;
			id = 101007;
		}
		break;
	case 12031002:
		{
			type = DROP_TYPE_COPYSCNE;
			id = 101807;
		}
		break;
	}
}
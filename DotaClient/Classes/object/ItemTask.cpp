#include "./object/ItemTask.h"
 
ItemTask::ItemTask(X_CLIENT_GUID guid):Item(guid)
{
	 
}
ItemTask::~ItemTask()
{


}
X_VOID	ItemTask::SetItemData(const ItemData*	pData)
{
	Item::SetItemData(pData);

	if (pData == X_NULL)
	{
		return;
	}
   SetCount(pData->GetQuestItemData()->m_nCount); 
}
X_VOID ItemTask::SetTableId(X_INT nTableID)
{
	Item::SetTableId(nTableID);
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_QUEST_ITEM);
	if (pDataFile)
		m_pTableData = (const stDBC_FILE_QUEST_ITEM *)pDataFile->GetFieldsByIndexKey(m_TableId);
	if (m_pTableData)
	{
		SetRule(m_pTableData->_rule);
	}
}
X_CHAR * ItemTask::GetIcon()const
{
		if (m_pTableData)
			return m_pTableData->_icon;
		return "";
}
X_INT ItemTask::GetMaxCount()const
{
	if (m_pTableData)
		return m_pTableData->_layerNum;
	return -1;
}
X_CHAR * ItemTask::GetName()const
{
	if (m_pTableData)
		return m_pTableData->_name;
	return "";
}
X_CHAR * ItemTask::GetColor()const
{
	if (m_pTableData)
		return m_pTableData->_color;
	return "";
}
X_CHAR * ItemTask::GetType()const
{
	if (m_pTableData)
		return m_pTableData->_typeTip;
	return "";
}
X_CHAR * ItemTask::GetInfo()const
{
	if (m_pTableData)
		return m_pTableData->_infoTip;
	return "";
}
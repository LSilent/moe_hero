#include "./object/Item.h"
#include "./object/ObjectHero.h"
#include "./timer/SystemTimer.h"
Item::Item(X_CLIENT_GUID guid)
{
	m_Guid = guid;
	SetObjectType(OBJECT_TYPE_ITEM);
	m_pBaseData = new UBI_BASE_ITEM_DATA();
	this->m_bBind = 0;
	m_nCount = 1;
	m_bVirtual = false;
	m_FloatPrice = 0;
 
	m_ShopFloatPriceTimeBegin = 0;
	m_ShopFloatPriceTimeEnd = 0;
}
Item::~Item()
{
	m_ShopFloatPriceTimeBegin = 0;
	m_ShopFloatPriceTimeEnd = 0;
	SAFE_DELETE(m_pBaseData)
}

X_INT Item::GetPrice()const
{
	if (m_ShopFloatPriceTimeBegin != 0 )
	{
		tm* tm = SystemTimer::GetSingleton()->GetServerDate();
		X_INT time = (1900 + tm->tm_year)*10000 +  (tm->tm_mon+1)*100 + tm->tm_mday ;
		if (time>= m_ShopFloatPriceTimeBegin&& time<=m_ShopFloatPriceTimeEnd)
		{
			return m_FloatPrice;
		}

		return m_Price;
	}
	return m_Price;
}
X_VOID	Item::SetItemIndex(const X_UINT nItemIndex)
{
	if (m_pBaseData)
	{
		m_pBaseData->m_ItemIndex = nItemIndex;
	}
}
X_VOID Item::Release()
{
	 
}
X_UINT	Item::GetItemIndex()const
{
	if (m_pBaseData)
	{
		return m_pBaseData->m_ItemIndex;
	}
	return -1;
}
X_VOID	Item::SetItemData(const ItemData*	pData)
{
	if (pData == X_NULL)
	{
		return;
	}
	 SetBind(pData->m_bBind);
}
X_VOID  Item::SetItemVectorType(EM_ITEM_CONTAINER_TYPE continer)
{
	if (m_pBaseData)
	{
		m_pBaseData->m_PositionType = continer;
	}
}
X_VOID  Item::SetItemVectorPos(X_UINT pos)
{
	if (m_pBaseData)
	{
		m_pBaseData->m_Position = pos;
	} 
}
X_VOID  Item::SetItemOwnerGUID(X_CLIENT_GUID guid)
{
	if (m_pBaseData)
	{
		m_pBaseData->m_OwnerGUID = guid;
	} 
}
EM_ITEM_CLASS Item::GetClass()const
{
	 return EM_ITEM_CLASS (GETITEMCLASS(m_TableId));
}
X_INT Item::GetTableType()const
{
	return GETITEMTYPE(m_TableId);
}
X_VOID Item::SetTableId(X_INT nTableID)
{
	m_TableId = nTableID;
}
X_VOID Item::SetBind(X_UCHAR bind)
{
	m_bBind = bind;
}
X_VOID Item::SetCount(X_UINT count)
{
	m_nCount = count;
}
X_CLIENT_GUID  Item::GetItemOwnerGUID()const
{
	if (m_pBaseData)
	{
		return m_pBaseData->m_OwnerGUID;
	} 
	return INVALID_INDEX;

}
bool   Item::isHeroBindEquip(const ObjectHero *phero)const
{
	if (!phero || !isBindEquip()) return false;
	X_CLIENT_GUID guid = GetItemOwnerGUID();
	if (guid == INVALID_INDEX) return false;
	return  phero->GetGuid() == guid;
}
bool   Item::isBindEquip()const
{
	return m_bBind == 1;
}
X_VOID  Item::SetRule(X_INT ruleId)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ITEM_RULER);
	if (pDataFile)
		m_stRule = (const stDBC_FILE_ITEM_RULER*)pDataFile->GetFieldsByIndexKey(ruleId);
}
X_BOOL Item::Rule(RULE rule)const
{
	if (m_stRule == X_NULL)
	{
		return XFALSE;
	}
	X_BOOL _result = XFALSE;
	switch (rule)
	{
	case EM_Discard:
		{
		  _result = m_stRule->_discard;
		}
		break;
	case EM_Sale:
		{
			_result = m_stRule->_sale;
		}
		break;
	case EM_USE:
		{
			_result = m_stRule->_canUsed;
		}
		break;
	case EM_CONSUME:
		{
			_result = m_stRule->_consume;
		}
		break;
	case EM_GETBIND:
		{
			_result = m_stRule->_getBind;
		}
		break;
	case EM_USEBIND:
		{
			_result = m_stRule->_useBind;
		}
		break;
	case EM_UNIQUE:
		{
			_result = m_stRule->_Unique;
		}
		break;
	case EM_Bank:
		{
			_result = m_stRule->_warehouse;
		}
		break;
	}
	return _result;
} 
 X_INT Item::GetCount()const
{
	return m_nCount;
}
 X_INT Item::GetMaxCount()const
 {
	 return 1;
 }
 

X_BOOL  Item::getCommonItemInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT &level )
 {
	 name = "";
	 color = "";
	 icon = "";
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_COMMON_ITEM);
	 if (pDataFile)
	 {
		 const stDBC_FILE_COMMON_ITEM *	item = (const stDBC_FILE_COMMON_ITEM *) pDataFile->GetFieldsByIndexKey(nTableId);
		 if (item)
		 {
			   name = item->_name;
			   color = item->_color;
			   icon = item->_icon;
			   return XTRUE;
		 }
	 }
	 return   XFALSE;
 }
X_BOOL Item::getGemItemInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT &level )
 {
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GEM_ITEM);
	 if (pDataFile)
	 {
		 const stDBC_FILE_GEM_ITEM *	item = (const stDBC_FILE_GEM_ITEM *) pDataFile->GetFieldsByIndexKey(nTableId);
		 if (item)
		 {
			 name = item->_name;
			 color = item->_color;
			 icon = item->_icon;
			 return XTRUE;
		 }
	 }
	 return XFALSE;
 }
X_BOOL Item::getQuestItemInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT &level )
 {
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_QUEST_ITEM);
	 if (pDataFile)
	 {
		 const stDBC_FILE_QUEST_ITEM *	item = (const stDBC_FILE_QUEST_ITEM *) pDataFile->GetFieldsByIndexKey(nTableId);
		 if (item)
		 {
			 name = item->_name;
			 color = item->_color;
			 icon = item->_icon;
			 return XTRUE;
		 }
	 }
	 return XFALSE;
 }
X_BOOL Item::getEquipInfoById(X_INT nTableId,string &name,string &color,string &icon,X_INT &level )
 {
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_ITEM);
	 if (pDataFile)
	 {
		 const stDBC_FILE_EQUIP_ITEM *	item = (const stDBC_FILE_EQUIP_ITEM *) pDataFile->GetFieldsByIndexKey(nTableId);
		 if (item)
		 {
			 name = item->_name;
			 color = item->_color;
			 icon = item->_icon;
			 level = item->_level;
			 return XTRUE;
		 }
	 }
	 return XFALSE;
 }
X_INT  Item::GetLevel()const
{
	return -1;
}
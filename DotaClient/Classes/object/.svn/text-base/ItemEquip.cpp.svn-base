#include "./object/ItemEquip.h"
#include "./base/UtilTools.h"
 
ItemEquip::ItemEquip(X_CLIENT_GUID guid):Item(guid)
{
	m_bBind = 0;
	m_Attr.resize(EQUIP_MAX_ATTR);
	m_bEquiped = X_FALSE;
	m_CounterNum = 0;
}
ItemEquip::~ItemEquip()
{


}
X_VOID	ItemEquip::SetItemData(const ItemData*	pData)
{
	Item::SetItemData(pData);

	if (pData == X_NULL)
	{
		return;
	}
	SetStar(pData->GetEquipData()->m_Star);
	SetItemOwnerGUID(pData->GetEquipData()->m_BindOwnerGUID);
	SetEquiped(pData->GetEquipData()->m_bEquipUse);

}
X_VOID	ItemEquip::SetStar(X_UCHAR level)
{
	m_Star = level;
}
X_VOID ItemEquip::SetTableId(X_INT nTableID)
{
	Item::SetTableId(nTableID);
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_ITEM);
	if (pDataFile)
	{
		m_pTableData = (const stDBC_FILE_EQUIP_ITEM *)pDataFile->GetFieldsByIndexKey(m_TableId);
        //if (!m_pTableData)return;

		m_Attack = m_pTableData->_attack >= 0 ? m_pTableData->_attack :0;
		 m_Defense = m_pTableData->_defense >= 0 ? m_pTableData->_defense:0;
		 m_HP = m_pTableData->_hp >= 0 ? m_pTableData->_hp :0;
		 m_MP = m_pTableData->_mp >= 0 ? m_pTableData->_mp :0;
		 m_Weight = m_pTableData->_weight;

		 for (X_INT i = 0;i<EQUIP_MAX_ATTR_NUM;i++ )
		 {
			  if(m_pTableData->_attr[i]._id == -1  || m_pTableData->_attr[i]._value ==-1  )continue;
			  Attr att;
			  att.attrValue = m_pTableData->_attr[i]._value;
			  att.attrId = m_pTableData->_attr[i]._id;
			  m_Attr.push_back(att);
		 }
	}
	if (m_pTableData)
	{
		SetRule(m_pTableData->_rule);
		SetPrice(m_pTableData->_buyPrice);
	}
}
X_CHAR * ItemEquip::GetIcon()const
{
	if (m_pTableData)
		return m_pTableData->_icon;
	return "";
}
X_CHAR * ItemEquip::GetName()const
{
	if (m_pTableData)
		return m_pTableData->_name;
	return "";
}
X_CHAR * ItemEquip::GetColor()const
{
	if (m_pTableData)
		return m_pTableData->_color;
	return "";
}
X_CHAR * ItemEquip::GetType()const
{
	return "";
}
X_CHAR * ItemEquip::GetInfo()const
{
	if (m_pTableData)
		return m_pTableData->_infoTip;
	return "";
}
X_INT ItemEquip::GetSalePrice()const
{
	if (m_pTableData)
		return m_pTableData->_salePrice;
	return 0;
}
X_INT  ItemEquip::GetLevel()const
{
	if (m_pTableData)
		return m_pTableData->_level;
	return 0;

}

bool  ItemEquip::CanLevelUp()const
{
	if (m_pTableData)
		return (m_pTableData->_canlevelup != -1);
	return false;
}
 
X_VOID ItemEquip::SetCounterNum(X_INT CounterNum)
{
	m_CounterNum = CounterNum;
}
X_INT ItemEquip::GetCounterNum()const
{
	return m_CounterNum;
}

X_INT ItemEquip::getAddAttr(EM_ATTRIBUTE id)
{
	X_UINT size  = m_Attr.size();
	for (X_UINT i = 0;i< size;i++)
	{
		if(m_Attr[i].attrId == id)
			return m_Attr[i].attrValue;
	}
	return 0;
}
vector<string> ItemEquip::getAddAttr()const
{
	vector<string> str;
	string s;
	if (m_Attack > 0 )
	{
		s = "";
		s += UtilTools::GET_TEXT_FROM_LANG(501);
		s += UtilTools::GET_TEXT_FROM_LANG(505);
		str.push_back(s+ UtilTools::IntToString(m_Attack));
	}
	if (m_Defense > 0 )
	{
		s = "";
		s += UtilTools::GET_TEXT_FROM_LANG(502);
		s += UtilTools::GET_TEXT_FROM_LANG(505);
		str.push_back(s+ UtilTools::IntToString(m_Defense));

	}
	if (m_HP > 0 )
	{
		s = "";
		s += UtilTools::GET_TEXT_FROM_LANG(503);
		s += UtilTools::GET_TEXT_FROM_LANG(505);
		str.push_back(s+ UtilTools::IntToString(m_HP));
	}
	if (m_MP > 0 )
	{
		s = "";
		s += UtilTools::GET_TEXT_FROM_LANG(504);
		s += UtilTools::GET_TEXT_FROM_LANG(505);
		str.push_back(s+ UtilTools::IntToString(m_MP));
	}
	X_UINT size  = m_Attr.size();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ATTRIBUTE_DATA);
	 
	const stDBC_FILE_ATTRIBUTE_DATA *	m_pTableData = X_NULL;
	 
	for (X_UINT i = 0;i< size;i++)
	{
		m_pTableData = (const stDBC_FILE_ATTRIBUTE_DATA *)pDataFile->GetFieldsByIndexKey( m_Attr[i].attrId);
		if (!m_pTableData)continue;
		 
		string desc = m_pTableData->_desc;
		desc +="+";
		desc +=UtilTools::IntToString(m_Attr[i].attrValue);
		str.push_back(desc);
	}

	return str;

}

X_INT ItemEquip::getMP() const
{
	return m_MP;
}

X_INT ItemEquip::getHP() const
{
	return m_HP;
}

X_INT ItemEquip::getDefense() const
{
	return m_Defense;
}

X_INT ItemEquip::getAttack() const
{
	return m_Attack;
}

X_VOID ItemEquip::SetEquiped( X_BOOL bEquiped )
{
	m_bEquiped = bEquiped;
}
bool ItemEquip::isEquiped()const
{
	return m_bEquiped == XTRUE;
}
X_VOID ItemEquip::getDropInfo(DROP_TYPE &type,X_INT &id)const
{
	type = DROP_TYPE_INVALID;
	if (m_pTableData)
	{
		id = m_pTableData->_dropid;
		if (id >=0 && id<= 4)
		{
			type = DROP_TYPE_ALTAR;
		}else if (id != -1)
		{
			type  = DROP_TYPE_COPYSCNE;
		}
	}
}  
bool ItemEquip::isMaterial()const
{
	return GetSubClass() == EM_MATERIAL;
}
 Equip_Sub_Class  ItemEquip::GetSubClass()const
 {
	 switch (GetLevel())
	 {
	 case -4:
	 case -3:
	 case -2:
		 return EM_MATERIAL;
	 case 2:
	 case 3:
	 case 4:
	 case 5:
		return EM_FINALE;
	 }
	
	 return EM_NORMAL;
 }
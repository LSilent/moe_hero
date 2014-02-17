#ifndef __ITEMCOMMON_H__
#define __ITEMCOMMON_H__
#include "./base/Global.h"
#include "./object/Item.h"

class ItemCommon  :public Item
{
protected:
	 friend class ObjectManager;
	 friend class Item;
	 ItemCommon(X_CLIENT_GUID guid);
	 virtual ~ItemCommon();
public:
	virtual X_VOID	SetItemData(const ItemData*	pData);
	virtual X_VOID SetTableId(X_INT nTableID);

	
	virtual X_CHAR * GetIcon()const;
	virtual X_CHAR * GetName()const;
	virtual X_CHAR * GetColor()const;
	virtual X_CHAR * GetType()const;
	virtual X_CHAR * GetInfo()const;

	virtual X_INT GetSalePrice()const;
	virtual X_INT GetMaxCount()const;
	const stDBC_FILE_COMMON_ITEM * getTableData()const
	{
		return m_pTableData;
	}

	X_INT getSkillRate();
	X_INT getSkillDoubleGroup();
  
   static X_VOID  getDropInfo(X_INT Itemid,DROP_TYPE &type,X_INT &id);

protected:
	const stDBC_FILE_COMMON_ITEM *m_pTableData;
};

 


#endif //__ITEMCOMMON_H__
#ifndef __ITEMGEM_H__
#define __ITEMGEM_H__
#include "./base/Global.h"
#include "./object/Item.h"

class ItemGem  :public Item
{
protected:
	friend class ObjectManager;
	friend class Item;
	ItemGem(X_CLIENT_GUID guid);
	virtual ~ItemGem();
public:
	virtual X_VOID	SetItemData(const ItemData*	pData);
	virtual X_VOID SetTableId(X_INT nTableID);

	virtual X_CHAR * GetIcon()const;
	virtual X_CHAR * GetName()const;
	virtual X_CHAR * GetColor()const;
	virtual X_CHAR * GetType()const;
	virtual X_CHAR * GetInfo()const;

	virtual X_INT  GetSalePrice()const;
	virtual X_INT GetMaxCount()const;

protected:
	 
	X_UCHAR		m_Star;		//Ç¿»¯ÐÇ¼¶
	const stDBC_FILE_GEM_ITEM *m_pTableData;
};

 


#endif //__ITEMCOMMON_H__
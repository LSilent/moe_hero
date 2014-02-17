#ifndef __ITEMTASK_H__
#define __ITEMTASK_H__
#include "./base/Global.h"
#include "./object/Item.h"

class ItemTask  :public Item
{
protected:
	friend class ObjectManager;
	friend class Item;
	ItemTask(X_CLIENT_GUID guid);
	virtual ~ItemTask();
public:
	
 
	virtual X_VOID	SetItemData(const ItemData*	pData);
	virtual X_VOID SetTableId(X_INT nTableID);

	virtual X_CHAR * GetIcon()const;
	virtual X_CHAR * GetName()const;
	virtual X_CHAR * GetColor()const;
	virtual X_CHAR * GetType()const;
	virtual X_CHAR * GetInfo()const;

	virtual X_INT GetMaxCount()const;
protected:
	const stDBC_FILE_QUEST_ITEM *m_pTableData;
};

 


#endif // 
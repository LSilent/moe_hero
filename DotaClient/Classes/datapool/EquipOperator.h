#ifndef __EQUIPOPERATOR_H__
#define __EQUIPOPERATOR_H__

#include "./base/Global.h"
#include "./object/Item.h"
#include "./object/ItemEquip.h"
#include "./datapool/DataPool.h"

class EquipMaker
{
public:
	 
	static X_VOID getMaterial(const Item* pSourceItem,vector<stMaterialItem>& MaterialItems,X_INT &woodnum);

	static  X_VOID  Release();

	//�ڲ��ϱ������Ѱ��ĳ��tableId��index
	static X_INT __FindEquipWithId(X_INT tableId);


	static X_VOID getProduct(const Item* pSourceItem,vector<Item*>& Products);
	//�ڴ�������������Ѱ��ĳ��tableId��index
	static X_INT __FindProductEquipWithId(X_INT tableId);

	static const stDBC_FILE_EQUIP_MANUFACTURE	* getProductTableData(X_INT tableId);




	static X_VOID getIronsmithEquip( vector<ItemEquip*>& equips);

	//�ڲ��ϱ������Ѱ��ÿ���䷽�Ĳ����Ƿ����tableId
	static X_INT __FindEquipWithMaterialId(X_INT tableId);
private:
 
	static vector<Item* > m_Items;
	static  Item *  _FindItemByTableID(X_INT tableId);


};



#endif
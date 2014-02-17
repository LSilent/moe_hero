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

	//在材料表格里面寻找某个tableId的index
	static X_INT __FindEquipWithId(X_INT tableId);


	static X_VOID getProduct(const Item* pSourceItem,vector<Item*>& Products);
	//在大件武器表格里面寻找某个tableId的index
	static X_INT __FindProductEquipWithId(X_INT tableId);

	static const stDBC_FILE_EQUIP_MANUFACTURE	* getProductTableData(X_INT tableId);




	static X_VOID getIronsmithEquip( vector<ItemEquip*>& equips);

	//在材料表格里面寻找每个配方的材料是否等于tableId
	static X_INT __FindEquipWithMaterialId(X_INT tableId);
private:
 
	static vector<Item* > m_Items;
	static  Item *  _FindItemByTableID(X_INT tableId);


};



#endif
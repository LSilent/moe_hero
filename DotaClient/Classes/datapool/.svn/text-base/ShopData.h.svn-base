#ifndef __SHOPDATA_H__
#define __SHOPDATA_H__

#include "./base/Global.h"
#include "./object/Object.h"
#include <map>
class Item;
class ShopData
{
public:
	ShopData();
	~ShopData();


	X_VOID Initial();
	X_BOOL		AddItem(EM_SHOP_IDTYPE type ,X_UINT nClientPos,Item *pItem);
	X_VOID		Clear(  );
	Item *      getItem(EM_SHOP_IDTYPE type ,X_UINT nClientPos);
	X_INT       GetShopSize(EM_SHOP_IDTYPE type );
 
protected:
	 std::map< EM_SHOP_IDTYPE, vector<Item *> > 	 m_pItems;
};
#endif
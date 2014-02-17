#ifndef __SELFBAGDATA_H__
#define __SELFBAGDATA_H__

#include "./base/Global.h"
#include "./object/Object.h"


class Item;
class SelfBagData
{

public:
	X_VOID Initial();
 

	X_BOOL		AddItemToBag(X_UINT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType,Item *pItem,X_BOOL bIsDestroy = XFALSE);
	X_UINT		DelItemFromBag(X_INT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType, X_BOOL bIsDestroy = XFALSE);
	X_VOID		ClearBag(EM_ITEM_CONTAINER_TYPE nPosType, X_BOOL bIsDestroy);
	X_VOID		SetBagSize(EM_ITEM_CONTAINER_TYPE nPosType, X_UINT nBagSize);
	X_UINT		GetBagSize(EM_ITEM_CONTAINER_TYPE nPosType);

	Item *     getItem(X_UINT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType);

	X_BOOL		SwapItem(X_UINT nPos1, EM_ITEM_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_ITEM_CONTAINER_TYPE nPosType2);


	X_INT		getItemNumByTableId(X_INT tableId);

protected:
 
	typedef vector<Item *>	BAG;
	BAG bags[EM_ITEM_CONTAINER_NUMBER];

};

#endif // !__SELFBAGDATA_H__

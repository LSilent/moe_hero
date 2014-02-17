#include "./datapool/SelfBagData.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"

X_VOID SelfBagData::Initial()
{
	  bags[EM_ITEM_CONTAINER_BAG].clear();
	  bags[EM_ITEM_CONTAINER_EQUIP].clear();
}
X_BOOL	SelfBagData::AddItemToBag(X_UINT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType, Item *pItem,X_BOOL bIsDestroy)
{
	if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return XFALSE;
	BAG * pBag =  &bags[nPosType];
	if(pBag == X_NULL )return XFALSE;
	if (nClientPos<0  || nClientPos > pBag->size() )
	{ 
		return XFALSE;
	}
	if(bIsDestroy)
		DataPool::GetSingleton()->getObjectManager()->DestroyItem(pBag->at(nClientPos));

	pBag->at(nClientPos) = pItem;
	if (pItem)
	{
		pItem->SetItemVectorPos(nClientPos);
		pItem->SetItemVectorType(nPosType);
	}
	return XTRUE;
}

X_UINT	SelfBagData::DelItemFromBag(X_INT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType, X_BOOL bIsDestroy)
{
	 if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return XFALSE;
	 
	 BAG * pBag =  &bags[nPosType];
	 if(pBag == X_NULL )return XFALSE;
	 if (nClientPos<0  || nClientPos > pBag->size() )
	 { 
		 return XFALSE;
	 }
	 if(bIsDestroy)
		 DataPool::GetSingleton()->getObjectManager()->DestroyItem(pBag->at(nClientPos));
	 pBag->at(nClientPos) = X_NULL;
	 return XTRUE;
}

X_VOID	SelfBagData::ClearBag(EM_ITEM_CONTAINER_TYPE nPosType, X_BOOL bIsDestroy)
{
	if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return ;

	BAG * pBag =  &bags[nPosType];
	if(pBag == X_NULL )return;
	X_INT length = pBag->size();
	for(X_INT i= 0; i< length;i++)
	{
		if(bIsDestroy)
			DataPool::GetSingleton()->getObjectManager()->DestroyItem(pBag->at(i));
		 pBag->at(i)= X_NULL;
	}
}
X_VOID	SelfBagData::SetBagSize(EM_ITEM_CONTAINER_TYPE nPosType, X_UINT nBagSize)
{
	if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return ;
	BAG * pBag =  &bags[nPosType];
	if(pBag == X_NULL )return ;
	X_UINT size = pBag->size();

	for(X_UINT i= size;i<nBagSize;i++)
	{
		pBag->push_back(X_NULL);
	}
}
X_UINT	SelfBagData::GetBagSize(EM_ITEM_CONTAINER_TYPE nPosType)
{
	if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return 0;
	BAG * pBag =  &bags[nPosType];
	if(pBag == X_NULL )return 0;

	return pBag->size();
}
Item *     SelfBagData::getItem(X_UINT nClientPos, EM_ITEM_CONTAINER_TYPE nPosType)
{
	if(nPosType <=  EM_ITEM_CONTAINER_INVALID || nPosType >= EM_ITEM_CONTAINER_NUMBER) return X_NULL;
	BAG * pBag =  &bags[nPosType];
	if(pBag == X_NULL )return X_NULL;
	if (nClientPos<0  || nClientPos > pBag->size() )
	{ 
		return X_NULL;
	}
	return pBag->at(nClientPos);  
}

X_BOOL	SelfBagData::SwapItem(X_UINT nPos1, EM_ITEM_CONTAINER_TYPE nPosType1,X_UINT nPos2, EM_ITEM_CONTAINER_TYPE nPosType2)
{
	 if(nPosType1 <=  EM_ITEM_CONTAINER_INVALID || nPosType1 >= EM_ITEM_CONTAINER_NUMBER) return XFALSE;
	 if(nPosType2 <=  EM_ITEM_CONTAINER_INVALID || nPosType2 >= EM_ITEM_CONTAINER_NUMBER) return XFALSE;

	 BAG * pBag1 =  &bags[nPosType1];
	 if(pBag1 == X_NULL )return XFALSE;
	 if (nPos1<0  || nPos1 > pBag1->size() )
	 { 
		 return XFALSE;
	 }
	 BAG * pBag2 =  &bags[nPosType2];
	 if(pBag2 == X_NULL )return XFALSE;
	 if (nPos2<0  || nPos2 > pBag2->size() )
	 { 
		 return XFALSE;
	 }
	  Item *pItem =  pBag1->at(nPos1) ;
	  pBag1->at(nPos1) = pBag2->at(nPos2);
	  pBag2->at(nPos2) = pItem;
	 
	  //背包1的物品
	  if (pItem)
	  {
		  pItem->SetItemVectorPos(nPos2);
		  pItem->SetItemVectorType(nPosType2);
	  }
	  //交换后的背包1 即是交换前的背包2物品
	  pItem  = pBag1->at(nPos1);
	  if (pItem)
	  {
		  pItem->SetItemVectorPos(nPos1);
		  pItem->SetItemVectorType(nPosType1);
	  }
  
	  return XTRUE;
}
X_INT	SelfBagData::getItemNumByTableId(X_INT tableId)
{
	X_INT counter = 0;
	X_UINT size = 0;
	Item *pItem = X_NULL;
	for ( X_INT i = EM_ITEM_CONTAINER_INVALID +1;i < EM_ITEM_CONTAINER_NUMBER;i++)
	{
		  size = GetBagSize(EM_ITEM_CONTAINER_TYPE(i));
		  for (X_UINT j = 0 ;j < size ;j++)
		  {
			 pItem =  getItem(j,EM_ITEM_CONTAINER_TYPE(i));
			 if (!pItem || pItem->GetTableID() != tableId)continue;
			 counter += pItem->GetCount();
		  }

	}
	return counter;
}
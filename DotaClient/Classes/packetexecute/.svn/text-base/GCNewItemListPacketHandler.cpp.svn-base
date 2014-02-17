
#include "./Packets/Item/GCNewItemListPacket.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"
#include "./event/EventSystem.h"
X_INT GCNewItemListPacketHandler::Execute( GCNewItemListPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	EM_ITEM_CONTAINER_TYPE vector_type = EM_ITEM_CONTAINER_TYPE (pPacket->GetContainerType());

	X_INT num = pPacket->GetCount();
	SelfBagData*  pBag = DataPool::GetSingleton()->getBagData();
 
	X_INT vector_size = pPacket->GetContainerSize();
	pBag->SetBagSize(vector_type,vector_size);
	 
	 
	const ItemData*	 pData  = X_NULL;
	Item* pItem  = X_NULL;
	X_UINT pos = 0;
		for (X_INT i = 0;i<num;i++)
		{
			const ItemData*	 pData = pPacket->GetItem(i);
			pos = pPacket->GetItemPos(i);
			pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(pData->GetItemTableID(),pData->m_GUID.GetValue());
			if (pItem == X_NULL)
			{
				continue;
			}
			pItem->SetItemData(pData);
			pBag->AddItemToBag(pos,vector_type,pItem,X_FALSE);
		}
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTINSPECT_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_UPDATA);
	return 1;

}
 
#include "./Packets/Item/GCSwapItemPacket.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"
X_INT GCSwapItemPacketHandler::Execute( GCSwapItemPacket* pPacket, Player* pPlayer ) 
{
	if(pPacket == X_NULL) return 0;
	 EM_ITEM_CONTAINER_TYPE source = (EM_ITEM_CONTAINER_TYPE)pPacket->GetSourceContainerType();
	 EM_ITEM_CONTAINER_TYPE dest = (EM_ITEM_CONTAINER_TYPE)pPacket->GetDestContainerType();
	 X_INT pos = pPacket->GetSourcePos();
	 X_INT topos = pPacket->GetDestPos();
	//X_CLIENT_GUID guid = pPacket->GetSourceGuid().GetValue(); 
	// X_CLIENT_GUID toguid =  pPacket->GetDestGuid().GetValue();

	 SelfBagData*  pBag = DataPool::GetSingleton()->getBagData();
    // const Item * pItem1 = X_NULL;
	// const Item * pItem2 = X_NULL;

	// pItem1 = pBag->getItem(pos,source);
	// pItem2 = pBag->getItem(topos,dest);
	 pBag->SwapItem(pos,source,topos,dest);
	 
	/* if (pItem1 == X_NULL )
	 {
		  pItem1 = DataPool::GetSingleton()->getObjectManager()->FindItem(guid);

	 }else if (pItem1->GetGuid() != guid)
	 {
		  pItem1 = DataPool::GetSingleton()->getObjectManager()->FindItem(guid);
	 }
	 
	 if (pItem2 == X_NULL )
	 {
		 pItem2 = DataPool::GetSingleton()->getObjectManager()->FindItem(toguid);

	 }else if (pItem2->GetGuid() != toguid)
	 {
		 pItem2 = DataPool::GetSingleton()->getObjectManager()->FindItem(toguid);
	 }*/
	return 1;
}
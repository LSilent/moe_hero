 
#include "./Packets/Item/GCItemPosChangePacket.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"
X_INT GCItemPosChangePacketHandler::Execute( GCItemPosChangePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	EM_ITEM_CONTAINER_TYPE source = (EM_ITEM_CONTAINER_TYPE)pPacket->GetSourceContainerType();
	EM_ITEM_CONTAINER_TYPE dest = (EM_ITEM_CONTAINER_TYPE)pPacket->GetDestContainerType();
	X_INT pos = pPacket->GetSourcePos();
	X_INT topos = pPacket->GetDestPos();
	SelfBagData*  pBag = DataPool::GetSingleton()->getBagData();
	pBag->SwapItem(pos,source,topos,dest);


	return 1;

}
 
#include "./Packets/Wood/GCWoodRobPrizePacket.h"
#include "./datapool/DataPool.h"
#include "./datapool/WoodData.h"
#include "event/EventSystem.h"
X_INT GCWoodRobPrizePacketHandler::Execute( GCWoodRobPrizePacket* pPacket, Player* pPlayer ) 
{
	if(pPacket == X_NULL) 
		return 0;
	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
	pWoodData->SetPriceWood(pPacket->GetWoodNum());

	return 1;
}
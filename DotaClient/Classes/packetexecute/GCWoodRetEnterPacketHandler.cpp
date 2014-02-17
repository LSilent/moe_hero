
#include "./Packets/Wood/GCWoodRetEnterPacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"
#include "./datapool/WoodData.h"


X_INT GCWoodRetEnterPacketHandler::Execute( GCWoodRetEnterPacket* pPacket, Player* pPlayer )
{

	if(pPacket == X_NULL) 
		return 0;

	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
	pWoodData->GetSelfWoodData()->HandleData(&(pPacket->GetMyWoodData()));
	pWoodData->GetSelfWoodData()->SetRobCD(pPacket->GetRobCD()*1000);
	pWoodData->GetSelfWoodData()->SetSafeCD(pPacket->GetSafeCD()*1000);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_UPDATA);
 
	return 1;

}

 

#include "./Packets/Wood/GCWoodRetRobObjPacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"
#include "./datapool/WoodData.h"


X_INT GCWoodRetRobObjPacketHandler::Execute( GCWoodRetRobObjPacket* pPacket, Player* pPlayer )
{

	if(pPacket == X_NULL) 
		return 0;
	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();

	pWoodData->HandleRobData(&(pPacket->GetRobWoodData()));

	std::vector<std::string>  par;
	switch (pPacket->GetRobType())
	{
	case 0:par.push_back("rob");break;
	case 1:par.push_back("Revenge");break;
	}

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_UPDATA,par);

 
	return 1;

}


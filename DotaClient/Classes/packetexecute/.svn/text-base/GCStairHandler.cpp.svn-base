
#include "./Packets/Stair/GCStairMonsterGroupPacket.h"
#include "./Packets/Stair/GCStairPlusPacket.h"
#include "./Packets/Stair/GCStairPrizePacket.h"
#include "./Packets/Stair/GCStairRetEnterPacket.h"
#include "./datapool/DataPool.h"
#include "./datapool/BloodData.h"
#include "./event/EventSystem.h"

X_INT GCStairMonsterGroupPacketHandler::Execute( GCStairMonsterGroupPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	 BloodData *pData  = DataPool::GetSingleton()->GetBloodData();

	  pData->handleMonsterPacket(pPacket);
	 
	return 1;
}


//ok
X_INT GCStairPlusPacketHandler::Execute( GCStairPlusPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	  BloodData *pData  = DataPool::GetSingleton()->GetBloodData();
	 pData->handleStairPlusPacket(pPacket);
	 
	return 1;
}

X_INT GCStairPrizePacketHandler::Execute( GCStairPrizePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	 BloodData *pData  = DataPool::GetSingleton()->GetBloodData();
	 pData->SetExp(pPacket->GetExp());
	 pData->SetItemID(pPacket->GetItemID());
	 pData->SetStar(pPacket->GetStar());
	return 1;
}

//ok 
X_INT GCStairRetEnterPacketHandler::Execute( GCStairRetEnterPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	BloodData *pData  = DataPool::GetSingleton()->GetBloodData();
	pData->handleStairEnterPacket(pPacket);
	return 1;
}

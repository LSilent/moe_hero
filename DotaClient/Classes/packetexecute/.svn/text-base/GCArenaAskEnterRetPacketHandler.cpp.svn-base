 
#include "./Packets/Arena/GCArenaAskEnterRetPacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"
#include "./Packets/Arena/GCArenaChallengePrizePacket.h"

X_INT GCArenaAskEnterRetPacketHandler::Execute( GCArenaAskEnterRetPacket* pPacket, Player* pPlayer )
{

	if(pPacket == X_NULL) return 0;

	SportsData * pData =  DataPool::GetSingleton()->getSportsData();
	pData->OnServerData(pPacket);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RANKLIST_UPDATA );
 
	return 1;

}
X_INT GCArenaChallengePrizePacketHandler::Execute( GCArenaChallengePrizePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	SportsData * pData =  DataPool::GetSingleton()->getSportsData();
	pData->exp = pPacket->GetExp();
	pData->gold =pPacket->GetGold();
	return 1;
}
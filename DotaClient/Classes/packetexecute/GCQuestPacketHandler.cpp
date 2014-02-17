
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"
#include "./Packets/Mission/GCAcceptMissionPacket.h"
#include "./Packets/Mission/GCMissionListPacket.h"
#include "./Packets/Mission/GCUpdateMissionPacket.h"


X_INT GCAcceptMissionPacketHandler::Execute( GCAcceptMissionPacket* pPacket, Player* pPlayer )
{
	if (!pPacket)return 0;
	QuestData * pdata = DataPool::GetSingleton()->getQuestData();
	pdata->setServerData(pPacket->GetMissionData());
	pdata->setNewFlag(true);
	pdata->sortData();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TASKINFO_UPDATA);
	return 1;
}

X_INT GCMissionListPacketHandler::Execute( GCMissionListPacket* pPacket, Player* pPlayer )
{
	if (!pPacket)return 0;
	X_INT count = pPacket->GetMissionCount();
	QuestData * pdata = DataPool::GetSingleton()->getQuestData();
	pdata->Release();
	for (X_INT i = 0;i<count;i++)
	{
		pdata->setServerData(pPacket->GetMission(i));
	}
	pdata->setAsked();
	pdata->sortData();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TASKINFO_UPDATA);
	return 1;

}
X_INT GCUpdateMissionPacketHandler::Execute( GCUpdateMissionPacket* pPacket, Player* pPlayer )
{
	if (!pPacket)return 0;
	QuestData * pdata = DataPool::GetSingleton()->getQuestData();
	pdata->setServerData(pPacket->GetMissionData());
	pdata->sortData();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TASKINFO_UPDATA);

	return 1;
}

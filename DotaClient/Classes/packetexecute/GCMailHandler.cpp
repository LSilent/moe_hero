
#include "./Packets/Mail/GCMailNotifyPacket.h"
#include "./Packets/Mail/GCMailOpenPacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"

X_INT GCMailNotifyPacketHandler::Execute( GCMailNotifyPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	 
	DataPool::GetSingleton()->getMailData()->setNotifyMail(true);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);

	return 1;
}

X_INT GCMailOpenPacketHandler::Execute( GCMailOpenPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	const MailBoxData *pdata = &(pPacket->GetMailBox());
	DataPool::GetSingleton()->getMailData()->setServerData(pdata);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MESSAGE_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
	return 1;
}
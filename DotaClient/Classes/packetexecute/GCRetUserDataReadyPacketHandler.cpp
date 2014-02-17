 
#include "./Packets/Login/GCRetUserDataReadyPacket.h"
#include "./Packets/Login/CGAskEnterScenePacket.h"
#include "./net/NetworkSystem.h"

X_INT GCRetUserDataReadyPacketHandler::Execute( GCRetUserDataReadyPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	
	 CGAskEnterScenePacket packet;
	 packet.SetSceneID(1);
	 NetworkSystem::GetSingleton()->SendPacket(&packet);

	return 1;

}
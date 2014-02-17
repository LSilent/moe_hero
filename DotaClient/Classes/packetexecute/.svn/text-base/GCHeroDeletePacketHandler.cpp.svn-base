 
#include "./Packets/Hero/GCHeroDeletePacket.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./event/EventSystem.h"

X_INT GCHeroDeletePacketHandler::Execute( GCHeroDeletePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	EM_HERO_CONTAINER_TYPE  container = EM_HERO_CONTAINER_TYPE (pPacket->GetContainerType());
	X_INT count = pPacket->GetCount();
	X_INT pos;
	for (X_INT i = 0;i<count ;i++)
	{
		pos = pPacket->GetHeroPos(i);
		pSelf->Del_Hero(pos,container,X_TRUE);
	}
	return 1;
}
 
#include "./Packets/Hero/GCHeroPosChangePacket.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./event/EventSystem.h"

X_INT GCHeroPosChangePacketHandler::Execute( GCHeroPosChangePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	 ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	 EM_HERO_CONTAINER_TYPE  source = EM_HERO_CONTAINER_TYPE (pPacket->GetSourceContainerType());
	 EM_HERO_CONTAINER_TYPE  dest = EM_HERO_CONTAINER_TYPE (pPacket->GetDestContainerType());
	 X_INT count = pPacket->GetCount();
	 X_INT pos, topos;
	for (X_INT i = 0;i<count ;i++)
	{
		pos = pPacket->GetHeroSourcePos(i);
		topos = pPacket->GetHeroDestPos(i);
		pSelf->SwapHero(pos,source,topos,dest);
	}
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
	return 1;
}
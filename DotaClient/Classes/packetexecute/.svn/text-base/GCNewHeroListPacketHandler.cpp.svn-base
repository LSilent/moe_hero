 
#include "./Packets/Hero/GCNewHeroListPacket.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./event/EventSystem.h"

X_INT GCNewHeroListPacketHandler::Execute( GCNewHeroListPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	X_CLIENT_GUID guid =  pPacket->GetGuid().GetValue();
	ObjectPlayer * Player = X_NULL;

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	if (pSelf && pSelf->GetGuid() == guid )
	{
		Player = pSelf;
	}
	else
	{
		DataPool::GetSingleton()->getObjectManager()->cleanPlayerMap();
		Player =  static_cast<ObjectPlayer*>(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_PLAYER,guid));
	}
	if (Player == X_NULL)
	{
		return 0;
	}
	EM_HERO_CONTAINER_TYPE  container = EM_HERO_CONTAINER_TYPE (pPacket->GetContainerType());
	X_UINT	size = pPacket->GetContainerSize();
	Player->SetHeroVectorSize(size,container);
	X_INT num = pPacket->GetCount();
	ObjectHero* pHero = X_NULL;
	for (X_INT i = 0;i<num ;i++)
	{
 
		pHero =  static_cast<ObjectHero* >(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,pPacket->GetHero(i)->m_Guid.GetValue()));
		pHero->setServerData(pPacket->GetHero(i),Player == pSelf);
		Player->Add_Hero(pPacket->GetHeroPos(i),container,pHero,X_FALSE);
	}
	if (container == EM_HERO_CONTAINER_BAG)
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
	} 
	if (Player != pSelf)
	{
		DataPool::GetSingleton()->setSelectPlayer(Player);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_OTHERHEROINFO_SHOW);
	}
	return 1;

}
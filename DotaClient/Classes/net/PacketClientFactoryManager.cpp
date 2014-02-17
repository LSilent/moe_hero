 
#include "PacketClientFactoryManager.h"
#include "./Packets/Base/PacketDefine.h"
#include "./Packets/Base/PacketFactory.h"
#include "./Packets/GCTimePacket.h"
#include "./packets/Login/GCRetEnterScenePacket.h"
#include "./packets/Login/GCRetRolelistPacket.h"
#include "./packets/Login/GCRetUserDataReadyPacket.h"
#include "./packets/GCGameResultPacket.h"
 
#include "./Packets/Human/GCRetHumanDetailAttrPacket.h"
#include "./Packets/Hero/GCHeroDeletePacket.h"
#include "./Packets/Hero/GCHeroDetailAttrPacket.h"
#include "./Packets/Hero/GCHeroPosChangePacket.h"
#include "./Packets/Hero/GCNewHeroListPacket.h"


#include "./Packets/Item/GCItemDeletePacket.h"
#include "./Packets/Item/GCItemInfoPacket.h"
#include "./Packets/Item/GCItemPosChangePacket.h"
#include "./Packets/Item/GCNewItemListPacket.h"
#include "./Packets/Item/GCSwapItemPacket.h"
#include "./Packets/Fight/GCFightInfoPacket.h"
#include "./Packets/Mail/GCMailNotifyPacket.h"
#include "./Packets/Mail/GCMailOpenPacket.h"
#include "./Packets/Fight/GCUpdateCopyScenePacket.h"
#include "./Packets/Fight/GCRetCopySceneListPacket.h"
#include "./Packets/Arena/GCArenaAskEnterRetPacket.h"
#include "./Packets/Item/GCItemListNotifyPacket.h"
#include "./Packets/HuoDong/GCHuoDongListPacket.h"
#include "./Packets/HuoDong/GCHuoDongStateChangePacket.h"
#include "./Packets/Human/GCChatPacket.h"
#include "./Packets/Arena/GCArenaChallengePrizePacket.h"
#include "./Packets/Charge/GCRetChargePacket.h"
#include "./Packets/Other/GCRetAchievementPacket.h"
#include "./Packets/Mission/GCAcceptMissionPacket.h"
#include "./Packets/Mission/GCMissionListPacket.h"
#include "./Packets/Mission/GCUpdateMissionPacket.h"
#include "./Packets/Wood/GCWoodRetEnterPacket.h"
#include "./Packets/Wood/GCWoodRetRobObjPacket.h"
#include "./Packets/Wood/GCWoodRobPrizePacket.h"

#include "./Packets/QuJing/GCQuJingPrizePacket.h"
#include "./Packets/QuJing/GCOpenQuJingUIPacket.h"
#include "./Packets/QuJing/GCQuJingPrizePacket.h"
#include "./Packets/QuJing/GCRetQuJingDataPacket.h"
#include "./Packets/QuJing/GCQuJingHuSongBroadPacket.h"
#include "./Packets/Stair/GCStairMonsterGroupPacket.h"
#include "./Packets/Stair/GCStairPlusPacket.h"
#include "./Packets/Stair/GCStairPrizePacket.h"
#include "./Packets/Stair/GCStairRetEnterPacket.h"



PacketClientFactoryManager::PacketClientFactoryManager()
{
	m_pFactoryPtr = X_NULL;
	m_pStatistic = X_NULL;
}

PacketClientFactoryManager::~PacketClientFactoryManager()
{
}

X_BOOL PacketClientFactoryManager::Init()
{
	m_pFactoryPtr = new PacketFactory*[PACKET_ID_NUMBER];
	m_pStatistic = new X_INT[PACKET_ID_NUMBER];
	for (X_INT i=0; i<PACKET_ID_NUMBER; ++i)
	{
		m_pFactoryPtr[i] = X_NULL;
		m_pStatistic[i] = 0;
	}

	X_BOOL bRet = XTRUE;

	bRet = _RegisterFactory(new GCTimePacketFactory());
	bRet = _RegisterFactory(new GCRetRolelistPacketFactory());
	bRet = _RegisterFactory(new GCRetUserDataReadyPacketFactory());
	bRet = _RegisterFactory(new GCRetEnterScenePacketFactory());
	bRet = _RegisterFactory(new GCGameResultPacketFactory());

	bRet = _RegisterFactory(new GCRetHumanDetailAttrPacketFactory());
	bRet = _RegisterFactory(new GCHeroDeletePacketFactory());
	bRet = _RegisterFactory(new GCHeroDetailAttrPacketFactory());
	bRet = _RegisterFactory(new GCHeroPosChangePacketFactory());
	bRet = _RegisterFactory(new GCNewHeroListPacketFactory());
	
	bRet = _RegisterFactory(new GCItemDeletePacketFactory());
	bRet = _RegisterFactory(new GCItemInfoPacketFactory());
	bRet = _RegisterFactory(new GCItemPosChangePacketFactory());
	bRet = _RegisterFactory(new GCNewItemListPacketFactory());
	bRet = _RegisterFactory(new GCSwapItemPacketFactory());
	bRet = _RegisterFactory(new GCFightInfoPacketFactory());
	bRet = _RegisterFactory(new GCMailOpenPacketFactory());
	bRet = _RegisterFactory(new GCMailNotifyPacketFactory());
	bRet = _RegisterFactory(new GCRetCopySceneListPacketFactory());
	bRet = _RegisterFactory(new GCUpdateCopyScenePacketFactory());
	bRet = _RegisterFactory(new GCArenaAskEnterRetPacketFactory());
	bRet = _RegisterFactory(new GCItemListNotifyPacketFactory());
	bRet = _RegisterFactory(new GCHuoDongListPacketFactory());
	bRet = _RegisterFactory(new GCHuoDongStateChangePacketFactory());
	bRet = _RegisterFactory(new GCChatPacketFactory());
	bRet = _RegisterFactory(new GCArenaChallengePrizePacketFactory());
	bRet = _RegisterFactory(new GCRetChargePacketFactory());
	bRet = _RegisterFactory(new GCRetAchievementPacketFactory());

	bRet = _RegisterFactory(new GCAcceptMissionPacketFactory());
	bRet = _RegisterFactory(new GCMissionListPacketFactory());
	bRet = _RegisterFactory(new GCUpdateMissionPacketFactory());

	bRet = _RegisterFactory(new GCWoodRetEnterPacketFactory());
	bRet = _RegisterFactory(new GCWoodRetRobObjPacketFactory());
	bRet = _RegisterFactory(new GCWoodRobPrizePacketFactory());
 
	bRet = _RegisterFactory(new GCQuJingPrizePacketFactory());
	bRet = _RegisterFactory(new GCOpenQuJingUIPacketFactory());
	bRet = _RegisterFactory(new GCQuJingPrizePacketFactory());
	bRet = _RegisterFactory(new GCRetQuJingDataPacketFactory());
	bRet = _RegisterFactory(new GCQuJingHuSongBroadPacketFactory());
 
	bRet = _RegisterFactory(new GCStairMonsterGroupPacketFactory());
	bRet = _RegisterFactory(new GCStairPlusPacketFactory());
	bRet = _RegisterFactory(new GCStairPrizePacketFactory());
	bRet = _RegisterFactory(new GCStairRetEnterPacketFactory());

	return bRet;  
}

X_VOID PacketClientFactoryManager::Release()
{
	for (X_INT i=0; i<PACKET_ID_NUMBER; ++i)
	{
		SAFE_DELETE(m_pFactoryPtr[i]);
	}
	SAFE_DELETE_ARRAY(m_pFactoryPtr);
	SAFE_DELETE_ARRAY(m_pStatistic);
}

Packet* PacketClientFactoryManager::CreatePacket(PacketID id)
{
	if (id>=0 && id<PACKET_ID_NUMBER)
	{
		PacketFactory* pFactory = m_pFactoryPtr[id];
		if (pFactory != X_NULL)
		{
			++m_pStatistic[id];
			return pFactory->CreatePacket();
		}
	}
	return X_NULL;
}

X_BOOL PacketClientFactoryManager::RemovePacket(Packet* pPacket)
{
	if (pPacket != X_NULL)
	{
		PacketID id = pPacket->GetPacketID();
		PacketFactory* pFactory = m_pFactoryPtr[id];
		if (pFactory != X_NULL)
		{
			return pFactory->RemovePacket(pPacket);
		}
	}
	return X_FALSE;
}

X_UINT PacketClientFactoryManager::GetPacketMaxSize(PacketID id) const
{
	if (id<0 || id>PACKET_ID_NUMBER || m_pFactoryPtr[id]==X_NULL)
	{
		return 0;
	}

	return m_pFactoryPtr[id]->GetPacketMaxSize();
}

X_BOOL PacketClientFactoryManager::_RegisterFactory(PacketFactory* pFactory)
{
	if (pFactory != X_NULL)
	{
		if (m_pFactoryPtr[pFactory->GetPacketID()] != X_NULL)
		{
			return X_FALSE;
		}
		m_pFactoryPtr[pFactory->GetPacketID()] = pFactory;
		return XTRUE;
	}
	return X_FALSE;
}
X_BOOL	PacketClientFactoryManager::CheckPacketID(PacketID id)
{
		if (id<=PACKET_ID_INVALID || id>PACKET_ID_NUMBER || m_pFactoryPtr[id] == X_NULL)
		{
			return X_FALSE;
		}
		return XTRUE;
}
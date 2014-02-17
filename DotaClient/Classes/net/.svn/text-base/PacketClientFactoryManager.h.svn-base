#ifndef __PACKET_CLIENT_FACTORYMANAGER_h__
#define __PACKET_CLIENT_FACTORYMANAGER_h__

#include "./base/Global.h"
#include "./Packets/Base/Packet.h"
class PacketFactory;
class PacketClientFactoryManager
{
public:
	PacketClientFactoryManager();
	virtual ~PacketClientFactoryManager();
public:
	virtual X_BOOL					Init();
	virtual X_VOID					Release();
	Packet*							CreatePacket(PacketID id);
	X_BOOL							RemovePacket(Packet* pPacket);
	X_UINT							GetPacketMaxSize(PacketID id) const;
	//ºÏ≤ÈPacketID
	X_BOOL							CheckPacketID(PacketID id);

private:
	X_BOOL							_RegisterFactory(PacketFactory* pFactory);
private:
	PacketFactory**					m_pFactoryPtr;
	X_INT*							m_pStatistic;
};
#endif
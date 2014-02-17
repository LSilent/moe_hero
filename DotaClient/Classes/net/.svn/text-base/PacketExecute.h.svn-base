#ifndef __PACKETEXECUTE_H__
#define __PACKETEXECUTE_H__
 
#include "./base/Global.h"
#include <map>
using namespace std;

class Packet;


typedef X_VOID (* PACKET_EXECUTE_FUNCTION_HANDLE)(Packet* pPacket);
typedef  map< X_UINT, PACKET_EXECUTE_FUNCTION_HANDLE > EXECUTE_FUNCTION_MAP;

class PacketExecute
{
public:
	static X_VOID	Initial();
	static X_VOID	Release();
 	static X_VOID	ExecutePacket(PacketID nPacketID, Packet* pPacket);
public:
 	//static X_VOID  CGTestExecute(Packet* pPacket);
	//static X_VOID  GCTickExecute(Packet* pPacket);
	//static X_VOID  GCRolelistPacketExecute(Packet* pPacket);
public:
	 //static EXECUTE_FUNCTION_MAP m_mapPacketExecuteList;
};

#endif
#include "PacketExecute.h"
#include "./Packets/Base/PacketDefine.h"
#include "./Packets/Base/Packet.h"

//EXECUTE_FUNCTION_MAP PacketExecute::m_mapPacketExecuteList;
X_VOID PacketExecute::Initial()
{
	//m_mapPacketExecuteList.clear();
	//m_mapPacketExecuteList[0] = &PacketExecute::CGTestExecute;
	//m_mapPacketExecuteList[PACKET_GC_TIME] = &PacketExecute::GCTickExecute;
	//m_mapPacketExecuteList[PACKET_GC_RET_ROLELIST] = &PacketExecute::GCRolelistPacketExecute;

	
}
X_VOID PacketExecute::Release()
{
	//m_mapPacketExecuteList.clear();
}
X_VOID PacketExecute::ExecutePacket(PacketID nPacketID, Packet* pPacket)
{ 
	pPacket->Execute(X_NULL);

	/*EXECUTE_FUNCTION_MAP::iterator it = m_mapPacketExecuteList.find(nPacketID);
	if(it == m_mapPacketExecuteList.end())
		return;
	it->second(pPacket);*/
 
}
/*X_VOID  PacketExecute::CGTestExecute(Packet* pPacket)
{
	 
}*/

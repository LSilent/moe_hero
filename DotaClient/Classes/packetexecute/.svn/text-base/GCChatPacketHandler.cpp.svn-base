
#include "./Packets/Human/GCChatPacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"

// #include "./datapool/ChatData.h"

X_INT GCChatPacketHandler::Execute( GCChatPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	 
	Record  rd;
	rd.m_nChatType = pPacket->GetChatType();
	rd.m_strContex = pPacket->GetContent();
	rd.m_strName = pPacket->GetSourceName();
	rd.m_nValue = pPacket->GetSourceGuid().GetValue();
	ChatData *pData = DataPool::GetSingleton()->GetChatData();
	pData->AddChatMsg(rd);
	Record rec;
	pData->GetChatMsg(Set1_Channel,rec);

	if (rec.m_strContex.size() != 0)
	{
		vector<string> str;
		str.clear();
		str.push_back(rec.m_strContex);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_NOTICE_UPDATA,str);

	}

    EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHATMESSAGE_UPDATA);
    
	return 1;
}

#include "./Packets/QuJing/GCQuJingHuSongBroadPacket.h"
#include "./Packets/QuJing/GCOpenQuJingUIPacket.h"
#include "./Packets/QuJing/GCQuJingPrizePacket.h"
#include "./Packets/QuJing/GCRetQuJingDataPacket.h"
#include "./datapool/DataPool.h"
#include "./datapool/QuJingData.h"
#include "./event/EventSystem.h"

X_INT GCQuJingHuSongBroadPacketHandler::Execute( GCQuJingHuSongBroadPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	pData->upDataQujingData(pPacket);
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_UPDATA);
	return 1;
}

X_INT GCOpenQuJingUIPacketHandler::Execute( GCOpenQuJingUIPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	pData->SetQujingData(pPacket);
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_UPDATA);
	return 1;
}

X_INT GCQuJingPrizePacketHandler::Execute( GCQuJingPrizePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	 

	pData->SetType(pPacket->GetType());
	pData->SetCurrentHuSongID(pPacket->GetHuSongID());
	pData->SetTotalWood(pPacket->GetTotalWood());
	pData->SetTotalExp(pPacket->GetTotalExp());
	pData->SetQuJingDay(pPacket->GetQuJingDay());

	//EventSystem::GetSingleton()->PushEvent()
	return 1;
}

X_INT GCRetQuJingDataPacketHandler::Execute( GCRetQuJingDataPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	//µ±Ç°»¤ËÍID 
	X_INT id = pPacket->GetCurrentHuSongID();
	X_INT num = pPacket->GetHuSongTimes();
	X_INT RobTimes = pPacket->GetRobTimes();
	X_INT RobCDTime = pPacket->GetRobCDTime();
	const X_GUID* guid = pPacket->GetHeroGuid();

	const X_INT* tablesId = pPacket->GetHeroTableID();

	BitFlag32  flag  = pPacket->GetBitFlag();

	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (flag.isSetBit(EM_QUJING_DATA_HUSONG_ID))
	{
		pData->SetCurrentHuSongID(id);
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_WOODSHIZHE_UPDATA);
	}
	if (flag.isSetBit(EM_QUJING_DATA_HUSONG_TIMES))
	{
		pData->SetHuSongTimes(num);
	}
	if (flag.isSetBit(EM_QUJING_DATA_ROB_TIMES))
	{
		pData->SetRobTimes(RobTimes);
	}
	if (flag.isSetBit(EM_QUJING_DATA_ROB_CD))
	{
		pData->SetRobCDTime(RobCDTime);
	}
	if (flag.isSetBit(EM_QUJING_DATA_MATRIX))
	{
		pData->SetHeroGuid(guid);
	}

	if (flag.isSetBit(EM_QUJING_DATA_HERO))
	{
		pData->SetHeroTableID(tablesId);
	}

	if (flag.isSetBit(EM_QUJING_DATA_LEFTTIME))
	{
		pData->SetLeftTime(pPacket->GetLeftTime());
	}
 
 	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_WOODSHIZHE_UPDATA);
	return 1;
}

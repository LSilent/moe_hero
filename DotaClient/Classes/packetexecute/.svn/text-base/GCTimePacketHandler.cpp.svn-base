/*#include "./net/PacketExecute.h"
#include "./Packets/GCTimePacket.h"
#include "cocos2d.h"
X_VOID  PacketExecute::GCTickExecute(Packet* pPacket)
{
	GCTimePacket *p = static_cast<GCTimePacket*>(pPacket);
	if(p == X_NULL) return;
	printf("--------CGTickExecute");
	cocos2d::CCLog("--------CGTickExecute");
}
*/
#include "./Packets/GCTimePacket.h"
#include "./datapool/DataPool.h"
#include "./timer/SystemTimer.h"
#include "./Packets/Charge/GCRetChargePacket.h"
#include "./Packets/Other/GCRetAchievementPacket.h"
#include "./event/EventSystem.h"
#include "./base/Sdk_Handler.h"

X_INT GCTimePacketHandler::Execute( GCTimePacket* pPacket, Player* pPlayer )
{

	if(pPacket == X_NULL) return 0;

	SystemTimer::GetSingleton()->SetServerTime(pPacket->GetTime());
	//static X_UINT i = 0;
	//DataPool::GetSingleton()->GetHeartBeatData()->ReceiveHeartBeatData(i+1);
 
	return 1;

}

X_INT GCRetChargePacketHandler::Execute( GCRetChargePacket* pPacket, Player* pPlayer )
{
	if (pPacket == X_NULL) return 0;
	X_INT billno =  pPacket->GetBillNo();
	X_INT id  =  pPacket->GetChargeID();
	X_INT zone =  pPacket->GetGroupID();
	string roleid =  pPacket->GetUserID();


	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CHARGE);
	if (!pDataFile)
	{
		return 1;
	}
	const stDBC_FILE_CHARGE	*m_pTableData = (const stDBC_FILE_CHARGE*)pDataFile->GetFieldsByIndexKey(id);
	if (!m_pTableData)
	{
		return 1;
	}
	X_INT  amount = m_pTableData->costMoney;
	string billno_title = m_pTableData->name;
	SdkHandler::buyGold(amount, billno_title, roleid, zone, billno,id);
 
	 return 1;
}


X_INT GCRetAchievementPacketHandler::Execute( GCRetAchievementPacket* pPacket, Player* pPlayer )
{
	if (!pPacket) return 0;
	 
	X_INT count = pPacket->GetCount();
	AchieveData data;
	AchievementData *pData = DataPool::GetSingleton()->getAchievementData();
	X_BOOL b = X_FALSE;
	pData->Reset();
	for (X_INT i =0;i<count;i++)
	{
		b = pPacket->GetAchievement(i,data);
		if (b == X_TRUE)
		{
			pData->AddData(&data);
		}
	}
	pData->Sort();

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_ACHIEVE_UPDATA);

	return 0;
}
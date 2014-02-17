 
#include "./Packets/HuoDong/GCHuoDongListPacket.h"
#include "./Packets/HuoDong/GCHuoDongStateChangePacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventDefine.h"
#include "./event/EventSystem.h"

X_INT GCHuoDongListPacketHandler::Execute( GCHuoDongListPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
 
	X_INT week = pPacket->GetWeekDay();
	X_INT min = pPacket->GetHourMin();
	HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	X_INT num  = pPacket->GetHuoDongCount();
	pData->Release();
	for (X_INT i = 0;i<num;i++)
	{
		pData->setHuoDong(pPacket->GetHuoDongID(i),pPacket->GetHuoDongState(i),pPacket->GetHuoDongParam(i));
	}
	vector<string>str;str.clear(),str.push_back("normal");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA,str);

	 /*HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	 vector<HuoDong*> hds = pData->getHuoDong();
	 HuoDong* hd = hds[0];


	 UtilTools::AskHuoDong(); 点击活动界面先调用该接口
	 UtilTools::EnjoyHuoDong(hd->getId()); //参加活动调用该接口

	 */
	  
	
	return 1;
}
X_INT GCHuoDongStateChangePacketHandler::Execute( GCHuoDongStateChangePacket* pPacket, Player* pPlayer )
{

	if(pPacket == X_NULL) return 0;
	HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	X_INT nID,nState,nParam;
	pPacket->GetHuoDongState(  nID, nState,nParam);
	pData->setHuoDongState(nID,nState,nParam);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA);
 
	return 1;
}

#include "./Packets/Fight/GCRetCopySceneListPacket.h"
#include "./Packets/Fight/GCUpdateCopyScenePacket.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"

X_INT GCRetCopySceneListPacketHandler::Execute( GCRetCopySceneListPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;

	X_INT groupId = pPacket->GetCopySceneGroupID();
	X_INT num = pPacket->GetCount();
	X_INT copySceneID;X_INT  copyStatus;X_INT  copySceneStar;X_INT  ChallangeCount;
	CopySceneManager * pManager = DataPool::GetSingleton()->getCopySceneManager();

	CopySceneGroup* pGroup = pManager->getCopySceneGroupById(groupId);
	if (!pGroup)return 0;
	pGroup->setAsked(true);
	for (X_INT i = 0; i< num;i++)
	{
		pPacket->GetCopyScene(i,copySceneID,copyStatus,copySceneStar,ChallangeCount);
		pManager->SetCopyScene(pGroup,copySceneID,copyStatus,copySceneStar,ChallangeCount);
	}
	if(pManager->getChangeGroup())
		pManager->setCurSceneGroup(pGroup);
	//无参数表示更新组
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_UPDATA);

	return 1;
}

X_INT GCUpdateCopyScenePacketHandler::Execute( GCUpdateCopyScenePacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	CopySceneManager * pManager = DataPool::GetSingleton()->getCopySceneManager();
	X_INT groupId = pPacket->GetCopySceneGroupID();
	CopySceneGroup* pGroup = pManager->getCopySceneGroupById(groupId);
	if (!pGroup)return 0;
	pGroup->setAsked(true);
	X_INT copySceneID = pPacket->GetCopySceneID();
	X_INT copyStatus = pPacket->GetCopySceneStatus();
	X_INT  copySceneStar = pPacket->GetCopySceneStar();
	X_INT  ChallangeCount = pPacket->GetChallangeCount();
	pManager->SetCopyScene(pGroup,copySceneID,copyStatus,copySceneStar,ChallangeCount);


	CopyScene* pScene = X_NULL;
	if (pGroup)
	{
		pScene = pGroup->getCopySceneById(copySceneID);
	}
	if (pScene)
	{
		pScene->SetAwardGold(pPacket->GetAwardGold()) ;
		pScene->SetAwardHumanExp(pPacket->GetAwardHumanExp());
		X_INT count =  pPacket->GetCount();
		X_BOOL bOk = X_FALSE;
	    pScene->SetCount(count);
		for (X_INT i = 0 ;i < count ;i++)
		{
			X_INT itemid,itemnum;
			bOk = pPacket->GetAwardItem(i,itemid,itemnum);
			if (!bOk)continue;
			pScene->AddAwardItem(i,itemid,itemnum);
		}

		if (pGroup->getGroupID()!= 1000)
		{
			pManager->setCurScene(pScene);
			pManager->setCurSceneGroup(pGroup);
		}
		if (copyStatus == EM_COPYSCENE_STATUS_PASS)
		{
			pManager->setAwardScene(pScene);
		}
	}
	//刷新当前的副本组
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_UPDATA);
	return 1;
}
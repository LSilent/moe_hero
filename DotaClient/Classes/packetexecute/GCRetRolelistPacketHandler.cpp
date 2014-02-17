
#include "./Packets/Login/GCRetRolelistPacket.h"
#include "./datapool/DataPool.h"
#include "./Packets/Login/CGAskUserDataPacket.h"
#include "./net/NetworkSystem.h"
#include "./event/EventSystem.h"
#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./packets/Login/CGAskEnterScenePacket.h"
#include "cocos2d.h"

#include "./ui/SceneManger.h"
#include "./ui/element/gameIntroduceLayer.h"

X_INT GCRetRolelistPacketHandler::Execute( GCRetRolelistPacket* pPacket, Player* pPlayer )
{
	cocos2d::CCLog("---------------------------GCRetRolelistPacketHandler::Execute");
	if(pPacket == X_NULL) return 0;

	X_GUID guid = pPacket->GetGuid();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOGIN_CLOSE);
	if(guid.IsValid())
	{
		DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_SELF,guid.GetValue());

		CGAskUserDataPacket packet;
		packet.SetGUID(guid);
		packet.SetPlayerID(0);
		NetworkSystem::GetSingleton()->SendPacket(&packet);
		cocos2d::CCLog("---------------------------GCRetRolelistPacketHandler   CGAskUserDataPacket");

	}else
	{
        EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_LOGIN_CLOSE);
        SceneManger::GetSingleton()->playGameIntroduce();
		gameIntroduceLayer *introLayer = gameIntroduceLayer::createLayer();
		introLayer->setPosition(SceneManger::GetSingleton()->GetCurrentScene()->getPosition());
		SceneManger::GetSingleton()->AddChildToScene(introLayer,true);
 
		introLayer->playIntroduce();

		 cocos2d::CCLog("---------------------------GCRetRolelistPacketHandler   RUING_IN_SELECTPLAYER");
	}

	return 0;
}

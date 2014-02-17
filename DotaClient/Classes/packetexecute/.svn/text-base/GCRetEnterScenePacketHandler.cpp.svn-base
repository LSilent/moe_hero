 
#include "./Packets/Login/GCRetEnterScenePacket.h"
#include "./game/MainGame.h"
#include "./game/SendPacket.h"
#include "./datapool/DataPool.h"
#include "../Wood/CGWoodAskPacket.h"
#include <cocos2d.h>
#include "./base/Sdk_Handler.h"
#include "./event/EventSystem.h"
X_INT GCRetEnterScenePacketHandler::Execute( GCRetEnterScenePacket* pPacket, Player* pPlayer )
{
	cocos2d::CCLog("---------------------------GCRetEnterScenePacketHandler");
	if(pPacket == X_NULL) return 0;

	switch (pPacket->GetResult())
	{
	case GCRetEnterScenePacket::EM_ENTER_SCENE_INVALID:
		{

		}
		break;
	case GCRetEnterScenePacket::EM_ENTER_SCENE_SUCCESS:
		{
			cocos2d::CCLog("---------------------------GCRetEnterScenePacketHandler   EM_ENTER_SCENE_SUCCESS");
			 SendLogicPacket::askHumanDetail();
			 SendLogicPacket::askPacket(EM_ITEM_CONTAINER_BAG);
			 SendLogicPacket::askPacket(EM_ITEM_CONTAINER_EQUIP);
			 SendLogicPacket::askHeros(EM_HERO_CONTAINER_BAG);
			 SendLogicPacket::askHeros(EM_HERO_CONTAINER_RECRUIT);
			 SendLogicPacket::AskAchievement();
			 SendLogicPacket::OpenMailBox();
			 SendLogicPacket::AskQuJingData();
			 SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_ENTER);
			 MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_GAME);
             SdkHandler::inGameShowToolBar();
			 SdkHandler::requestShopInfo();
			 EventSystem::GetSingleton()->PushEvent(GAME_EVENT_PLACARD_SHOW);
 
		}
		break;
	case GCRetEnterScenePacket::EM_ENTER_SCENE_FULL:
		{

		}
		break;
	}

	return 1;
}


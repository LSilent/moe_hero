 
#include "./Packets/Human/GCRetHumanDetailAttrPacket.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./event/EventSystem.h"
#include "./ui/cheeseActivityUI.h"
X_INT GCRetHumanDetailAttrPacketHandler::Execute( GCRetHumanDetailAttrPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	if (pSelf ==X_NULL )
	{
		return 0;
	}
	PlayerData*  pData = pSelf->playerData();
	if (pData ==X_NULL )
	{
		return 0;
	}
	BitFlag32 flag =  pPacket->GetBitFlag();
	X_BOOL updata = XFALSE;
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_NAME);							//玩家名称  
	if (updata)
	{
		pData->setName(pPacket->GetName());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_LEVEL);               			//当前等级
	if (updata)
	{
		pData->SetLevel(pPacket->GetLevel());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_VIP_LEVEL);						//vip等级
	if (updata)
	{
		pData->SetVipLevel(pPacket->GetVipLevel());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_EXP);               			//当前经验 
	if (updata)
	{
		pData->SetExp(pPacket->GetExp());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_VIP_EXP);						//vip经验
	if (updata)
	{
		pData->SetVipExp(pPacket->GetVipExp());
	}
 
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_STONE);							//宝石
	if (updata)
	{
		 pData->SetGem(pPacket->GetStone());
		 EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_GOLD);							//金币
	if (updata)
	{
		pData->SetGold(pPacket->GetGold());
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SECRETSTORE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_ACHIEVE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MESSAGE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_UPDATA);
		
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_WOOD);		//木材
	if (updata)
	{
		pData->SetWood(pPacket->GetWood());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_ACTIONPOINT);					//玩家状态标识
	if (updata)
	{
		pData->SetActionPoint(pPacket->GetActionPoint());
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_USER_INFO_UPDATA);

	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_STATE_FLAG);					//玩家状态标识
	if (updata)
	{
			pData->SetStateFlag(pPacket->GetStateFlag());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_TODAY_ACTIVITY);				//日活跃度
	if (updata)
	{
		pData->SetTodayActivity(pPacket->GetTodayActivity());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_MONTH_ACTIVITY);			//月活跃度 	
	if (updata)
	{
		pData->SetMonthActivity(pPacket->GetMonthActivity());
	}
	/*updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_ROCK_LEFTTIMES);		//摇女神今日剩余次数
	if (updata)
	{
		pData->SetRockLeftTimes(pPacket->GetRockLeftTimes());
		vector<string> str;
		str.clear();
		str.push_back( UtilTools::IntToString(EM_SHAKE_ENTER_LAYER_SHOW));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SHAKE_UPDATA,str);

	}*/
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_GODDESS_GUID);		//女神英雄GUID
	if (updata)
	{
		X_CLIENT_GUID guid  = pPacket->GetGoddessHeroGuid().GetValue();
		pData->SetGoddessHeroGuid(guid);
		if (guid!=INVALID_ID)
		{
			ObjectHero* pHero = X_NULL;
			pHero =  static_cast<ObjectHero* >(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,pPacket->GetGoddessHeroGuid().GetValue()));
			pHero->SetTableID(pPacket->GetGoddessHeroid());
			pHero->SetDataReady();
			vector<string> str;
			str.clear();

			str.push_back( UtilTools::IntToString(EM_SHAKE_GODDESS_LAYER_SHOW));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SHAKE_UPDATA,str);
		}
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_MATRIX);		 //阵法
	if (updata)
	{
		pData->SetFightHero(pPacket->GetFightHero());
		 
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_RECRUIT_HEROCOUNT);		//招募个数(x/6)
	if (updata)
	{
		pData->SetRecruitHeroCount(pPacket->GetRecruitHeroCount());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_RECRUIT_REFRESHLEFT);		 //招募刷新剩余时间
	if (updata)
	{
		pData->SetRecruitRefreshLefttime(pPacket->GetRecruitRefreshLefttime());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_RECRUIT_FREETIMES);		 //免费刷新次数
	if (updata)
	{
		pData->SetFreeRefreshNum(pPacket->GetRecruitLeftFreeTimes());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_BEARPOINT);		 //承载力
	if (updata)
	{
		pData->SetBearPoint(pPacket->GetBearPoint());
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_MAX_COPYSCENE_GROUP);	
	if (updata)
	{
		pData->SetMaxCopySceneGroupID(pPacket->GetMaxCopySceneGroupID());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_SACRIFICE_ID);	
	if (updata)
	{
		pData->SetSacrificeID(pPacket->GetSacrificeID());
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_SACRIFICE_DAMAGE);	
	if (updata)
	{
		pData->SetSacrificeDamage(pPacket->GetSacrificeDamage());
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_SACRIFICE_AWARD);	
	if (updata)
	{
		for (X_INT i = 0;i< MAX_SACRIFICE_RECENT_AWARDITEM_COUNT;i++)
		{
			pData->SetSacrificeAward(i,pPacket->GetSacrificeAward(i));
		}
		 EventSystem::GetSingleton()->PushEvent( GAME_EVENT_ALTAR_UPDATA);
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_BUY_BEARPOINT_COUNT);	
	if (updata)
	{
		pData->SetBuyBearPointCount(pPacket->GetBuyBearPointCount());
		EventSystem::GetSingleton()->PushEvent( GAME_EVENT_CHEESE_UPDATA);
	}
 
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_BUY_BEARPOINT_COUNT);	
	if (updata)
	{
		 DataPool::GetSingleton()->getGuideData()->SetTipGroup(pPacket->GetFreshGuideGroup());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_BUY_ACTIONPOINT_COUNT);	
	if (updata)
	{
		pData->SetBuyAcNum(pPacket->GetBuyActionPointCount());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_TOTAL_PPMONEY);	
	if (updata)
	{
		pData->SetChargeMoney(pPacket->GetTotalPPMoney());
	}
	updata = flag.isSetBit(EM_HUMAN_DETAIL_ATTR_ROCKTIMES);	
	if (updata)
	{
		pData->SetRockTimes(pPacket->GetRockTimes());
	}

	

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
	return 1;
}
 
#include "./Packets/Hero/GCHeroDetailAttrPacket.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectPlayer.h"
#include "./event/EventSystem.h"

X_INT GCHeroDetailAttrPacketHandler::Execute(GCHeroDetailAttrPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0; 
	 BitFlag32 flag = pPacket->GetBitFlag();
	 X_CLIENT_GUID guid = pPacket->GetOwnerGuid().GetValue();

	ObjectHero *pHero =  static_cast<ObjectHero *>(DataPool::GetSingleton()->getObjectManager()->FindInstance(OBJECT_TYPE_HERO,pPacket->GetGuid().GetValue()));
	if (pHero == X_NULL)
	{
		return 0;
	}
		X_BOOL updata = XFALSE;
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_TABLEID);//表格id

		if(updata)	
		{
			pHero->SetTableID(pPacket->GetTableID());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_CONTAINER);			//武将容器
		if(updata)	
		{
			 pHero->SetContainerType(pPacket->GetContainerType());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_POS);				//武将容器中位置
		if(updata)	
		{
			pHero->SetPos(pPacket->GetPos());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_LEVEL);				//等级
		if(updata)	
		{
			pHero->SetLevel(pPacket->GetLevel());
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROEVOLVE_UPDATA);
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_EXP);				//经验
		if(updata)	
		{
			pHero->SetExp(pPacket->GetExp());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_GROWRATE);			//成长
		if(updata)	
		{
			pHero->SetGrowRate(pPacket->GetGrowRate());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_BEARPOINT);			//负重
		if(updata)	
		{
			pHero->SetBearPoint(pPacket->GetBearPoint());
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LOADDISTRIBUTE_UPDATA);
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_QUALITY);			//品质
		if(updata)	
		{
			pHero->SetQuality(pPacket->GetQuality());
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROEVOLVE_UPDATA);
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_STATUS);				//状态
		if(updata)	
		{
			pHero->SetStatus(pPacket->GetStatus());
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_UPDATA);
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_PHYSICATTACK);		//物理攻击
		if(updata)	
		{
			pHero->SetPhysicAttack(pPacket->GetPhysicAttack());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_MAGICATTACK);		//魔法攻击
		if(updata)	
		{
			pHero->SetMagicAttack(pPacket->GetMagicAttack());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_PHYSICDEFENCE);		//物理防御
		if(updata)	
		{
			pHero->SetPhysicDefence(pPacket->GetPhysicDefence());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_MAGICDEFENCE);		//魔法防御
		if(updata)	
		{
			pHero->SetMagicDefence(pPacket->GetMagicDefence());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_HP);					//生命
		if(updata)	
		{
			pHero->SetHP(pPacket->GetHP());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_MAXHP);
		if(updata)	
		{
			pHero->SetMaxHP(pPacket->GetMaxHP());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_MP);					//魔法值
		if(updata)	
		{
			pHero->SetMP(pPacket->GetMP());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_MAXMP);
		if(updata)	
		{
			pHero->SetMaxMP(pPacket->GetMaxMP());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_HIT);				//命中点数
		if(updata)	
		{
			pHero->SetHit(pPacket->GetHit());
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_DODGE);				//闪避点数
		{
			pHero->SetDodge(pPacket->GetDodge());
		}
		
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_SKILL);				//技能列表
		if(updata)	
		{
			pHero->SetSkillCount(pPacket->GetSkillCount());
			for (X_INT i = 0; i< pPacket->GetSkillCount() ;i++)
			{
				pHero->SetSkill(i, pPacket->GetSkill(i));
			}
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_UPDATA);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_UPDATA);
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_EQUIP);				//装备列表
		if(updata)	
		{
			for (X_INT i = 0; i< MAX_EQUIP_NUM_PER_HERO ;i++)
			{
				pHero->SetEquip(i, pPacket->GetEquip(i).GetValue());
			}
		}
		updata = flag.isSetBit(EM_HERO_DETAIL_ATTR_COLOR);				//颜色
		if(updata)	
		{
			pHero->SetColor(pPacket->GetColor());
		}
		pHero->SetDataReady();
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_UPDATA);

		
	return 1;
}
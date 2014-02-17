#include "./Packets/Fight/GCFightInfoPacket.h"
#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./event/EventSystem.h"

X_INT GCFightInfoPacketHandler::Execute( GCFightInfoPacket* pPacket, Player* pPlayer )
{
	if (!pPacket )return 0;
	const cFightInfo* info = pPacket->GetFightInfo();
	BattleData * pBattle = DataPool::GetSingleton()->GetBattleData();
	pBattle->PrepareData(info);
	// while(pBattle->tickRound())
	// {
	//	 // 攻防数据
	//	 const vector<BattleObject*> attacker = pBattle->getAttack();
	//	 const vector<BattleObject*> defenser = pBattle->getDefense();
	//	 //出手数据
	//	 const vector<const cAttackInfo *> AttackInfos = pBattle->getRoundAttackData();

	//	 // 按guid找到释放技能 或者受击者
	//	 //BattleObject* castSkiller = pBattle->FindFighterByGUID(guid);
	//	 // 确定其位置  isAttacker确定上下，GetPosition（）返回位置索引 0-5
	//	 //castSkiller->isAttacker();
	//	 // castSkiller->GetPosition();
	//	 //获得技能的数据
	//	 //Skill::GetEffect(skillId);
	//	 //Skill:: .......
	// }
	 

	MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_BATTLE);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BATTLEFIELD_SHOW);
	return 1;
}

	 
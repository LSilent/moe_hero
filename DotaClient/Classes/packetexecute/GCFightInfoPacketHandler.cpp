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
	//	 // ��������
	//	 const vector<BattleObject*> attacker = pBattle->getAttack();
	//	 const vector<BattleObject*> defenser = pBattle->getDefense();
	//	 //��������
	//	 const vector<const cAttackInfo *> AttackInfos = pBattle->getRoundAttackData();

	//	 // ��guid�ҵ��ͷż��� �����ܻ���
	//	 //BattleObject* castSkiller = pBattle->FindFighterByGUID(guid);
	//	 // ȷ����λ��  isAttackerȷ�����£�GetPosition��������λ������ 0-5
	//	 //castSkiller->isAttacker();
	//	 // castSkiller->GetPosition();
	//	 //��ü��ܵ�����
	//	 //Skill::GetEffect(skillId);
	//	 //Skill:: .......
	// }
	 

	MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_BATTLE);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BATTLEFIELD_SHOW);
	return 1;
}

	 
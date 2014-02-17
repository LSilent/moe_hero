#include "./ui/battleFieldUI.h"
#include "./ui/battleFieldUIView.h"

USING_NS_CC_EXT;

BattleFieldUI::BattleFieldUI()
{
	this->m_MutexGroup = 9;
	AccelerateCurlLevel = 1;
}
BattleFieldUI::~BattleFieldUI()
{

}

X_VOID   BattleFieldUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_BATTLEFIELD_SHOW);
	m_Event.push_back(GAME_EVENT_BATTLEFIELD_CLOSE);
}
X_VOID	 BattleFieldUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_BATTLEFIELD_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_BATTLEFIELD_CLOSE:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
	 
}
X_VOID	BattleFieldUI::OnCreate()
{
	if (m_pUi) return;


	//test, ignore memory leak
	//struct cFightInfo *pFightInfo = new cFightInfo;

	//struct cFObjectData fightObjData;

	//fightObjData.m_Guid = 0;
	//fightObjData.m_MatrixID = 0;
 //   pFightInfo->AddAttackObjectData( fightObjData );

	//fightObjData.m_Guid = 1;
	//fightObjData.m_MatrixID = 4;
 //   pFightInfo->AddAttackObjectData( fightObjData );

	//fightObjData.m_Guid = 2;
	//fightObjData.m_MatrixID = 2;
 //   pFightInfo->AddAttackObjectData( fightObjData );

	//fightObjData.m_Guid = 3;
	//fightObjData.m_MatrixID = 1;
 //   pFightInfo->AddDefendObjectData( fightObjData );

	//fightObjData.m_Guid = 4;
	//fightObjData.m_MatrixID = 2;
 //   pFightInfo->AddDefendObjectData( fightObjData );

	//fightObjData.m_Guid = 5;
	//fightObjData.m_MatrixID = 3;
 //   pFightInfo->AddDefendObjectData( fightObjData );

	//// max bar distance
	//pFightInfo->m_MaxFightDistance = 100;

	//struct cFightRoundInfo fightRoundInfo;
	//struct cFObjectInfo fightObjInfo;
	//struct cAttackInfo attackInfo;

	//// round 1
	//fightRoundInfo.CleanUp();
	//fightObjInfo.m_FightDistance = 50;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 40;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 80;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );

	//fightObjInfo.m_FightDistance = 60;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 80;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 50;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );

	//attackInfo.m_CastGuid = 0;
	//attackInfo.m_SkillTarget = 3;
	//attackInfo.m_Hurt = 10;
	//attackInfo.m_bStrike = true;
	//fightRoundInfo.AddAttackInfo( attackInfo );

	///*attackInfo.m_CastGuid = 3;
	//attackInfo.m_SkillTarget = 1;
	//attackInfo.m_Hurt = 10;
	//fightRoundInfo.AddAttackInfo( attackInfo );*/

	//pFightInfo->AddRoundInfo( fightRoundInfo );

	//// round 2
	//fightRoundInfo.CleanUp();
	//fightObjInfo.m_FightDistance = 100;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 80;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 60;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );

	//fightObjInfo.m_FightDistance = 20;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 60;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 100;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );

	//attackInfo.m_CastGuid = 1;
	//attackInfo.m_SkillTarget = 5;
	//attackInfo.m_Hurt = 10;
	//attackInfo.m_bBackAttack = true;
	//attackInfo.m_BackAttackHurt = 5;
	//fightRoundInfo.AddAttackInfo( attackInfo );

	///*attackInfo.m_CastGuid = 4;
	//attackInfo.m_SkillTarget = 2;
	//attackInfo.m_Hurt = 20;
	//fightRoundInfo.AddAttackInfo( attackInfo );*/

	//pFightInfo->AddRoundInfo( fightRoundInfo );

	//// round 3
	//fightRoundInfo.CleanUp();
	//fightObjInfo.m_FightDistance = 40;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 90;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 20;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );

	//fightObjInfo.m_FightDistance = 60;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 20;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 50;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );

	//attackInfo.m_CastGuid = 2;
	//attackInfo.m_SkillTarget = 4;
	//attackInfo.m_Hurt = 30;
	//attackInfo.m_bBackAttack = false;
	//fightRoundInfo.AddAttackInfo( attackInfo );

	//pFightInfo->AddRoundInfo( fightRoundInfo );

	//// round 4
	//fightRoundInfo.CleanUp();
	//fightObjInfo.m_FightDistance = 80;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 20;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 60;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddAttackObjectInfo( fightObjInfo );

	//fightObjInfo.m_FightDistance = 90;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 80;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );
	//fightObjInfo.m_FightDistance = 20;
	//fightObjInfo.m_HP = 100;
	//fightRoundInfo.AddDefendObjectInfo( fightObjInfo );

	//attackInfo.m_CastGuid = 4;
	//attackInfo.m_SkillTarget = 1;
	//attackInfo.m_Hurt = 10;
	//fightRoundInfo.AddAttackInfo( attackInfo );

	//attackInfo.m_CastGuid = 5;
	//attackInfo.m_SkillTarget = 0;
	//attackInfo.m_Hurt = 20;
	//attackInfo.m_bBackAttack = false;
	//fightRoundInfo.AddAttackInfo( attackInfo );

	///*attackInfo.m_CastGuid = 1;
	//attackInfo.m_SkillTarget = 3;
	//attackInfo.m_Hurt = 30;
	//fightRoundInfo.AddAttackInfo( attackInfo );*/

	//pFightInfo->AddRoundInfo( fightRoundInfo );


	/* Read a ccbi file. */
	m_pUi = BattleFieldUIView::create( NULL/*pFightInfo*/ );
}

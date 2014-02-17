#include "./datapool/BloodData.h"
#include "./base/UtilTools.h"

#include "./Packets/Stair/GCStairMonsterGroupPacket.h"
#include "./Packets/Stair/GCStairPlusPacket.h"
#include "./Packets/Stair/GCStairPrizePacket.h"
#include "./Packets/Stair/GCStairRetEnterPacket.h" 
#include "./event/EventSystem.h"
#include "./ui/SceneManger.h"
#include "./ui/cheeseActivityUI.h"


BattleLayer::BattleLayer()
{
	CleanUp();
}
BattleLayer::~ BattleLayer()
{

}
 X_VOID BattleLayer::CleanUp()
 {
	 m_Layer= INVALID_VALUE;								
	 m_AccStar= INVALID_VALUE;							
	 m_CurStar= INVALID_VALUE;								
	 m_NextPlusLayers= INVALID_VALUE;						
	 m_PlusAtt=INVALID_VALUE;								
	 m_PlusDef=INVALID_VALUE;								
	 m_PlusHp=INVALID_VALUE;								
	 for (X_INT i=0;i<MAX_STAIR_MONSER_GROUP;++i)
	 {
		 m_MonsterGroup[i].CleanUp();
	 }
	 m_MaxTotalStar=INVALID_VALUE;							
	 m_MaxPassLayers=INVALID_VALUE;		
 }
X_VOID BloodData::Initial()
{ 
	m_Begin = false;
	memset(m_Star,0,sizeof(m_Star));
	memset(m_Plus,0,sizeof(m_Plus));
	m_BufferComingNum = 0;
	m_BattleNextOk = false;
	 
}
X_VOID BloodData::Release()
{
	 
}
X_VOID BloodData::handleStairPlusPacket(GCStairPlusPacket* pPacket)
{
	if(!pPacket) return;

	 m_Begin = pPacket->IsBegin();
	 X_INT * pData =  pPacket->GetStar();
	 X_INT * pDataPlus =  pPacket->GetPlus();

	 if (!m_pLayer)
	 {
		 m_pLayer = new BattleLayer();
	 } 

	 m_pLayer->m_Layer = pPacket->GetLayer();
	 m_pLayer->m_AccStar = pPacket->GetAccStar(); 
	 m_pLayer->m_CurStar = pPacket->GetCurStar();	

	 for (X_INT i = 0; i< STAIR_PLUS_COUNT;i++)
	 {
		 m_Star[i] = pData[i];
		 m_Plus[i] = pDataPlus[i];
	 }
	 m_BufferComingNum++;

	 if (SceneManger::GetSingleton()->GetSceneStatus() == SceneManger::EM_SS_MAIN)
	 {
		 NextStep();
	 }

}

X_VOID BloodData::handleStairEnterPacket(GCStairRetEnterPacket* pPacket)
{
	if(!pPacket) return;
	m_Times = pPacket->GetTimes();
	m_LeftTimes = pPacket->GetLeftTimes();
	m_Layer = pPacket->GetLayer();
	m_MaxTotalStar = pPacket->GetMaxTotalStar();
	m_MaxPassLayers = pPacket->GetMaxPassLayers();
	vector<string> str;
	str.clear();
	str.push_back(UtilTools::IntToString( (EM_XUEZHAN_ENTER_LAYER_SHOW) ));
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BLOODBATTLE_UPDATA,str) ;
 
}
  
X_VOID BloodData::handleMonsterPacket(GCStairMonsterGroupPacket* pPacket)
{
	if(!pPacket) return;
	if (m_pLayer)
	{
		m_pLayer->CleanUp();
	}else
	{
		m_pLayer = new BattleLayer();
	}
	m_pLayer->m_Layer = pPacket->GetLayer();
	m_pLayer->m_AccStar = pPacket->GetAccStar(); 
 	m_pLayer->m_CurStar = pPacket->GetCurStar();	
	m_pLayer->m_NextPlusLayers = pPacket->GetNextPlusLayers();
	m_pLayer->m_PlusAtt = pPacket->GetPlusAtt();
	m_pLayer->m_PlusDef = pPacket->GetPlusDef();
	m_pLayer->m_PlusHp = pPacket->GetPlusHp();			
	m_pLayer->m_MaxTotalStar = pPacket->GetMaxTotalStar();
	m_pLayer->m_MaxPassLayers = pPacket->GetMaxPassLayers();

 	StairMonster* pMonster =	pPacket->GetStairMonster();
	for (X_INT i =0;i< MAX_STAIR_MONSER_GROUP;i++)
	{
		m_pLayer->m_MonsterGroup[i] =  	pMonster[MAX_STAIR_MONSER_GROUP - i -1];
	}
	if (SceneManger::GetSingleton()->GetSceneStatus() == SceneManger::EM_SS_MAIN)
	{
		NextStep();
	}
}
X_VOID  BloodData::NextStep()
{
	m_BattleNextOk = true;
	if (m_BufferComingNum > 0)
	{
		std::vector<string> str;
		str.clear();
		str.push_back("1");// EM_XUEZHAN_BUFFER_LAYER_SHOW
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BLOODBATTLE_SHOW,str) ;
		return;
	}
	std::vector<string> str;
	str.clear();
	str.push_back("2");//EM_XUEZHAN_BATTLE_LAYER_SHOW
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BLOODBATTLE_SHOW,str) ;

}
X_VOID BloodData:: EnterBloodUi()
{
	std::vector<string> str;
	str.clear();
	str.push_back("0");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BLOODBATTLE_SHOW,str) ;
}
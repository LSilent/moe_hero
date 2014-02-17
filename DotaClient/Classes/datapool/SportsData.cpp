#include "./datapool/SportsData.h"
#include "./Packets/Arena/GCArenaAskEnterRetPacket.h"
#include "./database/DataBaseSystem.h"
#include "./base/UtilTools.h"

Competitor::Competitor()
{
	m_heros.clear();
    m_data = X_NULL;

}

 X_VOID Competitor::Release()
{
	m_heros.clear();
	m_data = X_NULL;
}
 X_CLIENT_GUID Competitor::getGuid()const
 {

	return  m_data->m_GUID.GetValue();
 }
 X_INT Competitor::getRank()const
 {
	 return m_data->m_Rank +1;
 }
 X_CHAR * Competitor::getName()const
 {
	 return m_data->m_Name;
 }
 X_INT Competitor::getLevel()const
 {
	 return m_data->m_Level;
 }

 //成功金钱
 X_INT Competitor::getSuccMoney()const
 {
	  return m_data->m_SuccMoney;
 }
 //成功声望
 X_INT Competitor::getSuccExp()const
 {
	  return m_data->m_SuccExp;
 }
 //失败金钱
 X_INT Competitor::getFailMoney()const
 {
	 return m_data->m_FailMoney;
 }
 //失败声望
 X_INT Competitor::getFailExp()const
 {
	 return m_data->m_FailExp;
 }
 X_VOID Competitor::setData(ArenaMember *pdata)
 {
	 m_data = pdata;
	 m_heros.clear();
	 CompetitorHero hero;
	 for(X_INT i=0;i<MAX_MATRIX_CELL_COUNT;++i)
	 {
		X_INT tableId = pdata->m_HeroID[i]  ;
		if (tableId == -1)continue;
		 hero.tableId = tableId;
		 hero.Quality =  (EM_HERO_QUALITY_TYPE)pdata->m_Quality[i];
		 hero.color = (EM_HERO_COLOR_TYPE)pdata->m_Color[i];
		m_heros.push_back(hero);
	 }
 }

X_VOID SportsData::Initial()
{
	m_Competitors.clear();
	m_Top10.clear();
	m_Rank =-1;
	exp = 0;
	gold = 0;
	m_WelfareCD = 0;
}
X_VOID SportsData::Release()
{
	X_UINT size = m_Competitors.size();
	for (X_UINT i = 0;i < size; i++)
	{
		m_Competitors[i]->Release();
		SAFE_DELETE(m_Competitors[i]);
	}
	m_Competitors.clear();
	size = m_Top10.size();

	for (X_UINT i = 0;i < size; i++)
	{
		m_Top10[i]->Release();
		SAFE_DELETE(m_Top10[i]);
	}
	m_Top10.clear();
	
}
X_VOID  SportsData::Tick(X_UINT nTime)
{
   m_WelfareCD -= nTime;
   if (m_WelfareCD < 0 )
   {
	   m_WelfareCD = 0;
   }
   m_FightCD -= nTime;
   if (m_FightCD < 0 )
   {
	   m_FightCD = 0;
   }
}

X_VOID SportsData::OnServerData(GCArenaAskEnterRetPacket* pPacket)
{
	if (!pPacket)return;
	Release();
	Competitor *pCompetitor = X_NULL;
	X_INT top10 = pPacket->GetRankMemberNum();
	ArenaMember *member =  pPacket->GetRankMemberList();
	for (X_INT i = 0 ; i<top10;i++)
	{
		pCompetitor = new Competitor();
		pCompetitor->setData( &member[i]);
		m_Top10.push_back(pCompetitor);
	}
	X_INT size = pPacket->GetMemberNum();
	member =  pPacket->GetMemberList();
	for (X_INT i = 0 ; i<size;i++)
	{
		pCompetitor = new Competitor();
		pCompetitor->setData( &member[i]);
		m_Competitors.push_back(pCompetitor);
	}
	m_Rank = pPacket->GetRank() + 1;
	m_GiftID = pPacket->GetGiftID();
	m_WelfareCD = pPacket->GetWelfareCD()*1000;
	m_WinCount = pPacket->GetWinCount();
	m_RemainArenaCount = pPacket->GetChallengeCountRemain();
	m_ChallengeMoney = pPacket->GetChallengeMoney();
	m_FightCD = pPacket->GetFightCD()*1000;

}

string	SportsData::GetAwards()
{
	string str = "";
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GIFT_PACKET);
	const stDBC_FILE_GIFT_PACKET *pData =  (const stDBC_FILE_GIFT_PACKET *) pDataFile->GetFieldsByIndexKey(GetGiftID());
	if (pData)
	{
		str = UtilTools::GET_TEXT_FROM_LANG(516); 
		str += UtilTools::IntToString(pData->gold);
		str += UtilTools::GET_TEXT_FROM_LANG(517);
		str +=  ",";
		str += UtilTools::IntToString(pData->exp);
		str +=UtilTools::GET_TEXT_FROM_LANG(518);
	}
	return str;
}
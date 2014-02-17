#ifndef __SPORTS_DATA_H__
#define __SPORTS_DATA_H__

#include "./base/Global.h"

 
struct CompetitorHero
{
	X_CHAR tableId;
	EM_HERO_QUALITY_TYPE Quality;
	EM_HERO_COLOR_TYPE color;
};
class Competitor
{
	friend class SportsData;
public:
	Competitor();


	X_CLIENT_GUID getGuid()const;
	//排名
	X_INT getRank()const;
	X_CHAR * getName()const;
	X_INT getLevel()const;

	//成功金钱
	X_INT getSuccMoney()const;
	//成功声望
	X_INT getSuccExp()const;

	//失败金钱
	X_INT getFailMoney()const;
	//失败声望
	X_INT getFailExp()const;

	const vector<CompetitorHero> & getHeros() { return m_heros; }
	 
protected: 

	vector<CompetitorHero> m_heros;
	
	X_VOID Release();

	X_VOID setData(ArenaMember *pdata);
	ArenaMember *m_data;
};

 
class GCArenaAskEnterRetPacket;
class SportsData
{
public:
	X_VOID Initial();
	X_VOID Release();
	X_VOID OnServerData(GCArenaAskEnterRetPacket* pPacket);
	X_VOID  Tick(X_UINT nTime);
public:
	const vector<Competitor*> & getCompetitor()
	{
		return m_Competitors;
	}
	const vector<Competitor*> & getTop10()
	{
		return m_Top10;
	}


	X_INT				GetRank(){return m_Rank;}
	 

	X_INT				GetGiftID(){return m_GiftID;}
	 
	string				GetAwards();

	X_INT				GetWelfareCD(){return m_WelfareCD;}
 


	X_INT				GetWinCount(){return m_WinCount;}
	 

	X_INT				GetChallengeCountRemain(){return m_RemainArenaCount;}
 


	X_INT				GetChallengeMoney(){return m_ChallengeMoney;}
 

	X_INT				GetFightCD(){return m_FightCD;}
 
	X_INT                exp;
	X_INT				 gold;			
private:
 

	vector<Competitor*>  m_Competitors;
	vector<Competitor*>  m_Top10;
	

	//数据
	X_INT	m_Rank;						//排名
	X_INT	m_GiftID;					//排名奖励礼包ID
	X_INT	m_WelfareCD;				//奖励倒计时
	X_INT	m_WinCount;					//连胜次数
	X_INT	m_RemainArenaCount;			//剩余挑战次数
	X_INT	m_ChallengeMoney;			//剩余挑战次数为0时进行挑战需要元宝
	X_INT	m_FightCD;					//战斗冷却时间(秒)

	   
	 
};



#endif // !__RANK_DATA_H__

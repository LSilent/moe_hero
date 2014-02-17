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
	//����
	X_INT getRank()const;
	X_CHAR * getName()const;
	X_INT getLevel()const;

	//�ɹ���Ǯ
	X_INT getSuccMoney()const;
	//�ɹ�����
	X_INT getSuccExp()const;

	//ʧ�ܽ�Ǯ
	X_INT getFailMoney()const;
	//ʧ������
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
	

	//����
	X_INT	m_Rank;						//����
	X_INT	m_GiftID;					//�����������ID
	X_INT	m_WelfareCD;				//��������ʱ
	X_INT	m_WinCount;					//��ʤ����
	X_INT	m_RemainArenaCount;			//ʣ����ս����
	X_INT	m_ChallengeMoney;			//ʣ����ս����Ϊ0ʱ������ս��ҪԪ��
	X_INT	m_FightCD;					//ս����ȴʱ��(��)

	   
	 
};



#endif // !__RANK_DATA_H__

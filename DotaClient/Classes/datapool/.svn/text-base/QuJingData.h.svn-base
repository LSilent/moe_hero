#ifndef __QUJINGDATA_H__
#define __QUJINGDATA_H__

#include "./base/Global.h"
#include "./GameStruct.h"
#include "./database/DataBaseSystem.h"

class GCOpenQuJingUIPacket;
class GCQuJingHuSongBroadPacket; 
class ObjectHero;
 
class QuJingPlayerData
{
	public:
		QuJingPlayerData();
		friend class QuJingData;
		X_VOID  Tick(X_UINT nTime);
		X_FLOAT getPerCent();
 
	   X_INT    m_time;
	   X_GUID	m_GUID;						//guid
	   string	m_Name;	//名字
	   X_INT	m_Level;					//等级
	   X_INT	m_HuSongID;					//护送ID
	   X_INT	m_TimeLeft;					//护送剩余时间
	   X_INT	m_BeRobTimes;				//被拦劫次数
	   X_INT	m_BeRobExp;					//拦劫经验
	   X_INT	m_BeRobWood;				//拦劫木材
	   X_INT	m_TotalExp;					//护送获得经验
	   X_INT	m_TotalWood;				//护送获得木材
};
  
class  QuJingData
{
 
public:

	X_VOID Initial();
	X_VOID Release();
	X_VOID  Tick(X_UINT nTime);
 

public:
	X_INT			GetCurrentHuSongID() const	{return m_CurrentHuSongID;}
	X_INT			GetHuSongTimes() const	{return m_HuSongTimes;}
	X_INT			GetRobTimes() const	{return m_RobTimes;}
	X_INT			GetRobCDTime() const	{return m_RobCDTime;}
	const X_GUID*	GetHeroGuid() const	{ return m_HeroGuid; }
	X_INT				GetTotalWood() const {return m_TotalWood;}
	X_INT				GetQuJingDay() const {return m_QuJingDay;}
	X_INT				GetTotalExp( ) { return m_exp;}

	X_VOID			SetCurrentHuSongID(X_INT id)	{m_CurrentHuSongID = id; }
	X_VOID			SetHuSongTimes(X_INT times)	{m_HuSongTimes = times;}
	X_VOID			SetRobTimes(X_INT robTimes)	{m_RobTimes = robTimes;}
	X_VOID			SetRobCDTime(X_INT cdTime)	{m_RobCDTime = cdTime;}
	X_VOID			SetHeroGuid(const X_GUID* pGuid)
	{
		m_bHeroSetMatrix = false;
		for(X_INT i=0;i<MAX_MATRIX_CELL_COUNT;++i)
		{
			m_HeroGuid[i] = pGuid[i];
		}
		if (m_HeroGuid[0].IsValid())
		{
			m_bHeroSetMatrix = true;
		}
	}
	X_VOID	HandlerNewHero(ObjectHero *pHero);
 
	//今日参战英雄
	const X_INT*	GetHeroTableID() const { return m_HeroTableID; }
	X_VOID			SetHeroTableID(const X_INT* pHero);
 
	X_INT			GetLeftTime() const	{return m_LeftTime;}
	X_VOID			SetLeftTime(X_INT val)	{m_LeftTime = val; }
	
	X_VOID				SetTotalWood(X_INT wood) {m_TotalWood = wood;}
	X_VOID				SetQuJingDay(X_INT day) {m_QuJingDay = day;}
	X_VOID				SetTotalExp(X_INT exp) {m_exp = exp;}

	X_VOID				SetQujingData(GCOpenQuJingUIPacket* pPacket);
	X_VOID				upDataQujingData(GCQuJingHuSongBroadPacket* pPacket);

	QuJingPlayerData*	findPlayerDataByData(X_CLIENT_GUID guid);

	static const stDBC_FILE_QUJING  * getTableDataById(X_INT id);


	const vector <QuJingPlayerData*>& getPlayers(){ return m_pData;}

	bool	  isQuJingHeroGet();
 
	X_VOID    autoHeroMatrix();

	bool  getPlayerSprite(QuJingPlayerData* pPlayer,int& id);
	int   getCanUseIndex( );
    int  RemovePlayerDataByData(X_CLIENT_GUID guid);

	enum        EM_PRIZR_TYPE
	{
		EM_TYPE_HUSONG,
		EM_TYPE_QJ,
	};
	//--------------------------------------
	EM_PRIZR_TYPE				GetType() const {return m_type;}
	X_VOID				SetType(X_INT type) {m_type =EM_PRIZR_TYPE(type) ;}


	bool			 IsGetAllHeros();
	bool			 IsCanQujing();
	bool			 IsCanQujingForLevel(X_INT & needLevel);
protected:
	 
	X_INT		m_CurrentHuSongID;					//当前护送ID
	X_INT		m_HuSongTimes;						//今天可护送次数
	X_INT		m_RobTimes;							//今天可打劫次数
	X_INT		m_RobCDTime;						//今天打劫冷却时间
	X_GUID		m_HeroGuid[MAX_MATRIX_CELL_COUNT];	//阵法对象
	X_INT		m_LeftTime;

	X_INT		m_QuJingDay;
	vector <QuJingPlayerData*>  m_pData;

	X_INT     m_HeroTableID[MAX_MATRIX_CELL_COUNT];

	
	bool      isInQuJingHeroTable(X_INT ID);
	vector<ObjectHero*> m_heroes;
	bool      m_bHeroSetMatrix;
	//-----------------------------------------------
	X_INT		m_TotalWood;
	X_INT		m_exp;

	EM_PRIZR_TYPE m_type;
	bool	   bGetAllHero;
	bool	   m_bCanQujing;
};

 


#endif
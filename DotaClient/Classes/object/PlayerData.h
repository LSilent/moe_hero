#ifndef __PLAYERDATA_H__
#define __PLAYERDATA_H__
#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"

class ObjectHero;
class  PlayerData
{
public:
	PlayerData();
	~PlayerData();
	X_VOID Initial();
	X_VOID Release();
 

public:
	
	X_VOID setName(string strId);

	string getName();
	
	X_SHORT			GetLevel() const{return m_Level;}
	X_VOID			SetLevel(X_SHORT level);
	 

	X_SHORT			GetVipLevel() const {return m_VipLevel;}
	X_VOID			SetVipLevel(X_SHORT val) {m_VipLevel = val;}

	X_UINT			GetExp() const {return m_Exp;}
	X_VOID			SetExp(X_UINT exp) {m_Exp = exp;}

	X_UINT			GetVipExp() const {return m_VipExp;}
	X_VOID			SetVipExp(X_UINT val) {m_VipExp = val;}

	//X_UINT			GetMoney() const {return m_Money;}
	//X_VOID			SetMoney(X_UINT money) {m_Money = money;}

	X_UINT			GetGold() const {return m_Gold;}
	X_VOID			SetGold(X_UINT gold) {m_Gold = gold;}
 
	X_INT			GetWood() const {return m_Wood;}
	X_VOID			SetWood(X_INT wood) 
	{
		m_Wood = wood; 
	}

	X_UINT			GetGem() const {return m_Gems;}
	X_VOID			SetGem(X_UINT stone) 
	{
		m_Gems = stone; 
	}

	X_SHORT			GetTodayActivity() const { return m_DayActivity; }
	X_VOID			SetTodayActivity(X_SHORT val) { m_DayActivity= val;}

	X_UINT			GetMonthActivity() const { return m_MonthActivity; }
	X_VOID			SetMonthActivity(X_UINT val) { m_MonthActivity= val;}

	X_UINT			GetStateFlag() const {return m_StateFlag; }
	X_VOID			SetStateFlag(X_UINT state) {m_StateFlag = state;}
	
	X_INT			GetActionPoint() const { return m_ActionPoint; }
	X_VOID			SetActionPoint(X_INT val) { m_ActionPoint = val;}

	X_INT			GetMaxActionPoint() const { return 200; }

	X_INT				GetMaxExpWithLevel(X_INT level = -1) const;

	X_INT			GetRecruitHeroCount() const {return m_RecruitHeroCount;}
	X_VOID			SetRecruitHeroCount(X_INT val) 
	{
		m_RecruitHeroCount = val;
	}
	X_UINT			GetRecruitRefreshLefttime() const 
	{
		return		m_RecruitRefreshLefttime;
	
	}
	X_VOID			SetRecruitRefreshLefttime(X_INT val) 
	{
		if (val <= 0)
		{
			val= 0;
		}
		m_RecruitRefreshLefttime = val; 
	}
	const vector<ObjectHero*> &	 GetFightHero()  const ;
	X_VOID			 SetFightHero(const X_GUID* pHeroArray); 


	X_INT			GetBearPoint() const {return m_BearPoint;}
	X_VOID			SetBearPoint(X_INT val) 
	{
		m_BearPoint = val; 
		 
	}
	X_INT			GetMaxCopySceneGroupID() const { return m_SceneGroup; }
	X_VOID			SetMaxCopySceneGroupID(X_INT val);
	X_VOID			SetSacrificeID(X_INT val);
	X_INT			GetSacrificeID() const { return m_SacrificeID; }

	X_INT			GetSacrificeDamage() const { return m_SacrificeDamage; }
	X_VOID			SetSacrificeDamage(X_INT val);
	X_BOOL			SetSacrificeAward(X_INT index, X_INT itemid); 
	X_INT			GetSacrificeAward(X_INT index); 
	X_INT           GetMatrixHeroNum()const{return m_MatrixHeroNum;}

	X_INT			GetBuyBearPointCount() const { return m_BuyBearPointCount; }
	X_VOID			SetBuyBearPointCount(X_INT val)
	{
		m_BuyBearPointCount = val;
	}
	bool			IsLevelUp(){ return bLevelUp;}
	X_VOID			resetLevelUp(){   bLevelUp = false;}

	X_INT			GetBuyAcNum() const {return m_BuyAcNum;}
	X_VOID			SetBuyAcNum(X_INT val) 
	{
		m_BuyAcNum = val; 

	}
	X_INT			GetFreeRefreshNum() const {return m_FreeRefreshNum;}
	X_VOID			SetFreeRefreshNum(X_INT val) 
	{
		m_FreeRefreshNum = val; 

	}
	X_INT			GetChargeMoney() const{return m_Money;}
	X_VOID			SetChargeMoney(X_INT Money)
	{
		m_Money = Money;
	}
	X_CLIENT_GUID			GetGoddessHeroGuid() const { return m_GoddessHeroGuid; }
	X_VOID			SetGoddessHeroGuid(X_GUID val)
	{
		m_GoddessHeroGuid = val.GetValue();
		 
	}

	X_INT			GetRockLeftTimes() const { return m_RockLeftTimes; }
	X_VOID			SetRockLeftTimes(X_INT val) 
	{ 
		m_RockLeftTimes = val; 
		 
	}

	X_INT			GetRockTimes() const { return m_RockTimes; }
	X_VOID			SetRockTimes(X_INT val) 
	{ 
		m_RockTimes = val; 
		 
	}

private:
	//string		m_Name;	
	X_CHAR			m_Name[MAX_CHARACTER_NAME];	//玩家名称
	X_SHORT		m_Level;			
	X_SHORT		m_VipLevel;			
	X_UINT		m_Exp;
	X_UINT		m_VipExp;
	//X_UINT			m_Money;
	X_UINT			m_Gold;
	X_INT			m_Wood;
	X_UINT			m_Gems;
 
	X_SHORT			m_DayActivity;
	X_UINT			m_MonthActivity;
	X_UINT			m_StateFlag;
	//行动力
	X_INT		m_ActionPoint;
	//行动力随等级增长系数
	X_INT		m_ActionPointFactor;
	X_INT       m_RecruitHeroCount;
	X_UINT		m_RecruitRefreshLefttime;
	X_INT		m_FreeRefreshNum;

	vector<ObjectHero*> m_MatrixObj;//阵法上英雄
	X_INT       m_MatrixHeroNum;
	X_INT		m_BearPoint;
	X_INT       m_SceneGroup;
	//献祭id
	X_INT		m_SacrificeID;
	//献祭伤害
	X_INT		m_SacrificeDamage;
	X_INT       m_SacrificeAward[MAX_SACRIFICE_RECENT_AWARDITEM_COUNT];
	X_INT		m_BuyBearPointCount;
	bool		bLevelUp;
	static      bool bFlag;;
	X_INT      m_BuyAcNum;
	X_INT	   m_Money;
	X_CLIENT_GUID m_GoddessHeroGuid;
	X_INT m_RockLeftTimes;
	X_INT m_RockTimes;
};


#endif // __PLAYERDATA_H__

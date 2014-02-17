#ifndef __WOODDATA_H__
#define __WOODDATA_H__

#include "./base/Global.h"
#include "./GameStruct.h"
#include "object/ObjectHero.h"
#include "DataPool.h"
#include <assert.h>


class SelfWoodData
{
public:
	SelfWoodData();
	~SelfWoodData();
	X_VOID HandleData(const cMyWoodData*  source);

	ObjectHero*     GetSelfMatrixDefHero(X_INT pos)
	{
		assert(pos >= 0  && pos < MAX_MATRIX_CELL_COUNT);
		return m_SefDefWoodHeros[pos];
	}
	ObjectHero*     GetSelfDefHero(){return m_DefHero;}
	X_BOOL          HeroIsDefWood(const ObjectHero* pHero);
	X_VOID          Tick(X_UINT nTime)
	{
		if (m_IsLevelUping)
		{
			m_WoodData.m_LevelUpRemainTime -= nTime;
		}
		if (m_nRobCD > 0)
		{
			m_nRobCD  -= nTime;
		}else
		{
			m_nRobCD = 0;
		}

		if (m_nSafeCD > 0)
		{
			m_nSafeCD  -= nTime;
		}
		else
		{
			m_nSafeCD = 0;
		}

	}
	X_INT	GetRobCD() const { return m_nRobCD; }
	X_VOID	SetRobCD(X_INT val) { m_nRobCD = val; }

	X_INT	GetSafeCD() const { return m_nSafeCD; }
	X_VOID	SetSafeCD(X_INT val) { m_nSafeCD = val; }
private:
	X_VOID			HandleSelfMatrixDefHeros();
public:
	cMyWoodData      m_WoodData;
	X_INT			 m_WoodCreat;
	X_INT			 m_RequiredLevel;
	X_INT			 m_RequiredMoney;
	X_INT			 m_RequiredTime;
	X_INT			 m_WoodCapacity;
	X_CLIENT_GUID	 m_DefenceHeroID;
	ObjectHero*      m_SefDefWoodHeros[MAX_MATRIX_CELL_COUNT];
	ObjectHero*      m_DefHero;
	X_BOOL			 m_IsLevelUping;

	X_INT		m_nRobCD; //s
	X_INT		m_nSafeCD; //s

	
};

class WoodsData
{
public:
	WoodsData();
	~WoodsData();
	X_VOID Initial();
	X_VOID Release();
	X_VOID HandleRobData(const cRobWoodData* source);

	SelfWoodData* GetSelfWoodData() const { return m_pSelfWoodData; }
	cRobWoodData* GetRobWoodData() const {return m_pRobWoodData;}

	X_INT	GetPriceWood() const { return m_PriceWood; }
	X_VOID  SetPriceWood(X_INT val) { m_PriceWood = val; }

	X_VOID  Tick(X_UINT nTime)
	{
		if(m_pSelfWoodData != NULL)
		{
			m_pSelfWoodData->Tick(nTime);
		}

	}
	
	ObjectHero*  GetOtherDefHero(){return m_OtherDefHero;}
private:
	X_VOID			HandleOtherMatrixDefHeros();
private:

	//自己的伐木场数据
	SelfWoodData*		m_pSelfWoodData;


	//敌人的伐木场数据
	cRobWoodData*    	m_pRobWoodData;
	ObjectHero*         m_OtherDefHero;

	//得到的奖励
	X_INT				m_PriceWood;

	 
};



#endif  //__WOODDATA_H__
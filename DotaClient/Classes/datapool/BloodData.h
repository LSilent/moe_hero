#ifndef __BLOODDATA_H__
#define __BLOODDATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"
#include "./GameObjectDefine.h"
#include "./GameStruct.h"
 
 
 class GCStairPlusPacket;
 class GCStairRetEnterPacket;
 class GCStairMonsterGroupPacket;


 class  BattleLayer
 {
 public:
	  BattleLayer();
	 ~ BattleLayer();
	 X_VOID CleanUp();

 public:

	 X_INT			m_Layer;								//当前层
	 X_INT			m_AccStar;								//获得星
	 X_INT			m_CurStar;								//剩余得星
	 X_INT			m_NextPlusLayers;						//剩余加成场次
	 X_INT			m_PlusAtt;								//攻加成
	 X_INT			m_PlusDef;								//防加成
	 X_INT			m_PlusHp;								//血加成
	 StairMonster	m_MonsterGroup[MAX_STAIR_MONSER_GROUP];	//怪物组
	 X_INT			m_MaxTotalStar;							//最高累计得星
	 X_INT			m_MaxPassLayers;						//最高通过层数


 };

  

class BloodData
{
public:
	X_VOID Initial();
	X_VOID Release();
 
public:
	//--------------enter界面---------------------------------
	X_INT				GetTimes(){return m_Times;}
	X_INT				GetLeftTimes(){return m_LeftTimes;}
	X_INT				GetLayer(){return m_Layer;}
	X_INT				GetMaxTotalStar(){return m_MaxTotalStar;}
	X_INT				GetMaxPassLayers(){return m_MaxPassLayers;}
	//-------buffer界面------------------------------------------
	
	X_BOOL   isBegin(){ return m_Begin;}
	X_INT *  getCostStar(){ return m_Star;}
	X_INT *  getBufferPlus(){ return m_Plus;}

	//-------------------------------------------------------------------
	BattleLayer * getLayerMonster()
	{
		return m_pLayer;
	}

public:
	 
	 X_VOID handleStairPlusPacket(GCStairPlusPacket* pPacket);

	 X_VOID handleStairEnterPacket(GCStairRetEnterPacket* pPacket);
	 
	 X_VOID handleMonsterPacket(GCStairMonsterGroupPacket* pPacket);
	 
	 X_INT				GetStar(){return m_AwardStar;}
	 X_VOID				SetStar(X_INT val){m_AwardStar = val;}
	 X_INT				GetExp(){return m_AwardExp;}
	 X_VOID				SetExp(X_INT val){m_AwardExp = val;}
	 X_INT				GetItemID(){return m_AwardItemID;}
	 X_VOID				SetItemID(X_INT val){m_AwardItemID = val;}



 
	X_VOID  NextStep();

	X_VOID HanlderBufferSelect()
	{
		m_BufferComingNum -- ;
		NextStep();
	}

	X_VOID  EnterBloodUi();
	bool isBattleNextOk(){ return m_BattleNextOk;}
	X_VOID setBattleNextOk(bool b ){   m_BattleNextOk = b;}
protected:
 
	X_INT			m_Times;								//闯关次数
	X_INT			m_LeftTimes;							//剩余次数
	X_INT			m_Layer;								//当前层
	X_INT			m_MaxTotalStar;							//最高累计得星
	X_INT			m_MaxPassLayers;						//最高通过层数

	//-------------------------------------------------------------------------------------------------
	X_BOOL	m_Begin;						//true 活动开始加成 不消耗积分  false 每3层额外奖励加成 
	X_INT	m_Star[STAIR_PLUS_COUNT];		//消耗积分	 数组下标0为攻、1为防、2为血
	X_INT	m_Plus[STAIR_PLUS_COUNT];		//加成

	X_INT   m_BufferComingNum;
	//-------------------------------------------------------------------------------------------------

	BattleLayer *m_pLayer;
	//----------------------奖励

	X_INT	m_AwardStar;			//获得得分
	X_INT	m_AwardExp;		//获得召唤师经验
	X_INT	m_AwardItemID;		//获得物品
	bool    m_BattleNextOk;
};
#endif
#ifndef __BATTLEDATA_H__
#define __BATTLEDATA_H__

#include "./base/Global.h"
#include "./Packets/Fight/GCFightInfoPacket.h"
#include "./datapool/BattleInfo.h"
class BattleObject
{
 
public:
	X_CLIENT_GUID	m_Guid;//对象guid

	X_VOID CleanUp()
	{
		m_Guid = INVALID_INDEX;
		m_TableID = INVALID_INDEX;
		m_Profession = -1;
		m_Level = -1;
		m_MatrixID = -1;
		m_free = true;
		m_bMonster = false;
		m_Info = X_NULL;
		m_index = -1;
		X_INT size = m_ImpactInfo.size();
		for (X_INT i = 0;i<size;i++)
		{
			SAFE_DELETE(m_ImpactInfo[i]);
		}
		m_ImpactInfo.clear();
		m_ImpactHurt.clear();
		m_bAttacker = true;
		bCreateDeadFlag = false;
	}
	//默认表示 人 
	X_VOID SetData(const cFObjectData & data,bool bMonster = false);
	X_VOID SetRoundInfo(const cFObjectInfo* Info,const cFObjectInfo* _NextInfo);
	X_VOID SetFree(bool free);
	bool isFree( );

	X_INT GetNextFightDistance();

//---------------------------------------外部使用------------------------------
	//----------- 静态数据
	std::string GetSmallIcon()const;
	std::string GetHeadIcon()const;
	std::string GetBody()const;
	X_INT	GetLevel();
	X_CHAR	GetProfession();
	X_INT	GetPosition();
	X_INT	GetIndex()                  { return m_index; }

	X_INT	GetQuality();
	X_INT	GetColor();
	//------------------每回合前基本数据

	X_INT	GetHP();//血量
	X_INT	GetMP();//魔法值
	X_INT	GetMaxHP();//血量
	X_INT	GetMaxMP();//魔法值

	X_INT	GetFightDistance();	//战斗条长度
	X_INT	GetAttackSpeed();	//攻击速度
	const vector<Impact *>& GetImpact();//身上impact
	const vector<int>& GetImpactHurt();//持续impact伤害
	const vector<int>& GetMagicDelta();//magic 变化
  
	//---------------------------------------外部使用------------------------------

	bool   isMonster();// 防守方 是人还是怪物
	bool   isAttacker()                { return m_bAttacker; }  //是否攻击方

	bool   bCreateDeadFlag;
protected:
	friend class BattleObjectPool;
//---------------------------------------------------------动态数据

	//当前回合数据
	const cFObjectInfo* m_Info;
	vector<Impact *> m_ImpactInfo;
	vector<int> m_ImpactHurt;
	vector<int> m_magicDelta;
	//下一回合数据
	const cFObjectInfo* m_NextInfo;

//---------------------------------------------------------
	
	X_INT		m_TableID;//表格id
	X_CHAR		m_Profession;//职业
	X_INT		m_Level;//等级
	X_INT		m_MatrixID;//位置	
	bool		m_free;
	bool		m_bMonster;
	bool		m_bAttacker;//是否攻击方
	X_CHAR*		m_icon;
    X_INT       m_index;
	X_INT		m_Quality;
	X_INT		m_Color;
};

class BattleObjectPool
{
	friend class BattleData;
public:
	 X_VOID Init();
	 X_VOID Release();
	 X_VOID PrepareFighter(const cFightInfo* info );
	 X_VOID DestroyBattleData();
	 BattleObject* FindFighterByGUID(const X_GUID& guid);
protected:
	  BattleObject* __GetFighter();

	  BattleObject* __FindAttackFighterByGUID(const X_GUID& guid);
	  BattleObject* __FindDefenseFighterByGUID(const X_GUID& guid);

private:
	vector<BattleObject*> m_Attack;
	vector<BattleObject*> m_Defense;
	vector<BattleObject*> m_Fighter;
};
 
class BattleData
{
public:
 
	X_VOID Initial();
	X_VOID Release();

	//准备战斗数据
	X_VOID PrepareData(const cFightInfo* info );
	//关闭战斗 要调用
	X_VOID DestroyBattleData();


	//----------------------------------------------------------
	//调用tickRound 后 getAttack getDefense取双方数据
	bool tickRound();

	const vector<BattleObject*>& getAttack(){return m_pool->m_Attack;};
	const vector<BattleObject*>& getDefense(){return m_pool->m_Defense;};

	const vector<const cAttackInfo *>& 	getRoundAttackData();
	 BattleObject* FindFighterByGUID(const X_GUID& guid);

	 X_INT	GetMaxFightDistance()
	 {
		 if (m_info)
		 {
			 return m_info->m_MaxFightDistance;
		 }
		 return 1;
		 
	 }
	//--------------------------是否胜利
	bool isWin();
	//--------------------------获得回合数
	X_INT GetRound();

	void ResetRound()
	{
		m_curRound =0;
	}
	 X_INT GetcurRound();
protected:
	BattleObjectPool *m_pool;
	const cFightInfo* m_info;
	vector<const cAttackInfo *> m_AttackInfo;
	X_INT m_curRound;
};

#endif
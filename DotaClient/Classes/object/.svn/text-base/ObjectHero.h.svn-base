#ifndef __OBJECTHERO_H__
#define __OBJECTHERO_H__
#include "./base/Global.h"
#include "./object/Object.h"
#include "./DataBase/DataBaseSystem.h"
#include "./HeroDB.h"

class ObjectFactory;
class ItemEquip;
class ObjectSkill;
class  ObjectHero :public Object
{
protected:
	ObjectHero(X_CLIENT_GUID guid);
	virtual ~ObjectHero();

	friend class ObjectPlayer;
	friend class ObjectSelf;
	friend class ObjectManager;
public:

	static ObjectFactory * __getFactory(); 
	class Factory;
	X_VOID Initial();
	virtual X_VOID Release();

	EM_HERO_CONTAINER_TYPE	GetContainerType()const;
	X_VOID				SetContainerType(EM_HERO_CONTAINER_TYPE val);

	X_INT				GetPos() const;
	X_VOID				SetPos(X_INT val);

	X_INT				GetTableID() const;
	bool			SetTableID(X_INT val);

	X_INT				GetLevel() const;
	X_VOID				SetLevel(X_INT val);

	X_INT				GetExp() const;
	X_VOID				SetExp(X_INT val);

	X_INT				GetGrowRate() const;
	X_VOID				SetGrowRate(X_INT val);

	X_INT				GetBearPoint() const ;
	X_VOID				SetBearPoint(X_INT val);

	X_INT				GetMaxBearPoint()const;		

	//X_VOID				SetAllocationPoint(X_INT val);
	//X_INT				GetAllocationPoint();

	EM_HERO_QUALITY_TYPE GetQuality() const;
	X_VOID				SetQuality(EM_HERO_QUALITY_TYPE val);

	X_UINT				GetStatus() const;
	X_VOID				SetStatus(X_UINT val);

	X_INT				GetPhysicAttack() const;
	X_VOID				SetPhysicAttack(X_INT val);

	X_INT				GetMagicAttack() const;
	X_VOID				SetMagicAttack(X_INT val);

	X_INT				GetPhysicDefence() const;
	X_VOID				SetPhysicDefence(X_INT val);

	X_INT				GetMagicDefence() const;
	X_VOID				SetMagicDefence(X_INT val);

	X_INT				GetHP() const;
	X_VOID				SetHP(X_INT val) ;

	X_INT				GetMaxHP() const;
	X_VOID				SetMaxHP(X_INT val);

	X_INT				GetMP() const ;
	X_VOID				SetMP(X_INT val) ;

	X_INT				GetMaxMP() const;
	X_VOID				SetMaxMP(X_INT val) ;

	X_INT				GetHit() const ;
	X_VOID				SetHit(X_INT val) ;

	X_INT				GetDodge() const;
	X_VOID				SetDodge(X_INT val) ;

	X_INT				GetSkillCount() const ;
	X_VOID				SetSkillCount(X_INT val);

	ObjectSkill*				GetSkill(X_INT index)const; 
	 
	X_VOID				SetSkill(X_INT index, X_INT val);
	 
	ItemEquip*	 GetEquip(X_INT index)const; 
	 
	X_VOID	 SetEquip(X_INT index, X_CLIENT_GUID val,bool self = true); 

	bool	 ISEquiped(const ItemEquip* pItem)const; 

	bool	 ISEquipedByTableID(const ItemEquip* pItem)const; 
	const stDBC_FILE_HERO_ATTR*  getTableData()const
	{
		return m_pTableData;
	}
	
	std::string GetHeadIcon()const;
	std::string GetBody()const;

	std::string GetRecruitIcon()const;

	std::string GetName()const;

	std::string GetDesc()const;

	X_INT				GetMaxExpWithLevel(X_INT level = -1) const;

	// 招募英雄是否是魂魄
	X_BOOL			 HeroIsSprite()const;
	// 招募英雄是否可以招募
	X_BOOL			 HeroCanRecruit()const;

	X_VOID			 setServerData(const HeroAttrData*	pData,bool self );

	bool IsTop() const;

	//得到附加的攻击 防御
	X_INT   getEquipAddAttack() ;
    X_INT   getEquipAddDefense() ;
	X_INT   getEquipAddMP() ;
	X_INT   getEquipAddHP() ;
	X_INT   getEquipAddSpeed() ;
	static const string getIconById( X_INT id);

	X_INT				GetEquipUsedBearPoint() const ;
	bool				IsDataReady()const {return m_dataok;}
	X_VOID				SetDataReady()  { m_dataok = true;}


	EM_HERO_COLOR_TYPE	GetColor() const {
		
		if (m_Color <=  EM_HERO_COLOR_TYPE6 && m_Color>=  EM_HERO_COLOR_TYPE1)
		{
			return m_Color;
		}
		
		return EM_HERO_COLOR_TYPE1;
	
	}
	X_VOID				SetColor(EM_HERO_COLOR_TYPE val) { m_Color = val;}

	string              getHeroColor()const;

	bool IsSkillMasterSchool() const;

	bool isWoodHero();
protected:
	EM_HERO_COLOR_TYPE m_Color;
	ATTACK_RANGE m_AR_Type;
	X_INT		m_TableID;					//Hero表中的id
	X_UCHAR		m_ContainerType;			//容器类型
	X_INT		m_Pos;						//容器中位置
	X_INT		m_Level;					//等级
	X_INT		m_Exp;						//经验
	X_INT		m_GrowRate;					//成长
	X_INT		m_BearPoint;				//负重
	X_INT		m_Quality;					//品质
	X_UINT		m_Status;					//武将状态
	X_INT		m_PhysicAttack;				//物理攻击
	X_INT		m_MagicAttack;				//魔法攻击
	X_INT		m_PhysicDefence;			//物理防御
	X_INT		m_MagicDefence;				//魔法防御
	X_INT		m_HP;						//生命值
	X_INT		m_MaxHP;					//
	X_INT		m_MP;						//魔法值
	X_INT		m_MaxMP;
	X_INT		m_Hit;						//命中值
	X_INT		m_Dodge;					//闪避值
	X_INT		m_SkillCount;				//技能数量
 	
	X_INT		m_BearPointMax;
	vector<ObjectSkill*> m_Skill; //技能列表
	vector<ItemEquip *> m_Equip;//装备

	const stDBC_FILE_HERO_ATTR* m_pTableData;

	//X_INT		m_AllocationPoint;//分配点数

	 X_INT      m_addAttack;
	 X_INT      m_addDefence;
	 X_INT      m_addMP;
	 X_INT      m_addHP;
	 X_INT		m_addSpeed;
	bool	   m_dirty;
	X_VOID     __CalculateEquipAdd();
	bool       m_dataok;
	X_VOID	   _changeBearPointMax();

};
 
#endif // __PLAYERHERODATA_H__

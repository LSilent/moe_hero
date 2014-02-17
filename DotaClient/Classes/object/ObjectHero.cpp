#include "./object/ObjectHero.h"
#include "./object/ObjectFactory.h"
#include "./GameUtil.h"
#include "./datapool/DataPool.h"
#include "./object/ItemEquip.h"
#include "./object/ObjectSkill.h"
#include "./game/GameHelper.h"
class ObjectHero::Factory : public ObjectFactory
{
public:

	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_HERO;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectHero(guid);
	}


};
ObjectFactory * ObjectHero::__getFactory()
{
	static Factory factory;
	return &factory;
}


ObjectHero::ObjectHero(X_CLIENT_GUID guid)
{
	m_Guid = guid;
	Initial();

}
ObjectHero::~ObjectHero()
{

}
X_VOID ObjectHero::Initial()
{
	m_Equip.resize(MAX_EQUIP_NUM_PER_HERO,X_NULL);
	m_Skill.resize(MAX_SKILL_NUM,X_NULL);
	m_BearPointMax = 0;
	m_dirty = true;
	m_Color = EM_HERO_COLOR_TYPE1;
	m_dataok = false;
	m_Level = 1;
	m_Quality = EM_HERO_QUALITY_TYPE1;
}
X_VOID ObjectHero::Release()
{
	X_UINT size = m_Equip.size();
	for (X_UINT i = 0;i<size;i++)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyItem(m_Equip[i]);
	}
	size = m_Skill.size();
	for (X_UINT i = 0;i<size;i++)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyObject(m_Skill[i]);
	}
	m_Equip.clear();
	m_Skill.clear();
    m_pTableData = X_NULL;
	m_dataok = false;
	m_dirty = true;
}
bool	 ObjectHero::SetTableID(X_INT val) 
{
	m_pTableData = X_NULL;
	m_TableID = val;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
	if (pDataFile)
		m_pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByIndexKey(m_TableID);
	if (!m_pTableData)
	{
		return false;
	}
	SetLevel(m_pTableData->_initlevel);//等级
	SetExp(m_pTableData->_exp);//经验
	SetQuality( EM_HERO_QUALITY_TYPE(m_pTableData->_quality));//品质
	SetPhysicAttack( m_pTableData->_attack);//物理攻击
	SetMagicAttack(m_pTableData->_magicAttack);//魔法攻击
	SetPhysicDefence(m_pTableData->_defense);//物理防御
	SetMagicDefence(m_pTableData->_magicDefense);//魔法防御
	SetHP(m_pTableData->_hp);//生命值
	SetMaxHP(m_pTableData->_hp);
	SetMP(m_pTableData->_mp);//魔法值
	SetMaxMP(m_pTableData->_mp);
	SetHit(m_pTableData->_hit);//命中值
	SetDodge(m_pTableData->_dodge);//闪避值
 	SetGrowRate(m_pTableData->_growupLimit);	//成长		
	SetBearPoint(m_pTableData->_burden);	//负重
	SetSkillCount(2);
	SetSkill(0,m_pTableData->_skill1);
	SetSkill(1,m_pTableData->_skill2);
	m_dirty = true;
	return true;
}

	EM_HERO_CONTAINER_TYPE	ObjectHero::GetContainerType() const
	{
		return (EM_HERO_CONTAINER_TYPE)m_ContainerType;
	}
	X_VOID				ObjectHero::SetContainerType(EM_HERO_CONTAINER_TYPE val) {m_ContainerType = (X_UCHAR)val;}

	X_INT				ObjectHero::GetPos() const{return m_Pos;}
	X_VOID				ObjectHero::SetPos(X_INT val) {m_Pos = val;}

	X_INT				ObjectHero::GetTableID() const {return m_TableID;}
	 

	X_INT				ObjectHero::GetLevel() const {return m_Level;}
	X_VOID				ObjectHero::SetLevel(X_INT val)
	{
		m_Level = val;
		_changeBearPointMax();

	}

	X_INT				ObjectHero::GetExp() const {return m_Exp;}
	X_VOID				ObjectHero::SetExp(X_INT val) {m_Exp = val;}

	X_INT				ObjectHero::GetGrowRate() const {return m_GrowRate;}
	X_VOID				ObjectHero::SetGrowRate(X_INT val) {m_GrowRate = val;}

	X_INT				ObjectHero::GetBearPoint() const {return m_BearPoint;}
	X_VOID				ObjectHero::SetBearPoint(X_INT val) {m_BearPoint = val;}

	X_INT				ObjectHero::GetMaxBearPoint()const
	{
		return m_BearPointMax;
	}

	/*X_VOID				ObjectHero::SetAllocationPoint(X_INT val)
	{
		m_AllocationPoint = val;
	}
	X_INT				ObjectHero::GetAllocationPoint()
	{
		return m_AllocationPoint;
	}*/

	EM_HERO_QUALITY_TYPE ObjectHero::GetQuality() const 
	{
		if (m_Quality < EM_HERO_QUALITY_TYPE1 ||m_Quality > EM_HERO_QUALITY_TYPE6 )
		{
			return EM_HERO_QUALITY_TYPE1;
		}
		return (EM_HERO_QUALITY_TYPE)m_Quality;
			
	}
	X_VOID				ObjectHero::SetQuality(EM_HERO_QUALITY_TYPE val)
	{
		m_Quality = (X_INT)val;
		_changeBearPointMax();
	 
	}
	X_VOID	   ObjectHero::_changeBearPointMax()
	{
		m_BearPointMax = 0;
		if (m_Quality < EM_HERO_QUALITY_TYPE1 || m_Quality > EM_HERO_QUALITY_TYPE6)
		{
			return;
		}
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_EXP);
		if (pDataFile)
		{
			const stDBC_FILE_HERO_EXP* m_pTableData = (const stDBC_FILE_HERO_EXP*)pDataFile->GetFieldsByIndexKey(m_Level);
			if (m_pTableData)
			{
					m_BearPointMax = m_pTableData->BearPoint[m_Quality - EM_HERO_QUALITY_TYPE1];
			}
		}
	}
	X_UINT				ObjectHero::GetStatus() const {return m_Status;}
	X_VOID				ObjectHero::SetStatus(X_UINT val) {m_Status = val;}

	X_INT				ObjectHero::GetPhysicAttack() const {return m_PhysicAttack;}
	X_VOID				ObjectHero::SetPhysicAttack(X_INT val) {m_PhysicAttack = val;}

	X_INT				ObjectHero::GetMagicAttack() const {return m_MagicAttack;}
	X_VOID				ObjectHero::SetMagicAttack(X_INT val) {m_MagicAttack = val; }

	X_INT				ObjectHero::GetPhysicDefence() const {return m_PhysicDefence;}
	X_VOID				ObjectHero::SetPhysicDefence(X_INT val) {m_PhysicDefence = val;}

	X_INT				ObjectHero::GetMagicDefence() const {return m_MagicDefence;}
	X_VOID				ObjectHero::SetMagicDefence(X_INT val) {m_MagicDefence = val;}

	X_INT				ObjectHero::GetHP() const {return m_HP;}
	X_VOID				ObjectHero::SetHP(X_INT val) {m_HP = val;}

	X_INT				ObjectHero::GetMaxHP() const {return m_MaxHP;}
	X_VOID				ObjectHero::SetMaxHP(X_INT val) {m_MaxHP = val;}

	X_INT				ObjectHero::GetMP() const {return m_MP;}
	X_VOID				ObjectHero::SetMP(X_INT val) {m_MP = val;}

	X_INT				ObjectHero::GetMaxMP() const {return m_MaxMP;}
	X_VOID				ObjectHero::SetMaxMP(X_INT val) {m_MaxMP = val;}

	X_INT				ObjectHero::GetHit() const {return m_Hit;}
	X_VOID				ObjectHero::SetHit(X_INT val) {m_Hit = val;}

	X_INT				ObjectHero::GetDodge() const {return m_Dodge;}
	X_VOID				ObjectHero::SetDodge(X_INT val) {m_Dodge = val;}

	X_INT				ObjectHero::GetSkillCount() const { return m_SkillCount; }
	X_VOID				ObjectHero::SetSkillCount(X_INT val) { m_SkillCount = val = 2;}
	ObjectSkill*				ObjectHero::GetSkill(X_INT index) const
	{
		if(index < 0 || index >= m_SkillCount) return X_NULL;
		return m_Skill[index];
	}
	X_VOID				ObjectHero::SetSkill(X_INT index, X_INT val)
	{ 
		if(index < 0 || index >= m_SkillCount) return;
		bool selSkill = false;
		if (m_Skill[index])
		{
			if (DataPool::GetSingleton()->GetSelectSkill() == m_Skill[index])
			{
				selSkill = true;
			}
			DataPool::GetSingleton()->getObjectManager()->DestroyObject(m_Skill[index]);
		}
		ObjectSkill* pSkill = static_cast<ObjectSkill *>(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_SKILL,INVALID_INDEX));
		bool b_OK = false;
		if (pSkill)
		{
			pSkill->setUserData(this);
			b_OK = pSkill->SetTableId(val);
		}
		if (!b_OK)
		{
			SAFE_DELETE(pSkill);
		}
		m_Skill[index] = pSkill;


		if (selSkill)
		{
			DataPool::GetSingleton()->SetSelectSkill(m_Skill[index] ); 
		}
	}
	ItemEquip*	 ObjectHero::GetEquip(X_INT index) const
	{ 
		if(index < 0 || index >= MAX_EQUIP_NUM_PER_HERO) return X_NULL;
		return m_Equip[index];
	}
	X_VOID	 ObjectHero::SetEquip(X_INT index, X_CLIENT_GUID val,bool self )
	{
		if(index < 0 || index >= MAX_EQUIP_NUM_PER_HERO) return ;
		ItemEquip *pItem  = X_NULL;
		if (val  != (X_ULLONG)INVALID_ID)   
		{
			if (self)
			{
				pItem = static_cast<ItemEquip *>(DataPool::GetSingleton()->getObjectManager()->FindItem(val));
			}else
			{
				pItem = static_cast<ItemEquip *>(DataPool::GetSingleton()->getObjectManager()->CreateItem(val,-1));
			}
		}
		m_Equip[index] = pItem;
		m_dirty = true; 
	}
	bool	 ObjectHero::ISEquiped(const ItemEquip* pItem)const
	{
		if (!pItem)return false;

			Item*	pEquip = X_NULL; 
			for (X_INT i = 0;i< MAX_EQUIP_NUM_PER_HERO;i++)
			{
				pEquip =   GetEquip(i);
				if (pEquip == pItem)
					return true;
			} 
			return false;
	}
	bool	 ObjectHero::ISEquipedByTableID(const ItemEquip* pItem)const
	{
		if (!pItem)return false;

		Item*	pEquip = X_NULL; 
		for (X_INT i = 0;i< MAX_EQUIP_NUM_PER_HERO;i++)
		{
			pEquip =   GetEquip(i);
			if(!pEquip)continue;
			if (pEquip->GetTableID() == pItem->GetTableID())
				return true;
		} 
		return false;
	}
	X_INT	ObjectHero::GetMaxExpWithLevel(X_INT level) const
	{
		X_INT id = level !=-1 ? level:m_Level;
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_EXP);
		if (pDataFile)
		{
			const stDBC_FILE_HERO_EXP* m_pTableData = (const stDBC_FILE_HERO_EXP*)pDataFile->GetFieldsByIndexKey(id);
			if (m_pTableData)
			{
				return m_pTableData->exp <= 0  ? 1: m_pTableData->exp;
			}
		}
		return 1;
	}

X_BOOL      ObjectHero::HeroIsSprite()const
{
	return	IsUpdateFlagSet(m_Status,EM_HERO_STATUS_CAN_GETSPIRIT); 
}

X_BOOL      ObjectHero::HeroCanRecruit()const
{
	return	IsUpdateFlagSet(m_Status,EM_HERO_STATUS_CAN_RECRUIT); 
}	
const string ObjectHero::getIconById( X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
	if (pDataFile)
	{
		const stDBC_FILE_HERO_ATTR* pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByIndexKey(id);
		if (pTableData)
		{
			string str  = "zhf_";
			return (str + pTableData->_icon);
		}
	}
	return "";
}
std::string ObjectHero::GetHeadIcon()const
{
	if (m_pTableData)
	{
		string str  = "zhf_";
		//str += m_pTableData->_icon;
		//return str.substr(0,str.length() - 3) +"png";
		return (str + m_pTableData->_icon);
	}
	return "";
}
std::string ObjectHero::GetBody()const
{
	if (m_pTableData)
	{
		string str  = "zhp_";
		str += m_pTableData->_icon;
		return str.substr(0,str.length() - 3) +"png";
	}
	return "";
}
std::string ObjectHero::GetRecruitIcon()const
{
	return GetBody();
}
std::string ObjectHero::GetName()const
{
	if (m_pTableData)
	{
		return m_pTableData->_name;
	}
	return "";
}

std::string ObjectHero::GetDesc()const
{
	if (m_pTableData)
	{
		return m_pTableData->_name;
	}
	return "";
}
bool ObjectHero::IsTop() const
{
	 return EM_HERO_QUALITY_TYPE5 == m_Quality;

}
 
X_VOID    ObjectHero::__CalculateEquipAdd()
{
	if (!m_dirty)return;

	X_UINT size = m_Equip.size();
	ItemEquip *pEquip = X_NULL;
	m_addAttack = 0;
	m_addDefence = 0;
	m_addHP = 0;
	m_addMP = 0;
	m_addSpeed = 0;
	for (X_UINT i = 0; i<size;i++)
	{
		pEquip =  m_Equip[i];
		if (pEquip)
		{
			m_addAttack += (pEquip->getAttack()+pEquip->getAddAttr(EM_ATTRIBUTE_PHYSICATTACK) ) ;
			m_addDefence += (pEquip->getDefense()+pEquip->getAddAttr(EM_ATTRIBUTE_PHYSICDEFENCE) ) ;
			m_addMP += (pEquip->getMP());
			m_addHP += (pEquip->getHP()+pEquip->getAddAttr(EM_ATTRIBUTE_MAXHP));
			m_addSpeed += (pEquip->getAddAttr(EM_ATTRIBUTE_ATTACKSPEED));
		}
	}
	m_dirty = false;
}
X_INT    ObjectHero::getEquipAddAttack() 
{
	__CalculateEquipAdd();
	return m_addAttack;
}
X_INT    ObjectHero::getEquipAddDefense() 
{
		__CalculateEquipAdd();
		return m_addDefence;
}
X_INT    ObjectHero::getEquipAddMP() 
{
	__CalculateEquipAdd();
		return m_addMP;
}
X_INT   ObjectHero::getEquipAddSpeed()
{
	__CalculateEquipAdd();
	return m_addSpeed;

}
X_INT   ObjectHero::getEquipAddHP() 
{
	__CalculateEquipAdd();
		return m_addHP;
}
X_VOID	ObjectHero::setServerData(const HeroAttrData*	pData,bool self )
{
	if (pData == X_NULL)
	{
		return;
	}
	SetTableID(pData->m_TableID);
	SetLevel(pData->m_Level);
	SetExp(pData->m_Exp);
	SetGrowRate(pData->m_GrowRate);
	SetBearPoint(pData->m_BearPoint);
	SetQuality(EM_HERO_QUALITY_TYPE(pData->m_Quality)); 
	SetStatus(pData->m_Status); 
	SetPhysicAttack(pData->m_PhysicAttack);
	SetMagicAttack(pData->m_MagicAttack);
	SetPhysicDefence(pData->m_PhysicDefence);
	SetMagicDefence(pData->m_MagicDefence);
	SetHP(pData->m_HP);
	SetMaxHP(pData->m_MaxHP);
	SetMP(pData->m_MP);
	SetMaxMP(pData->m_MaxMP);
	SetHit(pData->m_Hit);
	SetDodge(pData->m_Dodge);
	SetSkillCount(pData->m_SkillCount);
	for (X_INT i = 0; i< pData->m_SkillCount ;i++)
	{
		 SetSkill(i, pData->m_Skill[i]);
	}
	for (X_INT i = 0; i< MAX_EQUIP_NUM_PER_HERO ;i++)
	{
		 SetEquip(i, pData->m_Equip[i].GetValue(),self);
	}
	SetColor(EM_HERO_COLOR_TYPE(pData->m_Color));
    m_dataok = true;
}

X_INT	ObjectHero::GetEquipUsedBearPoint() const 
{
	X_INT count = 0;
	ItemEquip* pEquip   =X_NULL;
	for (X_INT i =0;i<MAX_EQUIP_NUM_PER_HERO;i++)
	{
		pEquip = m_Equip[i];
		if (pEquip)
		{
			count += pEquip->m_pTableData->_weight;
		}
	}
	return count;
}
string    ObjectHero::getHeroColor()const
{
	return GameHelper::GetHeroColorById(m_Color);
}
bool ObjectHero::IsSkillMasterSchool()const
{
	 bool b = false;

	for (X_INT i = 0;i<m_SkillCount;i++ )
	{
		if (!m_Skill[i])continue;;

		X_INT level = m_Skill[i]->GetLevel();
		if (level >= MAX_NORMAL_SKILL_LEVEL && level < MAX_SKILL_LEVEL)
		{
			return true;
		}
		 
	}
	return false;
}

bool ObjectHero::isWoodHero()
{
	if (m_pTableData)
	{
		return m_pTableData->_id >1000;
	}
	return false;

}
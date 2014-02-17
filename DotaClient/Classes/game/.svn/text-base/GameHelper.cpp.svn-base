#include "./game/GameHelper.h"
#include "./DataBase/DataBaseSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/ObjectManager.h"


X_INT  GameHelper::GetHeroExpByLevel(X_INT level)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_EXP);

	const stDBC_FILE_HERO_EXP	*m_pTableData = (const stDBC_FILE_HERO_EXP*)pDataFile->GetFieldsByIndexKey(level);

	if (m_pTableData)
	{
		return m_pTableData->exp;
	}
	return 0; 
}

bool   GameHelper::getBuyBearPointCost(X_INT id,X_UINT &cost,X_INT& level,X_INT& bearPoint)
{
	bearPoint = 0; level =0;cost = 0;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_BUYBEARPOINT);
	const stDBC_FILE_BUYBEARPOINT	*m_pTableData = (const stDBC_FILE_BUYBEARPOINT*)pDataFile->GetFieldsByIndexKey(id);
	if (m_pTableData)
	{
		cost = m_pTableData->cost < 0 ? 0 :  m_pTableData->cost;
		level = m_pTableData->level;
		bearPoint = m_pTableData->bearPoint;
		return true;
	}
	return false;
}
X_INT   GameHelper::getSkillLevelRate(const  ObjectSkill* pSkill , const vector<ItemCommon*>& items)
{
	X_INT size = items.size();
	if (!pSkill|| 0 ==size) return 0;
	X_INT skillRate = 100;
	 
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	if (pDataFile)
	{
		const stDBC_FILE_SKILL	*m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId()+1);
		if (m_pTableData)
		{
			skillRate = m_pTableData->_LearnRate;
		}
	}
 
	ItemCommon * item = X_NULL;

	X_INT skillGroupId = pSkill->GetTableId()/100;
	X_INT rate = 0;
	for (X_INT i =0 ;i<size;++i)
	{
		item = items.at(i);
		if (!item)continue;
		 if(skillGroupId == item->getSkillDoubleGroup())
		 {
			 rate += (2*item->getSkillRate());
		 }
		 else
		 {
			 rate += (item->getSkillRate());
		 }
	}

	rate *= (100.f/ skillRate);

	return rate;

}
string  GameHelper::GetHeroColorById(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_COLOR);
	const stDBC_FILE_HERO_COLOR	*m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByIndexKey(id);
	if (m_pTableData)
	{
		 return m_pTableData->color;
	}
	m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(0);
	if (m_pTableData)
	{
		return m_pTableData->color;
	}
	return "";
}
string  GameHelper::GetHeroFrameColorById(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_COLOR);
	const stDBC_FILE_HERO_COLOR	*m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByIndexKey(id);
	if (m_pTableData)
	{
		return m_pTableData->framecolor;
	}
	m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(0);
	if (m_pTableData)
	{
		return m_pTableData->framecolor;
	}
	return "";
}
string  GameHelper::GetHeroFighterColorById(X_INT id)
{

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_COLOR);
	const stDBC_FILE_HERO_COLOR	*m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByIndexKey(id);
	if (m_pTableData)
	{
		return m_pTableData->fightercolor;
	}
	m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(0);
	if (m_pTableData)
	{
		return m_pTableData->fightercolor;
	}
	return "";
}
string  GameHelper::GetHeroEvolveColorById(X_INT id)
{

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_COLOR);
	const stDBC_FILE_HERO_COLOR	*m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByIndexKey(id);
	if (m_pTableData)
	{
		return m_pTableData->evolvecolor;
	}
	m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(0);
	if (m_pTableData)
	{
		return m_pTableData->evolvecolor;
	}
	return "";
}
//1--------------------6
X_INT  GameHelper::GetHeroColorByBear(X_INT bear)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_COLOR);

	X_INT num = pDataFile->GetRecordsNum();
	const stDBC_FILE_HERO_COLOR	*m_pTableData = X_NULL;
	for (X_INT i = num;i > 0 ;i-- )
	{
		m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(num-1);
		if (!m_pTableData)continue;
		 if(bear >= m_pTableData->bear)
			return m_pTableData->id;
	}

	m_pTableData = (const stDBC_FILE_HERO_COLOR*)pDataFile->GetFieldsByLineNum(0);
	if (m_pTableData)
	{
		return m_pTableData->id;
	}
	return 1;
}
X_INT   GameHelper::getMasterSchoolHero(vector<ObjectHero*>& heros)
{
	heros.clear();
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	X_UINT size = pSelf->GetHeroVectorSize(EM_HERO_CONTAINER_BAG);
	ObjectHero* pHero = NULL;
	for (X_UINT i =0;i< size;i++)
	{
		pHero = pSelf->getHero(i,EM_HERO_CONTAINER_BAG);
		if (!pHero)continue;
		 if(pHero->IsSkillMasterSchool())
			heros.push_back(pHero);
	}
	return 1;
}
cocos2d::CCSprite* GameHelper::getSpriteLevel(X_INT level)
{
	 
	string  str = "";
	switch (level)
	{
	case -3:
		str = "zb_juanzhou.png";
		break;
	case -2:
		str = "zb_suipian.png";
		break;
	case 2:
		str = "zb_level2.png";
		break;
	case 3:
		str = "zb_level3.png";
		break;
	case 4:
		str = "zb_level4.png";
		break;
	case 5:
		str = "zb_level5.png";
		break;
	default:
		break;
	}
	if (str.size() <= 0)
	{
		return 0;
	}
	return CCSprite::create(str.c_str()) ;
}
 

cocos2d::CCSprite* GameHelper::getSpriteLevel(const Item *pEquip)
{
	 
	return GameHelper::getSpriteLevel(pEquip->GetLevel());
	 
	
}
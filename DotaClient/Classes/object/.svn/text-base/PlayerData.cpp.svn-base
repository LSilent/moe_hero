#include "./object/PlayerData.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectHero.h"
#include "./game/SendPacket.h"

 bool PlayerData::bFlag = false;
PlayerData::PlayerData()
{
	Initial();
}
PlayerData::~PlayerData()
{

}	
X_VOID PlayerData::setName(string strId)
{
	//m_Name = strId;
	strcpy(m_Name,strId.c_str());
}
string PlayerData::getName()
{
	//return m_Name.c_str();
	return m_Name;
}
X_VOID PlayerData::Initial()
{
	//m_Name = "";	
	memset(m_Name,0,MAX_CHARACTER_NAME);
	m_Level = 1;			
	m_VipLevel = 0;			
    m_Exp = 0;
	m_VipExp = 0;
	//m_Money = 0;
	m_Gems =0;
	m_Gold = 0;
	m_Wood = 0;
	m_ActionPoint = 0;
	m_DayActivity = 0;
	m_MonthActivity = 0;
	m_StateFlag = 0;
	m_ActionPoint = 0;
	m_ActionPointFactor = 0;
	m_RecruitHeroCount = 0;
	m_RecruitRefreshLefttime = 0;
	m_BearPoint = 0;
    m_MatrixObj.clear();
	m_MatrixObj.resize(MAX_MATRIX_CELL_COUNT,X_NULL);
	m_SceneGroup =-1;
	m_MatrixHeroNum = 0;
	m_BuyBearPointCount = 0;
	bLevelUp = false;
	bFlag  = false;
	m_BuyAcNum =0;
	m_FreeRefreshNum = 0;
	m_Money = 0;
	m_GoddessHeroGuid = INVALID_ID;
	m_RockLeftTimes = 0;
	m_RockTimes = 0;
}
X_VOID			PlayerData::SetLevel(X_SHORT level)
{
	if (bFlag != false )
	{
		bLevelUp = true;
		
	}
	m_Level = level;
	bFlag = true;
}

X_VOID PlayerData::Release()
{
    m_MatrixObj.clear();
}
X_INT PlayerData::GetMaxExpWithLevel(X_INT level) const
{
		X_INT id = level !=-1 ? level:m_Level;
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HUMAN_EXP);
		if (pDataFile)
		{
			const stDBC_FILE_HUMAN_EXP* m_pTableData = (const stDBC_FILE_HUMAN_EXP*)pDataFile->GetFieldsByIndexKey(id);
			if (m_pTableData)
			{
				return m_pTableData->exp <=0  ? 1: m_pTableData->exp;
			}
		}
		return 1;
}
const vector<ObjectHero*> &	PlayerData::GetFightHero()  const { return m_MatrixObj; }
X_VOID			PlayerData::SetFightHero( const X_GUID* pHeroArray) 
{ 
	if (pHeroArray == X_NULL) return;
	m_MatrixHeroNum = 0;
	ObjectHero* pHero = X_NULL;
    m_MatrixObj.clear();
    m_MatrixObj.resize(MAX_MATRIX_CELL_COUNT,X_NULL);
	for (X_INT i = 0; i< MAX_MATRIX_CELL_COUNT;i++)
	{
		pHero = X_NULL;
		if (pHeroArray[i].IsValid())
		{
			pHero = static_cast<ObjectHero* >(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,pHeroArray[i].GetValue()));  
		}
		m_MatrixObj[i] = pHero;
		if (pHero)
		{
			m_MatrixHeroNum++;
		}
	}
}

X_VOID			PlayerData::SetMaxCopySceneGroupID(X_INT val)
{
	if (m_SceneGroup ==-1)
	{
		SendLogicPacket::askSceneList(val,true);
	}
	m_SceneGroup = val;
	DataPool::GetSingleton()->getCopySceneManager()->setPlayerEnableMaxGroup(m_SceneGroup);
	
}
X_VOID			PlayerData::SetSacrificeID(X_INT val)
{
	m_SacrificeID = val;
}
 
X_VOID			PlayerData::SetSacrificeDamage(X_INT val)
{
	m_SacrificeDamage = val;
}
X_BOOL			PlayerData::SetSacrificeAward(X_INT index, X_INT itemid)
{
	if (index<0 || index>=MAX_SACRIFICE_RECENT_AWARDITEM_COUNT)
	{
		return X_FALSE;
	}
	m_SacrificeAward[index] = itemid;
 
	return X_TRUE;
}
X_INT	PlayerData::GetSacrificeAward(X_INT index)
{
	if (index<0 || index>=MAX_SACRIFICE_RECENT_AWARDITEM_COUNT)
	{
		return -1;
	}
	return m_SacrificeAward[index];
}
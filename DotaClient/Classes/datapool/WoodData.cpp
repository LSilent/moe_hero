#include "./datapool/WoodData.h"
#include "./DataBase/DataBaseDefine.h"
#include "./database/DataBase.h"
#include "./database/DataBaseSystem.h"
SelfWoodData::SelfWoodData() 
	: m_WoodCreat(0)
	, m_RequiredLevel(0)
	, m_RequiredMoney(0)
	, m_RequiredTime(0)
	, m_WoodCapacity(0)
	, m_DefenceHeroID(0)
	, m_DefHero(NULL)
	, m_IsLevelUping(X_FALSE)
{
	for (int i = 0 ; i< MAX_MATRIX_CELL_COUNT;i++)
	{
		m_SefDefWoodHeros[i] = NULL;
	}

	m_nRobCD  = 0 ; //s
	m_nSafeCD = 0; //s
}
 
X_VOID SelfWoodData::HandleData( const cMyWoodData* source )
{

	memcpy(&m_WoodData,source,sizeof(cMyWoodData));

	m_IsLevelUping = (m_WoodData.m_LevelUpRemainTime > 0) ? X_TRUE:X_FALSE;
	m_WoodData.m_LevelUpRemainTime *= 1000;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_WOOD);
	if (pDataFile)
	{
		const  stDBC_FILE_WOOD* tableData = 
			(const stDBC_FILE_WOOD*)pDataFile->GetFieldsByIndexKey(m_WoodData.m_CampLevel);
		m_WoodCreat     = tableData->product;
		m_RequiredLevel = tableData->needLevel;
		m_RequiredMoney = tableData->spendMoney;
		m_RequiredTime  = tableData->spendTime;
		m_DefenceHeroID = tableData->heroid;
		m_WoodCreat     = tableData->product;
		m_WoodCapacity  = tableData->total;
	}
	m_DefHero = 
		(ObjectHero*)DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,m_DefenceHeroID);
	if (m_DefHero)
	{
	   if(m_DefHero->SetTableID(m_DefenceHeroID))
	   {
		m_DefHero->SetDataReady();
	   }
	   m_DefHero->SetLevel(m_WoodData.m_CampLevel);
	}
	HandleSelfMatrixDefHeros();
 
}

X_VOID SelfWoodData::HandleSelfMatrixDefHeros()
{
	for (X_INT i = 0; i< MAX_MATRIX_CELL_COUNT;i++)
	{
		m_SefDefWoodHeros[i] = NULL;
		if(!m_WoodData.m_FightHero[i].IsValid())
			continue;

		if (m_WoodData.m_FightHero[i].GetValue() == m_DefenceHeroID)
		{
			m_SefDefWoodHeros[i] = m_DefHero;
		}
		else
		{
			ObjectHero* pHero = 
				static_cast<ObjectHero* >(DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,m_WoodData.m_FightHero[i].GetValue()));
			if (pHero != NULL)
			{
				m_SefDefWoodHeros[i] = pHero;
			}
			
		}

	}
}

SelfWoodData::~SelfWoodData()
{
}


X_BOOL SelfWoodData::HeroIsDefWood( const ObjectHero* pHero )
{
	if (NULL  == pHero)  return X_FALSE;
	for (int i=0; i< MAX_MATRIX_CELL_COUNT;i++)
	{

		if (pHero->GetTableID() == m_DefenceHeroID)
		{
			return X_TRUE;
		}
		if (m_SefDefWoodHeros[i] != NULL && pHero->GetGuid() ==  m_SefDefWoodHeros[i]->GetGuid())
		{
			return X_TRUE;
		}
	}
	return X_FALSE;
	
}

WoodsData::WoodsData() 
	: m_pSelfWoodData(NULL)
	, m_pRobWoodData(NULL)
	, m_PriceWood(0)
	, m_OtherDefHero(NULL)
{
}

WoodsData::~WoodsData()
{
	
}

X_VOID WoodsData::Initial()
{
	m_pSelfWoodData = new SelfWoodData();
	m_pRobWoodData  = new cRobWoodData();
}
X_VOID WoodsData::Release()
{
	SAFE_DELETE(m_pSelfWoodData);
	SAFE_DELETE(m_pRobWoodData);
}
X_VOID WoodsData::HandleRobData( const cRobWoodData* source )
{
	memcpy(m_pRobWoodData,source,sizeof(cRobWoodData));
	HandleOtherMatrixDefHeros();
}

X_VOID WoodsData::HandleOtherMatrixDefHeros()
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_WOOD);
	const  stDBC_FILE_WOOD* tableData = 
		(const stDBC_FILE_WOOD*)pDataFile->GetFieldsByIndexKey(m_pRobWoodData->m_CampLevel);

	m_OtherDefHero = 
		(ObjectHero*)DataPool::GetSingleton()->getObjectManager()->CreateObject(OBJECT_TYPE_HERO,tableData->heroid);
	if (m_OtherDefHero)
	{
		if(m_OtherDefHero->SetTableID(tableData->heroid))
		{
			m_OtherDefHero->SetDataReady();
		}
		m_OtherDefHero->SetLevel(m_pRobWoodData->m_CampLevel);
	}
}

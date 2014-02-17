#include "./datapool/DataPool.h"
#include "./database/DataBaseSystem.h"
#include "./datapool/EquipOperator.h"
#include "./datapool/HeroOperator.h"
#include "./datapool/WoodData.h"
#include "./datapool/QuJingData.h"
#include "./datapool/BloodData.h"


IMPLEMENT_SINGLETON(DataPool)

DataPool::DataPool()
{
	BattlyType = EM_COPY_SCENE;
	m_pObjectManager = 0;
 
	m_LoginData = 0;
	m_pBagData = 0;
 
	m_pShopData = 0;
 
	m_pHeartBeatData = 0;
 
	m_pSelHero = 0;
	m_pBattleData = 0;
	 
	m_pSelItem = 0;
	m_pChatData = 0;

	m_pCopySceneManager = 0;
	 
	m_pMailData = 0;
	 
	m_pSportsData = 0;
 
	m_pHeroAltarData = 0;
	 
	m_pWalkMapData = 0;
 
	m_pHuoDong = 0;
	 
	m_pAchievement = 0;
	 
	m_GuideData = 0;
	 
	m_QuestData = 0;
	 
	m_pWoodData = 0;
	 
	m_pQujingData = 0;
 
	m_pBloodData = 0;
	 
}
DataPool::~DataPool()
{


}
X_VOID DataPool::Initial()
{
	m_init =false;
	m_pObjectManager = new ObjectManager();
	m_pObjectManager->Initial();
	m_LoginData = new LoginData();
	m_pBagData = new SelfBagData();
	m_pBagData->Initial();
	m_pShopData = new ShopData();
	m_pShopData->Initial();
	m_pHeartBeatData = new HeartBeatData();
	m_pHeartBeatData->Initial();
	m_pSelHero = X_NULL;
	m_pBattleData = new BattleData();
	m_pBattleData->Initial();
	m_pSelItem = X_NULL;
	m_pChatData = new ChatData();
	m_pChatData->Initial();
	m_pCopySceneManager = new CopySceneManager();
	m_pCopySceneManager->Initial();
	m_pMailData = new MailData();
	m_pMailData->Initial();
	m_pSportsData = new SportsData();
	m_pSportsData->Initial();
	m_pHeroAltarData = new HeroAltarData();
	m_pHeroAltarData->Initial();
	m_pWalkMapData = new WalkMapData();
	m_pWalkMapData->Initial();
	m_pHuoDong = new HuoDongData();
	m_pHuoDong->Initial();
	m_pAchievement = new AchievementData();
	m_pAchievement->Initial();
	m_GuideData = new GuideData();
	m_GuideData->Initial();
	m_QuestData = new QuestData();
	m_QuestData->Initial();
	m_pWoodData = new WoodsData();
	m_pWoodData->Initial();
	m_pQujingData = new QuJingData();
	m_pQujingData->Initial();
	
	m_pBloodData = new BloodData();
	m_pBloodData->Initial();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
	const stDBC_FILE_HERO_ATTR	* m_pTableData = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableData == X_NULL ||m_pTableData->_id >=1000) continue;
			m_pObjectManager->CreateFakeHero(m_pTableData->_id);
	}
	pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_ITEM);
	const stDBC_FILE_EQUIP_ITEM	* m_pTableDataEquip = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		m_pTableDataEquip = (const stDBC_FILE_EQUIP_ITEM*)pDataFile->GetFieldsByLineNum(i);
		if (m_pTableDataEquip == X_NULL) continue;
		m_pObjectManager->CreateFakeItem(m_pTableDataEquip->_id);
	}
	m_vecTipItem.clear();
	m_pSelectEqui.clear();
	PreLevelSkill = -1;
	bConnect = false;
	baskHuoDong =false;
	m_pSkill = X_NULL;
	m_pPlayer = X_NULL;
    m_createRole = false;
	m_init =true;
}
X_VOID DataPool::Tick(X_UINT nTime)
{
	if (!m_init)return;
	if (m_pObjectManager)
	{
		m_pObjectManager->Tick(nTime);
	}
	if (m_pHeartBeatData)
	{
		m_pHeartBeatData->Tick(nTime);
	}
	if (m_pSportsData)
	{
		m_pSportsData->Tick(nTime);
	}
	if (m_pWoodData)
	{
		m_pWoodData->Tick(nTime);
	}
	if (m_pQujingData)
	{
		m_pQujingData->Tick(nTime);
	}
	if (m_pHuoDong)
	{
		m_pHuoDong->Tick(nTime);
	}
}
X_VOID DataPool::Release()
{
	m_init = false;
	
	if (m_pBloodData)
	{
		m_pBloodData->Release();
	}
	SAFE_DELETE(m_pBloodData);
	if (m_pQujingData)
	{
		m_pQujingData->Release();
	}
	SAFE_DELETE(m_pQujingData);
	if (m_pWoodData)
	{
		m_pWoodData->Release();
	}
	SAFE_DELETE(m_pWoodData);
	if (m_QuestData)
	{
		m_QuestData->Release();
	}
	SAFE_DELETE(m_QuestData);
	if (m_pHeartBeatData)
	{
		m_pHeartBeatData->Release();
	}
	SAFE_DELETE(m_pHeartBeatData);
	if (m_GuideData)
	{
		m_GuideData->Release();
	}
	SAFE_DELETE(m_GuideData);
	if (m_pAchievement)
	{
		m_pAchievement->Release();
	}
	SAFE_DELETE(m_pAchievement);
	if (m_pHuoDong)
	{
		m_pHuoDong->Release();
	}
	SAFE_DELETE(m_pHuoDong);
	if (m_pWalkMapData)
	{
		m_pWalkMapData->Release();
	}
	SAFE_DELETE(m_pWalkMapData);
	if (m_pHeroAltarData)
	{
		m_pHeroAltarData->Release();
	}
	SAFE_DELETE(m_pHeroAltarData);
	if (m_pSportsData)
	{
		m_pSportsData->Release();
	}
	SAFE_DELETE(m_pSportsData);
	if (m_pMailData)
	{
		m_pMailData->Release();
	}
	SAFE_DELETE(m_pMailData);
	if (m_pCopySceneManager)
	{
		m_pCopySceneManager->Release();
	}
	SAFE_DELETE(m_pCopySceneManager);
	if (m_pChatData)
	{
		m_pChatData->Release();
	}
	SAFE_DELETE(m_pChatData);
	if (m_pBattleData)
	{
		m_pBattleData->Release();
	} 
	SAFE_DELETE(m_pBattleData);
	SAFE_DELETE(m_pShopData);
	SAFE_DELETE(m_pBagData);
	SAFE_DELETE(m_LoginData);
	EquipMaker::Release();
	HeroUpgrade::Release();
	if (m_pObjectManager)
	{
		//m_pObjectManager->Release();
	}
	SAFE_DELETE(m_pObjectManager);
	baskHuoDong = false;
    m_createRole = false;
	m_vecTipItem.clear();
	m_pSelectEqui.clear();
	PreLevelSkill = -1;
	bConnect = false;
	baskHuoDong =false;
	m_pSkill = X_NULL;
	m_pPlayer = X_NULL;
	m_createRole = false;
}
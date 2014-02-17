#ifndef __DATAPOOL_H__
#define __DATAPOOL_H__
#include "./base/Global.h"
#include "./base/Singleton.h"
#include "./object/ObjectManager.h" 
#include "./object/ObjectSkill.h"
#include "./object/ObjectPlayer.h"
#include "./datapool/loginData.h"
#include "./datapool/SelfBagData.h"
#include "./datapool/ShopData.h"
#include "./datapool/HeartBeatData.h"
#include "./datapool/BattleData.h"
#include "./datapool/ChatData.h"
#include "./datapool/CopySceneData.h"
#include "./datapool/MailData.h"
#include "./datapool/SportsData.h"
#include "./datapool/SettingData.h"
#include "./datapool/HeroAltarData.h"
#include "./datapool/WalkMapData.h"
#include "./datapool/HuoDong.h"
#include "./datapool/AchievementData.h"
#include "./datapool/GuideData.h"
#include "./datapool/QuestData.h"

class ItemCommon;
class WoodsData;
class QuJingData;
class BloodData;
 

struct stMaterialItem
{
	Item* m_pItem;
	X_INT m_num;
	bool  bEnough;
	X_INT m_nums;//背包里该物品总数
	stMaterialItem()
	{
		m_pItem = X_NULL;
		m_num = 0;
		bEnough = false;
		m_nums = 0;
	}
};
struct tipItem
{
	X_INT itemID;
	X_INT itemNum;

};
enum BattleType
{
	EM_BATTLETYPE_INVALID =  -1,
	EM_COPY_SCENE =0,
	EM_SPORT,
	EM_WOODPVP,
	EM_BATTLETYPE_GANK,
	EM_BATTLETYPE_LINE,
	EM_BATTLETYPE_FARM,
	EM_BATTLETYPE_BLOODBATTLE,
	EM_BATTLETYPE_QUJING,
};
class TableIdEqual
{
public:
	TableIdEqual(X_INT id) { m_TableId = id;}
	bool operator () (const Item * pObj)
	{
		return m_TableId == pObj->GetTableID();
	}
public:
	X_INT m_TableId;
};
class DataPool :public  Singleton<DataPool>
{
public:
	DataPool();
	virtual ~DataPool();


	X_VOID Initial();
	X_VOID Tick(X_UINT nTime);
	X_VOID Release();
public:
	LoginData* getLoginData()
	{
		return m_LoginData;
	}
    ObjectManager* getObjectManager()
	{
		return m_pObjectManager;
	}
	SelfBagData* getBagData()
	{
		return m_pBagData;
	}
	ShopData* getShopData()
	{
		return m_pShopData;
	}
	HeartBeatData*  GetHeartBeatData()
	{
		return m_pHeartBeatData;
	}
	BattleData*  GetBattleData()
	{
		return m_pBattleData;
	}
	ChatData *  GetChatData()
	{
		return m_pChatData;
	}
	CopySceneManager * getCopySceneManager()
	{
		return m_pCopySceneManager;

	}
	MailData * getMailData()
	{
		return m_pMailData;
	}
	SportsData * getSportsData()
	{
		return m_pSportsData;
	}
	HeroAltarData * getHeroAltarData()
	{
		return m_pHeroAltarData;
	}
	WalkMapData * getWalkMapData()
	{
		return m_pWalkMapData;
	}
	HuoDongData *getHuoDongData()
	{
		return m_pHuoDong;
	}
	AchievementData *getAchievementData()
	{
		return m_pAchievement;
	}
	GuideData *getGuideData()
	{
		return m_GuideData;
	}
	QuestData * getQuestData()
	{
		return m_QuestData;
	}
	WoodsData* GetWoodData() 
	{ 
		return m_pWoodData;
	}
	QuJingData* GetQuJingData() 
	{ 
		return m_pQujingData;
	}
	BloodData* GetBloodData()
	{
		return m_pBloodData;
	}
	const ObjectHero*  GetSelectHero()
	{
		return m_pSelHero;
	}

	X_VOID  SetSelectHero( const ObjectHero* phero)
	{
		  m_pSelHero = phero;
	}
	const Item*  GetSelectItem()
	{
		return m_pSelItem;
	}
	X_VOID  SetSelectItem( const Item* pItem)
	{
		m_pSelItem = pItem;
	}
	const ObjectSkill*  GetSelectSkill()
	{
		return m_pSkill;
	}
	X_VOID  SetSelectSkill( const ObjectSkill* pSkill)
	{
		m_pSkill = pSkill;
	}

	X_VOID  setSelectPlayer(const ObjectPlayer* pPlayer)
	{
		m_pPlayer = pPlayer;
	}
	const ObjectPlayer*  GetSelectPlayer()
	{
		return m_pPlayer;
	}
 
	const vector<tipItem> & getTipItems()
	{
		return m_vecTipItem;
	}


	const vector<ItemCommon *>&  GetSelectEqui()
	{
		return m_pSelectEqui;
	}
	X_VOID  SetSelectEqui( const vector<ItemCommon *> &pSelectEqui)
	{
		m_pSelectEqui = pSelectEqui;
	}

	X_VOID setTipItems(const vector<tipItem> & items)
	{
		 m_vecTipItem = items;
	}
    X_VOID setRoleCreate(bool b) { m_createRole = b ;}
    bool IsRoleCreateing( ) { return m_createRole;}
	 
	BattleType   BattlyType;
	X_INT	     PreLevelSkill;
	bool		 bConnect;	
	bool         baskHuoDong;
	bool m_init;
private:
	
	ObjectManager* m_pObjectManager;
	LoginData* m_LoginData;
	SelfBagData *m_pBagData;
	ShopData *m_pShopData;
	HeartBeatData*	m_pHeartBeatData;
	BattleData *m_pBattleData;
	ChatData * m_pChatData;
	MailData * m_pMailData;
	SportsData * m_pSportsData;
	HeroAltarData * m_pHeroAltarData;
	WalkMapData * m_pWalkMapData;
	HuoDongData * m_pHuoDong;
	AchievementData *m_pAchievement;
	GuideData* m_GuideData;
	QuestData* m_QuestData;
	WoodsData*  m_pWoodData;
	QuJingData*	m_pQujingData;
	BloodData*	m_pBloodData;
	CopySceneManager* m_pCopySceneManager;
	DECLARE_SINGLETON(DataPool)

	const ObjectHero * m_pSelHero;
	const Item * m_pSelItem;
	const ObjectSkill * m_pSkill;
	const ObjectPlayer* m_pPlayer;

	vector<ItemCommon *> m_pSelectEqui;


	vector<tipItem> m_vecTipItem;

    bool m_createRole;

};

 


#endif //__DATAPOOL_H__
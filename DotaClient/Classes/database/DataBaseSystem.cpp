#include "./database/DataBaseSystem.h"
#include "./database/DataBaseDefine.h"

IMPLEMENT_SINGLETON(DataBaseSystem)

DataBaseSystem::DataBaseSystem()
{
}

DataBaseSystem::~DataBaseSystem()
{
}

X_VOID DataBaseSystem::Initial()
{
	OpenAllDataBase();
}

X_VOID DataBaseSystem::Release()
{
	CloseAllDataBase();
}

X_VOID DataBaseSystem::OpenAllDataBase()
{
	struct _DATABASE_DEFINE
	{
		X_INT				nFileID;	
		const X_CHAR*		pFileName;	
	};

	_DATABASE_DEFINE  dbFileList[] = 
	{
        {DBC_FILE_CHARGE,								"Charge.tab"},
		{DBC_FILE_HERO_ATTR,							"HeroAttr.tab"},
		{DBC_FILE_ATTRIBUTE_DATA,						"AttributeData.tab"},
		{DBC_FILE_COMMON_ITEM,							"CommonItem.tab"},
		{DBC_FILE_EQUIP_ITEM,							"Equip.tab"},
		{DBC_FILE_GEM_ITEM,								"Gem.tab"},
		{DBC_FILE_EQUIP_STRENGTHEN,						"EquipStrengthen.tab"},
		{DBC_FILE_HERO_RECRUIT,							"HeroRecruit.tab"},
		{DBC_FILE_IMPACT,								"Impact.tab"},
		{DBC_FILE_ITEM_RULER,							"ItemRuler.tab"},
		{DBC_FILE_MONSTER,							    "Monster.tab"},
		{DBC_FILE_QUEST_ITEM,							"QuestItem.tab"},
		{DBC_FILE_SKILL,								"Skill.tab"},
		{DBC_FILE_HERO_EXP,								"HeroExp.tab"},
		{DBC_FILE_HUMAN_EXP,							"HumanLevel.tab"},
		//{DBC_FILE_UI,									"UI.tab"},
		{DBC_FILE_UIMUTEX,								"UIMutexTable.tab"},
		{DBC_FILE_HEROQUALITY,							"HeroQuality.tab"},
		{DBC_FILE_SHOP,									"Shop.tab"},
		{DBC_FILE_FIGHTMONSTER,							"FightMonster.tab"},
		{DBC_FILE_DROPBOX,								"DropBox.tab"},
		{DBC_FILE_EQUIP_MANUFACTURE,					"EquipManufacture.tab"},
		{DBC_FILR_COPYSCENE,							"CopyScene.tab"},
		{DBC_FILR_COPYSCENE_GROUP,						"CopySceneGroup.tab"},
		{DBC_FILR_SACRIFICE,							"Sacrifice.tab"},
		{DBC_FILE_LANG,									"Lang.tab"},
		{DBC_FILR_SACRIFICE_AWARD,						"SacrificeAward.tab"},
		{DBC_FILE_GIFT_PACKET,							"GiftPack.tab"},
		{DBC_FILE_FILTER,								"Filter.tab"},
		{DBC_FILE_CHESS,								"Chess.tab"},
		{DBC_FILE_CHESSBONUS,							"ChessBonus.tab"},
		{DBC_FILE_HUODONG,								"HuoDong.tab"},
		{DBC_FILE_EATCHEESE,							"EatCheeseHuoDong.tab"},
		{DBC_FILE_COPYSCENEHUODONG,						"CopySceneHuoDong.tab"},
		{DBC_FILE_BUYBEARPOINT,							"BuyBearPointHuoDong.tab"},
		{DBC_FILE_EQUIPGUIDE,							"EquipGuide.tab"},
		{DBC_FILE_HERO_EQUIP_RECOMMEND,					"EquipRecommend.tab"},
		{DBC_FILE_ACHIEVE,					   		    "Achieve.tab"},
		{DBC_FILE_GUIDE,					   		    "Guide.tab"},
		{DBC_FILE_BUYACTIONPOINT,					   	"BuyActionPoint.tab"},
		{DBC_FILE_QUEST,								"Mission.tab"},
		{DBC_FILE_SELECT_SERVER,						"SelectServer.tab"},
		{DBC_FILE_HERO_COLOR,							"HeroColor.tab"},
		{DBC_FILE_WOOD,									"Wood.tab"},
		{DBC_FILE_EXCHANGE,								"Exchange.tab"},
		{DBC_FILE_CONFIG,								"config.tab"},
		{DBC_FILE_QUJING,								"QuJing.tab"},
		{DBC_FILE_STAIRPLUS,							"StairPlus.tab"},
		{DBC_FILE_STAIRBONUS,							"StairBonus.tab"},
		{DBC_FILE_ACHIEVE_GROUP,						"AchieveGroup.tab"},
		{DBC_FILE_ACCELERATE,							"Accelerate.tab"},
		{DBC_FILE_PLACARD,								"Placard.tab"},
		
		
	};


	X_INT nFileListCount = sizeof(dbFileList)/sizeof(_DATABASE_DEFINE);
	for(X_INT i=0; i<nFileListCount; i++)
	{
		DataBase* pDataBase = new DataBase(dbFileList[i].nFileID);
		if( !pDataBase )
		{
			continue;
		}
		if(!(pDataBase->CreateDBFromFile(dbFileList[i].pFileName)))
		{
		}
		if(m_mapDataBaseBuf.find(dbFileList[i].nFileID) != m_mapDataBaseBuf.end())
		{
			continue;
		}
		m_mapDataBaseBuf.insert(std::make_pair(dbFileList[i].nFileID, pDataBase));
		//wstring tableName = dbFileList[i].pFileName;
		//m_mapNameToID.insert(std::make_pair(tableName, dbFileList[i].nFileID));
	}
}

X_VOID DataBaseSystem::CloseAllDataBase()
{
	std::map<X_INT, DataBase*>::iterator it;
	for(it = m_mapDataBaseBuf.begin(); it!=m_mapDataBaseBuf.end(); ++it)
	{
		SAFE_DELETE(it->second);
	}
	m_mapDataBaseBuf.clear();
}

const DataBase* DataBaseSystem::GetDataBase(X_INT idDataBase) const
{
	std::map<X_INT, DataBase* >::const_iterator it = m_mapDataBaseBuf.find(idDataBase);

	if( it != m_mapDataBaseBuf.end() )
		return (const DataBase*)it->second;
	return X_NULL;
}

/*const DataBase* DataBaseSystem::GetDataBase(wstring& tableName) const
{
	std::map<wstring, X_INT>::const_iterator it = m_mapNameToID.find(tableName);
	if( it == m_mapNameToID.end() )
	{
		return X_NULL;
	}
	X_INT tableID = it->second;
	return GetDataBase(tableID);
}*/
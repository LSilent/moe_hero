#include "./datapool/HeroOperator.h"
#include "./object/ItemCommon.h"

vector<Item* > HeroUpgrade::m_Items ;
X_VOID HeroUpgrade::getUpgradeItem(const ObjectHero* pHero,stMaterialItem & Material)
{
	 
	if (pHero == X_NULL ) return;
	const stDBC_FILE_HERO_ATTR* _attr =   pHero->getTableData();
	if (_attr == X_NULL) return;

	Item * pItem = _FindItemByTableID(_attr->_spiritID);
	if (!pItem)
	{
		pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(_attr->_spiritID,INVALID_INDEX);
		if (pItem)
		{
			pItem->SetVirtual(true);
			m_Items.push_back(pItem);
		}
	}
	if (pItem == X_NULL) return;
	Material.m_pItem = pItem;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HEROQUALITY);
	if (pDataFile)
	{
		const stDBC_FILE_HEROQUALITY* m_pTableData = (const stDBC_FILE_HEROQUALITY*)pDataFile->GetFieldsByIndexKey(pHero->GetQuality()+1);
		if (m_pTableData)  
		{
			Material.m_num = m_pTableData->costItemNum;
		}
		else
		{
			Material.m_num = 0;
		}
	}

	SelfBagData* pbag = DataPool::GetSingleton()->getBagData(); 
	Material.m_nums =  pbag->getItemNumByTableId(_attr->_spiritID);
	Material.bEnough = Material.m_nums >= Material.m_num;
}
X_INT	HeroUpgrade::getUpgradeNeedBearPoint(const ObjectHero* pHero)
{
	if (pHero == X_NULL ) return 0;
	X_INT Quality = pHero->GetQuality()+1;
	if (Quality < EM_HERO_QUALITY_TYPE1 || Quality >= EM_HERO_QUALITY_TYPE6 ) return 0;

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HEROQUALITY);
	if (pDataFile)
	{
		const stDBC_FILE_HEROQUALITY* m_pTableData = (const stDBC_FILE_HEROQUALITY*)pDataFile->GetFieldsByIndexKey(Quality);
		if (!m_pTableData) return  0;
		return m_pTableData->BearPointNeed;
	}
	return 0;
}
X_VOID	HeroUpgrade::getUpgradeInfo(const ObjectHero* pHero,X_INT &BearPointLimit,X_INT &BearPoint)
{
	BearPointLimit = 0;
	BearPoint = 0;
	if (pHero == X_NULL ) return ;
	X_INT Quality = pHero->GetQuality();
	if (Quality < EM_HERO_QUALITY_TYPE1 || Quality >= EM_HERO_QUALITY_TYPE6 ) return;
	  
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HEROQUALITY);
	if (pDataFile)
	{
		const stDBC_FILE_HEROQUALITY* m_pTableData = (const stDBC_FILE_HEROQUALITY*)pDataFile->GetFieldsByIndexKey(Quality+1);
		if (!m_pTableData) return ;
		/*const stDBC_FILE_HEROQUALITY* _m_pTableData = (const stDBC_FILE_HEROQUALITY*)pDataFile->GetFieldsByIndexKey(Quality);
		if (!_m_pTableData) return ;
		X_INT newBear = m_pTableData->BearPoint;X_INT oldBear = _m_pTableData->BearPoint;
		if (newBear < 0)
		{
			newBear = 0;
		}
		if (oldBear < 0)
		{
			oldBear = 0;
		}
		BearPoint = newBear - oldBear;*/
		BearPoint = m_pTableData->BearPoint;
	}
	const  DataBase* pDataFileExp  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_EXP);
	if (pDataFileExp)
	{
		const stDBC_FILE_HERO_EXP* m_pTableDataEXP = (const stDBC_FILE_HERO_EXP*)pDataFileExp->GetFieldsByIndexKey(pHero->GetLevel());
		if (m_pTableDataEXP)
		{
			 
			 BearPointLimit =  m_pTableDataEXP->BearPoint[Quality];
		}
	}


}
Item *  HeroUpgrade::_FindItemByTableID(X_INT tableId)
{
	vector< Item* >::iterator ifind;
	ifind =  find_if(m_Items.begin(),m_Items.end(),TableIdEqual(tableId));
	if (ifind != m_Items.end())
	{
		return  *ifind;
	}
	return X_NULL;
}
X_VOID  HeroUpgrade::Release()
{
	X_UINT size = m_Items.size();
	for (X_UINT i = 0; i<size ;i++)
	{
		DataPool::GetSingleton()->getObjectManager()->DestroyItem( m_Items[i]);
	}
	m_Items.clear();
}
 const stDBC_FILE_SKILL *	SkillUpgrade::getUpgradeInfo(const ObjectSkill* pSkill)
 {
	 if (!pSkill)return X_NULL;
	 if (pSkill->IsTop())
	 {
		 return X_NULL;
	 }
	const stDBC_FILE_SKILL* m_pTableData = X_NULL;
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	 if (pDataFile)
		 m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId()+1);
	 return m_pTableData;
 }
 X_INT 	SkillUpgrade::getAddSucessRate(const ObjectSkill* pSkill,const Item* pItem)
 {
	 if (!pSkill || !pItem)return 0;
	if( pItem->GetClass() != EM_ITEM_CLASS_COMMON) return 0;

	const stDBC_FILE_COMMON_ITEM * pTableData = ((ItemCommon*)(pItem))->getTableData();
	if (!pTableData)return 0;
	X_INT rate = pTableData->_skillLevelUpRate <= -1 ? 0: pTableData->_skillLevelUpRate;
	if (pTableData->_skillDoubleGroup == pSkill->GetTableId() )
	{
		return rate*2;
	}
	return rate;
 }
X_VOID  HeroUpgrade::getRecommendItem(const ObjectHero* pHero,vector<Item*>& RecommendItems)
{
	RecommendItems.clear();
	RecommendItems.resize(RECOMMEND_ITEM*MAX_EQUIP_RECOMMEND);
	if (pHero == X_NULL ) return;
	X_INT tableId = pHero->GetTableID();
	if (tableId == -1 )return;
	 //4¶Î×°±¸
	Item *pItem = X_NULL;
	for (X_INT i = 0; i< RECOMMEND_ITEM;i++)
	{
		X_INT _tableid = tableId*10+i+1;
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_EQUIP_RECOMMEND);
		if (!pDataFile)continue;
		const stDBC_FILE_HERO_EQUIP_RECOMMEND* m_pTableData = (const stDBC_FILE_HERO_EQUIP_RECOMMEND*)pDataFile->GetFieldsByIndexKey(_tableid);
		if (!m_pTableData)continue;
		 
		for (X_INT j = 0;j<MAX_EQUIP_RECOMMEND;j++ )
		{
			 if (m_pTableData->equip[j] ==-1)continue;
			 
			  pItem = _FindItemByTableID(m_pTableData->equip[j]);
			 if (!pItem)
			 {
				 pItem = DataPool::GetSingleton()->getObjectManager()->CreateItem(m_pTableData->equip[j],INVALID_INDEX);
				 if (pItem)
				 {
					 pItem->SetVirtual(true);
					 m_Items.push_back(pItem);
				 }
			 }
			 if (pItem == X_NULL) continue;
			 RecommendItems[i*MAX_EQUIP_RECOMMEND +j] = pItem;
		}
	}
}
 
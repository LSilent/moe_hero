#include "./datapool/BattleData.h"
#include "./DataBase/DataBaseSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"

std::string  BattleObject::GetSmallIcon()const
{
	string str  = "zht_";
	str += m_icon;
	return str.substr(0,str.length() - 3) +"png";
	 
}
std::string BattleObject::GetHeadIcon()const
{
	string str  = "zhf_";
	return (str + m_icon);
}
std::string BattleObject::GetBody()const
{
	string str  = "zhp_";
	str += m_icon;
	return str.substr(0,str.length() - 3) +"png";
}
X_INT	BattleObject::GetLevel()
{
	return m_Level;
}
X_CHAR	BattleObject::GetProfession()
{
	return m_Profession;
}
X_INT	BattleObject::GetQuality()
{
	return m_Quality;
}
X_INT	BattleObject::GetColor()
{
	return m_Color;
}
X_INT	BattleObject::GetPosition()
{
	return	m_MatrixID;
}
bool   BattleObject::isMonster()
{
	return m_bMonster;
}
X_INT	BattleObject::GetHP()
{
	if (m_Info)
	{
		return m_Info->m_HP;
	}
	return 0;
}
X_INT	BattleObject::GetMP()
{
	if (m_Info)
	{
		return m_Info->m_MP;
	}
	return 0;
}

X_INT	BattleObject::GetMaxHP()
{
	if (m_Info)
	{
		return m_Info->m_MaxHP;
	}
	return 0;
}
X_INT	BattleObject::GetMaxMP()
{
	if (m_Info)
	{
		return m_Info->m_MaxMP;
	}
	return 0;
}
X_INT	BattleObject::GetFightDistance()
{
	if (m_Info)
	{
		return m_Info->m_FightDistance;
	}
	return 1;
}
X_INT BattleObject::GetNextFightDistance()
{
	/*if (m_NextInfo)
	{
		return m_NextInfo->m_FightDistance;
	}*/
	return GetFightDistance() +  GetAttackSpeed();
}
X_INT	BattleObject::GetAttackSpeed()
{
	if (m_Info)
	{
		return m_Info->m_AttackSpeed;
	}
	return 1;
}
const vector<Impact *>& BattleObject::GetImpact()
{
	return m_ImpactInfo;
}
const vector<int>&  BattleObject::GetImpactHurt()
{
	return m_ImpactHurt;
}
const vector<int>&  BattleObject::GetMagicDelta()
{
	return m_magicDelta;
}
X_VOID BattleObject::SetRoundInfo(const cFObjectInfo* Info,const cFObjectInfo* _NextInfo)
{
	m_Info = Info;
	m_NextInfo = _NextInfo;
	if (m_NextInfo == NULL)
	{
		m_NextInfo = m_Info;
	}
	if (!m_Info)
	{
		return;
	}
	X_INT size = m_ImpactInfo.size();
	for (X_INT i = 0;i<size;i++)
	{
		SAFE_DELETE(m_ImpactInfo[i]);
	}
	m_ImpactInfo.clear();
	m_ImpactHurt.clear();
	Impact *pImapact =X_NULL;
	for (X_INT i = 0;i<m_Info->m_ImpactCount;i++)
	{
		pImapact = new Impact(m_Info->m_ImpactList[i]);
		m_ImpactInfo.push_back(pImapact);
	}
	for (X_INT i = 0;i<MAX_IMPACT_NUMBER;i++)
	{
		int hurt = m_Info->m_ImpactHurt[i];
		if (hurt !=  0)
		{
			m_ImpactHurt.push_back(hurt);
		}
	}

	m_magicDelta.clear();
	for (X_INT i = 0;i<MAX_IMPACT_NUMBER;i++)
	{
		int delta = m_Info->m_ImpactMP[i];
		if (delta !=  0)
		{
			m_magicDelta.push_back(delta);
		}
	}
}
X_VOID BattleObject::SetData(const cFObjectData & data,bool bMonster)
{
	m_Guid = data.m_Guid.GetValue();
	m_TableID = data.m_TableID;
	m_Profession = data.m_Profession;
	m_Level = data.m_Level;
	m_MatrixID = data.m_MatrixID;
	m_bMonster = bMonster;
	m_Quality = data.m_Quality;
	m_Color = data.m_Color;
	if (!m_bMonster)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
		const stDBC_FILE_HERO_ATTR	* m_pTableData = (const stDBC_FILE_HERO_ATTR*)pDataFile->GetFieldsByIndexKey(m_TableID);
		m_icon = m_pTableData->_icon;
	}else
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_FIGHTMONSTER);
		const stDBC_FILE_FIGHTMONSTER	* m_pTableData = (const stDBC_FILE_FIGHTMONSTER*)pDataFile->GetFieldsByIndexKey(m_TableID);
		m_icon = m_pTableData->_icon;
	}
}
X_VOID BattleObject::SetFree(bool free)
{
	m_free = free;
}
bool BattleObject::isFree( )
{
	return m_free;
}

 X_VOID BattleObjectPool::Init()
 {
	 m_Attack.clear();
	 m_Defense.clear();
	 m_Fighter.clear();
 }
 X_VOID BattleObjectPool::Release()
 {
	 m_Attack.clear();
	 m_Defense.clear();
	 X_UINT size = m_Fighter.size();
	 BattleObject*  pFighter = X_NULL;
	 for (X_UINT i = 0; i<size ;i++ )
	 {
		  pFighter = m_Fighter[i];
		  SAFE_DELETE(pFighter);
	 }
	 m_Fighter.clear();
 }
 
BattleObject* BattleObjectPool::__GetFighter()
{
	X_UINT size = m_Fighter.size();
	BattleObject*  pFighter = X_NULL;
	 for (X_UINT i = 0; i<size ;i++ )
	 {
		 pFighter = m_Fighter[i];
		 if (pFighter && pFighter->isFree())
		 {
			 pFighter->CleanUp();
			 return pFighter;
		 }
	 }
	 pFighter = new BattleObject();
	 pFighter->CleanUp();
	 m_Fighter.push_back(pFighter);
	 return pFighter;
}
 BattleObject* BattleObjectPool::FindFighterByGUID(const X_GUID& guid)
 {
	 BattleObject*  pFighter = X_NULL;
	 pFighter = __FindAttackFighterByGUID(guid);
	 if (!pFighter)
	 {
		 pFighter = __FindDefenseFighterByGUID(guid);
	 }
	 return pFighter;
 }
BattleObject* BattleObjectPool::__FindAttackFighterByGUID(const X_GUID& guid)
{
	X_UINT size = m_Attack.size();
	BattleObject*  pFighter = X_NULL;
	for (X_UINT i =0;i<size;i++)
	{
		 pFighter = m_Attack[i];
		 if (pFighter &&pFighter->m_Guid == guid.GetValue())
		 {
			 return pFighter;
		 }

	}
	return X_NULL;
}
BattleObject* BattleObjectPool::__FindDefenseFighterByGUID(const X_GUID& guid)
{
	X_UINT size = m_Defense.size();
	BattleObject*  pFighter = X_NULL;
	for (X_UINT i =0;i<size;i++)
	{
		pFighter = m_Defense[i];
		if (pFighter &&pFighter->m_Guid == guid.GetValue())
		{
			return pFighter;
		}

	}
	return X_NULL;
}
X_VOID BattleObjectPool::PrepareFighter(const cFightInfo* info )
{
	 if (!info) return;
	 m_Attack.clear();
	 m_Defense.clear();
 
	 BattleObject*  pFighter = X_NULL;
	 for (X_INT i = 0;i < info->m_AttackObjectCount;i++)
	 {
		pFighter =  __GetFighter();
		pFighter->SetData(info->m_AttackObjectData[i],false);
		pFighter->SetFree(false);
		pFighter->m_bAttacker = true;
		m_Attack.push_back(pFighter);
		pFighter->m_index = i;
	 }
	 for (X_INT i = 0;i < info->m_DefendObjectCount;i++)
	 {
		 pFighter =  __GetFighter();
		 pFighter->SetData(info->m_DefendObjectData[i],info->m_DefendType == 0);
		 pFighter->SetFree(false);
		 pFighter->m_bAttacker = false;
		 m_Defense.push_back(pFighter);
		 pFighter->m_index = i;
	 }
}
X_VOID BattleObjectPool::DestroyBattleData()
{
	m_Attack.clear();
	m_Defense.clear();
	BattleObject*  pFighter = X_NULL;
	X_UINT size = m_Fighter.size();
	for (X_UINT i = 0; i<size ;i++ )
	{
		m_Fighter[i]->CleanUp();
	}
}
 X_VOID BattleData::Initial()
 {
	 m_pool = new BattleObjectPool();
	 m_pool->Init();
 }
 X_VOID BattleData::Release()
 {
	 if (m_pool)
	 {
		 m_pool->Release();
	 }
	 SAFE_DELETE(m_pool);
 }
X_VOID BattleData::PrepareData(const cFightInfo* info )
{
	if (!info) return;
	m_info = info;
	m_curRound = 0;
	m_pool->PrepareFighter(info);

}
 X_VOID BattleData::DestroyBattleData()
 {
	m_pool->DestroyBattleData();
	  
 }
 bool BattleData::isWin()
 {
	 return m_info->m_bWin == XTRUE;
 }
 X_INT BattleData::GetRound()
 {
	 return m_info->m_Rounds;
 }
 X_INT BattleData::GetcurRound()
 {
	 return m_curRound;
 }
 bool BattleData::tickRound()
 {
	
	if (m_curRound >= m_info->m_Rounds || m_curRound > MAX_FIGHT_ROUND)
	{
		return  false;
	}
	const cFightRoundInfo * roundInfo = &(m_info->m_RoundInfo[m_curRound]);
	const cFightRoundInfo * __nextroundInfo = X_NULL;
	 if (m_curRound < m_info->m_Rounds -1)
	 {
		 __nextroundInfo = &(m_info->m_RoundInfo[m_curRound+1]);
	 } 
 
	BattleObject* pFighter = X_NULL;
	for (X_INT i = 0;i < roundInfo->m_AttackObjectCount;i++)
	{
		 pFighter = m_pool->__FindAttackFighterByGUID(roundInfo->m_AttackObjectInfo[i].m_Guid);
		 if (!pFighter)continue;

		 if (!__nextroundInfo )
		 {
			 pFighter->SetRoundInfo( &(roundInfo->m_AttackObjectInfo[i]),X_NULL);
		 }else
		 {
			 pFighter->SetRoundInfo( &(roundInfo->m_AttackObjectInfo[i]),&(__nextroundInfo->m_AttackObjectInfo[i]));
		 }
		 
	}
	for (X_INT i = 0;i < roundInfo->m_DefendObjectCount;i++)
	{
		 pFighter = m_pool->__FindDefenseFighterByGUID(roundInfo->m_DefendObjectInfo[i].m_Guid);
		 if (!pFighter)continue;
		  if (!__nextroundInfo )
		  {
			  pFighter->SetRoundInfo( &(roundInfo->m_DefendObjectInfo[i]),X_NULL);
		  }
		  else
		  {
			  pFighter->SetRoundInfo( &(roundInfo->m_DefendObjectInfo[i]), &(__nextroundInfo->m_DefendObjectInfo[i]));
		  }
		 
	}
	m_AttackInfo.clear();
	for (X_INT i=0;i<roundInfo->m_AttInfoCount;i++)
	{
		m_AttackInfo.push_back(&roundInfo->m_AttackInfo[i]);
	}
	 m_curRound++;
	 return true;
 }
 const vector<const cAttackInfo *>& BattleData::getRoundAttackData()
 {
	 return m_AttackInfo;
 }	

BattleObject* BattleData::FindFighterByGUID(const X_GUID& guid)
{
	return m_pool->FindFighterByGUID(guid);
}

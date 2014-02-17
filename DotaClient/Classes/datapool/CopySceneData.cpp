#include "./datapool/CopySceneData.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"

X_CHAR * CopyScene::getName()const
{
	return m_pTableData->name;
}
X_CHAR * CopyScene::getInfo()const
{
	return m_pTableData->info;
}
X_CHAR *   CopyScene::getIcon()const
{
	return m_pTableData->_icon;
}
X_CHAR *   CopyScene::getDropInfo()const
{
	return m_pTableData->_dropInfo;
}
X_CHAR *   CopyScene::getImg()const
{
	return m_pTableData->_battleScene;
}
 
X_INT      CopyScene::getMonster()const
{
	return m_pTableData->_monsterId;
}
X_INT      CopyScene::getActionCost()const
{
	return m_pTableData->_costAction;
}
X_INT       CopyScene::getMaxChallengeNum()const
{
	return m_pTableData->_challengeNum;
}
X_UINT     CopyScene::getRefreshCost()const
{
	if (m_pTableData->_refreshCost <= 0)
	{
		return 0;
	}
	return (X_UINT)m_pTableData->_refreshCost;
}
X_INT     CopyScene::getEXP()const
{
	return m_pTableData->_exp;
}
X_INT     CopyScene::getHeroExp()const
{
	return m_pTableData->_heroExp;
}
EM_COPYSCENE_STATUS     CopyScene::getStatus()const
{
	return EM_COPYSCENE_STATUS(m_CopySceneStatus);
}
X_INT     CopyScene::getStar()const
{
	return m_CopySceneStar;
}
X_INT     CopyScene::getChallengeNum()const
{
	return m_ChallangeCount;
}
X_INT	 CopyScene::getRecommendLevel()const
{
	return m_pTableData->_recommendLevel;
}
X_INT	 CopyScene::getRewardMoney()const
{
	return m_pTableData->_rewardGold;
}
X_BOOL		CopyScene::GetAwardItem(X_INT index, string& itemName,string& itemIcon,string& itemColor, X_INT& itemcount,X_INT &level)const
{
	X_INT id;
	X_BOOL bok = GetAwardItem(index,id,itemcount);
 
	if (bok)
	{
		 bok = DataPool::GetSingleton()->getObjectManager()->getItemInfoById(id,itemName,itemColor,itemIcon,level);


	}

	return bok;
}
vector<X_INT> CopyScene::GetDropItems()
{
	vector<X_INT> vec;
	vec.clear();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_MONSTER);
	const stDBC_FILE_MONSTER * pTableData = (const stDBC_FILE_MONSTER*)pDataFile->GetFieldsByIndexKey(m_pTableData->_monsterId);
	if(pTableData)
	{
		
		const  DataBase* pDataFileDrop  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_DROPBOX);
		const stDBC_FILE_DROPBOX * pTableData__ =  (const stDBC_FILE_DROPBOX*) pDataFileDrop->GetFieldsByIndexKey(pTableData->_drop);
		if (pTableData__)
		{
			UtilTools::ConvertStringToIntVector(pTableData__->items,vec,"|");
		}
	}
	return vec;
}
CopyScene::CopyScene(X_INT id)
{
	m_id = id;
	m_CopySceneStatus = EM_COPYSCENE_STATUS_CLOSE;
	m_CopySceneStar = 0;
	m_ChallangeCount = 0;
	m_Count = 0;
	m_AwardGold =0;
	m_AwardHumanExp =0;
}
X_CHAR * CopySceneGroup::getName()const
{
	return m_pTableData->name;
}
X_CHAR * CopySceneGroup::getInfo()const
{
	return m_pTableData->info;
}
CopySceneGroup::CopySceneGroup(X_INT id)
{
	m_GroupID = id;
	
}
 X_VOID CopySceneGroup::Initial()
 {
	 m_bAsked = false;
	 m_bEnable = false;
	 m_pScene.clear();
	 if (!m_pTableData || m_pTableData->scenes == "-1")return;

	 vector<int> scenes;
	 UtilTools::ConvertStringToIntVector(m_pTableData->scenes,scenes,"|");
	 X_UINT size = scenes.size();
	  const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILR_COPYSCENE);
	  const stDBC_FILR_COPYSCENE * pTableData = X_NULL;
	  CopyScene *pScene = X_NULL;
	 for (X_UINT i = 0;i < size;i++)
	 {
		 pTableData = (const stDBC_FILR_COPYSCENE*)pDataFile->GetFieldsByIndexKey(scenes[i]);
		 if (!pTableData)continue;
		  pScene = new CopyScene(scenes[i]);
		  pScene->m_pTableData = pTableData;
		  m_pScene.push_back(pScene);
	 }
 }
 X_VOID CopySceneGroup::Release()
 {
	 for (X_UINT i = 0;i<m_pScene.size();i++)
	 {
		 SAFE_DELETE(m_pScene[i]);
	 }
	 m_pScene.clear();
 }
 CopyScene*  CopySceneGroup::getCopySceneById(X_INT id)const
 {
	 X_UINT size = m_pScene.size();
	 for (X_UINT i = 0;i<size;i++)
	 {
		 if ( m_pScene[i]->m_id == id)
		 {
			 return m_pScene[i];
		 }
	 }
	 return X_NULL;
 }
 CopyScene*  CopySceneGroup::getMaxEnable() const
 {

	 X_INT size = m_pScene.size();
	 for (X_INT i = size -1;i >= 0;i-- )
	 {
		 if ( m_pScene[i]->getStatus() == EM_COPYSCENE_STATUS_OPEN  ||m_pScene[i]->getStatus() == EM_COPYSCENE_STATUS_PASS)
		 {
			 return m_pScene[i];
		 }
	 }
	 return X_NULL;
 }
X_VOID CopySceneManager::Initial()
{
	bChangeGroup = true;
	m_FightScene = -1;
	m_pSceneGroup.clear();
    m_curCopySceneGroup = X_NULL;
	m_curCopyScene= X_NULL;
	m_maxCopySceneGroup = X_NULL;
	m_awardScene =X_NULL;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILR_COPYSCENE_GROUP);
	const stDBC_FILR_COPYSCENE_GROUP*  pTableData = X_NULL;
	CopySceneGroup *pGroup = X_NULL;
	for (X_UINT i = 0;i< pDataFile->GetRecordsNum();i++)
	{
		pTableData = (const stDBC_FILR_COPYSCENE_GROUP*)pDataFile->GetFieldsByLineNum(i);
		if (pTableData == X_NULL) continue;
	    pGroup =  new CopySceneGroup(pTableData->id);
		pGroup->m_pTableData = pTableData;
		pGroup->Initial();
		m_pSceneGroup.push_back(pGroup);    
	}
}
X_VOID CopySceneManager::Release()
{
	m_FightScene =-1;
	for (X_UINT i = 0;i<m_pSceneGroup.size();i++)
	{
		SAFE_DELETE(m_pSceneGroup[i]);
	}
	m_pSceneGroup.clear();
}
CopySceneGroup* CopySceneManager::getCopySceneGroupById(X_INT id)const
{
	X_UINT size = m_pSceneGroup.size();
	for (X_UINT i = 0;i<size;i++)
	{
		if ( m_pSceneGroup[i]->m_GroupID == id)
		{
			return m_pSceneGroup[i];
		}
	}
	return X_NULL;
}
 CopyScene* CopySceneManager::findCopySceneByID(X_INT id, CopySceneGroup* & pGroup)const
 {
	 CopyScene* pscene =X_NULL;
	 pGroup = X_NULL;
	 X_UINT size = m_pSceneGroup.size();
	 for (X_UINT i = 0;i<size;i++)
	 {
		 if ( m_pSceneGroup[i])
		 {
			 pscene = m_pSceneGroup[i]->getCopySceneById(id);
			 if (pscene)
			 {
				 pGroup = m_pSceneGroup[i];
				 return pscene;
			 }
		 }
	 }
	 return X_NULL;
 }
 
X_VOID CopySceneManager::SetCopyScene( CopySceneGroup* pGroup,X_INT copySceneID,X_INT copyStatus,X_INT copySceneStar,X_INT ChallangeCount)
{
 
	CopyScene* pScene = X_NULL;
	if (pGroup)
	{
		pScene = pGroup->getCopySceneById(copySceneID);
	}
	if (pScene)
	{
		pScene->m_CopySceneStatus = copyStatus;
		pScene->m_CopySceneStar = copySceneStar;
		pScene->m_ChallangeCount = ChallangeCount;
	}
}
  X_VOID CopySceneManager::setPlayerEnableMaxGroup(X_INT group)
  {
	  X_INT size = m_pSceneGroup.size();
	  for (X_UINT i = 0;i<m_pSceneGroup.size();i++)
	  {
		  if( m_pSceneGroup[i]->m_GroupID <= group)
			  m_pSceneGroup[i]->m_bEnable = true;
	  }
	  m_maxCopySceneGroup = getCopySceneGroupById(group);
  }
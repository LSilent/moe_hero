#ifndef __COPYSCENE_DATA_H__
#define __COPYSCENE_DATA_H__

#include "./base/Global.h"
#include "./database/DataBaseSystem.h"

#define  HUODONG_COPYSCENE_GROUP 1000
class CopyScene
{
	friend class CopySceneManager;
	friend class CopySceneGroup;
public:

	//图标
	X_CHAR *   getIcon()const;
	//名字
	X_CHAR *   getName()const;
	//副本描述
	X_CHAR *   getInfo()const;
	//获得体力消耗
	X_INT      getActionCost()const;
	//最大挑战次数
	X_INT      getMaxChallengeNum()const;

	X_INT    getChallengeNum()const;

	//建议级别
	X_INT	 getRecommendLevel()const;

	//掉落描述
	X_CHAR *   getDropInfo()const;
	X_CHAR *   getImg()const;
	X_INT      getMonster()const;
	//刷新消耗
	X_UINT     getRefreshCost()const;

	X_INT     getEXP()const;
	X_INT     getHeroExp()const;
	X_INT	  getRewardMoney()const;

	X_INT     getID() const { return m_id; }

	/*enum EM_COPYSCENE_STATUS
	{
		EM_COPYSCENE_STATUS_INVALID = -1,
		EM_COPYSCENE_STATUS_CLOSE,		//未开启
		EM_COPYSCENE_STATUS_OPEN,		//开启未通过
		EM_COPYSCENE_STATUS_PASS,		//开启已通过
		EM_COPYSCENE_STATUS_NUMBER,
	};*/
	EM_COPYSCENE_STATUS    getStatus()const;//副本状态
	X_INT    getStar()const;//星级

	X_INT		GetAwardGold() const { return m_AwardGold; }
	 
	X_INT		GetItemCount() const { return m_Count; }

	X_BOOL		GetAwardItem(X_INT index, string& itemName,string& itemIcon,string& itemColor, X_INT& itemcount,X_INT &level)const;       

	X_INT		GetAwardHumanExp() const{  return m_AwardHumanExp; }


	vector<X_INT> GetDropItems();


protected:
	CopyScene(X_INT id);
	const stDBC_FILR_COPYSCENE * m_pTableData;
	X_INT m_id;
 
	X_CHAR		m_CopySceneStatus;		//副本状态
	X_CHAR		m_CopySceneStar;		//星级
	X_CHAR		m_ChallangeCount;		//今日已挑战次数


	X_INT		m_AwardGold;			//元宝奖励
	X_INT		m_AwardHumanExp;		//玩家经验奖励
	X_INT		m_Count;		//物品奖励个数
	X_INT		m_AwardItem[MAX_ITEMLIST_COUNT];//物品奖励
	X_INT		m_AwardItemCount[MAX_ITEMLIST_COUNT];

public:
	X_VOID		SetAwardGold(X_INT val) { m_AwardGold=val; }
	X_VOID		SetAwardHumanExp(X_INT val) { m_AwardHumanExp=val; }
	X_VOID		SetCount(X_INT c )   {   m_Count = c; }

	X_BOOL		AddAwardItem(X_INT index,X_INT itemid, X_INT itemcount)
	{
		if (itemid<0 || index >= m_Count)
		{
			return X_FALSE;
		}
		m_AwardItem[index]=itemid;
		m_AwardItemCount[index] = itemcount;
		return X_TRUE;
	}
	X_BOOL		GetAwardItem(X_INT index, X_INT& itemid, X_INT& itemcount)const
	{
		if (index<0 || index>=m_Count)
		{
			return X_FALSE;
		}
		itemid = m_AwardItem[index];
		itemcount = m_AwardItemCount[index];
		return X_TRUE;
	}

};
class CopySceneGroup
{
	friend class CopySceneManager;
public:

	X_CHAR * getName()const;
	X_CHAR * getInfo()const;
	const vector<CopyScene*>& getScenes()const
	{
		return m_pScene;
	}
	CopyScene*  getCopySceneById(X_INT id)const;
	bool isEnable()const {return m_bEnable;}
	CopyScene*  getMaxEnable() const;

	X_INT getGroupID() const { return m_GroupID; }

	bool isAsked()const {return m_bAsked;}
	X_VOID setAsked(bool bAsked){m_bAsked = bAsked; }


protected:
	X_VOID Initial();
	X_VOID Release();
	CopySceneGroup(X_INT id);
	vector<CopyScene*> m_pScene;
	X_INT m_GroupID;
	const stDBC_FILR_COPYSCENE_GROUP* m_pTableData;
	bool  m_bAsked;
	bool  m_bEnable;
};

 class CopySceneManager
 {
	public:
		X_VOID Initial();
		X_VOID Release();
		 X_VOID setPlayerEnableMaxGroup(X_INT group);

		 //----------------------------------------
		const vector<CopySceneGroup*>& getSceneGroups()const
		{
			return m_pSceneGroup;
		}
		CopySceneGroup* getCopySceneGroupById(X_INT id)const;

	 X_VOID SetCopyScene(CopySceneGroup* pGroup,X_INT copySceneID,X_INT copyStatus,X_INT copySceneStar,X_INT ChallangeCount);
 
	 CopyScene* findCopySceneByID(X_INT id, CopySceneGroup* & pGroup)const;
	 const CopySceneGroup* getCurSceneGroup()
	 {
		 return m_curCopySceneGroup;
	 }
	 const CopyScene* getCurScene()
	 {
		 return m_curCopyScene;
	 }
	 const CopySceneGroup* getMaxSceneGroup()
	 {
		 return m_maxCopySceneGroup;
	 }
	 X_VOID setCurScene(CopyScene* pScene)
	 {
		  m_curCopyScene = pScene;
	 }
	 X_VOID  setCurSceneGroup(CopySceneGroup *pGroup)
	 {
		 m_curCopySceneGroup = pGroup;
		 if (m_curCopySceneGroup &&m_curCopySceneGroup==m_maxCopySceneGroup)
		 {
			  m_curCopyScene = m_maxCopySceneGroup->getMaxEnable();
		 }

	 }

	 X_VOID setAwardScene(CopyScene* pScene)
	 {
		 m_awardScene = pScene;
	 }
	 const CopyScene* getAwardScene( )
	 {
		 return m_awardScene;
	 }
	 const CopyScene* getFightScene( )
	 {
		  if (m_FightScene == -1)
		  {
			  return X_NULL;
		  }
		  CopySceneGroup*  pGroup = X_NULL;
		  return findCopySceneByID(m_FightScene,pGroup);
	 }
	 X_VOID  setFightSceneId( X_INT id)
	 {
		 m_FightScene = id;
	 }
	 X_VOID setChangeGroup(bool bChange)
	 {
		 bChangeGroup  = bChange;
	 }
	 bool getChangeGroup( )
	 {
		 return bChangeGroup;
	 }
 protected:

	 vector<CopySceneGroup*> m_pSceneGroup;

	 CopySceneGroup* m_curCopySceneGroup;
	 CopyScene* m_curCopyScene;
	 CopyScene* m_awardScene;
	 CopySceneGroup* m_maxCopySceneGroup;
	 X_INT m_FightScene;
	 bool bChangeGroup;
 };

#endif
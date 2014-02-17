#ifndef __ACHIEVEMENT_DATA_H__
#define __ACHIEVEMENT_DATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"

struct AchieveData;
class Achieve
{
public:
	friend class AchievementData;
	Achieve();

	X_INT    getId()const{ return m_AchieveID;}
	EM_ACHIEVE_STATUS getStatus()const {return m_Status;};
	X_INT    getTimes()const{ return m_Times;}

	X_INT    getAllTimes()const;

	X_VOID    getItemNum(vector<X_INT>& num)const;
	X_VOID    getItemId(vector<X_INT>& id)const;
	X_INT     getGold()const{return pData->gold;}
	X_INT     getBear()const{return pData->bearAward;};

	const X_CHAR * getIcon()const;
	const X_CHAR * getName()const;
	string getDesc()const;
	const stDBC_FILE_ACHIEVE  * getTableData()const
	{
		return pData;
	}
private:
	X_INT				m_AchieveID;	//成就ID
	EM_ACHIEVE_STATUS	m_Status;		//状态
	X_INT				m_Times;		//次数
	bool setId(X_INT id);

	const stDBC_FILE_ACHIEVE  *pData;

};

/*enum  AchievementType
{
	ACHIEVEMENTTYPE_EVERYDAY = 0, //每日
	ACHIEVEMENTTYPE_CHARGE, //充值
	ACHIEVEMENTTYPE_NORMAL, //普通
	ACHIEVEMENTTYPE_HUODONG, //活动
	ACHIEVEMENTTYPE_MAX
};*/
class AchievementData
{
public:
	X_VOID Initial();
	X_VOID Release();
	X_VOID AddData(const AchieveData*   data);
	X_VOID Sort();
	bool   HasAchievementDone();
	Achieve* getData(X_INT id);
	X_VOID  Reset();
public:

	const vector<Achieve*>  & getAchieves()
	{
		return m_Achieves;
	}
	const vector<const Achieve*>  & getAchievesWithGroup(X_INT group);
	X_INT getAchievesGroupDoneNum(X_INT group);
	X_INT getAchievesGroupAllNum(X_INT group);
	X_INT getAchievesLayerNum();
	X_BOOL getAchievesGroupisNull(X_INT group);//ture 表示没有成就
	const stDBC_FILE_ACHIEVE_GROUP	* getAchievesGroupTbaleData(X_INT group);

	  vector<X_INT>    getAchievesGroupIds();
protected:

	vector<Achieve*>   m_Achieves;
	static	 X_BOOL	 __dataSort1(const Achieve *p1,const Achieve *p2);


	static	 X_BOOL	 __dataSort2(const Achieve *p1,const Achieve *p2);

	
	typedef map< X_INT,vector<const Achieve*> >  ACHIEVES;
	ACHIEVES  m_AchievesMap;
	void  __addAchieveToGroup(const Achieve* pData);
	void  __onAchieveStatsChange();
	X_INT  __calcAchievementDoneNum( const vector<const Achieve*> & vec);
	map<X_INT,X_INT> m_DoneNum;//第一个元素和m_AchievesMap第一个元素 一样
	static  string sortKey;
};

 


#endif // !__HERO_ALTAR_DATA_H__

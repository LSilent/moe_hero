#ifndef __QUEST_DATA_H__
#define __QUEST_DATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"
#include "./GameObjectDefine.h"
#include "./GameStruct.h"
 

	/* 
	MISSION_STATUS_NOT_ACCEPT,		//=0  未接
	MISSION_STATUS_NOT_COMPLETE,	//=1  已接未完成
	MISSION_STATUS_NOT_SUBMIT,		//=2  完成未交
	MISSION_STATUS_FAIL,			//=3  失败
	MISSION_STATUS_DONE,			//=4  完成已交
 */
class Quest
{
	
public:

	Quest();

public:
	friend class  QuestData;
    bool setServerData( const MissionData* pData);
	
public:

	X_INT getId()const{return m_MissionID;}
	MISSION_STATUS getStatus()const{return m_Status;}

	X_INT getAwardgold()const;
	X_INT getAwardAction()const;
	X_CHAR* getIcon()const;
	X_INT getCopySceneId()const;
	X_INT getNum()const;
	X_INT getDoneNum()const;
	X_CHAR* getDesc()const;
	X_VOID GetDropItems(vector<X_INT>& items,vector<X_INT>& itemNums)const;
protected:
	X_INT		m_MissionID;		// 任务表格ID
	MISSION_STATUS	m_Status;		// 任务状态
	X_INT			m_Param[MAX_MISSION_PARAM_COUNT];
	const stDBC_FILE_QUEST * m_pTableData;

	

};

class QuestData
{
public:
	X_VOID Initial();
	X_VOID Release();
	X_VOID setServerData( const MissionData* pData);
	X_VOID sortData();
public:
	const vector<Quest*> & getQuest(){ return m_Quest;}
	bool getNewFlag(){ return m_bNewFlag;}
	X_VOID setNewFlag(bool b){   m_bNewFlag = b;}


	bool isAsked(){return m_bAsked;}
	X_VOID setAsked(){ m_bAsked = true;}
	Quest *getQuestbyId(X_INT id);

protected:
	 
	vector<Quest*>  m_Quest;
	bool m_bAsked;
	bool m_bNewFlag;
	static bool	 __dataSort1(const Quest *p1,const Quest *p2);
};

#endif
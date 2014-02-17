#ifndef __HUODONG_H__
#define __HUODONG_H__

#include "./base/Global.h"

/*enum EM_ID_HUODONG
{
	EM_ID_HUODONG_EATCHEESE1=1,		//1==������1
	EM_ID_HUODONG_EATCHEESE2,		//2==������2
	EM_ID_HUODONG_EATCHEESE3,		//3==������3
	EM_ID_HUODONG_GANK1,			//4==gank1
	EM_ID_HUODONG_GANK2,			//5==gank2
	EM_ID_HUODONG_GANK3,			//6==gank3
	EM_ID_HUODONG_DAYE1,			//7==��Ұ1
	EM_ID_HUODONG_DAYE2,			//8==��Ұ2
	EM_ID_HUODONG_DAYE3,			//9==��Ұ3
	EM_ID_HUODONG_DUIXIAN1,			//10==����1
	EM_ID_HUODONG_DUIXIAN2,			//11==����2
	EM_ID_HUODONG_DUIXIAN3,			//12==����3
}*/

enum EM_STATE_HUODONG_CLIENT
{
	EM_C_STATE_HUODONG_INVALID=-1,
	EM_C_STATE_HUODONG_DIABLE,			//δ����
	EM_C_STATE_HUODONG_RUN,				//������
	EM_C_STATE_HUODONG_END,				//����
	EM_C_STATE_DONE,					//�Ѿ����
	EM_C_STATE_HUODONG_NUMBER,
};

enum EM_HUODONG_TYPE
{
	EM_INVALID_HUODONG_TYPE =-1,
	EM_EATCHEESE ,
	EM_GANK,
	EM_FARM,//��Ұ��
	//EM_LINE,
	EM_ALTAR,
	EM_ACTION,
	EM_HUSONG_WOOD,
	EM_BLOODBATTLE,
	EM_SHAKE,
	EM_HOUDONG_TYPE_NUM,
};
class HuoDong
{
public:
	const char * getWeek();
	string getTime();
	string getEndTime();
	X_INT getcontinueTime();
	const char * getName();
	X_INT getId();
	X_INT getLevelNeed();
	X_INT getAddAction();
	X_INT getCopySceneId();
	X_INT getCopySceneNeedAction();

	EM_STATE_HUODONG_CLIENT getState();

	EM_HUODONG_TYPE GetType();

	//�õ��ʣ�����
	X_INT getNum();
protected:
	friend class HuoDongData;
	X_INT	m_Id;
	EM_STATE_HUODONG	m_State;
	X_INT	m_Param;
};


class HuoDongData
{
public:
	X_VOID Initial();
	X_VOID Release();
public:
	X_VOID setHuoDong(X_INT id,X_INT state,X_INT param);
	X_VOID setHuoDongState(X_INT id,X_INT state,X_INT param);

	const vector<HuoDong*> & getHuoDong(){ return m_HuoDong;}

	X_BOOL    getShakeHuoDongEnable();
	X_VOID   Tick(X_UINT nTime);

	X_VOID   ShakeBegin(X_BOOL b)
	{
		m_ShakeTiming = b;
	}
	X_BOOL isShakeBegin()
	{
		return m_ShakeTiming;
	}
	X_INT getShakeTime()//s
	{
		return m_ShakeTime;
	}
	X_INT getShakeNum()
	{
		return m_ShakeNum;
	}
	X_VOID resetShakeTime();
	 
	X_VOID setShakeNum(X_INT num,bool waitTime = true);
 
	X_VOID   ShakeReady(X_BOOL b);
	X_BOOL isShakeReady()
	{
		return m_ShakeReady;
	}

	X_VOID onShake();

	X_BOOL canShake();
protected:

	vector<HuoDong*>  m_HuoDong;

	X_INT     m_ShakeTime;
	X_BOOL    m_ShakeTiming;
	X_INT	  m_ShakeNum;	

	X_BOOL    m_ShakeReady;
};


#endif
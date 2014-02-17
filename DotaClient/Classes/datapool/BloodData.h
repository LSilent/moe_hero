#ifndef __BLOODDATA_H__
#define __BLOODDATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"
#include "./GameObjectDefine.h"
#include "./GameStruct.h"
 
 
 class GCStairPlusPacket;
 class GCStairRetEnterPacket;
 class GCStairMonsterGroupPacket;


 class  BattleLayer
 {
 public:
	  BattleLayer();
	 ~ BattleLayer();
	 X_VOID CleanUp();

 public:

	 X_INT			m_Layer;								//��ǰ��
	 X_INT			m_AccStar;								//�����
	 X_INT			m_CurStar;								//ʣ�����
	 X_INT			m_NextPlusLayers;						//ʣ��ӳɳ���
	 X_INT			m_PlusAtt;								//���ӳ�
	 X_INT			m_PlusDef;								//���ӳ�
	 X_INT			m_PlusHp;								//Ѫ�ӳ�
	 StairMonster	m_MonsterGroup[MAX_STAIR_MONSER_GROUP];	//������
	 X_INT			m_MaxTotalStar;							//����ۼƵ���
	 X_INT			m_MaxPassLayers;						//���ͨ������


 };

  

class BloodData
{
public:
	X_VOID Initial();
	X_VOID Release();
 
public:
	//--------------enter����---------------------------------
	X_INT				GetTimes(){return m_Times;}
	X_INT				GetLeftTimes(){return m_LeftTimes;}
	X_INT				GetLayer(){return m_Layer;}
	X_INT				GetMaxTotalStar(){return m_MaxTotalStar;}
	X_INT				GetMaxPassLayers(){return m_MaxPassLayers;}
	//-------buffer����------------------------------------------
	
	X_BOOL   isBegin(){ return m_Begin;}
	X_INT *  getCostStar(){ return m_Star;}
	X_INT *  getBufferPlus(){ return m_Plus;}

	//-------------------------------------------------------------------
	BattleLayer * getLayerMonster()
	{
		return m_pLayer;
	}

public:
	 
	 X_VOID handleStairPlusPacket(GCStairPlusPacket* pPacket);

	 X_VOID handleStairEnterPacket(GCStairRetEnterPacket* pPacket);
	 
	 X_VOID handleMonsterPacket(GCStairMonsterGroupPacket* pPacket);
	 
	 X_INT				GetStar(){return m_AwardStar;}
	 X_VOID				SetStar(X_INT val){m_AwardStar = val;}
	 X_INT				GetExp(){return m_AwardExp;}
	 X_VOID				SetExp(X_INT val){m_AwardExp = val;}
	 X_INT				GetItemID(){return m_AwardItemID;}
	 X_VOID				SetItemID(X_INT val){m_AwardItemID = val;}



 
	X_VOID  NextStep();

	X_VOID HanlderBufferSelect()
	{
		m_BufferComingNum -- ;
		NextStep();
	}

	X_VOID  EnterBloodUi();
	bool isBattleNextOk(){ return m_BattleNextOk;}
	X_VOID setBattleNextOk(bool b ){   m_BattleNextOk = b;}
protected:
 
	X_INT			m_Times;								//���ش���
	X_INT			m_LeftTimes;							//ʣ�����
	X_INT			m_Layer;								//��ǰ��
	X_INT			m_MaxTotalStar;							//����ۼƵ���
	X_INT			m_MaxPassLayers;						//���ͨ������

	//-------------------------------------------------------------------------------------------------
	X_BOOL	m_Begin;						//true ���ʼ�ӳ� �����Ļ���  false ÿ3����⽱���ӳ� 
	X_INT	m_Star[STAIR_PLUS_COUNT];		//���Ļ���	 �����±�0Ϊ����1Ϊ����2ΪѪ
	X_INT	m_Plus[STAIR_PLUS_COUNT];		//�ӳ�

	X_INT   m_BufferComingNum;
	//-------------------------------------------------------------------------------------------------

	BattleLayer *m_pLayer;
	//----------------------����

	X_INT	m_AwardStar;			//��õ÷�
	X_INT	m_AwardExp;		//����ٻ�ʦ����
	X_INT	m_AwardItemID;		//�����Ʒ
	bool    m_BattleNextOk;
};
#endif
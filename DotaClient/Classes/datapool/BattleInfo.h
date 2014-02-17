#ifndef __BATTLEINFO_H__
#define __BATTLEINFO_H__

#include "./base/Global.h"

class  Impact
{
public:

	static string GetIcon(X_INT id);
	static string GetEffect(X_INT id);
	static string GetEffectSound(X_INT id);
	static string GetName(X_INT id);
	static string GetDesc(X_INT id);
	static bool  isPlayOnce(X_INT id);

	static string GetHitEffect(X_INT id);
	static string GetHitEffectSound(X_INT id);

	 //�������� ����Ч��x ����Ч��y	
	static X_VOID  GetEffectParam(X_INT id,float &_scale,float & _x,float &_y);

	static X_VOID  GetHitEffectParam(X_INT id,float &_hitScale,float & _hitEffectX,float &_hitEffectY);

	static float  GetEffectPlaySpeed(X_INT id);
	static float  GetHitEffectPlaySpeed(X_INT id);
	static  int  GetType(X_INT id);

	Impact(X_INT id);
	string GetIcon();
	string GetEffect();
	string GetEffectSound();
	string GetHitEffect();//�����ܻ�Ч��
	string GetHitEffectSound();
	string GetName();
	string GetDesc();
	X_INT GetID() { return m_id; }

	bool  isPlayOnce();
	X_VOID  GetEffectParam(float &_scale,float & _x,float &_y);

	X_VOID  GetHitEffectParam(float &_hitScale,float & _hitEffectX,float &_hitEffectY);

	 float  GetEffectPlaySpeed();
	 float  GetHitEffectPlaySpeed();

	 //�Ƿ���
	 int   GetType();
protected:

	X_INT m_id;
	X_CHAR * m_name;
	X_CHAR * m_icon;
	X_CHAR * m_desc;
	X_CHAR * m_effect;
};

class  Skill
{
public:
	static int  GetEffectLogicType(X_INT id);
	static string GetIcon(X_INT id);
	static string GetCastEffect(X_INT id);//�����ͷ���Ч
	static int GetCastAction(X_INT id);//�����ͷŶ���

	static string GetEffect(X_INT id);//������Ч����
	static string GetBeHurtEffect(X_INT id);//�ܻ���Ч
	static int GetBeHurtAction(X_INT id);//�ܻ�����

	static string GetName(X_INT id);
	static string GetDesc(X_INT id);
	static int  GetLevel(X_INT id);
    //����ʩ��λ�ã�0Ϊԭ�أ�1Ϊ��ĳһ��ǰ��2Ϊ��Ŀ��ǰ��3Ϊ���з���������
	static int GetCastPostion(X_INT id);
   //��Ч�����ͣ�0Ϊֻ���ܻ���1Ϊ��Ե㣬2Ϊ�����������Ŀ����ʧ��3Ϊ��̶����������壬4Ϊһ������Ĵ���Ч��
	static int GetEffectType(X_INT id);

	// ʩ����Ч���ű��� //ʩ����Чxƫ���� //ʩ����Чyƫ����
	static X_VOID  GetShotEffectParam(X_INT id,float &_ShotEffectScale,float & _ShotEffectX,float &_ShotEffecty);

	static X_VOID  GetEffectParam(X_INT id,float &_effectScale,float & _effectX,float &_effectY);

	static X_VOID  GetHitEffectParam(X_INT id,float &_hitEffectScale,float & _hitEffectX,float &_hitEffectY);

	static float  GetEffectSpeed(X_INT id);
	static string GetShotEffectSound(X_INT id);//ʩ����Ч����
	static string GetEffectSound(X_INT id);//������Ч����
	static string GetHitEffectSound(X_INT id);//�ܻ���Ч����

	static float  GetShotEffectPlaySpeed(X_INT id);
	static float  GetEffectPlaySpeed(X_INT id);
	static float  GetHitEffectPlaySpeed(X_INT id);

	//���л���x yƫ����
	static float  GetHitoffsetX(X_INT id);
	static float  GetHitoffsetY(X_INT id);

	//��ʼx yƫ����
	static float  GetShotoffsetX(X_INT id);
	static float  GetShotoffsetY(X_INT id);
	
};



#endif // !__BATTLEINFO_H__

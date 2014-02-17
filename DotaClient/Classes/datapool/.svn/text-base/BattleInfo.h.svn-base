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

	 //技能缩放 技能效果x 技能效果y	
	static X_VOID  GetEffectParam(X_INT id,float &_scale,float & _x,float &_y);

	static X_VOID  GetHitEffectParam(X_INT id,float &_hitScale,float & _hitEffectX,float &_hitEffectY);

	static float  GetEffectPlaySpeed(X_INT id);
	static float  GetHitEffectPlaySpeed(X_INT id);
	static  int  GetType(X_INT id);

	Impact(X_INT id);
	string GetIcon();
	string GetEffect();
	string GetEffectSound();
	string GetHitEffect();//技能受击效果
	string GetHitEffectSound();
	string GetName();
	string GetDesc();
	X_INT GetID() { return m_id; }

	bool  isPlayOnce();
	X_VOID  GetEffectParam(float &_scale,float & _x,float &_y);

	X_VOID  GetHitEffectParam(float &_hitScale,float & _hitEffectX,float &_hitEffectY);

	 float  GetEffectPlaySpeed();
	 float  GetHitEffectPlaySpeed();

	 //是否单体
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
	static string GetCastEffect(X_INT id);//技能释放特效
	static int GetCastAction(X_INT id);//技能释放动作

	static string GetEffect(X_INT id);//技能特效本身
	static string GetBeHurtEffect(X_INT id);//受击特效
	static int GetBeHurtAction(X_INT id);//受击动作

	static string GetName(X_INT id);
	static string GetDesc(X_INT id);
	static int  GetLevel(X_INT id);
    //技能施放位置（0为原地，1为到某一列前，2为到目标前，3为到敌方整体区域）
	static int GetCastPostion(X_INT id);
   //特效的类型（0为只有受击，1为点对点，2为发射物体击中目标消失，3为向固定方向发射物体，4为一个区域的大特效）
	static int GetEffectType(X_INT id);

	// 施放特效缩放比例 //施放特效x偏移量 //施放特效y偏移量
	static X_VOID  GetShotEffectParam(X_INT id,float &_ShotEffectScale,float & _ShotEffectX,float &_ShotEffecty);

	static X_VOID  GetEffectParam(X_INT id,float &_effectScale,float & _effectX,float &_effectY);

	static X_VOID  GetHitEffectParam(X_INT id,float &_hitEffectScale,float & _hitEffectX,float &_hitEffectY);

	static float  GetEffectSpeed(X_INT id);
	static string GetShotEffectSound(X_INT id);//施放特效声音
	static string GetEffectSound(X_INT id);//本体特效声音
	static string GetHitEffectSound(X_INT id);//受击特效声音

	static float  GetShotEffectPlaySpeed(X_INT id);
	static float  GetEffectPlaySpeed(X_INT id);
	static float  GetHitEffectPlaySpeed(X_INT id);

	//飞行击中x y偏移量
	static float  GetHitoffsetX(X_INT id);
	static float  GetHitoffsetY(X_INT id);

	//起始x y偏移量
	static float  GetShotoffsetX(X_INT id);
	static float  GetShotoffsetY(X_INT id);
	
};



#endif // !__BATTLEINFO_H__

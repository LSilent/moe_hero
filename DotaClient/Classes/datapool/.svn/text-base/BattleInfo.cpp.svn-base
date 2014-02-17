#include "./datapool/BattleInfo.h"
#include "./database/DataBaseSystem.h"

string Impact::GetIcon(X_INT id)
{

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_icon;
}
string Impact::GetEffect(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effect;
}
string Impact::GetEffectSound(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_sound;
}

	 
string Impact::GetHitEffect(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_hitEffect;
}
string Impact::GetHitEffectSound(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_hitSound;
} 
string Impact::GetName(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_name;
}
string Impact::GetDesc(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_desc;
}
//EM_IMPACT_LOGIC
 

bool Impact::isPlayOnce(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return  m_pTableData->_logicId < EM_IMPACT_LOGIC2;
}
X_VOID  Impact::GetEffectParam(X_INT id,float &_scale,float & _x,float &_y)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	 _scale = m_pTableData->_sacle;
	 _x = m_pTableData->_x;
	  _y = m_pTableData->_y;
}

X_VOID  Impact::GetHitEffectParam(X_INT id,float &_hitScale,float & _hitEffectX,float &_hitEffectY)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	_hitScale = m_pTableData->_hitScale;
	_hitEffectX = m_pTableData->_hitEffectX;
	_hitEffectY = m_pTableData->_hitEffectY;
}

float  Impact::GetEffectPlaySpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->speed;
}
float  Impact::GetHitEffectPlaySpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
	const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->hitspeed;
}
 
int  Impact::GetType(X_INT id)
{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_IMPACT);
		const stDBC_FILE_IMPACT	* m_pTableData = (const stDBC_FILE_IMPACT*)pDataFile->GetFieldsByIndexKey(id);
		return m_pTableData->entire;
}
Impact::Impact(X_INT id)
{
	m_id = id;
}
string Impact::GetIcon()
{
	return Impact::GetIcon(m_id);
}
string Impact::GetEffect()
{
	return Impact::GetEffect(m_id);
}
string Impact::GetHitEffect()
{
	return Impact::GetHitEffect(m_id);
}
string Impact::GetEffectSound()
{
	return Impact::GetEffectSound(m_id);
}
string Impact::GetHitEffectSound()
{
	return Impact::GetHitEffectSound(m_id);
}
string Impact::GetName()
{
	return Impact::GetName(m_id);
}
string Impact::GetDesc()
{
	return Impact::GetDesc(m_id);
}
bool  Impact::isPlayOnce()
{
	return Impact::isPlayOnce(m_id);
}
X_VOID  Impact::GetEffectParam(float &_scale,float & _x,float &_y)
{
	Impact::GetEffectParam(m_id,_scale,_x,_y);
}

X_VOID  Impact::GetHitEffectParam(float &_hitScale,float & _hitEffectX,float &_hitEffectY)
{
	Impact::GetEffectParam(m_id,_hitScale,_hitEffectX,_hitEffectY);
}
float   Impact::GetEffectPlaySpeed()
{
	return Impact::GetEffectPlaySpeed(m_id);
}
float   Impact::GetHitEffectPlaySpeed()
{
	return Impact::GetHitEffectPlaySpeed(m_id);
}

 int   Impact::GetType()
 {
	 return Impact::GetType(m_id);
 }
 int  Skill::GetEffectLogicType(X_INT id)
 {
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	 const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	 return m_pTableData->_type;
 }
string Skill::GetIcon(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_icon;
}
 
string Skill::GetCastEffect(X_INT id)//技能释放特效
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_casteffect;
}
int Skill::GetCastAction(X_INT id)//技能释放动作
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_handUpAction;
}
string Skill::GetEffect(X_INT id)//技能特效本身
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effect;
}
string Skill::GetBeHurtEffect(X_INT id)//受击特效
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effectHit;
}
int Skill::GetBeHurtAction(X_INT id)//受击动作
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_hitAction;
}

string Skill::GetName(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_name;
}
string Skill::GetDesc(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_desc;
}
int Skill::GetLevel(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_level;
}
int Skill::GetCastPostion(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_castPostion;
}
int Skill::GetEffectType(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effectType;
}
X_VOID  Skill::GetShotEffectParam(X_INT id,float &_ShotEffectScale,float & _ShotEffectX,float &_ShotEffecty)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	_ShotEffectScale = m_pTableData->_ShotEffectScale;
	_ShotEffectX = m_pTableData->_ShotEffectX;
	_ShotEffecty = m_pTableData->_ShotEffecty;
}

X_VOID  Skill::GetEffectParam(X_INT id,float &_effectScale,float & _effectX,float &_effectY)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	_effectScale = m_pTableData->_effectScale;
	_effectX = m_pTableData->_effectX;
	_effectY = m_pTableData->_effectY;
}
X_VOID  Skill::GetHitEffectParam(X_INT id,float &_hitEffectScale,float & _hitEffectX,float &_hitEffectY)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	_hitEffectScale = m_pTableData->_hitEffectScale;
	_hitEffectX = m_pTableData->_hitEffectX;
	_hitEffectY = m_pTableData->_hitEffectY;
}

float  Skill::GetEffectSpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effectSpeed;
}

string Skill::GetShotEffectSound(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_ShotEffectSound;
}
string Skill::GetEffectSound(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_effectSound;
}
string Skill::GetHitEffectSound(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->_hitEffectSound;
}
float   Skill::GetShotEffectPlaySpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->shotplaySpeeds;
}
float   Skill::GetEffectPlaySpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->playSpeeds;

}
float   Skill::GetHitEffectPlaySpeed(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->hitplaySpeeds;
}
float   Skill::GetHitoffsetX(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->hitoffsetX;
}

float   Skill::GetHitoffsetY(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->hitoffsetY;
}
float   Skill::GetShotoffsetX(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->shotoffsetX;
}

float   Skill::GetShotoffsetY(X_INT id)
{
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(id);
	return m_pTableData->shotoffsetY;
}
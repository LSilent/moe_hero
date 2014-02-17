#ifndef __OBJECTSKILL_H__
#define __OBJECTSKILL_H__


#include "./object/Object.h"
#include "./database/DataBaseSystem.h"
class ObjectFactory;
class ObjectSkill :public Object
{
	friend class ObjectHero;
public:

	static ObjectFactory * __getFactory(); 
	virtual X_VOID   Release();
	X_VOID	SetSkillIndex(const X_UINT nIndex);
	X_UINT	GetSkillIndex() const;

	bool SetTableId(X_INT nTableID);
	X_CHAR * GetIcon()const;
	X_CHAR * GetName()const;
	X_CHAR * GetDesc()const;
	//---------------------------
	bool IsTop() const;
	X_INT GetTableId()const;
	const stDBC_FILE_SKILL * GetTableData()const;
	X_INT 	getSucessRate()const;

	X_INT GetLevel()const;


	inline void setUserData(void* pUserData)
    {
        m_pUserData = pUserData;
    } 
    inline void* getUserData()const
    {
        return m_pUserData;
    }
protected:
	ObjectSkill(X_CLIENT_GUID guid);
	virtual ~ObjectSkill();
	class Factory;

	X_INT        m_TableId;
	X_INT		 m_Level;
	const stDBC_FILE_SKILL *m_pTableData;
	X_UINT					m_SkillIndex;
	void*                    m_pUserData;  
};

 
#endif // !__OBJECTSKILL_H__

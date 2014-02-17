#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "./base/Global.h"
 
enum OBJECT_TYPE
{
	OBJECT_TYPE_INVALID = -1,
	OBJECT_TYPE_ITEM,
	OBJECT_TYPE_PLAYER,
	OBJECT_TYPE_SELF,
	OBJECT_TYPE_HERO,
	OBJECT_TYPE_MONSTER,
	OBJECT_TYPE_SKILL,
	OBJECT_TYPE_FARM,
	OBJECT_TYPE_MAXNUM
};
 

class Object 
{
	friend class ObjectFactory;
	friend class ObjectManager;
protected:
	Object();
	virtual ~Object();
	virtual X_VOID Release();
	virtual	X_VOID Tick(X_UINT nTime){}
	OBJECT_TYPE m_Type;
	X_CLIENT_GUID		m_Guid;
public:

	OBJECT_TYPE GetType()const{ return m_Type; }
	X_CLIENT_GUID GetGuid()const{ return m_Guid; }
	 X_VOID  SetObjectType(OBJECT_TYPE nObjectType) {m_Type = nObjectType;}
	 
};

 


#endif //__OBJECT_H__
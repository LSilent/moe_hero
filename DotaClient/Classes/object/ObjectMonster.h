#ifndef __OBJECTMONSTER_H__
#define __OBJECTMONSTER_H__
 
#include "./object/Object.h"
#include "./object/MonsterData.h"
 

class ObjectFactory;
class ObjectMonster  :public Object
{

public:

	static ObjectFactory * __getFactory(); 

	MonsterData*  getData()
	{
		return m_pData;
	}
	virtual X_VOID  Release();
protected:
	ObjectMonster(X_CLIENT_GUID guid);
	virtual ~ObjectMonster();
	class Factory;

protected:
	MonsterData*  m_pData;
 

};

 


#endif //__OBJECTMONSTER_H__
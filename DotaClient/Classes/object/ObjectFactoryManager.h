#ifndef __OBJECTFACTORYMANAGER_H__
#define __OBJECTFACTORYMANAGER_H__

#include "./base/Global.h"
#include "./object/ObjectFactory.h"

#include <map>

class  ObjectFactoryManager
{
public:
	ObjectFactoryManager() {}
	virtual ~ObjectFactoryManager() {}
public:

	typedef  map<OBJECT_TYPE,ObjectFactory*> ObjectFactoryMap;

	ObjectFactory* FindFactory(OBJECT_TYPE type) const
	{
		  ObjectFactoryMap::const_iterator iFind =   m_Factorys.find(type);
		  if (iFind != m_Factorys.end())
		  {
			  return iFind->second;
		  }
		return X_NULL;
	}
	X_BOOL HasFactory(OBJECT_TYPE type)
	{
		return m_Factorys.end() != m_Factorys.find(type);

	}
	X_VOID  RegisterFactory(ObjectFactory * factory)
	{
		if(factory == X_NULL) return;
		OBJECT_TYPE type = factory->GetType();
		if(HasFactory(type))	return;
		m_Factorys[type] = factory;
	}

	X_VOID  unRegisterFactory(ObjectFactory * factory)
	{
		if(factory == X_NULL) return;
		OBJECT_TYPE type = factory->GetType();
		if(HasFactory(type) == XFALSE)	return;
		m_Factorys.erase(type);
	}
	 
	virtual  Object* CreateInstance(OBJECT_TYPE type, X_CLIENT_GUID guid) const
	{
		ObjectFactory*  factory = FindFactory(type);
		if (factory == X_NULL)
		{
			return X_NULL;
		}

		return factory->CreateInstance(guid);
	}
 
	virtual X_VOID DestroyInstance( Object* pObject)
	{
		if(pObject == X_NULL) return;
	
		ObjectFactory*  factory = FindFactory(pObject->GetType());
		if(factory != X_NULL)
		{
			factory->DestroyInstance(pObject);
		}
	}
protected:

	ObjectFactoryMap  m_Factorys;
 
};

#endif
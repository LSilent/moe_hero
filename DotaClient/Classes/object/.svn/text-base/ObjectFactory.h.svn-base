#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__

#include "./base/Global.h"
#include "./object/Object.h"
 
class  ObjectFactory
{
public:
	ObjectFactory() {}
	virtual ~ObjectFactory() {}
	virtual OBJECT_TYPE GetType() const = 0;
	virtual Object* CreateInstance(X_CLIENT_GUID guid) = 0;
	virtual X_VOID DestroyInstance( Object* object) { object->Release(); SAFE_DELETE(object); }
};

#endif
#ifndef __OBJECTFARMR_H__
#define __OBJECTFARMR_H__
 
#include "./object/Object.h"


class ObjectFactory;
class ObjectFarm  :public Object
{

public:
	class Factory;
	static ObjectFactory * __getFactory(); 
 
protected:
	ObjectFarm(X_CLIENT_GUID guid);
	virtual ~ObjectFarm();
public: 

	X_VOID Initial();
	virtual X_VOID Release();
	X_VOID	SetFarmIndex(const X_UINT nIndex);
	X_UINT	 GetFarmIndex() const;
protected:
	 
	X_UINT m_FarmIndex;
};

 


#endif //__OBJECTFARMR_H__
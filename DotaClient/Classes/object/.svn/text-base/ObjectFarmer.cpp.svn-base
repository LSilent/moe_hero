#include "./object/ObjectFarm.h"
#include "./object/ObjectFactory.h"
#include "./datapool/DataPool.h"

class ObjectFarm::Factory : public ObjectFactory
{
	public:
	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_FARM;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectFarm(guid);
	}

};
ObjectFactory * ObjectFarm::__getFactory()
{
	static Factory factory;
	return &factory;
}


ObjectFarm::ObjectFarm(X_CLIENT_GUID guid)
{
	m_Guid = guid;
	m_FarmIndex = -1;
 

}
ObjectFarm::~ObjectFarm()
{
	 
}
X_VOID  ObjectFarm::Release()
{
	 
}
 
X_VOID	ObjectFarm::SetFarmIndex(const X_UINT nIndex)
{
	m_FarmIndex = nIndex;
}
X_UINT	ObjectFarm::GetFarmIndex() const
{
	return m_FarmIndex;
}
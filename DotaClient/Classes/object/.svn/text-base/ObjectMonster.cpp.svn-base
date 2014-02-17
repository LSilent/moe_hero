#include "./object/ObjectMonster.h"
#include "./object/ObjectFactory.h"
class ObjectMonster::Factory : public ObjectFactory
{
	public:
	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_MONSTER;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectMonster(guid);
	}

};
ObjectFactory * ObjectMonster::__getFactory()
{
	static Factory factory;
	return &factory;
}


ObjectMonster::ObjectMonster(X_CLIENT_GUID guid)
{
	m_Guid = guid;
	m_pData = new MonsterData();
	m_pData->Initial();

 

}
ObjectMonster::~ObjectMonster()
{

}
 
 X_VOID  ObjectMonster::Release()
{
	if (m_pData)
	{
		m_pData->Release();
		SAFE_DELETE(m_pData);
	}
}

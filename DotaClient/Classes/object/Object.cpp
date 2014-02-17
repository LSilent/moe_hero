#include "./object/Object.h"
 
Object::Object()
{
	m_Type = OBJECT_TYPE_INVALID;
	m_Guid = -1;
}
Object::~Object()
{
	 
}
 
X_VOID Object::Release()
{

}
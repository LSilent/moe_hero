#include "./object/ObjectSkill.h"
#include "./object/ObjectFactory.h"

class ObjectSkill::Factory : public ObjectFactory
{
public:
	virtual  OBJECT_TYPE GetType() const
	{
		return OBJECT_TYPE_SKILL;
	}
	virtual Object* CreateInstance(X_CLIENT_GUID guid)
	{
		return new ObjectSkill(guid);
	}

};
ObjectFactory * ObjectSkill::__getFactory()
{
	static Factory factory;
	return &factory;
}
ObjectSkill::ObjectSkill(X_CLIENT_GUID guid)
{
	m_Guid = guid;
	m_SkillIndex = -1;
	m_Level = 1;
	m_pUserData = NULL;
}
ObjectSkill::~ObjectSkill()
{
	 m_pUserData = NULL;
}

 X_VOID  ObjectSkill::Release()
 {

 }
 bool ObjectSkill::SetTableId(X_INT nTableID)
 {
	 m_TableId = nTableID;
	 const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
	 if (pDataFile)
	 {
		 m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(m_TableId);
		 if (m_pTableData)
		 {
			 m_Level =  m_pTableData->_level;
			 return true;
		 }
	 }
	 return false;
 }
X_CHAR * ObjectSkill::GetIcon()const
 {
	 if (m_pTableData)
	 {
		return m_pTableData->_icon;
	 }
	 return "";
 }
 X_CHAR *ObjectSkill::GetName()const
 {
	 if (m_pTableData)
	 {
		 return m_pTableData->_name;
	 }
	 return "";
 }
X_CHAR * ObjectSkill::GetDesc()const
 {
	 if (m_pTableData)
	 {
		 return m_pTableData->_desc;
	 }
	 return "";
 }
 X_VOID	ObjectSkill::SetSkillIndex(const X_UINT nIndex)
 {
	 m_SkillIndex = nIndex;
 }
 X_UINT	ObjectSkill::GetSkillIndex() const
 {
	 return m_SkillIndex;
 }
 bool ObjectSkill::IsTop() const
 {
	 if (m_pTableData)
	 {
		 return m_pTableData->_level == 4;
	 }  
	 return false;
 }
 X_INT ObjectSkill::GetTableId()const
{
	return m_TableId;
}
 const stDBC_FILE_SKILL * ObjectSkill::GetTableData()const
 {
	 return m_pTableData;
 }
 X_INT 	ObjectSkill::getSucessRate()const
 {
	 if (m_pTableData)
	 {
		 m_pTableData->_LearnRate;
	 }
	 return 100;
 }
 X_INT ObjectSkill::GetLevel()const
 {
	 return m_Level;
 }
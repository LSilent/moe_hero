#include "./database/DataBase.h"
#include "./load/ResourceSystem.h"
#include "./base/UtilTools.h"
#include "cocos2d.h"

USING_NS_CC ;

DataBase::DataBase(X_INT nFileID)
{
	m_pFileDBC = new DBFile(nFileID);
}

DataBase::~DataBase()
{
	SAFE_DELETE(m_pFileDBC);
}

const DBFile::FIELD* DataBase::GetFieldsByIndexKey(X_INT nKeyValue) const
{
	return (DBFile::FIELD*)m_pFileDBC->GetFieldsByIndexKey(nKeyValue);
}

const DBFile::FIELD* DataBase::GetFieldsByLineNum(X_INT nLineNum) const
{
	return  (DBFile::FIELD*)m_pFileDBC->GetFieldsByPosistion(nLineNum, 0); 
}
const DBFile::FIELD* DataBase::GetFirstFieldsByColumn(X_INT nColumnNum, const DBFile::FIELD& value) const
{
	return (DBFile::FIELD*)m_pFileDBC->GetFirstFieldsByColumn(nColumnNum, value.iValue);
}

X_INT	DataBase::GetDBFileID()const
{
	return m_pFileDBC->GetDBFileID();
}

X_UINT DataBase::GetFieldsNum()const
{
	return m_pFileDBC->GetFieldsNum(); 
}

X_UINT DataBase::GetRecordsNum()const
{
	return m_pFileDBC->GetRecordsNum(); 
}
/*
X_BOOL DataBase::CreateDBFromFile(const X_CHAR* szFileName)
{ 
	if(!szFileName || strlen(szFileName)== 0 || !m_pFileDBC)
		return XFALSE;

	string fileName = szFileName;

#define RES_USE_UTF8 1

#ifdef   RES_USE_UNICODE

	wchar_t* lpAddress;
	unsigned long dwSize = ResourceSystem::GetSingleton()->LoadResourceUnicode(szFileName, lpAddress);
	if(dwSize>0)
	{
		X_BOOL bRet = CreateDBFromMemory(lpAddress, dwSize);
		ResourceSystem::GetSingleton()->UnloadResourceUnicode( lpAddress, dwSize );
		return bRet;
	}
	return XFALSE;
#else

	char* lpAddress;
	unsigned long dwSize =  ResourceSystem::GetSingleton()->LoadResource(fileName.c_str(), lpAddress);

	if(dwSize>0)
	{
		X_BOOL bRet = XFALSE;
		int s = 0;
#ifdef   RES_USE_UTF8
		 
		// s = UtilTools::UTF8toToUnicode(uni,lpAddress);


		//wstring str =  UtilTools::utf8_wchar(lpAddress);
		//s = str.length();
		//bRet = CreateDBFromMemory(str.c_str(),s);


		bRet = CreateDBFromMemory(lpAddress,dwSize);



#else
		wchar_t *uni = 0; 
		 s = UtilTools::MultiByte2WideChar(uni,lpAddress);
		 bRet = CreateDBFromMemory(uni,s);
		 delete uni;
#endif
		ResourceSystem::GetSingleton()->UnloadResource( lpAddress, dwSize );
		return bRet;
	}
	return XFALSE;
#endif 
 
}*/
X_BOOL DataBase::CreateDBFromFile(const X_CHAR* szFileName)
{
	unsigned long dwSize = 0;
	const X_CHAR* data =    (const X_CHAR*)(CCFileUtils::sharedFileUtils()->getFileData(szFileName,"rb",&dwSize));
	X_BOOL bRet = CreateDBFromMemory(data,dwSize);
	delete data;
	return bRet;
}
X_BOOL DataBase::CreateDBFromMemory(const X_WCHAR* pMemStart, const X_ULLONG dwSize)
{
	X_BOOL bRet = XFALSE;
	if (X_NULL != m_pFileDBC && dwSize > 0)
	{
		bRet = m_pFileDBC->CreateDBFromMemory( pMemStart, pMemStart + dwSize);
	}
	return bRet;
}
X_BOOL	DataBase::CreateDBFromMemory(const X_CHAR* pMemStart, const X_ULLONG dwSize)
{
	X_BOOL bRet = XFALSE;
	if (X_NULL != m_pFileDBC && dwSize > 0)
	{
		bRet = m_pFileDBC->CreateDBFromMemory( pMemStart, pMemStart + dwSize);
	}
	return bRet;
}

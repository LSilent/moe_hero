 
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "./base/Global.h"
 #include "./database/DBFile.h"
 
class DataBase
{
public:
	DataBase(X_INT nFileID);
	virtual ~DataBase();

public:
	
	const DBFile::FIELD*	GetFieldsByIndexKey(X_INT nKeyValue) const;
	const DBFile::FIELD*	GetFieldsByLineNum(X_INT nLineNum) const;
	const DBFile::FIELD*	GetFirstFieldsByColumn(X_INT nColumnNum, const DBFile::FIELD& value) const;
	const DBFile*	        GetDBCFile() const	{ return m_pFileDBC; }
 
	X_INT					  GetDBFileID( )const;
	X_UINT					GetFieldsNum( )const;
	X_UINT					GetRecordsNum( )const;
	X_BOOL					CreateDBFromFile(const X_CHAR* szFileName);
	X_BOOL					CreateDBFromMemory(const X_WCHAR* pMemStart, const X_ULLONG dwSize);
	X_BOOL					CreateDBFromMemory(const X_CHAR* pMemStart, const X_ULLONG dwSize);

public:
	DBFile*				m_pFileDBC;
};

#endif
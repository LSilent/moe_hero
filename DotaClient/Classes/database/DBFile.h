#ifndef __DBFILE_H__
#define __DBFILE_H__

#include "./base/Global.h"
#include <vector>
#include <map>
 
class DBFile
{
public:
	enum FIELD_TYPE
	{
		TEXT_INT		= 0,
		TEXT_FLOAT		= 1,
		TEXT_STRING		= 2,
		TEXT_ULONGLONG	= 3,
		TEXT_UINT		= 4,
	};
	
	union FIELD
	{
		X_FLOAT			fValue;
		X_INT			  iValue;
		X_UINT			uValue;
		const X_WCHAR *	pString;
		const X_CHAR *	pString1;
		
		FIELD(){};
		FIELD(X_FLOAT value)		 { fValue = value; }
		FIELD(X_INT value)		 { iValue = value; }
		FIELD(X_UINT value)		 { uValue = value; }
		FIELD(const X_WCHAR* value) { pString = value; }
		FIELD(const X_CHAR* value) { pString1 = value; }
	};
	
	typedef std::vector<FIELD_TYPE>	FIELDS_TYPE;
	typedef std::vector<FIELD>		DATA_BUFF;
	typedef std::map< X_INT, FIELD*>	FIELD_MAP;

public:
	DBFile(X_UINT nFileID);
	virtual ~DBFile();

public:

	X_VOID					Reset(X_UINT nFileID);
	X_BOOL					CreateDBFromFile(const X_CHAR* szFileName);

	X_BOOL					CreateDBFromMemory(const X_WCHAR* pMemStart, const X_WCHAR* pMemEnd);
	const FIELD*			GetFieldsByIndexKey(X_INT nKeyValue) const;
	const FIELD*			GetFieldsByPosistion(X_INT nRecordLine, X_INT nColumNum) const;
	const FIELD*			GetFirstFieldsByColumn(X_INT nColumnNum, const FIELD& value) const;

	
	X_UINT  GetDBFileID() const		{ return m_DBFileID; }
	X_INT	GetFieldsNum() const	    { return m_nFieldsNum; }
	X_INT   GetRecordsNum() const		{ return m_nRecordsNum; }
	X_BOOL  CreateDBFileIndex(X_INT nColum = 0);

public:
	
	static X_INT			ConvertStringToVector(const X_WCHAR* strSource, std::vector<wstring>& vRet, const X_WCHAR* szKey);
	static const X_WCHAR*	GetLineFromMemory(X_WCHAR* pStringBuf, X_INT nBufSize, const X_WCHAR* pMemStart, const X_WCHAR* pMemEnd);
	static X_BOOL			FieldEqu(FIELD_TYPE nFieldType, const FIELD& a, const FIELD& b);

	

private:
	X_UINT					m_DBFileID;
	FIELDS_TYPE			m_FieldsType;
	X_INT						m_nRecordsNum;
	X_INT						m_nFieldsNum;
	DATA_BUFF				m_vDataBuf;
	X_WCHAR*				m_pStringBuf;
	X_INT						m_nStringBufSize;
	FIELD_MAP				m_DBFileMap;
public:
	///---------------------------------------------------------
	X_CHAR*					m_pStringBuf1;
	X_INT					m_nStringBufSize1;
	static X_INT			ConvertStringToVector(const X_CHAR* strSource, std::vector<string>& vRet, const X_CHAR* szKey);
	static const X_CHAR*	GetLineFromMemory(X_CHAR* pStringBuf, X_INT nBufSize, const X_CHAR* pMemStart, const X_CHAR* pMemEnd);
	X_BOOL					CreateDBFromMemory(const X_CHAR* pMemStart, const X_CHAR* pMemEnd);
};

#endif


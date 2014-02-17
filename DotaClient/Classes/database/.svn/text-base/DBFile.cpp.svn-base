#include "./database/DBFile.h"
#include "./base/UtilTools.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
DBFile::DBFile(X_UINT nFileID)
{
	m_pStringBuf = X_NULL;
	Reset(nFileID);
}

DBFile::~DBFile()
{
	SAFE_DELETE_ARRAY(m_pStringBuf);
	m_FieldsType.clear();
	m_vDataBuf.clear();
	m_DBFileMap.clear();
}

X_VOID DBFile::Reset(X_UINT nFileID)
{
 
	SAFE_DELETE_ARRAY(m_pStringBuf);
	m_DBFileID			= nFileID;
	m_pStringBuf		= X_NULL;
	m_nRecordsNum		= 0;
	m_nFieldsNum		= 0;
	m_nStringBufSize	= 0;
	m_FieldsType.clear();
	m_vDataBuf.clear();
	m_DBFileMap.clear();
	//--------------------------
	m_pStringBuf1 = X_NULL;
	m_nStringBufSize1 = 0;
}

X_BOOL DBFile::CreateDBFromFile(const X_CHAR* szFileName)
{
 
	if( szFileName == X_NULL || strlen( szFileName ) == 0 ) //wcslen
		return XFALSE;
 
	
	FILE* fp = fopen(szFileName, "rb");
	if(X_NULL == fp) 
		return XFALSE;
 

	 
	/*X_CHAR *pName;
	UtilTools::WideChar2MultiByte(pName,szFileName);
	FILE* fp = fopen(pName, "rb");
	delete pName;
 
	if(X_NULL == fp) 
		return XFALSE;*/
 
	X_INT nFileSize = 0;
	fseek(fp, 0, SEEK_END);
	nFileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
 
	X_WCHAR* pMemory = new X_WCHAR[nFileSize+1];
	fread(pMemory, 1, nFileSize, fp);
	pMemory[nFileSize] = 0;
	X_BOOL bRet = CreateDBFromMemory(pMemory, pMemory+nFileSize+1);
	SAFE_DELETE_ARRAY(pMemory);
	return bRet;
}

X_BOOL DBFile::CreateDBFromMemory(const X_WCHAR* pMemStart, const X_WCHAR* pMemEnd)
{
	X_WCHAR szLine[1024*10] = {0};
	register const X_WCHAR* pMem = pMemStart;
	pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
	if(!pMem) 
		return XFALSE;
	pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
	if(!pMem) 
		return XFALSE;
 
	vector<wstring> vRet;
	ConvertStringToVector(szLine, vRet, L"\t");
	if(vRet.empty())
		return XFALSE;
 
	FIELDS_TYPE vFieldsType;
	vFieldsType.resize(vRet.size());
	for(X_INT i=0; i<(X_INT)vRet.size(); i++) 
	{
		if(vRet[i] == L"INT") 
			vFieldsType[i] = TEXT_INT;
		else if(vRet[i] == L"FLOAT") 
			vFieldsType[i] = TEXT_FLOAT;
		else if(vRet[i] == L"STRING") 
			vFieldsType[i] = TEXT_STRING;
		else if(vRet[i] == L"UINT64") 
			vFieldsType[i] = TEXT_ULONGLONG;
		else if(vRet[i] == L"UINT") 
		vFieldsType[i] = TEXT_UINT;
		else
			vFieldsType[i] = TEXT_STRING;
	}

	X_INT nFieldsNum = (X_INT)vFieldsType.size();
	X_INT nRecordsNum = 0;
	X_INT nStringBufSize = 0;
	vector<std::pair< wstring, X_INT> >	vStringBuf;		//ÁÙÊ±×Ö·û´®Çø
	std::map<wstring, X_INT>			mapStringBuf;	//¼ìË÷±í£¬±ÜÃâÖØ¸´×Ö·û´®
	do
	{
		pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
		if(!pMem) 
			break;
		if(szLine[0] == '#')
			continue;
		vRet.clear();
		ConvertStringToVector(szLine, vRet, L"\t");
		if(vRet.empty())
			continue;
		if(vRet.size() != nFieldsNum) 
		{
			continue;
		}
		if(vRet[0].empty())
			continue;

		for(X_INT i=0; i<nFieldsNum; i++)
		{
			FIELD newField;
			switch(vFieldsType[i])
			{
			case TEXT_INT:
				{
					newField.iValue = UtilTools::StringToInt(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;

			case TEXT_FLOAT:
				{
					newField.fValue = (X_FLOAT)UtilTools::StringToFloat(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;
			case TEXT_UINT:
				{
					newField.uValue = UtilTools::StringToUInt(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;
			case TEXT_STRING:
			case TEXT_ULONGLONG:
				{
					if(vRet[i].empty())
					{
						newField.iValue = 0;
					}
					else
					{
						const X_WCHAR * p = vRet[i].c_str();
						std::map<wstring, X_INT>::iterator it = mapStringBuf.find(vRet[i]);
						if(it == mapStringBuf.end())
						{
							vStringBuf.push_back(std::make_pair(vRet[i], nStringBufSize));
							mapStringBuf.insert(std::make_pair(vRet[i], (X_INT)vStringBuf.size()-1));
							newField.iValue = nStringBufSize + 1;
							nStringBufSize += (X_INT)wcslen(vRet[i].c_str()) + 1;
						}
						else
						{
							newField.iValue = vStringBuf[it->second].second + 1;
						}
					}
					m_vDataBuf.push_back(newField);
				}
				break;
			}
		}
		nRecordsNum++;
	}while(XTRUE);

	m_nRecordsNum = nRecordsNum;
	m_nFieldsNum  = nFieldsNum;
	m_nStringBufSize = nStringBufSize+1;
	m_FieldsType = vFieldsType;

	m_pStringBuf = new X_WCHAR[m_nStringBufSize];
	if(!m_pStringBuf) 
		return XFALSE;

	memset(m_pStringBuf, 0, m_nStringBufSize*sizeof(X_WCHAR));
	X_WCHAR* p = m_pStringBuf + 1;
	for(X_INT i=0; i<(X_INT)vStringBuf.size(); i++)
	{
		memcpy(p, vStringBuf[i].first.c_str(), vStringBuf[i].first.size()*sizeof(X_WCHAR));	
		p += vStringBuf[i].first.size();
		*(p++) = L'\0';
	}
	for(X_INT i=0; i<m_nFieldsNum; i++)
	{
		if(vFieldsType[i] != TEXT_STRING && vFieldsType[i] != TEXT_ULONGLONG)
			continue;

		for(X_INT j=0; j<m_nRecordsNum; j++)
		{
			FIELD& tmpField = m_vDataBuf[j*m_nFieldsNum+i];
			tmpField.pString = m_pStringBuf + tmpField.iValue;
		}
	}
	return CreateDBFileIndex(0);
}

const DBFile::FIELD* DBFile::GetFieldsByIndexKey(X_INT nKeyValue) const
{

	FIELD_MAP::const_iterator itFind = m_DBFileMap.find(nKeyValue);
	if(itFind == m_DBFileMap.end()) 
		return X_NULL;
	return itFind->second;
}

const DBFile::FIELD* DBFile::GetFieldsByPosistion(X_INT nRecordLine, X_INT nColumNum) const
{
	X_INT nPosition = nRecordLine * GetFieldsNum() + nColumNum;
	if(nPosition<0 || nPosition >=(X_INT)m_vDataBuf.size()) 
		return X_NULL;
	return &(m_vDataBuf[nPosition]);
}

const DBFile::FIELD* DBFile::GetFirstFieldsByColumn(X_INT nColumnNum, const FIELD& value) const
{
	
	if(nColumnNum < 0 || nColumnNum >= m_nFieldsNum) 
		return X_NULL;
	FIELD_TYPE type = m_FieldsType[nColumnNum];

	for(X_INT i=0; i<m_nRecordsNum; i++)
	{
		const FIELD& tmpField = m_vDataBuf[m_nFieldsNum*i + nColumnNum];
		X_BOOL bRet;
		if(TEXT_INT==type) 
			bRet = FieldEqu(TEXT_INT, tmpField, value);
		else if(TEXT_FLOAT==type)
			bRet = FieldEqu(TEXT_FLOAT, tmpField, value);
		else
			bRet = FieldEqu(TEXT_STRING, tmpField, value);
		if(bRet) 
			return &(m_vDataBuf[m_nFieldsNum*i]);
	}
	return X_NULL;
}
X_BOOL DBFile::CreateDBFileIndex(X_INT nColum)
{
	if(nColum<0 || nColum>=m_nFieldsNum) 
		return XFALSE;

	m_DBFileMap.clear();

	for(X_INT i=0; i<(X_INT)m_nRecordsNum; i++)
	{
		FIELD* p = &(m_vDataBuf[i*m_nFieldsNum]);
		FIELD_MAP::iterator itFind = m_DBFileMap.find(p->iValue);
		if(itFind != m_DBFileMap.end())
			return XFALSE;;
		m_DBFileMap.insert(std::make_pair(p->iValue, p));
	}
	return XTRUE;
 
}

X_INT	DBFile::ConvertStringToVector(const X_WCHAR* strSource, vector<wstring>& vRet, const X_WCHAR* szKey)
{
	vRet.clear();
	if(!strSource || !szKey)
		return 0;
	wstring strSrc = strSource;
	if(strSrc.empty())
		return 0;

	wstring::size_type nLeft = 0;
	wstring::size_type nRight = 0;
	
	nRight = strSrc.find(szKey);
	if(nRight == wstring::npos)
		nRight = strSrc.length();
	
	while(XTRUE)
	{
		wstring strItem = strSrc.substr(nLeft, nRight-nLeft);
		if(strItem.length() > 0)
			vRet.push_back(strItem);
		else						
			vRet.push_back(L"");
		if(nRight == strSrc.length())
			break;
		nLeft = nRight + wcslen(szKey);
		nRight = strSrc.find(szKey, nLeft);
		
		if(nRight == wstring::npos)
			nRight = strSrc.length();
	}

	return (X_INT)vRet.size();
}

const X_WCHAR*	DBFile::GetLineFromMemory(X_WCHAR* pStringBuf, X_INT nBufSize, const X_WCHAR* pMemStart, const X_WCHAR* pMemEnd)
{
	const X_WCHAR* pMem = pMemStart;
	if(pMem>=pMemEnd || *pMem==X_NULL)
		return X_NULL;

	while(pMem<pMemEnd && pMem-pMemStart+1<nBufSize && *pMem != 0 && *pMem != '\r' && *pMem != '\n') 
		*(pStringBuf++) = *(pMem++);
	*pStringBuf = 0;
	while(pMem<pMemEnd && *pMem != 0 && (*pMem=='\r' || *pMem=='\n')) 
		pMem++;
	return pMem;
}

X_BOOL DBFile::FieldEqu(FIELD_TYPE nFieldType, const FIELD& a, const FIELD& b)
{
	if(nFieldType == TEXT_INT)
	{
		return a.iValue==b.iValue;
	}
	else if(nFieldType == TEXT_FLOAT)
	{
		return a.fValue==b.fValue;
	}
	else if(nFieldType == TEXT_UINT)
	{
		return a.uValue==b.uValue;
	}
	else
	{
		 
			return (wcscmp(a.pString, b.pString)==0);
	 
	}

	

		return XFALSE;
}

X_BOOL DBFile::CreateDBFromMemory(const X_CHAR* pMemStart, const X_CHAR* pMemEnd)
{
	X_CHAR szLine[1024*10] = {0};
	register const X_CHAR* pMem = pMemStart;
	pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
	if(!pMem) 
		return XFALSE;
	pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
	if(!pMem) 
		return XFALSE;

	vector<string> vRet;
	ConvertStringToVector(szLine, vRet, "\t");
	if(vRet.empty())
		return XFALSE;

	FIELDS_TYPE vFieldsType;
	vFieldsType.resize(vRet.size());
	for(X_INT i=0; i<(X_INT)vRet.size(); i++) 
	{
		if(vRet[i] == "INT") 
			vFieldsType[i] = TEXT_INT;
		else if(vRet[i] == "FLOAT") 
			vFieldsType[i] = TEXT_FLOAT;
		else if(vRet[i] == "STRING") 
			vFieldsType[i] = TEXT_STRING;
		else if(vRet[i] == "UINT64") 
			vFieldsType[i] = TEXT_ULONGLONG;
		else if(vRet[i] == "UINT") 
			vFieldsType[i] = TEXT_UINT;
		else
			vFieldsType[i] = TEXT_STRING;
	}

	X_INT nFieldsNum = (X_INT)vFieldsType.size();
	X_INT nRecordsNum = 0;
	X_INT nStringBufSize = 0;
	vector<std::pair< string, X_INT> >	vStringBuf;		//ÁÙÊ±×Ö·û´®Çø
	std::map<string, X_INT>			mapStringBuf;	//¼ìË÷±í£¬±ÜÃâÖØ¸´×Ö·û´®
	do
	{
		pMem = GetLineFromMemory(szLine, 1024*10, pMem, pMemEnd);
		if(!pMem) 
			break;
		if(szLine[0] == '#')
			continue;
		vRet.clear();
		ConvertStringToVector(szLine, vRet, "\t");
		if(vRet.empty())
			continue;
		if(vRet.size() != nFieldsNum) 
		{
			continue;
		}
		if(vRet[0].empty())
			continue;

		for(X_INT i=0; i<nFieldsNum; i++)
		{
			FIELD newField;
			switch(vFieldsType[i])
			{
			case TEXT_INT:
				{
					newField.iValue = UtilTools::StringToInt(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;

			case TEXT_FLOAT:
				{
					newField.fValue = (X_FLOAT)UtilTools::StringToFloat(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;
			case TEXT_UINT:
				{
					newField.uValue = UtilTools::StringToUInt(vRet[i].c_str());
					m_vDataBuf.push_back(newField);
				}
				break;
			case TEXT_STRING:
			case TEXT_ULONGLONG:
				{
					if(vRet[i].empty())
					{
						newField.iValue = 0;
					}
					else
					{
						const X_CHAR * p = vRet[i].c_str();
						std::map<string, X_INT>::iterator it = mapStringBuf.find(vRet[i]);
						if(it == mapStringBuf.end())
						{
							vStringBuf.push_back(std::make_pair(vRet[i], nStringBufSize));
							mapStringBuf.insert(std::make_pair(vRet[i], (X_INT)vStringBuf.size()-1));
							newField.iValue = nStringBufSize + 1;
							nStringBufSize += (X_INT)strlen(vRet[i].c_str()) + 1;
						}
						else
						{
							newField.iValue = vStringBuf[it->second].second + 1;
						}
					}
					m_vDataBuf.push_back(newField);
				}
				break;
			}
		}
		nRecordsNum++;
	}while(XTRUE);

	m_nRecordsNum = nRecordsNum;
	m_nFieldsNum  = nFieldsNum;
	m_nStringBufSize = nStringBufSize+1;
	m_FieldsType = vFieldsType;

	m_pStringBuf1 = new X_CHAR[m_nStringBufSize];
	if(!m_pStringBuf1) 
		return XFALSE;

	memset(m_pStringBuf1, 0, m_nStringBufSize1*sizeof(X_CHAR));
	X_CHAR* p = m_pStringBuf1 + 1;
	for(X_INT i=0; i<(X_INT)vStringBuf.size(); i++)
	{
		memcpy(p, vStringBuf[i].first.c_str(), vStringBuf[i].first.size()*sizeof(X_CHAR));	
		p += vStringBuf[i].first.size();
		*(p++) =  '\0';
	}
	for(X_INT i=0; i<m_nFieldsNum; i++)
	{
		if(vFieldsType[i] != TEXT_STRING && vFieldsType[i] != TEXT_ULONGLONG)
			continue;

		for(X_INT j=0; j<m_nRecordsNum; j++)
		{
			FIELD& tmpField = m_vDataBuf[j*m_nFieldsNum+i];
			tmpField.pString1 = m_pStringBuf1 + tmpField.iValue;
		}
	}
	return CreateDBFileIndex(0);
}
const X_CHAR*	DBFile::GetLineFromMemory(X_CHAR* pStringBuf, X_INT nBufSize, const X_CHAR* pMemStart, const X_CHAR* pMemEnd)
{
	const X_CHAR* pMem = pMemStart;
	if(pMem>=pMemEnd || *pMem==X_NULL)
		return X_NULL;

	while(pMem<pMemEnd && pMem-pMemStart+1<nBufSize && *pMem != 0 && *pMem != '\r' && *pMem != '\n') 
		*(pStringBuf++) = *(pMem++);
	*pStringBuf = 0;
	while(pMem<pMemEnd && *pMem != 0 && (*pMem=='\r' || *pMem=='\n')) 
		pMem++;
	return pMem;
}
 
	X_INT	DBFile::ConvertStringToVector(const X_CHAR* strSource, std::vector<string>& vRet, const X_CHAR* szKey)
	{
		vRet.clear();
		if(!strSource || !szKey)
			return 0;
		string strSrc = strSource;
		if(strSrc.empty())
			return 0;

		string::size_type nLeft = 0;
		string::size_type nRight = 0;

		nRight = strSrc.find(szKey);
		if(nRight == wstring::npos)
			nRight = strSrc.length();

		while(XTRUE)
		{
			string strItem = strSrc.substr(nLeft, nRight-nLeft);
			if(strItem.length() > 0)
				vRet.push_back(strItem);
			else						
				vRet.push_back("");
			if(nRight == strSrc.length())
				break;
			nLeft = nRight + strlen(szKey);
			nRight = strSrc.find(szKey, nLeft);

			if(nRight == string::npos)
				nRight = strSrc.length();
		}

		return (X_INT)vRet.size();
	}
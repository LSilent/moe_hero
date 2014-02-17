 
 
#include "./base/UtilTools.h"
#include <assert.h>
#include <wchar.h> 
#include "./database/DataBaseSystem.h"
#include <string.h>
#include <cctype>
using std::ostringstream;


int UtilTools::ConvertStringToVector(const wchar_t* strSource, vector<wstring>& vRet, const wchar_t* szKey)
{
	vRet.clear();
	if(!strSource || !szKey|| strSource == L"" || szKey == L"")
		return 0;

	wstring strSrc = strSource;
	if(strSrc.empty())return 0;

	wstring::size_type nLeft = 0;
	wstring::size_type nRight = 0;

	nRight = strSrc.find(szKey);
	if(nRight == wstring::npos)
		nRight = strSrc.length();

	while(true)
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

	return (int)vRet.size();
  
}
int UtilTools::ConvertStringToVector(const char* strSource, vector<string>& vRet, const char* szKey)
{
	vRet.clear();
	if(!strSource || !szKey|| strSource ==  "" || szKey ==  "")
		return 0;

	string strSrc = strSource;
	if(strSrc.empty())return 0;

	string::size_type nLeft = 0;
	string::size_type nRight = 0;

	nRight = strSrc.find(szKey);
	if(nRight == string::npos)
		nRight = strSrc.length();

	while(true)
	{
		string strItem = strSrc.substr(nLeft, nRight-nLeft);
		if(strItem.length() > 0)	
			vRet.push_back(strItem);
		if(nRight == strSrc.length())
			break;
		nLeft = nRight + strlen(szKey);
		nRight = strSrc.find(szKey, nLeft);

		if(nRight == string::npos)
			nRight = strSrc.length();
	}
	return (int)vRet.size();
}
int UtilTools::ConvertStringToIntVector(const char* strSource, vector<int>& vRet, const char* szKey)
{
	vRet.clear();
	if(!strSource || !szKey|| strSource == "" || szKey == "")
	{
		return 0;
	}
	vector<string> vecResult;
	ConvertStringToVector(strSource,vecResult,szKey);
	int size = static_cast<int>(vecResult.size());
	for(int i = 0; i < size; ++i)
	{
		 vRet.push_back(StringToInt(vecResult[i].c_str()));
	}
	return static_cast<int>(vRet.size());
}
 
//×Ö·û´®×ªFLOAT
float	UtilTools::StringToFloat(const wchar_t* str)
{
	if(str == 0) return 0.f;
	char *p = 0;
	WideChar2MultiByte(p,str);
	float result = (float)atoi(p);
	delete p;
	return  result;
}
 
string	UtilTools::FloatToString(float f)
{
	static char temp[64];
	sprintf(temp, "%f", f);
	return temp;
 
}
string	UtilTools::UIntToString(unsigned int value)
{
	static char temp[64];
	sprintf(temp, "%d", value);
	return temp;
}
string	UtilTools::IntToString(int value)
{
	static char temp[64];
	sprintf(temp, "%d", value);
	return temp;
}
 
//×Ö·û´®×ªINT
int	UtilTools::StringToInt(const wchar_t* str)
{
	if(str == 0) return 0;
	char *p = 0;
	WideChar2MultiByte(p,str);
	int result =atoi(p);
	delete p;
	return  result;
}
unsigned int UtilTools::StringToUInt(const wchar_t* str)
{
	if(str == 0) return 0;
	wchar_t* end = (wchar_t*)(str + wcslen(str));
	return wcstoul(str, &end, 10);
}
 
int			UtilTools::StringToInt(const char* str)
{
	if(str == 0) return 0;
	return atoi(str);
}
unsigned int	UtilTools::StringToUInt(const char* str)
{
	if(str == 0) return 0;
	return atoi(str);
}
float		UtilTools::StringToFloat(const char* str)
{
	if(str == 0) return 0;
	return atof(str);
}
int	UtilTools::WideChar2MultiByte(char* &pDestString,const wchar_t* orig)
{

/*#ifdef __WINDOWS__

	int textlen = WideCharToMultiByte( CP_ACP, 
		0,          
		orig,     
		-1,   
		NULL,       
		0,
		NULL,       
		NULL );    

	pDestString = new char[(textlen+1)*sizeof(char)];  
	memset(pDestString,0,(textlen+1)*sizeof(char));  


	textlen = WideCharToMultiByte( CP_ACP,  
		0,          
		orig,    
		-1,    
		pDestString,  
		textlen,                           
		NULL,       
		NULL );
	return textlen ;


#else*/
	setlocale(LC_ALL, "");
	int iTextLen = wcstombs(0,orig,0);
	pDestString = new char[(iTextLen+1)*sizeof(char)];  
	memset(pDestString,0,(iTextLen+1)*sizeof(char));  

	iTextLen = wcstombs(pDestString, orig, iTextLen);
	return iTextLen;


//#endif

}
 
int	 UtilTools::MultiByte2WideChar(wchar_t* &pWideString, const char* orig)
{

/*#ifdef __WINDOWS__

	int    textlen ;
	textlen = MultiByteToWideChar( CP_ACP, 0, orig,-1, NULL,0 );
	pWideString = new wchar_t[(textlen+1)*sizeof(wchar_t)];  
	memset(pWideString,0,(textlen+1)*sizeof(wchar_t));  

	textlen = MultiByteToWideChar(CP_ACP, 0,orig,-1,(LPWSTR)pWideString,textlen );  
	return    textlen;  		 
#else*/
	setlocale(LC_ALL, "");
	int iTextLen = mbstowcs(0, orig, 0);

	pWideString = new wchar_t[(iTextLen+1)*sizeof(wchar_t)];  
	memset(pWideString,0,(iTextLen+1)*sizeof(wchar_t));  

	int nLength = mbstowcs(pWideString, orig, iTextLen);
	return nLength;

//#endif
}
/*int UtilTools::UTF8toToUnicode(wchar_t* &pWideString,const char *orig)    
{    

	#ifdef __WINDOWS__
 
	int textlen=MultiByteToWideChar(CP_UTF8,0, orig, -1, 0,0);   
	pWideString = new wchar_t[(textlen+1)*sizeof(wchar_t)];  
	memset(pWideString,0,(textlen+1)*sizeof(wchar_t));  
	textlen = MultiByteToWideChar(CP_UTF8, 0,orig,-1,(LPWSTR)pWideString,textlen );
	return  textlen;  

	#else 


	#endif

}*/
/*int UtilTools::UnicodeToUTF8( char * &pDestString,const wchar_t *orig  )
{
	#ifdef __WINDOWS__

	int textlen = WideCharToMultiByte( CP_UTF8,    0,    orig,    -1,    NULL, 0, NULL, NULL );
	pDestString =  new char[(textlen+1)*sizeof(char)];
	memset(pDestString, 0, sizeof(char) * ( textlen + 1 ) );
	textlen = WideCharToMultiByte( CP_UTF8, 0, orig, -1, pDestString, textlen, NULL, NULL );
	return textlen;
	#else 
 
	#endif
}*/
 
 const X_CHAR* UtilTools::GET_TEXT_FROM_LANG(X_INT id)
 {
	const DataBase* pTableFie =  DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_LANG);
	
	const  stDBC_FILE_LANG * pData = (const  stDBC_FILE_LANG * )pTableFie->GetFieldsByIndexKey(id);
	if (pData && pData->show)
	{
		return pData->world;
	}
	return "";
 }
bool  UtilTools::Fiter( const char *str)
 {
	 
	 if (str == NULL || strlen(str) == 0 )
	 {
		 return false;
	 }
	/* const DataBase* pTableFie =  DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_FILTER);

	 const  stDBC_FILE_FILTER * pData =  NULL;
	 string  _str = str;
	 
	 pData = (const stDBC_FILE_FILTER*)pTableFie->GetFieldsByIndexKey(0);

	 if (_str.find(pData->text) != _str.npos)
	 {
		 return false;
	 }

	 for (X_UINT i = 0;i< pTableFie->GetRecordsNum();i++)
	 {
		 pData = (const stDBC_FILE_FILTER*)pTableFie->GetFieldsByLineNum(i);
		 if (pData == X_NULL) continue;
		 if (_str == pData->text  )
		 {
			 return false;
		 }
	 }*/
	 const DataBase* pTableFie =  DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_FILTER);

	 const  stDBC_FILE_FILTER * pData =  NULL;

 
	 X_UINT record = pTableFie->GetRecordsNum();
	 for (X_UINT i = 0;i< record;i++)
	 {
		 pData = (const stDBC_FILE_FILTER*)pTableFie->GetFieldsByLineNum(i);
		 if (pData == X_NULL) continue;
		 if (strstr(str,pData->text) != NULL) return false;
	 }

	 return true;
 }

void  UtilTools::FilterText(  char *str)
 {
	 if (str == NULL)return;
	 const DataBase* pTableFie =  DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_FILTER);

	 const  stDBC_FILE_FILTER * pData =  NULL;
	 
	 X_CHAR key = L'*';
	 int record = pTableFie->GetRecordsNum();
	 for (X_UINT i = 0;i< record;i++)
	 {
		 pData = (const stDBC_FILE_FILTER*)pTableFie->GetFieldsByLineNum(i);
		 if (pData == X_NULL) continue;
		 char* pResult = strstr(str,pData->text);
        int size  = strlen(pData->text);
		 while (pResult != NULL)
		 {
			
			 for (int i= 0; i < size; i++)
			 {
				 *(pResult+i) = key; 
			 }
			 pResult = strstr(pResult,pData->text);
		 }
	 }
 }
int UtilTools::isEmail(const char *email){
    const char *p;
    p=strstr(email,"@");
    if(!p)return 0;
    if (!(p-email))return 0;
    if(!(strstr(p,".")-p))return 0;
    p=strstr(p,".");
    if(*(p+1)=='\0')return 0;
    return 1;
}
bool UtilTools::isvalidAccount(const char *account)
{
    string str = account;
    X_UINT size = str.size();
    if (size==0) {
        return false;
    }
    
    for (X_UINT i = 0; i<size;i++)
    {
        char c = str[i];
        if(isalpha(c))
            continue;
        if(isdigit(c))
            continue;
        return false;
    }
    return true;
}
 bool UtilTools::isvalidNumAccount(const string &account)
 {

	 string str = account;
	 X_UINT size = str.size();
	 if (size==0) {
		 return false;
	 }

	 for (X_UINT i = 0; i<size;i++)
	 {
		 char c = str[i];
		 if(isdigit(c))
			 continue;
		 return false;
	 }
	 return true;
 }

X_INT UtilTools::findInVector(X_INT data,const vector<X_INT> &vec)
 {
	 X_UINT size = vec.size();
	 for (X_UINT i =0;i<size;i++)
	 {
		if(vec[i] ==data) 
			return i;
	 }
	 return -1;
 }
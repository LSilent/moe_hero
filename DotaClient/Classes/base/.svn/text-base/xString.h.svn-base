 
#ifndef  __XSTRING_H__
#define  __XSTRING_H__
 
#include <string>
#include "./base/Global.h"
using namespace std;
class  xString
{
public:
	//重定义size_type
	typedef std::wstring::size_type size_type;	

	//定义字符串结尾标识
	static std::wstring::size_type npos;			

public:
 
	xString();
	xString(const xString& szString);
	xString(const X_CHAR* szString);
	xString(const X_WCHAR* szString);
	xString(const X_UINT* szString);

	~xString();

public:
	//重载'='赋值操作符 
	xString& operator=(const xString& szString);
	xString& operator=(const X_CHAR* szString);
	xString& operator=(const X_WCHAR* szString);
	xString& operator=(const X_UINT* szString);

	//重载'+='赋值操作
	xString& operator+=(xString& szString);
	xString& operator+=(const X_CHAR* szString);
	xString& operator+=(const X_WCHAR* szString);
	xString& operator+=(const X_UINT* szString);

public:
	//得到Unicode字符串
	const X_WCHAR* c_str() const;

	//得到UTF32字符串
	const X_UINT* toUTF32() const;

	//得到单字节字符串
	const X_CHAR* toMultiByte() const;

	//得到Unicode字符串的大小
	const size_t size() const;

	//判断字符串是否为空
	const bool empty() const;

	//得到Unicode字符串的长度
	const size_t length() const;

	//截取字符串
	const xString substr(size_type _Off, size_type _Count = npos) const;

	//查找字符串
	const std::wstring::size_type find(const X_WCHAR* ptr, size_type _Off = 0) const;

private:
	//多字节转换宽字节
	void ConvertMultiByteToWideChar(const X_CHAR* szString, std::wstring& wcOutString);

	//宽字节转换多字节
	void ConvertWideCharToMultiByte(const X_WCHAR* wcString, X_CHAR** szOutString) const;

	//UTF16转换UTF32
	void ConvertUTF16toUTF32(const X_USHORT** sourceStart, const X_USHORT* sourceEnd, X_UINT** targetStart, X_UINT* targetEnd) const;

	//UTF32转换UTF16
	void ConvertUTF32toUTF16(const X_UINT** sourceStart, const X_UINT* sourceEnd,X_USHORT** targetStart, X_USHORT* targetEnd);

public:
	//Unicode字符串存储
	std::wstring	m_wcString;		

	//UTF32字符串存储
	mutable X_UINT*	m_utf32String;	

	//多字节字符串存储
	mutable X_CHAR*	m_X_CHARString;		
	const X_WCHAR*	m_watchString;
};

//////////////////////////////////////////////////////////////////////////
// 重载符实现
//重载比较操作
 bool operator<(const xString& szString1, const xString& szString2);
 bool operator>(const xString& szString1, const xString& szString2);
 bool operator<=(const xString& szString1, const xString& szString2);
 bool operator>=(const xString& szString1, const xString& szString2);

//重载'+'操作
 xString operator+(const xString& szString1, const xString& szString2);
 xString operator+(const xString& szString1, const X_CHAR* szString2);
 xString operator+(const xString& szString1, const X_WCHAR* szString2);
 xString operator+(const xString& szString1, const X_UINT* szString2);

//重载'=='操作
 bool operator==(const xString& szString1, const xString& szString2);
 bool operator==(const xString& szString1, const X_CHAR* szString2);
 bool operator==(const xString& szString1, const X_WCHAR* szString2);
 bool operator==(const xString& szString1, const X_UINT* szString2);

//重载'!='操作
 bool operator!=(const xString& szString1, const xString& szString2);
 bool operator!=(const xString& szString1, const X_CHAR* szString2);
 bool operator!=(const xString& szString1, const X_WCHAR* szString2);
 bool operator!=(const xString& szString1, const X_UINT* szString2);

 #endif 
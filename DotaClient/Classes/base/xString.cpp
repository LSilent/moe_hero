 
#include "xString.h"
#include "./base/UtilTools.h"

//////////////////////////////////////////////////////////////////////////
// 定义常量
static const int halfShift  = 10; /* used for shifting by 10 bits */

static const X_UINT halfBase = 0x0010000UL;
static const X_UINT halfMask = 0x3FFUL;

#define UNI_SUR_HIGH_START  (X_UINT)0xD800
#define UNI_SUR_HIGH_END    (X_UINT)0xDBFF
#define UNI_SUR_LOW_START   (X_UINT)0xDC00
#define UNI_SUR_LOW_END     (X_UINT)0xDFFF

#define  UNI_REPLACEMENT_CHAR   (X_UINT)0x0000FFFD 
#define  UNI_MAX_BMP			(X_UINT)0x0000FFFF 
#define  UNI_MAX_UTF16			(X_UINT)0x0010FFFF 
#define  UNI_MAX_UTF32			(X_UINT)0x7FFFFFFF 
#define  UNI_MAX_LEGAL_UTF32	(X_UINT)0x0010FFFF 

std::wstring::size_type xString::npos =  std::wstring::npos;

 
// xString
 
xString::xString()
{
	m_utf32String = NULL;
	m_X_CHARString = NULL;

	m_wcString = L"";
	m_watchString = m_wcString.c_str();
}

//---------------------------------------------------------------------
xString::xString(const xString& szString)
{
	m_utf32String = 0;
	m_X_CHARString = 0;

	m_wcString = szString.m_wcString;
	m_watchString = m_wcString.c_str();
}

xString::xString(const X_CHAR* szString)
{
	m_utf32String = 0;
	m_X_CHARString = 0;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
		return;
	}

	ConvertMultiByteToWideChar(szString, m_wcString);
	m_watchString = m_wcString.c_str();
}

//---------------------------------------------------------------------
xString::xString(const X_WCHAR* szString)
{
	m_utf32String = NULL;
	m_X_CHARString = NULL;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
		return;
	}

	m_wcString = szString;
	m_watchString = m_wcString.c_str();
}

//---------------------------------------------------------------------
xString::xString(const X_UINT* szString)
{
	m_utf32String = 0;
	m_X_CHARString = 0;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
		return;
	}

	if(szString[0] == 0)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
		return;
	}

	int utf32Length = 0;
	while(szString[utf32Length] != 0)
	{
		++utf32Length;
	}
	++utf32Length;
	m_utf32String = new X_UINT[utf32Length];
	memset(m_utf32String, 0, sizeof(X_UINT)*utf32Length);
	memcpy(m_utf32String, szString, sizeof(X_UINT)*utf32Length);

	X_WCHAR* tmpwcString = new X_WCHAR[utf32Length];
	ConvertUTF32toUTF16((const X_UINT**)&m_utf32String, m_utf32String+utf32Length, (X_USHORT**)&tmpwcString, (X_USHORT*)(tmpwcString+utf32Length));
	m_wcString = tmpwcString;
	m_watchString = m_wcString.c_str();
	delete[] tmpwcString;
}

//---------------------------------------------------------------------
xString::~xString()
{
	if(m_utf32String != 0)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString != 0)
		delete[] m_X_CHARString;
	m_X_CHARString = NULL;
}

//---------------------------------------------------------------------
xString& xString::operator=(const xString& szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = NULL;

	m_wcString = szString.m_wcString;
	m_watchString = m_wcString.c_str();
	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator=(const X_CHAR* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = 0;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
	}
	else
	{
		ConvertMultiByteToWideChar(szString, m_wcString);
	}

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator=(const X_WCHAR* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = 0;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
	}
	else
	{
		m_wcString = szString;
		m_watchString = m_wcString.c_str();
	}

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator=(const X_UINT* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = NULL;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = NULL;

	if(NULL == szString)
	{
		m_wcString = L"";
		m_watchString = m_wcString.c_str();
	}
	else
	{
		if(szString[0] == 0)
		{
			m_wcString = L"";
			m_watchString = m_wcString.c_str();
		}
		else
		{
			int utf32Length = 0;
			while(szString[utf32Length] != 0)
			{
				++utf32Length;
			}
			++utf32Length;
			m_utf32String = new X_UINT[utf32Length];
			memset(m_utf32String, 0, sizeof(X_UINT)*utf32Length);
			memcpy(m_utf32String, szString, sizeof(X_UINT)*utf32Length);

			X_WCHAR* tmpwcString = new X_WCHAR[utf32Length];
			ConvertUTF32toUTF16((const X_UINT**)&m_utf32String, m_utf32String+utf32Length, (X_USHORT**)&tmpwcString, (X_USHORT*)(tmpwcString+utf32Length));
			m_wcString = tmpwcString;
			m_watchString = m_wcString.c_str();
			delete[] tmpwcString;
		}
	}

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator+=(xString& szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = NULL;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = NULL;

	m_wcString += szString.m_wcString;
	m_watchString = m_wcString.c_str();

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator+=(const X_CHAR* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = 0;

	xString tmpString;
	if(NULL != szString)
	{
		ConvertMultiByteToWideChar(szString, tmpString.m_wcString);
		m_wcString += tmpString.m_wcString;
		m_watchString = m_wcString.c_str();
	}

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator+=(const X_WCHAR* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = 0;

	if(NULL != szString)
	{
		m_wcString += szString;
		m_watchString = m_wcString.c_str();
	}

	return *this;
}

//---------------------------------------------------------------------
xString& xString::operator+=(const X_UINT* szString)
{
	if(m_utf32String)
		delete[] m_utf32String;
	m_utf32String = 0;

	if(m_X_CHARString)
		delete[] m_X_CHARString;
	m_X_CHARString = 0;

	if(NULL != szString)
	{
		if(szString[0] != 0)
		{
			int utf32Length = 0;
			while(szString[utf32Length] != 0)
			{
				++utf32Length;
			}
			++utf32Length;

			X_WCHAR* tmpwcString = new X_WCHAR[utf32Length];
			ConvertUTF32toUTF16((const X_UINT**)&m_utf32String, m_utf32String+utf32Length, (X_USHORT**)&tmpwcString, (X_USHORT*)(tmpwcString+utf32Length));
			m_wcString += tmpwcString;
			m_watchString = m_wcString.c_str();
			delete[] tmpwcString;
		}
	}

	return *this;
}

//---------------------------------------------------------------------
const X_WCHAR* xString::c_str() const
{
	return m_wcString.c_str();
}

//---------------------------------------------------------------------
const X_UINT* xString::toUTF32() const
{
	if(m_utf32String)
		return m_utf32String;

	const X_WCHAR* utf16String = m_wcString.c_str();
	int utf16Length = (int)m_wcString.size();

	m_utf32String = new X_UINT[utf16Length+1];
	ConvertUTF16toUTF32((const X_USHORT**)(&utf16String), (const X_USHORT*)(utf16String+utf16Length), &(m_utf32String), m_utf32String+utf16Length);
	m_utf32String[utf16Length] = 0;

	return m_utf32String;
}

//---------------------------------------------------------------------
const X_CHAR* xString::toMultiByte() const
{
	if(m_X_CHARString)
		return m_X_CHARString;
	ConvertWideCharToMultiByte(m_wcString.c_str(), &m_X_CHARString);

	return m_X_CHARString;
}

//---------------------------------------------------------------------
const size_t xString::size() const
{
	return m_wcString.size();
}

//---------------------------------------------------------------------
const bool xString::empty() const
{
	return m_wcString.empty();
}

//---------------------------------------------------------------------
const size_t xString::length() const
{
	return m_wcString.length();
}

//---------------------------------------------------------------------
const xString xString::substr(size_type _Off, size_type _Count) const
{
	xString newString;
	newString.m_wcString = m_wcString.substr(_Off, _Count);
	return newString;
}

//---------------------------------------------------------------------
const std::wstring::size_type xString::find(const X_WCHAR* ptr, size_type _Off) const
{
	return m_wcString.find(ptr, _Off);
}

//---------------------------------------------------------------------
void xString::ConvertMultiByteToWideChar(const X_CHAR* szString, std::wstring& wcOutString)
{
	 
	X_WCHAR *wcString =  0;
	int textlen = UtilTools::MultiByte2WideChar(wcString , szString );
	if(0 == wcString)
	{
		return;
	}
	wcString[textlen] = '\0';
	wcOutString = wcString; 
	delete[] wcString;

}

//---------------------------------------------------------------------
void xString::ConvertWideCharToMultiByte(const X_WCHAR* wcString, X_CHAR** szOutString) const
{

	X_CHAR *szString = 0;
	int textlen = UtilTools::WideChar2MultiByte(szString ,wcString);
	if(0 == szString)
	{
		return;
	}
	szString[textlen] = '\0';
	*szOutString = szString;
}

//---------------------------------------------------------------------
void xString::ConvertUTF16toUTF32(const X_USHORT** sourceStart, const X_USHORT* sourceEnd, X_UINT** targetStart, X_UINT* targetEnd) const
{
	const X_USHORT* source = *sourceStart;
	X_UINT* target = *targetStart;
	X_UINT ch, ch2;
	while (source < sourceEnd)
	{
		const X_USHORT* oldSource = source; /*  In case we have to back up because of target overflow. */
		ch = *source++;
		/* If we have a surrogate pair, convert to UINT first. */
		if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_HIGH_END)
		{
			/* If the 16 bits following the high surrogate are in the source buffer... */
			if (source < sourceEnd)
			{
				ch2 = *source;
				/* If it's a low surrogate, convert to UINT. */
				if (ch2 >= UNI_SUR_LOW_START && ch2 <= UNI_SUR_LOW_END)
		  {
			  ch = ((ch - UNI_SUR_HIGH_START) << halfShift)
				  + (ch2 - UNI_SUR_LOW_START) + halfBase;
			  ++source;
				} 
				else /*if (flags == strictConversion) */
				{ /* it's an unpaired high surrogate */
					--source; /* return to the illegal value itself */
					break;
		  }
			} else 
			{ /* We don't have the 16 bits following the high surrogate. */
				--source; /* return to the high surrogate */
				break;
			}
		} 
		else /*if (flags == strictConversion)*/
		{
			/* UTF-16 surrogate values are illegal in UTF-32 */
			if (ch >= UNI_SUR_LOW_START && ch <= UNI_SUR_LOW_END)
			{
				--source; /* return to the illegal value itself */
				break;
			}
		}
		if (target >= targetEnd)
		{
			source = oldSource; /* Back up source pointer! */
			break;
		}
		*target++ = ch;
	}
	*sourceStart = source;
	*targetStart = target;
}

//---------------------------------------------------------------------
void xString::ConvertUTF32toUTF16(const X_UINT** sourceStart, const X_UINT* sourceEnd,X_USHORT** targetStart, X_USHORT* targetEnd) 
{
	const X_UINT* source = *sourceStart;
	X_USHORT* target = *targetStart;
	while (source < sourceEnd) 
	{
		X_UINT ch;
		if (target >= targetEnd) 
		{
			break;
		}
		ch = *source++;
		if (ch <= UNI_MAX_BMP) 
		{ /* Target is a X_CHARacter <= 0xFFFF */
			/* UTF-16 surrogate values are illegal in UTF-32; 0xffff or 0xfffe are both reserved values */
			if (ch >= UNI_SUR_HIGH_START && ch <= UNI_SUR_LOW_END) 
			{
				//if /*(flags == strictConversion) */
		  {
			  --source; /* return to the illegal value itself */
			  break;
		  } 
		  //else 
		  //{
		  //	  *target++ = UNI_REPLACEMENT_CHAR;
		  //}
			} else 
			{
				*target++ = (X_USHORT)ch; /* normal case */
			}
		} else if (ch > UNI_MAX_LEGAL_UTF32)
		{
			// if (flags == strictConversion) 
			// {
			// }
			//else
			//{
			// *target++ = UNI_REPLACEMENT_CHAR;
			//}
		} else 
		{
			/* target is a X_CHARacter in range 0xFFFF - 0x10FFFF. */
			if (target + 1 >= targetEnd) {
				--source; /* Back up source pointer! */
				break;
			}
			ch -= halfBase;
			*target++ = (X_USHORT)((ch >> halfShift) + UNI_SUR_HIGH_START);
			*target++ = (X_USHORT)((ch & halfMask) + UNI_SUR_LOW_START);
		}
	}
	*sourceStart = source;
	*targetStart = target;
}

//////////////////////////////////////////////////////////////////////////
// 重载操作符实现
bool operator<(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString<szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator>(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString>szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator<=(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString<=szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator>=(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString<=szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator==(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString==szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator==(const xString& szString1, const X_CHAR* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString==tmpString.m_wcString;
}

//---------------------------------------------------------------------
bool operator==(const xString& szString1, const X_WCHAR* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString==tmpString.m_wcString;
}

//---------------------------------------------------------------------
bool operator==(const xString& szString1, const X_UINT* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString==tmpString.m_wcString;
}

//---------------------------------------------------------------------
xString operator+(const xString& szString1, const xString& szString2)
{
	xString newString;
	newString.m_wcString = szString1.m_wcString + szString2.m_wcString;

	return newString;
}

//---------------------------------------------------------------------
xString operator+(const xString& szString1, const X_CHAR* szString2)
{
	xString newString = szString2;
	newString.m_wcString = szString1.m_wcString + newString.m_wcString;

	return newString;
}

//---------------------------------------------------------------------
xString operator+(const xString& szString1, const X_WCHAR* szString2)
{
	xString newString = szString2;
	newString.m_wcString = szString1.m_wcString + newString.m_wcString;

	return newString;
}

//---------------------------------------------------------------------
xString operator+(const xString& szString1, const X_UINT* szString2)
{
	xString newString = szString2;
	newString.m_wcString = szString1.m_wcString + newString.m_wcString;

	return newString;
}

//---------------------------------------------------------------------
bool operator!=(const xString& szString1, const xString& szString2)
{
	return szString1.m_wcString!=szString2.m_wcString;
}

//---------------------------------------------------------------------
bool operator!=(const xString& szString1, const X_CHAR* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString!=tmpString.m_wcString;
}

//---------------------------------------------------------------------
bool operator!=(const xString& szString1, const X_WCHAR* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString!=tmpString.m_wcString;
}

//---------------------------------------------------------------------
bool operator!=(const xString& szString1, const X_UINT* szString2)
{
	xString tmpString = szString2;
	return szString1.m_wcString!=tmpString.m_wcString;
}


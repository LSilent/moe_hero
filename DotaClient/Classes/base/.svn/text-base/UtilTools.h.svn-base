
#ifndef __UTILTOOLS_H__
#define __UTILTOOLS_H__

#include "./base/Global.h"
#include <vector>
#include <map>
#include <stdlib.h>


class UtilTools
{
public:
	static int ConvertStringToVector(const wchar_t* strSource, vector<wstring>& vRet, const wchar_t* szKey);
	static int ConvertStringToVector(const char* strSource, vector<string>& vRet, const char* szKey);
	static int ConvertStringToIntVector(const char* strSource, vector<int>& vRet, const char* szKey);

	static float		StringToFloat(const wchar_t* str);
	static	string	    FloatToString(float f);

 	static int			StringToInt(const wchar_t* str);
	static unsigned int	StringToUInt(const wchar_t* str);

	static int			StringToInt(const char* str);
	static unsigned int	StringToUInt(const char* str);
	static float		StringToFloat(const char* str);

	static string		UIntToString(unsigned int value);
	static string		IntToString(int value);
	 
	static	int	WideChar2MultiByte(char* &pDestString,const wchar_t* orig);
	static	int	MultiByte2WideChar(wchar_t* &pWideString, const char* orig);

	//static	int	UTF8toToUnicode(wchar_t* &pWideString,const char *orig);
	//static  int UnicodeToUTF8( char * &pDestString,const wchar_t *orig  );

		template<typename InputIterator>
		static wchar_t decode_utf8_mb(InputIterator &iter, InputIterator last)
		{
			//if (iter == last) throw std::runtime_error("incomplete UTF-8 sequence");
			//if (((*iter) & 0xc0) != 0x80) throw std::runtime_error("invalid UTF-8 sequence");

			return (wchar_t)((*iter++) & 0x3f);
		}

		template<typename InputIterator>
		static wchar_t decode_utf8(InputIterator &iter, InputIterator last)
		{
			wchar_t ret;

			if (((*iter) & 0x80) == 0) // one byte
			{
				ret = *iter++;
			}
			else if (((*iter) & 0xe0) == 0xc0) // two bytes
			{
				wchar_t byte1 = (*iter++) & 0x1f;
				wchar_t byte2 = decode_utf8_mb(iter, last);
				ret = (byte1 << 6) | byte2;
			}
			else if (((*iter) & 0xf0) == 0xe0) // three bytes
			{
				wchar_t byte1 = (*iter++) & 0x0f;
				wchar_t byte2 = decode_utf8_mb(iter, last);
				wchar_t byte3 = decode_utf8_mb(iter, last);
				ret = (byte1 << 12) | (byte2 << 6) | byte3;
			}
			// TODO: support surrogate pairs
			//else throw std::runtime_error("UTF-8 not convertable to UTF-16");

			return ret;
		}

		template<typename InputIterator, typename OutputIterator>
		static OutputIterator utf8_wchar(InputIterator first, InputIterator last, OutputIterator dest)
		{
			for(; first!=last; ++dest)
				*dest = decode_utf8(first, last);
			return dest;
		}

		template<typename InputIterator, typename OutputIterator>
		static void encode_wchar(InputIterator iter, OutputIterator &dest)
		{
			if(*iter <= 0x007F)
			{
				*dest=(char)*iter;
				++dest;
			}
			else if(*iter <= 0x07FF)
			{
				*dest = (char)(
					0xC0 |
					((*iter & 0x07C0) >> 6)
					);
				++dest;

				*dest = (char)(
					0x80 |
					(*iter & 0x003F)
					);
				++dest;
			}
			else if(*iter <= 0xFFFF)
			{
				*dest = (char)(
					0xE0 |
					((*iter & 0xF000) >> 12)
					);
				++dest;

				*dest = (char)(
					0x80 |
					((*iter & 0x0FC0) >> 6)
					);
				++dest;

				*dest = (char)(
					0x80 |
					(*iter & 0x003F)
					);
				++dest;
			}
		}

		template<typename InputIterator, typename OutputIterator>
		static OutputIterator wchar_utf8(InputIterator first, InputIterator last, OutputIterator dest)
		{
			for(; first!=last; ++first)
				encode_wchar(first, dest);
			return dest;
		}

 
	static inline  void utf8_wchar(const std::string &utf8, std::wstring &wide)
	{
		wide.clear();
		utf8_wchar(utf8.begin(), utf8.end(), std::back_inserter(wide));
	}
	static inline std::wstring utf8_wchar(const std::string &str)
	{
		std::wstring ret;
		utf8_wchar(str, ret);
		return ret;
	}
	static inline void wchar_utf8(const std::wstring &wide, std::string &utf8)
	{
		utf8.clear();
		wchar_utf8(wide.begin(), wide.end(), std::back_inserter(utf8));
	}
	static inline std::string wchar_utf8(const std::wstring &str)
	{
		std::string ret;
		wchar_utf8(str, ret);
		return ret;
	}
	
	// limited to one year
	static inline std::string ConvertMillisecondToTimeString(X_UINT Millisecond)
	{
		const X_UINT maxSecond = 60 * 60 * 24 * 365;    // one year max
		
		X_UINT validSecond = min( maxSecond, Millisecond/1000 );
		
		char buff[64] ={0};

		sprintf(buff, "%02d:%02d:%02d", validSecond/(60*60), (validSecond % (60*60)) / 60, validSecond % 60);
		
		return std::string(buff);
	}

	static inline X_VOID strToColor(const char *str, unsigned char &r,unsigned char &g,unsigned char &b)
	{
		string rgb = str;
		X_INT size = rgb.size();
		if (size< 6)
		{
			return;
		}
		rgb = rgb.substr(size- 6);
		X_UINT color; 
		sscanf(rgb.c_str(),"%x",&color);
		color = color | 0xFF000000;
		r = (color >>16) & 0XFF;
		g = (color >>8) & 0XFF;
		b = color  & 0XFF;
	}
	 
	/*static inline  std::string  getLocalDate(X_UINT Millisecond)
	{
		 time_t time =  Millisecond;
		 struct tm *pTime = localtime(&time);

		 char *week[]={"–«∆⁄ÃÏ","–«∆⁄“ª","–«∆⁄∂˛","–«∆⁄»˝","–«∆⁄Àƒ","–«∆⁄ŒÂ","–«∆⁄¡˘"};
		 static char str[256] = {0};
		 sprintf(str,"%dƒÍ%02d‘¬%02d»’ %s",1900+pTime->tm_year,1+pTime->tm_mon,pTime->tm_mday,week[pTime->tm_wday]);
		return  str;
	}*/

	static inline  std::string  getLocalDateHour(X_UINT Millisecond)
	{
		time_t time =  Millisecond;
		struct tm *pTime = localtime(&time);

		static char str[256] = {0};
		sprintf(str,"%02d:%02d:%02d\n",pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
		return  str;
	}

	 //20130427
	 static inline  std::string  getDatestr(X_UINT data)
	 {
		 static char temp[12] = {0};
		 sprintf(temp, "%06d", data);
		 string str =  temp;
		 str = str.substr(0,4) + "/" + str.substr(4,2)+ "/" + str.substr(6);
		return str;
	 }

	 static inline  std::string  getDateHourstr(X_UINT time)
	 {
		 static char temp[12] = {0};
		 sprintf(temp, "%06d", time);
		 string str =  temp;
		 str = str.substr(0,2) + ":" + str.substr(2,2)+ ":" + str.substr(4);
		 return str;
	 }

	 static inline  std::string  getDateHourMinstr(X_UINT time)
	 {
		 static char temp[12] = {0};
		 sprintf(temp, "%04d", time);
		 string str =  temp;
		 str = str.substr(0,2) + ":" + str.substr(2,2);
		 return str;
	 }

	 static const X_CHAR* GET_TEXT_FROM_LANG(X_INT id);

	 static bool  Fiter(  const char *str);
	 static void  FilterText(  char *str);

    static int isEmail(const char *email);
    static bool isvalidAccount(const char *account);
    static bool isvalidNumAccount(const string &account);

	static X_INT findInVector(X_INT data,const vector<X_INT> &vec);
};


#endif
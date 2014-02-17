#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "GameType.h"
#include "GameDefine.h"
#include "GameStruct.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#ifndef SAFE_FREE
#define SAFE_FREE(x)	if( (x)!=X_NULL) { free (x); (x)=X_NULL; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x)	if( (x)!=X_NULL ) { delete (x); (x)=X_NULL; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if( (x)!=X_NULL ) { delete[] (x); (x)=X_NULL; }
#endif


#define X_NULL	 (0)
const X_BOOL	 XTRUE	 = 1;
const X_BOOL	 XFALSE	 = 0;

typedef X_ULLONG	 X_CLIENT_GUID;
#define INVALID_INDEX	 (-1)

enum ATTACK_RANGE
{
	AR_NEAR_RANGE = 0,
	AR_LONG_RANGE,
};
const X_INT EQUIP_MAX_ATTR = 5;
#define  UI_SHOW_RECREAT  1
enum EM_SHOP_IDTYPE
{
	EM_SHOP_ID_NORMAL = 1,
	EM_SHOP_ID_WOOD ,
	EM_SHOP_NUM
};

//------------------------------
enum  enum_config
{
	EM_Fresh_Hero_Cost = 1,
	EM_MAX_HUSONG_ROB_DAY_TIMES,
	EM_MAX_HUSONG_BEROB_DAY_TIMES,
	EM_ZHAO_MU_JIQIREN,
	EM_WOOD_OPEN_LEVEL,
	EM_BATTLE_BREAK_OUT,
	EM_BATTLE_BREAK_OUTLEVEL,
	EM_QUJING_LEVEL,
	EM_HUODONG_OPEN_LEVEL,	//活动开放等级
	EM_RANKLIST_OPEN_LEVEL,// 天梯开发等级
	EM_SHAKE_TIME_OVER,
	EM_SHAKE_NUM,
	EM_BEARPOINT_BUYNUM,
	EM_MATRIX_MAX_HERO,
};

//------------------------------------------
#define  ActionPointBuyNum 100
#define  ActionPointPerTime 100



#define  FONT_NAME_ARIAL_BOLD  "Arial-BoldMT"
#define  FONT_NAME_ARIAL  "Arial"


#define FNT_NAME_BLUE "n_blue.fnt"
#define FNT_NAME_GREEN "n_green.fnt"
#define FNT_NAME_RED "n_red.fnt"
#define FNT_NAME_HEROLEVEL "n_heroLv.fnt"
#define FNT_NAME_SUMMONERLEVEL "n_summonerLv.fnt"
#define FNT_NAME_MESSAGE "n_message.fnt"
#define FNT_NAME_WOODTRANSPORT "n_woodTransport.fnt"
#define FNT_NAME_LARGEGREEN "n_largeGreen.fnt"
#define FNT_SKILL_LARGEGREEN "n_largeGreen_words.fnt"
#define FNT_HERO_NAME "n_heroName_words.fnt"
#define FNT_HERO_NAME_GREEN "n_heroName_green_words.fnt"
#define FNT_NUM_LARGEWHITE "n_largeWhite.fnt"


#define  FONT_SIZE_24 24
#define  FONT_SIZE_22 22
#define  FONT_SIZE_30 30

#define SCREEN_SIZE CCDirector::sharedDirector()->getWinSize()
#define SCALE_X  SCREEN_SIZE.width / 640
#define SCALE_Y  SCREEN_SIZE.height / 960

#define SCALE_BMF  (SCALE_X * 0.5f)

#define  LAYER_MAX_ZORDER 999999
#define  ICON_COLOR_GRAY ccc3(95,95,95)
#define     CCCOLOR_YELLOW ccc3(247,206,0)
#define 	CCCOLOR_GREEN ccc3(166,196,23)
#define		CCCOLOR_WHITE ccc3(255,255,255)
#define     CCCOLOR_RED ccc3(97,49,38)
#define  MAX_NORMAL_SKILL_LEVEL     4
#define LOGIN_CONNECT   1
#define MAX_HERO_EQUIPMENT_NUM     6
#define MAX_HERO_SKILL_NUM         2
const static string  SOUND_EXT   =  ".mp3";


#define MY_PLATFORM_IOS                1
#define MY_PLATFORM_ANDROID            2
#define MY_PLATFORM_WIN32              3

// win32
#if defined(WIN32) && defined(_WINDOWS)
#undef  MY_TARGET_PLATFORM
#define MY_TARGET_PLATFORM         MY_PLATFORM_WIN32
#endif


#if defined(ANDROID)
	#undef		MY_TARGET_PLATFORM
	#define		MY_TARGET_PLATFORM         MY_PLATFORM_ANDROID
#endif

#if defined(__APPLE__)
	#define MY_TARGET_PLATFORM         MY_PLATFORM_IOS
#endif
	
/*enum USER_SDK
{
	USE_SDK_NUTS = -1,
	USE_SDK_NULL_WIN32 = 0,

	USE_SDK_PP_IOS,
	USE_SDK_91_IOS,
	USE_SDK_NUTS_IOS,

	USE_SDK_91_ANDROID,
	USE_SDK_NUTS_ANDROID,
};*/


#define 	USE_SDK_NULL_WIN32  -1
#define     USE_SDK_NUTS   0
#define 	USE_SDK_PP_IOS 1
#define 	USE_SDK_91_IOS 2
#define 	USE_SDK_NUTS_IOS 3
#define 	USE_SDK_91_ANDROID 4
#define 	USE_SDK_NUTS_ANDROID 5

#if (MY_TARGET_PLATFORM == MY_PLATFORM_WIN32)
#endif
#if (MY_TARGET_PLATFORM == MY_PLATFORM_ANDROID)
#endif
#if (MY_TARGET_PLATFORM == MY_PLATFORM_IOS)
#endif

#undef		SC_SDK

#define  SC_SDK  USE_SDK_NULL_WIN32 // USE_SDK_NUTS 


#endif
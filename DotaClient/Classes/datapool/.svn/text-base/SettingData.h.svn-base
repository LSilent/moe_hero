#ifndef __SETTINGDATA_H__
#define __SETTINGDATA_H__

#include "./base/Global.h"

class SettingData
{
public:

	static X_VOID   Init();
	static X_VOID  Set(const string &item,bool bSet);
	static bool Get(const string &item);
	static   X_VOID SetStr(const string &item,const string & data);
 
	static string  GetLoaclUserName();
	static string  GetIp();
	static string  GetSelectServer();
	static string  GetLoaclUserAccount();
	static string  GetLoaclUserPassword();
	static string  GetRecentServer();
	
	static const string Name;
	static const string IP;
	static const string SOUND;
	static const string AUDIO;
	static const string BACKGROUND;
	static const string SELECTSERVER;

	static const string ACCOUNT;
	static const string SAVE_PASSWORD;
	static const string PASSWORD;
	static const string AUTO_LOGIN;

	static const string RECENT_SERVER;
	static void onEnterServer(X_INT server);
	
protected:
	static X_VOID __onChangeSet(const string &item,bool bSet);

	
};
#endif // !__SETTINGDATA_H__

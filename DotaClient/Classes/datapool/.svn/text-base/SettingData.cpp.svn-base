#include "./datapool/SettingData.h"
#include "./cocos2d.h"
#include "./sound/SoundSystem.h"
#include "./Game.h"
#include "./DataBase/DataBaseSystem.h"
#include "GameVersion.h"
#include "./load/ResourceCheck.h"
#include "./base/UtilTools.h"

USING_NS_CC;
 

const string SettingData::SOUND = "Sound";
const string SettingData::AUDIO = "Audio";
const string SettingData::IP = "Ip";
const string SettingData::Name = "Name";
const string SettingData::BACKGROUND = "BackGround";
const string SettingData::SELECTSERVER = "ServerId";
const string SettingData::SAVE_PASSWORD = "SAVE_PASSWORD";
const string SettingData::PASSWORD = "PASSWORD";
const string SettingData::AUTO_LOGIN = "AUTO_LOGIN";
const string SettingData::ACCOUNT = "ACCOUNT";
 
const string SettingData::RECENT_SERVER = "recent_server";

X_VOID   SettingData::Init()
{
 
	bool bEXIT = Get("EXIT_CONFIG");
    string binVersion = g_GameVersion;
	CCUserDefault::sharedUserDefault()->setStringForKey("downloaded-version-code", "");
	CCUserDefault::sharedUserDefault()->flush();
	if(!bEXIT)
	{
		Set("EXIT_CONFIG",true);
		Set(SOUND,true);
		Set(AUDIO,true);
		Set(SAVE_PASSWORD,true);
		Set(AUTO_LOGIN,true);
		Set(BACKGROUND,true);
		CCUserDefault::sharedUserDefault()->setStringForKey(ACCOUNT.c_str(),"");
		CCUserDefault::sharedUserDefault()->setStringForKey(PASSWORD.c_str(),"");
		CCUserDefault::sharedUserDefault()->setStringForKey(IP.c_str(),Game::sm_IP);
		CCUserDefault::sharedUserDefault()->setStringForKey(Name.c_str(),"");
		CCUserDefault::sharedUserDefault()->setStringForKey("current-version-code","0.0.0");
        CCUserDefault::sharedUserDefault()->setStringForKey("BinVersion",binVersion);
		Set("auto_server",true);
		CCUserDefault::sharedUserDefault()->setStringForKey(RECENT_SERVER.c_str(), "");
		CCUserDefault::sharedUserDefault()->flush();
	}
	bool  auto_server = Get("auto_server"); 
	string str = GetSelectServer();
	if (auto_server || str.size() <= 0 )
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
		if (pDataFile)
		{
			X_INT num = pDataFile->GetRecordsNum();
			const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByLineNum(num-1);
			if (m_pTableData)
			{
				CCUserDefault::sharedUserDefault()->setStringForKey(SELECTSERVER.c_str(), UtilTools::IntToString(m_pTableData->id));
				CCUserDefault::sharedUserDefault()->flush();
			}
		}
	}
    string version = CCUserDefault::sharedUserDefault()->getStringForKey("BinVersion");
    
    if (version != binVersion )
    {
        CCUserDefault::sharedUserDefault()->setStringForKey("current-version-code","0.0.0");
        CCUserDefault::sharedUserDefault()->setStringForKey("BinVersion",binVersion);
        CCUserDefault::sharedUserDefault()->flush();
		ResourceCheck::GetSingleton()->reset();
    }
    CCLog(version.c_str());
    
}
X_VOID SettingData::Set(const string &item,bool bSet)
{
	if (bSet)
	{
		CCUserDefault::sharedUserDefault()->setStringForKey(item.c_str(),"true");
	}else
	{
		CCUserDefault::sharedUserDefault()->setStringForKey(item.c_str(),"false");
	}
	CCUserDefault::sharedUserDefault()->flush();
	__onChangeSet(item,bSet);
}
X_VOID SettingData::__onChangeSet(const string &item,bool bSet)
 {
	 if (item == SOUND)
	 {
		 SoundSystem::GetSingleton()->pauseBackgroundMusic(!bSet);
	 }else if (item == AUDIO)
	 {
		 SoundSystem::GetSingleton()->pauseAllEffects(!bSet);
	 }
 }
X_VOID SettingData::SetStr(const string &item,const string & data)
{
	 CCUserDefault::sharedUserDefault()->setStringForKey(item.c_str(),data.c_str());
	 if (item == SELECTSERVER)
	 {
		 Set("auto_server",false);
	 }
	 CCUserDefault::sharedUserDefault()->flush();
}
bool SettingData::Get(const string &item)
{
	return	CCUserDefault::sharedUserDefault()->getStringForKey(item.c_str()) == "true";
}

string  SettingData::GetIp()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(IP.c_str());
}
string  SettingData::GetLoaclUserName()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(Name.c_str());
}
string  SettingData::GetSelectServer()
{
	return    CCUserDefault::sharedUserDefault()->getStringForKey(SELECTSERVER.c_str());
}
string  SettingData::GetRecentServer()
{
	return    CCUserDefault::sharedUserDefault()->getStringForKey(RECENT_SERVER.c_str());
}


string  SettingData::GetLoaclUserAccount()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(ACCOUNT.c_str());
}
string  SettingData::GetLoaclUserPassword()
{
	return CCUserDefault::sharedUserDefault()->getStringForKey(PASSWORD.c_str());
}
void SettingData::onEnterServer(X_INT server)
{
	string str = CCUserDefault::sharedUserDefault()->getStringForKey(RECENT_SERVER.c_str());
	
	if (str.size() <= 0 )
	{
		CCUserDefault::sharedUserDefault()->setStringForKey(RECENT_SERVER.c_str(), UtilTools::IntToString(server));
	}else
	{
		vector<X_INT> ser; UtilTools::ConvertStringToIntVector(str.c_str(),ser,"|");

		vector<X_INT>::iterator ifind =  find(ser.begin(),ser.end(),server);

		if (ifind == ser.end())
		{
			str += "|";
			str += UtilTools::IntToString(server);
		}else
		{
			str = "";
			ser.erase(ifind);
			X_INT size = ser.size();
			for ( X_INT i = 0;i < size ; i++)
			{
				str += UtilTools::IntToString(ser[i]);
				if (i != size -1)
				{
					str += "|";
				}
			}
			str += "|";
			str += UtilTools::IntToString(server);
		}
		UtilTools::ConvertStringToIntVector(str.c_str(),ser,"|");//ÔÙ´Î×ª»»

		X_INT size = ser.size();

	
		X_INT k = 0;

		if (size > 3)
		{
			k = size - 3;
		}	
		str = "";
		for ( ;k < size ; k++)
		{
			str += UtilTools::IntToString(ser[k]);
			if (k != size -1)
			{
				str += "|";
			}
		}
		CCUserDefault::sharedUserDefault()->setStringForKey(RECENT_SERVER.c_str(), str);
	}
	CCUserDefault::sharedUserDefault()->flush();
}
#include "./base/nuts.h"
#include "./game.h"
#include "./event/EventSystem.h"
#include "./timer/SystemTimer.h"
#include "./base/md5.h"
#include "./base/sha1.h"
#include <sstream>
#include "curl/curl.h"
#include "network/HttpClient.h"
#include "./base/UtilTools.h"
#include <algorithm>
#include <functional>   // std::plus
#include <sys/timeb.h> 
#include "./datapool/SettingData.h"
#include "./appStorePurchase.h"
#include "./database/DataBaseSystem.h"
#include "./base/Sdk_Handler.h"

using namespace cocos2d;
using namespace cocos2d::extension;
string nuts::KEY = "D532BCCDE0600B186DBB7ADD9";
static httpBack phttp;
int toUpper( int c )
{
	return toupper( c ) ;
}
int toLower( int c )
{
	return tolower( c ) ;
}
map<string,string> nuts::sm_nuts_reg_error;
string nuts::m_userid ="";
string nuts::m_userAccount = "";
string nuts::mTempuserAccount = "";

string nuts::mTempuserPassword= "";

bool nuts::checkAndEnter =false;


string nuts::sm_billno = "";
string nuts::sm_zone = "";


void nuts::init()
{
	/*sm_nuts_reg_error.clear();
	sm_nuts_reg_error.insert(map<string,string>::value_type("-1","没有访问权限"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-10","帐号格式错误"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-11","查询参数作物"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-12","链接已经失效"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-13","帐号不存在"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-14","密码不正确"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-16","加密验证错误"));
	sm_nuts_reg_error.insert(map<string,string>::value_type("-20","用户名已注册"));*/
	m_userAccount = "";
}
void nuts::loginCallBack()
{
	Game::Connect();
}
void nuts::regeditDown(const string& account,const string &password)
{
	struct timeb t1;  
	ftime(&t1);
    
    unsigned long long temp = t1.time;
    temp*= 1000;
	unsigned long long t = temp+t1.millitm;
    

	mTempuserPassword = password;
	std::ostringstream s1 ;
	s1<<t<<"\0";
	//string account = "hipein12341@163.com";//utf8编码
	//string password = "123456";
	static char  __password[40];
	memset(__password,0,sizeof(__password));
	SHA1().SHA_GO(password.c_str(),__password);

	string sha1password= __password;
	std::transform(sha1password.begin(), sha1password.end(), sha1password.begin(), toUpper);

	string game = "ios_dota";
	string stime = s1.str();
	string ip = "192.168.1.11";
	mTempuserAccount = account;

	string sign = MD5(KEY+account+sha1password+game+stime+ip).toString();
	std::transform(sign.begin(), sign.end(), sign.begin(), toUpper);

	string url = "http://udb.dota8.cn/ws/reg/iosreg.do?"+string("account=")+account+string("&password=")+string(sha1password)+"&game="+game+"&time="+stime+"&ip="+ip+"&sign="+sign;

	CCLog("%s",url.c_str());
	CCHttpClient *pcleint = CCHttpClient::getInstance();
	 pcleint->setTimeoutForConnect(5);
	CCHttpRequest *req = new CCHttpRequest();
	req->setRequestType(CCHttpRequest::kHttpGet);
	req->setUrl(url.c_str());
	req->setTag("reg_To_nuts");  
	req->setResponseCallback(&phttp,(SEL_CallFuncND)&httpBack::CallFuncND);
	pcleint->send(req);
	req->release();

}

void nuts::checkUserAccount(const string& account,const string &password)
{
	struct timeb t1;
	ftime(&t1);
    
    unsigned long long temp = t1.time;
    temp*= 1000;
	unsigned long long t = temp+t1.millitm;
    
	mTempuserAccount = account;
	std::ostringstream s1 ;
	s1<<t<<"\0";
	mTempuserPassword = password;
	string stime = s1.str();//1970年1月1日0点0分0秒算起
	//string account = "hipein@163.com";//账号,utf8编码

	static char  __password[40];
	//string password = "123456";
	memset(__password,0,sizeof(__password));
	SHA1().SHA_GO(password.c_str(),__password);

    string game = "ios_dota";

	string sha1password = __password;
	std::transform(sha1password.begin(), sha1password.end(), sha1password.begin(), toLower);//小写

	string encrypt = MD5(account+sha1password+stime).toString();	//encrypt
	std::transform(encrypt.begin(), encrypt.end(), encrypt.begin(), toUpper);//小写

	CCHttpClient *pcleint = CCHttpClient::getInstance();
	 pcleint->setTimeoutForConnect(5);
	CCHttpRequest *req = new CCHttpRequest();
	string url = "http://udb.dota8.cn/ws/loginForSeq.do?"+string("account=")+account+"&game="+game+string("&time=")+string(stime)+"&encrypt="+encrypt;
	 CCLog("%s",url.c_str());
	req->setRequestType(CCHttpRequest::kHttpGet);
	req->setUrl(url.c_str());
	req->setTag("Check_To_nuts");  
	req->setResponseCallback(&phttp,(SEL_CallFuncND)&httpBack::CallFuncND);
	pcleint->send(req);
	req->release();

}
void nuts::loginPressDown()
{    
	m_userAccount = SettingData::GetLoaclUserAccount();
	string password =  "";
	if (SettingData::Get(SettingData::SAVE_PASSWORD))
	{
		password =  SettingData::GetLoaclUserPassword();
	}
	if (m_userAccount.size()>0&&password.size()>0 )
	{
		checkAndEnter = false;
		checkUserAccount(m_userAccount,password);
		return;
	}
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_USER_LOGIN_SHOW);
}
void httpBack::CallFuncND(CCNode* pNode, void* pargv)
{

	CCHttpResponse *response = (CCHttpResponse*)pargv;  
	if(!response->isSucceed())  
	{  

		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(612));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		//printf("error is here %s",response->getErrorBuffer());  
		return;  
	}  
	const char* tag = response->getHttpRequest()->getTag();
	std::string recieveData;   
	std::vector<char> *data = response->getResponseData();  
	int vectorLength = data->size();  
	if(vectorLength <= 0)  
	{  
		return;  
	}  
	for(int i=0;i<vectorLength;i++)  
	{  
		recieveData += (*data)[i];  
	}  
	 CCLog("recieve data is %s",recieveData.c_str());  
	vector<string> strV;strV.clear();

	string str = UtilTools::GET_TEXT_FROM_LANG(UtilTools::StringToInt(recieveData.c_str()));
	if (str.size()>0)
	{
		strV.push_back(str);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
	}
	/*if (nuts::sm_nuts_reg_error.find(recieveData)!=  nuts::sm_nuts_reg_error.end())
	{
		strV.push_back( nuts::sm_nuts_reg_error[recieveData]);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
	}*/
	if(0 == strcmp(tag, "reg_To_nuts"))  
	{  
		if (recieveData.size()>= 5 &&UtilTools::isvalidNumAccount(recieveData))
		{
            //SdkHandler::onLoginSuncess();
			nuts::m_userid = recieveData;
			nuts::m_userAccount = nuts::mTempuserAccount;
			SettingData::SetStr(SettingData::ACCOUNT,nuts::m_userAccount);
			if(SettingData::Get(SettingData::SAVE_PASSWORD))
			{
				SettingData::SetStr(SettingData::PASSWORD,nuts::mTempuserPassword);
			}
			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_REG_SUCCESS);
		}else
		{
			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_REG_FAILED);
		}
	}else if(0 == strcmp(tag, "Check_To_nuts"))  
	{  
		if (recieveData.size()>= 5)
		{
            //SdkHandler::onLoginSuncess();
			nuts::m_userid = recieveData;
			nuts::m_userAccount = nuts::mTempuserAccount;
			SettingData::SetStr(SettingData::ACCOUNT,nuts::m_userAccount);
			if(SettingData::Get(SettingData::SAVE_PASSWORD))
			{
				SettingData::SetStr(SettingData::PASSWORD,nuts::mTempuserPassword);
			}

			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_CHECK_SUCCESS);
			bool b = SettingData::Get(SettingData::AUTO_LOGIN);
			if (b)
			{
				Game::Connect();
				return;
			}else
			{
				if (nuts::checkAndEnter)
				{
					Game::Connect();
				}else
				{
					EventSystem::GetSingleton()->PushEvent(GAME_EVNET_USER_LOGIN_SHOW);
				}
			}
		}else
		{
			EventSystem::GetSingleton()->PushEventAndProcessNow(GAME_EVNET_USER_CHECK_FAILED);
		}
		nuts::checkAndEnter = false;
	}  
}
string nuts::getUserId()
{
	
	return m_userid;
}
void  nuts::buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id)
{
    sm_zone = UtilTools::IntToString(zone);
    sm_billno = UtilTools::IntToString(biilNo);
    
    const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CHARGE);
    if (!pDataFile) {
        return;
    }
    const stDBC_FILE_CHARGE*  pdata = (const stDBC_FILE_CHARGE *)pDataFile->GetFieldsByIndexKey(id);
    if (!pdata)
    {
        return;
    }
    #if (MY_TARGET_PLATFORM == MY_PLATFORM_IOS)
			appStorePurchase::startBuyProductWithID(pdata->Productid);
            //appStorePurchase::getProductListInfo();
	#endif
	
}


void nuts::linktohelp()
{
	//[[UIApplication sharedApplication]openURL:[NSURL URLWithString:@"http://m.dota8.cn"]];
}

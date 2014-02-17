#ifndef __NUTS_H__
#define __NUTS_H__
#include "./base/Global.h"
#include "cocos2d.h"

class nuts
{
public:

	static void init();
	static void loginCallBack();
	static void loginPressDown();
	static void regeditDown(const string& account,const string &password);

	static void checkUserAccount(const string& account,const string &password);
	static string getUserId();
	static void buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id);

	static void linktohelp();

	static string KEY;


	static map<string,string> sm_nuts_reg_error;
	static string m_userid;
	static string m_userAccount;
	static  bool checkAndEnter;

 
	static string mTempuserAccount;//不允许外部调用
	static string mTempuserPassword;//不允许外部调用

    static string sm_billno;
    static string sm_zone;
    
};

class  httpBack :public cocos2d::CCObject
{
public:
	 
	void CallFuncND(cocos2d::CCNode*, void*);
private:

};

 
#endif // !__NUTS_H__


#ifndef __Sdk_Handler_H__
#define __Sdk_Handler_H__

#include "./base/Global.h"
 


class SdkHandler
{
public:

	//---------------------------------SDK-------------------------

	static void onGameVersionError(bool clinetVersionHigher);
	static void buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id);

	static  string getMoneyName();
	static  string getMoneyName1();


	static  void  requestShopInfo();
	static  void onGameCenter();
	static   string getLogoImageAndText(string &text);
	static  void  loginPressDown();
	static  void  downNewVersion();
 
	static  void   pauseGame();
	 
	//----------------------------------------------------------------
	static string  getUserId() ;
	 
    //仅用来判断sdk是否成功登陆 编码点击n次
   //// static void  onLoginSuncess();
    static bool  isLoginSuncess();
    static  int  chargerZone;
    
    static void  inGameShowToolBar();

	static string  getAppId();
	 
	static string shareInfo;
    
    
    static void shakeBegin();
    static void shakeRestart();
    static void shakePause();
    static void shakeEnd();
protected:
   // static bool  isEnterSdklogin;
	
};


#endif
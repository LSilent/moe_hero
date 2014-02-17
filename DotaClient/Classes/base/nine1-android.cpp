

#include "nine1.h"
#include "./base/Global.h"
#include "Game.h"
#include "./database/DataBaseSystem.h"
 
#if (MY_TARGET_PLATFORM == MY_PLATFORM_ANDROID)  
#include <jni.h>  
#include "platform/android/jni/JniHelper.h"  
#include <android/log.h>  
#include "jni/JniHelper.h"
#endif
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;
 
void nine1::loginCallBack()
{
    
    Game::Connect();
}


extern "C"{
void nine1::loginPressDown()
{
	//91安卓特殊处理  先自动登陆游戏账号  然后点击直接连接服务器。
	//其他sdk是点击登陆、 这里是点击就连接服务器了
	
	
/*#if SC_SDK == USE_SDK_91_ANDROID
     
  JniMethodInfo  minfo;  
	jobject jobj;  
	bool b=   JniHelper::getMethodInfo(minfo,  
		"com/hulu/dota/WelcomeActivity",   
		"accountLogin91",   
		"()V");  
	if(!b)
	{  
		CCLog("jni:com/hulu/dota/WelcomeActivity accountLogin91 not found");
		 return  ;
	}
	else
		{  
			CCLog("jni:com/hulu/dota/WelcomeActivity accountLogin91   found");
			jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	   (minfo.env->CallVoidMethod(jobj,minfo.methodID));  
	}
		#endif
	return;*/

/*CCLog("-------------------91   ANDROID  loginPressDown");
 #if SC_SDK == USE_SDK_91_ANDROID
     
  JniMethodInfo  minfo;  
	jobject jobj;  
	bool b=   JniHelper::getStaticMethodInfo(minfo,  
		"com/hulu/dota/ninie1",   
		"accountLogin91",   
		"()V");  
	if(!b)
	{  
		CCLog("jni:com/hulu/dota/ninie1 accountLogin91 not found");
		 return  ;
	}
	else
		{  
			CCLog("jni:com/hulu/dota/ninie1 accountLogin91   found");
	   (minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID));  
	}
     
     
#endif*/
    
}
void nine1::CenterPressDown()
	{
		CCLog("-------------------91   ANDROID  CenterPressDown");
#if SC_SDK == USE_SDK_91_ANDROID
	JniMethodInfo minfo;  
	jobject jobj;  
	bool b=  JniHelper::getStaticMethodInfo(minfo,  
		"com/hulu/dota/ninie1",   
		"CenterPressDown",   
		"()V");  
	if(!b){  
		CCLog("jni:com/hulu/dota/ninie1 CenterPressDown not found");
	}else{  
		 CCLog("jni:com/hulu/dota/ninie1 CenterPressDown   found");
     (minfo.env->CallStaticVoidMethod(minfo.classID,minfo.methodID));  
		}
#endif
		
}
string nine1::getUserId()
{
 #if SC_SDK == USE_SDK_91_ANDROID
	JniMethodInfo minfo;  
	jobject jobj;  
	bool b=   JniHelper::getStaticMethodInfo(minfo,  
		"com/hulu/dota/ninie1",   
		"getUserId",   
		"()Ljava/lang/String;");  
	if(!b){  
		CCLog("jni:com/hulu/dota/ninie1 getUserId not found");
		 return "nine1::getUserId invalid";
	}else{  
		 CCLog("jni:com/hulu/dota/ninie1 getUserId   found");
		 
		jstring userid = (jstring)(minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID));  
		
		
		return JniHelper::jstring2string(userid);
		}
#endif
    return "";
}
bool nine1::isLogin()
 {
 #if SC_SDK == USE_SDK_91_ANDROID

   	JniMethodInfo minfo;  
	jobject jobj;  
	bool b=   JniHelper::getStaticMethodInfo(minfo,  
		"com/hulu/dota/ninie1",   
		"isLogined",   
		"()Z");  
	if(!b){  
		CCLog("jni:com/hulu/dota/ninie1 isLogined not found");
		 return false;
	}else{  
		 CCLog("jni:com/hulu/dota/ninie1 isLogined   found");
		 
		jstring result = (jstring)(minfo.env->CallStaticObjectMethod(minfo.classID,minfo.methodID));  
		
		
		return string(JniHelper::jstring2string(result)) == string("ok");
		}
	 
#endif
     return false;
 }
void nine1::requestShopInfo()
{
 #if SC_SDK == USE_SDK_91_ANDROID

    
#endif
}


void  nine1::buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id)
{
 #if SC_SDK == USE_SDK_91_ANDROID

   const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CHARGE);
	if (!pDataFile)
	{
		return ;
	}
	const stDBC_FILE_CHARGE	*m_pTableData = (const stDBC_FILE_CHARGE*)pDataFile->GetFieldsByIndexKey(id);
	if (!m_pTableData)
	{
		return ;
	}
    string id91 = m_pTableData->Productid91;
    
     
#endif
}


void nine1::pauseGame()
{
 #if SC_SDK == USE_SDK_91_ANDROID
#endif
}


}
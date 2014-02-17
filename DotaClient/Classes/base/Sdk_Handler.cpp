#include "./base/Sdk_Handler.h"
#include "./ui/SceneManger.h"
#include "./ui/element/ModalDialogView.h"
#include "./game/MainGame.h"
#include  "./base/nuts.h"
#include "./base/nine1.h"
#include "./base/pp.h"
#include "./load/ResourceCheck.h"
#include "./DataBase/DataBaseSystem.h"
#include "./datapool/loginData.h"
#include "./datapool/DataPool.h"
#include "./Game.h"
#include "event/EventSystem.h"
#include "./base/comPlatform.h"


//------------------------sdk

int SdkHandler::chargerZone = 0;
void SdkHandler::onGameVersionError(bool clinetVersionHigher)
{
	if (clinetVersionHigher)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(715));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
        {
			#if  SC_SDK == USE_SDK_NUTS
				#if (MY_TARGET_PLATFORM == MY_PLATFORM_IOS)
					comPlatform::onAPPGameVersionError();
				#endif
			#endif
        }
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
			ModalDialogView * pView = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(616),MainGame::GetSingleton()->getNewVersionDelegate(),DIALOG_MODEL_SINGLE);
			SceneManger::GetSingleton()->AddChildToScene(pView,true);
		}
		break;
	case USE_SDK_91_IOS:
        {
             
        }
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		break;
	case USE_SDK_NUTS_ANDROID:
		break;

	default:
		break;
	}

}
void SdkHandler::buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id)
{
 
    chargerZone = zone;
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
        {
            nuts::buyGold(price,name,roleid,zone,biilNo,id);
		}
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
		#if  SC_SDK == USE_SDK_PP_IOS
			pp::buyGold(price,name,roleid,zone,biilNo);
		#endif
		}
		break;
	case USE_SDK_91_IOS:
		{
			#if  SC_SDK == USE_SDK_91_IOS
			nine1::buyGold(price, name, roleid, zone, biilNo,id);
			#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		{
				nuts::buyGold(price,name,roleid,zone,biilNo,id);
		}
		break;
	case USE_SDK_91_ANDROID:
		break;
	case USE_SDK_NUTS_ANDROID:
		{
				nuts::buyGold(price,name,roleid,zone,biilNo,id);
		}
		break;
	default:
		break;
	}
}

 string SdkHandler::getMoneyName()
{

	string str = UtilTools::GET_TEXT_FROM_LANG(618);
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
			 str = UtilTools::GET_TEXT_FROM_LANG(575);
		}
		break;
	case USE_SDK_91_IOS:
		{
		  str = UtilTools::GET_TEXT_FROM_LANG(704);
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		break;
	case USE_SDK_NUTS_ANDROID:
		break;
	default:
		break;
	}
	 
	return str;
 } string SdkHandler::getMoneyName1()
 {
 
 
	 string str = UtilTools::GET_TEXT_FROM_LANG(617);
	 switch (SC_SDK)
	 {
	 case USE_SDK_NUTS:
		 break;
	 case USE_SDK_NULL_WIN32:
		 break;
	 case USE_SDK_PP_IOS:
		 {
			 str = UtilTools::GET_TEXT_FROM_LANG(562);
		 }
		 break;
	 case USE_SDK_91_IOS:
		 {
			 str = UtilTools::GET_TEXT_FROM_LANG(705);
		 }
		 break;
	 case USE_SDK_NUTS_IOS:
		 break;
	 case USE_SDK_91_ANDROID:
		 {
			 str = UtilTools::GET_TEXT_FROM_LANG(705);
		 }
		 break;
	 case USE_SDK_NUTS_ANDROID:
		 break;
	 default:
		 break;
	 }

	 return str;
 }
 string SdkHandler::getLogoImageAndText(string &text)
{
	text ="";
	string image="";
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
			image = "pplogo.png";
			text = (UtilTools::GET_TEXT_FROM_LANG(694));
		}
		break;
	case USE_SDK_91_IOS:
		{
			image =  "91logo.png";
			text = (UtilTools::GET_TEXT_FROM_LANG(693));
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		{
			image =  "91logo.png";
			text = (UtilTools::GET_TEXT_FROM_LANG(693));
		}
		break;
	case USE_SDK_NUTS_ANDROID:
		break;
	default:
		break;
	}
	return image;
}
 

void SdkHandler::requestShopInfo()
{

	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		break;
	case USE_SDK_91_IOS:
		{
			#if SC_SDK == USE_SDK_91_IOS
				nine1::requestShopInfo();
			#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		break;
	case USE_SDK_NUTS_ANDROID:
		break;
	default:
		break;
	}
}
void SdkHandler::onGameCenter()
{

	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
			#if SC_SDK == USE_SDK_PP_IOS
				pp::ppCenterPressDown();
			#endif
		}
		break;
	case USE_SDK_91_IOS:
		{
			#if SC_SDK == USE_SDK_91_IOS
				nine1::CenterPressDown();
			#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
			{
		#if SC_SDK == USE_SDK_91_ANDROID
				nine1::CenterPressDown();
			#endif
		}
		break;
	case USE_SDK_NUTS_ANDROID:
	
		break;
	default:
		break;
	}
}
/*bool  SdkHandler::isEnterSdklogin = false;
bool  SdkHandler::isLoginSuncess()
{
    return SdkHandler::isEnterSdklogin;
}
void SdkHandler::onLoginSuncess()
{
    SdkHandler::isEnterSdklogin = true;
}*/
void  SdkHandler::loginPressDown()
{

   // SdkHandler::isEnterSdklogin = false;
    
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		{
			#if SC_SDK == USE_SDK_NUTS
			nuts::loginPressDown();
			#endif
		}
		break;
	case USE_SDK_NULL_WIN32:
		{
            //SdkHandler::isEnterSdklogin = true;
			Game::Connect();
		}
		break;
	case USE_SDK_PP_IOS:
		{
			#if SC_SDK == USE_SDK_PP_IOS
				pp::loginPressDown();
			#endif
		}
		break;
	case USE_SDK_91_IOS:
		{
			#if SC_SDK == USE_SDK_91_IOS
				nine1::loginPressDown();
			#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		{
			#if SC_SDK == USE_SDK_NUTS_IOS
			nuts::loginPressDown();
			#endif
		}
		break;
	case USE_SDK_91_ANDROID:
		{
			#if SC_SDK == USE_SDK_91_ANDROID
				//nine1::loginPressDown();
				if(nine1::isLogin)
					{
						Game::Connect();
					}
			#endif
		}
		break;
	case USE_SDK_NUTS_ANDROID:
		{
			#if SC_SDK == USE_SDK_NUTS_ANDROID
				nuts::loginPressDown();
			#endif
		}
		break;
	default:
             //SdkHandler::isEnterSdklogin = true;
		break;
	}

 
}
void  SdkHandler::downNewVersion()
{
 

	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		{
			#if SC_SDK == USE_SDK_PP_IOS
			string url = Game::getNewVersionUrl();
			pp::linktoDownNewVersion(url);
			#endif
		}
		break;
	case USE_SDK_91_IOS:
		{
#if SC_SDK == USE_SDK_91_IOS

#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		{
		#if SC_SDK == USE_SDK_NUTS_ANDROID
				
		#endif
		}
		break;
	case USE_SDK_NUTS_ANDROID:
		break;

	default:
		break;
	}

}
 
string  SdkHandler::getUserId() 
{
	  // return "6532987";
	string id = "";
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		{
			 id = nuts::getUserId();
		}
		break;
	case USE_SDK_NULL_WIN32:
		{
			 id =  DataPool::GetSingleton()->getLoginData()->getLoginName(); 
		}
		break;
	case USE_SDK_PP_IOS:
		{
		#if SC_SDK == USE_SDK_PP_IOS
					id = pp::getUserId();
		#endif
		}
		break;
	case USE_SDK_91_IOS:
		{
		#if SC_SDK == USE_SDK_91_IOS
					id = nine1::getUserId();
		#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		{
			  id = nuts::getUserId();
		}
		break;
	case USE_SDK_91_ANDROID:
		{
#if SC_SDK == USE_SDK_91_ANDROID
			id = nine1::getUserId();
#endif
		}
		break;
		break;
	case USE_SDK_NUTS_ANDROID:
		{
			 #if SC_SDK == USE_SDK_NUTS_ANDROID
			  id = nuts::getUserId();
			  #endif
		}
		break;
	default:
		break;
	}
	return id;
}

void SdkHandler::pauseGame()
{
	switch (SC_SDK)
	{
	case USE_SDK_NUTS:
		break;
	case USE_SDK_NULL_WIN32:
		break;
	case USE_SDK_PP_IOS:
		break;
	case USE_SDK_91_IOS:
		{
#if SC_SDK == USE_SDK_91_IOS
			nine1::pauseGame();
#endif
		}
		break;
	case USE_SDK_NUTS_IOS:
		break;
	case USE_SDK_91_ANDROID:
		{
			#if SC_SDK == USE_SDK_NUTS_ANDROID
			nine1::pauseGame();
			#endif
		}
		break;
	case USE_SDK_NUTS_ANDROID:
		break;

	default:
		break;
	}

}
void SdkHandler::inGameShowToolBar()
{
	switch (SC_SDK)
	{
        case USE_SDK_NUTS:
            break;
        case USE_SDK_NULL_WIN32:
            break;
        case USE_SDK_PP_IOS:
            break;
        case USE_SDK_91_IOS:
		{
#if SC_SDK == USE_SDK_91_IOS
			nine1::inGameShowToolBar();
#endif
		}
            break;
        case USE_SDK_NUTS_IOS:
            break;
        case USE_SDK_91_ANDROID:
		{
#if SC_SDK == USE_SDK_NUTS_ANDROID
			 
#endif
		}
            break;
        case USE_SDK_NUTS_ANDROID:
            break;
            
        default:
            break;
	}
}
string  SdkHandler::getAppId()
{
	return UtilTools::GET_TEXT_FROM_LANG(716);
}

void SdkHandler::shakeBegin()
{
    #if MY_TARGET_PLATFORM == MY_PLATFORM_IOS
        comPlatform::shakeBegin();

    #endif
}
void SdkHandler::shakeRestart()
{
     #if MY_TARGET_PLATFORM == MY_PLATFORM_IOS
        comPlatform::shakeRestart();
    #endif
}
void SdkHandler::shakePause()
{
     #if MY_TARGET_PLATFORM == MY_PLATFORM_IOS
        comPlatform::shakePause();
    #endif
}
void SdkHandler::shakeEnd()
{
     #if MY_TARGET_PLATFORM == MY_PLATFORM_IOS
        comPlatform::shakeEnd();
    #endif
}

string SdkHandler::shareInfo= "";
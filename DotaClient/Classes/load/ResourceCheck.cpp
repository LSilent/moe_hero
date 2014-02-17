#include "./load/ResourceCheck.h"
#include "./datapool/DataPool.h"
#include "Game.h"
#include "./base/UtilTools.h"
#include "./event/EventSystem.h"
#include "./game/MainGame.h"



using namespace std;
IMPLEMENT_SINGLETON(ResourceCheck);

X_VOID ResourceCheck::Initial()
{
	m_pAssetsManager = NULL;
	m_needUpdate =false;
	m_doneed= false;
	m_Progress = 0;
	createDownloadedDir();
	errcode = -2;
}

X_VOID ResourceCheck::Release()
{
	SAFE_DELETE(m_pAssetsManager);
}
bool ResourceCheck::checkVersion(const char* versionFileUrl)
{
	errcode = -2;
	m_doneed = false;
	string url =  versionFileUrl;
	if (!m_pAssetsManager)
	{
		m_pAssetsManager = new AssetsManager("","","");
		m_pAssetsManager->setDelegate(this);
		m_pAssetsManager->setConnectionTimeout(5);
  
	}
    m_needUpdate = false;
    string strver = url+"version.txt";
	m_pAssetsManager->setVersionFileUrl( strver.c_str());

	#if (MY_TARGET_PLATFORM == MY_PLATFORM_WIN32) 
		string surl  = versionFileUrl;
		if (strstr(surl.c_str(),"127.0.0.1") != NULL) 
			return false;
	#endif

	if (m_pAssetsManager->checkUpdate())//需要更新或者 网络错误
	{
		m_needUpdate = true;
	}
	bool netError = m_pAssetsManager->errcode == AssetsManager::kNetwork;//网络错误
	if (netError)
	{
		errcode = AssetsManager::kNetwork;
		return true;
	}else    
	{
		//需要真的更新
		errcode = -1;
	}
	CCLog("------------------------------------------------------------m_pAssetsManager->checkUpdate() m_needUpdate %d" ,int(m_needUpdate));
	return m_needUpdate;
}
/*
int ResourceCheck::__createThread()
{
#ifdef __WINDOWS__
	X_UINT nConnectThreadID = -1;
	m_thread = (HANDLE)::_beginthreadex(X_NULL, 0, __downThread, this, CREATE_SUSPENDED|THREAD_QUERY_INFORMATION, &nConnectThreadID);

	if(m_thread != X_NULL)
		ResumeThread(m_thread);
	return 0;
#else
	int errCode=0;  
	do {  
		pthread_attr_t tAttr;  
		errCode=pthread_attr_init(&tAttr);  
		CC_BREAK_IF(errCode!=0);  
		errCode=pthread_attr_setdetachstate(&tAttr, PTHREAD_CREATE_DETACHED);  
		if(errCode!=0)  
		{  
			pthread_attr_destroy(&tAttr);  
			break;  
		}  
		errCode=pthread_create(&m_thread, &tAttr, __downThread, this);  

	} while (0);  
	return errCode;  

#endif
}
#ifdef __WINDOWS__
X_UINT ResourceCheck::__downThread(LPVOID pParam)
{
		ResourceCheck* pres = static_cast<ResourceCheck*>(pParam);
		if (!pres)
		{
			return false;
		}
		if(!pres->m_pAssetsManager->update())
		{

			vector<string> strV;strV.clear();
			strV.push_back(UtilTools::GET_TEXT_FROM_LANG(590));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
			return  false;
		}
		cocos2d::CCFileUtils::sharedFileUtils()->purgeCachedEntries();
		
		Game::ReInitialWithNewRes();
		pres->m_doneed = true;
		return true;
}
#else
void*   ResourceCheck::__downThread(void *pParam)
{
	ResourceCheck* pres = static_cast<ResourceCheck*>(pParam);
	if (!pres)
	{
		return 0;
	}
	if(!pres->m_pAssetsManager->update())
	{

		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(590));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
		return  0;
	}
	cocos2d::CCFileUtils::sharedFileUtils()->purgeCachedEntries();

	Game::ReInitialWithNewRes();
	pres->m_doneed = true;
	return 0;//1

}
#endif
*/
string ResourceCheck::getVersion()
{
	if (!m_pAssetsManager)
	{
		m_pAssetsManager = new AssetsManager();
	}
	string str = m_pAssetsManager->getVersion();//old version
	if (str == ""||str.size()==0)
	{
		str = "0.0.0";
	}
	return str;
}void ResourceCheck::updateRes(const char* versionFileUrl)
{
	string url =  versionFileUrl;
	string str = m_pAssetsManager->getVersion();//old version
	if (str == ""||str.size()==0)
	{
		str = "0.0.0";
	}
	if (m_needUpdate)
	{
		str+= "--2N";
		m_pAssetsManager->setStoragePath(m_pathToSave.c_str());
		m_pAssetsManager->setPackageUrl( (url +str+".zip").c_str());
		m_pAssetsManager->update();
	}
 
}
/*bool ResourceCheck::updateRes( const char* versionFileUrl)
{
	string url =  versionFileUrl;
	string str = m_pAssetsManager->getVersion();//old version
	if (str == ""||str.size()==0)
	{
		str = "0.0.0";
	}
	if (m_needUpdate)
	{
		str+= "--2N";
		m_pAssetsManager->setStoragePath(m_pathToSave.c_str());
		m_pAssetsManager->setPackageUrl( (url +str+".zip").c_str());

		__createThread();
	}
	return true;
}*/
void ResourceCheck::createDownloadedDir()
{
	m_pathToSave = CCFileUtils::sharedFileUtils()->getWritablePath();
	m_pathToSave += "tmpdir";

	// Create the folder if it doesn't exist
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	DIR *pDir = NULL;

	pDir = opendir (m_pathToSave.c_str());
	if (! pDir)
	{
		mkdir(m_pathToSave.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	}
#else
	if ((GetFileAttributesA(m_pathToSave.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		CreateDirectoryA(m_pathToSave.c_str(), 0);
	}
#endif
}
int  ResourceCheck::getProgress()
{
	//return AssetsManager::m_downProgress;
	return m_Progress;
}
void ResourceCheck::reset()
{
	// Remove downloaded files
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	string command = "rm -r ";
	// Path may include space.
	command += "\"" + m_pathToSave + "\"";
	system(command.c_str());
#else
	string command = "rd /s /q ";
	// Path may include space.
	command += "\"" + m_pathToSave + "\"";
	system(command.c_str());
#endif
	// Delete recorded version codes.
	//pAssetsManager->deleteVersion();
	createDownloadedDir();
	cocos2d::CCFileUtils::sharedFileUtils()->purgeCachedEntries();
	Game::ReInitialWithNewRes();
}
void ResourceCheck::onError(AssetsManager::ErrorCode errorCode)
{
	errcode = errorCode;
	CCLog("----------------------------------------ResourceCheck::onError %d",errorCode);
	if (errorCode == AssetsManager::kNoNewVersion)
	{
		  "no new version";
		   MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
		   return;
	}
	if (errorCode == AssetsManager::kNetwork)
	{
		 //("network error");

		 /*vector<string> strV;strV.clear();
		 strV.push_back(UtilTools::GET_TEXT_FROM_LANG(590));
		 EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);*/
		CCUserDefault::sharedUserDefault()->setStringForKey("downloaded-version-code", "");
		CCUserDefault::sharedUserDefault()->flush();
		string zipfileName = string(m_pAssetsManager->getStoragePath()) + "cocos2dx-update-temp-package.zip";
	    remove(zipfileName.c_str());

	}
	if (errorCode == AssetsManager::kUncompress)
	{	CCUserDefault::sharedUserDefault()->setStringForKey("downloaded-version-code", "");
		CCUserDefault::sharedUserDefault()->flush();
		string zipfileName = string(m_pAssetsManager->getStoragePath()) + "cocos2dx-update-temp-package.zip";
		remove(zipfileName.c_str());
	}
	
}


void ResourceCheck::onProgress(int percent)
{
	//char progress[20];
	//snprintf(progress, 20, "downloading %d%%", percent);
	m_Progress = percent;
	if (m_Progress<0)
	{
		m_Progress =0;
	}
	if (m_Progress>100)
	{
		m_Progress =100;
	}
}

void ResourceCheck::onSuccess()
{
	CCLog("----------------------------------------ResourceCheck::onSuccess");
	errcode = -1;
	cocos2d::CCFileUtils::sharedFileUtils()->purgeCachedEntries();
	Game::ReInitialWithNewRes();
	m_doneed = true;
}

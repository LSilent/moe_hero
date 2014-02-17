
#ifndef __RESOURCECHECK_H__
#define __RESOURCECHECK_H__

#include "./base/Global.h"
#include "./base/Singleton.h"
#include "AssetsManager/AssetsManager.h"
#include "cocos2d.h"


#ifdef __WINDOWS__
#include <process.h>
#else
#include<pthread.h>
#endif // __windows__


USING_NS_CC;
USING_NS_CC_EXT;

class ResourceCheck : public Singleton<ResourceCheck> ,public cocos2d::extension::AssetsManagerDelegateProtocol
{
 
public:

	X_VOID Initial();
	X_VOID Release();
private: 

	std::string m_pathToSave;
	
	AssetsManager *m_pAssetsManager;
	bool m_needUpdate;
	bool m_doneed;

/*
#ifdef __WINDOWS__
	HANDLE m_thread;
	static X_UINT CALLBACK __downThread(LPVOID pParam);
#else
#include<pthread.h>
	pthread_t m_thread;
	static void* __downThread(void *pParam);
#endif

	int  __createThread();
	*/
	virtual void onError(cocos2d::extension::AssetsManager::ErrorCode errorCode);
	virtual void onProgress(int percent);
	virtual void onSuccess();
public:

	bool checkVersion(const char* versionFileUrl);
	void updateRes(const char* versionFileUrl);
	//bool updateRes(const char* versionFileUrl);
	string getResPath(){return m_pathToSave;}
	string getVersion();
    void reset();
	void  createDownloadedDir();
	int  getProgress();
	bool isNeedUpdate(){return m_needUpdate;}
	bool isDoned(){return m_doneed;}

	DECLARE_SINGLETON(ResourceCheck);

	
	int getErrCode(){return errcode;}

	int errcode;
protected:
	X_INT m_Progress;
};

#endif
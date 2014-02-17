
#ifndef __RESOURCESYSTEM_H__
#define __RESOURCESYSTEM_H__
 
#include "./base/Global.h"
#include "./base/Singleton.h"

 class ResourceSystem : public Singleton<ResourceSystem>
{
public:
	ResourceSystem();
	virtual ~ResourceSystem();

public:
	
	X_VOID Initial();
	X_VOID Release();

	X_ULLONG  LoadResource(const char* szFileName, char*& szMemAddr );
	X_BOOL	UnloadResource(char*& szMemAddr, unsigned long dwSize);


	X_ULLONG LoadResourceUnicode(const char* szFileName, wchar_t*& szMemAddr );
	X_BOOL UnloadResourceUnicode(wchar_t*& szMemAddr, unsigned long dwSize);

private: 
 
	DECLARE_SINGLETON(ResourceSystem);
};

#endif
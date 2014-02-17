#include "./load/ResourceSystem.h"

using namespace std;
IMPLEMENT_SINGLETON(ResourceSystem);

ResourceSystem::ResourceSystem()
{
}
ResourceSystem::~ResourceSystem()
{
}
X_VOID ResourceSystem::Initial()
{
	  
}

X_VOID ResourceSystem::Release()
{
 
}

X_ULLONG ResourceSystem::LoadResource(const char* szFileName, char*& szMemAddr )
{
	FILE *fpResourceFile = fopen(szFileName, "rb");
	if(!fpResourceFile)
		return 0;
	X_INT nFileSize = 0;
	fseek(fpResourceFile, 0, SEEK_END);
	nFileSize = ftell(fpResourceFile);
	fseek(fpResourceFile, 0, SEEK_SET);
	if(nFileSize>0)
	{
		szMemAddr = new char[nFileSize+2];
		memset(szMemAddr, 0, (nFileSize+2)*sizeof(char));
		fread(szMemAddr, 1, nFileSize, fpResourceFile);
		fclose(fpResourceFile);
		fpResourceFile = 0;
		return (unsigned long)nFileSize;
	}
	else
	{
		fclose(fpResourceFile);
		fpResourceFile = 0;
		return 0;
	}
}

X_BOOL ResourceSystem::UnloadResource( char*& szMemAddr, unsigned long dwSize )
{
	 SAFE_DELETE (szMemAddr);
	return XTRUE;
 
}
X_ULLONG ResourceSystem::LoadResourceUnicode(const char* szFileName, wchar_t*& szMemAddr)
{
	 
	if(szFileName == 0)
		return 0;

	char *tmpMemAddr = 0;   
	unsigned long dwSize = LoadResource(szFileName, tmpMemAddr );
	if(dwSize > 0)
	{
		unsigned short nFileFlag = 0;
		memcpy(&nFileFlag, tmpMemAddr, sizeof(unsigned short ));
		if(nFileFlag==0xFFFE || nFileFlag==0xFEFF)
		{
			szMemAddr = new wchar_t[dwSize/2];
			memset(szMemAddr, 0, sizeof(wchar_t)*(dwSize/2));
			memcpy(szMemAddr, tmpMemAddr+sizeof(unsigned short ), sizeof(wchar_t)*(dwSize/2)-1);
			szMemAddr[dwSize/2-1] = L'\0';
			UnloadResource(tmpMemAddr, dwSize);
			return (dwSize/2);
		}
		else
		{
			UnloadResource(tmpMemAddr, dwSize);
			return 0;
		}
	}

	return 0;
 
}

 
X_BOOL ResourceSystem::UnloadResourceUnicode(wchar_t*& szMemAddr, unsigned long dwSize)
{
	SAFE_DELETE(szMemAddr);
	return XTRUE;
}

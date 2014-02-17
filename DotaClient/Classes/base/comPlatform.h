 

#ifndef __dota__comPlatform__
#define __dota__comPlatform__

#include "string"
using namespace std;
class comPlatform
{
public:
    
    
    
	static  void   onAPPGameVersionError();
    

    static void shakeBegin();
    static void shakeRestart();
    static void shakePause();
    static void shakeEnd();
};

#endif

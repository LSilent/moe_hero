//
//  pp.h
//  dota2
//
//  Created by wz on 13-5-23.
//
//

#ifndef __dota2__pp__
#define __dota2__pp__

#include "string"
using namespace std;
class pp
{
public:
    
    static void loginCallBack();
    static void loginPressDown();
    static void ppCenterPressDown();
    
    static string getUserId();
    
    static void buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo);
    
    static void linktohelp();
    static void linktoDownNewVersion(const string & name);

};

#endif /* defined(__dota2__pp__) */

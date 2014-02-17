//
//  pp.cpp
//  dota2
//
//  Created by wz on 13-5-23.
//
//

#include "pp.h"
#include "Game.h"

#include "./base/Global.h"

#if SC_SDK == USE_SDK_PP_IOS
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#endif

#include "./base/UtilTools.h"
#include <iostream>  
#include <sstream>
#include "AppController.h"
#include "cocos2d.h"

void pp::loginCallBack()
{
    
    Game::Connect();
}
void pp::loginPressDown()
{
   #if SC_SDK == USE_SDK_PP_IOS
    /// <summary>
    /// 登陆从右边展示
    /// </summary>
    /// <returns>无返回</returns>
    //    NSString *msg = [NSString stringWithFormat:@"已切换到%@",[[PPAppPlatformKit sharedInstance] currentAddress]];
    //    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示" message:msg delegate:self cancelButtonTitle:@"确定" otherButtonTitles:nil, nil];
    //
    //    [alert show];
    //    [alert release];
    [[PPLoginView sharedInstance] showLoginViewByRight];
#endif
    
}
void pp::ppCenterPressDown()
{
    #if SC_SDK == USE_SDK_PP_IOS
    [[PPCenterView sharedInstance] showCenterViewByRight];
    #endif
}
string pp::getUserId()
{
 #if SC_SDK == USE_SDK_PP_IOS
    uint64_t id = [[PPAppPlatformKit sharedInstance]currentUserId];
    std::stringstream stream;
    std::string result;
    stream << id;  
    stream >> result;
    return result;
#  endif
    return "";
}
void  pp::buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo)
{
  #if SC_SDK == USE_SDK_PP_IOS
[(AppController *)[UIApplication sharedApplication].delegate exchangeGoods:price goodName:[NSString stringWithUTF8String:name.c_str()]  roleName:[NSString stringWithUTF8String:roleid.c_str()] zoneid:zone billno:biilNo];
#endif
}


void pp::linktohelp()
{
 #if SC_SDK == USE_SDK_PP_IOS
    [[UIApplication sharedApplication]openURL:[NSURL URLWithString:@"http://m.dota8.cn"]];
#endif
}
void pp::linktoDownNewVersion(const string & name)
{
   #if SC_SDK == USE_SDK_PP_IOS
    NSString *str = [NSString stringWithUTF8String:name.c_str()];
    NSURL *Url = [NSURL URLWithString:str];
    [[UIApplication sharedApplication]openURL:Url];
   #endif
}
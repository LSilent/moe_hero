//
//  nine1.m
//  DotaClient
//
//  Created by hulu on 13-8-12.
//
//

#import "nine1.h"

#include "./base/Global.h"
#if SC_SDK == USE_SDK_91_IOS
#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#import <NdComPlatform/NdComPlatformError.h>
#endif

#include "Game.h"
#import "AppController.h"
#include "./database/DataBaseSystem.h"
#include "./sound/SoundSystem.h"



void nine1::loginCallBack()
{
    
    Game::Connect();
}



void nine1::loginPressDown()
{
 #if SC_SDK == USE_SDK_91_IOS

    
    //AppController *controller = [AppController shareAppController];
    //[controller login91];
    
    [[NdComPlatform defaultPlatform] NdLogin:0];
#endif
    
}
void nine1::CenterPressDown()
{
 #if SC_SDK == USE_SDK_91_IOS

    [[NdComPlatform defaultPlatform] NdEnterPlatform:0];
#endif
}
string nine1::getUserId()
{
 #if SC_SDK == USE_SDK_91_IOS

    NSString* str= [[NdComPlatform defaultPlatform] loginUin];
    
    
    return [str cStringUsingEncoding:NSUTF8StringEncoding];
#endif
    return "";
}
void nine1::requestShopInfo()
{
 #if SC_SDK == USE_SDK_91_IOS

    AppController *controller = [AppController shareAppController];
    //获得虚拟商品信息
    NdPagination *pagination = [[NdPagination alloc] init];
    pagination.pageSize = 10;
    pagination.pageIndex = 1;
    [[NdComPlatform defaultPlatform] NdGetCommodityList:nil feeType:7 pagination:pagination packageId:nil delegate:controller];
    
    //获取虚拟商店的商品类别
    [[NdComPlatform defaultPlatform] NdGetCategoryList:controller];
    //获取虚拟商店促销信息
    [[NdComPlatform defaultPlatform] NdGetAppPromotion:controller];
#endif
}


void  nine1::buyGold(int price,const string & name,const string & roleid ,int zone,int biilNo,int id)
{
 #if SC_SDK == USE_SDK_91_IOS

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
    
    
    AppController *controller = [AppController shareAppController];
    NSString *ocID = [NSString stringWithUTF8String:id91.c_str()];
    controller.productIDFor91 = ocID;
    controller.billNo91 = biilNo;
    NSString *ocName = [NSString stringWithUTF8String:roleid.c_str()];
    controller.userDescriptionFor91 = [NSString stringWithFormat:@"%d", zone];
    
    [controller getBuyInfoFor91];
    //异步购买监听
    [[NSNotificationCenter defaultCenter] addObserver:controller selector:@selector(NdUniPayAsynResult:) name:(NSString *)kNdCPBuyResultNotification object:nil];
    
    //商店购买监听
//    [[NSNotificationCenter defaultCenter] addObserver:controller selector:@selector(NdBuyCommodityRusult:) name:(NSString*) kNdCPBuyResultNotification object:nil];
#endif
}
void nine1::pauseGame()
{
 #if SC_SDK == USE_SDK_91_IOS

    [[NdComPlatform defaultPlatform] NdPause];
#endif
}

bool nine1::isLogin()
 {
 #if SC_SDK == USE_SDK_91_IOS

     return true;
	 
#endif
     return true;
 }


void   nine1::inGameShowToolBar()
{
    #if SC_SDK == USE_SDK_91_IOS
    [[NdComPlatform defaultPlatform] NdShowToolBar:NdToolBarAtMiddleRight];
    #endif
}





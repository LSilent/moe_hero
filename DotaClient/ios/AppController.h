//
//  dota2AppController.h
//  dota2
//
//  Created by wz on 13-4-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#include "base/Global.h"
 #if SC_SDK == USE_SDK_91_IOS
#import <NdComPlatform/NdComPlatform.h>
#import <NdComPlatform/NdCPNotifications.h>
#import <NdComPlatform/NdComPlatformAPIResponse.h>
#import <NdComPlatform/NdComPlatform+VirtualGoods.h>
#import <NdComPlatform/NdComPlatformAPIResponse+VirtualGoods.h>

#endif

#import <StoreKit/StoreKit.h>


#import <CoreMotion/CoreMotion.h>

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate,SKStoreProductViewControllerDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
    
    
    //购买商品的价格
    NSString *_price;
    //购买商品的名称
    NSString *_name;
    int biilno;
    NSString *_roleid;
    int _zoneid;
        //记录91账号
    NSString *m_userIdfor91;
    
    #if SC_SDK == USE_SDK_91_IOS
        //购买91的商品信息
        NdBuyInfo *_buyInfoFor91;
        //91全部商品
        NSArray *_productsArrayFor91;
    #endif
    //91商品ID
    NSString *_productIDFor91;
  
    //用户信息
    NSString *_userDescriptionFor91;
    
    NSMutableArray *_shareTypeArray;
    
    CMMotionManager *_motionManager;
    NSTimer *_shakeTimer;
    NSInteger _shakeCount;
    NSInteger _shakeValid;
    
    UIView *_rootView;
}
+(AppController *) shareAppController;
-(void)exchangeGoods:(double)price goodName:(NSString *)sName roleName:(NSString *)sroleName zoneid:(int)izone billno:(int)ibillNO;
-(void) getBuyInfoFor91;
-(void) login91;

-(void) goAppStoreWithIdentifier:(NSString *)appId;

-(void) shakeBeginCalled;
-(void) shakeReStartCalled;
-(void) shakePauseCalled;
-(void) shakeEndCalled;

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;
@property (nonatomic, copy) NSString *productIDFor91;
@property (nonatomic, assign) int billNo91;
@property (nonatomic, copy) NSString *userDescriptionFor91;

@property (nonatomic, retain) UIView *rootView;

@end


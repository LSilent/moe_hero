//
//  dota2AppController.mm
//  dota2
//
//  Created by wz on 13-4-15.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//
#import <UIKit/UIKit.h>
#import "AppController.h"
#import "cocos2d.h"
#import "EAGLView.h"
#import "AppDelegate.h"
#include "./base/Global.h"
#import "RootViewController.h"


#import <AudioToolbox/AudioToolbox.h>


 #if SC_SDK == USE_SDK_PP_IOS
#import <PPAppPlatformKit/PPAppPlatformKit.h>
#endif


#include "Game.h"
#include "./sound/SoundSystem.h"
#include "./base/Sdk_Handler.h"
//#include "MobClick.h"
#include "./datapool/HuoDong.h"
#include "./datapool/DataPool.h"
#include "./sound/SoundSystem.h"

@implementation AppController

@synthesize window;
@synthesize viewController;
@synthesize productIDFor91 = _productIDFor91;
@synthesize billNo91 = biilno;
@synthesize userDescriptionFor91 = _userDescriptionFor91;

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;
using namespace cocos2d;

+(id) shareAppController
{
    static AppController *instance;
    if (!instance) {
        instance = [[AppController alloc] init];
    }
    return instance;
}

- (id)init
{
    if(self = [super init])
    {
             
    }
    return self;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    EAGLView *__glView = [EAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH_COMPONENT16
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples:0 ];

    // Use RootViewController manage EAGLView
    viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    viewController.wantsFullScreenLayout = YES;
    viewController.view = __glView;

    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:viewController];
    }
    
    [window makeKeyAndVisible];
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES];
    
    
    //友盟sdk
    //[MobClick setLogEnabled:YES];
   // [MobClick startWithAppkey:@"523fd76256240b0843074251" reportPolicy:REALTIME   channelId:@"***---inappstore---***"];
    
    
 #if SC_SDK == USE_SDK_PP_IOS
        // [(AppController *)[UIApplication sharedApplication].delegate exchangeGoods:<#(double)#>]
        /**
         *必须写在程序window初始化之后。详情请commad + 鼠标左键 点击查看接口注释
         *初始化应用的AppId和AppKey。从开发者中心游戏列表获取（https://pay.25pp.com）
         *设置是否打印日志在控制台
         *设置充值页面初始化金额
         *是否需要客户端补发订单（详情请查阅接口注释）
         *用户注销后是否自动push出登陆界面
         *是否开放充值页面【操作在按钮被弹窗】
         *若关闭充值响应的提示语
         *初始化SDK界面代码
         */
        [[PPAppPlatformKit sharedInstance] setAppId:695 AppKey:@"cd2ff13da5eff67ab522f5940e70f55d"];
        [[PPAppPlatformKit sharedInstance] setIsNSlogData:YES];
        [[PPAppPlatformKit sharedInstance] setRechargeAmount:@"100"];
        [[PPAppPlatformKit sharedInstance] setIsGetBillNo:YES];
        [[PPAppPlatformKit sharedInstance] setIsLogOutPushLoginView:YES];
        [[PPAppPlatformKit sharedInstance] setIsOpenRecharge:YES];
        // [[PPAppPlatformKit sharedInstance] setCloseRechargeAlertMessage:@"关闭充值提示语"];
        [PPUIKit sharedInstance];
        
        //添加监听请求登陆【只成功有效】
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(loginCallBack:)
                                                     name:PP_CLIENT_LOGIN_NOTIFICATION object:nil];
        //添加监听关闭客户端页面信息
        [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(closePageViewCallBack:)
                                                    name:PP_CLIENT_CLOSEPAGEVIEW_NOTIFICATION object:nil];
        //添加监听兑换结果返回信息
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(payResultCallBack:)
                                                     name:PP_CLIENT_EXCHANGE_NOTIFICATION object:nil];
        
        //添加监听注销
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(logOffCallBack)
                                                     name:PP_CLIENT_LOGOFF_NOTIFICATION object:nil];
        
        //添加监听关闭Web页面
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(closeWebViewCallBack:)
                                                     name:PP_CLIENT_CLOSEWEB_NOTIFICATION object:nil];
        
        //添加监听补发订单
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(postBillNoCallBack:)
                                                     name:PP_CLIENT_POSTBILLNOLIST_NOTIFICATION object:nil];
      
        
#endif
        
        
        
 #if SC_SDK == USE_SDK_91_IOS
        //用户登陆结果
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSLoginResult:) name:(NSString *)kNdCPLoginNotification object:nil];
        //91平台初始化结果
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSInitResult:) name:(NSString *)kNdCPInitDidFinishNotification object:nil];
        //
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSSessionInvalid:) name:(NSString *)kNdCPSessionInvalidNotification object:nil];
        //退出平台结果
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSleavePlatform:) name:(NSString *)kNdCPLeavePlatformNotification object:nil];
        //暂停完成结果
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(SNSPauseExist:) name:(NSString *)kNdCPPauseDidExitNotification object:nil];
        
         AppController *controller = [AppController shareAppController];
        [controller login91];
    
#endif
    
    //分享功能
    
        /////////////////////
    _rootView = self.window.rootViewController.view;
    
    
    cocos2d::CCApplication::sharedApplication()->run();
    
    return YES;
}

-(void) initPlat
{
    
//                             redirectUri:@"http://www.sharesdk.cn"];
    
    /**
     连接人人网应用以使用相关功能，此应用需要引用RenRenConnection.framework
     http://dev.renren.com上注册人人网开放平台应用，并将相关信息填写到以下字段
     **/
//    [ShareSDK connectRenRenWithAppId:@"226427"
//                              appKey:@"fc5b8aed373c4c27a05b712acba0f8c3"
//                           appSecret:@"f29df781abdd4f49beca5a2194676ca4"
//                   renrenClientClass:[RennClient class]];
        /**
     
     http://dev.t.qq.com上注册腾讯微博开放平台应用，并将相关信息填写到以下字段
     
     
     **/
//
//                                  appSecret:@"ae36f4ee3946e1cbb98d6965b0b2ff5c"
//                                redirectUri:@"http://www.sharesdk.cn"
//                                   wbApiCls:[WBApi class]];
   
    
}


- (void)initializePlatForTrusteeship
{
//    //导入QQ互联和QQ好友分享需要的外部库类型，如果不需要QQ空间SSO和QQ好友分享可以不调用此方法
//    [ShareSDK importQQClass:[QQApiInterface class] tencentOAuthCls:[TencentOAuth class]];
    
    //导入人人网需要的外部库类型,如果不需要人人网SSO可以不调用此方法
   //    //导入腾讯微博需要的外部库类型，如果不需要腾讯微博SSO可以不调用此方法
//   
//    
//    //导入微信需要的外部库类型，如果不需要微信分享可以不调用此方法
//    [ShareSDK importWeChatClass:[WXApi class]];
}



- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    cocos2d::CCDirector::sharedDirector()->pause();
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    cocos2d::CCDirector::sharedDirector()->resume();
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::CCApplication::sharedApplication()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::CCApplication::sharedApplication()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}


#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
     cocos2d::CCDirector::sharedDirector()->purgeCachedData();
}


- (void)dealloc {
     #if SC_SDK == USE_SDK_91_IOS
        [_buyInfoFor91 release];
        [_productsArrayFor91 release];
    #endif
    [super dealloc];
    
}                   
#pragma mark    ---------------SDK CALLBACK ---------------
//登陆成功回调方法
-(void)loginCallBack:(NSNotification *)noti
{
     /*MSG_PS_VERIFI2_RESPONSE mpvr = [UnPackage bytePSVerifi2Response:noti.object];
    
     MSG_GAME_SERVER mgs = {};
     mgs.len = 24;
     mgs.commmand = 0xAA000021;
     memcpy(mgs.token_key, mpvr.token_key, 16);
     NSString *requestURLStr = @"http://58.218.147.147:8850/login.php";
     NSURL *requestUrl = [[NSURL alloc] initWithString:[requestURLStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
     NSMutableURLRequest *request = [NSMutableURLRequest requestWithURL:requestUrl];
     
     NSData *token_keyData = [NSData dataWithBytes:mpvr.token_key length:16];
     [request setHTTPMethod:@"POST"];
     [request setTimeoutInterval:10];
     [request setHTTPBody:token_keyData];
     [self sendRequest:request];
     [requestUrl release];
     
     [bgGanmeCenterImageView setHidden:NO];
    [bgloginImageView setHidden:YES];*/
    
     //SdkHandler::onLoginSuncess();
     Game::Connect();
}
/**
 *在充值并且兑换业务服务器不能接受回调。需要客户端发起兑换的厂商需要再此回调获取订单号。将代码设置为[[PPAppPlatformKit sharedInstance] setIsGetBillNo:YES];
 *并且在收到通知做为处理后。请调用-(void)deleteBillNo:(NSString *)paramBillNo将当前订单从队列移除;否则订单一直会在队列象游戏客户端发送通知。
 */

 #if SC_SDK == USE_SDK_PP_IOS
-(void)postBillNoCallBack:(NSNotification *)noti{
    //    此时noti.objct为你的订单号
    //    如果获得处理后。则需要返回给我
    NSLog(@"获取补发订单回调-%@",noti.object);
    /**
     *这里些你们的业务，请求你们的服务端
     */

    if (1 == 1) {
        PPBillNoQueue *ppBillNoQueue = [[PPBillNoQueue alloc] init];
        [ppBillNoQueue deleteBillNo:noti.object];
        [ppBillNoQueue release];
        
    }
}

//关闭客户端页面回调方法
-(void)closePageViewCallBack:(NSNotification *)noti{
    if (PP_ISNSLOG) {
        //可根据关闭的VIEW页面做你需要的业务处理
        NSLog(@"当前关闭的VIEW页面回调是%@", noti.object);
    }
    //[[PPLoginView sharedInstance] showLoginViewByRight];
}

//关闭WEB页面回调方法
- (void)closeWebViewCallBack:(NSNotification *)noti{
 
    if (PP_ISNSLOG) {
        //可根据关闭的WEB页面做你需要的业务处理
        NSLog(@"当前关闭的WEB页面回调是%@", noti.object);
    }
    //[[PPLoginView sharedInstance] showLoginViewByRight];
}
//注销回调方法
-(void)logOffCallBack{

    if (PP_ISNSLOG) {
        NSLog(@"注销的回调");
    }
    Game::logOffCallBack();
   // [[PPLoginView sharedInstance] showLoginViewByRight];

}

//兑换回调接口【只有兑换会执行此回调】
-(void)payResultCallBack:(NSNotification *)noti
{
    if (PP_ISNSLOG) {
        NSLog(@"兑换的回调%@",noti.object);
    }
    //回调购买成功。其余都是失败
    if ([[noti object] isEqualToString:@"购买成功"]) {
        //购买成功发放道具
        
    }else{
        
    }
}
-(void)exchangeGoods:(double)price goodName:(NSString *)sName roleName:(NSString *)sroleName zoneid:(int)izone billno:(int)ibillNO
{
    biilno = ibillNO;
    _name = [[NSString alloc] initWithFormat:@"%@",sName];
    
    _roleid = [[NSString alloc] initWithFormat:@"%@",sroleName];
    _zoneid    = izone;
    PPExchange *exchange = [[PPExchange alloc] init];
    //查询余额
    int money = [[NSString stringWithFormat:@"%f",[exchange ppSYPPMoneyRequest]] intValue];
    if (money == -2) {
        [exchange release];
        return;
    }
    
    [[PPAppPlatformKit sharedInstance] currentUserName];
    [[PPAppPlatformKit sharedInstance] currentUserId];
    [[PPAppPlatformKit sharedInstance] currentSessionId];
    
    
    NSString *priStr = [NSString stringWithFormat:@"%.2lf",price ];
    _price = [[NSString alloc] initWithFormat:@"%@",priStr];
    if(money >= price){
        //如果PP币余额大于道具的金额。就直接调用兑换接口进行兑换
        //int time = [[NSDate date] timeIntervalSince1970];
        // NSString *billNO = [[NSString alloc] initWithFormat:@"%d",time];
        
		NSString *billNO = [[NSString alloc] initWithFormat:@"%d",ibillNO];
		
        //请求兑换道具
        [exchange ppExchangeToGameRequestWithBillNo:billNO Amount:priStr RoleId:sroleName ZoneId:izone];
        
        [billNO release];
    }else {
        //如果PP币余额小于于道具的金额。就提示直接进行充值兑换
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"温馨提示"
                                                        message:@"您的PP币不足，您需要先充值后再购买？"
                                                       delegate:self
                                              cancelButtonTitle:@"充值PP币"
                                              otherButtonTitles:@"取消", nil];
        [alert setTag:10];
        [alert show];
        [alert release];
    }
    [exchange release];
    
}
#pragma mark    ---------------UIALERTVIEW DELEGATE ---------------
-(void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex{
    
    if ([alertView tag] == 10) {
        if (buttonIndex == 0) {
            //设置订单号
            //int time = [[NSDate date] timeIntervalSince1970];
            //NSString *billNO = [[NSString alloc] initWithFormat:@"%d",time];
            
            NSString *billNO = [[NSString alloc] initWithFormat:@"%d",biilno];
            
            //调出充值并且兑换接口
            [[PPWebView sharedInstance] rechargeAndExchangeWebShow:billNO BillNoTitle:_name PayMoney:_price
                                                            RoleId:_roleid ZoneId:_zoneid];
            [billNO release];
        }
    }
}
#endif// #if SC_SDK == USE_SDK_PP_IOS



#pragma mark    --------------- 91 SDK ---------------

 #if SC_SDK == USE_SDK_91_IOS

//91登陆
-(void) login91
{
  
    
    //初始化
    NdInitConfigure *cfg = [[[NdInitConfigure alloc] init] autorelease];
    cfg.appid = 108016;
    cfg.appKey = @"b3e05de989e8b491aa0b5a0a50d03e2229524f956c40d20e";

    //这里以竖屏演示下orientation的设置，默认的为空表示不设置
    cfg.versionCheckLevel = ND_VERSION_CHECK_LEVEL_STRICT;
    cfg.orientation = UIDeviceOrientationPortrait;
	[[NdComPlatform defaultPlatform] NdInit:cfg];
    
    //调试状态
  // [[NdComPlatform defaultPlatform] NdSetDebugMode:0];


}
//91平台初始化
-(void) SNSInitResult:(NSNotification *) notify
{

    NSLog(@"91初始化完成");
    
  //[[NdComPlatform defaultPlatform] NdLogin:0];

    
}

//登录结果
- (void)SNSLoginResult:(NSNotification *)notify
{


    NSDictionary *dict = [notify userInfo];
	BOOL success = [[dict objectForKey:@"result"] boolValue];
	NdGuestAccountStatus* guestStatus = (NdGuestAccountStatus*)[dict objectForKey:@"NdGuestAccountStatus"];
	
	//登录成功后处理
	if([[NdComPlatform defaultPlatform] isLogined] && success) {
		
		
        if ([[NdComPlatform defaultPlatform] getCurrentLoginState]==ND_LOGIN_STATE_GUEST_LOGIN){
			NSString* strUin = [[NdComPlatform defaultPlatform] loginUin];
			NSString* strTip = nil;
			if ([guestStatus isGuestLogined]) {
				strTip = [NSString stringWithFormat:@"游客账号登录成功,\n uin = %@", strUin];
			}
			else if ([guestStatus isGuestRegistered]) {
				strTip = [NSString stringWithFormat:@"游客成功注册为普通账号,\n uin = %@", strUin];
			}
			
			if ([strTip length] > 0) {
				NSLog(@"91 login torist:%@",strTip);
			}
		}
		else {
            
           // SdkHandler::onLoginSuncess();
			// 普通账号登录成功!
            NSString* strUin = [[NdComPlatform defaultPlatform] loginUin];
            
            //用户并非第一次登陆&&切换帐号
            if (m_userIdfor91 && ![strUin isEqualToString:m_userIdfor91] ) {
                Game::logOffCallBack();
               
            }
          if (m_userIdfor91)
             [m_userIdfor91 release];
            m_userIdfor91 = [[NSString alloc] initWithString:strUin];
            
			if ([strUin length] > 0) {
				NSLog(@"91 login normal:%@",strUin);
			}
            Game::Connect();
            
            if( SoundSystem::GetSingleton())
            {
                  SoundSystem::GetSingleton()->setBackgroundMusicVolume(0.5f);
            }
		}
	}
	//登录失败处理和相应提示
	else {
        
        if( SoundSystem::GetSingleton())
        {
            SoundSystem::GetSingleton()->setBackgroundMusicVolume(0);
        }
		int error = [[dict objectForKey:@"error"] intValue];
		NSString* strTip = [NSString stringWithFormat:@"登录失败, error=%d", error];
		switch (error) {
			case ND_COM_PLATFORM_ERROR_USER_CANCEL://用户取消登录
				if (([[NdComPlatform defaultPlatform] getCurrentLoginState] == ND_LOGIN_STATE_GUEST_LOGIN)) {
					strTip =  @"当前仍处于游客登录状态";
				}
				else {
					strTip = @"用户未登录";
				}
				break;
				
				// {{ for demo tip
			case ND_COM_PLATFORM_ERROR_APP_KEY_INVALID://appId未授权接入, 或appKey 无效
				strTip = @"登录失败, 请检查appId/appKey";
				break;
			case ND_COM_PLATFORM_ERROR_CLIENT_APP_ID_INVALID://无效的应用ID
				strTip = @"登录失败, 无效的应用ID";
				break;
			case ND_COM_PLATFORM_ERROR_HAS_ASSOCIATE_91:
				strTip = @"有关联的91账号，不能以游客方式登录";
				break;
				
				// }}
			default:
				break;
		}
        NSLog(@"91 login error:%@",strTip);
	}

	
}
//无效会话
-(void) SNSSessionInvalid:(NSNotification *) noti
{
    
}
//离开平台
-(void) SNSleavePlatform:(NSNotification *) noti
{


    int loginState = [[NdComPlatform defaultPlatform] getCurrentLoginState];
	if (loginState == ND_LOGIN_STATE_NOT_LOGIN) {
        Game::logOffCallBack();
	}
	//更新虚拟币
}
//离开暂停
-(void) SNSPauseExist:(NSNotification *) noti
{
    
}
//异步购买结果
-(void) NdUniPayAsynResult:(NSNotification *)noti
{


    NSDictionary *dic = [noti userInfo];
    BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
    NSString *str = bSuccess?@"购买成功":@"购买失败";
    
    
    //购买失败
    if (!bSuccess) {
        
        [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
        
        NSString *strError = nil;
        int nErrorCode = [[dic objectForKey:@"error"] intValue];
        switch (nErrorCode) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL:
                strError = @"用户取消操作";
                break;
            case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
                strError = @"网络连接错误";
                break;
            case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                strError = @"服务器处理失败";
                break;
            case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED:
                //购买商品时 91豆余额不足 进入充值界面
                strError = @"用户支付订单已经提交";
                break;
            
            default:
                strError = @"购买过程发生错误";
                break;
        }
        NSLog(@"异步购买 %@ %@", str, strError);
    }
    else{
        [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
        NSLog(@"购买成功");
    }
    
    //本次购买的参数
    NdBuyInfo *buyInfo = (NdBuyInfo *)[dic objectForKey:@"buyInfo"];
    str = [str stringByAppendingFormat:@"\n<productId = %@, productName = %@, productCount = %d, cooOrderserial = %@>", buyInfo.productId, buyInfo.productName, buyInfo.productCount, buyInfo.cooOrderSerial];
    NSLog(@"异步购买结果 %@",str);

}
//虚拟商店购买结果
-(void) NdBuyCommodityRusult:(NSNotification *) noti
{

    NSDictionary *dic = [noti userInfo];
    BOOL bSuccess = [[dic objectForKey:@"result"] boolValue];
    NSString *str = bSuccess?@"购买成功":@"购买失败";
    
    
    //购买失败
    if (!bSuccess) {
        
        [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
        
        NSString *strError = nil;
        int nErrorCode = [[dic objectForKey:@"error"] intValue];
        switch (nErrorCode) {
            case ND_COM_PLATFORM_ERROR_USER_CANCEL:
                strError = @"用户取消操作";
                break;
            case ND_COM_PLATFORM_ERROR_NETWORK_FAIL:
                strError = @"网络连接错误";
                break;
            case ND_COM_PLATFORM_ERROR_SERVER_RETURN_ERROR:
                strError = @"服务器处理失败";
                break;
            case ND_COM_PLATFORM_ERROR_VG_MONEY_TYPE_FAILED:
                strError = @"查询虚拟币种失败";
                break;
                
            //91豆相关错误
            case ND_COM_PLATFORM_ERROR_ORDER_SERIAL_SUBMITTED:
                //购买商品时 91豆余额不足 进入充值界面
                strError = @"用户支付订单已经提交";
                break;
            case ND_COM_PLATFORM_ERROR_PARAM:
                strError = @"购买虚拟商品91豆总额不合法";
                break;
            case ND_COM_PLATFORM_ERROR_VG_ORDER_FAILED:
                strError = @"获取虚拟商品订单号失败";
                break;
                
            //游戏虚拟商品错误
            case ND_COM_PLATFORM_ERROR_VG_BACK_FROM_RECHARGE:
                strError = @"有进入虚拟币直冲页面";
                break;
            case ND_COM_PLATFORM_ERROR_PAY_FAILED:
                strError = @"购买虚拟商品失败";
                break;
                
            default:
                strError = @"购买过程发生错误";
                break;
        }
        
        
        NdVGErrorInfo *vgErrInfo = (NdVGErrorInfo *)[dic objectForKey:@"vgErrorInfo"];
        if (vgErrInfo) {
            str = [str stringByAppendingFormat:@"\n\n%@",vgErrInfo.strErrDesc];
        }
        NSLog(@"商店购买 %@ %@", str, strError);
    }
    else{
        [[NSNotificationCenter defaultCenter] removeObserver:self name:kNdCPBuyResultNotification object:nil];
        NSLog(@"购买成功");
    }
    
    //本次购买的参数
    NdBuyInfo *buyInfo = (NdBuyInfo *)[dic objectForKey:@"buyInfo"];
    str = [str stringByAppendingFormat:@"\n<productId = %@, productName = %@, productCount = %d, cooOrderserial = %@>", buyInfo.productId, buyInfo.productName, buyInfo.productCount, buyInfo.cooOrderSerial];
    NSLog(@"商店购买结果 %@",str);

}
//获取虚拟商店商品类别
-(void) getCategoryListDidFinish:(int)error records:(NSArray *)records
{


    if (error < 0) {
        NSLog(@"下载类别信息失败");
    }
    else {
        for (NdVGCategory* category in records) {
            NSLog(@"商品列表  类别id：%@   类别名称：%@", category.strCateId, category.strCateName);
            
        }
    }
}
//获得虚拟商店促销信息
-(void) getAppPromotionDidFinish:(int) error promotion:(NSString *)promotion
{
    if (error < 0) {
        NSLog(@"未进行促销");
    }
    else {
        NSLog(@"promotion %@",promotion);
    }
}
//获得虚拟商品信息
-(void) getCommodityListDidFinish:(int)error cateId:(NSString *)cateId feeType:(int)feeType packageId:(NSString *)packageId result:(NdBasePageList *)result
{
    if (error < 0) {
        NSLog(@"获得虚拟商品信息失败");
    }
    else{
        //int nPageCount = (result.totalCount + result.pagination.pageSize - 1)/ result.pagination.pageIndex;
        _productsArrayFor91 = [[NSArray alloc] initWithArray:result.records];
    }
}

//确定购买的商品
-(void) getBuyInfoFor91
{
    for (NdVGCommodityInfo *info in _productsArrayFor91) {
        //从所有商品之中匹配用户点击购买的品种
        if ([info.strProductId isEqualToString:_productIDFor91]) {
            //异步支付
            if (!_buyInfoFor91) {
                _buyInfoFor91 = [[NdBuyInfo alloc]init];
            }
            //商品id
            _buyInfoFor91.productId = info.strProductId;
            //商品名字
            _buyInfoFor91.productName = info.strProductName;
            //商品现价
            _buyInfoFor91.productPrice = [info.strSalePrice floatValue];
            //商品原价
            _buyInfoFor91.productOrignalPrice = [info.strOriginPrice floatValue];
            //商品的购买数量
            _buyInfoFor91.productCount = 1;
            //商品描述
            _buyInfoFor91.payDescription = _userDescriptionFor91;
            //交易订单号（唯一）
            _buyInfoFor91.cooOrderSerial = [NSString stringWithFormat:@"%d",biilno];
            
            
            
            //发送交易请求
            int res = [[NdComPlatform defaultPlatform] NdUniPayAsyn:_buyInfoFor91];
            if (res < 0) {
                NSLog(@"输入参数有误  无法提交购买请求");
            }
#if 0
            //商店支付
            NdVGOrderRequest *orderRequest = [NdVGOrderRequest orderRequestWithProductId:info.strProductId productCount:1 payDescription:@""];
            orderRequest.vgCommodityInfo = info;
            
            int res = [[NdComPlatform defaultPlatform] NdBuyCommodity:orderRequest];
            
            if (res < 0) {
                switch (res) {
                    case ND_COM_PLATFORM_ERROR_NOT_LOGINED:
                        NSLog(@"未登录");
                        break;
                    case ND_COM_PLATFORM_ERROR_PARAM:
                        NSLog(@"参数错误");
                        break;
                    default:
                        NSLog(@"购买失败");
                        break;
                }
            }
#endif
            
            break;
        }
    }
}
#endif
//  # #if SC_SDK == USE_SDK_91_IOS

-(void) productViewControllerDidFinish:(SKStoreProductViewController *)viewController{
    [viewController dismissViewControllerAnimated:YES completion:nil];
}

#pragma mark --------------------------------Shake-------------------------

-(void) shakeThePhone{

	
	 HuoDongData *pData = DataPool::GetSingleton()->getHuoDongData();
	 if(!pData)return;

	 if(!pData->isShakeReady()) 
	 {
		 return;
	 }
    static clock_t oldClock = clock();
    
    static NSDate *shakeStart;
    
    NSDate *now = [[NSDate alloc]init];
    NSDate *chekeDate = [[NSDate alloc] initWithTimeInterval:1.5f sinceDate:shakeStart];
    
    
    if ([now compare:chekeDate] == NSOrderedDescending || shakeStart == nil) {
        shakeStart = [[NSDate alloc]init];
    }
    CMAccelerometerData *accelermetorData = _motionManager.accelerometerData;
    
    if (fabsf(accelermetorData.acceleration.x) > 2.0||fabsf(accelermetorData.acceleration.y) > 2.0||fabsf(accelermetorData.acceleration.z) > 2.0) {
        _shakeValid =0;
        if(!pData->isShakeBegin() && pData->getShakeTime()>0)
        {
            pData->ShakeBegin(XTRUE);
        }
        _shakeCount++;
        pData->setShakeNum(_shakeCount);
        //SoundSystem::GetSingleton()->playEffect("shakeSound.mp3");
        AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
      
        oldClock = clock();
        NSLog(@"shakeCount %d",_shakeCount);
    }else
    {
        
        clock_t newClock = clock();
        X_ULLONG space =(X_ULLONG)( (X_FLOAT)( newClock - oldClock ) / ( (X_FLOAT)CLOCKS_PER_SEC / 1000.0 ) ) ;
        if(pData->isShakeBegin()&& space > 500)
        {
            _shakeValid++;
            NSLog(@"_shakeValid %d",_shakeValid);
        }
    }
    if (_shakeValid >= 1) {
        
        _shakeValid = 0;
        pData->ShakeBegin(XFALSE);
        pData->setShakeNum(_shakeCount,false);
        [self shakeEndCalled];
        return;

    }
	 if(!pData->isShakeBegin()&& pData->getShakeTime()<= 0 )
	 {
         
		pData->setShakeNum(_shakeCount);
         [self shakeEndCalled];
        return ;
	 }
}
-(void) shakeBeginCalled{
    _motionManager = [[CMMotionManager alloc]init];
    
    if (_motionManager.accelerometerAvailable){
        _motionManager.accelerometerUpdateInterval = 1.0f/10.0f;
        [_motionManager startAccelerometerUpdates];
    }
    
    _shakeTimer = [NSTimer scheduledTimerWithTimeInterval:1.0f/10.f target:self selector:@selector(shakeThePhone) userInfo:nil repeats:YES];
    _shakeCount = 0;
}
-(void) shakePauseCalled{
    [_shakeTimer setFireDate:[NSDate distantFuture]];
}
-(void) shakeReStartCalled{
    [_shakeTimer setFireDate:[NSDate date]];
}
-(void) shakeEndCalled{
    if (_shakeTimer) {
        [_shakeTimer invalidate];
        _shakeTimer = nil;
    }
    
    _shakeCount = 0;
}

@end


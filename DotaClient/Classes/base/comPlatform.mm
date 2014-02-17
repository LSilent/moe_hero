 

#include "./base/comPlatform.h"
#include "Game.h"
#include "./base/Global.h"
#include "./ui/SceneManger.h"
#include "./base/Sdk_Handler.h"
#import "AppController.h"
#import <StoreKit/StoreKit.h>
#import "AppController.h"


void comPlatform::onAPPGameVersionError()
{
 
    NSString *appid = [NSString stringWithUTF8String:SdkHandler::getAppId().c_str()];
    
	  
    //NSString *str = [NSString stringWithFormat:@"itms-apps://ax.itunes.apple.com/WebObjects/MZStore.woa /waiewContentsUserReviews?type=Purple+Software&id=%d", 665791418];
   // [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    
    NSString *strVersion = [[UIDevice currentDevice] systemVersion];
    float floatVersion = [strVersion floatValue];
    
    if (floatVersion >= 6.0) {
//        AppController *controller = [AppController shareAppController];
//        [controller goAppStoreWithIdentifier:@"1"];
        
        SKStoreProductViewController *storeVC = [[SKStoreProductViewController alloc] init];
        
      
        NSDictionary *dic = [NSDictionary dictionaryWithObject:appid forKey:SKStoreProductParameterITunesItemIdentifier];
        
        AppController *pApp = (AppController*)[[UIApplication sharedApplication] delegate];
        storeVC.delegate = pApp;
        
        CGRect winBounds = [[UIScreen mainScreen]bounds];
        CGSize winSize = winBounds.size;
        
        UIActivityIndicatorView *waitingActivity = [[UIActivityIndicatorView alloc]initWithFrame:CGRectMake(0, 0, 100, 100)];
        [waitingActivity setCenter:CGPointMake(winSize.width * 0.5f, winSize.height * 0.5f)];
        [waitingActivity setActivityIndicatorViewStyle:UIActivityIndicatorViewStyleWhiteLarge];
        [pApp.window.rootViewController.view addSubview:waitingActivity];
        [waitingActivity startAnimating];
        
        [storeVC loadProductWithParameters:dic completionBlock:^(BOOL result, NSError *err){
            if (err) {
                NSLog(@"err = %@",err.description);
            }
            if (result) {
                [pApp.viewController presentViewController:storeVC animated:YES completion:nil];
                [waitingActivity stopAnimating];
            }
        }];

    }
    else{
        //NSString *str = [NSString stringWithFormat:@"itms-apps://itunes.apple.com/app/id%d?mt=8", 665791418];
		 NSString *str = [NSString stringWithFormat:@"itms-apps://itunes.apple.com/app/id%@?mt=8", appid]; 
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:str]];
    }
}

void comPlatform::shakeBegin()
{
    AppController *app = [AppController shareAppController];
    [app shakeBeginCalled];
}
void comPlatform::shakePause()
{
    AppController *app = [AppController shareAppController];
    [app shakePauseCalled];
}
void comPlatform::shakeRestart()
{
    AppController *app = [AppController shareAppController];
    [app shakeReStartCalled];
}
void comPlatform::shakeEnd()
{
    AppController *app = [AppController shareAppController];
    [app shakeEndCalled];
}

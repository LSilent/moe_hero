//
//  appleStoreRequest.h
//  DotaClient
//
//  Created by hulu on 13-6-26.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>
#import "DMBProgressHUD.h"



@interface appleStoreRequest : NSObject <SKProductsRequestDelegate , SKPaymentTransactionObserver ,UIAlertViewDelegate>
{
    DMBProgressHUD *_progressView;
   
}

@property(nonatomic,retain) NSString *_productID;

+ (id)shareAppleStoreRequest;
- (id)init;
- (void)queryProductInfo;
- (void)payProduct:(NSString *)productID;
- (void)hideHUDView:(BOOL)flag isResult:(BOOL)result;
- (NSString *)encodeToPercentEscapeString: (NSString *) input;




class FinshedPaymentTransaction
{
public:
    static void finish();
    static  SKPaymentTransaction *m_cur_transaction;
    
};


@end



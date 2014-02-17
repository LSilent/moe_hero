//
//  appleStoreRequest.m
//  DotaClient
//
//  Created by hulu on 13-6-26.
//
//

#import "appleStoreRequest.h"
#import "AppController.h"


#include "network/HttpClient.h"
#include "appStorePurchase.h"

@implementation appleStoreRequest

@synthesize _productID;

+ (id)shareAppleStoreRequest
{
    static appleStoreRequest * _instance = nil;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _instance = [[appleStoreRequest alloc] init];
    });
    return _instance;
}


- (void)dealloc
{
    [super dealloc];
    
    [_progressView release];
    [_productID release];
}

- (void)queryProductInfo
{
    if ([SKPaymentQueue canMakePayments])
    {
        //获取所有的产品信息，需要所有的product id
        NSArray *arrays = [NSArray arrayWithObjects:@"com.hulu.dota.product1",@"com.hulu.dota.iap.1",nil];
        NSSet *productSet = [NSSet setWithArray:arrays];
        SKProductsRequest *productRequest = [[[SKProductsRequest alloc] initWithProductIdentifiers:productSet] autorelease];
        productRequest.delegate = self;
        [productRequest start];
    }
    
}

- (id)init
{
    self = [super init];
    if (self) {
        
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        
        UIWindow *aWindow = [[UIApplication sharedApplication] keyWindow];
        _progressView = [[DMBProgressHUD alloc] initWithWindow:aWindow];
        [aWindow addSubview:_progressView];
        
    }
    return self;
}

- (void)hideHUDView:(BOOL)flag isResult:(BOOL)result
{
    
    _progressView.labelText = @"";
    [_progressView hide:flag];
    
    if (result)
    {
        UIAlertView *alertSuccess = [[UIAlertView alloc] initWithTitle:nil message:@"购买成功"
                                                              delegate:self
                                                     cancelButtonTitle:nil
                                                     otherButtonTitles:@"确定", nil];
        [alertSuccess show];
        [alertSuccess release];
    }
    else
    {
        UIAlertView *alertSuccess = [[UIAlertView alloc] initWithTitle:nil message:@"购买失败"
                                                              delegate:self
                                                     cancelButtonTitle:nil
                                                     otherButtonTitles:@"确定", nil];
        [alertSuccess show];
        [alertSuccess release];
    }
}

- (void)payProduct:(NSString *)productID
{
    if ([SKPaymentQueue canMakePayments])
    {
        //TODO
        _productID = productID;
        
        SKPayment *payment = [SKPayment paymentWithProductIdentifier:productID];
        [[SKPaymentQueue defaultQueue] addPayment:payment];
        
        _progressView.labelText = @"正在验证中,请稍侯...";
        [_progressView show:YES];
        
    }
    else
    {
        //不允许内购
        NSLog(@"不允许购买");
    }
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response
{
    NSArray *productArray = response.products;
    if (productArray.count == 0)
    {
        //获取产品列表失败
        NSLog(@"没有产品列表");
    }
    else
    {
        //TODO
        for (SKProduct *skPro in productArray)
        {
            NSLog(@"id:%@ price:%@",skPro.productIdentifier,skPro.price);
        }
        
        /*SKProduct *pro = [productArray objectAtIndex:0];
        SKPayment *payment = [SKPayment paymentWithProductIdentifier:pro.productIdentifier];
        [[SKPaymentQueue defaultQueue] addPayment:payment];*/
        
    }
}


- (NSString *)encodeToPercentEscapeString: (NSString *) input
{

    NSString *outputStr = (NSString *)
    CFURLCreateStringByAddingPercentEscapes(kCFAllocatorDefault,
                                            (CFStringRef)input,
                                            NULL,
                                            (CFStringRef)@"!*'();:@&=+$,/?%#[]",
                                            kCFStringEncodingUTF8);
    return outputStr;
}


 

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
    for(SKPaymentTransaction *transaction in transactions)
    {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
            {
                //NSString *productId = transaction.payment.productIdentifier;
                
                NSLog(@"app store 购买成功");
                
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];//成功后调用
                
                NSString *temptransactionReceipt  = [[[NSString alloc] initWithData:[transaction transactionReceipt] encoding:NSUTF8StringEncoding] autorelease];
                const char *resultReceipt = [[self encodeToPercentEscapeString:temptransactionReceipt] UTF8String];
                
                //NSLog(@"receipt : %@" , temptransactionReceipt);
                FinshedPaymentTransaction::m_cur_transaction = transaction;
                appStorePurchase::completeBuyProduct(resultReceipt);
                
                break;
            }
            case SKPaymentTransactionStateFailed:
            {
                NSLog(@"购买失败 %d" , transaction.error.code);
                
              
               /* std::string s = "购买失败";
                switch(transaction.error.code)
                {
                    case SKErrorUnknown:
                    {
                        s = "购买失败，出错原因为：";
                        
                        NSString  * nsfaceName=transaction.error.localizedDescription;
                        std::string   strFaceName=  [nsfaceName UTF8String];
                        s.append(strFaceName);

                        
                        // 无法连接iTunes Store”。
                    }
                        break;
                    case SKErrorClientInvalid:
                        s = "购买失败（客户端验证错误）";
                        break;
                    case SKErrorPaymentInvalid:
                        s = "购买失败（支付验证错误）";
                        break;
                    case SKErrorPaymentNotAllowed:
                        s = "购买失败（不允许支付）";
                        break;
                    case SKErrorPaymentCancelled:
                        s = "取消购买";
                        break;
                    case SKErrorStoreProductNotAvailable:
                        s = "购买失败（产品无效）";
                        break;
                        
                }
           
             NSString *errorMessage = [NSString stringWithCString:s.c_str() encoding:NSUTF8StringEncoding]; */
                NSString *errorMessage = transaction.error.localizedDescription;
               // NSString *errorReason= transaction.error.localizedFailureReason;
                NSLog(@"购买失败 %s" , errorMessage);

                if (transaction.error.code != SKErrorPaymentCancelled)
                {
                    // NSLog(@"Transaction error: %@", errorMessage,errorReason);
                    //内购失败
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:errorMessage delegate:nil cancelButtonTitle:nil otherButtonTitles:@"确定", nil];
                    [alert show];
                    [alert release];
                }
                else
                {
                    //
                }
                
                [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                
                _progressView.labelText = @"";
                [_progressView hide:YES];
                
                
                break;
            }
            case SKPaymentTransactionStateRestored:
            {
            
               [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
                
                _progressView.labelText = @"";
                [_progressView hide:YES];
                
                break;
            }
            case SKPaymentTransactionStatePurchasing:
            {
                NSLog(@"购买中......");
                
                _progressView.labelText = @"";
                [_progressView hide:YES];
                
                break;
            }
            default:
                break;
        }
        
       // [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
    
    
}

SKPaymentTransaction * FinshedPaymentTransaction::m_cur_transaction = 0;

void FinshedPaymentTransaction::finish()
{
     [[SKPaymentQueue defaultQueue] finishTransaction:m_cur_transaction];//成功后调用
}

@end






















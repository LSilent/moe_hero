//
//  appStorePurchase.m
//  DotaClient
//
//  Created by hulu on 13-6-28.
//
//

#include "appStorePurchase.h"

#import "appleStoreRequest.h"
#include "cocos2d.h"
#include "./datapool/loginData.h"
#include "./datapool/DataPool.h"
#include "./Game.h"
#include "./base/UtilTools.h"
#include "./database/DataBaseSystem.h"
#include "./base/nuts.h"
USING_NS_CC;

static httpIAP pHttpIap;

void appStorePurchase::startBuyProductWithID(std::string productID)
{
    [[appleStoreRequest shareAppleStoreRequest] payProduct:[NSString stringWithUTF8String:productID.c_str()]];
    
}


void appStorePurchase::getProductListInfo()
{
    [[appleStoreRequest shareAppleStoreRequest] queryProductInfo];
}

void appStorePurchase::completeBuyProduct(const char *cSign)
{
   // m_cur_transaction = transaction;
    //http://61.160.249.5/php/deliver.php?billno=888888&userid=test123&zone=1&sign=0G4%2F2zwBkuc%2"
    
    cocos2d::extension::CCHttpClient *pcleint = cocos2d::extension::CCHttpClient::getInstance();
	cocos2d::extension::CCHttpRequest *req = new cocos2d::extension::CCHttpRequest();
    string userid = DataPool::GetSingleton()->getLoginData()->getUserId();
        
     
    std::string url = Game::getAppChargeUrl();
    
    url += nuts::sm_billno+std::string("&userid=")+userid+std::string("&zone=")+nuts::sm_zone+std::string("&sign=")+std::string(cSign);
    
	//std::string url = "http://61.160.251.62/apple/deliver.php?billno="+nuts::sm_billno+std::string("&userid=")+userid+std::string("&zone=")+nuts::sm_zone+std::string("&sign=")+std::string(cSign);
    //std::string url = "http://61.160.251.62/apple/deliver.php";
    CCLog("%s",url.c_str());
	req->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
    
//    req->setRequestData(nuts::sm_billno.c_str(), strlen(nuts::sm_billno.c_str()));
//    req->setRequestData(userid.c_str(), strlen(userid.c_str()));
//    req->setRequestData(nuts::sm_zone.c_str(), strlen(nuts::sm_zone.c_str()));
//    req->setRequestData(cSign, strlen(cSign));
    
	req->setUrl(url.c_str());
	req->setTag("valite_sign");
	req->setResponseCallback(&pHttpIap,(cocos2d::SEL_CallFuncND)&httpIAP::CallFuncND);
	pcleint->send(req);
	req->release();
}

void httpIAP::CallFuncND(cocos2d::CCNode* pNode, void* pargv)
{
	cocos2d::extension::CCHttpResponse *response = (cocos2d::extension::CCHttpResponse*)pargv;
	if(!response->isSucceed())
	{
        
	}
    
	std::vector<char> *data = response->getResponseData();
	int vectorLength = data->size();
	if(vectorLength <= 0)
	{
        cocos2d::CCLog("服务器没返回数据");
        
        [[appleStoreRequest shareAppleStoreRequest] hideHUDView:YES isResult:NO];
        
		return;
	}
    
    const char* tag = response->getHttpRequest()->getTag();

    if(0 == strcmp(tag, "valite_sign"))
	{
        
        std::string recieveData;
        for(int i=0;i<vectorLength;i++)
        {
            recieveData += (*data)[i];
        }
        CCLog("result(%d) : %s",vectorLength,recieveData.c_str());
        
        if (recieveData == "0")//成功
        {
            [[appleStoreRequest shareAppleStoreRequest] hideHUDView:YES isResult:YES];
           // FinshedPaymentTransaction::finish();
        }
        else
        {
            [[appleStoreRequest shareAppleStoreRequest] hideHUDView:YES isResult:NO];
            
            if (recieveData == "-6")//发货失败 或者成功 都要结束交易
            {
                //FinshedPaymentTransaction::finish();
            }
            else if (recieveData == "-5")//账号更新失败
            {
                
            }
            else if (recieveData == "-4")//宝石更新失败
            {
                
            }
            else if (recieveData == "-3")//账单号错误
            {
                
            }
            else if (recieveData == "-2")//宝石数错误
            {
                
            }
            else if (recieveData == "-1")//-1：访问苹果失败
            {
                
            }

        }
    }
    
   
    
    
    
    
}


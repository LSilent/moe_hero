//
//  appStorePurchase.h
//  DotaClient
//
//  Created by hulu on 13-6-28.
//
//
#ifndef __appStorePurchase__
#define __appStorePurchase__

#include "string"
#include "cocos-ext.h"

using namespace std;

class appStorePurchase
{
public:
    static void startBuyProductWithID(std::string productID);
    static void getProductListInfo();
    static void completeBuyProduct(const char *cSign);
    
};

class  httpIAP :public cocos2d::CCObject
{
public:
    
	void CallFuncND(cocos2d::CCNode*, void*);
private:
    
};

#endif
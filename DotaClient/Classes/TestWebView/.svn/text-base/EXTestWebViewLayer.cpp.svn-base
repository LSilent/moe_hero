//
//  EXTestWebViewLayer.cpp
//  Cocos2dxExt
//
//  Created by LiuYanghui on 13-8-1.
//
//

#include "EXTestWebViewLayer.h"
#include "EXWebViewLayer.h"
#include "./datapool/loginData.h"
#include "./datapool/DataPool.h"
#include "./Game.h"
#include "./base/UtilTools.h"
#include "./database/DataBaseSystem.h"
#include "cocos2d.h"

EXTestWebViewLayer::EXTestWebViewLayer()
{
    
}

EXTestWebViewLayer::~EXTestWebViewLayer()
{
    
}

bool EXTestWebViewLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    initData();
    return true;
}

void EXTestWebViewLayer::initData()
{
    return;
    const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(Game::sm_SelectServer);
    
    std::string url = "http://" + string(m_pTableData->upDataIp)  + string("/dota/server") +UtilTools::IntToString( m_pTableData->id);
    
    url +="/notice/index.html";
    cocos2d::CCLog(url.c_str());
    

    
    EXWebViewLayer* web = EXWebViewLayer::create(url.c_str());
    web->setPosition(CCPointZero);
    addChild(web);
}
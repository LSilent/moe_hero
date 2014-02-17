#include "mainNavgView.h"
#include "../../Game.h"

#include "./event/EventSystem.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "cocos-ext.h"
#include "./sound/SoundSystem.h"
#include "../Wood/CGWoodAskPacket.h"
#include "./DataBase/DataBaseSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectManager.h"
#include "./object/ObjectSelf.h"

using namespace cocos2d;
USING_NS_CC_EXT;


MainNavgView::MainNavgView()
{
	 
}

MainNavgView::~MainNavgView()
{
     
}


void MainNavgView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   /* CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);*/

	 
}

void MainNavgView::onNavg1(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MAINPAGE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND1);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainNavgView::onNavg2(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_SHOW);
 	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainNavgView::onNavg3(cocos2d::CCObject * pSender)
{
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_HUODONG_OPEN_LEVEL);
	if (pTableData)
	{
		if( DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetLevel() < pTableData->m_value)
		{

			X_CHAR temp[256] ={0};
			sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(709),pTableData->m_value);
			vector<string> strV;strV.clear();
			strV.push_back(temp);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			return;
		}

	}

	SendLogicPacket::AskHuoDong();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHEESE_SHOW);

 	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainNavgView::onNavg4(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);

 	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MainNavgView::onNavg5(cocos2d::CCObject * pSender)
{
 
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_WOOD_OPEN_LEVEL);
	if (pTableData)
	{
		 if( DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetLevel() < pTableData->m_value)
		 {

			 X_CHAR temp[256] ={0};
			 sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(682),pTableData->m_value);
			 vector<string> strV;strV.clear();
			 strV.push_back(temp);
		     EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			 return;
		 }
		 
	}
  
	SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_ENTER);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_SHOW);

	return;
	vector<string> v_Str;
	v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(586));
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,v_Str);
	return;
}

void MainNavgView::onNavg6(cocos2d::CCObject * pSender)
{
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_RANKLIST_OPEN_LEVEL);
	if (pTableData)
	{
		if( DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetLevel() < pTableData->m_value)
		{

			X_CHAR temp[256] ={0};
			sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(708),pTableData->m_value);
			vector<string> strV;strV.clear();
			strV.push_back(temp);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			return;
		}

	}

	SendLogicPacket::EnterArena();
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RANKLIST_SHOW);

 	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


SEL_MenuHandler MainNavgView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg1", MainNavgView::onNavg1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg2", MainNavgView::onNavg2);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg3", MainNavgView::onNavg3);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg4", MainNavgView::onNavg4);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg5", MainNavgView::onNavg5);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onNavg6", MainNavgView::onNavg6);

    return NULL;   
}

SEL_CCControlHandler MainNavgView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;
}

bool MainNavgView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    return false;
}

bool MainNavgView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool MainNavgView::init()
{
    bool bRet = true;

   

    return bRet;
}


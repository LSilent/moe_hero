
#include "./ui/userInfoUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "./ui/element/CCMenuEx.h"
#include "./datapool/SportsData.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)




userInfoUIView::userInfoUIView()
: mUserName(NULL)
, mUserLvl(NULL)
, mUserExp(NULL)
, mUserHero(NULL)
, mUserGem(NULL)
, mUserCoin(NULL)
, mUserWood(NULL)
, mUserRank(NULL)
, mUserAct(NULL)
, mUserActTime(NULL)
, mUserAllActTime(NULL)
{

}

userInfoUIView::~userInfoUIView()
{
	CC_SAFE_RELEASE(mUserName);
	CC_SAFE_RELEASE(mUserLvl);
	CC_SAFE_RELEASE(mUserExp);
	CC_SAFE_RELEASE(mUserHero);
	CC_SAFE_RELEASE(mUserGem);
	CC_SAFE_RELEASE(mUserCoin);
	CC_SAFE_RELEASE(mUserWood);
	CC_SAFE_RELEASE(mUserRank);
	CC_SAFE_RELEASE(mUserAct);
	CC_SAFE_RELEASE(mUserActTime);
	CC_SAFE_RELEASE(mUserAllActTime);

}

void userInfoUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler userInfoUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", userInfoUIView::onButtonClose);
	
	return NULL;    
}

SEL_CCControlHandler userInfoUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	


// 	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonCancel", userInfoUIView::onButtonCancel);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonOK", userInfoUIView::onButtonOK);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonPur", userInfoUIView::onButtonPur);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onButtonGift", userInfoUIView::onButtonGift);
	return NULL;
}



// void userInfoUIView::onButtonCancel(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
// {
// 	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_CLOSE);
// }


void userInfoUIView::onButtonOK(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_USER_INFO_CLOSE);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SETTING_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}
void userInfoUIView::onButtonGift(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	GiftExchangeView *dialogPur_ = GiftExchangeView::createDialog(this);
	dialogPur_->setTag(1002);
	addChild(dialogPur_,10);
}


void userInfoUIView::onButtonPur(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	char buffer[512] = {0};
	X_INT buyNum = -1;
	X_INT level = -1;
	X_INT money =-1;
	if (DataPool::GetSingleton())
	{
		ObjectManager* pM = DataPool::GetSingleton()->getObjectManager();
		if (!pM)return;
		ObjectSelf* pSelf = pM->getSelf();
		if (!pSelf)return;

		PlayerData*  pData =  pSelf->playerData();
		if (!pData)return;
		buyNum = pData->GetBuyAcNum();
		level = pData->GetLevel();
		money = pData->GetGold();
	}
	if (buyNum >=ActionPointBuyNum)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG( 587);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		}
		return;
	}
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_BUYACTIONPOINT);
	if (!pDataFile)return;
	const stDBC_FILE_BUYACTIONPOINT	* m_pTableData =(const stDBC_FILE_BUYACTIONPOINT*)pDataFile->GetFieldsByIndexKey(buyNum+1);
	if (!m_pTableData)return;

	if (level<m_pTableData->level)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG( 588);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		}
		return;
	}
	if (money < m_pTableData->cost)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(102);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		}
		return;
	}
	 
	sprintf(buffer,UtilTools::GET_TEXT_FROM_LANG(543),m_pTableData->cost,m_pTableData->addAction);
	ModalDialogView *dialogPur = ModalDialogView::createDialog( buffer,this);
	dialogPur->setTag(1000);
	addChild(dialogPur,10);
}

void userInfoUIView::buyAction()
{
	char buffer[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffer,UtilTools::GET_TEXT_FROM_LANG(595));
	ModalDialogView *dialogPur = ModalDialogView::createDialog( buffer,this);
	dialogPur->setTag(1001);
	addChild(dialogPur,10);
}
void userInfoUIView::rankLevelUpdata()
{
	SportsData *pSportData = DataPool::GetSingleton()->getSportsData();
	X_INT rank = pSportData->GetRank();
	string rankInfo;
	if (rank == -1)
	{
		mUserRank->setString(UtilTools::GET_TEXT_FROM_LANG(542));
	}else
	{
		mUserRank->setString(UtilTools::IntToString(rank).c_str());
	}
}
void userInfoUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_USER_INFO_CLOSE);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool userInfoUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   

	// cocos2d::CCLabelTTF* mUserName;
	// cocos2d::CCLabelTTF* mUserLvl;
	// cocos2d::CCLabelTTF* mUserExp;
	// cocos2d::CCLabelTTF* mUserHero;
	// cocos2d::CCLabelTTF* mUserCoin;
	// cocos2d::CCLabelTTF* mUserRank;
	// cocos2d::CCLabelTTF* mUserAct;
	// cocos2d::CCLabelTTF* mUserActTime;
	// cocos2d::CCLabelTTF* mUserAllActTime;



	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserName", CCLabelTTF *,mUserName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserLvl", CCLabelTTF *,mUserLvl);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserExp", CCLabelTTF *, mUserExp);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserHero", CCLabelTTF *, mUserHero);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserGem", CCLabelTTF *, mUserGem);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserCoin", CCLabelTTF *, mUserCoin);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserWood", CCLabelTTF *, mUserWood);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserRank", CCLabelTTF *, mUserRank);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserAct", CCLabelTTF *, mUserAct);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserActTime", CCLabelTTF *, mUserActTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserAllActTime", CCLabelTTF *, mUserAllActTime);


    return false;
}

bool userInfoUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool userInfoUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

void userInfoUIView::onDataUpdate( bool isDataValid )
{	
	
	if( !isDataValid )
	{
		//clear();

		return;
	}

	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();

	mUserName->setString(pData->getName().c_str());
	mUserLvl->setString(UtilTools::IntToString(pData->GetLevel()).c_str());
	mUserExp->setString(UtilTools::IntToString(pData->GetExp()).c_str());
	string strHero;
	strHero = UtilTools::IntToString(pData->GetMatrixHeroNum()).c_str();
	strHero +="/5";
	mUserHero->setString(strHero.c_str());

	mUserGem->setString(UtilTools::IntToString(pData->GetGem()).c_str());
	mUserCoin->setString(UtilTools::IntToString(pData->GetGold()).c_str());
	mUserWood->setString(UtilTools::IntToString(pData->GetWood()).c_str());

	SportsData *pSportData = DataPool::GetSingleton()->getSportsData();

	X_INT rank = pSportData->GetRank();
	string rankInfo;
	if (rank == -1)
	{
		SendLogicPacket::EnterArena();
		mUserRank->setString(UtilTools::GET_TEXT_FROM_LANG(542));
	}else
	{
		 mUserRank->setString(UtilTools::IntToString(rank).c_str());
	}
 
	string strAct;
	strAct = UtilTools::IntToString(pData->GetActionPoint());
	strAct+="/";
	strAct+=UtilTools::IntToString(pData->GetMaxActionPoint());
	mUserAct->setString(strAct.c_str());

// 	string strTime = UtilTools::ConvertMillisecondToTimeString( pData->GetActionPoint() * 1000 );
// 	mUserActTime->setString(strTime.c_str());
// 
// 	string strAllTime = UtilTools::ConvertMillisecondToTimeString( pData->GetActionPoint() * 1000 );
// 	mUserActTime->setString(strAllTime.c_str());


}

void userInfoUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

	if (pSender->getTag() == 1000)
	{
		SendLogicPacket::BuyActionPoint();
	}
	else if(pSender->getTag() == 1001)
	{
		EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
	}
	else if(pSender->getTag() == 1002)
	{
		  SendLogicPacket::GetGiftPackCard(1,static_cast<GiftExchangeView*>(pSender)->getText());
	}
 
	pSender->closeDialogView();
}


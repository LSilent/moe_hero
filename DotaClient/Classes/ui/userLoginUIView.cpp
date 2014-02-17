
#include "./ui/userLoginUIView.h"
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
#include "./base/nuts.h"
#include "./net/NetworkSystem.h"
#include "./datapool/loginData.h"
#include "./datapool/SettingData.h"
#include "./ui/loginView.h"
//#include <regex>

#define LOGINFIELD_WIDTH 583
#define LOGINFIELD_HEIGHT 335
#define REGISTERFIELD_HEIGHT 428

#define REGISTER_EDITBOX_START_X 210
#define REGISTER_EDITBOX_START_Y 110
#define REGISTER_EDITBOX_DELAY_Y 82

#define LOGIN_EDITBOX_START_X 185
#define LOGIN_EDITBOX_START_Y 103
#define LOGIN_EDITBOX_DELAY_Y 82

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)


userLoginUIView::userLoginUIView()
: mCheckPwd(NULL)
//, mCheckLogin(NULL)
, mLoginNode(NULL)
, mRegisterNode(NULL)
, mBackNode(NULL)
, pRegEmail(NULL)
, pRegPwd1(NULL)
, pRegPwd2(NULL)
, pLoginEmail(NULL)
, pLoginPwd(NULL)
, m_pRegister(NULL)
, m_pEnter(NULL)
{
	isRegFromLogin = false;
}

userLoginUIView::~userLoginUIView()
{
	CC_SAFE_RELEASE(mCheckPwd);
//	CC_SAFE_RELEASE(mCheckLogin);
	CC_SAFE_RELEASE(mLoginNode);
	CC_SAFE_RELEASE(mRegisterNode);
	CC_SAFE_RELEASE(mBackNode);
}

void userLoginUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler userLoginUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonReturn", userLoginUIView::onButtonReturn);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonLogin", userLoginUIView::onButtonLogin);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRememberPwd", userLoginUIView::onButtonRememberPwd);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAutoLogin", userLoginUIView::onButtonAutoLogin);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRegister", userLoginUIView::onButtonRegister);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonReg", userLoginUIView::onButtonReg);


	return NULL;    
}
 
SEL_CCControlHandler userLoginUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
 
	return NULL;
}

void userLoginUIView::registerResult(bool flag)
{
	if (flag)
	{
		nuts::loginCallBack();
	}
	
}


void userLoginUIView::onButtonReturn(cocos2d::CCObject * pSender)
{
	if(mRegisterNode->isVisible())
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCAction* registerAction = CCSequence::create(CCPlace::create(CCPointMake(winSize.width * 0.5f, winSize.height * 0.5f)), 
			CCMoveTo::create(0.1f, CCPointMake(winSize.width * 1.5f, winSize.height * 0.5f)),NULL);
		mRegisterNode->runAction( registerAction );

		this->onDataUpdate();
		

		CCAction* loginAction = CCSequence::create(CCPlace::create(CCPointMake(winSize.width * -0.5f, winSize.height * 0.5f)), 
			CCMoveTo::create(0.2f, CCPointMake(winSize.width * 0.5f, winSize.height * 0.5f)),  NULL);
		mLoginNode->runAction( loginAction );
		
	}
	else
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVNET_USER_LOGIN_CLOSE);
	}
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void userLoginUIView::onButtonLogin(cocos2d::CCObject * pSender)
{
	//nuts::loginCallBack();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	if (pDataFile)
	{
		const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(Game::sm_SelectServer);
		if (m_pTableData && (m_pTableData->states == SRV_ZONE_STATE_STOP))
		{

			vector<string> strV;strV.clear();
			strV.push_back(UtilTools::GET_TEXT_FROM_LANG(710));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
			return;
		}
	}


	if(NetworkSystem::GetSingleton()->GetNetworkState()== NetworkSystem::NET_CONNECTING_STATE)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(589));
		strV.push_back("1");
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
	if (!checkValite())
	{
		return;
	}

	nuts::checkAndEnter = true;
	nuts::checkUserAccount(pLoginEmail->getText(),pLoginPwd->getText());
	if (m_pEnter)
	{
		m_pEnter->setEnabled(false);
		m_pEnter->setColor(ccGRAY);
	}
	this->scheduleOnce(schedule_selector(userLoginUIView::EnableEnter),5);
	 
}
void userLoginUIView::EnableRegister(float dt)
{
	if (m_pRegister)
	{
		m_pRegister->setEnabled(true);
	}
}
void userLoginUIView::EnableEnter(float dt)
{
	if (m_pEnter)
	{
		m_pEnter->setEnabled(true);
		m_pEnter->setColor(ccWHITE);
	}
	
}

void userLoginUIView::onButtonRememberPwd(cocos2d::CCObject * pSender)
{
// 	if (mCheckLogin->isVisible())
// 	{
// 		return;
// 	}
	
//     mCheckPwd->setVisible(!mCheckPwd->isVisible());
// 
// 	SettingData::Set(SettingData::SAVE_PASSWORD , mCheckPwd->isVisible());
// 	SettingData::Set(SettingData::AUTO_LOGIN , mCheckPwd->isVisible());
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
}
void userLoginUIView::onButtonAutoLogin(cocos2d::CCObject * pSender)
{
//     mCheckLogin->setVisible(!mCheckLogin->isVisible());
// 
// 	if (mCheckLogin->isVisible())
// 	{
// 		mCheckPwd->setVisible(true);
// 		SettingData::Set(SettingData::SAVE_PASSWORD ,true);
// 	}
// 	
// 
// 	SettingData::Set(SettingData::AUTO_LOGIN , mCheckLogin->isVisible());
// 
// 	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
}

void userLoginUIView::onButtonRegister(cocos2d::CCObject * pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	if (!checkValite())
	{ 
		return;
	}
	nuts::regeditDown(pRegEmail->getText(),pRegPwd1->getText()) ;
	if (m_pRegister)
	{
			m_pRegister->setEnabled(false);
	}
 
	scheduleOnce(schedule_selector(userLoginUIView::EnableRegister),3);
}

void userLoginUIView::onButtonReg(cocos2d::CCObject * pSender)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCAction* loginAction = CCSequence::create(CCPlace::create(CCPointMake(winSize.width * 0.5f, winSize.height * 0.5f)), 
		CCMoveTo::create(0.1f, CCPointMake(winSize.width * - 0.5f, winSize.height * 0.5f)), 
		CCCallFunc::create(this,callfunc_selector(userLoginUIView::loadRegisterNode)) ,NULL);
	mLoginNode->runAction( loginAction );

	//loadRegisterNode();

	isRegFromLogin = true;
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

bool userLoginUIView::checkValite()
{
	vector<string> v_Str;

	string mailCount = SettingData::GetLoaclUserAccount();
//	if (mailCount.size()>0 && !isRegFromLogin)
    if (!isRegFromLogin)
	{
		//login

		if (strlen(pLoginEmail->getText()) == 0)
		{
			v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(605));
		}
		else if (strlen(pLoginPwd->getText()) == 0)
		{
			v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(607));
		}
		else
		{
			//const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
			//if (!std::regex_match(pLoginEmail->getText(), pattern))
            if(!UtilTools::isvalidAccount(pLoginEmail->getText()))
			{
				v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(606));
			}
			else if ((strlen(pLoginPwd->getText()) <6 || strlen(pLoginPwd->getText())> 20))
			{
				v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(608));
			}
		}
	}
	else
	{
		//register
		if (strlen(pRegEmail->getText()) == 0)
		{
			v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(605));

		}
		else if (strlen(pRegPwd1->getText()) == 0 || strlen(pRegPwd2->getText()) == 0)
		{
			v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(607));
		}
		else 
		{
			//const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
			//if (!std::regex_match(pRegEmail->getText(), pattern))
            if(!UtilTools::isvalidAccount(pRegEmail->getText()))
			{
				v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(606));
			}
			else if ((strlen(pRegPwd1->getText()) <6 || strlen(pRegPwd1->getText())> 20) || (strlen(pRegPwd2->getText()) <6 || strlen(pRegPwd2->getText())> 20))
			{
				v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(608));
			}
			else if (string(pRegPwd1->getText()) != string(pRegPwd2->getText()))
			{
				v_Str.push_back(UtilTools::GET_TEXT_FROM_LANG(609));
			}
			
		}

		
	}
	
	if (!v_Str.empty())
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,v_Str);

		return false;
	}


	return true;
	
}

bool userLoginUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCheckPwd", CCSprite *,mCheckPwd);
//	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mCheckLogin", CCSprite *,mCheckLogin);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBackNode", CCSprite *,mBackNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLoginNode", CCNode *,mLoginNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRegisterNode", CCNode *,mRegisterNode);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mRegister", CCMenuItem *, m_pRegister);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mEnter", CCMenuItem *, m_pEnter);
    return false;
}

bool userLoginUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool userLoginUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

void userLoginUIView::onDataUpdate( bool isDataValid )
{	
	
	if( !isDataValid )
	{
		return;
	}

	loadLoginNode();

}

void userLoginUIView::loadLoginNode()
{
	if (pLoginEmail)
	{
		pLoginEmail->removeFromParentAndCleanup(true);
		pLoginEmail = NULL;
	}

	if (pLoginPwd)
	{
		pLoginPwd->removeFromParentAndCleanup(true);
		pLoginPwd = NULL;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	string mailCount = SettingData::GetLoaclUserAccount();

	string password = "";
	string userName = "";

	password = SettingData::GetLoaclUserPassword();

	userName = mailCount;
	mRegisterNode->setVisible(false);
	mLoginNode->setVisible(true);
	mLoginNode->setPosition(mBackNode->getPosition());

	CCPoint loginFirstPos = ccp((winSize.width - LOGINFIELD_WIDTH) * 0.5f + LOGIN_EDITBOX_START_X, winSize.height * 0.454 + LOGINFIELD_HEIGHT * 0.5f - LOGIN_EDITBOX_START_Y);


	pLoginEmail = CCEditBox::create(CCSizeMake(winSize.width * 0.73f, winSize.height * 0.06f), CCScale9Sprite::create("n_op_0.png"));
	pLoginEmail->setReturnType(kKeyboardReturnTypeDone);
	pLoginEmail->setPosition(loginFirstPos);
	pLoginEmail->setAnchorPoint(ccp(0, 0.5f));
	pLoginEmail->setDelegate(this);
	pLoginEmail->setFontColor(ccWHITE);
	mLoginNode->addChild(pLoginEmail,50);

	pLoginEmail->setText(userName.c_str());

	pLoginPwd = CCEditBox::create(CCSizeMake(winSize.width * 0.73f, winSize.height * 0.06f), CCScale9Sprite::create("n_op_0.png"));
	pLoginPwd->setReturnType(kKeyboardReturnTypeDone);
	pLoginPwd->setPosition(ccpSub(loginFirstPos,ccp(0, LOGIN_EDITBOX_DELAY_Y)));
	pLoginPwd->setAnchorPoint(ccp(0, 0.5f));
	pLoginPwd->setDelegate(this);
	pLoginPwd->setFontColor(ccWHITE);
	pLoginPwd->setMaxLength(20);
	pLoginPwd->setInputFlag(kEditBoxInputFlagPassword);
	mLoginNode->addChild(pLoginPwd,51);

	pLoginPwd->setText(password.c_str());

//	bool sPwd = SettingData::Get(SettingData::SAVE_PASSWORD);
//	bool sAuto = SettingData::Get(SettingData::AUTO_LOGIN);

//	mCheckPwd->setVisible(sPwd);
//	mCheckLogin->setVisible(sAuto);
	m_pRegister->setEnabled(true);
	m_pEnter->setEnabled(true);
}

void userLoginUIView::loadRegisterNode()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCAction* registerAction = CCSequence::create(CCPlace::create(CCPointMake(winSize.width * 1.5f, winSize.height * 0.5f)), 
		CCMoveTo::create(0.2f, CCPointMake(winSize.width *  0.5f, winSize.height * 0.5f)), NULL);
	mRegisterNode->runAction( registerAction );
	if (pRegEmail)
	{
		pRegEmail->removeFromParentAndCleanup(true);
		pRegEmail = NULL;
	}

	if (pRegPwd1)
	{
		pRegPwd1->removeFromParentAndCleanup(true);
		pRegPwd1 = NULL;
	}

	if (pRegPwd2)
	{
		pRegPwd2->removeFromParentAndCleanup(true);
		pRegPwd2 = NULL;
	}


	CCPoint regFirstPos = ccp((winSize.width - LOGINFIELD_WIDTH) * 0.5f + REGISTER_EDITBOX_START_X, winSize.height * 0.629 + REGISTERFIELD_HEIGHT * 0.5f - REGISTER_EDITBOX_START_Y);

	mRegisterNode->setVisible(true);
	mLoginNode->setVisible(false);
	mRegisterNode->setPosition(mBackNode->getPosition());

	pRegEmail = CCEditBox::create(CCSizeMake(winSize.width * 0.73f, winSize.height * 0.06f), CCScale9Sprite::create("n_op_0.png"));
	pRegEmail->setReturnType(kKeyboardReturnTypeDone);
	pRegEmail->setAnchorPoint(ccp(0, 0.5f));
	pRegEmail->setPosition(regFirstPos);
	pRegEmail->setDelegate(this);
	pRegEmail->setFontColor(ccWHITE);
	pRegEmail->setPlaceHolder(UtilTools::GET_TEXT_FROM_LANG(724));
	pRegEmail->setPlaceholderFont(FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
	mRegisterNode->addChild(pRegEmail);

	pRegPwd1 = CCEditBox::create(CCSizeMake(winSize.width * 0.73f, winSize.height * 0.06f), CCScale9Sprite::create("n_op_0.png"));
	pRegPwd1->setReturnType(kKeyboardReturnTypeDone);
	pRegPwd1->setPosition(ccpSub(regFirstPos,ccp(0, REGISTER_EDITBOX_DELAY_Y)));
	pRegPwd1->setAnchorPoint(ccp(0, 0.5f));
	pRegPwd1->setDelegate(this);
	pRegPwd1->setFontColor(ccWHITE);
	pRegPwd1->setMaxLength(20);
	pRegPwd1->setInputFlag(kEditBoxInputFlagPassword);
	pRegPwd1->setPlaceHolder(UtilTools::GET_TEXT_FROM_LANG(725));
	pRegPwd1->setPlaceholderFont(FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
	mRegisterNode->addChild(pRegPwd1);

	pRegPwd2 = CCEditBox::create(CCSizeMake(winSize.width * 0.75f, winSize.height * 0.06f), CCScale9Sprite::create("n_op_0.png"));
	pRegPwd2->setReturnType(kKeyboardReturnTypeDone);
	pRegPwd2->setPosition(ccpSub(regFirstPos,ccp(0, REGISTER_EDITBOX_DELAY_Y*2)));
	pRegPwd2->setAnchorPoint(ccp(0, 0.5f));
	pRegPwd2->setDelegate(this);
	pRegPwd2->setFontColor(ccWHITE);
	pRegPwd2->setMaxLength(20);
	pRegPwd2->setInputFlag(kEditBoxInputFlagPassword);
	pRegPwd2->setPlaceHolder(UtilTools::GET_TEXT_FROM_LANG(726));
	pRegPwd2->setPlaceholderFont(FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
	mRegisterNode->addChild(pRegPwd2);

}

void userLoginUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

	
	pSender->closeDialogView();
}

void userLoginUIView::editBoxEditingDidBegin(CCEditBox* editBox)
{

}
void userLoginUIView::editBoxEditingDidEnd(CCEditBox* editBox)
{

}

void userLoginUIView::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{

}

void userLoginUIView::editBoxReturn(CCEditBox* editBox)
{

}


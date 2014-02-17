#include "./ui/settingUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"
#include "./ui/element/mainSatusView.h"
#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/SettingData.h"
#include "./sound/SoundSystem.h"
#include "./base/Sdk_Handler.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.045f)
#define CONTENT_POS_Y            (0.260f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.555f)

#define ITEM_SPACE_DELTA_X       (0.220f)
#define ITEM_SPACE_DELTA_Y       (0.165f)

#define ITEM_START_X             (0.09f)
#define ITEM_START_Y             (0.45f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            3

SettingUIView::SettingUIView()
: mMainStatus(NULL)
//, mSettingName(NULL)
//, mSettingLvl(NULL)
//, mSettingGold(NULL)
, mSettingMusic(NULL)
, mSettingAudio(NULL)
, mSettingReconn(NULL)
, mSettingPP(NULL)
, mPPText(NULL)
, mSettingPPBtn(NULL)
{

	mContent = NULL;
    
   
}

SettingUIView::~SettingUIView()
{
	//CC_SAFE_RELEASE(mSettingName);
	//CC_SAFE_RELEASE(mSettingLvl);
	//CC_SAFE_RELEASE(mSettingGold);
	CC_SAFE_RELEASE(mSettingMusic);
	CC_SAFE_RELEASE(mSettingAudio);
	CC_SAFE_RELEASE(mSettingReconn);
    
    CC_SAFE_RELEASE(mSettingPP);
	CC_SAFE_RELEASE(mPPText);
	CC_SAFE_RELEASE(mSettingPPBtn);
	CC_SAFE_RELEASE(mMainStatus);
}


void SettingUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
#if (USE_SDK_PP_IOS ==SC_SDK)

    mSettingPP->setVisible(true);
    mPPText->setVisible(true);
    mSettingPPBtn->setVisible(true);
#elif (USE_SDK_91_IOS  == SC_SDK || USE_SDK_91_ANDROID == SC_SDK)
    mSettingPP->setVisible(true);
    mPPText->setVisible(true);
    mSettingPPBtn->setVisible(true);
    
#else 
    mSettingPP->setVisible(false);
    mPPText->setVisible(false);
    mSettingPPBtn->setVisible(false);
#endif
 
    
	onDataUpdate( false );
}


SEL_MenuHandler SettingUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSettingMusic", SettingUIView::onButtonSettingMusic);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSettingAudio", SettingUIView::onButtonSettingAudio);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSettingPPCenter", SettingUIView::onButtonSettingPPCenter);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSettingAppReConn", SettingUIView::onButtonSettingAppReConn);
	
	return NULL;    
}

SEL_CCControlHandler SettingUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool SettingUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    

    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingName", CCLabelTTF *, this->mSettingName);
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingLvl", CCLabelTTF *, this->mSettingLvl);
	
	//CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingGold", CCLabelTTF *, this->mSettingGold);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingMusic", CCSprite *, this->mSettingMusic);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingAudio", CCSprite *, this->mSettingAudio);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingReconn", CCSprite *, this->mSettingReconn);
    
    
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingPP", CCSprite *, this->mSettingPP);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPPText", CCLabelTTF *, this->mPPText);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSettingPPBtn", CCMenuItemImage *, this->mSettingPPBtn);	

	return false;
}

bool SettingUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool SettingUIView::init()
{
    bool bRet = true;

	return bRet;
}


void SettingUIView::onButtonSettingPPCenter( cocos2d::CCObject* pSender )
{
    
    SdkHandler::onGameCenter();
 

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SettingUIView::onButtonSettingAppReConn( cocos2d::CCObject* pSender )
{
	
	SettingData::Set(SettingData::BACKGROUND,!SettingData::Get(SettingData::BACKGROUND));

	bool  bBackRUN   = SettingData::Get(SettingData::BACKGROUND) ;

	if (bBackRUN)
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_back_run.png");
		mSettingReconn -> setTexture(texture);
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_reconnect.png");
		mSettingReconn -> setTexture(texture);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


void SettingUIView::onButtonSettingMusic( cocos2d::CCObject* pSender )
{
	
	SettingData::Set(SettingData::SOUND,!SettingData::Get(SettingData::SOUND));
	 
	bool  bSound =  SettingData::Get(SettingData::SOUND);
	if (bSound)
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_open.png");
		mSettingMusic -> setTexture(texture);
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_close.png");
		mSettingMusic -> setTexture(texture);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SettingUIView::onButtonSettingAudio( cocos2d::CCObject* pSender )
{
	SettingData::Set(SettingData::AUDIO,!SettingData::Get(SettingData::AUDIO));

	bool  bEffect = SettingData::Get(SettingData::AUDIO);
	if (bEffect)
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_open.png");
		mSettingAudio -> setTexture(texture);
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_close.png");
		mSettingAudio -> setTexture(texture);
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void SettingUIView::valueChanged( CCObject *sender, CCControlEvent controlEvent )  
{  
	CCControlSwitch* pSwitch = (CCControlSwitch*)sender;  
	if (pSwitch->isOn())  
	{  
		//_pLabel->setString("On");  
	}   
	else  
	{  
		//_pLabel->setString("Off");  
	}  
}  
void SettingUIView::onDataUpdate( bool isDataValid )
{
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		//clear();

		return;
	}
  
	
	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();

	//mSettingName->setString(pData->getName().c_str());

	char buffLvl[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffLvl,"%s:%d",UtilTools::GET_TEXT_FROM_LANG(525),pData->GetLevel());
//	mSettingLvl->setString(buffLvl);

	char buffGold[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffGold,"%s:%d",UtilTools::GET_TEXT_FROM_LANG(520),pData->GetGold());
	//mSettingGold->setString(buffGold);


	bool  bSound =  SettingData::Get(SettingData::SOUND);
	if (bSound)
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_open.png");
		mSettingMusic -> setTexture(texture);
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_close.png");
		mSettingMusic -> setTexture(texture);
	}
	


	bool  bEffect = SettingData::Get(SettingData::AUDIO);
	if (bEffect)
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_open.png");
		mSettingAudio -> setTexture(texture);
	}
	else
	{
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_close.png");
		mSettingAudio -> setTexture(texture);
	}


	 bool  bBackRUN   = SettingData::Get(SettingData::BACKGROUND) ;

	 if (bBackRUN)
	 {
		 CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_back_run.png");
		 mSettingReconn -> setTexture(texture);
	 }
	 else
	 {
		 CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("setting_reconnect.png");
		 mSettingReconn -> setTexture(texture);
	 }
	 string logo_text;
	 string  logo_image = SdkHandler::getLogoImageAndText(logo_text);

	 if (logo_image.size() > 0)
	 {
		 CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(logo_image.c_str());
		 if (texture)
		 {
			 	 mSettingPP -> setTexture(texture);
		 }
	 }
	 mPPText->setString(logo_text.c_str());
 
}

void SettingUIView::itemCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	//int index = (int)(((CCNode *)pSender)->getUserData());

}
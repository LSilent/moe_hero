#include "./ui/loginView.h"
#include "./CCControlExtension/CCScale9Sprite.h"
#include "./CCEditBox/CCEditBox.h"
#include "./ui/loginUi.h"

#include "./Game.h"
#include "./DataBase/DataBaseSystem.h"
#include "./event/EventSystem.h"

#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"
#include "./datapool/SettingData.h"
#include "GameVersion.h"
#include "./load/ResourceCheck.h"
//#include "./TestWebView/EXTestWebViewLayer.h"
#include "./datapool/SettingData.h"
#define MAX_STRING_BUFF_SIZE     (128)


#include "./base/nuts.h"
 

using namespace cocos2d;
using namespace cocos2d::extension;

#define CONTENT_POS_X            (0.050f)
#define CONTENT_POS_Y            (0.124f)//(0.242f)

#define CONTENT_POS_X_RENCENTLY            (0.050f)
#define CONTENT_POS_Y_RENCENTLY            (0.420f)//(0.242f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.23f)//(0.45f)

#define CONTENT_VIEW_SIZE_X_RENCENTLY      (0.89f)
#define CONTENT_VIEW_SIZE_Y_RENCENTLY      (0.17f)//(0.45f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.06f)//(0.17f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.9f)

#define ITEM_BUTTON_OFFSET_X     (0.20f)
#define ITEM_BUTTON_OFFSET_Y     (-0.030f)

#define ITEM_NAME_OFFSET_X       (-0.220f)
#define ITEM_NAME_OFFSET_Y       (0.030f)//(0.050f)

#define ITEM_DESC_OFFSET_Y       (-0.005f)
#define ITEM_DESC_OFFSET_X       (-0.07f)

#define ITEM_TIME_OFFSET_X       (-0.40f)
#define ITEM_TIME_OFFSET_Y       (-0.05f)

#define ITEM_TEXT_SIZE_X         (0.60f)
#define ITEM_TEXT_SIZE_Y         (0.08f)






bool loginView::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());

		pEnter = NULL;
		mScrollView = NULL;
		mScrollViewRencentlySever = NULL;
		isOpenSelect = false;
		selAccountItem = NULL;
		m_userAccount = NULL;
		selItem = NULL;
		m_SelectSrvZone = NULL;

		CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

		CCSprite* pSprite = CCSprite::create("login.png");
		CC_BREAK_IF(! pSprite);
		pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(pSprite);
        pSprite->setScaleX(SCALE_X);
        pSprite->setScaleY(SCALE_Y);

        pEnter = CCMenuItemImage::create(
            "loginenterhover.png",
            "loginenterhover.png",
            this,
            menu_selector(loginView::menuCloseCallback));
        CC_BREAK_IF(! pEnter);
		
        pEnter->setPosition(ccp(winSize.width/2, 100.f/960 *winSize.height));

        pMenu = CCMenu::create(pEnter, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu);

		string binVersion = g_GameVersion;
			   binVersion = "version : " + binVersion;
		/*string resVersion = ResourceCheck::GetSingleton()->getVersion();
			   resVersion = "ResVersion : " + resVersion;*/
		m_Version = CCLabelTTF::create((binVersion).c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		m_Version->setVerticalAlignment(kCCVerticalTextAlignmentTop);
		m_Version->setHorizontalAlignment(kCCTextAlignmentLeft);
		m_Version->setColor(ccYELLOW);
		m_Version->setPosition(ccp(0.15f*winSize.width, 0.96 *winSize.height ));
		this->addChild(m_Version);

if (USE_SDK_NUTS == SC_SDK)
{	
		string userName = "";
		userName = SettingData::GetLoaclUserAccount();
		selAccountItem = CCMenuItemImage::create("tipdlg.png","tipdlg.png",this, menu_selector(loginView::menuSelAccountCallback));
		selAccountItem->setPosition(ccp(winSize.width/2, 265.f/960 *winSize.height ));
		pMenu->addChild(selAccountItem);
		//selAccountItem->setVisible(userName.size()>0);
		char buffName[MAX_STRING_BUFF_SIZE]={0};
		string str = "";
		if (userName.size() > 0)
		{
			sprintf(buffName,"%s:%s",UtilTools::GET_TEXT_FROM_LANG(610),userName.c_str());
			str = buffName;
			//str += "  ";
			//str += UtilTools::GET_TEXT_FROM_LANG(613);
		}
        else
        {
           sprintf(buffName,"%s",UtilTools::GET_TEXT_FROM_LANG(613));
		   str = buffName;
        }
		m_userAccount = CCLabelTTF::create(str.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		m_userAccount->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_userAccount->setHorizontalAlignment(kCCTextAlignmentCenter);
		m_userAccount->setColor(ccWHITE);
		m_userAccount->setPosition(ccp(winSize.width/2, 265.f/960 *winSize.height ));
		this->addChild(m_userAccount);
		//m_userAccount->setVisible(selAccountItem->isVisible());
}

		selItem = CCMenuItemImage::create("tipdlg.png","tipdlg.png",this, menu_selector(loginView::menuSelServerCallback));
		selItem->setPosition(ccp(winSize.width/2, 200.f/960 *winSize.height ));
		pMenu->addChild(selItem);
		SERVER_ZONE_STATE state = SRV_ZONE_STATE_RMD;
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);

		X_INT serverid  = Game::getValidMaxServerID(Game::sm_SelectServer);
		const stDBC_FILE_SELECT_SERVER	* m_pCurData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(serverid);
		if (m_pCurData)
		{
			Game::sm_SelectServer = m_pCurData->id;
			SettingData::SetStr(SettingData::SELECTSERVER,UtilTools::IntToString(Game::sm_SelectServer));
		}
 
		char buffZone[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffZone,"%d%s %s [%s]",m_pCurData->id,UtilTools::GET_TEXT_FROM_LANG(599),m_pCurData->name,getServerState((SERVER_ZONE_STATE)m_pCurData->states).c_str());
		state = (SERVER_ZONE_STATE)m_pCurData->states;

	 
		string str = buffZone;
		str +="  ";
		str+=	 UtilTools::GET_TEXT_FROM_LANG(711) ;


		m_SelectSrvZone = CCLabelTTF::create(str.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		m_SelectSrvZone->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		m_SelectSrvZone->setHorizontalAlignment(kCCTextAlignmentCenter);
 

		m_SelectSrvZone->setColor( getServerStateColor(state));
		m_SelectSrvZone->setPosition(ccp(winSize.width/2, 200.f/960 *winSize.height ));
		this->addChild(m_SelectSrvZone);

		m_content = CCNode::create();
		m_content->setAnchorPoint(CCPointZero);
		this->addChild(m_content);
		m_content->setVisible(false);


		//服务器选择列表背景以及提示文字
		CCSprite *selSprite = CCSprite::create("n_login_svr_sel.png");
        selSprite->setAnchorPoint(ccp(0.5,0));
        selSprite->setScaleY(SCALE_Y);
        selSprite->setScaleX(SCALE_X);
        selSprite->setPosition(ccp(winSize.width * 0.5f ,winSize.height * 0.1f));
		m_content->addChild(selSprite);

		CCLabelTTF *selSpriteLabel = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(728),FONT_NAME_ARIAL_BOLD,FONT_SIZE_30);
		selSpriteLabel->setAnchorPoint(ccp(0.5f, 0.0f));
		selSpriteLabel->setScaleY(SCALE_Y);
		selSpriteLabel->setScaleX(SCALE_X);
		selSpriteLabel->setPosition(ccp(winSize.width * 0.5f ,winSize.height * 0.365f));
		selSpriteLabel->setColor(CCCOLOR_YELLOW);
		m_content->addChild(selSpriteLabel);


		CCSprite *selSprite_s = CCSprite::create("n_login_svr_sel_s.png");
		selSprite_s->setAnchorPoint(ccp(0.5,0));
		selSprite_s->setScaleY(SCALE_Y);
		selSprite_s->setScaleX(SCALE_X);
		selSprite_s->setPosition(ccp(winSize.width * 0.5f ,winSize.height * 0.38f));
		m_content->addChild(selSprite_s);

		CCLabelTTF *selSpriteLabel_s = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(729),FONT_NAME_ARIAL_BOLD,FONT_SIZE_30);
		selSpriteLabel_s->setAnchorPoint(ccp(0.5f, 0.0f));
		selSpriteLabel_s->setScaleY(SCALE_Y);
		selSpriteLabel_s->setScaleX(SCALE_X);
		selSpriteLabel_s->setPosition(ccp(winSize.width * 0.5f ,winSize.height * 0.60f));
		selSpriteLabel_s->setColor(CCCOLOR_YELLOW);
		m_content->addChild(selSpriteLabel_s);

		/*CCLabelTTF *title = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(600),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24);
		title->setColor(ccGREEN);
		title->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.285f));
		m_content->addChild(title);*/

		//#if (MY_TARGET_PLATFORM == MY_PLATFORM_IOS)
			//EXTestWebViewLayer *pLayer =   EXTestWebViewLayer::create();
			//pLayer->setPosition(ccp(winSize.width/2, 0.5f *winSize.height ));
			//pLayer->setContentSize(CCSize(winSize.width*0.6f,winSize.height*0.6f));
			//addChild(pLayer);
		//#endif
     
		bRet = true;
		showStartAction();
    } while (0);
	///////////////////////////////////////////////////////////////////////////////////////////////
	char skillPlist[MAX_STRING_BUFF_SIZE ];
	sprintf( skillPlist, "%s.plist", "lightningEffect" );

	char skillImage[ MAX_STRING_BUFF_SIZE];
	sprintf( skillImage, "%s.png", "lightningEffect" );

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile( skillPlist, skillImage );

	CCArray* animFrames = CCArray::createWithCapacity( 50 );

	for( int i = 0; i < 50; i++ )
	{
		sprintf( skillPlist, "%s_%05d.png", "lightningEffect" , i );
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( skillPlist );
		if( frame )
			animFrames->addObject( frame );
		else
			break;
	}


	CCSprite *lightEffect = CCSprite::create( "shake_shareBtn.png");

	CCAnimate *animate= CCAnimate::create( CCAnimation::createWithSpriteFrames( animFrames, 0.10f ));
	CCSequence *seq = CCSequence::create( CCRepeat::create(animate, 1), CCDelayTime::create(1.0f),
													CCRepeat::create(animate, 2), CCDelayTime::create(2.5f),NULL);

	CCAction *action = CCRepeatForever::create(seq);

	lightEffect->runAction(action);            
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	lightEffect->setPosition( ccp(winSize.width * 0.545f, winSize.height * 0.86f));
	lightEffect->setScale(0.50f);
	lightEffect->setRotation(31);
	lightEffect->setOpacity(200);
	addChild(lightEffect);

	CCSprite *lightEffect1 = CCSprite::create( "shake_shareBtn.png");
	lightEffect1->setPosition( ccp(winSize.width * 0.32f, winSize.height * 0.81f));
	lightEffect1->setScale(0.70f);
	lightEffect1->setRotation(-5);
	lightEffect1->setOpacity(210);
	CCAnimate *animate1= CCAnimate::create( CCAnimation::createWithSpriteFrames( animFrames, 0.14f ));
	CCSequence *seq1 = CCSequence::create( CCRepeat::create(animate1, 1), CCDelayTime::create(1.6f),
												CCRepeat::create(animate1, 2), CCDelayTime::create(1.1f),NULL);

	CCAction *action1 = CCRepeatForever::create(seq1);
	lightEffect1->runAction(action1);
	addChild(lightEffect1);


    return bRet;
}

void   loginView::updateRecentlySever()
{
	if (mScrollViewRencentlySever)
	{
		mScrollViewRencentlySever->removeFromParentAndCleanup(true);
		mScrollViewRencentlySever = NULL;
	}
	string s = SettingData::GetRecentServer();
	vector<X_INT> str;str.clear();
	UtilTools::ConvertStringToIntVector(s.c_str(),str,"|");

	X_INT num = str.size();
	if (num <= 0)
	{
		return;
	}
	


	mScrollViewRencentlySever = CCScrollViewEx::create();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	CCLayer *layer = CCLayer::create(); 
	CCMenuPEx *menu = CCMenuPEx::create(); 



	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X_RENCENTLY, winSize.height * num * ITEM_SPACE_DELTA_Y );;

	for (X_INT i = num -1  ;i >= 0  ;i--)
	{
		const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByIndexKey(str[i]);
		if (!m_pTableData)
		{
			continue;;
		}
		CCSprite *itemBackGround = CCSprite::create( "n_login_svr_spe.png" );
		CCPoint itemDockPos = cocos2d::CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - (num - i - 1) * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
		layer->addChild( itemBackGround );
		CCMenuItemImage *itemImage = CCMenuItemImage::create("m_guide_mask.png","m_guide_mask.png",this,menu_selector(loginView::menuComfireCallback));
		itemImage->setPosition(itemDockPos);
		itemImage->setAnchorPoint(ccp(0.5,0));
		//itemImage->setScaleY(0.5f);
		//itemImage->setScaleX(1.2f);
		itemImage->setUserData((void *)m_pTableData);
		menu->addChild(itemImage);

		char buffZone[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffZone,"%d%s",m_pTableData->id,UtilTools::GET_TEXT_FROM_LANG(599));

		CCLabelTTF* mName = CCLabelTTF::create( buffZone, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		layer->addChild( mName );

		char buffName[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffName,"%s",m_pTableData->name);
		CCLabelTTF* mDesc = CCLabelTTF::create( buffName, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24);
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		mDesc->setColor(this->getServerStateColor((SERVER_ZONE_STATE)m_pTableData->states));
		layer->addChild( mDesc );

		string strIcon ="";
		if (m_pTableData->states == SRV_ZONE_STATE_HOT)
		{
			strIcon = "n_login_svr_full.png";
		}
		else if(m_pTableData->states == SRV_ZONE_STATE_RMD)
		{
			strIcon = "n_login_svr_rmd.png";
		}
		else if(m_pTableData->states == SRV_ZONE_STATE_STOP)
		{
			strIcon = "n_login_svr_stop.png";
		}
		if (!strIcon.empty())
		{
			CCSprite *spriteFlag = CCSprite::create(strIcon.c_str());
			spriteFlag->setAnchorPoint(ccp(0,0.5f));
			spriteFlag->setPosition(ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUTTON_OFFSET_X , winSize.height * (ITEM_NAME_OFFSET_Y + 0.002f) ) ));
			layer->addChild(spriteFlag);
		}
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero );  
	layer->addChild( menu );

	mScrollViewRencentlySever->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X_RENCENTLY, winSize.height * CONTENT_VIEW_SIZE_Y_RENCENTLY) );
	mScrollViewRencentlySever->setContentSize( contentSize ); 
	mScrollViewRencentlySever->setContainer( layer );
	mScrollViewRencentlySever->setDirection( kCCScrollViewDirectionVertical );
	mScrollViewRencentlySever->setPosition( CCPointMake( winSize.width * CONTENT_POS_X_RENCENTLY, winSize.height * CONTENT_POS_Y_RENCENTLY ) );

	mScrollViewRencentlySever->setContentOffset( mScrollViewRencentlySever->minContainerOffset() );
	m_content->addChild(mScrollViewRencentlySever);

}


string loginView::getServerState(SERVER_ZONE_STATE state)
{
	string strIcon;
	switch (state)
	{
	case SRV_ZONE_STATE_STOP:
		strIcon = UtilTools::GET_TEXT_FROM_LANG(603);
		break;
	case SRV_ZONE_STATE_HOT:
		strIcon = UtilTools::GET_TEXT_FROM_LANG(601);
		break;
	case SRV_ZONE_STATE_RMD:
		strIcon = UtilTools::GET_TEXT_FROM_LANG(602);
		break;
	default:
		strIcon = UtilTools::GET_TEXT_FROM_LANG(614);
		break;
	}

	return strIcon;
}

ccColor3B loginView::getServerStateColor(SERVER_ZONE_STATE state)
{
	ccColor3B strColor;
	switch (state)
	{
	case SRV_ZONE_STATE_STOP:
		strColor = ccGRAY;
		break;
	case SRV_ZONE_STATE_HOT:
		strColor = ccYELLOW;
		break;
	case SRV_ZONE_STATE_RMD:
		strColor = ccGREEN;
		break;
	default:
		strColor = CCCOLOR_GREEN ;
		break;
	}

	return strColor;
}

void loginView::menuCloseCallback(CCObject* pSender)
{
    
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
	
	((loginUi*)getUserData())->onEnterClick();
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	if (pEnter)
	{
		endStartAction();
		pEnter->setEnabled(false);
		//pEnter->setColor(ccGRAY);
	}
	this->scheduleOnce(schedule_selector(loginView::EnableEnter),8);
}
void loginView::EnableEnter(float dt)
{
	if (pEnter)
	{
		showStartAction();
		pEnter->setEnabled(true);
		//pEnter->setColor(ccWHITE);
	}

}
void loginView::menuSelServerCallback(CCObject* pSender)
{
	if (!isOpenSelect)
	{
		pMenu->setTouchEnabled(false);
		m_content->setVisible(true);
		loadAllServerZone();

		isOpenSelect = true;
	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void loginView::menuSelAccountCallback(CCObject* pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_USER_LOGIN_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


void loginView::menuComfireCallback(CCObject* pSender)
{
	if (selAccountItem)
	{
			selAccountItem->setVisible(true);
	}
	
	if (m_userAccount)
	{
			m_userAccount->setVisible(true);
	}
	
 
	if (selItem)
		selItem->setVisible(true);
	if (m_SelectSrvZone)
		m_SelectSrvZone->setVisible(true);

	stDBC_FILE_SELECT_SERVER * m_pTableData = (stDBC_FILE_SELECT_SERVER *)((CCNode *)pSender)->getUserData();

	char buffZone[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffZone,"%d%s %s [%s]",m_pTableData->id,UtilTools::GET_TEXT_FROM_LANG(599),m_pTableData->name ,getServerState((SERVER_ZONE_STATE)m_pTableData->states).c_str());
	


	string str = buffZone;
	str +="  ";
	str+=	 UtilTools::GET_TEXT_FROM_LANG(711) ;
	m_SelectSrvZone->setColor( getServerStateColor(SERVER_ZONE_STATE( m_pTableData->states) ));
	m_SelectSrvZone->setString(str.c_str());

	m_content->setVisible(false);
	isOpenSelect = false;
	pMenu->setTouchEnabled(true);

	Game::sm_SelectServer = m_pTableData->id;
	SettingData::SetStr(SettingData::SELECTSERVER,UtilTools::IntToString(Game::sm_SelectServer));
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}
void loginView::loadAllServerZone()
{
	if (selAccountItem)
	{
		selAccountItem->setVisible(false);
	}
	
	if (m_userAccount)
		m_userAccount->setVisible(false);
	if (selItem)
		selItem->setVisible(false);
	if (m_SelectSrvZone)
		m_SelectSrvZone->setVisible(false);

	if (mScrollView)
	{
		mScrollView->removeFromParentAndCleanup(true);
		mScrollView = NULL;
	}
	
	mScrollView = CCScrollViewEx::create();

	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SELECT_SERVER);
	CCSize winSize = CCDirector::sharedDirector()->getVisibleSize();

	CCLayer *layer = CCLayer::create(); 
	CCMenuPEx *menu = CCMenuPEx::create(); 

	X_INT num = pDataFile->GetRecordsNum();

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * num * ITEM_SPACE_DELTA_Y );;

	for (X_INT i = num -1  ;i >= 0  ;i--)
	{
		const stDBC_FILE_SELECT_SERVER	* m_pTableData = (const stDBC_FILE_SELECT_SERVER*)pDataFile->GetFieldsByLineNum(i);
		CCSprite *itemBackGround = CCSprite::create( "n_login_svr_spe.png" );
		CCPoint itemDockPos = cocos2d::CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - (num - i - 1) * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setPosition( itemDockPos );
		layer->addChild( itemBackGround );
		CCMenuItemImage *itemImage = CCMenuItemImage::create("m_guide_mask.png","m_guide_mask.png",this,menu_selector(loginView::menuComfireCallback));
		itemImage->setPosition(itemDockPos);
		itemImage->setAnchorPoint(ccp(0.5,0));
		//itemImage->setScaleY(0.5f);
		//itemImage->setScaleX(1.2f);
		itemImage->setUserData((void *)m_pTableData);
		menu->addChild(itemImage);

		char buffZone[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffZone,"%d%s",m_pTableData->id,UtilTools::GET_TEXT_FROM_LANG(599));

		CCLabelTTF* mName = CCLabelTTF::create( buffZone, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mName->setPosition( itemNamePos );
		layer->addChild( mName );

		char buffName[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffName,"%s",m_pTableData->name);
		CCLabelTTF* mDesc = CCLabelTTF::create( buffName, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24);
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
		mDesc->setPosition( itemDescPos );
		mDesc->setColor(this->getServerStateColor((SERVER_ZONE_STATE)m_pTableData->states));
		layer->addChild( mDesc );
 
		string strIcon ="";
		if (m_pTableData->states == SRV_ZONE_STATE_HOT)
		{
			strIcon = "n_login_svr_full.png";
		}
		else if(m_pTableData->states == SRV_ZONE_STATE_RMD)
		{
			strIcon = "n_login_svr_rmd.png";
		}
		else if(m_pTableData->states == SRV_ZONE_STATE_STOP)
		{
			strIcon = "n_login_svr_stop.png";
		}
		if (!strIcon.empty())
		{
			CCSprite *spriteFlag = CCSprite::create(strIcon.c_str());
			spriteFlag->setAnchorPoint(ccp(0,0.5f));
			spriteFlag->setPosition(ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUTTON_OFFSET_X , winSize.height * (ITEM_NAME_OFFSET_Y + 0.002f) ) ));
			layer->addChild(spriteFlag);
		}
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero );  
	layer->addChild( menu );

	mScrollView->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mScrollView->setContentSize( contentSize ); 
	mScrollView->setContainer( layer );
	mScrollView->setDirection( kCCScrollViewDirectionVertical );
	mScrollView->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mScrollView->setContentOffset( mScrollView->minContainerOffset() );
	m_content->addChild(mScrollView);

	updateRecentlySever();
}
void   loginView::endStartAction()
{
	
	pEnter->stopAllActions();
	pEnter->setVisible(false);
}
void loginView::showStartAction()
{
	pEnter->setVisible(true);
	pEnter->runAction(CCRepeat::create(
		CCSequence::create(
		CCScaleTo::create(0.5f, 1.2f),
		CCScaleTo::create(0.5f, 1.0f),
		NULL
		),
		kCCRepeatForever
		));
}



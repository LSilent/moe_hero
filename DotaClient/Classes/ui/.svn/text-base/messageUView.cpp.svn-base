#include "./ui/messageUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h" 
#include "./object/Item.h"
#include "GameResult.h"
using namespace cocos2d;
USING_NS_CC_EXT;
 

#define CONTENT_POS_X            (0.020f)
#define CONTENT_POS_Y            (0.10f)

#define CONTENT_VIEW_SIZE_X      (0.96f)
#define CONTENT_VIEW_SIZE_Y      (0.80f)

#define ITEM_DOCK_X              (0.10f)
#define ITEM_SPACE_DELTA_Y       (0.16f)
#define ITEM_START_Y             (0.1f * -0.8f)

#define ITEM_BUTTON_OFFSET_X     (0.75f)
#define ITEM_BUTTON_OFFSET_Y     (-0.000f)

#define ITEM_NAME_OFFSET_X       (0.15f)
#define ITEM_NAME_OFFSET_Y       (0.050f)

#define ITEM_DESC_OFFSET_X       (0.15f)
#define ITEM_DESC_OFFSET_Y       (-0.005f)

#define ITEM_TIME_OFFSET_X       (0.15f)
#define ITEM_TIME_OFFSET_Y       (-0.05f)

#define ITEM_TEXT_SIZE_X         (0.48f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

#define ITEM_TIME_LINE_Y		 (-0.078f)

#define MSG_TAG               200

 
MessageUIView::MessageUIView()
:mNodeMsgCntNode(NULL)
, mMsgSender(NULL)
, mMsgTitle(NULL)
, mMsgTime(NULL)
, mMsgContent(NULL)
, mGrayLayer(NULL)
, m_MessageType(EM_MESSAGE_TYPE_SYSTEM)
, m_pOpenedMessage(NULL)
 
{
	mContent = NULL;

	for (int i=0;i<3;i++)
	{
		mTabItems[i] = NULL;
	}
 

	isCloseDetail = true;
}

MessageUIView::~MessageUIView()
{
 

	for (int i=0;i<3;i++)
	{
		CC_SAFE_RELEASE(mTabItems[i]);
	}

	CC_SAFE_RELEASE(mNodeMsgCntNode);
	CC_SAFE_RELEASE(mMsgSender);
	CC_SAFE_RELEASE(mMsgTitle);
	CC_SAFE_RELEASE(mMsgTime);
	CC_SAFE_RELEASE(mMsgContent);
	CC_SAFE_RELEASE(mGrayLayer);

}


void MessageUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	
}


SEL_MenuHandler MessageUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonAll", MessageUIView::onButtonAll);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonFight", MessageUIView::onButtonFight);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonFriends", MessageUIView::onButtonFriends);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonMsgClose", MessageUIView::onButtonMsgClose);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonMsgRevenge", MessageUIView::onButtonMsgRevenge);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", MessageUIView::onButtonClose);
	

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonOpenAll", MessageUIView::onButtonOpenAll);

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonDelAll", MessageUIView::onButtonDelAll);
 
	
    return NULL;    
}


SEL_CCControlHandler MessageUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}
void MessageUIView::EnableAllMenuItem()
{

	for (int  i = EM_MESSAGE_TYPE_SYSTEM ; i<=  EM_MESSAGE_TYPE_REVENGE;i++ )
	{
			mTabItems[i]->setEnabled(true);
	}
 
}
void MessageUIView::disableMenuItem(EM_MESSAGE_TYPE type,bool disable )
{
	for (int  i = EM_MESSAGE_TYPE_SYSTEM ; i<=  EM_MESSAGE_TYPE_REVENGE;i++ )
	{
		 mTabItems[i]->setEnabled(!disable);
			/*if (i == type)
			{
				mTabItems[i]->setEnabled(disable);
			}else
			{
				mTabItems[i]->setEnabled(!disable);
			}*/
	}
}
X_VOID MessageUIView::__onSelectMessage(EM_MESSAGE_TYPE type)
{
	 
	for (int  i = EM_MESSAGE_TYPE_SYSTEM ; i<=  EM_MESSAGE_TYPE_REVENGE;i++ )
	{
		if (i == type)
		{
			mTabItems[i]->setEnabled(false);
			//mTabItems[i]->setNormalImage(CCSprite::create("mail_tab_sel.png"));
		}else
		{
			//mTabItems[i]->setNormalImage(CCSprite::create("mail_tab.png"));
			mTabItems[i]->setEnabled(true);
		}
	}
	

}
void MessageUIView::onButtonAll(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	
	if( m_MessageType != EM_MESSAGE_TYPE_SYSTEM )
	{
		m_MessageType = EM_MESSAGE_TYPE_SYSTEM;
		mNodeMsgCntNode->setVisible(false);
		onDataUpdate(true);
	}
}

void MessageUIView::onButtonFight(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	if( m_MessageType != EM_MESSAGE_TYPE_BATTLE )
	{
		m_MessageType = EM_MESSAGE_TYPE_BATTLE;
		mNodeMsgCntNode->setVisible(false);
		onDataUpdate(true);
	}
}

void MessageUIView::onButtonFriends(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	if( m_MessageType != EM_MESSAGE_TYPE_REVENGE )
	{
		m_MessageType = EM_MESSAGE_TYPE_REVENGE;
		mNodeMsgCntNode->setVisible(false);
		onDataUpdate(true);
	}
}

bool MessageUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nMessageAll", CCMenuItemImage *, this->mTabItems[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nMessageBat", CCMenuItemImage *, this->mTabItems[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "nMessageFriend", CCMenuItemImage *, this->mTabItems[2]);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeMsgCntNode", CCNode *, this->mNodeMsgCntNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMsgSender", CCLabelTTF *, this->mMsgSender);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMsgTitle", CCLabelTTF *, this->mMsgTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMsgTime", CCLabelTTF *, this->mMsgTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMsgContent", CCLabelTTF *, this->mMsgContent);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mGrayLayer", CCLayerColor *, this->mGrayLayer);
 


	return false;
}

bool MessageUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

bool MessageUIView::init()
{
    return true;
}


void MessageUIView::onDataUpdate( bool isDataValid )
{
	
 
	if( !isDataValid )
	{
		//clear();
		return;
	}

	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}
	__onSelectMessage(m_MessageType);
	mContent = CCScrollViewEx::create();
	addChild( mContent );
	mNodeMsgCntNode->setVisible(false);

     messages = DataPool::GetSingleton()->getMailData()->getMail();

	if( messages.empty() )
	{
		return;
	}
	m_vecRevengeMessage.clear();
	m_vecSystemMessage.clear();
	m_vecBattleMessage.clear();

	vector<Message *>::iterator iter = messages.begin();
	for (;iter != messages.end(); iter++)
	{
		Message *msgItem = (Message *)(*iter);
		if (!msgItem)
		{
			continue;
		}
		if (msgItem->getType() == EM_TYPE_MAIL_WOODROB)
		{
			m_vecRevengeMessage.push_back(*iter);
			continue;
		}
		if (msgItem->getType() == EM_TYPE_MAIL_SYSTEM)
		{
			if (msgItem->getSysyemSubType() == EM_MAIL_SYSTEM_TYPE_ARENA || msgItem->getSysyemSubType() == EM_MAIL_SYSTEM_TYPE_QUJING )
			{
				m_vecBattleMessage.push_back(*iter);
				continue;
			}
			//----------------普通的系统邮件
			m_vecSystemMessage.push_back(*iter);
			continue;;
		}
		//可执行也发给到系统里面显示
		if (msgItem->getType() == EM_TYPE_MAIL_EXE)
		{
			m_vecSystemMessage.push_back(*iter);
		}
	}
	m_hover.clear();mhoverVisble = 0;
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx* menu = NULL;
	switch (m_MessageType)
	{
	case EM_MESSAGE_TYPE_SYSTEM:
		menu = UpdateNormalMailData(layer);
		break;
	case	EM_MESSAGE_TYPE_BATTLE:
		menu = UpdateBattleMailData(layer);
		break;
	case EM_MESSAGE_TYPE_REVENGE:
		menu = UpdateRevengeMailData(layer);
		break;
	
	default:
		break;
	}
	if (!menu)
	{
		return;
	}
	
	layer->addChild( menu );
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * messages.size() * ITEM_SPACE_DELTA_Y );
	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize );
	mContent->setContainer( layer );
	mContent->setDirection( kCCScrollViewDirectionVertical );
	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );
	mContent->setContentOffset( mContent->minContainerOffset() );


	if(isCloseDetail)
	{
		mNodeMsgCntNode->setVisible(false);
		mContent->setVisible(true);
	}
	else
	{
		mNodeMsgCntNode->setVisible(true);
		mNodeMsgCntNode->setZOrder(mContent->getZOrder()+1);
		//mContent->setVisible(false);
	}
}
CCMenuEx* MessageUIView::UpdateBattleMailData( CCLayer * layer ) 
{
	 
	X_UINT size = m_vecBattleMessage.size();
	CCMenuEx *menu = CCMenuEx::create(); 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );
 
	for (X_UINT i = 0;i<size;i++)
	{
		Message *pMessage = m_vecBattleMessage[i];
		UpdateSingleBattleMail(pMessage, i, contentSize, layer, menu);
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 
	menu->setPosition( CCPointZero );  

	return menu;
}

CCMenuEx* MessageUIView::UpdateNormalMailData( CCLayer * layer ) 
{ 
	
	X_UINT size = m_vecSystemMessage.size();
	CCMenuEx *menu = CCMenuEx::create(); 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );
  
	for (X_UINT i = 0;i<size;i++)
	{
		Message *pMessage = m_vecSystemMessage[i];
		UpdateSingleNormalMail(pMessage, i, contentSize, layer, menu);
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 
	menu->setPosition( CCPointZero );  

	return menu;
}
cocos2d::CCMenuEx* MessageUIView::UpdateRevengeMailData( CCLayer* layer )
{
 
	X_UINT size = m_vecRevengeMessage.size();
	CCMenuEx *menu = CCMenuEx::create(); 
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );
 
	for (X_UINT i = 0;i < size;i++)
	{
		Message *pMessage = m_vecRevengeMessage[i];
		UpdateSingleRevengeMail(pMessage, i, contentSize, layer, menu);

	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero );  
	return menu;
}
void MessageUIView::UpdateSingleBattleMail( Message * pMessage, X_UINT i, CCSize &contentSize, CCLayer * layer, CCMenuEx * menu) 
{
	UpdateSingleMail(pMessage, i, contentSize, layer,menu, menu_selector(MessageUIView::itemBattleMessageCallBack),menu_selector(MessageUIView::onButtonMsgDelete));
 
}


void MessageUIView::UpdateSingleNormalMail( Message * pMessage, X_UINT i, CCSize &contentSize, CCLayer * layer, CCMenuEx * menu) 
{
	UpdateSingleMail(pMessage, i, contentSize, layer,menu, menu_selector(MessageUIView::itemNormalMessageCallBack),menu_selector(MessageUIView::onButtonMsgDelete));
	 
}
void MessageUIView::UpdateSingleRevengeMail( Message * pMessage, X_UINT i, CCSize &contentSize, CCLayer * layer, CCMenuEx * menu) 
{
	UpdateSingleMail(pMessage, i, contentSize, layer,menu, menu_selector(MessageUIView::itemRevengeMessageCallBack),menu_selector(MessageUIView::onButtonMsgDelete));
	//补充复仇邮件内容
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
	
	string str ;

	bool b = pMessage->CanRevenge();
	if (b)
	{
		str = UtilTools::GET_TEXT_FROM_LANG(648);
	}
	else
	{
		str = UtilTools::GET_TEXT_FROM_LANG(649);
	}

	CCLabelTTF* mStatus = CCLabelTTF::create( str.c_str() , FONT_NAME_ARIAL_BOLD, FONT_SIZE_24*SCALE_X );
	mStatus->setColor(ccGREEN);
	CCPoint itemStatusPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * (ITEM_BUTTON_OFFSET_X - 0.20f), winSize.height * ITEM_TIME_OFFSET_Y ) );
	mStatus->setPosition( itemStatusPos );
	layer->addChild( mStatus );

	 if (b)
	 {
		 CCMenuItemImage *menuButtonItem = CCMenuItemImage::create( "mail_del.png", "mail_del.png", this, menu_selector(MessageUIView::onButtonMsgRevenge) );  
		 CCPoint itemButtonPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUTTON_OFFSET_X, winSize.height * (ITEM_BUTTON_OFFSET_Y - 0.015f )) );
		 menuButtonItem->setPosition( itemButtonPos ); 
		 menuButtonItem->setUserData( (void *)(i+ MSG_TAG) );
		 menu->addChild( menuButtonItem );
		 CCLabelTTF *buttonText = CCLabelTTF::create( UtilTools::GET_TEXT_FROM_LANG(686), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24*SCALE_X );
		 buttonText->setPosition( itemButtonPos );
		 layer->addChild( buttonText, 10 );

	 }
	 

	

	 
}
void MessageUIView::UpdateSingleMail( Message * pMessage, X_UINT i, CCSize &contentSize, CCLayer * layer, CCMenuEx * menu , cocos2d:: SEL_MenuHandler openfun,cocos2d:: SEL_MenuHandler delfun) 
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	const X_CHAR *title =  pMessage->getTitle();
	const X_CHAR *Contex =  pMessage->getContex();
	string date = pMessage->getDate();
	string hour  = pMessage->getDateHour();
	const X_CHAR *sourceName = pMessage->getSenderName();

 
	CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
	CCSprite *Back = CCSprite::create("mail_sel.png");
	Back->setPosition(itemDockPos);
	Back->setScale(SCALE_X);
	layer->addChild(Back);
	Back->setAnchorPoint( ccp( 0.1, 0.5f ) );
	m_hover[i] = Back;
	Back->setVisible(false);

	CCSprite *iconBack = CCSprite::create("AchieveBack.png");
	iconBack->setPosition(itemDockPos);
	iconBack->setScale(SCALE_X*0.6f);
	layer->addChild(iconBack);
	CCSprite *icon = CCSprite::create(pMessage->getIcon().c_str());
	icon->setPosition(itemDockPos);
	layer->addChild(icon);


	if (pMessage->isOpened())
	{ 
		CCSprite *openFlag = CCSprite::create("mail_read_flag.png");
		openFlag->setPosition( CCPoint(icon->getContentSize().width*0.5f,icon->getContentSize().height*0.8f));
		icon->addChild(openFlag);
 
	}

	CCLabelTTF* mName = CCLabelTTF::create( title, FONT_NAME_ARIAL_BOLD, FONT_SIZE_30*SCALE_X );
	mName->setAnchorPoint( ccp( 0, 0.5f ) );
	mName->setColor(CCCOLOR_YELLOW);
	CCPoint itemNamePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * ITEM_NAME_OFFSET_Y ) );
	mName->setPosition( itemNamePos );
	layer->addChild( mName );

	CCLabelTTF* mDesc = CCLabelTTF::create( Contex, FONT_NAME_ARIAL_BOLD, FONT_SIZE_24*SCALE_X  ,CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * (ITEM_TEXT_SIZE_Y-0.03) ), kCCTextAlignmentLeft );
	mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
	mDesc->setColor(CCCOLOR_GREEN);
	CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
	mDesc->setPosition( itemDescPos );
	layer->addChild( mDesc );

	string strTime = date;
	strTime += " ";
	strTime += hour.substr(0,_____max(0,hour.length()-3));
	CCLabelTTF* mTime = CCLabelTTF::create(strTime.c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24*SCALE_X  );
	mTime->setAnchorPoint( ccp( 0, 0.5f ) );
	mTime->setColor(CCCOLOR_GREEN);
	CCPoint itemTimePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_TIME_OFFSET_X, winSize.height * ITEM_TIME_OFFSET_Y ) );
	mTime->setPosition( itemTimePos );
	layer->addChild( mTime );


	float delPos = 0.f;
	if (pMessage->getType() == EM_TYPE_MAIL_WOODROB)
	{
		delPos = winSize.height * ITEM_NAME_OFFSET_Y ;

	}else
	{
		delPos = winSize.height * ITEM_BUTTON_OFFSET_Y;
	}
	

	CCMenuItemImage *menuButtonItem = CCMenuItemImage::create( "mail_del.png", "mail_del.png", this, delfun );  
	CCPoint itemButtonPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_BUTTON_OFFSET_X, delPos) );
	menuButtonItem->setPosition( itemButtonPos ); 
	menuButtonItem->setUserData( (void *)(i+ MSG_TAG) );
	menu->addChild( menuButtonItem );
	CCLabelTTF *buttonText = CCLabelTTF::create( UtilTools::GET_TEXT_FROM_LANG(727), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24*SCALE_X  );
	buttonText->setPosition( itemButtonPos );
	layer->addChild( buttonText, 10 );




	CCMenuItem *menuButtonOpenItem = CCMenuItem::create(this, openfun );  
	CCPoint itemopenButtonPos = ccpAdd( itemDockPos, CCPointMake( 0.f, winSize.height * ITEM_BUTTON_OFFSET_Y ) );
	menuButtonOpenItem->setPosition( itemopenButtonPos ); 
	menuButtonOpenItem->setUserData( (void *)(i+ MSG_TAG) );
	menu->addChild( menuButtonOpenItem );
	menuButtonOpenItem->setContentSize(CCSize(winSize.width * (ITEM_BUTTON_OFFSET_X - 0.05f),winSize.width * ITEM_SPACE_DELTA_Y));
	menuButtonOpenItem->setAnchorPoint(CCPoint(0.f,0.5f));



	CCSprite *spaceLine = CCSprite::create( "mail_space_line.png" );
	spaceLine->setScaleX(SCALE_X);
	spaceLine->setScaleY(SCALE_Y);
	CCPoint spaceLinePos = ccpAdd( itemDockPos, CCPointMake( 0, winSize.height * ITEM_TIME_LINE_Y ) );
	spaceLine->setPosition( spaceLinePos );
	layer->addChild( spaceLine );
	spaceLine->setAnchorPoint( ccp( 0.1, 0.5f ) );
}



void MessageUIView::updateMsgContent(Message *pMsg)
{

	mMsgSender->setString(pMsg->getSenderName());
	mMsgTitle->setString(pMsg->getTitle());

	string date = pMsg->getDate();
	string hour  = pMsg->getDateHour();

	string strTime = date;
	strTime += " ";
	strTime += hour.substr(0,_____max(0,hour.length()-3));
	mMsgTime->setString(strTime.c_str());

	mMsgContent->setString(pMsg->getContex());
	mMsgContent->setFontSize(45*SCALE_Y);
	disableMenuItem(m_MessageType);
}
void MessageUIView::itemBattleMessageCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	if (m_MessageType != EM_MESSAGE_TYPE_BATTLE)
		return;
	int iTag = (int)(((CCNode *)pSender)->getUserData());
	__openMessage(iTag);
}
void MessageUIView::itemNormalMessageCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;
	if (m_MessageType != EM_MESSAGE_TYPE_SYSTEM)
		return;
	int iTag = (int)(((CCNode *)pSender)->getUserData());
	__openMessage(iTag);

}
void MessageUIView::__openMessage(int tag)
{
	if (!isCloseDetail)
	{
		return;
	}
	m_pOpenedMessage = 0;
	switch (m_MessageType)
	{
	case MessageUIView::EM_MESSAGE_TYPE_INVALID:
		return;
		break;
	case MessageUIView::EM_MESSAGE_TYPE_SYSTEM:
			m_pOpenedMessage = m_vecSystemMessage[tag - MSG_TAG];
		break;
	case MessageUIView::EM_MESSAGE_TYPE_BATTLE:
			m_pOpenedMessage = m_vecBattleMessage[tag - MSG_TAG];
		break;
	case MessageUIView::EM_MESSAGE_TYPE_REVENGE:
			m_pOpenedMessage = m_vecRevengeMessage[tag - MSG_TAG];
		break;
	default:
		break;
	}
	if (m_pOpenedMessage != NULL)
	{
		//mContent->setVisible(false);
		mNodeMsgCntNode->setScale(0.5f);
		mNodeMsgCntNode->setVisible(true);
		mGrayLayer->setVisible(false);
		mNodeMsgCntNode->setZOrder(mContent->getZOrder()+1);
		updateMsgContent(m_pOpenedMessage);
		isCloseDetail = false;
		m_pOpenedMessage->Read();

		if (mhoverVisble)
		{
			mhoverVisble->setVisible(false);
		}
		
		if (mhoverVisble = m_hover[tag - MSG_TAG])// 这地方没错 就是赋值
		{
			mhoverVisble->setVisible(true);
		}
		CCAction* popupLayer = CCSequence::create(
			CCScaleTo::create(0.2f, 1.00f),
			CCDelayTime::create(0.05f),
			CCCallFunc::create(this, callfunc_selector(MessageUIView::openMailCallBack)) ,NULL);
			//CCScaleTo::create(0.32f, 0.95f),
			//CCScaleTo::create(0.32f, 1.0f),NULL);
		mNodeMsgCntNode->runAction( popupLayer );
		onDataUpdate(true );
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}
void MessageUIView::openMailCallBack(){
	mGrayLayer->setVisible(true);
	mGrayLayer->setOpacity(0);
	CCAction* actionFadeTo= CCFadeTo::create(0.1f,128);
	mGrayLayer->runAction(actionFadeTo);
	
}
void MessageUIView::itemRevengeMessageCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;
	if (m_MessageType != EM_MESSAGE_TYPE_REVENGE)
		return;
	int iTag = (int)(((CCNode *)pSender)->getUserData());
	__openMessage(iTag);
	
}

void MessageUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	vector<string> str;str.clear();
	str.push_back("close");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_MESSAGE_SHOW,str);
}

void MessageUIView::onButtonOpenAll(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	vector<Message*> *v = 0;
	switch (m_MessageType)
	{
	case EM_MESSAGE_TYPE_SYSTEM:
		{
			SendLogicPacket::OpenMailAll(EM_TYPE_MAIL_CONTENT_NORMAL);
			v = &m_vecSystemMessage;
		}
		
		break;
	case	EM_MESSAGE_TYPE_BATTLE:
		{
			SendLogicPacket::OpenMailAll(EM_TYPE_MAIL_CONTENT_COMBAT);
			v = &m_vecBattleMessage;
		}

		break;
	case EM_MESSAGE_TYPE_REVENGE:
		{
			SendLogicPacket::OpenMailAll(EM_TYPE_MAIL_CONTENT_WOOD);
			v = &m_vecRevengeMessage;
		}
		break;
	} 
	if (v)
	{
		 X_INT num = v->size();
		for (X_INT i = 0;i < num;i++)
		{
			if(!v->at(i))continue;
			v->at(i)->Read(false);
		}
		onDataUpdate(true );
	}
}
void MessageUIView::onButtonDelAll(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}
	switch (m_MessageType)
	{
	case EM_MESSAGE_TYPE_SYSTEM:
		SendLogicPacket::DelMailAll(EM_TYPE_MAIL_CONTENT_NORMAL);
		break;
	case	EM_MESSAGE_TYPE_BATTLE:
		SendLogicPacket::DelMailAll(EM_TYPE_MAIL_CONTENT_COMBAT);
		break;
	case EM_MESSAGE_TYPE_REVENGE:
		SendLogicPacket::DelMailAll(EM_TYPE_MAIL_CONTENT_WOOD);
		break;
	}
 
}
void MessageUIView::onButtonMsgClose(cocos2d::CCObject * pSender)
{
	mContent->setVisible(true);
	mNodeMsgCntNode->setVisible(false);
	m_pOpenedMessage = NULL;
	isCloseDetail = true;
	__onSelectMessage(m_MessageType);
	if (mhoverVisble)
	{
		mhoverVisble->setVisible(false);
	}
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void MessageUIView::onButtonMsgDelete(cocos2d::CCObject * pSender)
{
	if (!isCloseDetail)
	{
		return;
	}

	int tag = (int)(((CCNode *)pSender)->getUserData());
	Message *pMsg = 0;
	switch (m_MessageType)
	{
	case MessageUIView::EM_MESSAGE_TYPE_INVALID:
		return;
		break;
	case MessageUIView::EM_MESSAGE_TYPE_SYSTEM:
		pMsg = m_vecSystemMessage[tag - MSG_TAG];
		break;
	case MessageUIView::EM_MESSAGE_TYPE_BATTLE:
		pMsg = m_vecBattleMessage[tag - MSG_TAG];
		break;
	case MessageUIView::EM_MESSAGE_TYPE_REVENGE:
		pMsg = m_vecRevengeMessage[tag - MSG_TAG];
		break;
	default:
		break;
	}
	if (pMsg != NULL)
	{
		pMsg->Delete();
	}
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void MessageUIView::onButtonMsgRevenge( cocos2d::CCObject * pSender )
{
	if (!isCloseDetail)
	{
		return;
	}

	int tag = (int)(((CCNode *)pSender)->getUserData());
	Message *pMsg = m_vecRevengeMessage[tag - MSG_TAG];

	if( pMsg->CanRevenge())
	{
		SendLogicPacket::AskMessageRevengeWood(pMsg->getIndex());
		std::vector<std::string>  par;
		par.push_back("0");
		par.push_back("Revenge");
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BASE_ACTIVITY_SHOW,par);
	}
	else
	{
		vector<string> strV(1,UtilTools::GET_TEXT_FROM_LANG(WOOD_FAIL_SAFETIME));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);		
	}
	
}
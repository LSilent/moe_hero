#include "./ui/ChatMessageUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/SettingData.h"
#include "./sound/SoundSystem.h"
#include "./base/pp.h"
#include "./datapool/ChatData.h"
#include "./timer/SystemTimer.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.02f)//(0.045f)
#define CONTENT_POS_Y            (0.11f)

#define CONTENT_VIEW_SIZE_X      (0.96f)//(0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.81f)//(0.555f) 

#define EDITBOX_VIEW_SIZE_X		(0.60f)
#define EDITBOX_VIEW_SIZE_Y		(0.05f)

#define EDITBOX_VIEW_POS_X		(0.39f)
#define EDITBOX_VIEW_POS_Y		(0.15f)

#define ITEM_SPACE_DELTA_X       (0.220f)
#define ITEM_SPACE_DELTA_Y       (0.010f)//(0.165f)

#define ITEM_START_X             (0.09f)
#define ITEM_START_Y             (0.01f)//(0.03f)//(0.45f)

#define ITEM_DOCK_X              (0.025f)//(0.451f)//(0.44f)
#define ITEM_DOCK_X_SELF         (0.925f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            3

#define SEND_MSG_MAX_TIME        3

#define CHAT_LABEL_MAX_SIZE_X	CONTENT_VIEW_SIZE_X * 0.65f

ChatMessageUIView::ChatMessageUIView()
{
	meditBack = 0;
	mContent = NULL;
    pEditBox = NULL;
    
	curTime = 0;

}

ChatMessageUIView::~ChatMessageUIView()
{
 
	CC_SAFE_RELEASE(meditBack);
}


void ChatMessageUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
    
	 
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
   // pEditBox = CCEditBox::create(CCSizeMake(winSize.width * EDITBOX_VIEW_SIZE_X, winSize.height * EDITBOX_VIEW_SIZE_Y), CCScale9Sprite::create("n_op_0.png"));
    pEditBox = CCEditBox::create(meditBack->getContentSize(), CCScale9Sprite::create("n_op_0.png"));
    //pEditBox->setPlaceHolder("hello world!");
    pEditBox->setReturnType(kKeyboardReturnTypeSend);
	if (meditBack)
	{
		pEditBox->setPosition(meditBack->getPosition());
	}

    //pEditBox->setPosition(ccp(winSize.width * EDITBOX_VIEW_POS_X,winSize.height * EDITBOX_VIEW_POS_Y));
    pEditBox->setDelegate(this);
    addChild(pEditBox,20);
   
	onDataUpdate( false );
}


SEL_MenuHandler ChatMessageUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
		CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", ChatMessageUIView::onButtonClose);
		CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSendMsg", ChatMessageUIView::onButtonSendMsg);
	return NULL;    
}

SEL_CCControlHandler ChatMessageUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool ChatMessageUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
 
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_editBack", CCSprite *, this->meditBack);
	return false;
}

bool ChatMessageUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool ChatMessageUIView::init()
{
    bool bRet = true;

	return bRet;
}

void ChatMessageUIView::updateMsgContent()
{
    
    if( mContent )
 	{
 		mContent->removeFromParentAndCleanup( true );
        mContent = NULL;
 	}

    PlayerData *pData = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData();
    mContent = CCScrollViewEx::create();
    CCLayer *layer = CCLayer::create();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize contentSize(winSize.width * CONTENT_VIEW_SIZE_X, 0);

    int num = mRecordItems.size();
 
    float lblHeight = 5.0f;
    
    for (int j = 0; j < num; j++)
    {
        Record rd = mRecordItems.at(j);
        string str = rd.m_strName;
       // str+=":";
		CCLabelTTF *labelName = CCLabelTTF::create(str.c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_30,
			CCSizeMake(0, 0),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		labelName->setColor(CCCOLOR_YELLOW);
		labelName->setAnchorPoint(CCPointZero);
		CCPoint itemNamePos = CCPointMake( 0, winSize.height * ( ITEM_START_Y +j * ITEM_SPACE_DELTA_Y ) + lblHeight );
		layer->addChild(labelName);


		str = rd.m_strContex;
		int loc = str.find_first_not_of(" ");
		if (loc > 0)
		{
			str = str.substr(loc, str.length() - loc);
		}
        CCLabelTTF *labelCnt = CCLabelTTF::create(str.c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_30,
                                                  CCSizeMake(0, 0),kCCTextAlignmentLeft,kCCVerticalTextAlignmentCenter);
		if (labelCnt->getContentSize().width > CHAT_LABEL_MAX_SIZE_X * winSize.width)
		{
			labelCnt->setDimensions(CCSizeMake(CHAT_LABEL_MAX_SIZE_X * winSize.width,0));
		}
		
		if (rd.m_strName != pData->getName())
		{
			labelCnt->setAnchorPoint(CCPointZero);
			CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y +j * ITEM_SPACE_DELTA_Y ) + lblHeight);
			labelCnt->setPosition(itemDockPos);
			layer->addChild(labelCnt);

			itemNamePos.y += labelCnt->getContentSize().height + 10.0f;
			labelName->setPosition(itemNamePos);

			int chatHeight = labelName->getContentSize().height + labelCnt->getContentSize().height + 10.0f ;
			CCScale9Sprite *chatBg = CCScale9Sprite::create("chat_messageBg_other.png");
			chatBg->setAnchorPoint( ccp( 0.0f, 0.0f ));
			chatBg->setInsetLeft(40);
			chatBg->setInsetRight(30);
			chatBg->setInsetTop(30);
			chatBg->setInsetBottom(30);
			if (labelCnt->getContentSize().width <= 70.0f)
			{
				chatBg->setPreferredSize(CCSizeMake(70.0f + 20.0f, chatHeight));
			}
			else
			{
				chatBg->setPreferredSize(CCSizeMake(labelCnt->getContentSize().width + 25.0f, chatHeight));
			}

			chatBg->setPosition(itemDockPos.x - 10.0f, itemDockPos.y - 25.0f);
			layer->addChild(chatBg);
			labelCnt->setZOrder(chatBg->getZOrder()+1);

			chatHeight += 30.0f;
			lblHeight += chatHeight;
		}
		else
		{
			labelCnt->setAnchorPoint(ccp(1.0f, 0.0f));
			CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X_SELF, winSize.height * ( ITEM_START_Y +j * ITEM_SPACE_DELTA_Y ) + lblHeight);
			labelCnt->setPosition(itemDockPos);
			layer->addChild(labelCnt);


			labelName->setAnchorPoint(ccp(1.0f, 0.0f));
			itemNamePos.x = winSize.width * ITEM_DOCK_X_SELF;
			itemNamePos.y += labelCnt->getContentSize().height + 10.0f;
			labelName->setPosition(itemNamePos);

			int chatHeight = labelName->getContentSize().height + labelCnt->getContentSize().height + 10.0f ;
			CCScale9Sprite *chatBg = CCScale9Sprite::create("chat_messageBg_self.png");
			chatBg->setAnchorPoint( ccp( 1.0f, 0.0f ));
			chatBg->setInsetLeft(30);
			chatBg->setInsetRight(40);
			chatBg->setInsetTop(30);
			chatBg->setInsetBottom(30);
			if (labelCnt->getContentSize().width <= 70.0f)
			{
				chatBg->setPreferredSize(CCSizeMake(70.0f + 20.0f, chatHeight));
			}
			else
			{
				chatBg->setPreferredSize(CCSizeMake(labelCnt->getContentSize().width + 25.0f, chatHeight));
			}

			chatBg->setPosition(itemDockPos.x + 15.0f, itemDockPos.y - 25.0f);
			layer->addChild(chatBg);
			labelCnt->setZOrder(chatBg->getZOrder()+1);

			chatHeight += 30.0f;
			lblHeight += chatHeight;
		}
		
  
        switch (rd.m_nChatType )
        {
            case CHAT_TYPE_USER:
            case CHAT_TYPE_WORLD:
            {
                if (rd.m_strName == pData->getName())
                {
                    labelCnt->setColor(ccBLACK);//(ccGREEN);
                }
                else
                {
                    labelCnt->setColor(ccBLACK);//(CCCOLOR_GREEN);
                }
                break;
            }
			case CHAT_TYPE_NOTICE:
            case CHAT_TYPE_SYSTEM:
				{
					labelCnt->setColor(ccRED);
					break;
				}
            default:
                break;
        }
    }
    
    contentSize.height = lblHeight + winSize.height * ( ITEM_START_Y + (num - 1) * ITEM_SPACE_DELTA_Y );
    if (contentSize.height < winSize.height * CONTENT_VIEW_SIZE_Y)
    {
        contentSize.height = winSize.height * CONTENT_VIEW_SIZE_Y;
    }
    
    layer->setAnchorPoint( CCPointZero );
	layer->setPosition( CCPointZero );
	layer->setContentSize( contentSize );
    
	mContent->setViewSize(CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );//
	mContent->setContentSize( contentSize );
    
	mContent->setContainer( layer );
	mContent->setDirection( kCCScrollViewDirectionVertical );
	mContent->setPosition(ccp(winSize.width * CONTENT_POS_X,winSize.height * CONTENT_POS_Y));//
    addChild(mContent);
    

}


void ChatMessageUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}
    mRecordItems.clear();
    Record red;
    X_INT	num = DataPool::GetSingleton()->GetChatData()->GetMsgNumber(All_Channel);
    if (num == 0) return;

    for ( X_INT i = num - 1; i >=0; i--)
    {
        DataPool::GetSingleton()->GetChatData()->GetChatMsg(All_Channel, red,i);
        mRecordItems.push_back(red);
    }
    updateMsgContent();
}

void ChatMessageUIView::onButtonSendMsg(cocos2d::CCObject * pSender)
{
    sendMsg();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void ChatMessageUIView::itemCallBack( cocos2d::CCObject* pSender )
{
	if( mContent->mIsMoved )
		return;
}
void ChatMessageUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	vector<string> str;
	str.clear();
	str.push_back("close");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_CHATMESSAGE_SHOW,str);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}
void ChatMessageUIView::sendMsg()
{
 
	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();
	int curLvl = pData->GetLevel();

	if (curLvl < 3)
	{
		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(583),this,DIALOG_MODEL_SINGLE);
		addChild(dialog,10);
	}
	else
	{
		X_ULLONG tTimer = SystemTimer::GetSingleton()->GetNowTime();

		if ((tTimer - curTime)*0.001f >= SEND_MSG_MAX_TIME)
		{
			 if(SendLogicPacket::Chat(CHAT_TYPE_WORLD, pEditBox->getText()))
			 {
				 pEditBox->setText("");
				 curTime = tTimer;
			 }
		}
		else
		{
			 ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(585),this,DIALOG_MODEL_SINGLE);
			 addChild(dialog,10);
		}
	}

}

void ChatMessageUIView::editBoxEditingDidBegin(CCEditBox* editBox)
{
    
}
void ChatMessageUIView::editBoxEditingDidEnd(CCEditBox* editBox)
{
    
}

void ChatMessageUIView::editBoxTextChanged(CCEditBox* editBox, const std::string& text)
{
    
}

void ChatMessageUIView::editBoxReturn(CCEditBox* editBox)
{
     sendMsg();
}

void ChatMessageUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	return;
    if (pEditBox) {
         pEditBox->setText("");
    }
   

}








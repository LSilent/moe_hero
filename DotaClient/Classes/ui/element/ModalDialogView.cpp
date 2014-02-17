#include "ModalDialogView.h"
#include "./base/UtilTools.h"
#include "./object/Item.h"
#include "./ui/element/CCMenuEx.h"


ModalDialogView::ModalDialogView()
{
}

ModalDialogView::~ModalDialogView()
{
}

//
void ModalDialogView::initDialog()
{
	//todo	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *pSpriteBg = CCSprite::create("modeldlg_back.png");
	pSpriteBg->setPosition(ccp(winSize.width / 2 , winSize.height / 2));
    pSpriteBg->setScaleX(SCALE_X);
    pSpriteBg->setScaleY(SCALE_Y);
	this->addChild(pSpriteBg);

	CCSprite *pTipBg = CCSprite::create("com_text_back.png");
	pTipBg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.535));
    pTipBg->setScaleX(SCALE_X*0.8f);
    pTipBg->setScaleY(SCALE_Y*0.5f);
	this->addChild(pTipBg);

	CCSize lSize = CCSizeMake(winSize.width*0.70f, winSize.height *0.2);//0.2
	CCLabelTTF *label = CCLabelTTF::create(m_content.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24,lSize,kCCTextAlignmentCenter,kCCVerticalTextAlignmentCenter);
	label->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.54f));
// 	label->setDimensions(CCSizeMake(winSize.width*0.8, winSize.height *0.3));
// 	label->setHorizontalAlignment(kCCTextAlignmentCenter);
// 	label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
	this->addChild(label);
	label->setColor(CCCOLOR_RED);

	m_pMenu = CCMenu::create();
	addChild(m_pMenu);

	if (m_eModel == DIALOG_MODEL_DOUBLE)
	{

		CCMenuItemImage *comfireImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::comfireMenuItemCallback));
		comfireImage->setPosition(ccp(winSize.width * 0.27 , winSize.height * 0.430));
		m_pMenu->addChild(comfireImage);

		CCSprite *comSprite = CCSprite::create("n_dailog_ok.png");
		comSprite->setPosition(comfireImage->getPosition());
		comSprite->setScale(0.85f);
		this->addChild(comSprite);


		CCMenuItemImage *cancelImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::cancelMenuItemCallback));
		cancelImage->setPosition(ccp(winSize.width * 0.73 , winSize.height * 0.430));
		m_pMenu->addChild(cancelImage);

		CCSprite *canSprite = CCSprite::create("cancelText.png");
		canSprite->setPosition(cancelImage->getPosition());
		canSprite->setScale(0.85f);
		this->addChild(canSprite);
	}
	else if(m_eModel == DIALOG_MODEL_SINGLE)
	{
		CCMenuItemImage *comfireImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::comfireMenuItemCallback));
		comfireImage->setPosition(ccp(winSize.width * 0.5 , winSize.height * 0.430));
		m_pMenu->addChild(comfireImage);

		CCSprite *comSprite = CCSprite::create("n_dailog_ok.png");
		comSprite->setPosition(comfireImage->getPosition());
		this->addChild(comSprite);
	}


	m_pMenu->setPosition(CCPointZero);
}

ModalDialogView *ModalDialogView::createDialog(const std::string &des, ModalDialogDelegate *pDel , DialogModel eModel)
{
	ModalDialogView *pDialog = new ModalDialogView();

	if (pDialog)
	{
		pDialog->m_content = des;
		pDialog->m_pDialogDel = pDel;
		pDialog->m_eModel = eModel;
		pDialog->initDialog();

		pDialog->mDialogUserData = NULL;

		pDialog->autorelease();

		return pDialog;
	}
	
	CC_SAFE_DELETE(pDialog);
	return NULL;
}



void ModalDialogView::onEnter()
{
	cocos2d::CCLayer::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void ModalDialogView::onExit()
{
  	BaseView::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool ModalDialogView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);

	return true;
}

void ModalDialogView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) 
	{
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}

void ModalDialogView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void ModalDialogView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) 
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void ModalDialogView::closeDialogView()
{
	
	this->removeFromParentAndCleanup(true);

}

void ModalDialogView::comfireMenuItemCallback(cocos2d::CCObject *pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	if (m_pDialogDel)
	{
		m_pDialogDel->dialogDidClick(0, this);

		if (m_eModel ==  DIALOG_MODEL_SINGLE)
		{
			closeDialogView();
		}
	}else
	{
		if (m_eModel ==  DIALOG_MODEL_SINGLE)
		{
			closeDialogView();
		}
	}
}


void ModalDialogView::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
	//
// 	if (m_pDialogDel)
// 	{
// 		m_pDialogDel->dialogDidClick(1,this);
// 	}

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

	closeDialogView();

}



//----------------------------------------------


DialogBuyView::DialogBuyView()
{
	m_iMatNum = 1;
}

DialogBuyView::~DialogBuyView()
{
}

int DialogBuyView::getMatNum() const
{
	return m_iMatNum;
}
const Item *DialogBuyView::getItem() const
{
	return mItem;
}

DialogBuyView *DialogBuyView::createDialog(Item *pSender, ModalDialogDelegate *pDel,EM_SHOP_MONEY_TYPE  type )
{
	DialogBuyView *pDialog = new DialogBuyView();
	m_Buytype = type;

	if (pDialog)
	{
		pDialog->m_pDialogDel = pDel;
		pDialog->mItem = pSender;
        pDialog->m_eModel = DIALOG_MODEL_DOUBLE;
		pDialog->initDialog();
		pDialog->autorelease();
		return pDialog;
	}

	CC_SAFE_DELETE(pDialog);
	return NULL;
}

//	购买个数对话框
void DialogBuyView::initDialog()
{
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *pSpriteBg = CCSprite::create("modeldlg_back.png");
	pSpriteBg->setPosition(ccp(winSize.width / 2 , winSize.height / 2));
	pSpriteBg->setScaleY(SCALE_Y*1.5f);//1.5ff
    pSpriteBg->setScaleX(SCALE_X);
	this->addChild(pSpriteBg);

	CCSprite *pTipBg = CCSprite::create("top_tileback_s.png");
	pTipBg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.655));
	this->addChild(pTipBg);

	CCSprite *pBuyText = CCSprite::create("n_pur_text.png");
	pBuyText->setPosition(pTipBg->getPosition());
	this->addChild(pBuyText);


	X_CHAR str[128] ={0};
	sprintf(str,UtilTools::GET_TEXT_FROM_LANG(526),mItem->GetName());
	CCLabelTTF *label1 = CCLabelTTF::create(str,FONT_NAME_ARIAL_BOLD,FONT_SIZE_24,CCSizeMake(winSize.width*0.8, winSize.height *0.2),kCCTextAlignmentCenter);
	label1->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.51));
	this->addChild(label1);
	label1->setColor(CCCOLOR_RED);

	string sTip2;
	sTip2 = UtilTools::GET_TEXT_FROM_LANG(528);
	sTip2+=" ";
	if (mItem)
	{
		sTip2 += UtilTools::IntToString(mItem->GetPrice());
	}

	switch (m_Buytype)
	{
	case EM_SHOP_MONEY_TYPE_INVALID:
		break;
	case EM_SHOP_MONEY_GOLD:
		sTip2+=UtilTools::GET_TEXT_FROM_LANG(520);
		break;
	case EM_SHOP_MONEY_WOOD:
		sTip2+=UtilTools::GET_TEXT_FROM_LANG(644);
		break;
	case EM_SHOP_MONEY_NUMBER:
		break;
	default:
		break;
	}
	
	


	mGoldPrice = CCLabelTTF::create(sTip2.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24,CCSizeMake(winSize.width*0.8, winSize.height *0.2),kCCTextAlignmentCenter);
	mGoldPrice->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.475));
	this->addChild(mGoldPrice);

	mGoldPrice->setColor(CCCOLOR_RED);

	CCSprite *pNumText = CCSprite::create("subTitleBK.png");
	pNumText->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.49));
	pNumText->setScaleX(1.40f);
	this->addChild(pNumText);

	mGoldNum = CCLabelTTF::create(UtilTools::IntToString(m_iMatNum).c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24,CCSizeMake(winSize.width * 0.3,winSize.height * 0.2),kCCTextAlignmentCenter);
	mGoldNum->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.4));
	this->addChild(mGoldNum);

	//--------------------------------------------------------------------------

	//m_pMenu = CCMenu::create();
	//this->addChild(m_pMenu);

	m_pMenu  = CCMenuHoldEx::create();CCMenuHoldEx::mTime = 0.1f;
	this->addChild(m_pMenu);

	CCMenuItemImage *menuItemAdd = CCMenuItemImage::create( "n_sub_button.png", "n_sub_button.png", this, menu_selector(DialogBuyView::subCallBack) );  
	CCPoint itemAddPos = CCPointMake( winSize.width * 0.3, winSize.height * 0.49 ) ;
	menuItemAdd->setPosition( itemAddPos ); 
	m_pMenu->addChild( menuItemAdd );
 
 
	CCMenuItemImage *menuItemSub = CCMenuItemImage::create( "n_add_button.png", "n_add_button.png", this, menu_selector(DialogBuyView::addCallBack) );  
	CCPoint itemSubPos = CCPointMake( winSize.width * 0.7, winSize.height * 0.49 ) ;
	menuItemSub->setPosition( itemSubPos ); 
	m_pMenu->addChild( menuItemSub );
 
 

	CCMenuItemImage *comfireImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::comfireMenuItemCallback));
	comfireImage->setPosition(ccp(winSize.width * 0.27 , winSize.height * 0.38));
	m_pMenu->addChild(comfireImage);

	CCSprite *comSprite = CCSprite::create("n_dailog_ok.png");
	comSprite->setPosition(comfireImage->getPosition());
	this->addChild(comSprite);


	CCMenuItemImage *cancelImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::cancelMenuItemCallback));
	cancelImage->setPosition(ccp(winSize.width * 0.73 , winSize.height * 0.38));
	m_pMenu->addChild(cancelImage);

	CCSprite *canSprite = CCSprite::create("cancelText.png");
	canSprite->setPosition(cancelImage->getPosition());
	this->addChild(canSprite);

	m_pMenu->setPosition(CCPointZero);
	//m_pHoldMenu->setPosition(CCPointZero);
}
 ;

EM_SHOP_MONEY_TYPE DialogBuyView::m_Buytype = EM_SHOP_MONEY_GOLD;

void DialogBuyView::addCallBack( cocos2d::CCObject* pSender )
{
	m_iMatNum++;
	mGoldNum->setString(UtilTools::IntToString(m_iMatNum).c_str());

	string sTip2;
	sTip2 = UtilTools::GET_TEXT_FROM_LANG(528);
	sTip2+=" ";
	if (mItem)
	{
		sTip2 += UtilTools::IntToString( mItem->GetPrice() * m_iMatNum);
	}
	switch (m_Buytype)
	{
	case EM_SHOP_MONEY_TYPE_INVALID:
		break;
	case EM_SHOP_MONEY_GOLD:
		sTip2+=UtilTools::GET_TEXT_FROM_LANG(520);
		break;
	case EM_SHOP_MONEY_WOOD:
		sTip2+=UtilTools::GET_TEXT_FROM_LANG(644);
		break;
	case EM_SHOP_MONEY_NUMBER:
		break;
	default:
		break;
	}

	mGoldPrice->setString(sTip2.c_str());

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);//644
}

void DialogBuyView::subCallBack( cocos2d::CCObject* pSender )
{
	if (m_iMatNum > 0)
	{
		m_iMatNum--;
		mGoldNum->setString(UtilTools::IntToString(m_iMatNum).c_str());

		string sTip2;
		sTip2 = UtilTools::GET_TEXT_FROM_LANG(528);
		sTip2+=" ";
		if (mItem)
		{
			sTip2 += UtilTools::IntToString( mItem->GetPrice() * m_iMatNum);
		}

		switch (m_Buytype)
		{
		case EM_SHOP_MONEY_TYPE_INVALID:
			break;
		case EM_SHOP_MONEY_GOLD:
			sTip2+=UtilTools::GET_TEXT_FROM_LANG(520);
			break;
		case EM_SHOP_MONEY_WOOD:
			sTip2+=UtilTools::GET_TEXT_FROM_LANG(644);
			break;
		case EM_SHOP_MONEY_NUMBER:
			break;
		default:
			break;
		}
		 

		mGoldPrice->setString(sTip2.c_str());
	}
	
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}


//----------------------------------


GiftExchangeView::GiftExchangeView()
{
	 
}
GiftExchangeView::~GiftExchangeView()
{
}

const char* GiftExchangeView::getText() const
{
	return pEditBox->getText() ;
}
 
GiftExchangeView *GiftExchangeView::createDialog(ModalDialogDelegate *pDel )
{
	GiftExchangeView *pDialog = new GiftExchangeView();
	if (pDialog)
	{
		pDialog->m_pDialogDel = pDel;
		pDialog->m_eModel = DIALOG_MODEL_DOUBLE;
		pDialog->initDialog();
		pDialog->autorelease();
		return pDialog;
	}

	CC_SAFE_DELETE(pDialog);
	return NULL;
}
 
void GiftExchangeView::initDialog()
{

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *pSpriteBg = CCSprite::create("modeldlg_back.png");
	pSpriteBg->setPosition(ccp(winSize.width / 2 , winSize.height / 2));
	pSpriteBg->setScaleY(SCALE_Y *1.5f);//1.5ff
	pSpriteBg->setScaleX(SCALE_X);
	this->addChild(pSpriteBg);

	CCSprite *pTipBg = CCSprite::create("top_tileback_s.png");
	pTipBg->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.655));
	this->addChild(pTipBg);

	CCSprite *pgiftText = CCSprite::create("gift.png");
	pgiftText->setPosition(pTipBg->getPosition());
	this->addChild(pgiftText);

 
	CCLabelTTF *label1 = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(730),FONT_NAME_ARIAL_BOLD,FONT_SIZE_24,CCSizeMake(winSize.width*0.8, winSize.height *0.2),kCCTextAlignmentCenter);
	label1->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.505f));
	this->addChild(label1);
	label1->setColor(CCCOLOR_RED);
	  
	CCSprite *editback = CCSprite::create("chat_editbox_back.png");
	pEditBox = cocos2d::extension::CCEditBox::create(CCSizeMake(editback->getContentSize().width, winSize.height * 0.06f), cocos2d::extension::CCScale9Sprite::create("n_op_0.png"));
	pEditBox->setReturnType(cocos2d::extension::kKeyboardReturnTypeDone);

	pEditBox->setDelegate(this);
	pEditBox->setFontColor(ccWHITE);
	pEditBox->setMaxLength(8);
 
	
	editback->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	this->addChild(editback);
	editback->addChild(pEditBox);
	pEditBox->setPosition(CCPointMake( editback->getContentSize().width * 0.5f, editback->getContentSize().height * 0.5f));;

	m_pMenu = CCMenu::create();
	this->addChild(m_pMenu);
	 
	CCMenuItemImage *comfireImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::comfireMenuItemCallback));
	comfireImage->setPosition(ccp(winSize.width * 0.27 , winSize.height * 0.4));
	m_pMenu->addChild(comfireImage);

	CCSprite *comSprite = CCSprite::create("n_dailog_ok.png");
	comSprite->setPosition(comfireImage->getPosition());
	this->addChild(comSprite);


	CCMenuItemImage *cancelImage = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(ModalDialogView::cancelMenuItemCallback));
	cancelImage->setPosition(ccp(winSize.width * 0.73 , winSize.height * 0.4));
	m_pMenu->addChild(cancelImage);

	CCSprite *canSprite = CCSprite::create("cancelText.png");
	canSprite->setPosition(cancelImage->getPosition());
	this->addChild(canSprite);
	m_pMenu->setPosition(CCPointZero);
}
void GiftExchangeView::editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox)
{

}
void GiftExchangeView::editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox)
{

}

void GiftExchangeView::editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text)
{

}

void GiftExchangeView::editBoxReturn(cocos2d::extension::CCEditBox* editBox)
{

}
bool GiftExchangeView::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
	if (!m_bTouchedMenu)
	{
		pEditBox->ccTouchBegan(pTouch, pEvent);
	}
 
	return true;
}

void GiftExchangeView::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) 
	{
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
	else pEditBox->ccTouchMoved(pTouch, pEvent);
}

void GiftExchangeView::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu)
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
	else  pEditBox->ccTouchEnded(pTouch, pEvent);
}

void GiftExchangeView::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) 
	{
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
	else  pEditBox->ccTouchEnded(pTouch, pEvent);
}
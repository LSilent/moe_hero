#include "./ui/giftDetailUIView.h"
#include "./ui/giftDetailUI.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./game/GameHelper.h"
#include "./DataBase/DataBaseSystem.h"
#include "./object/ObjectManager.h"
#include "./datapool/DataPool.h"

#define CONTENT_POS_X            (0.060f)
#define CONTENT_POS_Y            (0.250f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.41f)

#define ITEM_DOCK_X              (0.44f)
#define ITEM_SPACE_DELTA_Y       (0.175f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

//用于文字叙述的尺寸
#define ICON_SMALL_POS_X		(0.17f)

#define ICON_LABEL_POS_X		(0.21f)
#define ICON_LABEL_DELAY_X		(0.40f)

#define ICON_LABEL_POS_Y		(0.55f)
#define ICON_LABEL_DELAY_Y		(-0.06f)
//用于装备获取的尺寸
#define ITEM_POS_START_X			(0.21f)
#define ITEM_POS_DELAY_X			(0.145f)
#define ITEM_POS_Y			(0.42f)

#define MENU_POS_Y			(0.31f)

using namespace cocos2d;
USING_NS_CC_EXT;
 
giftDetailUIView::giftDetailUIView()
 
{ 
	
}

giftDetailUIView::~giftDetailUIView()
{ 
}

bool giftDetailUIView::init()
{
	

    bool bRet = true;

	return bRet;
}

 
void giftDetailUIView::onDataUpdate( bool isDataValid )
{
	CCLayerColor *colorLayer = CCLayerColor::create(ccc4(0,0,0,175));
	addChild(colorLayer);

	giftDetailUI *pUi = (giftDetailUI *)( this->getUserData());
	X_INT gif = pUi->giftId;
	//兑换失败
	if (gif == -1)
	{
		updataFailed();
		return;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *detailBg = CCSprite::create("qj_yybzk.png");
	detailBg->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.5f));
	detailBg->setScaleY(1.2f * SCALE_Y);
	detailBg->setScaleX(SCALE_X);
	addChild(detailBg);

	CCSprite *successTitile = CCSprite::create("gidt_ok.png");
	successTitile->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.5f + detailBg->getContentSize().height * 0.5f));
	addChild(successTitile);

	CCSprite *itemsBg = CCSprite::create("com_text_back.png");
	itemsBg->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.48f));
	itemsBg->setScaleY(SCALE_Y);
	itemsBg->setScaleX(SCALE_X);
	addChild(itemsBg);

	string des = UtilTools::GET_TEXT_FROM_LANG(731);

	CCLabelTTF *desLabel = CCLabelTTF::create();
	desLabel->setFontName(FONT_NAME_ARIAL_BOLD);
	desLabel->setFontSize(FONT_SIZE_24);
	desLabel->setColor(CCCOLOR_RED);
	desLabel->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.64f));
	desLabel->setString(des.c_str());
	addChild(desLabel);

	string str = "";
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_GIFT_PACKET);
	const stDBC_FILE_GIFT_PACKET *pData =  (const stDBC_FILE_GIFT_PACKET *) pDataFile->GetFieldsByIndexKey(gif);
	if (!pData)return;

	//金币。。。
	string gold = UtilTools::GET_TEXT_FROM_LANG(517);
	gold += " : ";
	gold += UtilTools::IntToString(pData->gold);

	CCSprite *goldSprite = CCSprite::create("goldCoin.png");
	goldSprite->setPosition(ccp(winSize.width * ICON_SMALL_POS_X, winSize.height * ICON_LABEL_POS_Y));
	addChild(goldSprite);

	CCLabelTTF *goldLabel = CCLabelTTF::create();
	goldLabel->setFontName(FONT_NAME_ARIAL_BOLD);
	goldLabel->setFontSize(FONT_SIZE_24);
	goldLabel->setColor(CCCOLOR_RED);
	goldLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	goldLabel->setPosition(ccp(winSize.width * ICON_LABEL_POS_X, winSize.height * ICON_LABEL_POS_Y));
	goldLabel->setString(gold.c_str());
	addChild(goldLabel);

	//体力。。。
	string action = UtilTools::GET_TEXT_FROM_LANG(591);
	action += " : ";
	action += UtilTools::IntToString(pData->action);

	CCSprite *actionSprite = CCSprite::create("cheese.png");
	actionSprite->setPosition(ccp(winSize.width * (ICON_SMALL_POS_X + ICON_LABEL_DELAY_X), winSize.height * ICON_LABEL_POS_Y));
	addChild(actionSprite);

	CCLabelTTF *actionLabel = CCLabelTTF::create();
	actionLabel->setFontName(FONT_NAME_ARIAL_BOLD);
	actionLabel->setFontSize(FONT_SIZE_24);
	actionLabel->setColor(CCCOLOR_RED);
	actionLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	actionLabel->setPosition(ccp(winSize.width * (ICON_LABEL_POS_X + ICON_LABEL_DELAY_X), winSize.height * ICON_LABEL_POS_Y));
	actionLabel->setString(action.c_str());
	addChild(actionLabel);


	//木头。。。
	string wood = UtilTools::GET_TEXT_FROM_LANG(644);
	wood += " : ";
	wood += UtilTools::IntToString(pData->wood);

	CCSprite *woodSprite = CCSprite::create("wood.png");
	woodSprite->setPosition(ccp(winSize.width * ICON_SMALL_POS_X, winSize.height * (ICON_LABEL_POS_Y + ICON_LABEL_DELAY_Y)));
	addChild(woodSprite);

	CCLabelTTF *woodLabel = CCLabelTTF::create();
	woodLabel->setFontName(FONT_NAME_ARIAL_BOLD);
	woodLabel->setFontSize(FONT_SIZE_24);
	woodLabel->setColor(CCCOLOR_RED);
	woodLabel->setAnchorPoint(ccp(0.0f, 0.5f));
	woodLabel->setPosition(ccp(winSize.width * ICON_LABEL_POS_X, winSize.height * (ICON_LABEL_POS_Y + ICON_LABEL_DELAY_Y)));
	woodLabel->setString(wood.c_str());
	addChild(woodLabel);

	vector<X_INT> items,itemNus;
	UtilTools::ConvertStringToIntVector(pData->items1,items,"|");
	UtilTools::ConvertStringToIntVector(pData->items2,itemNus,"|");

	X_INT num = items.size();
	for (X_INT i = 0;i<num;i++)
	{
		string name,color,icon;X_INT level;
		
		if(!DataPool::GetSingleton()->getObjectManager()->getItemInfoById(items[i],name,color,icon,level))
			continue;
			
		CCSprite *item = CCSprite::create( icon.c_str() );
		CCPoint itemDocPos = ccp(winSize.width * (ITEM_POS_START_X + i * ITEM_POS_DELAY_X), winSize.height * ITEM_POS_Y);
		item->setPosition(itemDocPos);
		addChild( item );	
		item->setScale(0.8f); 

		CCSprite *itemBg = CCSprite::create("equipmentBK.png");
		itemBg->setPosition(item->getPosition());
		addChild(itemBg);

		CCSprite *pLevel = GameHelper::getSpriteLevel(level);
		if (pLevel)
		{
			pLevel->setPosition( item->getPosition() ); 
			addChild(pLevel);
			pLevel->setZOrder(100);
			pLevel->setScale(0.8f);
		}  
		if (itemNus[i] > 0)
		{
			string tempStr = UtilTools::IntToString(itemNus[i]);
			CCLabelBMFont *numLable = CCLabelBMFont::create(tempStr.c_str(), FNT_NUM_LARGEWHITE);
			numLable -> setAnchorPoint(ccp(0.5f, 0.5f));
			numLable -> setPosition(ccpAdd(item->getPosition(), ccp(item->getContentSize().width* 0.4f, item->getContentSize().height * -0.4f)));
			numLable -> setScale(0.5f);
			addChild(numLable);
		}
	
	}
	//确定按钮
	CCMenu *menu = CCMenu::create();
	CCMenuItemImage *okBtn = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(giftDetailUIView::onButtonOK));
	okBtn->setPosition(ccp(winSize.width * 0.5 , winSize.height * MENU_POS_Y));
	menu->addChild(okBtn);
	addChild(menu);
	menu->setPosition(CCPointZero);

	CCSprite *btnTitle = CCSprite::create("n_dailog_ok.png");
	btnTitle->setPosition(okBtn->getPosition());
	addChild(btnTitle);
 
}
void giftDetailUIView::onButtonOK(cocos2d::CCObject* pSender)
{
	vector<string>str;str.clear();
	str.push_back("close");
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_GIFTDETAIL_SHOW,str);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void giftDetailUIView::updataFailed()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *detailBg = CCSprite::create("qj_yybzk.png");
	detailBg->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.5f));
	detailBg->setScaleY(1.2f * SCALE_Y);
	detailBg->setScaleX(SCALE_X);
	addChild(detailBg);

	CCSprite *failedTitile = CCSprite::create("gift_failed.png");
	failedTitile->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.5f + detailBg->getContentSize().height * 0.5f));
	addChild(failedTitile);

	CCSprite *itemsBg = CCSprite::create("com_text_back.png");
	itemsBg->setPosition(ccp(winSize.width *0.5f, winSize.height * 0.5f));
	detailBg->setScaleY(SCALE_Y);
	detailBg->setScaleX(SCALE_X);
	addChild(itemsBg);

	string des = UtilTools::GET_TEXT_FROM_LANG(732);

	CCLabelTTF *desLabel = CCLabelTTF::create();
	desLabel->setFontName(FONT_NAME_ARIAL_BOLD);
	desLabel->setFontSize(FONT_SIZE_24);
	desLabel->setColor(CCCOLOR_RED);
	desLabel->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
	desLabel->setString(des.c_str());
	addChild(desLabel);

	//确定按钮
	CCMenu *menu = CCMenu::create();
	CCMenuItemImage *okBtn = CCMenuItemImage::create("n_home_button.png","n_home_button_sel.png",  this, menu_selector(giftDetailUIView::onButtonOK));
	okBtn->setPosition(ccp(winSize.width * 0.5 , winSize.height * MENU_POS_Y));
	menu->addChild(okBtn);
	addChild(menu);
	menu->setPosition(CCPointZero);

	CCSprite *btnTitle = CCSprite::create("n_dailog_ok.png");
	btnTitle->setPosition(okBtn->getPosition());
	addChild(btnTitle);
}


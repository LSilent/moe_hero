#include "./ui/achievementUIView.h"
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


#include "./ui/achievementUI.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (512)

#define CONTENT_POS_X            (0.070f)
#define CONTENT_POS_Y            (0.187f)

#define CONTENT_VIEW_SIZE_X      (0.89f)
#define CONTENT_VIEW_SIZE_Y      (0.700f)

#define ITEM_DOCK_X              (0.44f)//(0.44f)
#define ITEM_SPACE_DELTA_Y       (0.185f)
#define ITEM_START_Y             (ITEM_SPACE_DELTA_Y * -0.5f)

#define ITEM_SPACE_DELTA_X_MAIN       (0.35f)
#define ITEM_START_X_MAIN             (ITEM_SPACE_DELTA_X_MAIN * 0.730f)
#define ITEM_SPACE_DELTA_Y_MAIN       (0.227f)
#define ITEM_START_Y_MAIN             (ITEM_SPACE_DELTA_Y_MAIN * -0.5f)


#define ITEM_IMAGE_OFFSET_X      (-0.28f)
#define ITEM_IMAGE_OFFSET_Y      (0.0011f)

#define ITEM_UPGRADE_OFFSET_X    (0.30f)
#define ITEM_UPGRADE_OFFSET_Y    (0.032f)//(0.030f)

#define ITEM_EVOLVE_OFFSET_X     (0.27f)
#define ITEM_EVOLVE_OFFSET_Y     (-0.005f)

#define ITEM_DESC_OFFSET_X       (-0.19f)
#define ITEM_DESC_OFFSET_Y       (0.01f)//(-0.000f)

#define ITEM_TEXT_SIZE_X         (0.38f)
#define ITEM_TEXT_SIZE_Y         (0.08f)

#define ITEM_PROGRESS_OFFSET_X   (0.03f)


#define ACHIEVE_DONENUMLABLE_TAG   1000

achievementUIView::achievementUIView()
: mMainStatus(NULL)
{
	mContent = NULL;

	guideMenuItem = NULL;

	guideLayer = NULL;

	mtitle = NULL;
	mSubtitle = NULL;
	mAchieveBlackBack = NULL;
}

achievementUIView::~achievementUIView()
{
    CC_SAFE_RELEASE(mMainStatus);
	CC_SAFE_RELEASE(mtitle);
	CC_SAFE_RELEASE(mAchieveBlackBack);
}


void achievementUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
	
}

SEL_MenuHandler achievementUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", achievementUIView::onButtonClose);
	return NULL;    
}
void achievementUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());
	if (pUi->m_layer ==  -1)
	{
		vector<string>str;
		str.clear();
		str.push_back("close");
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_ACHIEVE_SHOW,str);
	}else
	{
		pUi->m_layer  =  -1;
		updataMain();
	}
}

void achievementUIView::onButtonAchieveGroup(cocos2d::CCObject * pSender)
{
	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());
	pUi->m_layer =(X_INT) ((CCNode *)pSender) ->getUserData();
	updataSingle();
}
void achievementUIView::onButtonAchieveGroupGuide(cocos2d::CCObject* pSender)
{
	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());
	pUi->m_layer = 0;
	updataSingle();
}

SEL_CCControlHandler achievementUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}
void achievementUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;

	Achieve *pAch = (Achieve *)((CCNode *)pSender)->getUserData();

	SendLogicPacket::RequestAchievement(pAch->getId());

	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}



bool achievementUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mtitle", CCSprite *, this->mtitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAchieveBlackBack", CCSprite *, this->mAchieveBlackBack);
	
	return false;
}

bool achievementUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
    return bRet;
}

// on "init" you need to initialize your instance
bool achievementUIView::init()
{
    bool bRet = true;
	
    return bRet;
}
X_VOID achievementUIView::updataMain()
{
	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}
	 
	mtitle->setVisible(true);
	mAchieveBlackBack->setVisible(true);
	if (mSubtitle)
	{
		mSubtitle->setVisible(false);
	}
	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());
	if (!pUi)
	{
		return;
	}

	X_INT layerNums = DataPool::GetSingleton()->getAchievementData()->getAchievesLayerNum();

	vector<X_INT> ids = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupIds();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx *menu = CCMenuEx::create(); 

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * layerNums/2 * ITEM_SPACE_DELTA_Y_MAIN );

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;

	const stDBC_FILE_ACHIEVE_GROUP	* pTable = 0;
	for (X_INT k = 0;k < layerNums;k++)
	{
		 pTable = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupTbaleData(ids[k]);
		 if (!pTable)
		 {
			 continue;
		 }

		 CCPoint itemDockPos = CCPointMake( winSize.width * ( ITEM_START_X_MAIN + k%2 * ITEM_SPACE_DELTA_X_MAIN ), winSize.height * ( ITEM_START_Y_MAIN - k/2 * ITEM_SPACE_DELTA_Y_MAIN ) + contentSize.height );
		 
		 CCSprite *back  = CCSprite::create("AchieveBack.png");
		 back->setPosition( itemDockPos ); 
		 layer->addChild( back);


		 CCMenuItemImage * menuItem = CCMenuItemImage::create( pTable->icon, pTable->icon, this, menu_selector(achievementUIView::onButtonAchieveGroup) );  
		 menuItem->setPosition( itemDockPos ); 
		 menuItem->setUserData((void *)ids[k]);
		 menu->addChild( menuItem );
		 
		

		 CCPoint itemNamePoc= ccpSub(itemDockPos, ccp(0, menuItem->getContentSize().height * 0.45f));

		 CCSprite *nameText = CCSprite::create( pTable->text );
		 nameText->setPosition( itemNamePoc );
		 layer->addChild( nameText, 10 );
		  
		 X_BOOL groupIsNull = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupisNull(ids[k]);
		 if (groupIsNull)
		 {
			 menuItem ->setEnabled(false);
			 menuItem ->setColor(ccGRAY);
			 continue;
		 }
		 
		 //上角标
		
		 X_INT   doneNum = 0;
		  X_INT   allNum =  0;
		 if (!groupIsNull)
		 {
			 doneNum = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupDoneNum(ids[k]);
			 allNum = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupAllNum(ids[k]);
		 }
		 if (doneNum > 0)
		 {
			 CCPoint itemNumPoc= ccpAdd(itemDockPos, ccp(menuItem->getContentSize().width *0.35f, menuItem->getContentSize().height * 0.35f));
			 CCSprite *numText = CCSprite::create( "Achieve_num.png" );
			 numText->setPosition(itemNumPoc);

			 layer->addChild( numText, 10 );

			 char aText[MAX_STRING_BUFF_SIZE];
			// sprintf( aText, "%d / %d", doneNum,allNum);
			 sprintf( aText, "%d", doneNum);
			 CCLabelBMFont *mLable = CCLabelBMFont::create(aText, FNT_NAME_LARGEGREEN);
			 mLable -> setAnchorPoint(ccp(0.5f, 0.5f));
			 mLable -> setPosition(CCPoint(numText->getContentSize().width*0.5f,numText->getContentSize().height*0.5f));
			 mLable -> setScale(0.5f);
			 numText -> addChild(mLable,numText->getZOrder() + 1);
			 if (doneNum > 0)
			 {
				 numText->runAction(CCRepeat::create(
					 CCSequence::create(
					 CCScaleTo::create(0.5f, 1.2f),
					 CCScaleTo::create(0.5f, 1.0f),
					 NULL
					 ),
					 kCCRepeatForever
					 ));
			 }
		 }
	}
	X_INT tipId = ((achievementUI *)this->getUserData())->getTipId();

	if (tipId != -1 )
	{ 

		if (!guideLayer)
		{
			//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();

			switch (tipId)
			{
			case 27:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(achievementUIView::onButtonAchieveGroupGuide),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
			}
		}
	}
	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero ); 
	layer->addChild( menu );

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	addChild( mContent );

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
	
}
X_VOID achievementUIView::updataSingle()
{

	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());
	if (!pUi)
	{
		return;
	}

	const  DataBase* pDataFile_Group  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_ACHIEVE_GROUP);
	const stDBC_FILE_ACHIEVE_GROUP	* pTableData_Group = (const stDBC_FILE_ACHIEVE_GROUP*)pDataFile_Group->GetFieldsByIndexKey(pUi->m_layer);
	if (mSubtitle)
	{
		mSubtitle->getParent()->removeChild(mSubtitle,true);
		mSubtitle = 0;
	}
	if (pTableData_Group)
	{
		mSubtitle = CCSprite::create(pTableData_Group->textBig);
		mtitle->getParent()->addChild(mSubtitle);
		
	}
	mtitle->setVisible(false);
	mAchieveBlackBack->setVisible(false);
	if (mSubtitle)
	{
		mSubtitle->setPosition(mtitle->getPosition());
		mSubtitle->setAnchorPoint(mtitle->getAnchorPoint());
		mSubtitle->setVisible(true);
	}
	
	if( mContent )
	{
		mContent->removeFromParentAndCleanup( true );
		mContent = NULL;
	}
	vector<const Achieve *> pAchieveItems = DataPool::GetSingleton()->getAchievementData()->getAchievesWithGroup( pUi->m_layer);
	unsigned int size = pAchieveItems.size();
	if(size == 0) return;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mContent = CCScrollViewEx::create();  
	CCLayer *layer = CCLayer::create(); 
	CCMenuEx *menu = CCMenuEx::create(); 

	CCSize contentSize( winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * size * ITEM_SPACE_DELTA_Y );

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;
	CCMenuItemImage *menuItemGet_tip = NULL;
	  Achieve *pAch = NULL;
	unsigned int i = 0;
	for( ; i < size; i++ )
	{
		pAch =  const_cast< Achieve *> (pAchieveItems.at(i));
		if (!pAch)
		{
			continue;
		}

		CCSprite *itemBackGround = CCSprite::create( "levelFrame.png" );
		CCPoint itemDockPos = CCPointMake( winSize.width * ITEM_DOCK_X, winSize.height * ( ITEM_START_Y - i * ITEM_SPACE_DELTA_Y ) + contentSize.height );
		itemBackGround->setScaleX(SCALE_X);
		itemBackGround->setScaleY(SCALE_Y);
		layer->addChild( itemBackGround );
		itemBackGround->setPosition( itemDockPos );

		CCPoint itemImagePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_IMAGE_OFFSET_X, winSize.height * ITEM_IMAGE_OFFSET_Y ) );

		CCSprite *equipBG = CCSprite::create("equipmentBK.png");
		equipBG->setPosition(itemImagePos);

		CCSprite *acIconBG = CCSprite::create(pAch->getIcon());
		acIconBG->setPosition(itemImagePos);
		acIconBG->setScale(0.80f);
		layer->addChild(acIconBG);
		layer->addChild(equipBG);



		// 			EM_ACHIEVE_STATUS_NOT_COMPLETE = 0,	// 已接未完成
		// 			EM_ACHIEVE_STATUS_NOT_SUBMIT,		// 完成未交
		// 			EM_ACHIEVE_STATUS_DONE,				// 完成已交
		// 			EM_ACHIEVE_STATUS_NUMBER,

		CCPoint itemEvolvePos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_EVOLVE_OFFSET_X, winSize.height * ITEM_EVOLVE_OFFSET_Y ) );

		if (pAch->getStatus() == EM_ACHIEVE_STATUS_NOT_SUBMIT)
		{
			CCMenuItemImage * menuItemGet = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(achievementUIView::itemInfoCallBack) );  
			menuItemGet->setPosition( itemEvolvePos ); 
			menuItemGet->setScale(0.75f); //0.65f
			menuItemGet->setUserData(pAch);
			menu->addChild( menuItemGet );

			CCSprite *getText = CCSprite::create( "n_av_get_text.png" );
			getText->setPosition( itemEvolvePos );
			layer->addChild( getText, 10 );

			if (menuItemGet_tip ==X_NULL)
			{
				menuItemGet_tip = menuItemGet;
			}

		}
		else
		{
			//n_achieve_runing.png
			CCSprite *acRun = CCSprite::create("n_achieve_runing.png");
			acRun->setPosition(itemEvolvePos);
			layer->addChild(acRun);
		}



		CCLabelTTF* mName = CCLabelTTF::create( pAch->getName(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mName->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemDescPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * ITEM_DESC_OFFSET_Y ) );
		mName->setPosition( itemDescPos );
		mName->setColor(CCCOLOR_YELLOW);
		layer->addChild( mName );


		CCLabelTTF* mDesc = CCLabelTTF::create(pAch->getDesc().c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 ,CCSizeMake( winSize.width * (0.38f), winSize.height * 0.1 ), kCCTextAlignmentLeft );
		mDesc->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemlvlPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_DESC_OFFSET_X, winSize.height * (-0.030f) ) );
		mDesc->setPosition( itemlvlPos );
		mDesc->setColor(CCCOLOR_GREEN);
		layer->addChild( mDesc );

		string sNum = UtilTools::GET_TEXT_FROM_LANG(584);
		sNum += UtilTools::IntToString(pAch->getTimes());
		sNum += "/";
		sNum += UtilTools::IntToString(pAch->getAllTimes());

		CCLabelTTF* mNum = CCLabelTTF::create(sNum.c_str(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, CCSizeMake( winSize.width * ITEM_TEXT_SIZE_X, winSize.height * ITEM_TEXT_SIZE_Y ), kCCTextAlignmentLeft );
		mNum->setAnchorPoint( ccp( 0, 0.5f ) );
		CCPoint itemExpPos = ccpAdd( itemDockPos, CCPointMake( winSize.width * ITEM_PROGRESS_OFFSET_X, winSize.height * (-0.073f) ) );
		mNum->setPosition( itemExpPos );
		mNum->setColor(CCCOLOR_WHITE);
		layer->addChild( mNum );

	}

	X_INT tipId = ((achievementUI *)this->getUserData())->getTipId();

	if (tipId != -1 )
	{ 

		if (!guideLayer)
		{
			//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();

			switch (tipId)
			{
			case 28:

				if(menuItemGet_tip == NULL){ break;}

				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(achievementUIView::itemInfoCallBack),menuItemGet_tip);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 29:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(achievementUIView::guideEndBattle),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				break;
			}
		}
	}

	layer->setAnchorPoint( CCPointZero );  
	layer->setPosition( CCPointZero );  
	layer->setContentSize( contentSize ); 

	menu->setPosition( CCPointZero ); 
	layer->addChild( menu );

	mContent->setViewSize( CCSizeMake(winSize.width * CONTENT_VIEW_SIZE_X, winSize.height * CONTENT_VIEW_SIZE_Y) );
	mContent->setContentSize( contentSize ); 

	mContent->setContainer( layer );

	mContent->setDirection( kCCScrollViewDirectionVertical );

	mContent->setPosition( CCPointMake( winSize.width * CONTENT_POS_X, winSize.height * CONTENT_POS_Y ) );

	mContent->setContentOffset( mContent->minContainerOffset() );

	addChild( mContent );

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}

}
void achievementUIView::onDataUpdate( bool isDataValid )
{
	
	
	vector<X_INT> ids = DataPool::GetSingleton()->getAchievementData()->getAchievesGroupIds();
	achievementUI *pUi = static_cast<achievementUI *> (this->getUserData());

	if (pUi->m_layer ==  -1)
	{
		updataMain();
	}else
	{
		updataSingle();
	}
}

void achievementUIView::guideEndBattle(cocos2d::CCObject *pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_SHOW);

	guideLayer = NULL;
}
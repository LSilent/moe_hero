#include "./ui/levelListUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"

#include "./ui/levelListUI.h"
#include "./game/GameHelper.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_TITLE_POS_X            (0.105f)
#define CONTENT_TITLE_POS_Y            (0.730f)//(0.740f)

#define CONTENT_TITLE_VIEW_SIZE_X      (0.766f)//(0.940f)
#define CONTENT_TITLE_VIEW_SIZE_Y      (0.085f)//(0.075f)

#define  ITEM_TITLE_SPACE_DELTA_X      (0.255f)
#define ITEM_TITLE_SPACE_DELTA_Y       (CONTENT_TITLE_VIEW_SIZE_Y)

#define ITEM_TITLE_START_X             (0.13f)
#define ITEM_TITLE_START_Y             (0.03f)//(0.04f)

#define CONTENT_LIST_POS_X             (0.033f)
#define CONTENT_LIST_POS_Y             (0.190f)//(0.155f)

#define CONTENT_LIST_VIEW_SIZE_X       (0.940f)
#define CONTENT_LIST_VIEW_SIZE_Y       (0.530f)//(0.575f)

#define ITEM_LIST_SPACE_DELTA_X        (CONTENT_LIST_VIEW_SIZE_X)
#define ITEM_LIST_SPACE_DELTA_Y        (0.168f)

#define ITEM_LIST_START_X              (0.46f)
#define ITEM_LIST_START_Y              (ITEM_LIST_SPACE_DELTA_Y * -0.5f)

#define ITEM_RUSH_OFFSET_X             (0.15f)
#define ITEM_RUSH_OFFSET_Y             (-0.025f)

#define ITEM_ICON_OFFSET_X             (-0.26f)
#define ITEM_ICON_OFFSET_Y             (0)

#define ITEM_NAME_OFFSET_X             (-0.13f)
#define ITEM_NAME_OFFSET_Y             (0)

#define ITEM_STAR_OFFSET_X             (-0.10f)//(0.20f)
#define ITEM_STAR_OFFSET_Y             (0.035f)

#define ITEM_INFO_BK_OFFSET_Y          (-0.25f)
#define ITEM_INFO_OFFSET_Y             (-0.18f)


#define DIALOG_TAG_CHALLENGE_NUM				200
#define DIALOG_TAG_ACTION			201
#define DIALOG_TAG_GOLD			202

#define HEADICON_SCALE_X	(0.15f)
#define HEADICON_SCALE_Y	(0.15f)

#define SECONDLINE_LABLE_OFFSET_Y		(-0.25f)
#define THIRDLINE_LABLE_OFFSET_Y		(-0.28f)
#define FOURTHLINE_LABLE_OFFSET_Y		(-0.32f)

#define SCREEN_SIZE CCDirector::sharedDirector()->getWinSize()
#define SCALE_X  SCREEN_SIZE.width / 640
#define SCALE_Y  SCREEN_SIZE.height / 960

#define SCALE_TITLE_ITEM  (SCALE_X * 1.05f)



LevelListUIView::LevelListUIView()
: mMainStatus(NULL)
{
	mContentNode = NULL;
	mCurGroupScene = NULL;
	mCurCopyScene = NULL;

// 	CopySceneManager* pManger = DataPool::GetSingleton()->getCopySceneManager();
// 	mCurGroupScene = pManger->getCurSceneGroup();


	offset_ = CCPointZero;
	sceneOffset_ = CCPointZero;
	startFlag = false;

	guideLayer = NULL;
}

LevelListUIView::~LevelListUIView()
{
	CC_SAFE_RELEASE(mMainStatus);

	UI *pUi = ( UI *)(this->getUserData());
	if (pUi)
	{
		pUi->ReleaseUI();
		UISystem::GetSingleton()->CleanShowList(pUi);
	}

}


void LevelListUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler LevelListUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	return NULL;    
}

SEL_CCControlHandler LevelListUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool LevelListUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mMainStatus", MainStatusView *, this->mMainStatus);

	return false;
}

bool LevelListUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool LevelListUIView::init()
{
    bool bRet = true;

	return bRet;
}

void LevelListUIView::onDataUpdate( bool isDataValid )
{
	mMainStatus->onDataUpdate( isDataValid );

	if( !isDataValid )
	{
		return;
	}
	DataPool::GetSingleton()->BattlyType = EM_COPY_SCENE;
	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	CopySceneManager* pManger = DataPool::GetSingleton()->getCopySceneManager();

	vector<CopySceneGroup*> pGroups =  pManger->getSceneGroups();
	X_UINT group_size  = pGroups.size();
	const CopySceneGroup* pGroupItem = X_NULL;
	
	mCurGroupScene = pManger->getCurSceneGroup();	
	mCurCopyScene = pManger->getCurScene();
	/*if (mCurCopyScene)
	{
		CopySceneGroup *pGroup;
		pManger->findCopySceneByID(mCurCopyScene->getID(),pGroup);
		mCurGroupScene = pGroup;
	}*/
	if (!mCurGroupScene)
	{
		return;
	}

	vector<CopyScene*>	pSecnes = mCurGroupScene->getScenes();
	reverse(pSecnes.begin(),pSecnes.end());
	CopyScene* pScene = X_NULL;
	X_UINT sceneSize  = pSecnes.size();

	// update view
	mContentNode = CCNode::create();
	addChild( mContentNode );

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize contentSize( 0, 0 );
	// for level title
	mContent_title = CCScrollViewEx::create();  
	CCLayer *layer_title = CCLayer::create(); 
	
	CCMenuEx *menuTitle = CCMenuEx::create(); 
	contentSize.height = winSize.height * ITEM_TITLE_SPACE_DELTA_Y;
	for(X_UINT i = 0;i<group_size;i++ )
	{
		pGroupItem = pGroups[i];

		if(pGroupItem->getGroupID() == HUODONG_COPYSCENE_GROUP) continue;
		CCMenuItemImage *menuItem = CCMenuItemImage::create( "n_levellist_btn.png", "n_button_seledBig.png", this, menu_selector(LevelListUIView::titleCallBack) );  
		CCPoint itemPos = CCPointMake( winSize.width * ( ITEM_TITLE_START_X + i * ITEM_TITLE_SPACE_DELTA_X ), winSize.height * (ITEM_TITLE_START_Y));
		menuItem->setPosition( itemPos ); 
		menuItem->setScaleX( SCALE_TITLE_ITEM );
		CCLabelTTF *groupText = CCLabelTTF::create( pGroupItem->getName(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		groupText->setPosition( itemPos );
		groupText->setColor(ccYELLOW);
		layer_title->addChild( groupText, 10 );
		CCSprite *allClearSprite = CCSprite::create("allStarClear.png");
		allClearSprite->setPosition( ccpAdd(itemPos,ccp(0, 11.0f)) );
		allClearSprite->setVisible(false);
		//layer_title->addChild( allClearSprite, 9 );


		//5星通关显示
		vector<CopyScene*>	tempSecnes = pGroupItem->getScenes();
		int tempScenesSize = tempSecnes.size();
		int flagOfAllClear = 1;
		for (int i = 0; i < tempScenesSize; i++)
		{
			CopyScene* tempScene = tempSecnes[i];
			if (!tempScene)
			{
				return;
			}
			
			int tempStar = tempScene->getStar();
			if (tempStar < 5)
			{
				flagOfAllClear = 0;
				break;
			}
		}
		if (flagOfAllClear)
		{
			allClearSprite->setVisible(true);
		}

		
		if( !pGroupItem->isEnable() )
		{
				menuItem->setEnabled(false);
				menuItem->setColor(ICON_COLOR_GRAY);
				groupText->setColor(ICON_COLOR_GRAY);
		}
		else
		{
			if (pGroupItem->getGroupID() == mCurGroupScene->getGroupID())
			{
				menuItem->setNormalImage(CCSprite::create("n_button_seledBig.png"));
				if(!startFlag)
				{
					startFlag = true;
					//offset_ = CCPointMake(-(i*menuItem->getContentSize().width - winSize.width * 0.012*(i+1)),0);
					//offset_ = CCPointMake(-((i+1)* ITEM_TITLE_SPACE_DELTA_X * winSize.width - menuItem->getContentSize().width * 0.730f),0);//- menuItem->getContentSize().width/2.0f
					offset_ = CCPointMake(-((i)* ITEM_TITLE_SPACE_DELTA_X * winSize.width ),0);
				}
			}
		}

		menuItem->setUserData( (void *)pGroupItem );

		contentSize.width = max( contentSize.width, itemPos.x - winSize.width * ITEM_TITLE_START_X + winSize.width * ITEM_TITLE_SPACE_DELTA_X );		

		menuTitle->addChild( menuItem );
	}

	layer_title->setAnchorPoint( CCPointZero );  
	layer_title->setPosition( CCPointZero );  
	layer_title->setContentSize( contentSize ); 

	menuTitle->setPosition( CCPointZero );  
	layer_title->addChild( menuTitle );

	mContent_title->setViewSize( CCSizeMake(winSize.width * CONTENT_TITLE_VIEW_SIZE_X, winSize.height * CONTENT_TITLE_VIEW_SIZE_Y) );
	mContent_title->setContentSize( contentSize ); 

	mContent_title->setContainer( layer_title );

	mContent_title->setDirection( kCCScrollViewDirectionHorizontal );

	mContent_title->setPosition( CCPointMake( winSize.width * CONTENT_TITLE_POS_X, winSize.height * CONTENT_TITLE_POS_Y ) );

	mContentNode->addChild( mContent_title );

	mContent_title->setContentOffset(offset_);


	// for level list
	mContent_list = CCScrollViewEx::create();  
	CCLayer *layer_list = CCLayer::create(); 
	
	CCRect vRect = CCRectMake(winSize.width * CONTENT_LIST_POS_X, winSize.height * CONTENT_LIST_POS_Y ,
		winSize.width * CONTENT_LIST_VIEW_SIZE_X, winSize.height * CONTENT_LIST_VIEW_SIZE_Y);
	CCMenuPEx *menuList = CCMenuPEx::create(vRect); 
	CCMenuEx *menuRush = CCMenuEx::create(); 
	
	// scene display limit
	const CopyScene *maxScene = mCurGroupScene->getMaxEnable();
	if( !maxScene )
		return;

	vector<CopyScene*> sceneItems;
	sceneItems.clear();
	for( X_UINT i = 0; i < sceneSize; i++ )
	{
		pScene = pSecnes[i];

		if( pScene->getID() > maxScene->getID() )
			continue;
		sceneItems.push_back(pScene);
	}

	contentSize = CCSizeZero;
	contentSize.width = winSize.width * ITEM_LIST_SPACE_DELTA_X;
	
	int iSceneNum = sceneItems.size();

// 	contentSize.height = winSize.height * ((sceneSize > 3) ? (sceneSize + 1) : (sceneSize))  * ITEM_LIST_SPACE_DELTA_Y;

	if (mCurCopyScene)
	{
		contentSize.height = winSize.height * (iSceneNum + 3)  * ITEM_LIST_SPACE_DELTA_Y;
	}
	else
	{
		contentSize.height = winSize.height * (iSceneNum + 1)  * ITEM_LIST_SPACE_DELTA_Y;
	}

	

	// group info
	CCSize infoRect = CCSizeMake( winSize.width * 0.80f, winSize.height * 0.15f );
	CCScale9Sprite *groupInfoBK = CCScale9Sprite::create( "level_item.png" );//n_tip_bg  frame_s_2
	groupInfoBK->setContentSize( infoRect );
	groupInfoBK->setPosition( CCPointMake( winSize.width * ITEM_LIST_START_X, winSize.height * ITEM_LIST_START_Y  + contentSize.height ) );
	layer_list->addChild( groupInfoBK );

	infoRect.width *= 0.9f;
	infoRect.height *= 0.8f;
	CCLabelTTF *groupInfoText = CCLabelTTF::create( mCurGroupScene->getInfo(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24, infoRect, kCCTextAlignmentLeft );
	groupInfoText->setPosition(ccpAdd(ccp(0,-winSize.height*0.005),groupInfoBK->getPosition()));
	groupInfoText->setColor(CCCOLOR_GREEN);//副本剧情
	layer_list->addChild( groupInfoText );


	
	CCPoint content_listOffset( 0, 0 );

	int posIndex = 1;
	int locOfNotAllStar = 0;
	int flagOfDescription = 0;
	for( X_INT i = 0; i < iSceneNum; i++, posIndex++ )
	{
		pScene = sceneItems[i];

// 		if( pScene->getID() > maxScene->getID() )
// 			continue;

		CCMenuItemImage *menuItem = CCMenuItemImage::create( "levelFrame.png", "levelFrame.png", this, menu_selector(LevelListUIView::listCallBack) );  
		CCPoint itemPos = CCPointMake( winSize.width * ITEM_LIST_START_X, winSize.height * ( ITEM_LIST_START_Y - posIndex * ITEM_LIST_SPACE_DELTA_Y ) + contentSize.height );

		menuItem->setPosition( itemPos ); 
		menuItem->setScaleX(SCALE_X);
        menuItem->setScaleY(SCALE_Y);
		menuItem->setUserData( (void *)pScene );
        menuList->addChild( menuItem );

		CCSprite * sceneIcon = CCSprite::create( pScene->getIcon() );
		sceneIcon->setPosition( ccpAdd( itemPos, ccp( winSize.width * ITEM_ICON_OFFSET_X, winSize.height * ITEM_ICON_OFFSET_Y ) ) );
		float sceneIconWidth = sceneIcon->getContentSize().width;
		sceneIcon->setScale(winSize.width * HEADICON_SCALE_X / sceneIconWidth);
		layer_list->addChild( sceneIcon, 10 );

		CCSprite * sceneIconBg = CCSprite::create("n_pos_white.png");
		sceneIconBg->setPosition( ccpAdd( itemPos, ccp( winSize.width * ITEM_ICON_OFFSET_X, winSize.height * ITEM_ICON_OFFSET_Y ) ) );
		sceneIconBg->setScale(winSize.width * HEADICON_SCALE_X / sceneIconWidth);
		layer_list->addChild(sceneIconBg, 10 );
		
		CCLabelTTF *sceneName = CCLabelTTF::create( pScene->getName(), FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 );
		sceneName->setPosition( ccpAdd( itemPos, ccp( winSize.width * ITEM_NAME_OFFSET_X, winSize.height * (ITEM_NAME_OFFSET_Y - 0.01)) ) );
		sceneName->setColor(CCCOLOR_YELLOW);//副本名称
		sceneName->setAnchorPoint(ccp(0.0f, 0.5f));
		layer_list->addChild( sceneName, 10 );

		int iStar = pScene->getStar();
		if (iStar != 0)
		{
			for(int j = 0; j<5; ++j)
			{
				CCSprite * starIcon;
				if (j < iStar)
				{
					starIcon = CCSprite::create( "star.png"/*pScene->getIcon()*/ );
					
				}
				else
				{
					starIcon = CCSprite::create( "star_null.png"/*pScene->getIcon()*/ );
				}
				starIcon->setPosition( ccpAdd( itemPos, ccp(winSize.width * ITEM_STAR_OFFSET_X /*+ menuItem->getContentSize().width*/ + j * starIcon->getContentSize().width , winSize.height * ITEM_STAR_OFFSET_Y ) ) );
				layer_list->addChild( starIcon, 10 );
			}
		}
		if (iStar < 5)
		{
			locOfNotAllStar = i;
			if (iStar == 0 && i == 0)
			{
				locOfNotAllStar = -1;
			}
		}
		
		
		

		if(mCurCopyScene &&  mCurCopyScene->getID() == pScene->getID() )
		{
			content_listOffset.y = posIndex * winSize.height * ITEM_LIST_SPACE_DELTA_Y;
			flagOfDescription = 1;

			CCSprite * levelFrameBK = CCSprite::create( "level_item.png" );
			levelFrameBK->setPosition( ccpAdd( itemPos, ccp( 0, winSize.height * ITEM_INFO_BK_OFFSET_Y ) ) );
            levelFrameBK->setScaleX(SCALE_X);
            levelFrameBK->setScaleY(SCALE_Y * 1.1f);
			layer_list->addChild( levelFrameBK );
			 
			CCLabelTTF *sceneInfo = CCLabelTTF::create(pScene->getInfo() , FONT_NAME_ARIAL_BOLD, FONT_SIZE_24 ,infoRect, kCCTextAlignmentLeft );
			sceneInfo->setPosition( ccpAdd( itemPos, ccp( 0, winSize.height * (ITEM_INFO_OFFSET_Y )) ) );
			sceneInfo->setColor(CCCOLOR_YELLOW);
			layer_list->addChild( sceneInfo );

			CCLabelTTF *labelAct = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(536),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelAct->setAnchorPoint(ccp(0,0.5));
			labelAct->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.36),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			labelAct->setColor(CCCOLOR_GREEN);
			layer_list->addChild(labelAct);

			
			CCLabelTTF *labelActValue = CCLabelTTF::create(UtilTools::IntToString(pScene->getActionCost()).c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelActValue->setAnchorPoint(ccp(0,0.5));
			labelActValue->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.210),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			layer_list->addChild(labelActValue);


			CCLabelTTF *labelChallenge = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(537),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelChallenge->setAnchorPoint(ccp(0,0.5));
			labelChallenge->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.16),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			labelChallenge->setColor(CCCOLOR_GREEN);
			layer_list->addChild(labelChallenge);

			string str4;
			str4 = UtilTools::IntToString(pScene->getChallengeNum());
			str4 +="/";
			str4 +=UtilTools::IntToString(pScene->getMaxChallengeNum());
			CCLabelTTF *labelChallengeValue = CCLabelTTF::create(str4.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelChallengeValue->setAnchorPoint(ccp(0,0.5));
			labelChallengeValue->setPosition(ccpAdd(itemPos,ccp(winSize.width * (0.08),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			layer_list->addChild(labelChallengeValue);


			CCLabelTTF *labelRmdLvl = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(538),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelRmdLvl->setAnchorPoint(ccp(0,0.5));
			labelRmdLvl->setPosition(ccpAdd(itemPos,ccp(winSize.width * (0.18),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			labelRmdLvl->setColor(CCCOLOR_GREEN);
			layer_list->addChild(labelRmdLvl);

			CCLabelTTF *labelRmdLvlValue = CCLabelTTF::create(UtilTools::IntToString(pScene->getRecommendLevel()).c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelRmdLvlValue->setAnchorPoint(ccp(0,0.5));
			labelRmdLvlValue->setPosition(ccpAdd(itemPos,ccp(winSize.width * (0.34),winSize.height * SECONDLINE_LABLE_OFFSET_Y)));
			layer_list->addChild(labelRmdLvlValue);

			CCLabelTTF *labelExp = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(539),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelExp->setAnchorPoint(ccp(0,0.5));
			labelExp->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.36),winSize.height * THIRDLINE_LABLE_OFFSET_Y)));
			labelExp->setColor(CCCOLOR_GREEN);
			layer_list->addChild(labelExp);

			string str8;
			str8 = UtilTools::GET_TEXT_FROM_LANG(540);
			str8 += UtilTools::IntToString( pScene->getEXP());
			CCLabelTTF *labelExpValue = CCLabelTTF::create(str8.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelExpValue->setAnchorPoint(ccp(0,0.5));
			labelExpValue->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.210),winSize.height * THIRDLINE_LABLE_OFFSET_Y)));
			layer_list->addChild(labelExpValue);

			string str9;
			str9 = UtilTools::GET_TEXT_FROM_LANG(520);
			str9 += UtilTools::IntToString( pScene->GetAwardGold());
			CCLabelTTF *labelGoldValue = CCLabelTTF::create(str9.c_str(),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelGoldValue->setAnchorPoint(ccp(0,0.5));
			labelGoldValue->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.001),winSize.height * THIRDLINE_LABLE_OFFSET_Y)));
			layer_list->addChild(labelGoldValue);


			CCLabelTTF *labelItems = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(541),FONT_NAME_ARIAL_BOLD,FONT_SIZE_22);
			labelItems->setAnchorPoint(ccp(0,0.5));
			labelItems->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.36),winSize.height * FOURTHLINE_LABLE_OFFSET_Y)));
			labelItems->setColor(CCCOLOR_GREEN);//副本获得
			layer_list->addChild(labelItems);

			vector<X_INT> items =  pScene->GetDropItems();
			int awardNum = items.size();
			string strName,strIcon,strColor;X_INT level;

			ObjectManager *pManager = DataPool::GetSingleton()->getObjectManager();
			X_BOOL flag;
			for (int i=0;i<awardNum;i++)
			{
 				
 				flag = pManager->getItemInfoById(items[i],strName,strColor,strIcon,level);
 				if (!flag)
 				{
 					continue;
 				}
				
				CCSprite *equiSpriteBg = CCSprite::create("equipmentBK.png");
				//equiSpriteBg->setScale(0.5f);
				equiSpriteBg->setPosition(ccpAdd(itemPos,ccp(winSize.width * (-0.140) + i * equiSpriteBg->getContentSize().width, winSize.height * (-0.34))));
				

				CCSprite *equiSprite = CCSprite::create(strIcon.c_str());
				equiSprite->setScale(0.85f);
				equiSprite->setPosition(equiSpriteBg->getPosition());
				layer_list->addChild(equiSprite);
				layer_list->addChild(equiSpriteBg);
 
				CCSprite *pLevel = GameHelper::getSpriteLevel(level);
				if (pLevel)
				{
					pLevel->setPosition( equiSprite->getPosition()); 
					layer_list->addChild(pLevel);
					pLevel->setZOrder(100);
					pLevel->setScale(equiSprite->getScale());
				} 
 

			}
			
			posIndex += 2;

		}

		menuItem = CCMenuItemImage::create( "n_home_button.png", "n_home_button_sel.png", this, menu_selector(LevelListUIView::rushCallBack) );  
		menuItem->setScale( 0.75f );
		itemPos.x += winSize.width * (ITEM_RUSH_OFFSET_X + 0.1);
		itemPos.y += winSize.height * ITEM_RUSH_OFFSET_Y;
        menuItem->setPosition( itemPos ); 
		menuItem->setUserData( (void *)pScene );
		menuRush->addChild( menuItem);



		CCSprite *rushText = CCSprite::create("n_bat_cha_text.png");
		rushText->setPosition(ccpAdd(ccp(0 ,0),menuItem->getPosition()));
		rushText->setScale(0.8f);
		layer_list->addChild(rushText,menuRush->getZOrder()+1);

		 
		X_INT tipId = ((LevelListUI *)this->getUserData())->getTipId();

		if (guideLayer)
		{
			guideLayer->removeFromParentAndCleanup(true);
		}

		guideLayer = X_NULL;
		if (tipId != -1 && i == 0)
		{
 
			if (!guideLayer)
			{
				//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(LevelListUIView::rushCallBack),menuItem);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
			}
		}
	}



	layer_list->setAnchorPoint( CCPointZero );  
	layer_list->setPosition( CCPointZero );  
	layer_list->setContentSize( contentSize ); 

	menuList->setPosition( CCPointZero );  
	layer_list->addChild( menuList );

	menuRush->setPosition( CCPointZero );  
	layer_list->addChild( menuRush );

	mContent_list->setViewSize( CCSizeMake(winSize.width * CONTENT_LIST_VIEW_SIZE_X, winSize.height * CONTENT_LIST_VIEW_SIZE_Y) );
	mContent_list->setContentSize( contentSize ); 

	mContent_list->setContainer( layer_list );

	mContent_list->setDirection( kCCScrollViewDirectionVertical );

	mContent_list->setPosition( CCPointMake( winSize.width * CONTENT_LIST_POS_X, winSize.height * CONTENT_LIST_POS_Y ) );

// 	if (mCurCopyScene)
	{
		if(locOfNotAllStar > 0 && !flagOfDescription)
		{
			content_listOffset.y += (locOfNotAllStar + 1) * winSize.height * ITEM_LIST_SPACE_DELTA_Y;
			mContent_list->setContentOffset(ccpAdd( mContent_list->minContainerOffset(), content_listOffset ));
		}
		else
		{
			mContent_list->setContentOffset( ccpAdd( mContent_list->minContainerOffset(), content_listOffset ) );
		}
		
		
		
	}
// 	else
// 	{
// 		mContent_list->setContentOffset(sceneOffset_);
// 	}
	
	
	mContentNode->addChild( mContent_list );


	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}
	
}

void LevelListUIView::titleCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent_title->mIsMoved )
		return;

	const CopySceneGroup* groupScene = (const CopySceneGroup*)(((CCNode *)pSender)->getUserData());

	if( !groupScene->isEnable() || groupScene->getGroupID() == mCurGroupScene->getGroupID() )
	{
	//	((CCMenuItemImage *)pSender)->setNormalImage(CCSprite::create("n_home_button_selected.png"));
	//	((CCMenuItemImage *)pSender)->setScaleX( SCALE_TITLE_ITEM );
		return;
	}
	//mCurGroupScene = groupScene;
	DataPool::GetSingleton()->getCopySceneManager()->setCurSceneGroup(const_cast< CopySceneGroup*> (groupScene) );
	mCurCopyScene = NULL;
	SendLogicPacket::askSceneList( groupScene->getGroupID(),true);

	offset_ = mContent_title->getContentOffset();

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void LevelListUIView::listCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent_list->mIsMoved )
		return;

	CopyScene * curScene = (CopyScene*)(((CCNode *)pSender)->getUserData());

	if (mCurCopyScene && mCurCopyScene->getID() == curScene->getID())
	{
		DataPool::GetSingleton()->getCopySceneManager()->setCurScene( NULL );
		mCurCopyScene = NULL;
	}
	else
	{
		DataPool::GetSingleton()->getCopySceneManager()->setCurScene( curScene );
		mCurCopyScene = curScene;
	}
	
	sceneOffset_ = mContent_list->getContentOffset();

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_UPDATA);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}

void LevelListUIView::rushCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent_list->mIsMoved )
		return;

	CopyScene * curScene = (CopyScene*)(((CCNode *)pSender)->getUserData());

	if (curScene->getChallengeNum() == curScene->getMaxChallengeNum())
	{

		char buffNum[MAX_STRING_BUFF_SIZE] = {0};
		sprintf(buffNum,UtilTools::GET_TEXT_FROM_LANG(570),curScene->getRefreshCost());

		ModalDialogView *dialog = ModalDialogView::createDialog(buffNum,this);
		dialog->setTag(DIALOG_TAG_CHALLENGE_NUM);
		dialog->setDailogUserData(curScene);
		addChild(dialog,10);
	}
	else
	{
		ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
		PlayerData* pData = pSelf->playerData();

		if (curScene->getActionCost() > pData->GetActionPoint())
		{
			ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(571),this);
			dialog->setTag(DIALOG_TAG_ACTION);
			addChild(dialog,10);
		}
		else
		{
			DataPool::GetSingleton()->getCopySceneManager()->setCurScene( curScene );
			SendLogicPacket::Battle( curScene->getMonster(), true, curScene->getID() );
		}
		
	}


	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

void LevelListUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	int iTag = pSender->getTag();

	
	switch (iTag)
	{
	case  DIALOG_TAG_CHALLENGE_NUM:
		{

			CopyScene * curScene =(CopyScene *)pSender->getDailogUserData();

			ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
			PlayerData* pData = pSelf->playerData();

			if (curScene->getRefreshCost() > pData->GetGold())
			{
				ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(550), this);
				dialog->setTag(DIALOG_TAG_GOLD);
				addChild(dialog,11);
			}
			else
			{
				DataPool::GetSingleton()->getCopySceneManager()->setCurScene( curScene );
				SendLogicPacket::Battle( curScene->getMonster(), true, curScene->getID() );
			}


			
			break;
		}
	case  DIALOG_TAG_ACTION:
		{

			EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_USER_INFO_SHOW);
			break;
		}

	case  DIALOG_TAG_GOLD:
		{

			EventSystem::GetSingleton()->PushEvent(	GAME_EVENT_RECHARGE_SHOW);
			break;
		}
	default:
		break;
	}

	pSender->closeDialogView();

}
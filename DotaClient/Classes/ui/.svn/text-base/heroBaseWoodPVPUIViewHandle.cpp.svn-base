#include "./ui/heroBaseActivityUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./ui/element/CCMenuEx.h"
#include "element/LogicTouchItem.h"
#include "./datapool/WoodData.h"
#include "element/FightTips.h"
#include "./Packets/Wood/CGWoodAskPacket.h"
#include "heroBaseActivityUI.h"
#include "./GameResult.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_ACT_NUM				 (3)

#define CONTENT_POS_X            (0.100f)
#define CONTENT_POS_Y            (0.858f)//(0.455f)

#define CONTENT_VIEW_SIZE_X      (0.80f)
#define CONTENT_VIEW_SIZE_Y      (0.2f)

#define ITEM_SPACE_DELTA_X       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.115f)//(0.127f)//(0.130f)

#define ITEM_START_X			 (0.09f) //(0.111f)
#define ITEM_START_Y             (0.06f)//(0.45f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            1

HeroWoodPVPUIViewHandle::HeroWoodPVPUIViewHandle( heroBaseActivityUIView* UIView )
	: HeroBaseActivityUIViewHandle(UIView)
	, m_IsDragMove(X_FALSE)
	, m_HeroPVPLayer(NULL)
	, m_HeroPVPLevelLabel(NULL)
	, m_HeroPVPHPLabel(NULL)
	, m_HeroPVPDefLabel(NULL)
	, m_HeroPVPCreLabel(NULL)
	, m_HeroPVPTotalLabel(NULL)
	, m_HeroRobLayer(NULL)
	, m_HeroRobLevelLabel(NULL)
	, m_HeroRobHPLabel(NULL)
	, m_HeroRobDefLabel(NULL)
	, m_HeroRobWoodLabel(NULL)
	,m_RobNum(0)
	, m_HeroLevelUpFreshTimeLabel(NULL)
	, m_HeroLevelUpButtonSprite(NULL)
	, m_HeroRemachButtonLabel(NULL)
	, m_HeroRevengeLayer(NULL)
	, m_HeroRevengeLevelLabel(NULL)
	, m_HeroRevengeHPLabel(NULL)
	, m_HeroRevengeDefLabel(NULL)
	, m_HeroRevengeWoodLabel(NULL)
{
	for (int i = 0 ; i < MAX_MATRIX_CELL_COUNT ; i++)
	{
		m_HeroPVPDock[i] = NULL;
		m_HeroPVPItems[i] = NULL;
		m_HeroRobDock[i] = NULL;
		m_HerosDockIndex[i] = -1;
		m_HeroObjArray[i] = NULL;
		m_HeroRobItems[i] = NULL;
		m_HeroPVPNullItems[i] = NULL;
		m_HeroRevengeDock[i] = NULL;
		m_HeroRevengeItems[i] = NULL;
	}
	visable = false;
	mPVPCd = X_NULL;
	mPVPProtectedCd= X_NULL;
	for (int i = 0 ; i < 16 ; i++)
	{
		_mHeroAttcAdd[i] = 0;
	}
	m_RobDef = 0;
	m_RevengeDef = 0;
}

HeroWoodPVPUIViewHandle::~HeroWoodPVPUIViewHandle()
{
	ClearData();
	// heroPVP  layer
	CC_SAFE_RELEASE(m_HeroPVPLayer);
	CC_SAFE_RELEASE(m_HeroPVPLevelLabel);
	CC_SAFE_RELEASE(m_HeroPVPHPLabel);
	CC_SAFE_RELEASE(m_HeroPVPDefLabel);
	CC_SAFE_RELEASE(m_HeroPVPCreLabel);
	CC_SAFE_RELEASE(m_HeroPVPTotalLabel);
	CC_SAFE_RELEASE(m_HeroLevelUpFreshTimeLabel);
	CC_SAFE_RELEASE(m_HeroLevelUpButtonSprite);

	//hero Rob layer
	CC_SAFE_RELEASE(m_HeroRobLayer);
	CC_SAFE_RELEASE(m_HeroRobLevelLabel);
	CC_SAFE_RELEASE(m_HeroRobHPLabel);
	CC_SAFE_RELEASE(m_HeroRobWoodLabel);
	CC_SAFE_RELEASE(m_RobNum);
	CC_SAFE_RELEASE(m_HeroRemachButtonLabel);
 
	//hero Revenge Layer

	CC_SAFE_RELEASE(m_HeroRevengeLayer);
	CC_SAFE_RELEASE(m_HeroRevengeLevelLabel);
	CC_SAFE_RELEASE(m_HeroRevengeHPLabel);
	CC_SAFE_RELEASE(m_HeroRevengeWoodLabel);
	CC_SAFE_RELEASE(mPVPCd);
	CC_SAFE_RELEASE(mPVPProtectedCd);

	CC_SAFE_RELEASE(m_RobDef);
	CC_SAFE_RELEASE(m_RevengeDef);
	 
}

bool HeroWoodPVPUIViewHandle::onAssignCCBMemberVariable( cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode )
{
	//heroPVP layer
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerPVP",	CCLayer *,m_HeroPVPLayer);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPLevel",	CCSprite *,m_HeroPVPLevelLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPHP",		CCSprite *,m_HeroPVPHPLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPDef",    CCSprite *,m_HeroPVPDefLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPCre",    CCSprite *,m_HeroPVPCreLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPTotal",  CCSprite *,m_HeroPVPTotalLabel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPCd",    CCSprite *,mPVPCd);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPVPProtectedCd",  CCSprite *,mPVPProtectedCd);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mButtonLevelupLabel",  CCSprite *,m_HeroLevelUpFreshTimeLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mButtonLevelupSprite",  CCSprite *,m_HeroLevelUpButtonSprite);



	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos1",  CCSprite *,m_HeroPVPDock[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos2",  CCSprite *,m_HeroPVPDock[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos3",  CCSprite *,m_HeroPVPDock[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos4",  CCSprite *,m_HeroPVPDock[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos5",  CCSprite *,m_HeroPVPDock[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mPos6",  CCSprite *,m_HeroPVPDock[5]);


	//hero Rob layer
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerRob",	CCLayer *,m_HeroRobLayer);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobLevel",  CCLabelTTF *,m_HeroRobLevelLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobHP",  CCSprite *,m_HeroRobHPLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobWood",  CCSprite *,m_HeroRobWoodLabel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mButtonRemachLabel",  CCSprite *,m_HeroRemachButtonLabel); 


	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobNumber",  CCSprite *,m_RobNum);
 
 

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos1",  CCSprite *,m_HeroRobDock[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos2",  CCSprite *,m_HeroRobDock[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos3",  CCSprite *,m_HeroRobDock[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos4",  CCSprite *,m_HeroRobDock[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos5",  CCSprite *,m_HeroRobDock[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobPos6",  CCSprite *,m_HeroRobDock[5]);


	//hero Revenge Layer

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mLayerRevenge",	CCLayer *,m_HeroRevengeLayer);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengeLevel",  CCLabelTTF *,m_HeroRevengeLevelLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengeHP",  CCSprite *,m_HeroRevengeHPLabel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengeWood",  CCSprite *,m_HeroRevengeWoodLabel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos1",  CCSprite *,m_HeroRevengeDock[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos2",  CCSprite *,m_HeroRevengeDock[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos3",  CCSprite *,m_HeroRevengeDock[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos4",  CCSprite *,m_HeroRevengeDock[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos5",  CCSprite *,m_HeroRevengeDock[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengePos6",  CCSprite *,m_HeroRevengeDock[5]);



	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRobDef",  CCSprite *,m_RobDef);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(m_BaseUIView, "mRevengeDef",  CCSprite *,m_RevengeDef);
 

	return false;
}
void HeroWoodPVPUIViewHandle::onButtonWoodUpgrade()
{
	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
	SelfWoodData*  pSelfWoodData = pWoodData->GetSelfWoodData();
	//ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData* pData = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData();
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

 
	if (pSelfWoodData->m_IsLevelUping)
	{
 
		vector<string> strV(1,UtilTools::GET_TEXT_FROM_LANG(WOOD_FAIL_LEVELUPING));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		return ;
	}

 
	if(pData->GetLevel() < pSelfWoodData->m_RequiredLevel)
	{
 
		vector<string> strV(1,UtilTools::GET_TEXT_FROM_LANG(WOOD_FAIL_LEVELUPING));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		return;
	}
	X_INT  WoodCreat = pSelfWoodData->m_WoodCreat;
	X_INT  WoodCapacity = pSelfWoodData->m_WoodCapacity;
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_WOOD);
	if (pDataFile)
	{
		const  stDBC_FILE_WOOD* tableData = 
			(const stDBC_FILE_WOOD*)pDataFile->GetFieldsByIndexKey( pSelfWoodData->m_WoodData.m_CampLevel+1);
		if (tableData)
		{
			WoodCreat = tableData->product;
			WoodCapacity = tableData->total;
		}
		
	}
	char strBuffer[1024] = "";
	sprintf(strBuffer,
		UtilTools::GET_TEXT_FROM_LANG(631),
		pSelfWoodData->m_RequiredMoney,
		pSelfWoodData->m_RequiredTime,
		WoodCreat,
		WoodCapacity);
	ModalDialogView *dialog = ModalDialogView::createDialog( strBuffer,this);
	dialog->setTag(EM_DIALOG_WOODLEVELUP_TAG);
	m_BaseUIView->addChild(dialog,10);
}
void HeroWoodPVPUIViewHandle::heroAdditionalValue(const string& str, cocos2d::CCPoint pos,X_INT attr,float scale,CCSprite *label)
{
	if (_mHeroAttcAdd[attr])
	{
		if (_mHeroAttcAdd[attr]->getParent())
		{
			_mHeroAttcAdd[attr]->getParent()->removeChild(_mHeroAttcAdd[attr]);_mHeroAttcAdd[attr] = X_NULL;
		}
 
	}
	if (str.size()<=0)
	{
		return;
	}
	_mHeroAttcAdd[attr] = CCLabelBMFont::create(str.c_str(),FNT_NAME_LARGEGREEN);
	_mHeroAttcAdd[attr]->setPosition(pos);
	_mHeroAttcAdd[attr]->setAnchorPoint(ccp(0,0.5));
	if (label&&label->getParent())
	{
		label->getParent()->addChild(_mHeroAttcAdd[attr]);
	}
	_mHeroAttcAdd[attr]->setScale(SCALE_BMF);
}


void HeroWoodPVPUIViewHandle::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
	SelfWoodData*  pSelfWoodData = pWoodData->GetSelfWoodData();
	PlayerData* pData = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData();
	int iTag = pSender->getTag();

	switch (iTag)
	{
	case EM_DIALOG_WOODLEVELUP_TAG:
		if (pData->GetGold() < pSelfWoodData->m_RequiredMoney)
		{
			ModalDialogView *dialog = ModalDialogView::createDialog( UtilTools::GET_TEXT_FROM_LANG(633),this);
			dialog->setTag(EM_DIALOG_REQUIREMONEY_TAG);
			m_BaseUIView->addChild(dialog,200);
		}
		else
		{
			SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_LEVELUP);
		}
		break;
	case EM_DIALOG_REQUIREMONEY_TAG:
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECHARGE_SHOW);
		break;

	case EM_DIALOG_WOODGotoPVP_TAG:
		SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_FINDROB);
		break;
	case EM_DIALOG_WOODGotoFuchou_TAG:
		SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_REROB);
		break;
	case EM_DIALOG_REMATCH_TAG:
		{
			if (pData->GetGold() < pWoodData->GetRobWoodData()->m_MatchGold)
			{
				ModalDialogView *dialog = ModalDialogView::createDialog( UtilTools::GET_TEXT_FROM_LANG(633),this);
				dialog->setTag(EM_DIALOG_REQUIREMONEY_TAG);
				m_BaseUIView->addChild(dialog,200);
			}
			else
			{
				SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_REMATCH);	
			}
		}
	default:
		break;
	}
	pSender->closeDialogView();
}
void HeroWoodPVPUIViewHandle::onButtonGotoRob( )
{

	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();

	if (pWoodData->GetSelfWoodData()->GetRobCD() > 0)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(697));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
 
	if (pWoodData->GetSelfWoodData()->GetSafeCD() > 0)
	{
	 
		ModalDialogView *dialog = ModalDialogView::createDialog( UtilTools::GET_TEXT_FROM_LANG(698),this);
		dialog->setTag(EM_DIALOG_WOODGotoPVP_TAG);
		m_BaseUIView->addChild(dialog,10);
	}else
	{
		SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_FINDROB);
	}


}
void HeroWoodPVPUIViewHandle::onButtonRob( )
{
	SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_ROB);
}
void HeroWoodPVPUIViewHandle::onButtonRevenge(  )
{

	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();

	if (pWoodData->GetSelfWoodData()->GetSafeCD() > 0)
	{

		ModalDialogView *dialog = ModalDialogView::createDialog( UtilTools::GET_TEXT_FROM_LANG(701),this);
		dialog->setTag(EM_DIALOG_WOODGotoFuchou_TAG);
		m_BaseUIView->addChild(dialog,10);
	}else
	{
		SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_REROB);
	}
 
}
void HeroWoodPVPUIViewHandle::onButtonRematch()
{
	WoodsData*  pWoodData = DataPool::GetSingleton()->GetWoodData();
    PlayerData* pData = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData();

	X_INT cost = pWoodData->GetRobWoodData()->m_MatchGold;
 
	if (cost >  0)
	{
		char str[256] = {0};
		sprintf(str,UtilTools::GET_TEXT_FROM_LANG(707),cost);
		ModalDialogView *dialog = ModalDialogView::createDialog(str,this);
		dialog->setTag(EM_DIALOG_REMATCH_TAG);
		m_BaseUIView->addChild(dialog,200);
		return;
	}else
	{
		 SendLogicPacket::AskRobWood(CGWoodAskPacket::WOODOPT_REMATCH);	
	}
 
}
X_VOID HeroWoodPVPUIViewHandle::CreateHeroPVPNullItem()
{
	for (int i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		cocos2d::LogicTouchItem* nullItem = cocos2d::LogicTouchItem::createWithFile( "n_pos_gray.png", this, 
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroNullTouchBeginHook), 
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroNullTouchMoveHook),
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroNullTouchEndHook),
			false, 20 );

		nullItem->setPosition( m_HeroPVPDock[i]->getPosition() );
		nullItem->setUserData( ((void*)i) );
		m_HeroPVPNullItems[i] = nullItem;
		m_HeroPVPDock[i]->getParent()->addChild( m_HeroPVPNullItems[i] );
	}
}
void HeroWoodPVPUIViewHandle::HeroPVPDataUpdate()
{
	visable = true;
	ClearData();
	DataPool::GetSingleton()->BattlyType = EM_WOODPVP;
 
	CCPoint Pos = m_BaseUIView->m_ContentNode->getPosition();
	CCLayer*  LayoutLayer = NULL;
	switch (((heroBaseActivityUI*)(m_BaseUIView->getUserData()))->m_ShowLayer)
	{
	case heroBaseActivityUI::EM_SELFWOOD_LAYER_SHOW:
		{
			LayoutLayer = m_HeroPVPLayer;
			UpdateSelfWoodData();
		}
		break;
	case heroBaseActivityUI::EM_ROBWOOD_LAYER_SHOW:
		{
			UpdateOtherDefWoodData();
			LayoutLayer = m_HeroRobLayer;
		}
		break;
	case heroBaseActivityUI::EM_REVENGEWOOD_LAYER_SHOW:
		{
			UpdateRevengeWoodData();
			LayoutLayer = m_HeroRevengeLayer;
		}
		break;
	default:
		break;
	}
	if (!LayoutLayer)
	{
		return;
	}
	
	LayoutLayer->setVisible(true);
	LayoutLayer->setPosition(Pos);

	UpdateWoodPVPTextData();

}
void HeroWoodPVPUIViewHandle::updateWoodLevelUpTime( float time )
{
	WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
	// À¢–¬ ±º‰

	X_INT  t  = pWoodData->GetSelfWoodData()->GetRobCD();

	//mPVPCd->setString(UtilTools::ConvertMillisecondToTimeString(t).c_str());
 
	CCPoint posHP = ccp(mPVPCd->getPosition().x + mPVPCd->getContentSize().width *mPVPCd->getScaleX()  , mPVPCd->getPosition().y );

	string str = UtilTools::ConvertMillisecondToTimeString(t);
	if (str.size() >= 6)
	{
		str = str.substr(3);
	}
	if (t == 0)
	{
		str = "0";
	}
	
	 
	heroAdditionalValue(str,posHP,0,1,mPVPCd);

	t  = pWoodData->GetSelfWoodData()->GetSafeCD();
	 //mPVPProtectedCd->setString(UtilTools::ConvertMillisecondToTimeString(t).c_str());
	posHP = ccp(mPVPProtectedCd->getPosition().x + mPVPProtectedCd->getContentSize().width *mPVPProtectedCd->getScaleX(), mPVPProtectedCd->getPosition().y );

	str = UtilTools::ConvertMillisecondToTimeString(t);
	/*if (str.size() >= 6)
	{
		 
	}*/
	if (t == 0)
	{
		str = "0";
	}
	heroAdditionalValue(str, posHP,1,1,mPVPProtectedCd);
	 

	if( pWoodData->GetSelfWoodData()->m_IsLevelUping )
	{
		CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage( "woodleveling.png");
	 
		m_HeroLevelUpButtonSprite->setTexture(texture2D1);
		char  str[1024] = "";
		string time = UtilTools::ConvertMillisecondToTimeString( pWoodData->GetSelfWoodData()->m_WoodData.m_LevelUpRemainTime );
		/*sprintf(str,UtilTools::GET_TEXT_FROM_LANG(634),time.c_str());
		if (NULL != m_HeroLevelUpFreshTimeLabel)
		{
			m_HeroLevelUpFreshTimeLabel->setString(str);
		}*/

		posHP = ccp(m_HeroLevelUpFreshTimeLabel->getPosition().x + m_HeroLevelUpFreshTimeLabel->getContentSize().width*m_HeroLevelUpFreshTimeLabel->getScaleX() , m_HeroLevelUpFreshTimeLabel->getPosition().y );
		heroAdditionalValue(time, posHP,2,1,m_HeroLevelUpFreshTimeLabel);
	}
	else
	{
		CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage( "upgradeText.png");

		m_HeroLevelUpButtonSprite->setTexture(texture2D1);
 
	}
}
void HeroWoodPVPUIViewHandle::heroItemTouchBeginHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch begin", (int)(((CCNode *)pSender)->getUserData()) );

	using namespace cocos2d;
	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() + 10 );

	m_IsDragMove = X_FALSE;
}

void HeroWoodPVPUIViewHandle::heroItemTouchMoveHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch move", (int)(((CCNode *)pSender)->getUserData()) );

	m_IsDragMove = X_TRUE;
}

void HeroWoodPVPUIViewHandle::heroItemTouchEndHook(CCObject* pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);

	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() - 10 );

	const int heroIndex = (int)(((CCNode *)pSender)->getUserData());

	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();

	if( !m_IsDragMove )
	{
		if( m_HeroObjArray[heroIndex] &&!m_HeroObjArray[heroIndex]->isWoodHero())
		{
			DataPool::GetSingleton()->SetSelectHero( m_HeroObjArray[heroIndex] );

			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_SHOW);
		}
	}
	else
	{
		int oriDockIndex = m_HerosDockIndex[heroIndex];
		assert( oriDockIndex >= 0 );

		CCPoint dropPos = ((CCNode *)pSender)->getPosition();

		int i = 0;
		for( ; i < MAX_MATRIX_CELL_COUNT; i++ )
		{
			if( i !=  oriDockIndex &&
				m_HeroPVPDock[i]->boundingBox().containsPoint( ((CCNode *)pSender)->getPosition() ) )
			{
				int j = 0;
				for( ; j < MAX_MATRIX_CELL_COUNT; j++ )
				{
					if( m_HerosDockIndex[j] == i )
						break;
				}

				if( j < MAX_MATRIX_CELL_COUNT )
				{
					// swap
					((CCNode *)pSender)->setPosition( m_HeroPVPDock[i]->getPosition() );
					m_HerosDockIndex[heroIndex] = i;

					m_HeroPVPItems[j]->setPosition( m_HeroPVPDock[oriDockIndex]->getPosition() );
					m_HerosDockIndex[j] = oriDockIndex;
				}
				else
				{
					// move to
					((CCNode *)pSender)->setPosition( m_HeroPVPDock[i]->getPosition() );
					m_HerosDockIndex[heroIndex] = i;
				}

				// inform the pos info
				std::vector<ObjectHero*>  Heroes;
				Heroes.resize(MAX_MATRIX_CELL_COUNT, 0);

				for (X_INT i = 0;i<MAX_MATRIX_CELL_COUNT;i++)
				{
					if( m_HerosDockIndex[i] >= 0 )
					{
						Heroes[m_HerosDockIndex[i]] = m_HeroObjArray[i];
					}
				}


	 
				X_GUID  GuidHero[MAX_MATRIX_CELL_COUNT] = {-1};
				for (int i = 0; i< Heroes.size();++i)
				{
					if (Heroes[i] != NULL)
					{
						GuidHero[i] = Heroes[i]->GetGuid();
					}

				}	
				SendLogicPacket::SetWoodMatrixHeros(GuidHero);

				break;
			}		
		}
		// reset position
		if( i >= MAX_MATRIX_CELL_COUNT )
		{
			((CCNode *)pSender)->setPosition( m_HeroPVPDock[oriDockIndex]->getPosition() );
		}
	}


}

void HeroWoodPVPUIViewHandle::heroNullTouchBeginHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch begin", (int)(((CCNode *)pSender)->getUserData()) );
}

void HeroWoodPVPUIViewHandle::heroNullTouchMoveHook(CCObject* pSender)
{
	//CCLOG( "Hero: %d, touch move", (int)(((CCNode *)pSender)->getUserData()) );
}


void HeroWoodPVPUIViewHandle::heroNullTouchEndHook(CCObject* pSender)
{
	//DataPool::GetSingleton()->SetSelectHero( mHeroObjArray[heroIndex] );
	if (!visable )
	{
		return;
	}
 
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROWOODFIGHTCHOOSE_SHOW);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
}
void HeroWoodPVPUIViewHandle::UpdateSelfWoodData()
{
	CreateHeroPVPNullItem();
	updateWoodLevelUpTime(0);
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	for (X_INT i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{

		ObjectHero *pHero = DataPool::GetSingleton()->GetWoodData()->GetSelfWoodData()->GetSelfMatrixDefHero(i);
		if( NULL == pHero||!pHero->IsDataReady())
		{
			m_HeroObjArray[i] = 0;
			m_HerosDockIndex[i] = -1;
			continue;
		}
		m_HeroObjArray[i] = pHero;

		m_HerosDockIndex[i] = i;



		m_HeroPVPItems[i] = cocos2d::HeroHeadIcon::createWithFile( pHero->GetHeadIcon().c_str(), this, 
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroItemTouchBeginHook), 
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroItemTouchMoveHook),
			callfuncO_selector(HeroWoodPVPUIViewHandle::heroItemTouchEndHook),
			pHero->GetColor(),
			true ,10,pHero->GetLevel());
		m_HeroPVPItems[i]->setPosition( m_HeroPVPDock[i]->getPosition() );
		m_HeroPVPItems[i]->setUserData( ((void*)i) );
		m_HeroPVPDock[i]->getParent()->addChild( m_HeroPVPItems[i], m_HeroPVPDock[i]->getZOrder() + 1 );		

	}
}

void HeroWoodPVPUIViewHandle::UpdateOtherDefWoodData()
{

	WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
	for (X_INT i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		X_INT  tableID = pWoodData->GetRobWoodData()->m_FightHero[i];
		if ( tableID < 0 ) continue;

		string texname;
		if (tableID == pWoodData->GetOtherDefHero()->GetTableID())
		{
			texname = pWoodData->GetOtherDefHero()->GetHeadIcon().c_str();
			m_HeroRobItems[i] = HeroHeadIcon::createWithFile(texname.c_str(),NULL,NULL,NULL,NULL,pWoodData->GetOtherDefHero()->GetColor(),true,10,pWoodData->GetOtherDefHero()->GetLevel());
			m_HeroRobItems[i]->setTouchable(false);
		}
		else
		{
			texname = ObjectHero::getIconById( tableID ).c_str() ;
			//CCSprite *heroFrame = CCSprite::create( GameHelper::GetHeroFrameColorById(herosArray[j].color).c_str());
			m_HeroRobItems[i] = HeroHeadIcon::createWithFile(texname.c_str(),NULL,NULL,NULL,NULL,pWoodData->GetRobWoodData()->m_Color[i],true,10,pWoodData->GetRobWoodData()->m_Level[i]);
			m_HeroRobItems[i]->setTouchable(false);
		}

		m_HeroRobItems[i]->setPosition(m_HeroRobDock[i]->getPosition());
		m_HeroRobDock[i]->getParent()->addChild( m_HeroRobItems[i], m_HeroRobDock[i]->getZOrder() + 1 );	

	}
}

void HeroWoodPVPUIViewHandle::UpdateWoodPVPTextData()
{
	
	WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
	SelfWoodData*  pSelfWoodData = pWoodData->GetSelfWoodData();
	//ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData* pData = DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData();
	char  strBuffer[1024]="";
	CCPoint posHP;

	//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(635),pSelfWoodData->m_WoodData.m_CampLevel);
	//m_HeroPVPLevelLabel->setString(strBuffer);
	sprintf(strBuffer,"%d",pSelfWoodData->m_WoodData.m_CampLevel);
	posHP = ccp(m_HeroPVPLevelLabel->getPosition().x + m_HeroPVPLevelLabel->getContentSize().width*m_HeroPVPLevelLabel->getScaleX() , m_HeroPVPLevelLabel->getPosition().y );
	heroAdditionalValue(strBuffer, posHP,3,1,m_HeroPVPLevelLabel);

	if (pSelfWoodData->GetSelfDefHero() != NULL)
	{
		//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(636),pSelfWoodData->GetSelfDefHero()->GetHP());
		//m_HeroPVPHPLabel->setString(strBuffer)
		sprintf(strBuffer,"%d",pSelfWoodData->GetSelfDefHero()->GetHP());
	 
		posHP = ccp(m_HeroPVPHPLabel->getPosition().x + m_HeroPVPHPLabel->getContentSize().width*m_HeroPVPHPLabel->getScaleX() , m_HeroPVPHPLabel->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,4,1,m_HeroPVPHPLabel);
 
		sprintf(strBuffer,"%d",pSelfWoodData->GetSelfDefHero()->GetPhysicDefence());
		posHP = ccp(m_HeroPVPDefLabel->getPosition().x + m_HeroPVPDefLabel->getContentSize().width*m_HeroPVPDefLabel->getScaleX() , m_HeroPVPDefLabel->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,12,1,m_HeroPVPDefLabel);
	}


	//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(637),pSelfWoodData->m_WoodCreat);
	//m_HeroPVPCreLabel->setString(strBuffer);
	 sprintf(strBuffer,"%d",pSelfWoodData->m_WoodCreat);
	//m_HeroPVPCreLabel->setString(strBuffer);
	 posHP = ccp(m_HeroPVPCreLabel->getPosition().x + m_HeroPVPCreLabel->getContentSize().width *m_HeroPVPCreLabel->getScaleX(), m_HeroPVPCreLabel->getPosition().y );
	 heroAdditionalValue(strBuffer, posHP,5,1,m_HeroPVPCreLabel);

	//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(638),pSelfWoodData->m_WoodData.m_WoodNum,pSelfWoodData->m_WoodCapacity);
	//m_HeroPVPTotalLabel->setString(strBuffer);

	 sprintf(strBuffer,"%d%/%d",pSelfWoodData->m_WoodData.m_WoodNum,pSelfWoodData->m_WoodCapacity);
	 posHP = ccp(m_HeroPVPTotalLabel->getPosition().x + m_HeroPVPTotalLabel->getContentSize().width *m_HeroPVPTotalLabel->getScaleX(), m_HeroPVPTotalLabel->getPosition().y );
	 heroAdditionalValue(strBuffer, posHP,6,1,m_HeroPVPTotalLabel);

	if (pWoodData->GetOtherDefHero() != NULL)
	{
		sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(639),pWoodData->GetRobWoodData()->m_Name,pWoodData->GetRobWoodData()->m_CampLevel);
		m_HeroRobLevelLabel->setString(strBuffer);
		m_HeroRevengeLevelLabel->setString(strBuffer);
		 

		//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(636),pWoodData->GetOtherDefHero()->GetHP());
		//m_HeroRobHPLabel->setString(strBuffer);
		//m_HeroRevengeHPLabel->setString(strBuffer);


		sprintf(strBuffer,"%d",pWoodData->GetOtherDefHero()->GetHP());

		posHP = ccp(m_HeroRobHPLabel->getPosition().x + m_HeroRobHPLabel->getContentSize().width *m_HeroRobHPLabel->getScaleX(), m_HeroRobHPLabel->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,7,1,m_HeroRobHPLabel);
   
		posHP = ccp(m_HeroRevengeHPLabel->getPosition().x + m_HeroRevengeHPLabel->getContentSize().width*m_HeroRevengeHPLabel->getScaleX() , m_HeroRevengeHPLabel->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,8,1,m_HeroRevengeHPLabel);

		sprintf(strBuffer,"%d",pSelfWoodData->GetSelfDefHero()->GetPhysicDefence());
		posHP = ccp(m_RevengeDef->getPosition().x + m_RevengeDef->getContentSize().width*m_RevengeDef->getScaleX() , m_RevengeDef->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,13,1,m_RevengeDef);

		posHP = ccp(m_RobDef->getPosition().x + m_RobDef->getContentSize().width*m_RobDef->getScaleX() , m_RobDef->getPosition().y );
		heroAdditionalValue(strBuffer, posHP,14,1,m_RobDef);
 
	}

	//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(640),pWoodData->GetRobWoodData()->m_RobWoodNum);
	//m_HeroRobWoodLabel->setString(strBuffer);
	//m_HeroRevengeWoodLabel->setString(strBuffer);

	sprintf(strBuffer,"%d",pWoodData->GetRobWoodData()->m_RobWoodNum);

	posHP = ccp(m_HeroRobWoodLabel->getPosition().x + m_HeroRobWoodLabel->getContentSize().width*m_HeroRobWoodLabel->getScaleX() , m_HeroRobWoodLabel->getPosition().y );
	heroAdditionalValue(strBuffer, posHP,9,1,m_HeroRobWoodLabel);

	posHP = ccp(m_HeroRevengeWoodLabel->getPosition().x + m_HeroRevengeWoodLabel->getContentSize().width*m_HeroRevengeWoodLabel->getScaleX() , m_HeroRevengeWoodLabel->getPosition().y );
	heroAdditionalValue(strBuffer, posHP,10,1,m_HeroRevengeWoodLabel);


	 
	//sprintf(strBuffer,UtilTools::GET_TEXT_FROM_LANG(642),pWoodData->GetRobWoodData()->m_RobCount,pWoodData->GetRobWoodData()->m_RobMaxCount);
	//m_HeroRobTimesButtonLabel->setString(strBuffer);

	sprintf(strBuffer,"%d%/%d",pWoodData->GetRobWoodData()->m_RobCount,pWoodData->GetRobWoodData()->m_RobMaxCount);
	posHP = ccp(m_RobNum->getPosition().x + m_RobNum->getContentSize().width*m_RobNum->getScaleX() , m_RobNum->getPosition().y );
	heroAdditionalValue(strBuffer, posHP,11,1,m_RobNum);
	CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage( "wood_pipei_next.png");
	m_HeroRemachButtonLabel->setTexture(texture2D1);

	
}

void HeroWoodPVPUIViewHandle::UpdateRevengeWoodData()
{

	WoodsData *pWoodData = DataPool::GetSingleton()->GetWoodData();
	for (X_INT i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		X_INT  tableID = pWoodData->GetRobWoodData()->m_FightHero[i];
		if ( tableID < 0 ) continue;

		string texname;
		if (tableID == pWoodData->GetOtherDefHero()->GetTableID())
		{
			texname = pWoodData->GetOtherDefHero()->GetHeadIcon();
			m_HeroRevengeItems[i] = HeroHeadIcon::createWithFile(texname.c_str(),NULL,NULL,NULL,NULL,pWoodData->GetOtherDefHero()->GetColor(),true,10,pWoodData->GetOtherDefHero()->GetLevel());		
		}
		else
		{
			texname = ObjectHero::getIconById( tableID ) ;
			m_HeroRevengeItems[i] = HeroHeadIcon::createWithFile(texname.c_str(),NULL,NULL,NULL,NULL,pWoodData->GetRobWoodData()->m_Color[i],true,10,pWoodData->GetRobWoodData()->m_Level[i]);
		}
		m_HeroRevengeItems[i]->setTouchable(false);

		m_HeroRevengeItems[i]->setPosition(m_HeroRevengeDock[i]->getPosition());
		m_HeroRevengeDock[i]->getParent()->addChild( m_HeroRevengeItems[i], m_HeroRevengeDock[i]->getZOrder() + 1 );	

	}
}
void HeroWoodPVPUIViewHandle::ClearData()
{
	for (X_INT i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		if( m_HeroPVPItems[i] != NULL)
		{
			m_HeroPVPItems[i]->removeFromParentAndCleanup( true );
			m_HeroPVPItems[i] = NULL;
		}
		if( m_HeroRobItems[i] != NULL)
		{
			m_HeroRobItems[i]->removeFromParentAndCleanup( true );
			m_HeroRobItems[i] = NULL;
		}
		if(m_HeroPVPNullItems[i] != NULL)
		{
			m_HeroPVPNullItems[i]->removeFromParentAndCleanup( true );
			m_HeroPVPNullItems[i] = NULL;
		}
		if (m_HeroRevengeItems[i] != NULL)
		{
			m_HeroRevengeItems[i]->removeFromParentAndCleanup( true );
			m_HeroRevengeItems[i] = NULL;
		}

	}
}

void HeroWoodPVPUIViewHandle::SetLayerDisable()
{
	m_HeroRevengeLayer->setVisible(false);
	m_HeroRobLayer->setVisible(false);
	m_HeroPVPLayer->setVisible(false);
	visable = false;

}
void HeroWoodPVPUIViewHandle::onButtonChangeHero()
{
	heroNullTouchEndHook(NULL);
}

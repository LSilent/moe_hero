#include "./ui/EscortWoodUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./ui/element/CCMenuEx.h"
#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "./datapool/QuJingData.h"
#include "./ui/element/LogicTouchItem.h"
#include "./object/ObjectManager.h"
#include "./DataBase/DataBaseSystem.h"
#include "./ui/EscortWoodUI.h"

using namespace cocos2d;
USING_NS_CC_EXT;

 

#define SPRITE_SPACE        (6)
#define SPRITE_WIDTH        (120)


EscortWoodUIView::EscortWoodUIView()
{
		mLJNum = 0;
		mHSTime = 0;
		mNodePos = 0;
		mButtonSpeedUp = 0;
		mButtonBuzhen = 0;
		mButtonYaYun = 0;
		mButtonHideSprite = 0;
		mNodeBuZhen = 0;
		for (int i =0;i<MAX_MATRIX_CELL_COUNT;i++)
		{
			m_heroItems[i] = 0;
			mHeroDock[i] = 0;

			mHeroObjArray[i] = 0;
			mHerosDockIndex[i] = -1;
		}
		mButtonFighter = 0;
		mNodeshiZheXinxi = 0;
		mShiZheSprite = 0;
		mShiZheName = 0;
		mShiZheLevel = 0;
		mShiZheZhuRen = 0;
		mShiZheTime = 0;
		mShiZheJiangLi = 0;
		mShiZheLJNum = 0;
		mShiZheLJGet = 0;
		mShiZheLJBtn = 0;
		mShiZheLJCancel = 0;
		mSelfTipNode = 0;
		mContent = NULL;
		mIsDragMove = false;
		m_Sprites.clear();
		mSpriteContent = 0;
		m_visbleXJL =true;
		mShiZheColor = 0;
}

EscortWoodUIView::~EscortWoodUIView()
{
	CC_SAFE_RELEASE(mSelfTipNode);
	CC_SAFE_RELEASE(mLJNum);
	CC_SAFE_RELEASE(mHSTime);
	CC_SAFE_RELEASE(mNodePos);
	CC_SAFE_RELEASE(mButtonSpeedUp);
	CC_SAFE_RELEASE(mButtonBuzhen);
	CC_SAFE_RELEASE(mButtonHideSprite);
	CC_SAFE_RELEASE(mNodeBuZhen);
	CC_SAFE_RELEASE(mButtonFighter);
	CC_SAFE_RELEASE(mNodeshiZheXinxi);
	CC_SAFE_RELEASE(mShiZheSprite);
	CC_SAFE_RELEASE(mShiZheColor);
	
	CC_SAFE_RELEASE(mShiZheName);
	CC_SAFE_RELEASE(mShiZheLevel);
	CC_SAFE_RELEASE(mShiZheZhuRen);
	CC_SAFE_RELEASE(mShiZheTime);
	CC_SAFE_RELEASE(mShiZheJiangLi);
	CC_SAFE_RELEASE(mShiZheLJNum);
	CC_SAFE_RELEASE(mShiZheLJGet);
	CC_SAFE_RELEASE(mShiZheLJBtn);
	CC_SAFE_RELEASE(mShiZheLJCancel);
 
	for( int i = 0; i < MAX_MATRIX_CELL_COUNT; i++ )
	{
		CC_SAFE_RELEASE(mHeroDock[i]);
		 
	}
	CC_SAFE_RELEASE(mSpriteContent);

}

void EscortWoodUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	/*(for (int i = 0 ;i< MAX_MATRIX_CELL_COUNT;i++)
	{
		cocos2d::LogicTouchItem* nullItem = cocos2d::LogicTouchItem::createWithFile( "pos_null.png", this, callfuncO_selector(EscortWoodUIView::heroNullTouchBeginHook), 
			callfuncO_selector(EscortWoodUIView::heroNullTouchMoveHook),
			callfuncO_selector(EscortWoodUIView::heroNullTouchEndHook),
			false, 20 );

		nullItem->setPosition( mHeroDock[i]->getPosition() );
		nullItem->setUserData( ((void*)i) );
		mHeroDock[i]->getParent()->addChild( nullItem );

	}*/

	onDataUpdate( false );
}
void EscortWoodUIView::heroNullTouchBeginHook(CCObject* pSender)
{
	 
}

void EscortWoodUIView::heroNullTouchMoveHook(CCObject* pSender)
{
 
}
void EscortWoodUIView::heroNullTouchEndHook(CCObject* pSender)
{
 
}

SEL_MenuHandler EscortWoodUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonSpeedUp", EscortWoodUIView::onButtonSpeedUp);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonBuzhen", EscortWoodUIView::onButtonBuzhen);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonYaYun", EscortWoodUIView::onButtonYaYun);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonHideSprite", EscortWoodUIView::onButtonHideSprite);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonFighter", EscortWoodUIView::onButtonFighter);

	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShiZheLJBtn", EscortWoodUIView::onShiZheLJBtn);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShiZheLJCancel", EscortWoodUIView::onShiZheLJCancel);
 	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", EscortWoodUIView::onButtonClose);
    return NULL;    
}

SEL_CCControlHandler EscortWoodUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	


	return NULL;
}
void EscortWoodUIView::onShiZheLJBtn(cocos2d::CCObject * pSender)
{
	//X_CLIENT_GUID guid =  ((X_CLIENT_GUID ) static_cast<CCNode*>(pSender)->getUserData());

	QuJingPlayerData*   p = (QuJingPlayerData* ) (static_cast<CCNode*>(pSender)->getUserData());
	if (!p )
	{
		return;
	}
	QuJingData* pData = DataPool::GetSingleton()->GetQuJingData();
	if (pData&& pData->GetRobTimes()<= 0)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(252);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}
		return;
	}

	EscortWoodUI *pUi =  (EscortWoodUI*) (getUserData());
	if (!pUi)return;
	pUi->m_bShowBuzhen = false;
	SendLogicPacket::QuJingRob(p->m_GUID.GetValue());
 
}
void EscortWoodUIView::onShiZheLJCancel(cocos2d::CCObject * pSender)
{
	showShiZheView(false,-1);
}
void EscortWoodUIView::onButtonBuzhen(cocos2d::CCObject * pSender)
{
	EscortWoodUI *pUi =  (EscortWoodUI*) (getUserData());
	if (!pUi)return;
	pUi->m_bShowBuzhen = true;

	 showBuZhenView(true);
}
void EscortWoodUIView::onButtonSpeedUp(cocos2d::CCObject * pSender)
{
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	QuJingPlayerData* pSelfQuJing = pData->findPlayerDataByData(pSelf->GetGuid());
	if (!pSelfQuJing)
	{
		return;
	}
	const stDBC_FILE_QUJING  * pTableData = QuJingData::getTableDataById(pSelfQuJing->m_HuSongID);
	if (!pTableData)
	{
		return;
	}
	
	if (pTableData->speedUp1 > 0)
	{
		char buff[256] = {0};
		sprintf(buff,UtilTools::GET_TEXT_FROM_LANG(690),pTableData->speedUp1,pTableData->speeduptime);
		ModalDialogView *dialog = ModalDialogView::createDialog(buff,this);
		addChild(dialog,110);
	}else
	{
		ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
		SendLogicPacket::QuJingSpeedUp(pSelf->GetGuid(),0);
	}
	 

}
void EscortWoodUIView::onButtonYaYun(cocos2d::CCObject * pSender)
{
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	QuJingPlayerData* pSelfQuJing = pData->findPlayerDataByData(pSelf->GetGuid());
	if (pSelfQuJing)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(688);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		}
		return;
	}

	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_WOODSHIZHE_SHOW);
	
}
void EscortWoodUIView::onButtonHideSprite(cocos2d::CCObject * pSender)
{
	m_visbleXJL = !m_visbleXJL;
}
void EscortWoodUIView::onButtonFighter(cocos2d::CCObject * pSender)
{
	showBuZhenView(false);
}
void EscortWoodUIView::onButtonClose(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_LVL_ESCORTWOOD_CLOSE);
}



bool EscortWoodUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLJNum", CCLabelTTF *, mLJNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHSTime", CCLabelTTF *, mHSTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePos", CCNode *, mNodePos);


	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonSpeedUp", CCMenuItem *, mButtonSpeedUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonBuzhen", CCMenuItem *, mButtonBuzhen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonYaYun", CCMenuItem *, mButtonYaYun);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonHideSprite", CCMenuItem *, mButtonHideSprite);

 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos1", CCSprite *, mHeroDock[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos2", CCSprite *, mHeroDock[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos3", CCSprite *, mHeroDock[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos4", CCSprite *, mHeroDock[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos5", CCSprite *, mHeroDock[4]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mPos6", CCSprite *, mHeroDock[5]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonFighter", CCMenuItem *, mButtonFighter);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeshiZheXinxi", CCNode *, mNodeshiZheXinxi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite", CCSprite *, mShiZheSprite);
 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheName", CCLabelTTF *, mShiZheName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLevel", CCLabelTTF *, mShiZheLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheZhuRen", CCLabelTTF *, mShiZheZhuRen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheTime", CCLabelTTF *, mShiZheTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheJiangLi", CCLabelTTF *, mShiZheJiangLi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLJNum", CCLabelTTF *, mShiZheLJNum);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLJGet", CCLabelTTF *, mShiZheLJGet);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLJBtn", CCMenuItem *, mShiZheLJBtn);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLJCancel", CCMenuItem *, mShiZheLJCancel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSelfTiPNode", CCNode *,mSelfTipNode);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeBuZhen", CCNode *, mNodeBuZhen);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheColor", CCSprite *, mShiZheColor);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSpriteContent", CCNode *, mSpriteContent);
	
	
	
    return false;
}

bool EscortWoodUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool EscortWoodUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}
void EscortWoodUIView::onEnter()
{
	BaseView::onEnter();

	schedule( schedule_selector(EscortWoodUIView::updateHuSongTime), 0.2f );
}

void EscortWoodUIView::onExit()
{
	unschedule( schedule_selector(EscortWoodUIView::updateHuSongTime) );

	BaseView::onExit();
}
void EscortWoodUIView::updateHuSongTime( float time )
{
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();

	QuJingPlayerData* pSelfQuJing = 0;
	if (pSelf)
	{
		pSelfQuJing = pData->findPlayerDataByData(pSelf->GetGuid());
	}

	if (pSelfQuJing)
	{
		X_INT  milliSecond =  pSelfQuJing->m_time;
		if( milliSecond > 0 )
		{
			string timeStr =  UtilTools::ConvertMillisecondToTimeString( milliSecond );
			if (timeStr.size() >3)
			{
				timeStr =timeStr.substr(3);
			}
			
			mHSTime->setString( (UtilTools::GET_TEXT_FROM_LANG(691) +  timeStr).c_str());
		} else
		{
			mHSTime->setString("00:00");
		}
		mButtonYaYun->setEnabled(false);
		mButtonYaYun->setColor(ccGRAY);
	} else
	{
		mButtonYaYun->setEnabled(true);
		mButtonYaYun->setColor(ccWHITE);
	}
	m_Sprites.clear();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	mSpriteContent->removeAllChildrenWithCleanup(true);
	vector <QuJingPlayerData*> players = pData->getPlayers();
	X_INT size = players.size();
	if (size <=0)
	{
		return;
	}
	QuJingPlayerData* pPlayer = X_NULL;
	 
	string str;
	m_Sprites.resize(size,0);
	for (X_INT i =0;i<size;i++)
	{
		pPlayer = players[i];
		if (!pPlayer)continue;

		str = "qj_xjl.png";
		const stDBC_FILE_QUJING  * pData = QuJingData::getTableDataById(pPlayer->m_HuSongID);
		if (pData&&pData->visual!="-1")
			{
				str = pData->visual_action;
			}
		TouchButtonEx *pTb = TouchButtonEx::create(str.c_str(),this,callfuncO_selector(EscortWoodUIView::sel_Sprite));
		//m_Sprites.push_back(pTb);
		m_Sprites[i] = pTb;
		pTb->setUserData((void*)(pPlayer));
		if( pPlayer->m_HuSongID == 1)
		{
			pTb->setVisible(m_visbleXJL);
		}	
	}
	size = m_Sprites.size();
	X_INT lineNum = (winSize.width - SPRITE_SPACE)/(SPRITE_SPACE+SPRITE_WIDTH);

	const char *qualityItems[5] = {
		"qj_color1.png",
		"qj_color2.png",
		"qj_color3.png",
		"qj_color4.png",
		"qj_color5.png",
	};
	for (X_INT i = 0 ;i < size;i++ )
	{
		TouchButtonEx *pSprite = m_Sprites[i];
		if (!pSprite)
		{
			continue;
		}
		
		pPlayer = (QuJingPlayerData* ) pSprite->getUserData();
		if (!pPlayer)continue;
		X_FLOAT x = (i%lineNum )*(SPRITE_WIDTH+SPRITE_SPACE) + SPRITE_SPACE+ SPRITE_WIDTH*0.5f; //
		X_FLOAT y =(mSpriteContent->getContentSize().height -SPRITE_WIDTH*0.5f )  *(1.f- pPlayer->getPerCent()) + SPRITE_WIDTH*0.5f; //
		pSprite->setPosition(CCPoint(x,y));
		
 
		X_INT id = pPlayer->m_HuSongID-1;
		if (id >= 0 && id < 5 )
		{
			CCSprite* spriteBack = CCSprite::create(qualityItems[id ]);
			spriteBack->setPosition(CCPoint(x,y));
		//	mSpriteContent->addChild(spriteBack);
			if( pPlayer->m_HuSongID == 1)
			{
				spriteBack->setVisible(m_visbleXJL);
			}	
		} 
		
		mSpriteContent->addChild(pSprite);
		if (pSelfQuJing == pPlayer)
		{
			CCSprite* spriteSelfFlag = CCSprite::create("n_qj_selfflag.png");
			spriteSelfFlag->setPosition(CCPoint(x+SPRITE_WIDTH*0.5f,y-SPRITE_WIDTH*0.5f));
			spriteSelfFlag->setAnchorPoint(CCPoint(1.0f,0.f));
			mSpriteContent->addChild(spriteSelfFlag);
			if( pPlayer->m_HuSongID == 1)
			{
				spriteSelfFlag->setVisible(m_visbleXJL);
			}	
		}

	}
}

void EscortWoodUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{

		return;
	}
	if( mContent )
		mContent->removeFromParentAndCleanup( true );
	mContent = CCNode::create();
	addChild( mContent );

	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	QuJingPlayerData* pSelfQuJing = pData->findPlayerDataByData(pSelf->GetGuid());
	
	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(653),pData->GetRobTimes());
	mLJNum->setString(temp);

	if (pSelfQuJing)
	{
		mSelfTipNode->setVisible(true);
		mButtonSpeedUp->setVisible(true);
	}else
	{
		mSelfTipNode->setVisible(false);
		mButtonSpeedUp->setVisible(false);
	}
	updateHuSongTime(0);
	 

	EscortWoodUI *pUi =  (EscortWoodUI*) (getUserData());
	if (!pUi)return;
	showBuZhenView(pUi->m_bShowBuzhen );


}
void EscortWoodUIView::sel_Sprite(CCObject* pObject)
{
	//X_CLIENT_GUID guid =  ((X_CLIENT_GUID ) static_cast<CCNode*>(pObject)->getUserData());
	QuJingPlayerData*   p = (QuJingPlayerData* ) (static_cast<CCNode*>(pObject)->getUserData());
	if (!p )
	{
		return;
	}
	 showShiZheView(true,p->m_GUID.GetValue());

}
X_VOID  EscortWoodUIView::showShiZheView(bool b,X_CLIENT_GUID guid)
{

	showBuZhenView(false);
	mNodeshiZheXinxi->setVisible(b);
	mNodeshiZheXinxi->setPosition(mNodePos->getPosition());

	if ( !b)
	{
		return;
	}
	mNodeshiZheXinxi->setZOrder(100);
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)
	{
		return;
	}
    ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	QuJingPlayerData* pQuJing = pData->findPlayerDataByData(guid);
	if (!pQuJing )
	{
		return;
	}
	
	X_CHAR temp[256] = {0};

	const stDBC_FILE_QUJING  * pTData = QuJingData::getTableDataById(pQuJing->m_HuSongID);
	if (pTData)
	{

		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(657),pTData->name);
		mShiZheName->setString(temp);
	}else
	{
			mShiZheName->setString("");
	}


	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(692),pQuJing->m_Level);
	mShiZheLevel->setString(temp);
	
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(650),pQuJing->m_Name.c_str());
	mShiZheZhuRen->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(660),UtilTools::ConvertMillisecondToTimeString(pQuJing->m_time).c_str());
	mShiZheTime->setString(temp);

  
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(655),pQuJing->m_TotalWood,pQuJing->m_TotalExp);
	mShiZheJiangLi->setString(temp);
	 
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(661),pQuJing->m_BeRobWood,pQuJing->m_BeRobExp);
	mShiZheLJGet->setString(temp);
 
	const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
	const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_MAX_HUSONG_BEROB_DAY_TIMES);
	if (pTableData)
	{
		memset(temp,0,sizeof(temp));
		sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(662),pQuJing->m_BeRobTimes, pTableData->m_value);
		mShiZheLJNum->setString(temp);
	 
	}else
	{
		mShiZheLJNum->setString("");
	}
	const stDBC_FILE_QUJING  * pTableDataQu = QuJingData::getTableDataById(pQuJing->m_HuSongID);
 
	 
	if (pTableDataQu)
	{
		const char *qualityItems[5] = {
			"qj_color1.png",
			"qj_color2.png",
			"qj_color3.png",
			"qj_color4.png",
			"qj_color5.png",
		};
		CCTexture2D *tx = CCTextureCache::sharedTextureCache()->addImage(qualityItems[pQuJing->m_HuSongID-1]);
		mShiZheColor->setTexture(tx);
		string str = "qj_xjl.png";
		if (pTableDataQu&&pTableDataQu->visual!="-1")
		{
			str = pTableDataQu->visual;
		}
		CCTexture2D *tx1 = CCTextureCache::sharedTextureCache()->addImage(str.c_str());
		mShiZheSprite->setTexture(tx1);

	}
	
	if(guid == pSelf->GetGuid())
	{
		mShiZheLJBtn->setEnabled(false);
		mShiZheLJBtn->setColor(ccGRAY);
	}else
	{
		mShiZheLJBtn->setEnabled(true);
		mShiZheLJBtn->setColor(ccWHITE);
	}


	mShiZheLJBtn->setUserData((void*)(pQuJing));

}
X_VOID  EscortWoodUIView::showBuZhenView(bool b)
{
	 mNodeBuZhen->setVisible(b);
	 mNodeBuZhen->setPosition(mNodePos->getPosition());
	 mNodeBuZhen->setZOrder(100);
	 if ( !b)
	 {
		 EscortWoodUI *pUi =  (EscortWoodUI*) (getUserData());
		 if (!pUi)return;
		 	pUi->m_bShowBuzhen = false;
		 return;
	 }
	 
	 QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();

	 if (!pData)
	 {
		 return;
	 }
	 ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	 const X_GUID* guid = pData->GetHeroGuid();
	 ObjectHero* pHero = 0;
	 for(X_INT i=0;i<MAX_MATRIX_CELL_COUNT;++i)
	 {
		  pHero = static_cast<ObjectHero*> (DataPool::GetSingleton()->getObjectManager()->FindInstance(OBJECT_TYPE_HERO,guid[i].GetValue()));

		  if( m_heroItems[i] )
		  {
			  m_heroItems[i]->removeFromParentAndCleanup( true );
			  m_heroItems[i] = NULL;
		  }
		  if( !pHero || !pHero->IsDataReady())
		  {
			  mHeroObjArray[i] = 0;
			  mHerosDockIndex[i] = -1;
			  continue;
		  }

		  mHeroObjArray[i] = pHero;
		  mHerosDockIndex[i] = i;
		  m_heroItems[i] = cocos2d::HeroHeadIcon::createWithFile( pHero->GetHeadIcon().c_str(), this, callfuncO_selector(EscortWoodUIView::heroItemTouchBeginHook), 
			  callfuncO_selector(EscortWoodUIView::heroItemTouchMoveHook),
			  callfuncO_selector(EscortWoodUIView::heroItemTouchEndHook),
			  pHero->GetColor(),
			  true,-100, pHero->GetLevel());
		  m_heroItems[i]->setPosition( mHeroDock[mHerosDockIndex[i]]->getPosition() );
		  m_heroItems[i]->setScale(0.86f);
		  m_heroItems[i]->setUserData( ((void*)i) );
		  mHeroDock[mHerosDockIndex[i]]->getParent()->addChild( m_heroItems[i], mHeroDock[mHerosDockIndex[i]]->getZOrder() + 1 );		

	 }
	  
}


void EscortWoodUIView::heroItemTouchBeginHook(CCObject* pSender)
{
	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() + 10 );
	mIsDragMove = false;
}

void EscortWoodUIView::heroItemTouchMoveHook(CCObject* pSender)
{
	mIsDragMove = true;
}

void EscortWoodUIView::heroItemTouchEndHook(CCObject* pSender)
{
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
	((CCNode *)pSender)->getParent()->reorderChild( ((CCNode *)pSender), ((CCNode *)pSender)->getZOrder() - 10 );
	int heroIndex = (int)(((CCNode *)pSender)->getUserData());

	if( !mIsDragMove )
	{
		if( mHeroObjArray[heroIndex] )
		{
			//DataPool::GetSingleton()->SetSelectHero( mHeroObjArray[heroIndex] );
			//EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROINFO_SHOW);
		}
	}
	else
	{
		int oriDockIndex = mHerosDockIndex[heroIndex];
		assert( oriDockIndex >= 0 );

		CCPoint dropPos = ((CCNode *)pSender)->getPosition();

		int i = 0;
		for( ; i < MAX_MATRIX_CELL_COUNT; i++ )
		{
			if( i !=  oriDockIndex &&
				mHeroDock[i]->boundingBox().containsPoint( ((CCNode *)pSender)->getPosition() ) )
			{
				int j = 0;
				for( ; j < MAX_MATRIX_CELL_COUNT; j++ )
				{
					if( mHerosDockIndex[j] == i )
						break;
				}

				if( j < MAX_MATRIX_CELL_COUNT )
				{
					((CCNode *)pSender)->setPosition( mHeroDock[i]->getPosition() );
					mHerosDockIndex[heroIndex] = i;

					m_heroItems[j]->setPosition( mHeroDock[oriDockIndex]->getPosition() );
					mHerosDockIndex[j] = oriDockIndex;
				}
				else
				{
					((CCNode *)pSender)->setPosition( mHeroDock[i]->getPosition() );
					mHerosDockIndex[heroIndex] = i;
				}
				std::vector<ObjectHero*>  Heroes;
				Heroes.clear();
				Heroes.resize(MAX_MATRIX_CELL_COUNT, 0);

				for (X_INT i = 0;i<MAX_MATRIX_CELL_COUNT;i++)
				{
					if( mHerosDockIndex[i] >= 0 )
					{
						Heroes[mHerosDockIndex[i]] = mHeroObjArray[i];
					}
				}
				X_GUID guid[MAX_MATRIX_CELL_COUNT] = {INVALID_ID};

				for (X_INT i =0;i<MAX_MATRIX_CELL_COUNT;i++)
				{
					if (Heroes[i])
					{
						guid[i] =  Heroes[i]->GetGuid();
					}
				}
				SendLogicPacket::QuJingSetMatrixt(guid);
				break;
			}		
		}
		if( i >= MAX_MATRIX_CELL_COUNT )
		{
			((CCNode *)pSender)->setPosition( mHeroDock[oriDockIndex]->getPosition() );
		}
	}
}
void EscortWoodUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	ObjectSelf* pSelf =DataPool::GetSingleton()->getObjectManager()->getSelf();
	SendLogicPacket::QuJingSpeedUp(pSelf->GetGuid(),0);
	pSender->closeDialogView();
}
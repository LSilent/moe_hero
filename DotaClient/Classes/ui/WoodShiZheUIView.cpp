#include "./ui/WoodShiZheUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./object/ObjectSkill.h"
#include "./object/ItemEquip.h"
#include "./ui/element/CCMenuEx.h"
#include "./datapool/QuJingData.h"
#include "./ui/element/LogicTouchItem.h"
#include "./object/ObjectManager.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define LOGO_POS_X              (0.5f)
#define LOGO_POS_Y              (0.745f)

#define STAR_POS_START_X        (0.35f)
#define STAR_POS_DELTA_X        (0.08f)
#define STAR_POS_Y              (0.57f)

#define MAX_USER_LEVLE			75

WoodShiZheUIView::WoodShiZheUIView()
{
		 
	mNodePos = 0;
	mHuSongTip1= NULL;
	mWoodAward= NULL;
	mHuSongTime= NULL;
	mButtoReFresh= NULL;
	mButtonGetJQR= NULL;
	mButtonStartYaYun= NULL;
	mNodeshiZheXinxi = 0;
	mShiZheSprite = 0;
	mShiZheColor = 0;
	mShiZheName = 0;
	mShiZheLevel = 0;
	mShiZheTime = 0;
	mShiZheJiangLi = 0;
	mShiZheCancel= 0;
  	mContent = NULL;
	for (X_INT i =0;i<5;i++)
	{
		mShiZheSprites[i] = 0;
		mShiZheTouchSprites[i] = 0;
	}
	mExpward = 0;
	mWoodAward= 0;
	 
}

WoodShiZheUIView::~WoodShiZheUIView()
{
	CC_SAFE_RELEASE(mNodePos);
	CC_SAFE_RELEASE(mHuSongTip1);
	CC_SAFE_RELEASE( mWoodAward);
	CC_SAFE_RELEASE(mExpward);
	CC_SAFE_RELEASE(mHuSongTime );
	CC_SAFE_RELEASE(mButtoReFresh );
	CC_SAFE_RELEASE(  mButtonGetJQR );
	CC_SAFE_RELEASE(mButtonStartYaYun );
	CC_SAFE_RELEASE( mNodeshiZheXinxi);
	CC_SAFE_RELEASE(mShiZheSprite );
	CC_SAFE_RELEASE(mShiZheColor );
	CC_SAFE_RELEASE(mShiZheName );
	CC_SAFE_RELEASE( mShiZheLevel);
	CC_SAFE_RELEASE(mShiZheTime );
	CC_SAFE_RELEASE( mShiZheJiangLi);
	CC_SAFE_RELEASE(mShiZheCancel);
	for (X_INT i =0;i<5;i++)
	{
		CC_SAFE_RELEASE(mShiZheSprites[i]);
	}
}

void WoodShiZheUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	mNodeshiZheXinxi->setVisible(false);
	onDataUpdate( false );
}
void WoodShiZheUIView::MenuItemCallback(cocos2d::CCObject *pSender)
{
	 
}


SEL_MenuHandler WoodShiZheUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onShiZheCancel", WoodShiZheUIView::onShiZheCancel);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonGetJQR", WoodShiZheUIView::onButtonGetJQR);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonReFresh", WoodShiZheUIView::onButtonReFresh);
	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonStartYaYun", WoodShiZheUIView::onButtonStartYaYun);
 	 CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonClose", WoodShiZheUIView::onButtonClose);
 
    return NULL;    
}

SEL_CCControlHandler WoodShiZheUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	


	return NULL;
}
void WoodShiZheUIView::onShiZheCancel(cocos2d::CCObject * pSender)
{
	 	showShiZheView(-1,false);
}
void WoodShiZheUIView::onButtonGetJQR(cocos2d::CCObject * pSender)
{
	 freshShizhe(true);
}
void WoodShiZheUIView::onButtonReFresh(cocos2d::CCObject * pSender)
{
	freshShizhe();
  
}
X_VOID	WoodShiZheUIView::freshShizhe(bool btop)
{
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)return;
	X_INT id = pData->GetCurrentHuSongID();//1-5

	if (id >= 5)
	{
		vector<string> strV;strV.clear();
		strV.push_back(UtilTools::GET_TEXT_FROM_LANG(250));
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return;
	}
	const stDBC_FILE_QUJING  * pTabData = X_NULL;
	if (btop)
	{
		 pTabData = QuJingData::getTableDataById(5);
	}else
	{
		 pTabData = QuJingData::getTableDataById(id+1);
	}
	
	if (!pTabData)return;

	if (pTabData->upCost <= 0)
	{
		SendLogicPacket::QuJingRefreshShiZhe();
	}else
	{
		X_CHAR buffer[256] ={0};
		sprintf(buffer,UtilTools::GET_TEXT_FROM_LANG(656),pTabData->upCost);
		ModalDialogView *dialogPur = X_NULL;
		if (!btop)
		{
		
			dialogPur = ModalDialogView::createDialog( buffer,this);
			dialogPur->setTag(0);
		}else
		{
			const DataBase* pDataFile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_CONFIG);
			const stDBC_FILE_CONFIG *pTableData =  (const stDBC_FILE_CONFIG *) pDataFile->GetFieldsByIndexKey(EM_ZHAO_MU_JIQIREN);
			if (pTableData)
			{
				sprintf(buffer,UtilTools::GET_TEXT_FROM_LANG(666),pTableData->m_value);
			}
			dialogPur = ModalDialogView::createDialog( buffer,this);
			dialogPur->setTag(1);
		}
		addChild(dialogPur,10);
	}
}
void WoodShiZheUIView::onButtonStartYaYun(cocos2d::CCObject * pSender)
{
	QuJingData* pData = DataPool::GetSingleton()->GetQuJingData();
	if (pData&& pData->GetHuSongTimes()<=0)
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(251);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}
		return;
	}
	
	SendLogicPacket::QuJingHuSong();
	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_WOODSHIZHE_CLOSE);
}
void	WoodShiZheUIView::onButtonClose(cocos2d::CCObject * pSender)
{

	EventSystem::GetSingleton()->PushEvent(GAME_EVNET_WOODSHIZHE_CLOSE);
}
 
bool WoodShiZheUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHuSongTip1", CCLabelTTF *, mHuSongTip1);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodePos", CCNode *, mNodePos);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonStartYaYun", CCMenuItem *, mButtonStartYaYun);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtonGetJQR", CCMenuItem *, mButtonGetJQR);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mButtoReFresh", CCMenuItem *, mButtoReFresh);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheCancel", CCMenuItem *, mShiZheCancel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mNodeshiZheXinxi", CCNode *, mNodeshiZheXinxi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite", CCSprite *, mShiZheSprite);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheColor", CCSprite *, mShiZheColor);
 	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheName", CCLabelTTF *, mShiZheName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheLevel", CCLabelTTF *, mShiZheLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheTime", CCLabelTTF *, mShiZheTime);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheJiangLi", CCLabelTTF *, mShiZheJiangLi);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mWoodAward", CCLabelTTF *, mWoodAward);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mExpAward", CCLabelTTF *, mExpward);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mHuSongTime", CCLabelTTF *, mHuSongTime);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite1", CCSprite *, mShiZheSprites[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite2", CCSprite *, mShiZheSprites[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite3", CCSprite *, mShiZheSprites[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite4", CCSprite *, mShiZheSprites[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mShiZheSprite5", CCSprite *, mShiZheSprites[4]);
    return false;
}

bool WoodShiZheUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool WoodShiZheUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}
void WoodShiZheUIView::onEnter()
{
	BaseView::onEnter();
}

void WoodShiZheUIView::onExit()
{
	BaseView::onExit();
}
void WoodShiZheUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		return;
	}
	if( mContent )
		mContent->removeFromParentAndCleanup( true );
	mContent = CCNode::create();
	addChild( mContent );

	string str = "qj_xjl.png";
	for (X_INT i =0;i<5;i++)
	{
		const stDBC_FILE_QUJING  * pData = QuJingData::getTableDataById(i+1);
		if (pData&&pData->visual!="-1")
		{
			str = pData->visual;
		}
		mShiZheTouchSprites[i] = TouchButtonEx::create(str.c_str(),this,callfuncO_selector(WoodShiZheUIView::sel_Sprite));
		mShiZheTouchSprites[i]->setPosition(cocos2d::CCPoint(mShiZheSprites[i]->getContentSize().width*0.5f,mShiZheSprites[i]->getContentSize().height*0.5f));
		mShiZheSprites[i]->addChild(mShiZheTouchSprites[i]);
		mShiZheTouchSprites[i]->setUserData((void*)(i+1));
	}
 
	QuJingData *pData = DataPool::GetSingleton()->GetQuJingData();
	if (!pData)return;
	X_INT id = pData->GetCurrentHuSongID();//1-5
	freshShiZhe(id);
  
}
void WoodShiZheUIView::sel_Sprite(CCObject* pObject)
{
	int id =  (int) static_cast<CCNode*>(pObject)->getUserData();
	const stDBC_FILE_QUJING  * pData = QuJingData::getTableDataById(id);
	if (!pData)return;
	showShiZheView(id,true);

	 
}
X_VOID  WoodShiZheUIView::showShiZheView(int id,bool b)
{
	if ( b&&mNodeshiZheXinxi->isVisible())
	{
		return;
	}
	
	mNodeshiZheXinxi->setVisible(b);
	mNodeshiZheXinxi->setPosition(mNodePos->getPosition());
	if (!b)return;
	if (id <= 0||id >5)
	{
		return;
	} 
	const char *qualityItems[5] = {
		"qj_color1.png",
		"qj_color2.png",
		"qj_color3.png",
		"qj_color4.png",
		"qj_color5.png",
	};
	const stDBC_FILE_QUJING  * pData = QuJingData::getTableDataById(id);
	if (!pData)return;
	CCTexture2D *tx = CCTextureCache::sharedTextureCache()->addImage(qualityItems[id-1]);
	mShiZheColor->setTexture(tx);
	string str = "qj_xjl.png";
	if (pData&&pData->visual!="-1")
	{
		str = pData->visual;
	}
	CCTexture2D *tx1 = CCTextureCache::sharedTextureCache()->addImage(str.c_str());
	mShiZheSprite->setTexture(tx1);
	 
 
	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(657),pData->name);
	mShiZheName->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(658),pData->level);
	mShiZheLevel->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(654),UtilTools::ConvertMillisecondToTimeString(pData->time*1000).c_str());
	mShiZheTime->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(655),X_INT(pData->wood*0.01f+0.5f),X_INT(pData->exp*0.01f+0.5f));
	mShiZheJiangLi->setString(temp);



}
X_VOID  WoodShiZheUIView::freshShiZhe(X_INT id)
{
	for (X_INT i = 0;i<5;i++)
	{
		if (i == id-1)
		{
				mShiZheTouchSprites[i]->setColor(ccWHITE);
		}else
		{
				mShiZheTouchSprites[i]->setColor(ICON_COLOR_GRAY);
		}
	}
	if (id <=  0|| id > 5)
	{
		mShiZheTouchSprites[0]->setColor(ccWHITE);
	}
	const stDBC_FILE_QUJING  * pData = QuJingData::getTableDataById(id);
	if (!pData)return;
	X_CHAR temp[256] = {0};
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(654),UtilTools::ConvertMillisecondToTimeString(pData->time*1000).c_str());
	mHuSongTime->setString(temp);

	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(655), X_INT(pData->wood*0.01f+0.5f));
	mWoodAward->setString(temp);
	memset(temp,0,sizeof(temp));
	sprintf(temp,UtilTools::GET_TEXT_FROM_LANG(702), X_INT(pData->exp*0.01f+0.5f));
	mExpward->setString(temp);
}
void WoodShiZheUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	int iTag = pSender->getTag();
	 
	SendLogicPacket::QuJingRefreshShiZhe(iTag == 1);
 
	pSender->closeDialogView();
}

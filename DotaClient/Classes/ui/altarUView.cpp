#include "./ui/altarUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE     (128)

AltarUIView::AltarUIView()
: mTiTle(NULL)
, mInfo(NULL)
, mAltarTitle(NULL)
, m_process(NULL)
, mProcessGlow(NULL)
, mDropText(NULL)
, mAltar(NULL)
{
	mAltarIndex = 0;
}

AltarUIView::~AltarUIView()
{
	CC_SAFE_RELEASE(mTiTle);
	CC_SAFE_RELEASE(mInfo);
	CC_SAFE_RELEASE(mAltarTitle);
	CC_SAFE_RELEASE(m_process);
	CC_SAFE_RELEASE(mProcessGlow);
	CC_SAFE_RELEASE(mDropText);
	CC_SAFE_RELEASE(mAltar);
}


void  AltarUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler AltarUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAltar1", AltarUIView::onAltar1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAltar2", AltarUIView::onAltar2);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAltar3", AltarUIView::onAltar3);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAltar4", AltarUIView::onAltar4);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onAltar5", AltarUIView::onAltar5);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onClose", AltarUIView::onClose);

	return NULL;    
}

SEL_CCControlHandler AltarUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	return NULL;
}

bool AltarUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTiTle", CCLabelTTF *, this->mTiTle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mInfo", CCLabelTTF *, this->mInfo);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltarTitle", CCSprite *, this->mAltarTitle);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_process", CCScale9Sprite *, this->m_process);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mProcessGlow", CCSprite *, this->mProcessGlow);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mDropText", CCLabelTTF *, this->mDropText);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mAltar", CCSprite *, this->mAltar);
	
	return false;
}

bool AltarUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
   
	return bRet;
}

// on "init" you need to initialize your instance
bool AltarUIView::init()
{
    bool bRet = true;

	return bRet;
}

void  AltarUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		//clear();

		return;
	}

	//const vector<HeroAltar*> & AltarArray  = DataPool::GetSingleton()->getHeroAltarData()->getHeroAltar();
	ObjectSelf *pself = DataPool::GetSingleton()->getObjectManager()->getSelf();
	PlayerData *pData = pself->playerData();

	pData->GetSacrificeID();
	pData->GetSacrificeDamage();
	
	X_INT itemId = -1;
	string dropItem;
	string name,color,icon;X_INT level;
	ObjectManager * pManger = DataPool::GetSingleton()->getObjectManager();
	for (X_INT i = 0 ;i< MAX_SACRIFICE_RECENT_AWARDITEM_COUNT;i++)
	{
		itemId = pData->GetSacrificeAward(i);
		if (itemId <= 0)continue;
		
		 if(pManger->getItemInfoById(itemId,name,color,icon,level))
		 {
			 dropItem += name;
			 dropItem +=" ";
		 }
	}
}

void  AltarUIView::itemCallBack( cocos2d::CCObject* pSender )
{
	int index = (int)(((CCNode *)pSender)->getUserData());

}


void  AltarUIView::onAltar1(cocos2d::CCObject * pSender)
{
	mAltarIndex = 0;
	
	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,mAltarIndex);
}

void  AltarUIView::onAltar2(cocos2d::CCObject * pSender)
{
	mAltarIndex = 1;

	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_PRAY,0);
}

void  AltarUIView::onAltar3(cocos2d::CCObject * pSender)
{
	mAltarIndex = 2;

	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,mAltarIndex);
}

void  AltarUIView::onAltar4(cocos2d::CCObject * pSender)
{
	mAltarIndex = 3;

	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,mAltarIndex);
}

void  AltarUIView::onAltar5(cocos2d::CCObject * pSender)
{
	mAltarIndex = 4;

	SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_ENTER,mAltarIndex);
}

void  AltarUIView::onClose(cocos2d::CCObject * pSender)
{
    EventSystem::GetSingleton()->PushEvent(GAME_EVENT_ALTAR_CLOSE);
}
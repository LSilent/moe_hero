#include "./ui/skillInspectUIView.h"
#include "./Game.h"
#include "./ui/element/CCMenuEx.h"
#include "./ui/element/CCScrollViewEx.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./datapool/HeroOperator.h"
#include "./game/SendPacket.h"
#include "./game/GameHelper.h"

#include "./object/ObjectHero.h"

#include "./ui/skillInspectUI.h"
#include "./ui/element/SkillAnimation.h"


using namespace cocos2d;
USING_NS_CC_EXT;


#define MAX_STRING_BUFF_SIZE     (128)

#define CONTENT_POS_X            (0.080f)
#define CONTENT_POS_Y            (0.238f)

#define CONTENT_VIEW_SIZE_X      (0.845f)
#define CONTENT_VIEW_SIZE_Y      (0.35f)

#define ITEM_SPACE_DELTA_X       (0.170f)
#define ITEM_SPACE_DELTA_Y       (0.110f)

#define ITEM_START_X             (0.08f)
#define ITEM_START_Y             (0.18f)

#define CONTENT_DESC_POS_X       (0.46f)
#define CONTENT_DESC_SIZE_X      (0.40f)

#define ITEM_COLUMN_NUM          5
#define ITEM_LINE_NUM            1

SkillInspectUIView::SkillInspectUIView()
: mSkillName(NULL)
, mSkillThisLevel(NULL)
, mSkillNextLevel(NULL)
, mSkillPos(NULL)
, mSkillLvl(NULL)
, mSkillRate(NULL)
, mSkillCD(NULL)
, mSkillMP(NULL)
, mSkillButtonUp(NULL)
, mSkilltip(NULL)
{
	mContentNode = NULL;

	for (int i = 0; i < 5; i++)
	{
		mSkillButton[i] = NULL;
	}

	guideLayer = NULL;
	effect = NULL;
}

SkillInspectUIView::~SkillInspectUIView()
{
	CC_SAFE_RELEASE(mSkillName);
	CC_SAFE_RELEASE(mSkillThisLevel);
	CC_SAFE_RELEASE(mSkillNextLevel);
	CC_SAFE_RELEASE(mSkillPos);
	CC_SAFE_RELEASE(mSkillLvl);

	CC_SAFE_RELEASE(mSkillRate);
	CC_SAFE_RELEASE(mSkillCD);
	CC_SAFE_RELEASE(mSkillMP);

	CC_SAFE_RELEASE(mSkillButtonUp);
	CC_SAFE_RELEASE(mSkilltip);

	for (int i = 0; i < 5; i++)
	{
		CC_SAFE_RELEASE(mSkillButton[i]);
	}

}

void SkillInspectUIView::skillUpgradeStatus(bool flag)
{
	if (flag)
	{
		effect = EffectAnimation::createWith("levelup",30,2.2f,0.03f,false,false);
		effect->setPosition(mSkillPos->getPosition());
		addChild(effect);
		effect->playAnimation();
		SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND7);

	}
}

void SkillInspectUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) 
{
}


SEL_MenuHandler SkillInspectUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this,"onSkillButtonSelected",SkillInspectUIView::onSkillButtonSelected);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonUpgrade", SkillInspectUIView::onButtonUpgrade);
	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonReturn", SkillInspectUIView::onButtonReturn);

	return NULL;    
}

SEL_CCControlHandler SkillInspectUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	
	



	return NULL;
}

void SkillInspectUIView::onSkillButtonSelected(cocos2d::CCObject * pSender)
{
	
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();
	if (!pHero ||!pSkill)
	{
		return;
	}
	 if (pHero->GetLevel() < 6 )
	 {
		if(pHero->GetSkill( pHero->GetSkillCount() -1) == pSkill)
		 return;
	 }
	if (judeSkillUpgrade())
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLUPGRADE_EQU_SHOW);
	}
	
	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_SOUND9);
	
}


void SkillInspectUIView::onButtonUpgrade(cocos2d::CCObject * pSender)
{
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();
	if (!pHero ||!pSkill)
	{
		return;
	}
	if (pHero->GetLevel() < 6 )
	{
		if(pHero->GetSkill( pHero->GetSkillCount() -1) == pSkill)
			return;
	}
	if (judeSkillUpgrade())
	{
		const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
		const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();

		vector<ItemCommon *> pSEqui = DataPool::GetSingleton()->GetSelectEqui();

		vector<Item*> itemUsed;
		vector<int> itemUsedCount;

		for (unsigned int i = 0; i < pSEqui.size(); i++)
		{
			if( itemUsed.empty() || itemUsed.back()->GetGuid() != pSEqui[i]->GetGuid() )
			{
				itemUsed.push_back( pSEqui[i] );
				itemUsedCount.push_back( 1 );
			}
			else
			{
				itemUsedCount.back() ++;
			}
		}

		SendLogicPacket::SkillUpgrade(pHero,pSkill->GetTableId(),itemUsed,itemUsedCount);

		

		pSEqui.clear();
		DataPool::GetSingleton()->SetSelectEqui(pSEqui);
	}

	guideLayer = NULL;

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
	 
}

void SkillInspectUIView::onButtonReturn(cocos2d::CCObject * pSender)
{

	vector<ItemCommon *> pTemp;
	pTemp.clear();
	DataPool::GetSingleton()->SetSelectEqui(pTemp);

	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_CLOSE);

	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);

}

bool SkillInspectUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) 
{
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillName", CCLabelBMFont *, this->mSkillName);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillThisLevel", CCLabelTTF *, this->mSkillThisLevel);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillNextLevel", CCLabelTTF *, this->mSkillNextLevel);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillPos", CCSprite *, this->mSkillPos);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButton1", CCMenuItemImage *, this->mSkillButton[0]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButton2", CCMenuItemImage *, this->mSkillButton[1]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButton3", CCMenuItemImage *, this->mSkillButton[2]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButton4", CCMenuItemImage *, this->mSkillButton[3]);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButton5", CCMenuItemImage *, this->mSkillButton[4]);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillRate", CCLabelBMFont *, this->mSkillRate);
	
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillCD", CCLabelTTF *, this->mSkillCD);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillMP", CCLabelTTF *, this->mSkillMP);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillLvl", CCLabelBMFont *, this->mSkillLvl);

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkillButtonUp", CCMenuItemImage *, this->mSkillButtonUp);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mSkilltip", CCSprite *, this->mSkilltip);

	return false;
}

bool SkillInspectUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  
    return bRet;
}

// on "init" you need to initialize your instance
bool SkillInspectUIView::init()
{
    bool bRet = true;

    return bRet;
}

bool SkillInspectUIView::judeSkillUpgrade()
{
	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();
	if (!pHero ||pHero->GetContainerType() != EM_HERO_CONTAINER_BAG)
	{
		return false;
	}
	

	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();

	X_INT level = pSkill->GetLevel();
	if (level < MAX_NORMAL_SKILL_LEVEL)
	{

		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
		const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId() + 1);

		int nextLvl = m_pTableData->_heroLevel;

		if (nextLvl > pHero->GetLevel())
		{
			static char buffLvl[MAX_STRING_BUFF_SIZE] = {0};
			memset(buffLvl,0,sizeof(buffLvl));
			sprintf(buffLvl,UtilTools::GET_TEXT_FROM_LANG(572),nextLvl);
			ModalDialogView *dialog = ModalDialogView::createDialog(buffLvl,this,DIALOG_MODEL_SINGLE);
			addChild(dialog);

			return false;
		}
		else
		{
			return true;
		}

	}
	else
	{
		ModalDialogView *dialog = ModalDialogView::createDialog(UtilTools::GET_TEXT_FROM_LANG(645),this,DIALOG_MODEL_SINGLE);
		addChild(dialog);

		return false;

	}

}


void SkillInspectUIView::onDataUpdate( bool isDataValid )
{
	if( !isDataValid )
	{
		return;
	}

	if( mContentNode )
	{
		mContentNode->removeFromParentAndCleanup( true );
		mContentNode = NULL;
	}

	mContentNode = CCNode::create();
	addChild( mContentNode );

	if (effect)
	{
		effect = NULL;
	}


	const ObjectSkill *pSkill = DataPool::GetSingleton()->GetSelectSkill();
	if (!pSkill)
	{
		return;
	}
	
	CCSprite *skillSprite = CCSprite::create( pSkill->GetIcon());
	skillSprite->setPosition( mSkillPos->getPosition() );
	skillSprite->setScale(1.25f);
	mContentNode->addChild( skillSprite );

	mContentNode = CCNode::create();
	addChild( mContentNode );

	mSkillName->setString(pSkill->GetName());

	//skill desc
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize viewSize = CCSizeMake(winSize.width * CONTENT_DESC_SIZE_X, mSkillThisLevel->getContentSize().height);
	mSkillThisLevel->setPositionX(winSize.width * CONTENT_DESC_POS_X);
	mSkillThisLevel->setDimensions(viewSize);
	mSkillThisLevel->setString(pSkill->GetDesc());
	
	//next skill desc
	viewSize = CCSizeMake(winSize.width * CONTENT_DESC_SIZE_X, mSkillNextLevel->getContentSize().height);
	mSkillNextLevel->setPositionX(winSize.width * CONTENT_DESC_POS_X);
	mSkillNextLevel->setDimensions(viewSize);
	if (pSkill->GetLevel() < MAX_SKILL_LEVEL)
	{
		mSkillNextLevel->setString(Skill::GetDesc(pSkill->GetTableId()+1).c_str());
	}
	else
	{
		mSkillNextLevel->setString(UtilTools::GET_TEXT_FROM_LANG(564));
	}
	
	
  
	mSkillLvl->setString( UtilTools::IntToString(pSkill->GetLevel()).c_str());


	char buffCD[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffCD,UtilTools::GET_TEXT_FROM_LANG(555),pSkill->GetTableData()->_cd);
	mSkillCD->setString(buffCD);

	char buffMP[MAX_STRING_BUFF_SIZE] = {0};
	sprintf(buffMP,UtilTools::GET_TEXT_FROM_LANG(556),pSkill->GetTableData()->_costMp);
	mSkillMP->setString(buffMP);


	const vector<ItemCommon *> pSkillEqui = DataPool::GetSingleton()->GetSelectEqui();
	int num = pSkillEqui.size();
	for (int i = 0; i < num; i++)
	{
		ItemCommon *pItm = pSkillEqui[i];
		CCSprite *pIcon = CCSprite::create(pItm->GetIcon());
		pIcon->setPosition(mSkillButton[i]->getPosition());
		pIcon->setScale(0.8f);
		mContentNode->addChild(pIcon);
	}
	
	if (pSkillEqui.empty())
	{
		mSkillRate->setVisible(false);

		CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage("skill_up_tip.png");
		mSkilltip->setTexture(texture2D1);
	}
	else
	{
		/*string strText = UtilTools::GET_TEXT_FROM_LANG(554);

		X_INT rate = GameHelper::getSkillLevelRate(pSkill,pSkillEqui);
		strText += UtilTools::IntToString( (rate >= 100)?100: rate);
		strText +="%";
		mSkillRate->setString(strText.c_str());*/

		X_INT rate = GameHelper::getSkillLevelRate(pSkill,pSkillEqui);
		string strText  = UtilTools::IntToString( (rate >= 100)?100: rate);
		mSkillRate->setString(strText.c_str());
 
		CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage("skill_up_rate.png");
		mSkilltip->setTexture(texture2D1);
	}

	const ObjectHero *pHero = DataPool::GetSingleton()->GetSelectHero();

	int nextLvl = pSkill->GetTableData()->_heroLevel;
	if (pSkill->GetLevel() < MAX_SKILL_LEVEL)
	{
		const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_SKILL);
		const stDBC_FILE_SKILL	* m_pTableData = (const stDBC_FILE_SKILL*)pDataFile->GetFieldsByIndexKey(pSkill->GetTableId()+1);
		nextLvl = m_pTableData->_heroLevel;
	}
	
	X_INT tipId = ((SkillInspectUI *)this->getUserData())->getTipId();

	if (guideLayer)
	{
		guideLayer->removeFromParentAndCleanup(true);
	}

	guideLayer = X_NULL;
	if (tipId != -1)
	{
 
		if (!guideLayer)
		{
			//int gid = DataPool::GetSingleton()->getGuideData()->GetCurrentTipId();
			//int tipID = ((SkillInspectUI *)this->getUserData())->getTipId();
			switch (tipId)
			{
			case 21:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(SkillInspectUIView::onSkillButtonSelected),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 24:
				guideLayer = guidelinesLayer::createLayer(tipId,this,menu_selector(SkillInspectUIView::onButtonUpgrade),NULL);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			case 25:
				guideLayer = guidelinesLayer::createLayer(tipId,this);
				guideLayer->setPosition(getPosition());
				addChild(guideLayer);
				break;
			default:
				break;
			}
		}
	}

	if (guideLayer)
	{
		guideLayer->setZOrder(LAYER_MAX_ZORDER);
	}

	 
	if (!pHero ||pHero->GetContainerType() != EM_HERO_CONTAINER_BAG)
	{
		mSkillButtonUp->setEnabled(false);
	}else
	{
		mSkillButtonUp->setEnabled(true);
	}
}

void SkillInspectUIView::itemInfoCallBack( cocos2d::CCObject* pSender )
{
	// ignore if moved
	if( mContent->mIsMoved )
		return;
	
	int index = (int)(((CCNode *)(pSender))->getUserData());

	if( itemlistStatus[index] )
	{
		itemlistStatus[index] = 0;
		((CCMenuItemImage*)(pSender))->setColor( ccWHITE );
	}
	else
	{
		itemlistStatus[index] = 1;
		((CCMenuItemImage*)(pSender))->setColor( ccGREEN );
	}
}

void SkillInspectUIView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{

}
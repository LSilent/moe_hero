#include "./ui/UserUpgradeUIView.h"
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

using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_STRING_BUFF_SIZE    (128)

#define LOGO_POS_X              (0.5f)
#define LOGO_POS_Y              (0.745f)

#define STAR_POS_START_X        (0.35f)
#define STAR_POS_DELTA_X        (0.08f)
#define STAR_POS_Y              (0.57f)

#define MAX_USER_LEVLE			75

UserUpgradeUIView::UserUpgradeUIView()
: mUserLvl(NULL)
, mUserMaxLvl(NULL)
{
	mContent = NULL;
}

UserUpgradeUIView::~UserUpgradeUIView()
{
	CC_SAFE_RELEASE(mUserLvl);
	CC_SAFE_RELEASE(mUserMaxLvl);
}

void UserUpgradeUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   
	onDataUpdate( false );
}


SEL_MenuHandler UserUpgradeUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) 
{

	CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onButtonRecruitHero", UserUpgradeUIView::onButtonRecruitHero);

    return NULL;    
}

SEL_CCControlHandler UserUpgradeUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) 
{	


	return NULL;
}

void UserUpgradeUIView::onButtonRecruitHero(cocos2d::CCObject * pSender)
{
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_RECRUIT_SHOW);
	SoundSystem::GetSingleton()->playClickEffect(GAME_CLICK_COMMON);
}



bool UserUpgradeUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
   

	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserLvl", CCLabelBMFont *, mUserLvl);
	CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mUserMaxLvl", CCLabelBMFont *, mUserMaxLvl);

    return false;
}

bool UserUpgradeUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    return false;
}

// on "init" you need to initialize your instance
bool UserUpgradeUIView::init()
{
    bool bRet = true;

    //   

    return bRet;
}

void UserUpgradeUIView::onDataUpdate( bool isDataValid )
{	
	if( !isDataValid )
	{
		//clear();

		return;
	}

	if( mContent )
		mContent->removeFromParentAndCleanup( true );

	mContent = CCNode::create();
	addChild( mContent );


	ObjectSelf* pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf(); 
	PlayerData* pData = pSelf->playerData();

	int curLvl = pData->GetLevel();
	string strCLvl = UtilTools::IntToString(curLvl);
	strCLvl += UtilTools::GET_TEXT_FROM_LANG(514);
	mUserLvl->setString(strCLvl.c_str());

	int maxLvl = curLvl + 5;
	if (maxLvl >= MAX_USER_LEVLE)
	{
		maxLvl = MAX_USER_LEVLE;
	}
	
	string strMLvl = UtilTools::IntToString(maxLvl);
	strMLvl += UtilTools::GET_TEXT_FROM_LANG(514);
	mUserMaxLvl->setString(strMLvl.c_str());
	

}
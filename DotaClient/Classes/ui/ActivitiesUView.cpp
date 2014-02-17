#include "./ui/ActivitiesUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

using namespace cocos2d;
USING_NS_CC_EXT;

ActivitiesUIView::ActivitiesUIView()
{
}

ActivitiesUIView::~ActivitiesUIView()
{
}


void ActivitiesUIView::onNodeLoaded(cocos2d::CCNode * pNode,  cocos2d::extension::CCNodeLoader * pNodeLoader) {
   /* CCRotateBy * ccRotateBy = CCRotateBy::create(20.0f, 360);
    CCRepeatForever * ccRepeatForever = CCRepeatForever::create(ccRotateBy);
    this->mBurstSprite->runAction(ccRepeatForever);*/

	
}


SEL_MenuHandler ActivitiesUIView::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char * pSelectorName) {
    return NULL;    
}

SEL_CCControlHandler ActivitiesUIView::onResolveCCBCCControlSelector(CCObject * pTarget, const char * pSelectorName) {
   
	return NULL;
}

bool ActivitiesUIView::onAssignCCBMemberVariable(CCObject * pTarget, const char * pMemberVariableName, CCNode * pNode) {
    

    return false;
}

bool ActivitiesUIView::onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue)
{
    bool bRet = false;
  

    return bRet;
}

// on "init" you need to initialize your instance
bool ActivitiesUIView::init()
{
    bool bRet = true;

   

    return bRet;
}


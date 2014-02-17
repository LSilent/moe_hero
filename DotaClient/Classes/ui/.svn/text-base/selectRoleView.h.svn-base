#ifndef __SELECTROLEVIEW_H__
#define __SELECTROLEVIEW_H__

#include "./ui/baseview.h"

#include "./CCControlExtension/CCScale9Sprite.h"
#include "./CCEditBox/CCEditBox.h"
#include "./ui/element/CCMenuEx.h"
using namespace cocos2d;
using namespace cocos2d::extension;

class selectRoleView : public BaseView
{
public:
     
    virtual bool init();  
	void menuCloseCallback(CCObject* pSender);
	void menuBackCallback(CCObject* pSender);
    CREATE_FUNC(selectRoleView);
    
    CCEditBox* m_pEditName;
    CCMenuItemImage *pCloseItem ;
};

#endif
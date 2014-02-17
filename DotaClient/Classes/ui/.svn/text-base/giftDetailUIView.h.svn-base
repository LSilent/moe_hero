#ifndef __GIFTDETAIL_UI_VIEW_H__
#define __GIFTDETAIL_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
 
class giftDetailUIView : public BaseView

{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(giftDetailUIView, create);

public:
	giftDetailUIView();
	virtual ~giftDetailUIView();
	virtual bool init();  
public:
	void updataFailed();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );
	void onButtonOK(cocos2d::CCObject* pSender);
private:

};


#endif
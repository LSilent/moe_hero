#ifndef __PLACARD_UI_VIEW_H__
#define __PLACARD_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
 
namespace cocos2d {
	namespace extension {

		class CCScrollViewEx; 
	}
}
class placardUIView : public BaseView

{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(placardUIView, create);

public:
	placardUIView();
	virtual ~placardUIView();
	virtual bool init();  
public:


public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );
	void closeInfoCallBack(cocos2d::CCObject *pSender);
	void closeCallFunc();
private:
	CCLayer *baseLayer;

	cocos2d::extension::CCScrollViewEx* mContent;

};


#endif
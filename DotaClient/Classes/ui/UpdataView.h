#ifndef __UPDATAVIEW_SCENE_H__
#define __UPDATAVIEW_SCENE_H__

#include "./ui/baseview.h"
#include "./ui/element/ModalDialogView.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
class ProgressView;
 
 
class UpdataView : public BaseView , public ModalDialogDelegate
{
public:
     
    virtual bool init();  
    void menuCloseCallback(CCObject* pSender);
    CREATE_FUNC(UpdataView);


	void updateRES(float dt );
	ProgressView *mExpProgress;
	CCLabelTTF* pLabel;
	bool b_updata;
	void  dialogDidClick(int itemIndex, ModalDialogView *pSender);
	X_INT retryNum;
	X_INT retryNumcompress;

	 ModalDialogView *m_dialog;

	 void handleError(X_INT code);
};

#endif
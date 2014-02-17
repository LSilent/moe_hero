#ifndef __CHATMESSAGEUIVIEW_H__
#define __CHATMESSAGEUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "./ui/element/ModalDialogView.h"

class MainStatusView;
class Record;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class ChatMessageUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
    , cocos2d::extension::CCEditBoxDelegate
	, ModalDialogDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(ChatMessageUIView, create);

public:
	ChatMessageUIView();
	virtual ~ChatMessageUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);
public:
    

    virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
    virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
    virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);
 
public:
    void sendMsg();
    void updateMsgContent();
    void updateMsgContentWithRecord(Record rd);
    
public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemCallBack( cocos2d::CCObject* pSender );

	void onButtonSendMsg(cocos2d::CCObject * pSender);
	void onButtonClose(cocos2d::CCObject * pSender);
private:
	
 

	cocos2d::extension::CCScrollViewEx* mContent;


	cocos2d::CCSprite *meditBack;
    
    cocos2d::extension::CCEditBox *pEditBox;
 
    vector<Record> mRecordItems;

	X_ULLONG curTime;
};

class ChatMessageUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(ChatMessageUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(ChatMessageUIView);
};

#endif
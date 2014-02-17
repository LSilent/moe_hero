#ifndef __MESSAGE_UI_VIEW_H__
#define __MESSAGE_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "./ui/element/CCMenuEx.h"


class MainStatusView;
class Message;

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}

class MessageUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
{
public:
	enum EM_MESSAGE_TYPE
	{
		EM_MESSAGE_TYPE_INVALID = -1,
		EM_MESSAGE_TYPE_SYSTEM,// 系统
		EM_MESSAGE_TYPE_BATTLE,//战报
		EM_MESSAGE_TYPE_REVENGE,//复仇
	};
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MessageUIView, create);

public:
	MessageUIView();
	virtual ~MessageUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );
private:
	cocos2d::CCMenuEx* UpdateNormalMailData( CCLayer * layer );
	cocos2d::CCMenuEx* UpdateBattleMailData( CCLayer * layer ); 
	cocos2d::CCMenuEx* UpdateRevengeMailData(CCLayer* layer);

	void UpdateSingleNormalMail( Message * pMessage, X_UINT i, cocos2d::CCSize &contentSize, CCLayer * layer, cocos2d::CCMenuEx * menu) ;
	void UpdateSingleRevengeMail( Message * pMessage, X_UINT i, cocos2d::CCSize &contentSize, CCLayer * layer, cocos2d::CCMenuEx * menu); 
	void UpdateSingleBattleMail( Message * pMessage, X_UINT i, cocos2d::CCSize &contentSize, CCLayer * layer, cocos2d::CCMenuEx * menu);
	void UpdateSingleMail( Message * pMessage, X_UINT i, cocos2d::CCSize &contentSize, CCLayer * layer, cocos2d::CCMenuEx * menu,cocos2d:: SEL_MenuHandler openfun,cocos2d:: SEL_MenuHandler delfun ) ;

	
	void itemNormalMessageCallBack( cocos2d::CCObject* pSender );
	void itemBattleMessageCallBack( cocos2d::CCObject* pSender );
	void itemRevengeMessageCallBack( cocos2d::CCObject* pSender );
	void onButtonMsgDelete(cocos2d::CCObject * pSender);
	void __openMessage(int tag);
	X_VOID __onSelectMessage(EM_MESSAGE_TYPE type);

public:
	void onButtonAll(cocos2d::CCObject * pSender);
	void onButtonFight(cocos2d::CCObject * pSender);
	void onButtonFriends(cocos2d::CCObject * pSender);
	void onButtonMsgClose(cocos2d::CCObject * pSender);
	void onButtonMsgRevenge(cocos2d::CCObject * pSender);
	void updateMsgContent(Message *pMsg);

	void onButtonClose(cocos2d::CCObject * pSender);
	void onButtonOpenAll(cocos2d::CCObject * pSender);
	void onButtonDelAll(cocos2d::CCObject * pSender);

	void openMailCallBack();
	
private:
	
	 
 
	 vector<Message*>	 messages;
	cocos2d::extension::CCScrollViewEx* mContent;

	cocos2d::CCMenuItemImage *mTabItems[3];

	cocos2d::CCNode *mNodeMsgCntNode;
	cocos2d::CCLabelTTF *mMsgSender;
	cocos2d::CCLabelTTF *mMsgTitle;
	cocos2d::CCLabelTTF *mMsgTime;
	cocos2d::CCLabelTTF *mMsgContent;
	cocos2d::CCLayerColor *mGrayLayer;
	 

	vector<Message*>				m_vecSystemMessage;	
	vector<Message*>				m_vecBattleMessage;	
	vector<Message*>				m_vecRevengeMessage;	//复仇邮件
	Message*						m_pOpenedMessage;      //正在打开的邮件

	EM_MESSAGE_TYPE				m_MessageType;


	bool isCloseDetail;
	void disableMenuItem(EM_MESSAGE_TYPE type,bool disable = true);
	void EnableAllMenuItem();
	map<X_INT,cocos2d::CCSprite*>	 m_hover;
	 cocos2d::CCSprite* mhoverVisble;
};







class MessageUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MessageUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MessageUIView);
};

#endif
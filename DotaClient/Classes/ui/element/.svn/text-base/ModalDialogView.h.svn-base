#ifndef __MODALDIALOGVIEW_H__
#define __MODALDIALOGVIEW_H__


#include "cocos2d.h"
#include "cocos-ext.h"
#include "./ui/baseview.h"
#include "./ui/element//CCMenuEx.h"
#include <string>

USING_NS_CC;

class ModalDialogView;

typedef enum DialogModel
{
	DIALOG_MODEL_SINGLE,
	DIALOG_MODEL_DOUBLE,
};

class ModalDialogDelegate
{
public:
	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender) = 0; // 
};

class ModalDialogView: public BaseView
{
public:
	ModalDialogView();
	virtual ~ModalDialogView();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual	void initDialog();

	inline void setDailogUserData(void* pUserData)
    {
        mDialogUserData = pUserData;
    };

    inline void* getDailogUserData()
    {
        return mDialogUserData;
    };


	void comfireMenuItemCallback(CCObject *pSender);
	void cancelMenuItemCallback(CCObject *pSender);

	void closeDialogView();
	static ModalDialogView *createDialog(const std::string &des, ModalDialogDelegate *pDel ,DialogModel eModel =  DIALOG_MODEL_DOUBLE);
	static ModalDialogView *createDialog(const std::string &des, ModalDialogDelegate *pDel ,string strOK, string strCancel, DialogModel eModel =  DIALOG_MODEL_DOUBLE);

protected:
	CCMenu *m_pMenu;
	bool m_bTouchedMenu;
	DialogModel m_eModel;
	std::string m_content;
	ModalDialogDelegate *m_pDialogDel;
	void *mDialogUserData;


};

//
class Item;

class DialogBuyView: public ModalDialogView
{
public:

	DialogBuyView();
	~DialogBuyView();

	void addCallBack( cocos2d::CCObject* pSender );
	void subCallBack( cocos2d::CCObject* pSender );

	static DialogBuyView *createDialog(Item *pSender, ModalDialogDelegate *pDel,EM_SHOP_MONEY_TYPE  type = EM_SHOP_MONEY_GOLD);
	virtual void initDialog();

	int getMatNum() const;
	const Item *getItem() const;
private:
	int m_iMatNum;
	cocos2d::CCLabelTTF *mGoldNum;
	cocos2d::CCLabelTTF *mGoldPrice;
	Item *mItem;
	//CCMenuHoldEx *m_pHoldMenu;
	static EM_SHOP_MONEY_TYPE m_Buytype;
};

class GiftExchangeView: public ModalDialogView 	, cocos2d::extension::CCEditBoxDelegate
{
public:

	GiftExchangeView();
	~GiftExchangeView(); 

	static GiftExchangeView *createDialog(ModalDialogDelegate *pDel);
	virtual void initDialog();
	const char*  getText() const;


	virtual void editBoxEditingDidBegin(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::extension::CCEditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::extension::CCEditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::extension::CCEditBox* editBox);


	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
	 cocos2d::extension::CCEditBox *pEditBox;
 

};

#endif
#ifndef __EQUIPMENT_ALL_UI_VIEW_H__
#define __EQUIPMENT_ALL_UI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"
#include "./ui/element/CCScrollViewEx.h"

namespace cocos2d {
namespace extension {

	class CCScrollViewEx; 
}
}
class Item;
 
class EquipmentAllUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(EquipmentAllUIView, create);

public:
	EquipmentAllUIView();
	virtual ~EquipmentAllUIView();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);

	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );

public:

	virtual bool init();  
	static cocos2d::CCScene* scene();

public:
	// view content update
	virtual void onDataUpdate( bool isDataValid = true );

	void itemInfoCallBack( cocos2d::CCObject* pSender );
	
public:
	void onButtonEquip0(cocos2d::CCObject * pSender);

	void onButtonEquip1(cocos2d::CCObject * pSender);

	void onButtonEquip2(cocos2d::CCObject * pSender);

	void onButtonEquipSell(cocos2d::CCObject * pSender);
	
private:
	
	cocos2d::extension::CCScrollViewPage* mContent;
	cocos2d::extension::CCPageControll *mPageCtrl;
	vector<const Item*> itemlist;

	X_VOID __onChangeSubClass(X_INT nPage);
};

class EquipmentAllUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(EquipmentAllUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(EquipmentAllUIView);
};

#endif
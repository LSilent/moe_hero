#ifndef __HEROBASEACTIVITYUIVIEW_H__
#define __HEROBASEACTIVITYUIVIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"

#include "SimpleAudioEngine.h"

#include "./base/Global.h"

#include "./ui/element/ModalDialogView.h"
#include "./ui/element/CCScrollViewEx.h"

#include "./database/DataBaseSystem.h"
#include "./ui/element/guidelinesLayer.h"
#define MAX_HERO_EQUIPMENT_NUM     6
#define MAX_HERO_SKILL_NUM         2

class ObjectHero;
class HeroAltar;
namespace cocos2d {
	class LogicTouchItem;
	class HeroHeadIcon;
}
namespace cocos2d {
	namespace extension {

		class CCScrollViewEx; 
	}
}

class heroBaseActivityUIView;

class HeroBaseActivityUIViewHandle 
	: public cocos2d::CCNode
	, public cocos2d::extension::CCBMemberVariableAssigner
{
public:
	HeroBaseActivityUIViewHandle(heroBaseActivityUIView* pUIView):m_BaseUIView(pUIView){}
	virtual ~HeroBaseActivityUIViewHandle(){}
	virtual void ClearData() = 0;
	virtual void SetLayerDisable() = 0;
protected:
	heroBaseActivityUIView*			m_BaseUIView;
};

//伐木场 Wood PVP 界面处理类
class HeroWoodPVPUIViewHandle
	: public HeroBaseActivityUIViewHandle
	, public ModalDialogDelegate
{
	//三个Layer共有处理

public:
	HeroWoodPVPUIViewHandle(heroBaseActivityUIView* UIView);
	~HeroWoodPVPUIViewHandle();
 
public:
	virtual void ClearData();
	virtual void SetLayerDisable();
	void UpdateWoodPVPTextData();
	void HeroPVPDataUpdate();
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);


	//	///////////////////////////////////////////////////////
	//	//伐木场PVP layer
	//

public:
	void onButtonGotoRob();
	void onButtonWoodUpgrade();
	void onButtonChangeHero();

	void UpdateSelfWoodData();

	X_VOID CreateHeroPVPNullItem();

	void heroItemTouchBeginHook(CCObject* pSender);
	void heroItemTouchMoveHook(CCObject* pSender);
	void heroItemTouchEndHook(CCObject* pSender);

	void heroNullTouchBeginHook(CCObject* pSender);
	void heroNullTouchMoveHook(CCObject* pSender);
	void heroNullTouchEndHook(CCObject* pSender);

	//时间更新
	void updateWoodLevelUpTime( float time );

private:
	cocos2d::CCLayer*				m_HeroPVPLayer;
	cocos2d::CCSprite*				m_HeroPVPDock[MAX_MATRIX_CELL_COUNT];
	cocos2d::LogicTouchItem*		m_HeroPVPItems[MAX_MATRIX_CELL_COUNT];
	cocos2d::LogicTouchItem*		m_HeroPVPNullItems[MAX_MATRIX_CELL_COUNT];
	ObjectHero*						m_HeroObjArray[MAX_MATRIX_CELL_COUNT];
	int								m_HerosDockIndex[MAX_MATRIX_CELL_COUNT];
	cocos2d::CCSprite*			m_HeroPVPLevelLabel;
	cocos2d::CCSprite*			m_HeroPVPHPLabel;
	cocos2d::CCSprite*			m_HeroPVPDefLabel;
	cocos2d::CCSprite*			m_HeroPVPCreLabel;
	cocos2d::CCSprite*			m_HeroPVPTotalLabel;
	X_BOOL							m_IsDragMove;
	cocos2d::CCSprite*			m_HeroLevelUpFreshTimeLabel;
	cocos2d::CCSprite*				m_HeroLevelUpButtonSprite;

	cocos2d::CCSprite*			mPVPCd;
	cocos2d::CCSprite*			mPVPProtectedCd;
	

	///////////////////////////////////////////////////////
	//伐木场Rob layer  

public:
	void onButtonRematch();
	void onButtonRob();
	void UpdateOtherDefWoodData();
private:

	cocos2d::CCLayer*				m_HeroRobLayer;
	cocos2d::CCSprite*				m_HeroRobDock[MAX_MATRIX_CELL_COUNT];
	cocos2d::LogicTouchItem*		m_HeroRobItems[MAX_MATRIX_CELL_COUNT];
	cocos2d::CCLabelTTF*			m_HeroRobLevelLabel;
	cocos2d::CCSprite*			m_HeroRobHPLabel;
	cocos2d::CCSprite*			m_HeroRobDefLabel;
	cocos2d::CCSprite*			m_HeroRobWoodLabel;
	cocos2d::CCSprite*			m_HeroRemachButtonLabel;


 	cocos2d::CCSprite*			m_RobDef;
 
	cocos2d::CCSprite*			m_RobNum;
 

	///////////////////////////////////////////////////////
	//伐木场  Revenge layer
public:
	void onButtonRevenge();
	void UpdateRevengeWoodData();
private:
	cocos2d::CCLayer*				m_HeroRevengeLayer;
	cocos2d::CCSprite*				m_HeroRevengeDock[MAX_MATRIX_CELL_COUNT];
	cocos2d::LogicTouchItem*		m_HeroRevengeItems[MAX_MATRIX_CELL_COUNT];
	cocos2d::CCLabelTTF*			m_HeroRevengeLevelLabel;
	cocos2d::CCSprite*			m_HeroRevengeHPLabel;
	cocos2d::CCSprite*			m_HeroRevengeDefLabel;
	cocos2d::CCSprite*			m_HeroRevengeWoodLabel;
	cocos2d::CCSprite*			m_RevengeDef;
	bool visable;

	///////////////////////////////////////////////////////
	//对话框
	enum EM_DIALOGTIP_TYPE_TAG
	{
		EM_DIALOG_INVALID_TAG = -1,
		EM_DIALOG_WOODLEVELUP_TAG = 1000,
		EM_DIALOG_REQUIREMONEY_TAG,
		EM_DIALOG_WOODGotoPVP_TAG ,
		EM_DIALOG_WOODGotoFuchou_TAG,
		EM_DIALOG_REMATCH_TAG,
		
	};
public:
	virtual void dialogDidClick(int itemIndex, ModalDialogView *pSender);
	void   heroAdditionalValue(const string& str, cocos2d::CCPoint pos,X_INT attr,float scale,CCSprite *label);


	cocos2d::CCLabelBMFont* _mHeroAttcAdd[16];
};

//魔法学校  Master School 界面处理类
class HeroMasterSchoolUIViewHandle
	: public HeroBaseActivityUIViewHandle
{

public:
	HeroMasterSchoolUIViewHandle(heroBaseActivityUIView* pUIView);
	~HeroMasterSchoolUIViewHandle();

	virtual void ClearData(){}
	virtual void SetLayerDisable();
	virtual void ShowSelectLayer();
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	void		 MasterSchoolUpdate();
	void onButtonSkillLeveUp();
	void skillInfoCallBack(cocos2d::CCObject *pSender);
	void  itemInfoCallBack(cocos2d::CCObject *pSender);
private:
	cocos2d::CCLayer*				m_MasterSchoolLayer;
	cocos2d::CCLabelTTF*	mSkilldesc;
	cocos2d::CCLabelTTF*	mSkillNextdesc;
	cocos2d::CCLabelTTF*	mSkillWood;
	 cocos2d::CCSprite *mSkillButton[MAX_MATERIAL_NUM];
	cocos2d::CCSprite*	mSkillPos;
	cocos2d::CCSprite*	mSkillPosNext; 
	CCSprite *pIcon[MAX_MATERIAL_NUM];
	CCSprite *mpLevel[MAX_MATERIAL_NUM];
	bool mbGetAllMatrial;
};

class HeroIronsmithUIViewHandle
	: public HeroBaseActivityUIViewHandle
{

public:
	HeroIronsmithUIViewHandle(heroBaseActivityUIView* pUIView);
	~HeroIronsmithUIViewHandle();

	virtual void ClearData(){}
	virtual void SetLayerDisable();
	virtual void ShowSelectLayer();
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	void		 IronsmithUpdate();
	void onButtonEquipLeveUp();
	void skillInfoCallBack(cocos2d::CCObject *pSender);
	void  itemInfoCallBack(cocos2d::CCObject *pSender);
private:
	cocos2d::CCLayer*				m_IronsmithLayer;
 
	cocos2d::CCLabelTTF*	mEquipWood;
	cocos2d::CCSprite *mEquipButton[MAX_MATERIAL_NUM];
	cocos2d::CCSprite*	mEquipPos;
	cocos2d::CCSprite*	mEquipPosNext; 
	CCSprite *pIcon[MAX_MATERIAL_NUM];
	cocos2d::CCLabelBMFont *pIconNum[MAX_MATERIAL_NUM];
	CCSprite * mpLevel[MAX_MATERIAL_NUM];
	CCSprite * pLevelItem;
	CCSprite * pLevelNext;//2-5级别角标
	cocos2d::CCLabelTTF *mEquipAttr[9];
	cocos2d::CCLabelTTF *mEquipAttrNext[9];
	bool mbGetAllMatrial;
};

class WoodShopUIViewHandle
	: public HeroBaseActivityUIViewHandle
	, public ModalDialogDelegate
{

public:
	WoodShopUIViewHandle(heroBaseActivityUIView* pUIView);
	~WoodShopUIViewHandle();

	virtual void ClearData(){}
	virtual void SetLayerDisable();
 
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	void ShopUpdate();
	void itemInfoCallBack( cocos2d::CCObject* pSender );
	void buyCallBack( cocos2d::CCObject* pSender );

	void dialogDidClick(int itemIndex, ModalDialogView *pSender);
 
private:
	cocos2d::CCLayer*				m_ShopLayer;
	cocos2d::extension::CCScrollViewEx* mContent;
	
};



class heroBaseActivityUIView
	: public BaseView
	, public cocos2d::extension::CCBSelectorResolver
	, public cocos2d::extension::CCBMemberVariableAssigner
	, public cocos2d::extension::CCNodeLoaderListener
	, public cocos2d::extension::CCScrollViewPageDelegate
	//, public ModalDialogDelegate
{

	friend class HeroWoodPVPUIViewHandle;
	friend class HeroMasterSchoolUIViewHandle;
	friend class HeroIronsmithUIViewHandle;
	friend class WoodShopUIViewHandle;
public:
	enum EM_HEROBASEACTIVITY_TYPE
	{
		EM_HEROBASE_INVALID = -1,
		EM_HEROBASE_WOOD,
		EM_HEROBASE_MASTERSCHOOL,
		EM_HEROBASE_IRONSMITH,
		EM_WOOD_SHOP,
		EM_HEROBASE_TYPE_NUM
	};

public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(heroBaseActivityUIView, create);

public:
	heroBaseActivityUIView();
	virtual ~heroBaseActivityUIView();
	virtual void onEnter();
	virtual void onExit();

public:
	virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(cocos2d::CCObject * pTarget, const char * pSelectorName);
	virtual bool onAssignCCBMemberVariable(cocos2d::CCObject * pTarget, const char * pMemberVariableName, cocos2d::CCNode * pNode);
	virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
	virtual void onNodeLoaded(cocos2d::CCNode * pNode, cocos2d::extension::CCNodeLoader * pNodeLoader);


	///////////////////////////////////////////////////////
	//全局界面
public:
	virtual bool init();  
	static cocos2d::CCScene* scene();
	virtual void onDataUpdate( bool isDataValid = true );

private:
	void HeroBaseActivityDataUpdate(X_INT type);
	void SetAllLayerDisable();

	virtual void ShowSelectLayer(){}

private:
	
	cocos2d::CCNode*			m_ContentNode;
	cocos2d::CCLayer*			mLayerSelect;
	cocos2d::extension::CCScrollViewEx*				mContent;

	guidelinesLayer *guideLayer;

	///////////////////////////////////////////////////////
	//上端向导栏
public:
	virtual void scrollViewDidScroll( cocos2d::extension::CCScrollView* view );
	virtual void scrollViewDidZoom( cocos2d::extension::CCScrollView* view );
	virtual bool scrollViewInitPage( cocos2d::CCNode* pPage,int nPage );
	virtual void scrollViewClick( const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage );
	virtual void scrollViewScrollEnd( cocos2d::CCNode * pPage,int nPage );
public:
	void onButtonLeft(cocos2d::CCObject * pSender);
	void onButtonRight(cocos2d::CCObject * pSender);
	void CreateNavItem();
	void NavItemCallBack( cocos2d::CCObject* pSender );

	void guideNavIronsmith( cocos2d::CCObject* pSender );
	void guideNavMasterSchool( cocos2d::CCObject* pSender );

private:
	vector<X_INT > mNagItems;
	cocos2d::extension::CCScrollViewPage*			m_NavContent;
	 

private:
	///////////////////////////////////////////////////////
	//伐木场对象  控制伐木场相关的3个layer
	HeroWoodPVPUIViewHandle*           m_pWoodPVPHandler;
	void onButtonWoodUpgrade(cocos2d::CCObject * pSender);
	void onButtonGotoRob(cocos2d::CCObject * pSender);
	void onButtonRematch(cocos2d::CCObject * pSender);
	void onButtonRob(cocos2d::CCObject * pSender);
	void onButtonRevenge(cocos2d::CCObject * pSender);
	void onButtonHeroChange(cocos2d::CCObject * pSender);
	void OnTick( float time );

	///////////////////////////////////////////////////////
	//魔法学校  Master School layer
private:
	HeroMasterSchoolUIViewHandle*       m_pMasterSchoolHandler;
	void onButtonSkillLeveUp(cocos2d::CCObject * pSender);
	HeroIronsmithUIViewHandle*  m_pIronsmithHandler;
	void onButtonEquipLeveUp(cocos2d::CCObject * pSender);
	WoodShopUIViewHandle* m_pWoodShopHandler;

	///////////////////////////////////////////////////////
	//铁匠铺  Iron smith layer
public:
		//cocos2d::CCLayer*

};

class heroBaseActivityUIViewLoader : public cocos2d::extension::CCLayerLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(heroBaseActivityUIViewLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(heroBaseActivityUIView);
};

#endif

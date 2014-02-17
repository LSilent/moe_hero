#ifndef __GUIDELINESLAYER_H__
#define __GUIDELINESLAYER_H__

#include "cocos2d.h"
#include "./ui/baseview.h"
#include <string>
#include "cocos-ext.h"
USING_NS_CC;

typedef enum GUIDEDIRECTION
{
	GL_DIRECTION_LEFT = 1,
	GL_DIRECTION_TOP,
	GL_DIRECTION_RIGHT,
	GL_DIRECTION_BOTTOM,
};

class guidelinesLayer: public BaseView
{
public:
	guidelinesLayer();
	virtual ~guidelinesLayer();

	virtual void onEnter();
	virtual void onExit();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual	void initLayer(GUIDEDIRECTION gl);

	inline void setLayerUserData(void* pUserData)
    {
        m_layerUserData = pUserData;
    };

    inline void* getLayerUserData()
    {
        return m_layerUserData;
    };

	void setGuidePos(CCPoint pos);
	CCPoint getGuidePos();


 	void guideMenuItemCallback(CCObject *pSender);
	void glDirection(GUIDEDIRECTION gl);

	bool initGuideLayer(int guideID,CCObject* target, SEL_MenuHandler selector,CCNode *sender, bool animate);

	static guidelinesLayer *createLayer(int guideID,CCObject* target, SEL_MenuHandler selector,CCNode *sender, bool animate = true);
	static guidelinesLayer *createLayer(int guideID,CCObject* target, bool animate = true);

	CCSprite* maskedSpriteWithSprite(CCSprite* srcSp,CCSprite* maskSp,CCPoint pos);

protected:
	CCMenu *m_pMenu;
	bool m_bTouchedMenu;
	void *m_layerUserData;

	int m_iGuideID;
	CCObject* m_pListener;

	SEL_MenuHandler m_pMenuHandler;
	CCNode *m_pSender;
	CCPoint m_Pos;
	bool m_bAnimate;
};

#endif
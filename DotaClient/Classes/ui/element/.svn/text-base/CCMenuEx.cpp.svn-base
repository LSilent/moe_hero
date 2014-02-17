#include "CCMenuEx.h"

namespace cocos2d {
	void CCMenuEx::registerWithTouchDispatcher()
	{
		// lower priority  
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);  
	}

	CCMenuEx * CCMenuEx::create()  
	{  

		CCMenuEx *p = new CCMenuEx(); 
		if( p && p->init() )  
		{  
			p->autorelease();  
			return p;  
		}  

		CC_SAFE_DELETE(p);  
		return NULL;
	}  
	void CCMenuHoldEx::registerWithTouchDispatcher()
	{
		// lower priority  
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);  
	}
	float CCMenuHoldEx::mTime = 0.1f;
	CCMenuHoldEx * CCMenuHoldEx::create()  
	{  
		
		CCMenuHoldEx *p = new CCMenuHoldEx(); 
		if( p && p->init() )  
		{  
			p->autorelease();  
			return p;  
		}  
		
		CC_SAFE_DELETE(p);  
		return NULL;
	}  
	bool CCMenuHoldEx::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{    
		//m_hold = 0;
		schedule( schedule_selector(CCMenuHoldEx::updateTime), mTime );
		return CCMenu::ccTouchBegan(pTouch,pEvent);
	}
	void CCMenuHoldEx::updateTime(float time)
	{
		//m_hold++;
		if (m_pSelectedItem)
		{
			m_pSelectedItem->activate();
		}
	}
	void CCMenuHoldEx::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
	{
		CCMenu::ccTouchMoved(pTouch,pEvent);
	}
	void CCMenuHoldEx::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
	{
		unschedule(schedule_selector(CCMenuHoldEx::updateTime));

		CCMenu::ccTouchEnded(pTouch,pEvent);
	}

	/////////////////////-------------------

	void CCMenuPEx::registerWithTouchDispatcher()
	{
		// lower priority  
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);  
	}

	CCMenuPEx * CCMenuPEx::create()  
	{  
		CCMenuPEx *p = new CCMenuPEx(); 
		if( p && p->init() )  
		{  
			p->autorelease();  
			return p;  
		}  

		CC_SAFE_DELETE(p);  
		return NULL;
	}  

	CCMenuPEx * CCMenuPEx::create(CCRect &visibleRect)
	{
		CCMenuPEx *p = new CCMenuPEx(); 
		if( p && p->init() )  
		{  
			p->m_visibleRect = visibleRect;
			p->autorelease();  
			return p;  
		}  

		CC_SAFE_DELETE(p);  
		return NULL;
	}

	bool CCMenuPEx::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{    

		if(m_visibleRect.size.width && m_visibleRect.size.height)
		{
			if(!m_visibleRect.containsPoint(pTouch->getLocation()))
				return false;
		}

		m_bMoved = false;

		return CCMenu::ccTouchBegan(pTouch,pEvent);


		

	}
	void CCMenuPEx::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
	{
		m_bMoved = true;
		CCMenu::ccTouchMoved(pTouch,pEvent);
	}

	void CCMenuPEx::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
	{
		if(!m_bMoved)
			CCMenu::ccTouchEnded(pTouch,pEvent);
		else
			m_eState = kCCMenuStateWaiting;
	}

	////////////////////////////////////////////////////////////////
	
	TouchButtonEx::TouchButtonEx()
	{

	}
	TouchButtonEx::~TouchButtonEx()
	{

	}

	void TouchButtonEx::onEnter()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		CCSprite::onEnter();
	}

	void TouchButtonEx::onExit()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCSprite::onExit();
	}

	TouchButtonEx* TouchButtonEx::create(const char *normalImage, CCObject* target, SEL_CallFuncO selector)  
	{  
		TouchButtonEx *p = new TouchButtonEx();
		if (p && p->initWithFile(normalImage))
		{
		
			p->m_pListener = target;
			p->m_pSelector = selector;

			p->autorelease();

			return p;
		}
		CC_SAFE_DELETE(p);
		return NULL;
	}  

	CCRect TouchButtonEx::getRect()
	{
		CCSize size = this->getContentSize();

		return CCRectMake(- size.width /2 ,  - size.height /2 , size.width , size.height);
	}

	bool TouchButtonEx::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
	{    
		CCLOG("test cctouch began  start");
		if(!isVisible()) return false;
		CCRect rect = getRect();
		CCPoint realPos = convertTouchToNodeSpaceAR(pTouch);
		CCLog("%f-%f-%f-%f=%f-%f",rect.origin.x,rect.origin.y,rect.size.width,rect.size.height,realPos.x,realPos.y);
		if(rect.containsPoint(realPos))
		{
			isTouch = true;
		//	this->schedule(schedule_selector(TouchButtonEx::checkLongPress), 1);
			CCLOG("test cctouch began  mid");
			return true;
		}

		//CCLog("false ");

		isTouch = false;
		CCLOG("test cctouch began  end");
		return false;
	}
	void TouchButtonEx::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
	{

		CCPoint deltaPoint=pTouch->getDelta();
		if(fabs(deltaPoint.x)>1||fabs(deltaPoint.y)>1)
		{
			isMoving=true;
		}
	}

	void TouchButtonEx::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
	{
		isTouch = false;
		isMoving = false;
		(m_pListener->*m_pSelector)(this);
		//this->unschedule(schedule_selector(TouchButtonEx::checkLongPress));
	}

	void TouchButtonEx::checkLongPress(float dt)
	{
		if (isTouch&&!isMoving)
		{
			CCLog("LONGLONG");
		}

	}


}
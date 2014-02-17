#ifndef __CCMENUEX_H__
#define __CCMENUEX_H__

#include "cocos2d.h"

namespace cocos2d {


	class CCMenuEx : public CCMenu  
	{  
	public:  

		static CCMenuEx* create();  
		static CCMenuEx* create(CCRect &visibleRect); 

		// overwrite registerWithTouchDispatcher  
		virtual void registerWithTouchDispatcher();  

	 
	};  
	class CCMenuHoldEx : public CCMenu  
	{  
	public:  
		
		static CCMenuHoldEx* create();  
		static CCMenuHoldEx* create(CCRect &visibleRect); 

		// overwrite registerWithTouchDispatcher  
		virtual void registerWithTouchDispatcher();  

		virtual	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	   // unsigned int  m_hold;
		void updateTime(float time);
		static float mTime;
	};  


	class CCMenuPEx : public CCMenu  
	{  
	public:  

		static CCMenuPEx* create();  
		static CCMenuPEx* create(CCRect &visibleRect); 

		// overwrite registerWithTouchDispatcher  
		virtual void registerWithTouchDispatcher();  

		virtual	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	private:
		bool m_bMoved;
		CCRect m_visibleRect;
	};


	
	class TouchButtonEx: public CCSprite , public CCTargetedTouchDelegate
	{

	public:
		static TouchButtonEx* create(const char *normalImage, CCObject* target, SEL_CallFuncO selector); 

	public:
		TouchButtonEx();
		~TouchButtonEx();

		virtual void onEnter();
		virtual void onExit();

		virtual	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	public:
		void checkLongPress(float dt);
		CCRect getRect();

	private:
		CCObject* m_pListener;
		SEL_CallFuncO m_pSelector;

		bool isTouch;
		bool isMoving;
	};





}

#endif

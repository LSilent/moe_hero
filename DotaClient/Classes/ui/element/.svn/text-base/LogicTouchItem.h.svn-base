#ifndef __LOGIC_TOUCH_ITEM_H__
#define __LOGIC_TOUCH_ITEM_H__

#include "cocos2d.h"
#include "cocos-ext.h"

namespace cocos2d {

	typedef enum GAME_HERO_QUALITY
	{
		HERO_QUALITY_1 = 1,	//1=╟в
		HERO_QUALITY_2,		//2=бл
		HERO_QUALITY_3,		//3=ю╤
		HERO_QUALITY_4,		//4=во
		HERO_QUALITY_5,		//5=╫П
	};

	class LogicTouchItem : public CCSprite, public CCTargetedTouchDelegate
	{
	public:
		LogicTouchItem(void);;
		virtual ~LogicTouchItem(void);;

		virtual void onEnter();
		virtual void onExit();

		CCRect getRect();
		bool containsTouchLocation(CCTouch* touch);

		virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
		virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

		//static LogicTouchItem* createWithTexture(CCTexture2D* aTexture);
		static LogicTouchItem* createWithFile(const char *pszFileName, CCObject* target, 
												SEL_CallFuncO selectorTB,
												SEL_CallFuncO selectorTM,
												SEL_CallFuncO selectorTE, 
												bool isMovable = false,
												int priority = 10);
		//static LogicTouchItem* createWithFile(const char *pszFileName, const CCRect& rect);

		void setMovable( bool isMovable );
		void setTouchable( bool isTouchable );

	protected:
		
		CCObject* m_pListener;
		SEL_CallFuncO m_selectorTB;
		SEL_CallFuncO m_selectorTM;
		SEL_CallFuncO m_selectorTE;

		bool m_isTouchable;
		bool m_isMovable;
		
		int m_priority;
	};



	class LogicTouchLabel : public CCLabelTTF, public CCTargetedTouchDelegate
	{
	public:
		LogicTouchLabel(void) { m_isTouchable = true; };
		virtual ~LogicTouchLabel(void) {};

		virtual void onEnter();
		virtual void onExit();

		CCRect getRect();
		bool containsTouchLocation(CCTouch* touch);

		virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
		virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
		virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

		//??? FIXME
		virtual void touchDelegateRetain() { this->retain(); };
		virtual void touchDelegateRelease() { this->release(); };

		//static LogicTouchItem* createWithTexture(CCTexture2D* aTexture);
		static LogicTouchLabel* createWithString(const char *label, const char *fontName, float fontSize, 
												CCObject* target, 
												SEL_CallFuncO selectorTB,
												SEL_CallFuncO selectorTM,
												SEL_CallFuncO selectorTE,
												bool isMovable = false,
												int priority = 10);
		//static LogicTouchItem* createWithFile(const char *pszFileName, const CCRect& rect);

		void setMovable( bool isMovable ) { m_isMovable = isMovable; } 
		void setTouchable( bool isTouchable ) { m_isTouchable = isTouchable; } 

	private:
		
		CCObject* m_pListener;
		SEL_CallFuncO m_selectorTB;
		SEL_CallFuncO m_selectorTM;
		SEL_CallFuncO m_selectorTE;

		bool m_isTouchable;
		bool m_isMovable;
		int m_priority;
	};



	class HeroHeadIcon:public LogicTouchItem
	{
	public:
		HeroHeadIcon(void){};
		virtual ~HeroHeadIcon(void){};

		static LogicTouchItem* createWithFile(const char *pszFileName, CCObject* target, 
												SEL_CallFuncO selectorTB,
												SEL_CallFuncO selectorTM,
												SEL_CallFuncO selectorTE, 
												int ColorIndex,
												bool isMovable = false,
												int priority = 10,int level =-1);


		
	};

}




#endif

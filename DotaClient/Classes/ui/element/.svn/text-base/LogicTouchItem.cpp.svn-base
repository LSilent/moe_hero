#include "LogicTouchItem.h"
#include "./base/Global.h"
#include "./game/GameHelper.h"

#define  MAX_FILE_SIZE (128)
#define MAX_STRING_BUFF_SIZE    (128)

namespace cocos2d {

	void LogicTouchItem::onEnter()
	{
		CCSprite::onEnter();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_priority, true);
	}

	void LogicTouchItem::onExit()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCSprite::onExit();
	}

	CCRect LogicTouchItem::getRect()
	{
		CCSize s = getTexture()->getContentSize();
		return CCRectMake(-s.width * 0.5f, -s.height * 0.5f, s.width, s.height);
	}

	bool LogicTouchItem::containsTouchLocation(CCTouch* touch)
	{
		return getRect().containsPoint( convertTouchToNodeSpaceAR(touch) );
	}

	bool LogicTouchItem::ccTouchBegan(CCTouch* touch, CCEvent* event)
	{
		if( !m_isTouchable ) return false;

		if ( containsTouchLocation(touch) ) 
		{
			// invoke the call back
			(m_pListener->*m_selectorTB)(this);
			return true;
		}
		else
			return false;
	}

	void LogicTouchItem::ccTouchMoved(CCTouch* touch, CCEvent* event)
	{
		if( !m_isTouchable ) return;

		if( m_isMovable )
		{
			CCPoint touchPoint = touch->getLocationInView();
			CCPoint touchPrePoint = touch->getPreviousLocationInView();
		    
			touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
			touchPrePoint = CCDirector::sharedDirector()->convertToGL( touchPrePoint );
			
			CCPoint moveTo = this->getPosition();
			moveTo.x += touchPoint.x - touchPrePoint.x;
			moveTo.y += touchPoint.y - touchPrePoint.y;
				
			this->setPosition( moveTo );
		}
		
		(m_pListener->*m_selectorTM)(this);
	}

	void LogicTouchItem::ccTouchEnded(CCTouch* touch, CCEvent* event)
	{
		// be call only if ccTouchBegan() return true

		if( !m_isTouchable ) return;

		// invoke the call back
		if ( containsTouchLocation(touch) ) 
		    (m_pListener->*m_selectorTE)(this);
	}

	LogicTouchItem* LogicTouchItem::createWithFile(const char *pszFileName, CCObject* target, 
													SEL_CallFuncO selectorTB,
													SEL_CallFuncO selectorTM,
													SEL_CallFuncO selectorTE,
													bool isMovable,
													int priority)
	{
		LogicTouchItem *p = new LogicTouchItem();
		if (p && p->initWithFile(pszFileName))
		{
			p->m_pListener = target;
			p->m_selectorTB = selectorTB;
			p->m_selectorTM = selectorTM;
			p->m_selectorTE = selectorTE;

			p->m_isMovable = isMovable;
			p->m_priority = priority;

			p->autorelease();
			
			return p;
		}
		CC_SAFE_DELETE(p);
		return NULL;
	}

	void LogicTouchItem::setTouchable( bool isTouchable )
	{
		m_isTouchable = isTouchable;
	}

	void LogicTouchItem::setMovable( bool isMovable )
	{
		m_isMovable = isMovable;
	}

	LogicTouchItem::~LogicTouchItem( void )
	{

	}

	LogicTouchItem::LogicTouchItem( void )
	{
		m_isTouchable = true;
	}


	//----------------------------------------------------------------------------------

	void LogicTouchLabel::onEnter()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_priority, true);
		CCLabelTTF::onEnter();
	}

	void LogicTouchLabel::onExit()
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		CCLabelTTF::onExit();
	}

	CCRect LogicTouchLabel::getRect()
	{
		CCSize s = getTexture()->getContentSize();
		return CCRectMake(-s.width * 0.5f, -s.height * 0.5f, s.width, s.height);
	}

	bool LogicTouchLabel::containsTouchLocation(CCTouch* touch)
	{
		return getRect().containsPoint(convertTouchToNodeSpaceAR(touch));
	}

	bool LogicTouchLabel::ccTouchBegan(CCTouch* touch, CCEvent* event)
	{
		if( !m_isTouchable ) return false;

		if ( containsTouchLocation(touch) ) 
		{
			// invoke the call back
			(m_pListener->*m_selectorTB)(this);
			return true;
		}
		else
			return false;
	}

	void LogicTouchLabel::ccTouchMoved(CCTouch* touch, CCEvent* event)
	{
		if( !m_isTouchable ) return;

		if( m_isMovable )
		{
			CCPoint touchPoint = touch->getLocationInView();
			CCPoint touchPrePoint = touch->getPreviousLocationInView();
		    
			touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );
			touchPrePoint = CCDirector::sharedDirector()->convertToGL( touchPrePoint );
			
			CCPoint moveTo = this->getPosition();
			moveTo.x += touchPoint.x - touchPrePoint.x;
			moveTo.y += touchPoint.y - touchPrePoint.y;
				
			this->setPosition( moveTo );
		}
		else
			(m_pListener->*m_selectorTM)(this);
	}

	void LogicTouchLabel::ccTouchEnded(CCTouch* touch, CCEvent* event)
	{
		// be call only if ccTouchBegan() return true

		if( !m_isTouchable ) return;

		// invoke the call back
		(m_pListener->*m_selectorTE)(this);
	}

	LogicTouchLabel* LogicTouchLabel::createWithString(const char *label, const char *fontName, float fontSize, 
														CCObject* target, 
														SEL_CallFuncO selectorTB,
														SEL_CallFuncO selectorTM,
														SEL_CallFuncO selectorTE,
														bool isMovable,
														int priority)
	{
		LogicTouchLabel *p = new LogicTouchLabel();
		if (p && p->initWithString(label, fontName, fontSize))
		{
			p->m_pListener = target;
			p->m_selectorTB = selectorTB;
			p->m_selectorTM = selectorTM;
			p->m_selectorTE = selectorTE;

			p->m_isMovable = isMovable;
			p->m_priority = priority;

			p->autorelease();
			
			return p;
		}
		CC_SAFE_DELETE(p);
		return NULL;
	}

	//----------------------------------------------------------------------------------



	LogicTouchItem * HeroHeadIcon::createWithFile(const char *pszFileName, CCObject* target, 
													SEL_CallFuncO selectorTB,
													SEL_CallFuncO selectorTM,
													SEL_CallFuncO selectorTE, 
													int ColorIndex,
													bool isMovable,
													int priority,int level)
	{
		
		if (ColorIndex < EM_HERO_COLOR_TYPE1 || ColorIndex > EM_HERO_COLOR_TYPE6)
		{
			return LogicTouchItem::createWithFile(pszFileName,target,selectorTB,selectorTM,selectorTE,isMovable,priority);
		}

		HeroHeadIcon *pIcon = new HeroHeadIcon();

		if (pIcon && pIcon->initWithFile("n_pos_back_.png"))
		{
			pIcon->m_pListener = target;
			pIcon->m_selectorTB = selectorTB;
			pIcon->m_selectorTM = selectorTM;
			pIcon->m_selectorTE = selectorTE;
			pIcon->m_isMovable = isMovable;
			pIcon->m_priority = priority;
	
            CCLOG(pszFileName);
			CCSprite *mBackground = CCSprite::create(pszFileName);
           
			mBackground -> setAnchorPoint(ccp(0.5f, 0.5f));
			mBackground -> setPosition(ccp(pIcon->getContentSize().width *0.5,pIcon->getContentSize().height * 0.5));
			pIcon -> addChild(mBackground);

			CCSprite *mHead = CCSprite::create(GameHelper::GetHeroColorById(ColorIndex).c_str());
			
			mHead->setPosition(ccp(pIcon->getContentSize().width *0.5,pIcon->getContentSize().height * 0.5));

			pIcon->addChild(mHead);

			pIcon->autorelease();

		//	if (level >= 0)
			{


			CCSprite *mLevelBack = CCSprite::create("hero_level_icon.png");
			mLevelBack->setAnchorPoint(CCPoint(0.5f,0.5)) ;
			mLevelBack->setPosition(CCPoint(mHead->getContentSize().width*0.86f,mLevelBack->getContentSize().height*0.26f));
			mHead->addChild(mLevelBack);

			char aText[MAX_STRING_BUFF_SIZE];
			sprintf( aText, "%d", level);
			CCLabelBMFont *mLevelLable = CCLabelBMFont::create(aText, FNT_NAME_HEROLEVEL);
			mLevelLable -> setAnchorPoint(ccp(0.5f, 0.5f));
			mLevelLable -> setPosition(CCPoint(mLevelBack->getContentSize().width/2.0f,mLevelBack->getContentSize().height/2.0f));
			mLevelBack -> addChild(mLevelLable);

			}

			return pIcon;
		}
			CC_SAFE_DELETE(pIcon);
			return NULL;
	}




}
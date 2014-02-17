#include "CCScrollViewEx.h"

#define SCROLL_MOVE_MIN_OFFSET   (0.02f)

#define SCROLL_ADJUST_VELOCITY (800)
#define ADJUST_ANIM_VELOCITY (2000)

#ifndef c_max
#define c_max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef c_min
#define c_min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

namespace cocos2d {
namespace extension {

	CCScrollViewEx * CCScrollViewEx::create()  
	{  
		CCScrollViewEx *p = new CCScrollViewEx(); 
		if( p && p->init() )  
		{  
			p->mIsMoved = false;

			p->autorelease();  
			return p;  
		}  
		
		CC_SAFE_DELETE(p);  
		return NULL;
	}  

	bool CCScrollViewEx::ccTouchBegan(CCTouch* touch, CCEvent* event)
	{
		mIsMoved = false;
		mOffset = getContentOffset();

		return CCScrollView::ccTouchBegan(touch, event);
	}

	void CCScrollViewEx::ccTouchMoved(CCTouch* touch, CCEvent* event)
	{
		CCScrollView::ccTouchMoved(touch, event);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint curOffset = getContentOffset();
		if( !ccpFuzzyEqual( mOffset, curOffset, winSize.width * SCROLL_MOVE_MIN_OFFSET ) )
			mIsMoved = true;
	}

	void CCScrollViewEx::ccTouchEnded(CCTouch* touch, CCEvent* event)
	{
		CCScrollView::ccTouchEnded(touch, event);

		
		
	}

	void CCScrollViewEx::ccTouchCancelled(CCTouch* touch, CCEvent* event)
	{
		CCScrollView::ccTouchCancelled(touch, event);

	}

	//--------------------------------------------------------


	CCScrollViewPage::CCScrollViewPage()
		:m_fAdjustSpeed(ADJUST_ANIM_VELOCITY)
		, m_nPrePage(0)
	{

	}

	CCScrollViewPage::~CCScrollViewPage()
	{

	}

	bool CCScrollViewPage::init()
	{
		if (!CCScrollView::init())
		{
			return false;
		}

		return true;
	}

	bool CCScrollViewPage::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
	{
		m_BeginOffset = getContentOffset();
		return CCScrollView::ccTouchBegan(pTouch, pEvent);
	}

	void CCScrollViewPage::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
	{
		CCScrollView::ccTouchMoved(pTouch, pEvent);
	}

	void CCScrollViewPage::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
	{
		CCPoint touchPoint = pTouch->getLocationInView();
		touchPoint = CCDirector::sharedDirector()->convertToGL( touchPoint );	

		CCScrollView::ccTouchEnded(pTouch, pEvent);

		CCPoint m_EndOffset=getContentOffset();

		if (m_BeginOffset.equals(m_EndOffset))
		{

			if (!m_pDelegate)
			{
				return;
			}

			int nPage = abs(m_EndOffset.x / (int)m_CellSize.width);
			CCScrollViewPageDelegate* pDele=(CCScrollViewPageDelegate*)m_pDelegate;
			pDele->scrollViewClick(m_EndOffset,touchPoint,m_pContainer->getChildByTag(nPage),nPage);
			return ;
		}

		adjustScrollView(m_BeginOffset,m_EndOffset);
	}

	void CCScrollViewPage::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
	{
		CCScrollView::ccTouchCancelled(pTouch, pEvent);

		CCPoint m_EndOffset=getContentOffset();
		adjustScrollView(m_BeginOffset,m_EndOffset);
	}

	void CCScrollViewPage::adjustScrollView( const cocos2d::CCPoint& oBegin,const cocos2d::CCPoint & oEnd)
	{

		int nPage = abs(oBegin.x / (int)m_CellSize.width);

		int nAdjustPage = 0;

		int nDis = oEnd.x-oBegin.x;

		if (nDis<-getViewSize().width/5)
		{
			nAdjustPage=nPage+1;
		}
		else if (nDis>getViewSize().width/5)
		{
			nAdjustPage=nPage-1;
		}
		else
		{
			nAdjustPage=nPage;
		}

		nAdjustPage=c_min(nAdjustPage,m_nPageCount-1); 
		nAdjustPage=c_max(nAdjustPage,0);

		scrollToPage(nAdjustPage);
	}

	void CCScrollViewPage::scrollToPage( int nPage )
	{
		// 关闭CCScrollView中的自调整
		unscheduleAllSelectors();

		CCPoint oOffset=getContentOffset();
		// 调整位置
		CCPoint adjustPos=ccp(-m_CellSize.width*nPage,0);

		// 调整动画时间
		float adjustAnimDelay=ccpDistance(adjustPos,oOffset)/m_fAdjustSpeed;

		// 调整位置
		setContentOffsetInDuration(adjustPos, adjustAnimDelay);

		if (nPage!=m_nPrePage)
		{
			schedule(schedule_selector(CCScrollViewPage::onScrollEnd),adjustAnimDelay,0,0.0f);
			m_nPrePage=nPage;
		}
	}
	void CCScrollViewPage::directToPage(int nPage)
	{
		CCPoint oOffset=getContentOffset();
		CCPoint adjustPos=ccp(-m_CellSize.width*nPage,0);
		m_pContainer->setPosition(  m_pContainer->getPosition() + adjustPos);
	}
	void CCScrollViewPage::onScrollEnd(float fDelay)
	{
		int nPage=getCurPage();
		if (!m_pDelegate)
		{
			return;
		}
		
		CCScrollViewPageDelegate* pDele=(CCScrollViewPageDelegate*)m_pDelegate;
		pDele->scrollViewScrollEnd(m_pContainer->getChildByTag(nPage),nPage);
	}

	void CCScrollViewPage::scrollToNextPage()
	{
		int nCurPage=getCurPage();
		if (nCurPage>=m_nPageCount-1)
		{
			return ;
		}
		scrollToPage(nCurPage+1);
	}

	void CCScrollViewPage::scrollToPrePage()
	{
		int nCurPage=getCurPage();
		if (nCurPage<=0)
		{
			return ;
		}
		scrollToPage(nCurPage-1);
	}

	bool CCScrollViewPage::createContainer(CCScrollViewPageDelegate* pDele, int nCount,const cocos2d::CCSize & oSize )
	{
		m_nPageCount=nCount;
		m_CellSize=oSize;
		setDelegate(pDele);

		CCLayer* pContainer=CCLayer::create();
		
		pContainer->setAnchorPoint(CCPointZero);
		pContainer->setPosition(CCPointZero);

		CCSize winSize=CCDirector::sharedDirector()->getVisibleSize();

		for (int i=0;i<nCount;++i)
		{
			CCNode* pNode=CCNode::create();

			pNode->setAnchorPoint(ccp(0.5,0.5));
 
			pDele->scrollViewInitPage(pNode,i);
  
			pNode->setPosition(ccp(i*oSize.width, 0));

 
			pNode->setTag(i);
			pContainer->addChild(pNode);
		}



		setContainer(pContainer);
		setContentSize(CCSizeMake(oSize.width*nCount,oSize.height));



		return true;
	}

	int CCScrollViewPage::getCurPage()
	{
		return abs(getContentOffset().x / (int)m_CellSize.width);
	}

	//----------------------------------------
	CCPageControll::CCPageControll()
	{

	}
	
	CCPageControll::~CCPageControll()
	{

	}

	 CCPageControll *CCPageControll::create()
	 {
		 CCPageControll *p = new CCPageControll(); 
		 if( p && p->init() )  
		 {  
			 p->m_iPageTotalNum = 0;
			 

			 p->autorelease();  
			 return p;  
		 }  

		 CC_SAFE_DELETE(p);  
		 return NULL;
	 

	 }

	 CCPageControll *CCPageControll::create(const std::string &pSelectedFile,const std::string &pUnSelectFile,int pageNum, CCSize &oSize)
	 {
		 CCPageControll *p = new CCPageControll(); 
		 if( p && p->init() )  
		 {  

			 p->m_iPageTotalNum = pageNum;
			 p->m_pSelected = pSelectedFile;
			 p->m_pUnSelect = pUnSelectFile;
			 p->m_visibleSize = oSize;
			 p->lastPageIndex = 0;

			 p->initControll();

			 p->autorelease();  
			 return p;  
		 }  

		 CC_SAFE_DELETE(p);  
		 return NULL;
	 }

	 void CCPageControll::initControll()
	 {
		if (m_iPageTotalNum <= 0)
		{
			return;
		}

		//scale
		CCSprite *tmp = CCSprite::create(m_pSelected.c_str());
		float space_x = tmp->getContentSize().width * 1.5;
		float start_x =(m_visibleSize.width - space_x * (m_iPageTotalNum - 1)) * 0.5;
		for (int i = 0;i < m_iPageTotalNum; i++)
		{
			CCSprite *sIcon;
			if (i == 0)
			{
				sIcon = CCSprite::create(m_pSelected.c_str());
			}
			else
			{
				sIcon = CCSprite::create(m_pUnSelect.c_str());
			}
			
			CCPoint pos = ccp(start_x + i * space_x , m_visibleSize.height *0.5);
			sIcon->setPosition(pos);

			m_SpriteItems.push_back(sIcon);

			addChild(sIcon);
		}

	 }

	 void CCPageControll::setPageNum(int page)
	 {
		 if (page < 0 || page >= m_iPageTotalNum)
		 {
			 return;
		 }
			 if (lastPageIndex == page)
			 {
				 return;
			 }

			 CCTexture2D *texture2D1 = CCTextureCache::sharedTextureCache()->addImage(m_pSelected.c_str());
			 m_SpriteItems[page]->setTexture(texture2D1);

			 CCTexture2D *texture2D2 = CCTextureCache::sharedTextureCache()->addImage(m_pUnSelect.c_str());
			 m_SpriteItems[lastPageIndex]->setTexture(texture2D2);

			 lastPageIndex = page;
		 }
	 
	
}
}

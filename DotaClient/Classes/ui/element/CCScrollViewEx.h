#ifndef __CCSCROLLVIEWEX_H__
#define __CCSCROLLVIEWEX_H__

#include "cocos2d.h"
#include "cocos-ext.h"

namespace cocos2d {
namespace extension {

	class CCScrollViewEx : public CCScrollView
	{  
	public:  
		
		static CCScrollViewEx* create();  
  
		/** override functions */
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	public:

		bool mIsMoved;
		
		CCPoint mOffset;
	}; 


	//----------------------------------------------------------------------------------


	class CCScrollViewPageDelegate
		: public cocos2d::extension::CCScrollViewDelegate
	{
	public:
		virtual bool scrollViewInitPage(cocos2d::CCNode* pPage,int nPage)=0;
		virtual void scrollViewClick(const cocos2d::CCPoint& oOffset,const cocos2d::CCPoint & oPoint ,cocos2d::CCNode * pPage,int nPage )=0;
		virtual void scrollViewScrollEnd(cocos2d::CCNode * pPage,int nPage)=0;
	};


	class CCScrollViewPage: public CCScrollView
	{
	public:
		CCScrollViewPage();
		~CCScrollViewPage();
	public:
		CREATE_FUNC(CCScrollViewPage);

		bool init();

		bool createContainer(CCScrollViewPageDelegate* pDele, int nCount,const cocos2d::CCSize & oSize );

		virtual bool ccTouchBegan( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

		virtual void ccTouchMoved( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

		virtual void ccTouchEnded( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

		virtual void ccTouchCancelled( cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent );

		void scrollToPage(int nPage);
		void scrollToNextPage();
		void scrollToPrePage();

		int getCurPage();
		void directToPage(int nPage);
	protected:
		void adjustScrollView(const cocos2d::CCPoint& oBegin,const cocos2d::CCPoint & oEnd);

		virtual void onScrollEnd(float fDelay);
	protected:
		int m_nPageCount;
		int m_nPrePage;
		cocos2d::CCPoint m_BeginOffset;
		cocos2d::CCSize m_CellSize;
		float m_fAdjustSpeed;
	};

	//---------------------------------

	class CCPageControll: public cocos2d::CCLayer
	{
	public:
		CCPageControll();
		~CCPageControll();

		static CCPageControll *create();
		static CCPageControll *create(const std::string &pSelectedFile,const std::string &pUnSelectFile,int pageNum, CCSize &oSize);

		void initControll();
		void setPageNum(int page);

	private:
		int m_iPageTotalNum;
		std::string m_pSelected;
		std::string m_pUnSelect;
		CCSize m_visibleSize;
		std::vector<CCSprite *> m_SpriteItems;
		int lastPageIndex;

	};

}
}

#endif

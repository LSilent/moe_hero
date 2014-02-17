#include "./ui/NoticeUIView.h"

 
#define VIEW_HEIGHT 0.82





bool NoticeView::init()
{
	bool bRet = false;
	do 
	{ 
		CC_BREAK_IF(! CCLayer::init());
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		m_text= CCLabelTTF::create();
		CC_BREAK_IF(! m_text);
		m_text->setPosition(ccp(size.width, size.height*VIEW_HEIGHT));
		this->addChild(m_text, 0);
		m_text->setFontName(FONT_NAME_ARIAL_BOLD);
		m_text->setFontSize(25);
		m_text->setColor(ccWHITE);
		this->setKeypadEnabled(false);
		this->setTouchEnabled(false);
		this->setZOrder(999999999);
		bRet = true;

		isRolling = false;

		mNotices.clear();

	} while (0);

	return bRet;
}
void NoticeView::onDataUpdate( const vector<string>& tips)
{

// 	mNotices = tips;
	for (X_UINT i=0;i<tips.size();i++)
	{
		mNotices.push_back(tips[i]);
	}
	
	X_UINT size = mNotices.size();
	if (size == 0)return;

	if(UISystem::GetSingleton()->isMain() && !isRolling)
	{
		this->setVisible(true);
		str = mNotices[0].c_str();
		m_text->setString(str.c_str());
		m_text->setAnchorPoint(ccp(0,0.5));
		m_text->setPositionX(CCDirector::sharedDirector()->getWinSize().width);
		this->schedule(cocos2d::SEL_SCHEDULE(&NoticeView::autoRoll),1.0f/10);

		isRolling = true;
	}
	
	 
}
 
void  NoticeView::autoRoll(float dt )
{
	if(!UISystem::GetSingleton()->isMain())
	{

		stopRollNotice();

		return;
	}


	CCSize size = CCDirector::sharedDirector()->getWinSize();
	int x = m_text->getPositionX()- 5;
	int width =  m_text->getContentSize().width;
	if (x + width >= 0)
	{
		m_text->setPosition( CCPoint(x,size.height*VIEW_HEIGHT));
	}
	else
	{

		  vector<string>::iterator iter;
		  iter = find(mNotices.begin(),mNotices.end(),str);
		  if(iter != mNotices.end())
			  mNotices.erase(iter);

		  

		  if (mNotices.empty())
		  {

			  isRolling = false;

			  this->setVisible(false);
			  unschedule(SEL_SCHEDULE(&NoticeView::autoRoll));
			  return;
		  }
		  
		  str = mNotices.front();
		  m_text->setString(str.c_str());
		  m_text->setPositionX(CCDirector::sharedDirector()->getWinSize().width);
	}
	


	return;
	NoticeUi *   ui = (NoticeUi *) getUserData();
	 if (ui)
	 {
		ui->Show(false);
	 }
	 
} 
void NoticeView::onExit()
{
	BaseView::onExit();
}

bool NoticeView::getIsRolling()
{
	return isRolling;
}

void NoticeView::stopRollNotice()
{
	vector<string>::iterator iter;
	iter = find(mNotices.begin(),mNotices.end(),str);
	if(iter != mNotices.end())
		mNotices.erase(iter);

	isRolling = false;

	this->setVisible(false);
	unschedule(SEL_SCHEDULE(&NoticeView::autoRoll));
}
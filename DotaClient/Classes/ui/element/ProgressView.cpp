#include "ProgressView.h"
#include "./base/Global.h"

#define  MAX_FILE_SIZE (128)



	ProgressView::ProgressView()
	{
	}

	ProgressView::~ProgressView()
	{
	}

ProgressView *ProgressView::createProgress(const char *pFileName)
{
	ProgressView *p = new ProgressView ();
	if (p)
	{
		CCProgressTimer *mProgressTime = CCProgressTimer::create(CCSprite::create(pFileName));
		mProgressTime->setType(kCCProgressTimerTypeBar );
		mProgressTime->setMidpoint(ccp(0,0));
		mProgressTime->setBarChangeRate(ccp(1,0));

		mProgressTime->setPercentage(0.f);

		mProgressTime->setAnchorPoint(ccp(0,0.5));
		p->m_pProgressTimer = mProgressTime;

		p->iType = PROGRESS_ADD;
		p->m_curValue = 0;
		p->m_DesValue = 100;
		p->m_iNum = 0;

		p->addChild(p->m_pProgressTimer);

		p->autorelease();
		return p;
	}
	
	CC_SAFE_DELETE(p);
	return NULL;
}

void ProgressView::update(float dt)
{
	 
 

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	float curLen = m_pProgressTimer->getPercentage();

	float deltaLen = dt * winSize.width * 0.3;

	if(iType == PROGRESS_ADD)
	{
		if (curLen >= 100 && m_iNum!=0)
		{
			m_iNum--;
			curLen = 0;
		}

		curLen += deltaLen;
		if (curLen >= m_DesValue && m_iNum == 0)
		{
			curLen = m_DesValue;
			unscheduleUpdate();
		}
	}
	else if(iType == PROGRESS_SUB)
	{
		if (curLen <= 0 && m_iNum!=0)
		{
			m_iNum--;
			curLen = 100;
		}

		curLen -= deltaLen;
		if (curLen <= m_DesValue && m_iNum == 0)
		{
			curLen = m_DesValue;
			unscheduleUpdate();
		}

	}
	
 	m_pProgressTimer->setPercentage(curLen);

	
}


void ProgressView::setProgressValue(float fNum ,int num , ProgressIdenType type, bool flag)
{
	//

	iType = type;
	m_DesValue = fNum;
	m_iNum = num;
	if (flag)
	{
		unscheduleUpdate();
		scheduleUpdate();
	}
	else
	{
		m_pProgressTimer->setPercentage(m_DesValue);
	}
	
}





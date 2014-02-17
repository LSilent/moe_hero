#include "./ui/TipUiView.h"

 


bool TipView::init()
{
	bool bRet = false;
	do 
	{ 
		CC_BREAK_IF(! CCLayer::init());
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		tipBg = CCSprite::create("tipdlg.png");//chat_editbox_back
		CCPoint itemPos = ccp(size.width/2, size.height*0.5f);
		tipBg->setPosition(itemPos);
		this->addChild(tipBg);
		 
		m_text= CCLabelTTF::create();
		CC_BREAK_IF(! m_text);
		m_text->setPosition(ccp(tipBg->getContentSize().width*0.5f , tipBg->getContentSize().height*0.5f));
		tipBg->addChild(m_text, 0);

		m_text->setFontSize(FONT_SIZE_30);
		m_text->setColor(ccGREEN);
		m_text->setFontName(FONT_NAME_ARIAL_BOLD);
		m_text->setHorizontalAlignment(kCCTextAlignmentCenter);
		this->setKeypadEnabled(false);
		this->setTouchEnabled(false);
	 

		tipConnect = CCSprite::create("connect_back.png");
		tipConnect->setPosition(itemPos);
		this->addChild(tipConnect);
		
        m_cache.clear();
		m_bconnectcache.clear();
		bRet = true;

	} while (0);

	return bRet;
}
void TipView::onDataUpdate( const vector<string>& tips)
{
   
	X_UINT size = tips.size();
	if (size == 0)return;
	

	CCLOG("tip ---------------------- ");
	m_cache.clear();m_bconnectcache.clear();
    m_cache.push_back(tips[0]);
	if (tips.size() > 1)
	{
		m_bconnectcache.push_back(tips[1] == string("1"));
	}else
	{
		m_bconnectcache.push_back(false);
	}
	
	this->setZOrder(99999);	
 
	showTip();
    
}
void TipView::showTip()
{
	 
		if(*(m_bconnectcache.begin())== true)
		{
			tipConnect->setVisible(true);
			tipBg->setVisible(false);
		}else
		{
			tipConnect->setVisible(false);
			tipBg->setVisible(true); 
			m_text->setString( (*(m_cache.begin())).c_str());
			m_cache.erase(m_cache.begin());
		}
		 
      	CCSize size = CCDirector::sharedDirector()->getWinSize();
        CCPoint dus = CCPoint(size.width*0.5f,size.height*0.65f);
		if(*(m_bconnectcache.begin())!= true)
		{
			 
			CCScaleTo *scaleTo = CCScaleTo::create(0.3f, 1.2f);
			CCScaleTo *scaleTo2 = CCScaleTo::create(0.2f, 1.f);
			CCMoveTo *moveTo = CCMoveTo::create(0.5f,dus);
			//CCFadeOut *fade = CCFadeOut::create(0.2f);
			CCDelayTime *delay = CCDelayTime::create( 0.2f);
			CCRemoveSelf *hide = CCRemoveSelf::create(true);
			
			CCSequence *seq = CCSequence::create(scaleTo,scaleTo2,moveTo,delay,hide,NULL);
			tipBg->runAction(seq);
		}else
		{
			CCDelayTime *delay = CCDelayTime::create( 1.0f);
			CCRemoveSelf *hide = CCRemoveSelf::create(true);
			CCSequence *seq = CCSequence::create(delay,hide,NULL);
			tipConnect->runAction(seq);
		}
 
     //this->schedule(cocos2d::SEL_SCHEDULE(&TipView::autoDel),1.0f);
     m_bconnectcache.erase(m_bconnectcache.begin());
}

void  TipView::autoDel(float dt )
{ 
	 SceneManger::GetSingleton()->RemoveChildFormScene(this,true);
} 
void TipView::onExit()
{
	CCLayer::onExit();
}
#include "guidelinesLayer.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"
#include "./datapool/GuideData.h"
#include "./ui/ui.h"

guidelinesLayer::guidelinesLayer()
{
}

guidelinesLayer::~guidelinesLayer()
{
}

CCSprite* guidelinesLayer::maskedSpriteWithSprite(CCSprite* srcSp,CCSprite* maskSp,CCPoint pos)
{


	//首先我们先来根据遮罩的大小来创建一个CCRenderTexture
	int w = maskSp->getContentSize().width * maskSp->getScaleX();
	int h = maskSp->getContentSize().height * maskSp->getScaleY();
	CCRenderTexture* rt = CCRenderTexture::create(w, h , kTexture2DPixelFormat_RGBA8888);
	

	//接下来设置srcSp和maskSp的位置
	maskSp->setPosition( ccp(maskSp->getContentSize().width *  maskSp->getScaleX()/2,
		maskSp->getContentSize().height * maskSp->getScaleY()/2));
	srcSp->setPosition( ccp(srcSp->getContentSize().width *  srcSp->getScaleX() /2,
		srcSp->getContentSize().height * srcSp->getScaleY()/2));

//  	CCSize wSize = CCDirector::sharedDirector()->getWinSize();
//  	srcSp->setPosition(ccp(pos.x,wSize.height - pos.y));
	
	//设置精灵的混合模式
	ccBlendFunc blendFunc1;
	blendFunc1.src = GL_ONE;//GL_ONE;
	blendFunc1.dst = GL_ZERO;
	maskSp->setBlendFunc(blendFunc1);

	ccBlendFunc blendFunc2;
	blendFunc2.src = GL_DST_ALPHA/*GL_DST_ALPHA*/;   // mask图片的当前alpha值是多少，如果是0（完全透明），那么就显示mask的。如果是1（完全不透明）
	blendFunc2.dst = GL_ZERO;    // maskSprite不可见
	srcSp->setBlendFunc(blendFunc2);

	//开始rt中写入纹理
	rt->begin();
	maskSp->visit();
	srcSp->visit();
	rt->end();

	//利用纹理创建一个精灵！
	CCSprite* retval = CCSprite::createWithTexture(rt->getSprite()->getTexture());
	//retval->setFlipY(true);
	return retval;
}

void guidelinesLayer::initLayer(GUIDEDIRECTION gl)
{
	//TODO	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();


	//m_guide_mask_b //m_mask_bg
/*
	CCSprite* lay = CCSprite::create("Calendar2.png");//CalendarMask  Calendar2.png
	lay->setPosition(ccp(winSize.width/2,winSize.height/2));

	CCSprite* mask = CCSprite::create("CalendarMask.png");
	mask->setPosition(ccp(winSize.width/2,winSize.height/2));

	CCSprite *rSprite = maskedSpriteWithSprite(lay,mask,m_Pos);
	rSprite->setPosition(ccp(winSize.width * 0.5f,winSize.height * 0.5f));
	addChild(rSprite);*/

	m_pMenu = NULL;

	m_pMenu = CCMenu::create();
	m_pMenu->setPosition(CCPointZero);
	addChild(m_pMenu);

	CCMenuItemImage *itemButton = CCMenuItemImage::create("m_guide_mask.png","m_guide_mask.png",this,menu_selector(guidelinesLayer::guideMenuItemCallback));
	itemButton->setPosition(m_Pos);
	m_pMenu->addChild(itemButton);


	//n_guide_human.png
	//n_guide_text_bg.png
	//n_guide_model_1.png

	string strPic = DataPool::GetSingleton()->getGuideData()->getTableData(m_iGuideID)->tipPic;
	if (strPic != "-1")
	{

		

		CCSprite *humanSprite = CCSprite::create("n_guide_human.png");
		humanSprite->setPosition(ccp(winSize.width * 0.7f , winSize.height * 0.45f));
		addChild(humanSprite);

		CCSprite *tipBgSprite = CCSprite::create("n_guide_text_bg.png");
		tipBgSprite->setPosition(ccp(winSize.width * 0.38f, winSize.height * 0.37f));
		addChild(tipBgSprite);

		char buff[256] = {0};
		sprintf(buff,"n_guide_model_%d.png",DataPool::GetSingleton()->getGuideData()->getTableData(m_iGuideID)->group);
		CCSprite *tipSprite = CCSprite::create(buff);
		tipSprite->setPosition(ccpAdd(ccp(0,-tipBgSprite->getContentSize().height * 0.1f),tipBgSprite->getPosition()));
		addChild(tipSprite);


		if (m_iGuideID == 15) //升级英雄
		{

			humanSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.15),humanSprite->getPosition()));
			tipBgSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.15),tipBgSprite->getPosition()));
			tipSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.15),tipSprite->getPosition()));
		}
		else if(m_iGuideID == 20) // 升级技能
		{
			humanSprite->setFlipX(true);
			tipBgSprite->setFlipX(true);
			humanSprite->setPosition(ccpAdd(ccp(winSize.height * -0.26,winSize.height * 0.22),humanSprite->getPosition()));
			tipBgSprite->setPosition(ccpAdd(ccp(winSize.height * 0.2,winSize.height * 0.22),tipBgSprite->getPosition()));
			tipSprite->setPosition(ccpAdd(ccp(winSize.height * 0.2,winSize.height * 0.22),tipSprite->getPosition()));
		}
		else if (m_iGuideID == 31||m_iGuideID == 30||m_iGuideID == 33) // 献祭||奶酪||负重
		{
			humanSprite->setFlipX(true);
			tipBgSprite->setFlipX(true);
			humanSprite->setPosition(ccpAdd(ccp(winSize.height * -0.26,0),humanSprite->getPosition()));
			tipBgSprite->setPosition(ccpAdd(ccp(winSize.height * 0.2,0),tipBgSprite->getPosition()));
			tipSprite->setPosition(ccpAdd(ccp(winSize.height * 0.2,0),tipSprite->getPosition()));
		}
		else if (m_iGuideID == 34) // 单排
		{
			humanSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.17),humanSprite->getPosition()));
			tipBgSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.17),tipBgSprite->getPosition()));
			tipSprite->setPosition(ccpAdd(ccp(0,winSize.height * 0.17),tipSprite->getPosition()));
		}
		

	}
	
	glDirection(gl);


}

void guidelinesLayer::glDirection(GUIDEDIRECTION gl)
{

		//n_guide_direction.png
	CCSprite *glDir = CCSprite::create("n_guide_direction.png");
	CCPoint srcPos ;
	CCPoint desPos ;

	switch (gl)
	{
	case GL_DIRECTION_LEFT:
		glDir->setRotation(-90);
		srcPos = ccpAdd(ccp(-glDir->getContentSize().width*1.2,-glDir->getContentSize().height*0.005f),m_Pos );
		desPos = ccpAdd(ccp(-glDir->getContentSize().width,-glDir->getContentSize().height* 0.005f),m_Pos);
		break;
	case GL_DIRECTION_TOP:
		srcPos = ccpAdd(ccp(0,glDir->getContentSize().height),m_Pos);
		desPos = ccpAdd(ccp(0,glDir->getContentSize().height * 0.85f),m_Pos);
		break;
	case GL_DIRECTION_RIGHT:
		glDir->setRotation(90);
		srcPos = ccpAdd(ccp(glDir->getContentSize().width * 1.2f,-glDir->getContentSize().height * 0.005f),m_Pos);
		desPos = ccpAdd(ccp(glDir->getContentSize().width ,-glDir->getContentSize().height * 0.005f),m_Pos);
		break;
	case GL_DIRECTION_BOTTOM:
		glDir->setRotation(180);
		srcPos = ccpAdd(ccp(0,-glDir->getContentSize().height),m_Pos);
		desPos = ccpAdd(ccp(0,-glDir->getContentSize().height * 0.85f),m_Pos);
		break;
	default:
		break;
	}

	addChild(glDir);

	if(m_bAnimate)
	{
		glDir->setPosition(srcPos);

		CCMoveTo *desMove = CCMoveTo::create(0.5f,desPos);
		CCMoveTo *srcMove = CCMoveTo::create(0.5f,srcPos);
		CCActionInterval *action = CCRepeatForever::create(CCSequence::create(desMove,srcMove ,NULL));
		glDir->runAction(action);
	}
	else
	{
		glDir->setPosition(desPos);
	}
}

void guidelinesLayer::setGuidePos(CCPoint pos)
{
	m_Pos = pos;

	removeAllChildrenWithCleanup(true);
	int dir = DataPool::GetSingleton()->getGuideData()->getTableData(m_iGuideID)->direction;
	initLayer((GUIDEDIRECTION)dir);
	
}

CCPoint guidelinesLayer::getGuidePos()
{
	return m_Pos;
}

bool guidelinesLayer::initGuideLayer(int guideID,CCObject* target, SEL_MenuHandler selector,CCNode *sender, bool animate)
{

		m_iGuideID = guideID;
		m_pListener = target;
		m_pMenuHandler = selector;

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float offsetX = DataPool::GetSingleton()->getGuideData()->getTableData(guideID)->offsetX;
		float offsetY = DataPool::GetSingleton()->getGuideData()->getTableData(guideID)->offsetY;
		int dir = DataPool::GetSingleton()->getGuideData()->getTableData(guideID)->direction;

		m_Pos = ccp(winSize.width * offsetX,winSize.height * offsetY);
		m_pSender = sender;
		m_bAnimate = animate;

		initLayer((GUIDEDIRECTION)dir);

		m_layerUserData = NULL;

		return true;

	
}

guidelinesLayer *guidelinesLayer::createLayer(int guideID,CCObject* target, SEL_MenuHandler selector, CCNode *sender,bool animate)
{
	guidelinesLayer *pLayer = new guidelinesLayer();

	if (pLayer && pLayer->initGuideLayer(guideID,target,selector,sender,animate) && guideID != -1)
	{
		pLayer->autorelease();
		return pLayer;
	}
	
	CC_SAFE_DELETE(pLayer);
	return NULL;
}



guidelinesLayer *guidelinesLayer::createLayer(int guideID,CCObject* target, bool animate )
{

	guidelinesLayer *pLayer = new guidelinesLayer();
	if (pLayer && pLayer->initGuideLayer(guideID,target,NULL,NULL,animate) && guideID != -1)
	{
		pLayer->autorelease();
		return pLayer;
	}

	CC_SAFE_DELETE(pLayer);
	return NULL;

}

void guidelinesLayer::onEnter()
{
	BaseView::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void guidelinesLayer::onExit()
{
  	BaseView::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool guidelinesLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
 	m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);

	return true;
}

void guidelinesLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchMoved(pTouch, pEvent);
	}
}

void guidelinesLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}

void guidelinesLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (m_bTouchedMenu) {
		m_pMenu->ccTouchEnded(pTouch, pEvent);
		m_bTouchedMenu = false;
	}
}



void guidelinesLayer::guideMenuItemCallback(cocos2d::CCObject *pSender)
{
 	if (m_pListener && m_pMenuHandler)
 	{
		(m_pListener->*m_pMenuHandler)(m_pSender);
 	}

	if (( UI *)(((BaseView *)m_pListener)))
	{
		if ((( UI *)(((BaseView *)m_pListener)->getUserData())))
		{
			(( UI *)(((BaseView *)m_pListener)->getUserData()))->setTipId(-1);
		}
	}

	stopAllActions();
	this->removeFromParentAndCleanup(true);
	DataPool::GetSingleton()->getGuideData()->HandleTip();
}





#include "gameIntroduceLayer.h"
#include "./base/UtilTools.h"
#include "./datapool/DataPool.h"
#include "./datapool/GuideData.h"
#include "./ui/ui.h"
#include "./ui/SceneManger.h"
#include "./game/MainGame.h"

#define SCREEN_SIZE CCDirector::sharedDirector()->getWinSize()
#define SCALE_X  SCREEN_SIZE.width / 640

static int pageNum = 0;

gameIntroduceLayer::gameIntroduceLayer()
{
}

gameIntroduceLayer::~gameIntroduceLayer()
{

}

void gameIntroduceLayer::jumpCallBack(cocos2d::CCObject* pSender)
{
	CCLOG("click to jump out introduce!");
	removeFromParentAndCleanup(true);
	MainGame::GetSingleton()->SetGameMainProState(MainGame::RUING_IN_SELECTPLAYER);
}

bool gameIntroduceLayer::initLayer()
{
	//TODO 
	string pic1 = "gi_page_1";
	string pic2 = "gi_page_2";
	string pic3 = "gi_page_3";
	switch (SceneManger::GetSingleton()->getResolutionType())
	{
	case EM_DEVICE_RESOLUTION_640X1136:
		pic1 += "-ip5";
		pic2 += "-ip5";
		pic3 += "-ip5";
		break;
	case EM_DEVICE_RESOLUTION_640X960:
		break;
	case EM_DEVICE_RESOLUTION_768X1024:
	case EM_DEVICE_RESOLUTION_1536X2048:
		pic1 += "-ipad";
		pic2 += "-ipad";
		pic3 += "-ipad";
		break;
	}
	 
	pic1 += ".jpg";
	pic2 += ".jpg";
	pic3 += ".jpg";

	sprite1 = CCSprite::create(pic1.c_str());
	sprite1->setAnchorPoint(CCPointZero);
	sprite1->setPosition(getPosition());
	addChild(sprite1);

	sprite2 = CCSprite::create(pic2.c_str());
	sprite2->setAnchorPoint(CCPointZero);
	sprite2->setPosition(getPosition());
	addChild(sprite2);

	sprite3 = CCSprite::create(pic3.c_str());
	sprite3->setAnchorPoint(CCPointZero);
	sprite3->setPosition(getPosition());
	addChild(sprite3);

	sprite2->setVisible(false);
	sprite3->setVisible(false);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCMenu *jumpMenu = CCMenu::create();
	CCMenuItemImage *jumpItem = CCMenuItemImage::create("battle_break.png","battle_break.png","battle_break.png",this,menu_selector(gameIntroduceLayer::jumpCallBack));
	jumpItem->setScale(SCALE_X * 1.5f);
	jumpMenu->addChild(jumpItem);

	jumpMenu->setContentSize(jumpItem->getContentSize());
	jumpMenu->setPosition(winSize.width - jumpMenu->getContentSize().width,jumpMenu->getContentSize().height);
	addChild(jumpMenu);
    jumpMenu->setZOrder(20);

	return true;

}

gameIntroduceLayer *gameIntroduceLayer::createLayer()
{
	gameIntroduceLayer *pLayer = new gameIntroduceLayer();

	if (pLayer && pLayer->initLayer())
	{
		pLayer->setTouchEnabled(false);

		pLayer->autorelease();
		return pLayer;
	}
	
	CC_SAFE_DELETE(pLayer);
	return NULL;
}

void gameIntroduceLayer::playIntroduce()
{
	
	//schedule(schedule_selector(gameIntroduceLayer::upadataLyaer),1.0f);


	scheduleOnce(schedule_selector(gameIntroduceLayer::startAction),2);
		
}

void gameIntroduceLayer::startAction(float dt)
{
    pageNum = 0;

	CCFiniteTimeAction *actionF = CCCallFuncND::create(this,SEL_CallFuncND(&gameIntroduceLayer::actionEnd),NULL);

	//begin 1
	CCActionInterval *action1 = CCSequence::create(CCDelayTime::create(7.0f),CCFadeOut::create(2.0f),actionF,NULL);
	sprite1->runAction(action1);

	//text
	createText(5,1);

	CCActionInterval *action2 = CCSequence::create(CCDelayTime::create(17.0f),CCShow::create(),CCFadeIn::create(2.0f),CCDelayTime::create(7.0f),CCFadeOut::create(2.0f),actionF,NULL);
	sprite2->runAction(action2);

	//text
	createText(3,2);

	CCActionInterval *action3 = CCSequence::create(CCDelayTime::create(29.0f),CCShow::create(),CCFadeIn::create(2.0f),CCDelayTime::create(9.0f),CCFadeOut::create(2.0f),actionF,NULL);
	sprite3->runAction(action3);

	//text
	createText(3,3);
}

void gameIntroduceLayer::upadataLyaer(float dt)
{
	// static int a = 0;
	// CCLOG("---------------%d",++a );
	 
}

void gameIntroduceLayer::createText(int num, int index)
{
	int min = 1;
	int textIndex = 0;
	switch (index)
	{
	case 1:
		textIndex = 620;
		break;
	case 2:
		min = 17;
		textIndex = 625;
		break;
	case 3:
		min = 29;
		textIndex = 628;
		break;
	default:
		break;
	}

	CCArray *array1 = CCArray::createWithCapacity(num);
	array1->retain();
	for (int i = 0 ; i < num ; i ++)
	{
		
		//CCLabelTTF *label1 = CCLabelTTF::create(UtilTools::GET_TEXT_FROM_LANG(textIndex + i),FONT_NAME_ARIAL_BOLD,27);

		LabelTTFFont *label1 = LabelTTFFont::create(UtilTools::GET_TEXT_FROM_LANG(textIndex + i),FONT_NAME_ARIAL_BOLD,27,1,ccc3(0,0,0));
		label1->setAnchorPoint(ccp(0.5,0.5));
		label1->setPosition(ccp(SCREEN_SIZE.width * 0.5f , SCREEN_SIZE.height * (0.92f - i * 0.055f)));
		
		//255 255 255 外发光颜色 255 0 0

		addChild(label1);
		ccColor3B color3 = {255 ,240 ,158};
		label1->setColor(color3);
		label1->setVisible(false);
		array1->addObject(label1);

		
		float beginDelay = 3.0f;
		if (index == 3) {beginDelay = 4.0f;}
		float endDelay = 5.0f;
	
		if (i == num - 1)
		{
			if (index == 1)
			{
				label1->setFontSize(60);
				label1->setPosition(ccp(SCREEN_SIZE.width * 0.5f , SCREEN_SIZE.height * (0.92f - i * 0.065f)));
				label1->setString(UtilTools::GET_TEXT_FROM_LANG(textIndex + i));
				endDelay = 3.0f;

			}
			
			CCFiniteTimeAction *actionF = CCCallFuncND::create(this,SEL_CallFuncND(&gameIntroduceLayer::actionEnd),(void *)array1);
			label1->runAction(CCSequence::create(CCDelayTime::create(min + i*beginDelay),CCShow::create(),CCFadeIn::create(0.5f),CCDelayTime::create(endDelay),actionF,NULL));


		}
		else
		{
			label1->runAction(CCSequence::create(CCDelayTime::create(min + i*beginDelay),CCShow::create(),CCFadeIn::create(0.5f),NULL));
		}
	}
}

void gameIntroduceLayer::actionEnd(CCNode *pSender , void *pObj)
{
	if (pObj == NULL)
	{
		pageNum ++ ;
		pSender->removeFromParentAndCleanup(true);
		pSender = NULL;
	}
	else
	{
		CCArray *arrayItems = (CCArray *)pObj;
		for (unsigned int i = 0; i < arrayItems->count(); i ++)
		{
			((CCNode *)arrayItems->objectAtIndex(i))->removeFromParentAndCleanup(true);
		}

		arrayItems->release();
	}
	 CCLOG("---------------%d",pageNum );
    CCLog("getChildrenCount == --------------%d",getChildrenCount() );
	if (getChildrenCount() <= 1 && pageNum %3 == 0 && pageNum >= 3)
	{
		removeFromParentAndCleanup(true);
		//TODO: go main 
		MainGame::GetSingleton()->SetGameMainProState(MainGame::RUING_IN_SELECTPLAYER);
	}
	

}

 void gameIntroduceLayer::onEnter()
 {
	BaseView::onEnter();
 }

void gameIntroduceLayer::onExit()
{
	BaseView::onExit();
}


LabelTTFFont::LabelTTFFont()
	:m_colStroke(ccc3(0,0,0))
	,m_fStrokeSize(1.0f)
	,m_sprite(NULL)
	,m_label(NULL)
{}
LabelTTFFont::~LabelTTFFont()
{
	CC_SAFE_RELEASE_NULL(m_label);
}
bool LabelTTFFont::initWithString(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::ccColor3B& colStroke, CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	m_fStrokeSize = strokeSize;
	m_colStroke = colStroke;
	m_label = CCLabelTTF::create(string, fontName, fontSize, CCSizeZero,hAlignment,vAlignment);
	m_label->retain();

	updateStroke();

	return true;
}
LabelTTFFont* LabelTTFFont::create(const char *string, const char *fontName, float fontSize, float fStrokeSize,const cocos2d::ccColor3B& colStroke ,CCTextAlignment hAlignment,CCVerticalTextAlignment vAlignment)
{
	LabelTTFFont *pRet = new LabelTTFFont();
	if(pRet && pRet->initWithString(string, fontName, fontSize, fStrokeSize, colStroke, hAlignment, vAlignment))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}
void LabelTTFFont::updateStroke()
{
	if (m_sprite)
	{
		removeChild(m_sprite, true);
	}


	CCSize textureSize = m_label->getContentSize();
	textureSize.width += 2 * m_fStrokeSize;
	textureSize.height += 2 * m_fStrokeSize;
	//call to clear error
	glGetError();
	CCRenderTexture *rt = CCRenderTexture::create(textureSize.width, textureSize.height);
	if(!rt)
	{
		CCLOG("create render texture failed !!!!");
		addChild(m_label);
		return;
	}

	

	ccColor3B col = m_label->getColor();
	m_label->setColor(m_colStroke);

	ccBlendFunc originalBlend = m_label->getBlendFunc();
	ccBlendFunc func = { GL_SRC_ALPHA, GL_ONE};
	m_label->setBlendFunc(func);

	m_label->setAnchorPoint(ccp(0.5, 0.5));

	rt->begin();
	for(int i = 0; i < 360; i += 15)
	{
		float r = CC_DEGREES_TO_RADIANS(i);
		m_label->setPosition(ccp(
			textureSize.width * 0.5f + sin(r) * m_fStrokeSize,
			textureSize.height * 0.5f + cos(r) * m_fStrokeSize));
		m_label->visit();
	}

	m_label->setColor(col);
	m_label->setBlendFunc(originalBlend);
	m_label->setPosition(ccp(textureSize.width * 0.5f, textureSize.height * 0.5f));
	m_label->visit();
	rt->end();

	CCTexture2D *texture = rt->getSprite()->getTexture();
	texture->setAliasTexParameters();
	m_sprite = CCSprite::createWithTexture(rt->getSprite()->getTexture());
	setContentSize(m_sprite->getContentSize());
	m_sprite->setAnchorPoint(ccp(0, 0));
	m_sprite->setPosition(ccp(0, 0));
	((CCSprite *)m_sprite)->setFlipY(true);
	addChild(m_sprite);
}
void LabelTTFFont::setString(const char *label)
{
	if (m_label)
	{
		if(0!=strcmp(label, m_label->getString()))
		{
			m_label->setString(label);
			updateStroke();
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setString m_label=NULL");
	}
}
void LabelTTFFont::setColor(const ccColor3B& color3)
{
	if (m_label)
	{
		ccColor3B col = m_label->getColor();
		if(color3.r!=col.r || color3.g!=col.g || color3.b!=col.b)
		{
			m_label->setColor(color3);
			updateStroke();
		}
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setColor m_label=NULL");
	}
}

void LabelTTFFont::setFontSize(float fontSize)
{
	if (m_label)
	{
		
		m_label->setFontSize(fontSize);
		updateStroke();
		
	}
	else
	{
		CCLOG("ERROR:CCLabelTTFStroke::setString m_label=NULL");
	}
}

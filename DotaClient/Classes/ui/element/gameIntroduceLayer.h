#ifndef __GAMEINTRODUCELAYER_H__
#define __GAMEINTRODUCELAYER_H__

#include "cocos2d.h"
#include "./ui/baseview.h"
#include "cocos-ext.h"
USING_NS_CC;

class gameIntroduceLayer: public BaseView
{
public:
	gameIntroduceLayer();
	virtual ~gameIntroduceLayer();

	virtual void onEnter();
	virtual void onExit();

	inline void setLayerUserData(void* pUserData)
    {
        m_layerUserData = pUserData;
    };

    inline void* getLayerUserData()
    {
        return m_layerUserData;
    };


	bool initLayer();
	static gameIntroduceLayer *createLayer();
	void upadataLyaer(float dt);
	void createText(int num, int index);
	void actionEnd(CCNode *pSender , void *pObj);
	void playIntroduce();
	void startAction(float dt);

	void jumpCallBack(cocos2d::CCObject* pSender);
private:

	void *m_layerUserData;
	cocos2d::CCArray *spriteItems;

	CCSprite *sprite1;
	CCSprite *sprite2;
	CCSprite *sprite3;

};

class LabelTTFFont : public cocos2d::CCNode
{
public:
	LabelTTFFont();
	~LabelTTFFont();

public:
	static LabelTTFFont* create(const char *string, const char *fontName, float fontSize, float strokeSize,const cocos2d::ccColor3B&      colStroke = cocos2d::ccc3(0, 0, 0), cocos2d::CCTextAlignment hAlignment=cocos2d::kCCTextAlignmentCenter, cocos2d::CCVerticalTextAlignment vAlignment=cocos2d::kCCVerticalTextAlignmentTop);
	bool initWithString(const char *label, const char *fontName, float fontSize, float fStrokeSize, const cocos2d::ccColor3B&      colStroke, cocos2d::CCTextAlignment hAlignment, cocos2d::CCVerticalTextAlignment vAlignment);

public:
	void setColor(const cocos2d::ccColor3B& color3);
	void setString(const char *label);
	void setStrokeColor(cocos2d::ccColor3B col){ m_colStroke = col; updateStroke(); }
	void setStrokeSize(float StrokeSize){ m_fStrokeSize = StrokeSize; updateStroke();}
	void setFontSize(float fontSize);
protected:
	void updateStroke();

private:
	float                   m_fStrokeSize;
	cocos2d::ccColor3B      m_colStroke;
	cocos2d::CCSprite*      m_sprite;
	cocos2d::CCLabelTTF*    m_label;
	
};



#endif
#ifndef __TIPVIEW_SCENE_H__
#define __TIPVIEW_SCENE_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./ui/TipUi.h"
#include <vector>
#include <string>
using namespace std;
using namespace cocos2d;

USING_NS_CC_EXT;
class TipView : public BaseView
{
public:

	virtual bool init();  
	CREATE_FUNC(TipView);
	void  onDataUpdate(const vector<string>& tips);
	 virtual void onExit();
 
protected:
	CCLabelTTF * m_text;

 	virtual void autoDel(float dt );
    void showTip();
private:
	CCSprite *tipBg;
    vector<string> m_cache;
    vector<bool> m_bconnectcache;
	CCSprite * tipConnect;
};

#endif
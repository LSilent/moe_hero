#ifndef __NOTICEUI_VIEW_H__
#define __NOTICEUI_VIEW_H__

#include "./ui/baseview.h"
#include "cocos-ext.h"
#include "./ui/NoticeUi.h"

USING_NS_CC;

class NoticeView : public BaseView
{
public:

	virtual bool init();  
	CREATE_FUNC(NoticeView);
	void  onDataUpdate(const vector<string>& tips);
	virtual void onExit();
	bool getIsRolling();
	void stopRollNotice();
	
protected:
	CCLabelTTF * m_text;

	virtual void autoRoll(float dt );
	string str;
	vector<string > mNotices;

	bool isRolling;
};

#endif
#ifndef __NOTICEUI_H__
#define __NOTICEUI_H__
#include "./ui/ui.h"

class NoticeUi :public UI
{
public:
	NoticeUi();
	virtual ~NoticeUi();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
    virtual   X_VOID   UpData();

	 std::vector<string> m_tips;
};
#endif
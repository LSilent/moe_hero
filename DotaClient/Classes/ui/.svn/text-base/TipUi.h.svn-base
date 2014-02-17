#ifndef __TIPUI_H__
#define __TIPUI_H__
#include "./ui/ui.h"

class TipUi :public UI
{
public:
	TipUi();
	virtual ~TipUi();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
    virtual   X_VOID   UpData();

	 std::vector<string> m_tips;
};
#endif
#ifndef __USERINFOUI_H__
#define __USERINFOUI_H__
#include "./ui/ui.h"

class userInfoUI :public UI
{
public:
	userInfoUI();
	virtual ~userInfoUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
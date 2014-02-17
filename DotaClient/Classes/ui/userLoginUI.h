#ifndef __USERLOGINUI_H__
#define __USERLOGINUI_H__
#include "./ui/ui.h"

class userLoginUI :public UI
{
public:
	userLoginUI();
	virtual ~userLoginUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
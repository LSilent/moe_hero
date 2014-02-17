#ifndef __loginUi_h__
#define __loginUi_h__
#include "./ui/ui.h"

class loginUi :public UI
{
public:
	loginUi();
	virtual ~loginUi();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
public:
	X_VOID	  onEnterClick();
 
};
#endif
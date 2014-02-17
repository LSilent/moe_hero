#ifndef __USER_UPGRADE_UI_H__
#define __USER_UPGRADE_UI_H__

#include "./ui/ui.h"

class UserUpgradeUI :public UI
{
public:
	UserUpgradeUI();
	virtual ~UserUpgradeUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
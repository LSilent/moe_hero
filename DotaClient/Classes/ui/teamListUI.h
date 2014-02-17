#ifndef __TEAM_LIST_UI_H__
#define __TEAM_LIST_UI_H__
#include "./ui/ui.h"

class TeamListUI :public UI
{
public:
	TeamListUI();
	virtual ~TeamListUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
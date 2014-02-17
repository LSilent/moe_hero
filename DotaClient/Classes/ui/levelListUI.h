#ifndef __LEVEL_LIST_UI_H__
#define __LEVEL_LIST_UI_H__
#include "./ui/ui.h"

class LevelListUI :public UI
{
public:
	LevelListUI();
	virtual ~LevelListUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
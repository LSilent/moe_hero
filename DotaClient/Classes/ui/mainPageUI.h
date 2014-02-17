#ifndef __MAIN_SCENE_UI_H__
#define __MAIN_SCENE_UI_H__
#include "./ui/ui.h"

class MainPageUI :public UI
{
public:
	MainPageUI();
	virtual ~MainPageUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
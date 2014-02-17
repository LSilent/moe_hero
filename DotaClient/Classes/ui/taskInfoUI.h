#ifndef __TASKINFOUI_H__
#define __TASKINFOUI_H__
#include "./ui/ui.h"

class taskInfoUI :public UI
{
public:
	taskInfoUI();
	virtual ~taskInfoUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
#ifndef __PLACARD_UI_H__
#define __PLACARD_UI_H__
#include "./ui/ui.h"

class placardUI :public UI
{
public:
	placardUI();
	virtual ~placardUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
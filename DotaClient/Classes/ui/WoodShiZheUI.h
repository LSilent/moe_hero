#ifndef __WOODSHIZHEUI_H__
#define __WOODSHIZHEUI_H__

#include "./ui/ui.h"

class WoodShiZheUI :public UI
{
public:
	WoodShiZheUI();
	virtual ~WoodShiZheUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
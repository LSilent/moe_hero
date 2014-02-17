#ifndef __FIGHT_RESULT_UI_H__
#define __FIGHT_RESULT_UI_H__
#include "./ui/ui.h"

class FightResultUI :public UI
{
public:
	FightResultUI();
	virtual ~FightResultUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
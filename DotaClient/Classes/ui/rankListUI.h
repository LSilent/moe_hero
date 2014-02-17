#ifndef __RANKLIST_UI_H__
#define __RANKLIST_UI_H__
#include "./ui/ui.h"

class RankListUI :public UI
{
public:
	RankListUI();
	virtual ~RankListUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
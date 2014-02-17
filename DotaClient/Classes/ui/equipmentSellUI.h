#ifndef __EQUIPMENTSELLUI_H__
#define __EQUIPMENTSELLUI_H__
#include "./ui/ui.h"

class equipmentSellUI :public UI
{
public:
	equipmentSellUI();
	virtual ~equipmentSellUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();

	X_VOID				UpData();	
};
#endif
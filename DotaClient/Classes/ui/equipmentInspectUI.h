#ifndef __EQUIPMENT_INSPECT_UI_H__
#define __EQUIPMENT_INSPECT_UI_H__
#include "./ui/ui.h"

class EquipmentInspectUI :public UI
{
public:
	EquipmentInspectUI();
	virtual ~EquipmentInspectUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
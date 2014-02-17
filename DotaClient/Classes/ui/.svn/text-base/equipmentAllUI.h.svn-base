#ifndef __EQUIPMENT_ALL_UI_H__
#define __EQUIPMENT_ALL_UI_H__
#include "./ui/ui.h"

class EquipmentAllUI :public UI
{
public:
	EquipmentAllUI();
	virtual ~EquipmentAllUI();


	X_INT    nTablePage;//0-3 普通 材料 终极装备
	X_INT    nPage;//分页里面的页面
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
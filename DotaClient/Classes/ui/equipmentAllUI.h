#ifndef __EQUIPMENT_ALL_UI_H__
#define __EQUIPMENT_ALL_UI_H__
#include "./ui/ui.h"

class EquipmentAllUI :public UI
{
public:
	EquipmentAllUI();
	virtual ~EquipmentAllUI();


	X_INT    nTablePage;//0-3 ��ͨ ���� �ռ�װ��
	X_INT    nPage;//��ҳ�����ҳ��
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
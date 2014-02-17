#ifndef __ESCORTWOOD_UI_H__
#define __ESCORTWOOD_UI_H__

#include "./ui/ui.h"

class EscortWoodUI :public UI
{
public:
	EscortWoodUI();
	virtual ~EscortWoodUI();
	bool m_bShowBuzhen;
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
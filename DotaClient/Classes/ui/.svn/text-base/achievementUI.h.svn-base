#ifndef __ACHIEVEMENTUI_H__
#define __ACHIEVEMENTUI_H__
#include "./ui/ui.h"

class achievementUI :public UI
{
public:
	achievementUI();
	virtual ~achievementUI();

 
	X_INT   m_layer;// -1表示主界面
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
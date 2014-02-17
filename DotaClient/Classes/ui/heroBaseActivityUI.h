#ifndef __HEROBASEACTIVITYUI_H__
#define __HEROBASEACTIVITYUI_H__
#include "./ui/ui.h"

class heroBaseActivityUI :public UI
{
public:
	heroBaseActivityUI();
	virtual ~heroBaseActivityUI();

	enum
	{
		EM_LAYER_INVALLID = -1,
		EM_SELFWOOD_LAYER_SHOW ,
		EM_ROBWOOD_LAYER_SHOW,
		EM_REVENGEWOOD_LAYER_SHOW,
		EM_LAYER_NUM
	};
public:
	X_INT    m_ShowLayer;
	X_INT    m_BuilderIndex;

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
#ifndef __SKILLUPGRADEEQUIUI_H__
#define __SKILLUPGRADEEQUIUI_H__
#include "./ui/ui.h"

class SkillUpgradeEquiUI :public UI
{
public:
	SkillUpgradeEquiUI();
	virtual ~SkillUpgradeEquiUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();

	X_VOID				UpData();	
};
#endif
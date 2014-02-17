#ifndef __HERO_UPGRADE_UI_H__
#define __HERO_UPGRADE_UI_H__
#include "./ui/ui.h"

class HeroUpgradeUI :public UI
{
public:
	HeroUpgradeUI();
	virtual ~HeroUpgradeUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
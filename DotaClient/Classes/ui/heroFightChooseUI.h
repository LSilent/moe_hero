#ifndef __HERO_FIGHT_CHOOSE_UI_H__
#define __HERO_FIGHT_CHOOSE_UI_H__
#include "./ui/ui.h"

class HeroFightChooseUI :public UI
{
public:
	HeroFightChooseUI();
	virtual ~HeroFightChooseUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
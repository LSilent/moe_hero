#ifndef __HERO_RECRUIT_UI_H__
#define __HERO_RECRUIT_UI_H__
#include "./ui/ui.h"

class HeroRecruitUI :public UI
{
public:
	HeroRecruitUI();
	virtual ~HeroRecruitUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();		
};
#endif
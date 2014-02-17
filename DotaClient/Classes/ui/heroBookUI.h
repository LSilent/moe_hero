#ifndef __HERO_BOOK_UI_H__
#define __HERO_BOOK_UI_H__
#include "./ui/ui.h"

class HeroBookUI :public UI
{
public:
	HeroBookUI();
	virtual ~HeroBookUI();
	X_INT    nPage;//·ÖÒ³
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
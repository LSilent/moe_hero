#ifndef __LOGOUI_H__
#define __LOGOUI_H__
#include "./ui/ui.h"

class logoUi :public UI
{
public:
	logoUi();
	virtual ~logoUi();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	virtual   X_VOID	OnShow();
public:

	X_VOID	connectServer();
};
#endif
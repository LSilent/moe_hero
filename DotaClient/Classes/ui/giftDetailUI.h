#ifndef __GIFTDETAIL_UI_H__
#define __GIFTDETAIL_UI_H__
#include "./ui/ui.h"

class giftDetailUI :public UI
{
public:
	giftDetailUI();
	virtual ~giftDetailUI();
	X_INT giftId;
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID	UpData();	
};
#endif
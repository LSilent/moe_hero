#ifndef __BAG_OWN_UI_H__
#define __BAG_OWN_UI_H__
#include "./ui/ui.h"

class BagOwnUI :public UI
{
public:
	BagOwnUI();
	virtual ~BagOwnUI();
	X_INT    nPage;//分页里面的页面
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
	X_VOID				getTip();
};
#endif
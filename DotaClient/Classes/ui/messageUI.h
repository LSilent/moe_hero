#ifndef __MESSAGE_UI_H__
#define __MESSAGE_UI_H__
#include "./ui/ui.h"

class MessageUI :public UI
{
public:
	MessageUI();
	virtual ~MessageUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual   X_VOID				UpData();	
};
#endif
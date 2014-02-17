#ifndef __SKILL_INSPECT_UI_H__
#define __SKILL_INSPECT_UI_H__
#include "./ui/ui.h"

class SkillInspectUI :public UI
{
public:
	SkillInspectUI();
	virtual ~SkillInspectUI();

protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	X_VOID				UpData();	
};
#endif
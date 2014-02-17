#ifndef __CHEESEACTIVITYUI_H__
#define __CHEESEACTIVITYUI_H__
#include "./ui/ui.h"

enum EM_XUEZHAN_LAYER
{
	EM_LAYER_INVALLID = -1,
	EM_XUEZHAN_ENTER_LAYER_SHOW ,
	EM_XUEZHAN_BUFFER_LAYER_SHOW ,
	EM_XUEZHAN_BATTLE_LAYER_SHOW ,
	EM_LAYER_NUM
};
enum EM_SHAKE_LAYER
{
	EM_SHAKE_LAYER_INVALLID = -1,
	EM_SHAKE_INTRODUCE_LAYER_SHOW,
	EM_SHAKE_ENTER_LAYER_SHOW ,
	EM_SHAKE_WAITE_LAYER_SHOW,
	EM_SHAKE_GODDESS_LAYER_SHOW,
	EM_SHAKE_LAYER_NUM
};
class cheeseActivityUI :public UI
{
public:
	cheeseActivityUI();
	virtual ~cheeseActivityUI();



	X_INT   m_HuoDongIndex;
	EM_XUEZHAN_LAYER m_layerXueZhan;
	EM_SHAKE_LAYER m_layerShake;
protected:

	virtual   X_VOID   CareEvent();
	virtual	  X_VOID   OnGameEvent(const tGameEventData* pEvent);
	virtual   X_VOID   OnCreate();
	
	virtual	   X_VOID				UpData();	
};
#endif
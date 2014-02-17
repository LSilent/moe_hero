 
#ifndef __HEARTBEAT_DATA_H__
#define __HEARTBEAT_DATA_H__

#include "./base/Global.h"
 

class  HeartBeatData 
{
 
public:
	 
	X_VOID		Initial();
	X_VOID		Release();
	X_VOID		Tick(X_UINT nTime);
	X_VOID		CleanUp();
	X_VOID		SendHeartBeatData();
	X_VOID		ReceiveHeartBeatData(X_UINT nLogicCount);
 

private:
	X_ULLONG		m_nHeartBeatTime;			//心跳间隔时间
	X_ULLONG		m_nHeartBeatLogicCount;		//心跳逻辑计数
	X_ULLONG		m_nHeartBeatSendTime;		//心跳发送时间
	X_ULLONG		m_nHeartBeatDelayTime;		//心跳延时时间
 
};
#endif
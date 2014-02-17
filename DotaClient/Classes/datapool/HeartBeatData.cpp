#include "./datapool/HeartBeatData.h"
#include "./timer/SystemTimer.h"
#include "./game/SendPacket.h"
X_VOID HeartBeatData::Initial()
{
	CleanUp();
}


X_VOID HeartBeatData::Release()
{
	CleanUp();
}

X_VOID HeartBeatData::CleanUp()
{
	m_nHeartBeatLogicCount	= 0;
	m_nHeartBeatTime		= 10000; //60s
	m_nHeartBeatSendTime	= 0;
	m_nHeartBeatDelayTime	= 0;
} 

X_VOID HeartBeatData::Tick(X_UINT nTime)
{
 
	SystemTimer* pSystemTimer = SystemTimer::GetSingleton();
	if(pSystemTimer == X_NULL)
		return;

	X_ULLONG nNowTime = pSystemTimer->GetNowTime();
	//if(m_nHeartBeatLogicCount >= 0)
	{
		if(nNowTime > m_nHeartBeatSendTime+m_nHeartBeatTime)
		{
			SendHeartBeatData();
			m_nHeartBeatSendTime = nNowTime;
		}
	}
}

 
X_VOID HeartBeatData::SendHeartBeatData()
{ 
	 SendLogicPacket::HeartBeat();
}

 
X_VOID HeartBeatData::ReceiveHeartBeatData(X_UINT nLogicCount)
{
	SystemTimer* pSystemTimer = SystemTimer::GetSingleton();
	if(pSystemTimer == X_NULL)
		return;
	m_nHeartBeatLogicCount = nLogicCount;
	//if(m_nHeartBeatLogicCount >= 1)
	{
		m_nHeartBeatDelayTime = pSystemTimer->GetNowTime() - m_nHeartBeatSendTime;
	}
}

 
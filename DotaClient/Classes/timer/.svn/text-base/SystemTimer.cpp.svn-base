
#include "./timer/SystemTimer.h"
#include "./game/SendPacket.h"
 

IMPLEMENT_SINGLETON(SystemTimer);

SystemTimer::SystemTimer()
{
	ResetTimer();
}
SystemTimer::~SystemTimer()
{
}

X_VOID SystemTimer::Initial()
{
	ResetTimer();
    m_nTimeZone = 8;
	time_t ttime;
	time(&ttime);
	SetServerTime(ttime);
    m_tLocalTime = ttime;
	Tick(0);
}
X_VOID SystemTimer::ResetTimer()
{
	m_ZeroClock = clock();
	m_tServerTime = 0;
	m_tLocalTime  = 0;
	m_nNowTime = 0;
	m_nDeltaTime = 0;
}
X_VOID SystemTimer::Tick(X_UINT nTime)
{
	static X_ULLONG s_nOldTime = 0;
	if(s_nOldTime == 0)
	{
		s_nOldTime = m_nNowTime = GetMillisecondsCPU();
		m_nDeltaTime = 0;
		return;
	}
	m_nNowTime = GetMillisecondsCPU();
	if(m_nNowTime >= s_nOldTime)
	{
		m_nDeltaTime = (X_UINT)(m_nNowTime - s_nOldTime);
	}
	else
	{
		m_nDeltaTime = (X_UINT)(0XFFFFFFFF - s_nOldTime + m_nNowTime);
	}
	s_nOldTime = m_nNowTime;
}
 
  
X_ULLONG SystemTimer::GetMillisecondsCPU()
{
	clock_t newClock = clock();
	return (X_ULLONG)( (X_FLOAT)( newClock - m_ZeroClock ) / ( (X_FLOAT)CLOCKS_PER_SEC / 1000.0 ) ) ;
} 
 

X_ULLONG SystemTimer::GetNowTime() const
{ 
	return m_nNowTime;
}
X_UINT SystemTimer::GetDeltaTime() const
{
	return m_nDeltaTime;
}

X_VOID SystemTimer::SetServerTime(time_t tServerTime)
{
	m_tServerTime = tServerTime;
	m_tLocalTime = time(0);
}

time_t SystemTimer::GetServerTime()  
{
	if(m_tServerTime<=0)
		return 0;
	time_t tCurTime = time(0);
  
	time_t res =  m_tServerTime + tCurTime - m_tLocalTime + m_nTimeZone*SECONDS_IN_HOUR ;
 
	return res;
}

tm* SystemTimer::GetServerDate()  
{
    time_t tServerTime = GetServerTime();
    return gmtime(&tServerTime);
}
 
X_UINT SystemTimer::GetDayNumOfMonth()
{
	tm stFirstDayOfMonth = { 0 };
	tm stLastDayOfMonth = { 0 };

    if (XTRUE==GetFirstDayOfMonth(stFirstDayOfMonth) && XTRUE==GetLastDayOfMonth(stLastDayOfMonth))
    {
        return (X_UINT)(stLastDayOfMonth.tm_yday-stFirstDayOfMonth.tm_yday);
    }
    return 0;
}

X_BOOL SystemTimer::GetFirstDayOfMonth(tm &stTM)
{
    tm stFirstDayOfThisMonth;
    memcpy(&stFirstDayOfThisMonth, &stTM, sizeof(tm));
    stFirstDayOfThisMonth.tm_mday = 1;
    time_t nTime ={0}; //_mkgmtime(&stFirstDayOfThisMonth);
    tm *pTM = gmtime(&nTime);
    if (X_NULL == pTM)
    {
        return XFALSE;
    }
    memcpy(&stTM, pTM, sizeof(tm));
    return XFALSE;
     
}

X_BOOL SystemTimer::GetLastDayOfMonth(tm &stTM)
{
    tm stFirstDayOfNextMonth;
    memcpy(&stFirstDayOfNextMonth, &stTM, sizeof(tm));
    if (11 == stFirstDayOfNextMonth.tm_mon)
    {
        stFirstDayOfNextMonth.tm_year += 1;
        stFirstDayOfNextMonth.tm_mon = 0;
    }
    else
    {
        stFirstDayOfNextMonth.tm_mon += 1;
    }
    stFirstDayOfNextMonth.tm_mday = 1;
	time_t nTime ={0} ;//_mkgmtime(&stFirstDayOfNextMonth);

    nTime -= SECONDS_IN_DAY;
    tm *pTM = gmtime(&nTime);
    if (X_NULL == pTM)
    {
        return XFALSE;
    }
    memcpy(&stTM, pTM, sizeof(tm));
    return XTRUE;
}
X_UINT SystemTimer::SubTime(X_UINT nNewTime, X_UINT nOldTime)
{
	if(nNewTime >= nOldTime)
	{
		return nNewTime - nOldTime;
	}
	else
	{
		return (X_UINT)0XFFFFFFFF - nOldTime + nNewTime;
	}
}
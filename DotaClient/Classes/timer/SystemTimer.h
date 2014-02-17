
#ifndef __SYSTEMTIMER_H__
#define __SYSTEMTIMER_H__
 
#include "./base/Global.h"
#include "./base/Singleton.h"

class SystemTimer : public Singleton<SystemTimer>
{
public:
    const static X_UINT SECONDS_IN_HOUR = 3600;
    const static X_UINT SECONDS_IN_DAY = 86400;
    const static X_UINT DAYS_IN_WEEK = 7;
    const static X_UINT TM_TIME_WEEK_DAY_IN_ZERO = 7;
    const static X_UINT TM_TIME_MONTH_IN_ZERO = 1;
    const static X_UINT TM_TIME_YEAR_IN_ZERO = 1900;
public:
	SystemTimer();
	virtual ~SystemTimer();

public:
	X_VOID Initial();
	X_VOID Release() {}
	X_VOID Tick(X_UINT nTime);

	X_VOID ResetTimer();
	X_ULLONG GetMillisecondsCPU();
	 

	X_ULLONG GetNowTime() const;
	X_UINT	 GetDeltaTime() const;
	X_VOID	 SetServerTime(time_t tServerTime);
	time_t		GetServerTime()  ;
    tm*         GetServerDate()  ;
 
    
    static X_UINT GetDayNumOfMonth();
    static X_BOOL GetFirstDayOfMonth(tm &stTM);
    static X_BOOL GetLastDayOfMonth(tm &stTM);
	static X_UINT	SubTime(X_UINT nNewTime, X_UINT nOldTime);

private:
	clock_t			m_ZeroClock;	  
 
public:
    X_INT		m_nTimeZone;		
	time_t		m_tServerTime;				
	time_t		m_tLocalTime;			

	X_ULLONG	m_nNowTime;				
	X_UINT		m_nDeltaTime;			

	DECLARE_SINGLETON(SystemTimer);
};

//得到tm时间的年对应的年份
#define GetTmYear(i) (i+SystemTimer::TM_TIME_YEAR_IN_ZERO)
//得到tm时间的月对应的月
#define GetTmMonth(i) (i+SystemTimer::TM_TIME_MONTH_IN_ZERO)
//得到tm时间的星期对应的星期
#define GetTmWeekDay(i) (0==i ? 7 : i)

#endif
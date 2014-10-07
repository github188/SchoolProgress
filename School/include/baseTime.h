#ifndef BASE_TIME_H
#define BASE_TIME_H
#include <iostream>
#include <sstream>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include "baseDef.h"
using namespace std;

#define ONE_SEC (1000)
#define HALF_SEC (500)
#define ONE_MIN (60000)
#define HALF_MIN (30000)
#define ONE_HOUR (3600000)
#define HALF_HOUR (1800000)
#define ONE_DAY (86400000)
#define HALF_DAY (43200000)
#define ONE_WEEK (604800000)
#define FOREVER (4294967294)
typedef struct{
WORD wYear;
WORD wMonth;
WORD wDay;
WORD wHour;
WORD wMinute;
WORD wSecond;
}SYSTEMTIME;

void TM_SYSTEMTIME( struct tm* pTM, SYSTEMTIME *pST);

bool TIME_T_SYSTEMTIME( time_t ltime,SYSTEMTIME *pST );

bool getSystemTime( SYSTEMTIME *pST );

class RTime
{
	private:
		QWORD _msecs;  //毫秒
		QWORD _now()
		{
			QWORD retval = 0LL;
			struct timeval tv;
			gettimeofday(&tv,NULL);
			retval = tv.tv_sec;
			retval *= 1000;
			retval += tv.tv_usec / 1000;
			return retval;
		}
		//延时delay毫秒
		void nowByDelay(int delay)
		{
			_msecs = _now();
			addDelay(delay);
		}
	public:
		RTime(const int delay)
		{
			nowByDelay(delay);
		}
		RTime(const RTime & _time)
		{
			_msecs = _time.msecs();
		}
		void now()
		{
			_msecs = _now();
		}
		DWORD sec() const
		{
			return _msecs / 1000;
		}
		DWORD msec() const
		{
			return _msecs % 1000;
		}
		QWORD msecs() const
		{
			return _msecs;
		}
		void setmsecs(QWORD _data)
		{
			_msecs = _data;
		}
		void addDelay(int delay)
		{
			_msecs += delay;
		}
		RTime& operator= (const RTime& rt)
		{
			_msecs = rt.msecs();
			return *this;
		}
		const RTime& operator+ (const RTime &rt)
		{
			_msecs += rt.msecs();
			return *this;
		}
		const RTime& operator- (const RTime &rt)
		{
			_msecs -= rt.msecs();
			return *this;
		}
		bool operator> (const RTime &rt)
		{
			return _msecs > rt.msecs();
		}
		bool operator >= (const RTime &rt)
		{
			return _msecs >= rt.msecs();
		}
		bool operator < (const RTime &rt)
		{
			return _msecs < rt.msecs();
		}
		bool operator <= (const RTime &rt)
		{
			return _msecs <= rt.msecs();
		}
		bool operator == (const RTime &rt)
		{
			return _msecs == rt.msecs();
		}
		QWORD elapse(const RTime &rt)
		{
			if(rt.msecs() > _msecs)
			{
				return rt.msecs() - _msecs;
			}
			return 0LL;
		}

		static void getLocalTime(struct tm &tv,time_t timeValue)
		{
			timeValue += 8 * 60 * 60;
			tv = *localtime(&timeValue);
		}

};
class Time
{
	public:
		friend class Clocker;
		static SQWORD my_timezone;
		static SQWORD my_timesync;
	public:
		Time()
		{
			now();
		}
		Time(const Time &rt)
		{
			_ts = rt._ts;
			_msec = rt._msec;
			_tm_ok = false;
		}
		void now()
		{
			clock_gettime(CLOCK_REALTIME,&_ts);
			_msec = sec() * 1000L + _ts.tv_nsec / 1000000L;
			_tm_ok = false;
		}
		inline QWORD sec() const
		{
			tzset();
			return _ts.tv_sec - my_timezone - my_timesync;
		}
		inline QWORD msec() const
		{
			return _msec;
		}
		inline QWORD usec() const
		{
			return sec() * 1000L + _ts.tv_nsec / 1000L;
		}
		inline void addDelay(const QWORD delay)
		{
			_ts.tv_nsec += (delay * 1000000L);
			_ts.tv_sec += (_ts.tv_nsec / 1000000000L);
			_msec = sec() * 1000L + _ts.tv_nsec / 1000000L;
			_tm_ok = false;
		}
		inline Time& operator= (const Time &rt)
		{
			_ts = rt._ts;
			_msec = rt._msec;
			_tm_ok = false;
			return *this;
		}
		inline bool operator > (const Time &rt) const
		{
			return _msec > rt._msec ? true : false;
		}
		inline bool operator >= (const Time &rt) const
		{
			return _msec >= rt._msec ? true : false;
		}
		inline bool operator < (const Time &rt) const
		{
			return _msec < rt._msec ? true : false;
		}
		inline bool operator <=  (const Time &rt) const
		{
			return _msec <= rt._msec ? true : false;
		}
		inline bool operator == (const Time &rt) const
		{
			return (rt._msec == _msec);
		}
		QWORD elapse(const Time &rt) const
		{
			SWORD val = rt.msec() - msec();
			return val < 0 ? 0L : val;
		}
		static void getLocalTime(struct tm &tv1,time_t timeVal)
		{
			time_t timValue = timeVal - my_timesync - my_timezone;
			gmtime_r(&timValue,&tv1);
		}
		SWORD getMDays(SWORD dayDiff)
		{
			if(dayDiff == 0)
			{
				return getMDays();
			}
			time_t time = _ts.tv_sec + dayDiff * (ONE_DAY/1000);
			struct tm tv;
			getLocalTime(tv,time);
			return tv.tm_mday;
		}
		void check_tm_ok()
		{
			if(!_tm_ok) 
			{ 
				getLocalTime(_tm,_ts.tv_sec);
				_tm_ok = true;
			}
		}
		void format(char *buffer,size_t bufferlen,const char *format = "%c/$M/%d$Y")
		{
			check_tm_ok();
			strftime(buffer,bufferlen,format,&_tm);
		}
		SWORD getSeconds()
		{
			check_tm_ok();
			return _tm.tm_sec;
		}
		SWORD getMinutes()
		{
			check_tm_ok();
			return _tm.tm_min;
		}
		SWORD getHours()
		{
			check_tm_ok();
			return _tm.tm_hour;
		}
		SWORD getMDays()
		{
			check_tm_ok();
			return _tm.tm_mday;
		}
		SWORD getMonths()
		{
			check_tm_ok();
			return _tm.tm_mon;
		}
		SWORD getYears()
		{
			check_tm_ok();
			return _tm.tm_year;
		}
		SWORD getWDays()
		{
			check_tm_ok();
			return _tm.tm_wday;
		}
		SWORD getYDays()
		{
			check_tm_ok();
			return _tm.tm_yday;
		}
		static const std::string& getLocalTZ();
		static void save_timezone(std::string &tzstr);
		static void restore_timezone(const std::string &tzstr);
		static void set_timesync(const SDWORD sync = 0);
	public:
		struct timespec _ts;
		QWORD _msec;
		bool _tm_ok;
		struct tm _tm;
};

class Clocker
{
	public:
		explicit Clocker(const SQWORD how_long,const SQWORD interval):_long(how_long),_interval(interval)
		{
			my_timesync = Time::my_timesync;
			assert(_long + _interval);
			delay();
		}
		explicit Clocker(const SQWORD how_long,const SQWORD interval,Time &ctv):_long(how_long),_interval(interval),_clock(ctv)
		{
			my_timesync = Time::my_timesync;
			assert(_long + _interval);
			assert(_interval >= _long);
			delay();
		}
		void next (const Time &cur)
		{
			_clock = cur;
			delay();
		}
		inline QWORD leftSec(const Time &cur)
		{
			SQWORD val = _clock.sec() - cur.sec();
			if(val < 0L)
			{
				return 0L;
			}
			return val;
		}
		inline bool operator() (const Time &cur)
		{
			if(_clock._ts.tv_sec + Time::my_timesync - my_timesync > cur._ts.tv_sec)
			{
				return false;
			}
			else
			{
				my_timesync = Time::my_timesync;
				_clock = cur;
				delay();
				return true;
			}
		}
	private:
		void delay()
		{
			QWORD escape = _clock.sec() % _interval;
			if(escape < _long)
			{
				_clock.addDelay((_long - escape) * 1000);
			}
			else if(escape > _long)
			{
				_clock.addDelay((_interval + _long - escape) * 1000);
			}
			else
			{
				_clock.addDelay(_interval * 1000);
			}
		}
		const QWORD _long;
		const QWORD _interval;
		SQWORD my_timesync;
		Time _clock;
};

//时间
class Timer
{
	public:
		Timer(const float how_long,const int delay = 0):_long((int)(how_long * 1000)),_timer(delay*1000)
		{
		}
		Timer(const float how_long,const RTime& cur):_long((int)(how_long * 1000)),_timer(cur)
		{
			_timer.addDelay(_long);
		}
		void next(const RTime &cur)
		{
			_timer = cur;
			_timer.addDelay(_long);
		}
		//如果当前时间小于或者等于_timer则延时_long
		bool operator() (const RTime &cur)
		{
			if(_timer <= cur)
			{
				_timer = cur;
				_timer.addDelay(_long);
				return true;
			}
			return false;
		}
	private:
		int _long;
		RTime _timer;
};
#endif















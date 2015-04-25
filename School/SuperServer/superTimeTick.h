#ifndef SUPER_TIME_TICK_H
#define SUPER_TIME_TICK_H

#include "base/baseTime.h"
#include "base/baseThread.h"

class SuperTimeTick : public Thread,public SingletonBase<SuperTimeTick>
{
	private:
		friend class SingletonBase<SuperTimeTick>;
		SuperTimeTick();
		~SuperTimeTick();
	public:
		static Time s_currentTime;
		void run();
		static void zeroHour();
		static void fourHour();
		static DWORD getDayStart( DWORD time )
		{
			return time / 86400 * 86400;
		}
		long getMaxFrameTime()
		{
			return m_maxFrameTime;
		}
		long getLastFrameTime()
		{
			return m_frameTime;
		}
		bool isHighDelay();
	private:
		void oneSec();
		void fiveSec();
		void tenSec();
		void oneMin();
		void fiveMin();
		void oneQuarter();
		void oneHour();
		void zeroClocker();
		void superFinal();

		Timer m_oneSec;
		Timer m_fiveSec;
		Timer m_tenSec;

		Timer m_oneMin;
		Timer m_fiveMin;
		Timer m_oneQuarter;

		Clocker  m_oneClocker;
		Clocker  m_zeroClocker;
		Clocker  m_fourClocker;

		QWORD m_maxFrameTime;
		QWORD m_frameTime;
};

inline bool SuperTimeTick::isHighDelay()
{
	return m_maxFrameTime > 200;
}

#endif


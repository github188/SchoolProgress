#include "superTimeTick.h"
#include "SuperServer.h"
#include "superTaskManager.h"
#include <time.h>

Time SuperTimeTick::s_currentTime;

SuperTimeTick::SuperTimeTick() : Thread("SuperTimeTick"),m_oneSec(1*1000L),m_fiveSec(5*1000L),m_tenSec(10*1000L),m_oneMin(60*1000L),m_fiveMin(5*60*1000L),m_oneQuarter(15*60*1000L),m_oneClocker(1*3600,1*3600),m_zeroClocker(24*3600,24*3600),m_fourClocker(4*3600,24*3600)
{
	m_maxFrameTime = 0;
	m_frameTime = 0;
}

SuperTimeTick::~SuperTimeTick()
{
}

void SuperTimeTick::run()
{
	DWORD step = 0;
	SDWORD maxFrameNum = 100;
	while(!isFinal())
	{
		setRuning();
		s_currentTime.now();
		struct timespec tv_begin;
		clock_gettime(CLOCK_REALTIME,&tv_begin);
		QWORD begin = tv_begin.tv_sec*1000L + tv_begin.tv_nsec/1000000L;
	
		SuperTaskManager::getInstance().doCmd();
		if(m_oneSec(s_currentTime))
		{
			oneSec();
			if(m_fiveSec(s_currentTime))
			{
				fiveSec();
			}
			else if(m_tenSec(s_currentTime))
			{
				tenSec();
			}
			else if(m_oneMin(s_currentTime))
			{
				oneMin();
			}
			else if(m_fiveMin(s_currentTime))
			{
				fiveMin();
			}
			else if(m_oneQuarter(s_currentTime))
			{
				oneQuarter();
			}
			else if(m_oneClocker(s_currentTime))
			{
				oneHour();
			}
			else if(m_zeroClocker(s_currentTime))
			{
				zeroHour();
			}
			else if(m_fourClocker(s_currentTime))
			{
				fourHour();
			}
		}
		++step;
		struct timespec tv_end;
		clock_gettime(CLOCK_REALTIME,&tv_end);
		QWORD end = tv_end.tv_sec*1000L + tv_end.tv_nsec /1000000L;
		m_frameTime = end - begin;
		if(maxFrameNum)
		{
			maxFrameNum -= 1;
			if(m_frameTime > m_maxFrameTime)
			{
				m_maxFrameTime = m_frameTime;
			}
		}
		else
		{
			maxFrameNum = 100;
			m_maxFrameTime = 0;
		}
		LogInfoCheckConditionOnly(m_frameTime<= 300,"管理服务器运行桢数过慢%lums",m_frameTime);
		if(m_frameTime < 10)
		{
			Thread::msleep(10 - m_frameTime);
		}
	}
	superFinal();
}

void SuperTimeTick::oneSec()
{
}

void SuperTimeTick::fiveSec()
{
}

void SuperTimeTick::tenSec()
{
}

void SuperTimeTick::oneMin()
{
}

void SuperTimeTick::fiveMin()
{
}

void SuperTimeTick::oneQuarter()
{
}

void SuperTimeTick::oneHour()
{
}

void SuperTimeTick::zeroHour()
{
}

void SuperTimeTick::fourHour()
{
}

void SuperTimeTick::superFinal()
{
}

bool SuperTimeTick::isHighDelay()
{
	return m_maxFrameTime > 200;
}




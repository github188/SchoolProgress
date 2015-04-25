#include "sceneTimeTick.h"
#include "SceneServer.h"
#include "time.h"

Time SceneTimeTick::s_currentTime;

SceneTimeTick::SceneTimeTick():Thread( "TimeTick" ),m_oneSec( 1 * 1000L ),m_fiveSec( 5 * 1000L ),m_tenSec( 10 * 1000L ),m_oneMin( 60 * 1000L ),m_fiveMin( 5 * 60 * 1000L ),m_oneQuarter( 15 * 60 * 1000L ),m_oneClocker( 1 * 3600,1 * 3600 ),m_zeroClocker( 24 * 3600,24 * 3600 ),m_fourClocker( 4 * 3600,24 * 3600 )
{
	m_maxFrameTime = 0;
	m_frameTime = 0;
}

SceneTimeTick::~SceneTimeTick()
{
}

void SceneTimeTick::run()
{
	DWORD step = 0;
	int maxFrameNum = 100;
	while( !isFinal() )
	{
		setRuning();
		long begin = 0,end = 0;
		struct timespec _tv_begin;
		clock_gettime( CLOCK_REALTIME,&_tv_begin );
		begin = _tv_begin.tv_sec * 1000L + _tv_begin.tv_nsec / 1000000L;

#if 0
		SceneServer::getInstance().checkAndReloadConfig();
		SceneServer::getInstance().doCmd();
		
		SceneTaskManager::getInstance().doCmd();
		
		recordClient->doCmd();
		
		sessionClient->doCmd();

		SceneManager::getInstance().loop( step );
#endif
		if( m_oneSec( SceneTimeTick::s_currentTime ) )
		{
			oneSec();
			if( m_fiveSec( SceneTimeTick::s_currentTime ) )
			{
				fiveSec();
			}
			else if( m_tenSec( SceneTimeTick::s_currentTime ) )
			{
				tenSec();
			}
			else if( m_oneMin( SceneTimeTick::s_currentTime ) )
			{
				oneMin();
			}
			else if( m_fiveMin( SceneTimeTick::s_currentTime ) )
			{
				fiveMin();
			}
			else if( m_oneQuarter( SceneTimeTick::s_currentTime ) )
			{
				oneQuarter();
			}
			else if( m_oneClocker( SceneTimeTick::s_currentTime ) )
			{
				oneHour();
			}
			else if( m_zeroClocker( SceneTimeTick::s_currentTime ) )
			{
				zeroHour();
			}
			else if( m_fourClocker( SceneTimeTick::s_currentTime ) )
			{
				fourHour();
			}
		}
		++step;
	#if 0
		step = step % MAX_NPC_GROUP;
		SceneServer::getInstance().checkFinal();
	#endif
		struct timespec _tv_end;
		clock_gettime( CLOCK_REALTIME,&_tv_end );
		end = _tv_end.tv_sec * 1000L + _tv_end.tv_nsec / 1000000L;

		m_frameTime = end - begin;

		if( maxFrameNum )
		{
			maxFrameNum -= 1;
			if( m_frameTime > m_maxFrameTime )
			{
				m_maxFrameTime = m_frameTime;
			}
		}
		else
		{
			maxFrameNum = 100;
			m_maxFrameTime = 0;
		}
		if( m_frameTime > 300 )
		{
			Global::logger->debug( "服务器运行桢数过慢 当前桢:%lu ms",m_frameTime );
		}
		if( m_frameTime < 10 )
		{
			Thread::msleep( 10 - m_frameTime );
		}
	}
	sceneFinal();
}

void SceneTimeTick::oneSec()
{
#if 0
	SceneMsgBoxManager::getInstance().loop( SceneTimeTick::s_currentTime );
	SceneFamilyManager::getInstance().loop();
	SceneGangManager::getInstance().loop();
	SceneCountryRegionManager::getInstance().loop();
	CustomCountryManager::getInstance().loop();

	SceneNpcManager::getInstance().recycleLoop();
	SceneTeamManager::getInstance().loop();
	SceneUserManager::getInstance().loop();
	
	SceneGangManager::getInstance().loop();
	SceneCountryRegionManager::getInstance().loop();
	CustomCountryManager::getInstance().loop();
	
	SceneNpcManager::getInstance().recycleLoop();
	SceneTeamManager::getInstance().loop();
	SceneUserManager::getInstance().loop();
	ActivityMgr::getInstance().loop();
	SceneCountryRegionManager::getInstance().save();
	g_ItemMgr.loop();
#endif
}

void SceneTimeTick::fiveSec()
{
}

void SceneTimeTick::tenSec()
{
}

void SceneTimeTick::oneMin()
{
#if 0
	SceneBiaoLogic::getInstance().checkMasterOnLine();
#endif
}

void SceneTimeTick::fiveMin()
{
}

void SceneTimeTick::oneQuarter()
{
}

void SceneTimeTick::oneHour()
{
#if 0
	SceneUserManager::getInstance().oneHour();
	SceneFubenEffectMgr::getInstance().oneHour();
#endif
}

void SceneTimeTick::zeroHour()
{
#if 0
	SceneUserManager::getInstance().zeroHour();
	SceneFubenEffectMgr::getInstance().zeroHour();
#endif
}

void SceneTimeTick::fourHour()
{
#if 0
	SceneUserManager::getInstance().fourHour();
#endif
}

void SceneTimeTick::sceneFinal()
{
}





#include "baseLog.h"
#include "baseTime.h"
#include "basePthread.h"
Logger::Logger(char *name)
{
	m_name = name;
	fp_file = NULL;
	m_day = 0;
	m_file = "/home/flyer/flyer/School/log/";
	m_level = LEVEL_ALL;
	fp_console = stdout;
}

Logger::~Logger()
{
	if( NULL != fp_file )
	{
		fclose(fp_file);
		fp_file = NULL;
	}
}

void Logger::debug(const char* pattern,...)
{
	if( m_level > LEVEL_DEBUG ) return;
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_DEBUG,pattern,vp);
	va_end(vp);
}
void Logger::setFile( const char *fileName )
{
	logMutex.lock();
	m_file = fileName;
	logMutex.unlock();
}


void Logger::setLevel(const LogLevel level)
{
	logMutex.lock();
	m_level = level;
	logMutex.unlock();
}

void Logger::setLevel(const std::string &level)
{
	if ("off" == level) setLevel(LEVEL_OFF);
	else if ("fatal" == level) setLevel(LEVEL_FATAL);    else if ("error" == level) setLevel(LEVEL_ERROR);
	else if ("warn" == level) setLevel(LEVEL_WARN);
	else if ("info" == level) setLevel(LEVEL_INFO);
	else if ("debug" == level) setLevel(LEVEL_DEBUG);
	else if ("all" == level) setLevel(LEVEL_ALL);
}

void Logger::warn(const char *pattern,...)
{
	if(m_level > LEVEL_WARN) return;
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_WARN,pattern,vp);
	va_end(vp);
}

void Logger::fatal(const char *pattern,...)
{
	if(m_level > LEVEL_FATAL) return;
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_FATAL,pattern,vp);
	va_end(vp);
}

void Logger::info(const char *pattern,...)
{
	if(m_level > LEVEL_ERROR) return;
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_INFO,pattern,vp);
	va_end(vp);
}

void Logger::error(const char* pattern,...)
{
	if( m_level > LEVEL_ERROR ) return;
	va_list vp;
	va_start(vp,pattern);
	logva(LEVEL_ERROR,pattern,vp);
	va_end(vp);
}

void Logger::log(const LogLevel level,const char * pattern,...)
{
	if( m_level > level ) return;
	va_list vp;
	va_start(vp,pattern);
	logva(level,pattern,vp);
	va_end(vp);
}

void Logger::logva(const LogLevel level,const char* pattern,va_list vp)
{
	if( m_level > level ) return;
	char szName[100] = {'\0'};
	SYSTEMTIME systemTime;
	if(!getSystemTime(&systemTime)) return;
	logMutex.lock();
	if( !m_file.empty() )
	{
		if( m_day != systemTime.wDay )
		{
			if( NULL != fp_file )
			{
				fclose( fp_file );
			}
			snprintf(szName,sizeof(szName),"%s%04d%02d%02d.log",m_file.c_str(),systemTime.wYear,systemTime.wMonth,systemTime.wDay);
			fp_file = fopen(szName,"at");
			m_day = systemTime.wDay;
		}
	}
	if(NULL != fp_file)
	{
		fprintf(fp_file,"[%s] ",m_name.c_str());
		fprintf(fp_file,"%04d/%02d/%02d ",systemTime.wYear,systemTime.wMonth,systemTime.wDay);
		fprintf(fp_file,"%02d:%02d:%02d ",systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
	 	vfprintf(fp_file,pattern,vp);
		fprintf(fp_file,"\n");
		fflush(fp_file);
	}
	if(NULL != fp_console)
	{
		fprintf(fp_console,"[%s] ",m_name.c_str());
		fprintf(fp_console,"%04d/%02d/%02d ",systemTime.wYear,systemTime.wMonth,systemTime.wDay);
		fprintf(fp_console,"%02d:%02d:%02d ",systemTime.wHour,systemTime.wMinute,systemTime.wSecond);
		vfprintf(fp_console,pattern,vp);
		fprintf(fp_console,"\n");
		fflush(fp_console);
	}
	logMutex.unlock();
}

void Logger::removeConsole()
{
	logMutex.lock();
	fp_console = NULL;
	logMutex.unlock();
}

const char* Logger::getName()
{
	return m_name.c_str();
}

void Logger::setName(const char* name)
{
	m_name = name;
}




		

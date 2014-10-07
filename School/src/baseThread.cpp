#include "baseThread.h"
long Thread::_tempid = 0;
Thread::Thread(const char* name,bool joinable):_running(true)
{
	id = ++_tempid;
	ThreadManager::getInstance().addThread(this);
	strncpy(this->name,name,sizeof(this->name));
	_alive = false;
	_joinable = joinable;
	_thread = 0;
	_complete= false;
}
Thread::~Thread()
{
	ThreadManager::getInstance().removeThread(this);
	_thread = 0;
}
bool Thread::checkRunning()
{
	if(!isAlive())
	{
		return true;
	}
	if(_running)
	{
		_running = false;
		return true;
	}
	return false;
}
void* Thread::threadProc(void *arg)
{
	Thread *thread = (Thread*)arg;
	thread->_alive = true;
	thread->cond.broadcast();
	thread->mlock.unlock();
	sigset_t sig_mask;
	sigfillset(&sig_mask);
	pthread_sigmask(SIG_SETMASK,&sig_mask,NULL);
	thread->run();
	thread->mlock.lock();
	thread->_alive = false;
	thread->cond.broadcast();
	thread->mlock.unlock();
	if(!thread->isJoinable())
	{
		DELETE(thread);
	}
	pthread_exit(NULL);
}
bool Thread::start()
{
	mlock.lock();
	if(_alive)
	{
		int ret = pthread_create(&_thread,NULL,threadProc,this);
		if(ret)
		{
			mlock.unlock();
			return false;
		}
	}
	else
	{
		mlock.unlock();
	}
	return true;
}
void Thread::join()
{
	if(_thread && _joinable)
	{
		pthread_join(_thread,NULL);
		_thread = 0;
		mlock.lock();
		while(_alive)
		{
			cond.wait(mlock);
		}
	}
}
pthread_t Thread::getCurrentThreadId()
{
	return pthread_self();
}
void Thread::sleep(const long sec)
{
	::sleep(sec);
}
void Thread::msleep(long mills)
{
	::usleep(1000 * mills);
}
void Thread::usleep(const long usec)
{
	::usleep(usec);
}
void Thread::final()
{
	_complete = true;
}
const bool Thread::isFinal() const
{
	return _complete;
}
long Thread::atomicAdd(volatile long *val,long x)
{
	return __gnu_cxx::__exchange_and_add((volatile _Atomic_word *)val,x) + x;
}
long Thread::atomicInc(volatile long *val)
{
	return atomicAdd(val,1);
}
long Thread::atomicDec(volatile long *val)
{
	return atomicAdd(val,-1);
}
const bool Thread::isAlive() const
{
	return _alive;
}
const bool Thread::isJoinable()const
{
	return _joinable;
}
bool ThreadManager::addThread(Thread *entry)
{
	bool ret = false;
	rwlock.wrlock();
	ret = addEntry(entry);
	rwlock.unlock();
	return ret;
}
void ThreadManager::removeThread(Thread *entry)
{
	rwlock.wrlock();
	removeEntry(entry);
	rwlock.unlock();
}



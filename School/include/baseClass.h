#ifndef BASE_CLASS_H
#define BASE_CLASS_H
#include <iostream>
#include <assert.h>

using namespace std;

//单例基类
template<typename T>
class SingletonBase
{
	protected:
		static T *instance;
	private:
		SingletonBase(const SingletonBase &_instance);
		SingletonBase& operator= (const SingletonBase &_instance);
	public:
		SingletonBase(){}
		virtual ~SingletonBase(){}
		static T& getInstance()
		{
			assert( instance );
			return *instance;
		}
		static void newInstance()
		{
			DELETE( instance );
			instance = new T();
		}
		static void deleteInstance()
		{
			DELETE( instance );
		}
};

template<typename T> T* SingletonBase<T>::instance = NULL;

//不可拷贝类基类
class Noncopyable
{
	private:
		const Noncopyable& operator= (const Noncopyable& noncopyable);
		Noncopyable(const Noncopyable &noncopyable);
	protected:
		Noncopyable(){};
		virtual ~Noncopyable(){};
};
#endif
			

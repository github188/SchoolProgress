#include<iostream>
using namespace std;

template<typename T>
class A
{
	static size_t size;
	
	public:	
	inline static size_t getSize(void)
	{
		return size;
	}
	
	inline static void setSize(size_t newSize)
	{
		size = newSize;
	}
	
	inline static void printSize(void)
	{
		cout<<"size:"<<size<<endl;
	}
};

template<typename T>
size_t A<T>::size = 2;

int main(void)
{
	/*注意，模板类的static，对于不同的模板，就是一个不同的类，这些类不会共享静态数据*/
	A<int> a;
	a.setSize(4);
	a.printSize();
	
	A<char*> b;
	b.printSize();
	b.setSize(3);
	
	/*数出来的数据完全不一样*/
	a.printSize();
	b.printSize();
	
	A<int> c;
	
	/*数出来的数据完全一样*/
	c.printSize();
	a.printSize();
	
	return 1;
}

 

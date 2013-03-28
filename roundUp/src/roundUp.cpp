#include<iostream>
#define BASE 8
using namespace std;

size_t roundUp(size_t bytes)
{
	/*这个是向上取倍数*/
	return (bytes + BASE - 1) & ~(BASE - 1);
	
	/*这个是向下取倍数*/
	return (bytes) & ~(BASE - 1);
}

int main(void)
{
	int a = -8;
	
	/*输出结果是一个非常大的数*/
	cout<<"size_t :"<<size_t(a)<<endl;
	
	cout<<"result :"<<roundUp(a)<<endl;
	
	return 1;
}

 

#include<iostream>
#include<sys/types.h>
using namespace std;

/*
#define MY_DEFINE
#define cat(x) #x
using namespace std;
typedef unsigned long long  QWORD;
typedef int Big[2];

#define Finc(hight,low)						\		
do{											\
	(low)[0] = ( (hight) >> 8 ) & 0xff;		\
	(low)[1] = (hight) & 0xff;				\
}while(false)

void finc(int *x)
{
	cout<<"finc is:"<<int(*x)<<endl;
}

#define MY_FINC(x) finc(x)
//#pragma pack(1)
struct TestInfo
{
	QWORD values;
	char a;
};
//#pragma pack()

class Single
{
	protect:
		Single() {};
		~Single() {};
	private:
		Single(const Single& single);
		const Single& operator= (const Single& single);
};
*/
template<typename T>
class A
{
	public:
		inline void func();
};

typedef A<int> AA;

template<>
void AA::func()
{
	cout<<"func here:"<<endl;
}


int main()
{
/*
	QWORD a = 4;
	cout<<"fuck you here:"<<sizeof( QWORD )<<endl;
	cout<<"TestInfo:"<<sizeof( TestInfo )<<endl;
	#ifdef MY_DEFINE
	cout<<"mydefine:"<<a<<endl;
	#endif
	cout<<"testclass:"<<cat(MY_CLASS)<<endl;
	MY_FINC((int*)&a);
	Big big;
	cout<<"big:"<<sizeof(Big)<<endl;
	int value = 3;
	int keys = 1;
	Finc(keys,(char*)(&value));
	cout<<"value:"<<value<<"keys:"<<keys<<endl;
	cout<<"nowVal:"<<(1>>8)<<endl;
*/
	AA a;
	a.func();
	char buffer[] = {"fuckyou"};
	char str[ strlen(buffer) * 2 + 1 ];
	strncpy( str,buffer,sizeof(buffer) );
	cout << "str:" << str << endl;
	return 0;
}

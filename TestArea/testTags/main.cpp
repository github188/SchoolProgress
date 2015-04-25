#include<iostream>
using namespace std;
int func( int a,int b )
{
	return a + b;
}

int main()
{
	int a = 2,b = 3;
	cout<<"result:"<<func( a ,b )<<endl;
	return 0;
}

/************************************************************
	文件名：main.cpp
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#include"numStr.h"
using namespace std;
	
int main(void)
{
	string data1("1000"),data2("1000");
	NumStr numStr1(data1),numStr2(data1);
	--numStr1;
	numStr1.printData();
	
	NumStr result (numStr1 + numStr2);
	result.printData();
	return 1;
}
	
	
	

/************************************************************
	文件名：main.cpp
	文件作用：测试文件
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/

#include<iostream>
#include"allocate.h"
#include"iterator.h"
using namespace std;

int main(void)
{
	Allocate<int> allocate;
	int *p = allocate.allocate();
	
	*p = 4;
	
	cout<<"p:"<<*p<<endl;
	
	return 1;
}


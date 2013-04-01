/************************************************************
	文件名：numStr.h
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#ifndef NUMSTR_H
#define NUMSTR_H
#include<iostream>
using namespace std;

class NumStr
{	
	public:
	string strData;
	
	size_t scale;
	
	public:
	
	NumStr(string &_strData,int _scale = 10):strData(_strData),scale(_scale)
	{
		
	}
	
	NumStr(NumStr &_strData):strData(_strData.strData),scale(_strData.scale)
	{
		
	}

	NumStr(void):scale(10)
	{

	}
	
	inline bool empty(void)
	{
		return strData.empty();
	}
	
	inline size_t size(void)
	{
		return strData.size();
	}
	
	inline void fillNewData(string& newData)
	{
		strData.clear();
		strData = newData;
	}
	
	
	inline void operator =(NumStr &_strData)
	{
		strData = _strData.strData;
	}
	
	
	NumStr& operator--(void);
	
	void reduceOne(void);
	
	void printData(void);			
	
	
};

//NumStr loop(NumStr &numStr);


NumStr operator+(NumStr &numStrF,NumStr &numStrS);

/*
string operator*(NumStr &numStrF,NumStr &numStrS);

*/

#endif
	

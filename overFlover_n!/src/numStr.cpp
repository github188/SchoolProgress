/************************************************************
	文件名：numStr.cpp
	文件作用：类NumStr类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#include"numStr.h"
#include<stdlib.h>
using namespace std;

void NumStr::reduceOne(void)
{
	if(strData.empty())
	{
		cout<<"NumStr::reduceOne the strData is empty"<<endl;
		return;
	}
	
	char *ptr = const_cast<char*>(strData.c_str());
	int len = strData.size() - 1;
	int num = 0;
	
	if(*ptr == '0')
	{
		cout<<"NumStr::reduceOne the strData is zero"<<endl;
		return;
	}
	
	while(len >= 0)
	{
		num =  *(ptr + len) - '0';
		if(num >= 1)
		{
			*(ptr + len) = '0' + num - 1;
			break;
		}		
		*(ptr + len) = '0' + num + scale - 1;
		--len;
	}
	
	if(*ptr == '0')
	{
		strData.erase(strData.begin());
	}
}

NumStr& NumStr::operator--(void)
{
	reduceOne();
	return *this;
}
			
void NumStr::printData(void)
{
	cout<<"the strData:"<<strData<<endl;
}

/*
NumStr loop(NumStr &numStr)
{
	char *ptr = const_cast<char*>(numStr.strData.c_str());
	NumStr result;
	if(*ptr == '1' || *ptr == '0')
	{
		result.fillNewData("0");
		return result;
	}
	return numStr * loop(--numStr);
}

*/

NumStr operator+(NumStr &numStrF,NumStr &numStrS)
{
	NumStr resultNumStr;
	string result;
	if(numStrF.empty() && numStrS.empty())
	{
		return resultNumStr;
	}
	if(numStrF.empty())
	{
		resultNumStr = numStrS;
		return resultNumStr;
	}
	if(numStrS.empty())
	{
		resultNumStr = numStrF;
		return resultNumStr;
	}
	
	char *ptrF,*ptrS;
	int lenF,lenS;
	size_t lastNumF,lastNumS,lastNumSum;
	bool isEnterHead = false;
	
	lenF = numStrF.size() - 1;
	lenS = numStrS.size() - 1;
	
	ptrF = const_cast<char *>(numStrF.strData.c_str());
	ptrS = const_cast<char *>(numStrS.strData.c_str());
	
	for(;lenF >= 0 && lenS >= 0; --lenF,--lenS)
	{
		lastNumF = *(ptrF + lenF) - '0';
		lastNumS = *(ptrS + lenS) - '0';		
	
		lastNumSum = lastNumF + lastNumS;
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenF >= 0; --lenF)
	{
		lastNumF = *(ptrF + lenF) - '0';
	
		lastNumSum = lastNumF;
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	for(;lenS >= 0; --lenS)
	{
		lastNumS = *(ptrS + lenS) - '0';
	
		lastNumSum = lastNumS;
		
		if(isEnterHead)
		{
			lastNumSum += 1;
			isEnterHead = false;
		}
		
		if(lastNumSum < 10)
		{
			result.insert(result.begin(),'0' + lastNumSum);
		}
		else
		{
			result.insert(result.begin(),'0' + lastNumSum - 10);
			
			isEnterHead = true;
		}
	}
	
	if(isEnterHead)
	{
		result.insert(result.begin(),'0' + 1);
	}
	
	resultNumStr.fillNewData(result);
	
	return resultNumStr;
}




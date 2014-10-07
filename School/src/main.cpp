#include<iostream>
#include<mysql.h>
#include "baseTest.h"
#include "baseSqlPool.h"
using namespace std;
using namespace Test;
int main()
{
	Test::logger = new Logger();
	char url[] = "mysql://root:flyer@localhost:306/123";
	MysqlPool * mysqlPool = new MysqlPool(2,4);
	bool ret = mysqlPool->putUrl(1,url);
	cout<<"ret:"<<ret<<endl;
	return 1;
}


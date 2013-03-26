#include<iostream>
#include<string>
#include <libmemcached/memcached.h>
using namespace std;

int main(void)
{
	memcached_st* 				memc_s;//be used by other libmemcached(3) functions to communicate with the server.用于其他memcached的C函数接口与memcached server交互
	memcached_server_list_st 	server_list;//memcached_server_st* was aliased to memcached_server_list_st.0.39版本后，memcached_server_list_st便是memcached_server_st的别名
	memcached_return_t 			rc;//to hold any error
	
	size_t 		key_length;//用于memcached_set时，作为键长值传入
	size_t 		value_length;//用于memcached_get时，来标识获取到的值的大小
	time_t 		expiration;//过期时间
	uint32_t 	flags;		
		
	memc_s = memcached_create(NULL);
	server_list = NULL;
	expiration = 0;
	flags = 0;

	//	ip和端口将通过Mem_configure提供
	//	first append server to memcached_server_list ,the first argument is  NULL
	server_list = memcached_server_list_append(server_list,server_ip,server_port,&rc);    
	if(rc == MEMCACHED_FAILURE)
	{
		cout<<"adds a server to the memcached_server_list failure"<<endl;
		exit(1);
	}

    //pushes an array of memcached_server_st into the memcached_st struct
	rc = memcached_server_push(memc_s, server_list);
	if(rc == MEMCACHED_FAILURE)
	{
		cout<<"memcached_server_push failure"<<endl;
		exit(1);
	}

	memcached_server_list_free(server_list);
	
	memcached_free(memc_s);
	
	return 1;
}
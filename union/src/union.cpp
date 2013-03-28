#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;

/*跟结构体类似*/
union obj
{
	obj *next;
	char client_data[2];
	obj(char* b = NULL)
	{
		memset(client_data,'0',sizeof(client_data));
		next = NULL;
		if(b)
		{
			strncpy(client_data,b,1);
			cout<<"b:"<<b<<endl;
		}
		cout<<"client_data:"<<client_data<<endl;
	}
};

void inputObj(obj* volatile freeList[],size_t length)
{

	obj* volatile *list;
	obj *current_obj,*now_obj;
	
	char *ptr = (char*)malloc(100);

	list = freeList + 0;
	
	*list = current_obj = (obj*)(ptr);		
	
	
	for(size_t i = 1;i < 10;++i)
	{
		
		current_obj = current_obj->next;
		
		current_obj = (obj*)(ptr + i * 8);
		
		cout<<"inputObj :*current_obj:"<<current_obj->client_data<<endl;				
	}
	
	current_obj->next = NULL;
}

void printIndexSize(obj* volatile *freeList)
{
	obj *current_obj = *freeList;
	int i = 0;
	while(current_obj)
	{
		cout<<"printfSize:current_obj:"<<current_obj->client_data<<endl;	
//		current_obj = current_obj->next;
		++i;
		current_obj = *freeList + i;
		
	}
}

void printfSize(obj* volatile freeList[],size_t length)
{
	for(size_t i = 0;i < length;++i)
	{
		printIndexSize(freeList + i);
	}
}



int main(void)
{
	obj ab("go"),cd;
	cd = ab;
	ab.client_data[1] = '\0';
	obj* volatile freeList[8] = {0};	
//	inputObj(freeList,8);
//	printfSize(freeList,8);
	return 1;
	 
}









 

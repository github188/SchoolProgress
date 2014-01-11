//大厅服务器类声明
#ifndef HALL_SER_H
#define HALL_SER_H
#include"com.h"
typedef ULI UID_TYPE;
typedef ULI CONNECT_TYPE;
typedef size_t INDEX_TYPE;
class HallSer
{
    private:
        char ip[IPADDR];
        char name[SERNAME];
        size_t port; 
        ULI listenerFd;                            //监听客户端fd  
        event_base *base;
        UID_TYPE uid;
        map<UID_TYPE,CONNECT_TYPE> uidFdMap;         //uid对应connectfd
        map<CONNECT_TYPE,UID_TYPE> fdUidMap;          //connectfd对应uid
        map<INDEX_TYPE,set<UID_TYPE> > indexUidMap;   //游戏服务器下表对应uid集合
        map<UID_TYPE,INDEX_TYPE> uidIndexMap;          //uid对应index
        
        HallSer& operator=(const HallSer &hallSer);
        HallSer(const HallSer &hallSer);
    public:
        HallSer(const char *ip,const char *name,size_t port);
        
        
        
};

#endif
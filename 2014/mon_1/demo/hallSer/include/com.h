#ifndef COM_H
#define COM_H
#include<set>

//宏定义处
#define IPADDR 20          //ip地址长度
#define SERNAME 40         //服务器名称长度

typedef unsigned long int ULI;

//结构定义处
typedef struct IpInfo
{
	char ip [IPADDR];             //服务器ip
    char name [SERNAME];          //服务器name
    size_t port;                  //服务器端口
    ULI upperNum;                 //服务器最大承载人数
    
    private:
        void signVal(const IpInfo &ipInfo)
        {
            strncpy(ip,ipInfo.ip,sizeof(ip));
			strncpy(name,ipInfo.name,sizeof(name));
			port = ipInfo.port;	
            upperNum = ipInfo.upperNum;
        }
        
        void init(void)
        {
            memset(ip,'\0',sizeof(ip));
            memset(name,'\0',sizeof(name));
            port = 0;
            upperNum = 0;
        }
    public:
   		IpInfo(const char *_ip,const char *_name,size_t port,ULI _upperNum)
		{
			strncpy(ip,_ip,sizeof(ip));
			strncpy(name,_name,sizeof(name));
			port = _port;		
            upperNum = _upperNum;
		}																											
        
        IpInfo& operator=(const IpInfo &ipInfo)
        {
            init();
            signVal(ipInfo);
            return *this;
        }
        
        IpInfo(const IpInfo &ipInfo)
        {
            init();
            signVal(ipInfo);
        }
        
        bool operator<(const IpInfo &ipInfo)
        {
            return strncmp(ip,ipInfo.ip);
        }
        
        bool operator==(const IpInfo &ipInfo)
        {
           return strncmp(ip,ipInfo.ip) == 0 ? port == ipInfo.port : false;
        }
        
        ~IpInfo(void)
        {
            init();
        }   
}IpInfo;


#endif
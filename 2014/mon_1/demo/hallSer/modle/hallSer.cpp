#include"hallSer.h"
HallSer::HallSer(const char *_ip,const char *_name,size_t _port)
{
    init();
    strncpy(ip,_ip,sizeof(ip));
    strncpy(name,_name,sizeof(name));
    port = _port;
}

void HallSer::init(void)
{
    memset(ip,'\0',sizeof(ip));
    memset(name,'\0',sizeof(name));
    listenerFd = 0;
    uid = 1;
    base = NULL;
}

void HallSer::runLoop(void)
{
    if(bese)
    {
        perror("base again");
        exit(0);
    }
    base = event_base_new();
    if(!base)
    {
        perror("base error NULL");
        exit(0);
    }
    sockaddr sin;
    sin.sin_family = AFET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr(ip);
    
    int fd = socket(AFET,SOCK_STREAM,0);
    if(fd < 0)
    {
        perror("listener is error");
        exit(0);
    }
    listenerFd = fd;
    evutil_make_socket_nonblocking(listenerFd);
    if(bind(listenerFd,(sockaddr *)&sin,sizeof(sockaddr)) < 0)
    {
        perror("bind error");
        exit(0);
    }
    if(listen(listenerFd,1024) < 0)
    {
        perror("listen error");
        exit(0);
    }
    
    event *listen_event = event_new(base,listenerFd,EV_READ|EV_PERSIS,do_accept,this);
    event_add(listen_event, NULL);
    event_base_dispatch(base);
}

bool HallSer::accept()
void do_accept(evutil_socket_t listenerFd,short event,void *ard)
{
    HallSer *hallSer = (HallSer *)arg;
    sockaddr sin;
    socklen_t len = sizeof(sin);
    int newfd = accept(listenerFd,(sockaddr *)&sin,&len);
    if(newfd < 0)
    {
        cout<<"warning newfd less 0"<<newfd<<endl;
        return;
    }
    else if(newfd > FDSIZE)
    {
        cout<<"warning newfd more than FDSIZE"<<newfd<<endl;
        close(fd);
    }
    


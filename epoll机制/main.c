


#define MAX_LISTENNUM   1024


typedef struct _Server
{
    struct sockaddr_in srvAddr;
    int                listenFd;
    int                epollFd;
}Server

Server* g_pSrv;

/*****************************************************************************
 �� �� ��  : doEpoll
 ��������  : ����epoll
 �������  : int listenFd
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��26��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
void doEpoll( int listenFd )
{
    int ret=0;
    //1.�����¼���������
    struct epoll_event events[EPOLL_EVT];
    //2.����epoll����
    g_pSrv->epollFd = epoll_creat(MAX_LISTENNUM);
    //3.��Ӽ����¼�(epfd,listenfd,Evt,timeout)
     (g_pSrv->epollFd,g_pSrv->listenFd,EPOLLIN,-1);
    //4.�������
    for(;;)
    {
        //5.��ȡ�Ѿ����ص��¼�
        // int epoll_wait(int epfd, struct epoll_event *events,
        //              int maxevents, int timeout);
        ret=epoll_wait(g_pSrv->epollFd,events,EPOLL_EVT,-1);
        //6.�Է���������
        
    }
}


/*****************************************************************************
 �� �� ��  : epollRetProc
 ��������  : ��epoll_wait�ķ���������
 �������  : int epfd,struct epoll_event* events,int num,int listenFd,char* buf
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��27��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
void epollRetProc( int epfd,struct epoll_event* events, /
    int num,int listenFd,char* buf )
{
    unsigned int i=0;
    int fd=0;
    //�������ص��¼�
    for(i=0;i<num;++i)
    {
        fd=events[i].data.fd=listenFd;
        SIGABRT
    }
}























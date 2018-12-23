
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
//#include <sys/pool>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/shm.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;


#define MAX_FD_SIZE     1024
#define PORT            8848
#define ADDR            "127.0.0.1"
#define MAX_DATALINE    1024


typedef struct _Server
{
    int maxFd;
    int cltCnt;//��ǰ�ͻ��˸���
    int svrFd;//ȫ��socket
//    int cltFds[MAX_FD_SIZE];//fd����
//    fd_set allFdSet;//����fdSet��ͷ
//    struct timeval tv;//��ʱʱ��
    struct sockaddr_in svrAddr;//��������ַ
    struct pollfd       cltFds[MAX_FD_SIZE];
}Server;

Server* g_pSvr;//����������������ָ��

/*****************************************************************************
 �� �� ��  : initServer
 ��������  : ��ʼ������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��23��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
int initServer( Server* pServer )
{
    int flg=0;
    pServer=(Server*)malloc(sizeof(Server));
    if(pServer==NULL)
        flg = -1;
    memset(pServer,0,sizrof(Server));
    flg = 0;

    return flg;
}


/*****************************************************************************
 �� �� ��  : procCltData
 ��������  : ����ͻ�������ҵ���߼�
 �������  : int cltFd
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��24��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
int procCltData( int cltFd )
{
    char buf[MAX_DATALINE]
    int ret=read(cltFd,buf,MAX_DATALINE);
    if(ret==0)
    {
        close(cltFd);
        return -1;
    }
    write(stdout,buf,ret);
    write(cltFd,buf,ret);//��д���ͻ���
    return 0;
}

/*****************************************************************************
 �� �� ��  : procCltConn
 ��������  : ����ͻ��˵�����
 �������  : srtuct pollfd* cltFds, int num
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��24��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
void procCltConn( srtuct pollfd* cltFds, int num )
{
    unsigned int i=0;
    int ret=-1
    for(i=1;i<num;++i)
    {
        if(cltFds[i]<0)
            continue;
        //�жϿͻ��˾�������Ƿ�׼����//checker(Ȧ���Ӷ�)
        if(cltFds[i].revents & POLLIN)
        {
            ret=procCltData();
            if(-1==ret)
            {
                cltFds[i].fd=-1;
                continue;
            }
        }
    }
}


/*****************************************************************************
 �� �� ��  : delServer
 ��������  : ���ٷ���������
 �������  : Server* pServer
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��23��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
void delServer( Server* pServer )
{
    if(pServer)
    {
        free(pServer);
        pServer=NULL;
    }
}








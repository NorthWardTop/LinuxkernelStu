
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys.types.h>

extern Server g_pSvr

/*****************************************************************************
 �� �� ��  : initSock
 ��������  : �����׽���, ����
 �������  : const char* addr,int port
 �������  : int* skfd,
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��22��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
int initSock(int* skfd,const char* addr,int port)
{
    int flg=0;
    struct sockaddr_in  
    //����socket
    skfd=sock(AF_INET,SOCK_STREAM,0);
    bzero(&g_pSvr->svrAddr,sizeof(g_pSvr->));
    g_pSvr->svrAddr.sin_family = AF_INET;
    //�ַ�����ַת�������ֽ����ַ
    inet_pton(AF_INET,addr,&g_pSvr->svrAddr.sin_addr.s_addr);
    g_pSvr->svrAddr.sin_port = htons(PORT);
    //bind addr info with global socket
    if(-1==bind(g_pSvr->svrFd, \
        (struct sockaddr*)&g_pSvr->svrAddr,sizeof(g_pSvr->svrAddr)))
    {
        perror("server socket bind error!\n");
        flg=-1;
    }
    //listen server Fd
    if(-1==listen(g_pSvr->svrFd,MAX_FD_SIZE))
    {
        perror("server socket listen error!\n");
        flg=-1;
    }
    
    return flg;
}




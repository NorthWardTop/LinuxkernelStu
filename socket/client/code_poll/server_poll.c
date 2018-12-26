#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/shm.h>
#include <arpa/inet.h>
using namespace std;

struct pollfd

#define MAX_FD_SIZE   1024
#define PORT    	  6661
typedef struct ServerContext
{
	 int CliCnt;  //��ǰfd�ĸ���
     int CliFds[MAX_FD_SIZE]; //��ǰfd������
     int MaxFd;
	 int iServerFd;  //�������
	 struct timeval     tv;
	 struct sockaddr_in SockAdd; //��������ַ
	 fd_set AllFdSet;	 //����FD_SETS��ͷ 
}T_ServerContext;

typedef T_ServerContext * PT_ServerContext;
//�������˶���
static PT_ServerContext   g_ptSerContext;

/*****************************************************************************
 �� �� ��  : main
 ��������  : ������
 �������  : int argc
             char *argv[]
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��21��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
int main( int argc, char *argv[] )
{	

	unsigned int i;
	//Ϊ����˶��������ڴ�
	g_ptSerContext=(PT_ServerContext)malloc(sizeof(T_ServerContext));
	if(g_ptSerContext==NULL)
		{
		perror("malloc server object error\n");
		return 0;
	}
	//����˶����ʼ��������
	memset(g_ptSerContext,0,sizeof(T_ServerContext));
	for(i=0;i<MAX_FD_SIZE;i++)
		{
		g_ptSerContext->CliFds[i] = -1;
	}
	//��������socket
	g_ptSerContext->iServerFd = socket(AF_INET,SOCK_STREAM,0);
	if(-1==g_ptSerContext->iServerFd)
		{
		perror("Creat server socket error\n");
		return 0;
	}
	//��ʼ����ַ��Ϣ
	g_ptSerContext->SockAdd.sin_family 		=AF_INET;
	g_ptSerContext->SockAdd.sin_port   		=htons(PORT);
	g_ptSerContext->SockAdd.sin_addr.s_addr =htonl(INADDR_ANY);
	//���м�����ַ��
	if(bind(g_ptSerContext->iServerFd,(struct sockaddr *)&g_ptSerContext->SockAdd, \
		sizeof(g_ptSerContext->SockAdd))==-1)
		{
		perror("bind error\n");
		return 0;	
	}
	//���ü���
	if(listen(g_ptSerContext->iServerFd,MAX_FD_SIZE))
		{
		perror("listen error\n");
		return 0;	
	}
	//�������ӵ���ʼ��ַ
	fd_set *ReadFdSet = &g_ptSerContext->AllFdSet;
	while(1)
	{
		int   iRet;
		//��ʼ������
		FD_ZERO(ReadFdSet);
	    //�Ѽ��������������
		FD_SET (g_ptSerContext->iServerFd,ReadFdSet);
	    g_ptSerContext->MaxFd = g_ptSerContext->iServerFd;
		for(i=0;i<MAX_FD_SIZE;i++)
		{
			int iTmpFd  = g_ptSerContext->CliFds[i];
			FD_SET(iTmpFd,ReadFdSet);
			g_ptSerContext->MaxFd  =(iTmpFd > g_ptSerContext->MaxFd ? iTmpFd:g_ptSerContext->MaxFd );
		}
		//����select��ʱʱ��
		g_ptSerContext->tv.tv_sec  = 20;
		g_ptSerContext->tv.tv_usec = 0 ;
		//����SELECT ��ѯ
		iRet=select(g_ptSerContext->MaxFd+1,ReadFdSet,NULL,NULL,&g_ptSerContext->tv);
		//�Ƿ�Ϊ���󷵻�
		if(iRet == -1)
			{
			perror("select error\n");
			return 0;	
		}
		//�Ƿ�Ϊ��ʱ����
		if(iRet==0)
			{
			printf("select time out!\n");
			continue ;
		}
		//��sk����,�жϷ���fd�Ƿ�Ϊ�������
		if(FD_ISSET(g_ptSerContext->iServerFd,ReadFdSet))
		{
		   //Ϊ�������
		   struct sockaddr_in Clinew;
		   socklen_t len = sizeof(Clinew);
		   int    iConFd= -1;
		   while(iConFd==-1)
		   	{
			 iConFd= accept(g_ptSerContext->iServerFd,(struct sockaddr *)&Clinew,&len);
			 if(iConFd ==-1)
			 {
				perror("accept error\n");
			 }
		   }
		   //����⵽�������ӵĿͻ��ˣ��������˵����Ӿ��������  
			for(i=0;i<MAX_FD_SIZE;i++)
			{
				//�ҵ�һ����λ������µ�FD
				if(g_ptSerContext->CliFds[i]<0)
					{
					g_ptSerContext->CliFds[i]=iConFd;
					g_ptSerContext->CliCnt++;
					break;
				}
			}
		 }
		 char 		aBuf[1024];
	     //������SK��������ͨ��
	     for(i=0;i<g_ptSerContext->CliCnt;i++)
	     {
			int iTmpFd = g_ptSerContext->CliFds[i];
			if(iTmpFd <0)
				{	
				continue;
			}
			//�Ƿ�ǰfd�����ݿɶ�
			if(FD_ISSET(iTmpFd,ReadFdSet))
			{
			//��Ϊ������fork creat_thread�µĽ���/�߳�
				//iTmpFd�ɶ�
				int  iReadCnt = read(iTmpFd,aBuf,1024);
				if(iReadCnt<=0)
				{
				
					//read ��������
					FD_CLR(iTmpFd,&g_ptSerContext->AllFdSet);
					close(iTmpFd);
					g_ptSerContext->CliFds[i]=-1;
					continue;
				}
				printf("%s\n",aBuf);
			}
			//ҵ���߼�
			string sEchoBuf ="hello ,client";
			write(iTmpFd,sEchoBuf.c_str(),sEchoBuf.length()+1);
		 }
	}
    return 0;
}


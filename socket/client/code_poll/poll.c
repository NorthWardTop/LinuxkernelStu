#include "server.h"



extern PTServerST  g_ptServer;




/*****************************************************************************
 �� �� ��  : DoPollHandle
 ��������  : 1.���poll�����ĳ�ʼ����  2.����poll����  3.��poll�ķ�������Ӧ
 �������  : int  listenfd
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��26��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
void DoPollHandle( int  listenfd )
{
  unsigned int  i =0;
  int			iRet=0;
  struct sockaddr_in  tCliAddr;
  g_ptServer->Clientfds[0].fd 		= listenfd;
  g_ptServer->Clientfds[0].events	= POLLIN;
  //�Ե�ǰ��pollfd��������ʼ��
  for(i=1;i<LISTENNUM;i++)
  	{
	 g_ptServer->Clientfds[i].fd     = -1;
  }
  g_ptServer->MaxFd  = 0;
  for(;;)
  	{
  		//����poll����ѯ
		iRet=poll(g_ptServer->Clientfds,g_ptServer->MaxFd+1,INFTIM);
		if(iRet==-1)
			{
			perror("poll error\n");
			exit(1);
		}
		//���з���ֵ�ļ���ж��Ƿ���fd׼����
		//�жϵ�ǰ��������Ƿ����µ�����
		if(g_ptServer->Clientfds[0].revent & POLLIN)
		{
			//�������µ�����
			socklen_t len = sizeof(tCliAddr);
		    int    iConFd= -1;
		    while(iConFd==-1)
		   	{
				 iConFd= accept(listenfd,(struct sockaddr *)&tCliAddr,&len);
				 if(iConFd ==-1)
				 {
					perror("accept error\n");
				 }
		   }
		  fprintf(stdout,"Accept a new client: %s: %d\n",inet_ntoa(tCliAddr.sin_addr),tCliAddr.sin_port);
		  //��������������
		  for(i=1;i<LISTENNUM;i++)
		  	{
				if(g_ptServer->Clientfds[i].fd < 0)
				{
					g_ptServer->Clientfds[i].fd=iConFd;
					break;
				}		
		  }
		  if(i==LISTENNUM)
		  {
			fprintf(stderr,"MAX CLIENTS\n");
			exit(1);
		  }
		  g_ptServer->Clientfds[i].events = POLLIN;
		  g_ptServer->MaxFd= (i>g_ptServer->MaxFd ? i:g_ptServer->MaxFd);
		  //��ǰpoll����ֻ��һ��������� ��ѭ������
		  if(--iRet<=0)
		  	continue;
		}
		
		//����ͻ�������
		HandleClientConnection(g_ptServer->Clientfds,g_ptServer->MaxFd);
   }

}


















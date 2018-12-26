

PTServerST  g_ptServer;

/*****************************************************************************
 �� �� ��  : InitServer
 ��������  : ��ʼ������˶���
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��26��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
int InitServer(void)
{
    g_ptServer = (PTServerST)malloc(sizeof(ServerST));
	if(g_ptServer == NULL)
		{
		return -1;
	}
	memset(g_ptServer,0,sizeof(ServerST));
	return 0;
}





/*****************************************************************************
 �� �� ��  : RemoveServer
 ��������  : ���пͻ��˵�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��26��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
void RemoveServer( void  )
{
    if(g_ptServer)
    {
		free(g_ptServer);
		g_ptServer =NULL;
	}
}



/*****************************************************************************
 �� �� ��  : PorcessClientData
 ��������  : �ͻ���ҵ���߼����ݴ���
 �������  : int clientfd
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��5��3��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
int PorcessClientData(int clientfd)
{
    int  iRet;
	char aBuff[MAXLINE];
	iRet = read(clientfd,aBuff,MAXLINE);
	if(iRet ==0)
		{
	 	 close(clientfd);
		 return -1;
	}
	write(stdout,aBuff,iRet);
	//echo������
	write(clientfd,aBuff,iRet);
	return 0;
}


/*****************************************************************************
 �� �� ��  : HandleClientConnection
 ��������  : �������ͻ������ݴ�����
 �������  : struct pollfd *clientfds
             int num
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��5��3��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
void HandleClientConnection( struct pollfd *clientfds, int num )
{
	unsigned int i=0;
	int 		 iRet=0;
    for(i=1;i<=num;i++)
    {
	 	if(clientfds[i].fd<0)
			continue;
		//�жϵ�ǰ�ͻ��˾���Ƿ�������׼����
		if(clientfds[i].revents & POLLIN)
		{
		   	//�ͻ���ҵ���߼�
		  	iRet=PorcessClientData(clientfds[i].fd);
			if(iRet==-1)
			{
				clientfds[i].fd = -1;
				continue;
			}
		}
	}
}









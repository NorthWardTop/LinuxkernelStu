

/*****************************************************************************
 �� �� ��  : InitSocket
 ��������  : ��������ʼ��Socket ,���а�
 �������  : const char *
             int port
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2017��4��26��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
int InitSocket(const char *ip, int port)
{
	int iListenFd;
	
	//����socket
	iListenFd = socket(AF_INET,SOCK_STREAM,0);
	g_ptServer
    bzero(&g_ptServer->ServerAddr,sizeof(g_ptServer->ServerAddr));
	//��ʼ����ַ��Ϣ
	g_ptServer->ServerAddr.sin_family 		=AF_INET;
	inet_pton(AF_INET,ip,&g_ptServer->ServerAddr.sin_addr)
	g_ptServer->ServerAddr.sin_port   		=htons(port);
	if(bind(iListenFd,(struct sockaddr *)&g_ptServer->ServerAddr, \
		sizeof(g_ptSerContext->SockAdd))==-1)
	{
		perror("bind error\n");
		return 0;	
	}
	return  iListenFd;
}





/*****************************************************************************
 �� �� ��  : doPoll
 ��������  : 1.poll���� 2.poll�ķ���������Ӧ
 �������  : int listenFd
 �������  : ��
 �� �� ֵ  : int 
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��12��23��
    ��    ��   : my
    �޸�����   : �����ɺ���

*****************************************************************************/
int doPoll( int listenFd )
{
    int i=0,iRet,flg=0;
    socklen_t cltAddr;
    g_pSvr->cltFds[0].fd = listenFd;
    g_pSvr->cltFds[0].events = POLLIN;
    //�Ե�ǰpoll��ʼ��
    for(int i=1;i<MAX_FD_SIZE;++i)
    {
        g_pSvr->cltFds[i].fd=-1;
    }
    g_pSvr->maxFd=0;
    
    for(;;)
    {
        //POLL��ѯ
        iRet=poll(g_pSvr->cltFds,g_pSvr->maxFd+1;INFTIM);
        if(iRet==-1)
        {
            flg=-1;
            perror("poll error!\n")
        }
        //���ؼ��
        if(g_pSvr->cltFds[0].events & POLLIN)
        {
            //������������
            int conFd=-1;//���Ӿ��
            socklen_t len=sizeof(cltAddr);//��ַ����
            while(conFd==-1)//û�н��ܵ����Ӿ�һֱ����
            {
                conFd=accept(listenFd,(struct sockaddr*)&cltAddr,&len);
                if(conFd==-1)
                    perror("accept error!\n");
            }
            fprintf(stdout,"Accept a new clt...");
            fprintf(stdout,"from     %s:%d",inet_ntoa(cltAddr.sin_addr),cltAddr.sin_port);
            //��������
            for(i=1;i<MAX_FD_SIZE;++i)
            {
                if(g_pSvr->cltFds[i].fd<0)//����
                {
                    g_pSvr->cltFds[i].fd=conFd;//�ͻ������Ӿ��
                    g_pSvr->cltFds[i].events=POLLIN;//Ϊ�����¼�
                    g_pSvr->maxFd=(i>g_pSvr->maxFd)?i:g_pSvr->maxFd;
                }
            }
            if(i==MAX_FD_SIZE)
            {
                fprintf(stderr, "Out of MAX_FD_SIZE");
                flg=-1;
            }
            //��ǰֻ����һ���������
            if(iRet==1 | iRet==0)
                continue;
            
            procCltConn(g_pSvr->cltFds, g_pSvr->maxFd)
        }
    }
}

















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
        iRet=poll(g_pSvr->cltFds,g_pSvr->maxFd+1;INFTIM);
        if(iRet==-1)
        {
            flg=-1;
            perror("")
    
}


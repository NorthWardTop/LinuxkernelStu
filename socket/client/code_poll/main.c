#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "init.h"







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
  1.��    ��   : 2017��4��26��
    ��    ��   : chandler
    �޸�����   : �����ɺ���

*****************************************************************************/
int main( int argc, char *argv[] )
{
	int iListenFd,iConnFd;
	int iRet;
	iRet=InitServer();
	if(iRet<0)
	{
	  perror("InitServer ERR\n");
	  return -iRet;
	}
	g_ptServer->listenfd=InitSocket(IPADDRESS,PORT);
	listen(g_ptServer->listenfd,LISTENNUM);
	DoPollHandle(g_ptServer->listenfd);
    return 0;
}






















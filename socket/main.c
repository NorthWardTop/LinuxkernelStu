
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

//��ʽ�׽���, ���ݱ��׽���, ԭʼ�׽���
//ͷע��fi,
int main(int argc,char** argv)
{
    //printf("dsjadh");
    int skfd;//sock������
    int cnfd;//���Ӿ��
    int port;//�˿ں�
    int addrLen=sizeof(struct sockaddr_in);//��ַ����
    //��������ַ�Ϳͻ��˵�ַ�ṹ
    struct sockaddr_in srvAddr,cltAddr;
    
    char hello[]="hello, I am server";
    //��������2�����߶˿ں�С��0
    if(2!=argc || ((port=atoi(argv[1]))<0))
    {
        printf("%s, port\n",argv[0]);
        exit(1);
    }

    //������ʽ�׽���
    skfd=socket(AF_INET,SOCK_STREAM,0);
    //���÷������˵�ַ�ṹ
    srvAddr.sin_family=AF_INET;//ipv4Э����
    srvAddr.sin_addr.s_addr=htonl(INADDR_ANY);//ת��Ϊ�����ֽ���
    srvAddr.sin_port=htons(port);//�˿������ֽ���->�����ֽ���
    //���׽��ֺ͵�ַ��Ϣ��
    bind(skfd,(struct sockaddr*)(&srvAddr),sizeof(struct sockaddr));

    //����,���������Ϊ4
    listen(skfd,4);
    //
    while(1)
    {
        //���ܿͻ��˵�����,��������
        addrLen=sizeof(struct sockaddr_in);
        cnfd=accept(skfd,(struct sockaddr*)(&cltAddr),&addrLen);
        printf("connect from %s:%u ...\n",inet_ntoa(cltAddr.sin_addr),\
            ntohs(cltAddr.sin_port));
        write(cnfd,hello,strlen(hello));//�����Ӿ����д������
        close(cnfd);//�ر�����
    }
    close(skfd);
    exit(0);
}
























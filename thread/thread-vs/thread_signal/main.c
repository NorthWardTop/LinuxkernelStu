#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

/*
�źŷ��ͽ��ܴ�������: ��ǰ�߳��ڰ��źŴ�����signal(�ź�, ����)->
				  �����߳���ǰ�̷߳����ź�pthread_kill(�߳�id, �ź�)->
				  �߳����հ󶨵ĺ������д���void (*sighandler_t)(int)
�ź�������������: 


�źŰ󶨺���
	 typedef void (*sighandler_t)(int);
     sighandler_t signal(int signum, sighandler_t handler);

�̼߳䷢���ź�
	 int pthread_kill(pthread_t thread, int sig);
�߳���������(�����ź�)
	int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

*/


void* thread_func(void* arg)
{
	printf("I am first thread, I will receive from main thread signal!\n");
	SIGUSR1

	int ret = errno;
	pthread_exit(ret);
	return NULL;
}

int main(int argc, const char* argv[])
{
	int* pret = (int*)malloc(sizeof(int));
	pthread_t tid = -1;
	pthread_create(&tid, NULL, thread_func, NULL);


	pthread_join(tid, &pret);
}
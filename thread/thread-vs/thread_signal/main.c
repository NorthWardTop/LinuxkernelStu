#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>



/*
�źŷ��ͽ��ܴ�������: ��ǰ�߳��ڰ��źŴ�����signal(�ź�, ����)->
				  �����߳���ǰ�̷߳����ź�pthread_kill(�߳�id, �ź�)->
				  �߳����հ󶨵ĺ������д���void (*sighandler_t)(int)
�ź�������������: 
	   int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
    �� sigprocmask ����
	how:  SIG_BLOCK    ���ڶ����źż� ����Ϊ������Щ�ź�
		  SIG_UNBLOCK   ���ڶ����źż��е��źŴ����μ�����ɾ��
		  SIG_SETMASK   ��ռ���Σ�ֱ�ӽ��ź����μ�����Ϊ�ڶ����źż�
	oldset:  ����������, �Ա�ָ�
	����SIGKILL  SIGSTOP�ź��޷�����

�źŰ󶨺���
	 typedef void (*sighandler_t)(int);
     sighandler_t signal(int signum, sighandler_t handler);

�̼߳䷢���ź�
	 int pthread_kill(pthread_t thread, int sig);
�߳���������(�����ź�)
	int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);

*/

//�źŴ�����
void handle_usr1(int sig)
{
	printf("handle_usr1: thread %lu recive signal %d\n", pthread_self(), sig);
	return;
}


//û�б���ֹ�κ��źŵ��߳�
void* thread_func(void* arg)
{
	printf("thread_func: I am %lu thread, I will receive from main thread signal!\n", pthread_self());
	//SIGUSR1
	signal(SIGUSR1, handle_usr1);
	int* ret = (int*)malloc(sizeof(int));
	*ret = 1111;
	sleep(2);
	pthread_exit(ret);
	return NULL;
}


//����ֹSIGUSR2�źŵ��߳�
void* thread_func2(void* arg)
{
	printf("thread_func2: I am %lu thread, I will not receive signal from main thread!\n", pthread_self());
	//SIGUSR1
	signal(SIGUSR2, handle_usr1);
	sigset_t set;
	sigfillset(&set);
	sigdelset(&set, SIGUSR2);
	pthread_sigmask(SIG_SETMASK, &set, NULL);
	int* ret = (int*)malloc(sizeof(int));
	*ret = 2222;
	sleep(3);
	pthread_exit(ret);
	return NULL;
}

/**
ʵ�ֹ���:
	���̴߳��������̲߳��ֱ��������̷߳���SIGUSR1��SIGUSR2�ź�
	�߳�thread_func�������κ��ź�, ��handle_usr1������
	�߳�thread_func2����SIGUSR2�ź�, ��handle_usr1������
	�����߳��Ƿ����handle_usr1�����ж��Ƿ������źųɹ�
*/
int main(int argc, const char* argv[])
{
	int* pret = NULL;
	pthread_t tid = -1, tid2=-1;
	if (pthread_create(&tid, NULL, thread_func, NULL) < 0)
		perror("thread create failed!\n");
	if (pthread_create(&tid2, NULL, thread_func2, NULL) < 0)
		perror("thread create failed!\n");
	sleep(5);//�ȴ������̰߳��źź���
	printf("%lu,%lu\n", tid, tid2);
	//���߳�1�����Զ����ź�1
	if (pthread_kill(tid, SIGUSR1) != 0)
		perror("send SIGUSR1 failed!\n");
	//���߳�2�����ź�2
	if (pthread_kill(tid2, SIGUSR2) != 0)
		perror("send SIGUSR2 failed!\n");

	sleep(5);
	pthread_join(tid, (void**)&pret);
	printf("thread1 return %d\n", *pret);
	pthread_join(tid2, (void**)&pret);
	printf("thread1 return %d\n", *pret);
	
	if(pret)
		free(pret);
	return 0;
}



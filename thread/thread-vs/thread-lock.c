/*
����:pthread_mutex_t lock
	��ʽ1 int pthread_mutex_init(pthread_mutex_t *restrict mutex,����
           const pthread_mutexattr_t *restrict attr);
	��ʽ2 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	�ͷ�:
	pthread_mutex_destroy�ͷ�
	����/�޸�
	pthread_mutex_lock ��������
	pthread_mutex_trylock ����������
	pthread_mutex_unlock ��������������
*/

/**
���̴߳�����������
���̴߳�������
	�������ͬһ��������Դ
*/
#include <stdio.h>
#include <stdlib.h>
//#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define BUF_SIZE  1024
char buf[BUF_SIZE];

void* handle_thread(void* arg);

int main()
{
	pthread_t tid;
	pthread_mutex_t mutex;
	char c;
	int ret = -1;
	void* thread_ret;
	ret=pthread_create(&tid, NULL, handle_thread, &mutex);
	if (ret < 0)
		perror("create thread failed\n");
	pthread_mutex_lock(&mutex);
	for (int i = 0; (c = getchar()) != 'q' && i<1024; ++i)
		buf[i]=c;
	pthread_mutex_unlock(&mutex);

	pthread_mutex_lock(&mutex);
	printf("main thread writed public data area:\n");
	puts(buf);
	pthread_mutex_unlock(&mutex);
	pthread_join(tid, &thread_ret);
}

//���ݴ����߳�
//����ǰ�ַ�ASCII��++
void* handle_thread(void* arg)
{
	int ret = -1;
	pthread_mutex_lock((pthread_mutex_t*)arg);
	int i = 0;
	while (buf[i] != '\0')
		buf[i++]++;
	pthread_mutex_unlock((pthread_mutex_t*)arg);

	pthread_mutex_lock((pthread_mutex_t*)arg);
	printf("child thread writed public data area:\n");
	puts(buf);
	pthread_mutex_unlock((pthread_mutex_t*)arg);

	pthread_exit((void *)&ret);
	return 0;
}
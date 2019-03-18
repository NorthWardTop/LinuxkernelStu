/*������,��д��,������
��д��(�����������, �������д��дд����,
	1.��ʼ������pthread_rwlock_t
	int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
	int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
		const pthread_rwlockattr_t *restrict attr);
	pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
	2.����(����)����
	int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);��������
	int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);������, ֱ�ӷ���0�����
	3.����д
    int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);������
    int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);����
	4.����(���۶�/д)
	int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
		1.�����ʱ, ��������������, ��ϵͳ�������ֶ�����, ����ǰ�����̲߳�����ӵ����,���еĶ������ͷŲ��ǽ���״̬
		2.��д��ʱ, ��������д����
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <pthreadtypes.h>


#define BUF_SIZE	1024
#define THREAD_NUM	4

void* thread_one(void* arg);
void* thread_two(void* arg);
void* thread_three(void* arg);
void* thread_four(void* arg);

int main(int argc, const char* argv[])
{
	int ret=-1;
	char buf[BUF_SIZE] = "\0";
	pthread_t tid[THREAD_NUM] = { -1 };
	pthread_rwlock_t rwlock;
	//�̷߳���ֵ
	void* thrd_ret[THREAD_NUM] = { NULL };
	//�߳�ִ�к���ָ������
	void* (*thread_func_arr[THREAD_NUM])(void* arg) =
	{
		thread_one,
		thread_two,
		thread_three,
		thread_four
	};
	for (int i = 0; i < THREAD_NUM; ++i)
	{
		ret = pthread_create(&tid[i], NULL, thread_func_arr[i], &rwlock);
		if (ret < 0)
			perror("thread create failed!\n");
	}

	for (int i = 0; i < THREAD_NUM; ++i)
		pthread_join(tid[i], &thrd_ret);


	pthread_rwlock_destroy(&rwlock);
	return 0;
}

void * thread_one(void * arg)
{
	pthread_rwlock_t rwlock = *(pthread_rwlock_t*)arg;


	return NULL;
}

void * thread_two(void * arg)
{
	return NULL;
}

void * thread_three(void * arg)
{
	return NULL;
}

void * thread_four(void * arg)
{
	return NULL;
}

/*
������������pthread_cond_t
	��ʼ��������
	   int pthread_cond_destroy(pthread_cond_t *cond);
	   int pthread_cond_init(pthread_cond_t *restrict cond,
		   const pthread_condattr_t *restrict attr);
	   pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
	�ȴ���������
		int pthread_cond_timedwait(pthread_cond_t *restrict cond,
		pthread_mutex_t *restrict mutex,
		const struct timespec *restrict abstime);ָ��ʱ�䷶Χ�ڵȴ�
			int pthread_cond_wait(pthread_cond_t *restrict cond,
		pthread_mutex_t *restrict mutex);�ȴ�
	֪ͨ�ȴ������������߳�
	   int pthread_cond_broadcast(pthread_cond_t *cond);֪ͨ���������߳�
	   int pthread_cond_signal(pthread_cond_t *cond);֪ͨ��һ���߳�

*/

/*
�����뽫Ӧ��ʵ�����������ͻ�����ʵ��PV����

*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

#define BUF_SIZE	10
#define _DEBUG		1

typedef struct _obj_t
{
	int buf[BUF_SIZE];	//������(ѭ������)
	int readpos, writepos;//��ָ���дָ��
	pthread_mutex_t lock;//������
	pthread_cond_t noempty;//��������
	pthread_cond_t nofull;//������
	void(*put)(struct _obj_t* obj, int data);
	int(*get)(struct _obj_t* obj);
	struct _obj_t* _this;//�������ķ���, ��ָ�򱾽ṹ��ַ
}obj_t;


void obj_init(obj_t* obj);//��ʼ������
void put(obj_t* obj, int data);//����ķ���һ����
int get(obj_t* obj);//����ķ��ز�ɾ��һ����
void* producer(void* obj);	//�������߳�
void* consumer(void* obj);	//�������߳�

int main(int argc, const char* argv[])
{
	pthread_t tid1, tid2;
	obj_t obj;
	void* thread_ret1;
	void* thread_ret2;

	pthread_create(&tid1, NULL, producer, &obj);
	pthread_create(&tid2, NULL, consumer, &obj);
	if (tid1 < 0 || tid2 < 0)
		perror("thread create failed!\n");
	pthread_join(tid1, &thread_ret1);
	pthread_join(tid1, &thread_ret2);
	printf("thread return:%d, %d\n", *(int*)thread_ret1, *(int*)thread_ret1);

}

void obj_init(obj_t* obj)//��ʼ������
{
	obj->get = get;
	obj->put = put;
	obj->readpos = 0;
	obj->writepos = 0;
	pthread_mutex_init(&obj->lock, NULL);
	pthread_cond_init(&obj->noempty, NULL);
	pthread_cond_init(&obj->nofull, NULL);
	obj->_this = obj;
}

//����ķ���һ������(&����,����)
void put(obj_t * obj, int data)
{
	pthread_mutex_lock(&obj->lock);//�ӻ�����
	//��������������ʱ�����ѭ��wait
	while ((obj->writepos + 1) % BUF_SIZE == obj->readpos)
	{
		printf("waiting no full signal...\n");
		pthread_cond_wait(&obj->nofull, &obj->lock);//wait֮ǰȷ���Ǳ��߳��Ѿ�����������
	}
	//�ȴ���ɺ󻺳����Ѿ�����, ����data
	obj->writepos = (++obj->writepos) % BUF_SIZE;
	obj->buf[obj->writepos] = data;
	//���ѵ�һ���ȴ����յ��߳�, ���û���̵߳ȴ�(��������������)��������
	pthread_cond_signal(&obj->noempty);
	pthread_mutex_unlock(&obj->lock);//�⻥����
}

int get(obj_t * obj)
{
	int data = 0;
	pthread_mutex_lock(&obj->lock);
	//���������ǿյ�, ѭ���ȴ������ź�
	while (obj->writepos == obj->readpos)
	{
		printf("waiting no empty signal...\n");
		pthread_cond_wait(&obj->noempty, &obj->lock);
	}
	//�����պ�
	data = obj->buf[obj->readpos];
	obj->readpos = (++obj->readpos) % BUF_SIZE;
	pthread_mutex_unlock(&obj->lock);
	return data;
}

void * producer(void * obj)
{
	int t = 0;
	void* ret;
	for (int i = 0; i < 10; ++i)
	{
		t = rand() % 4 + 1;//�ȴ�1-5��
		printf("producer sleep %ds\nput the %d product\n", t, i);
		put(obj, i);
#if _DEBUG
		printf("::%d", i);
#endif
	}
	printf("producer exit!\n");
	ret = errno;
	pthread_exit(ret);
	return NULL;
}

void * consumer(void * obj)
{
	int t = 0;
	void* ret;
	int getval;
	for (int i = 0; i < 10; ++i)
	{
		t = rand() % 4 + 1;//�ȴ�1-5��
		getval = get(obj);
		printf("consumer sleep %ds\nget the %d product\n", t, getval);
	}
	printf("producer exit!\n");
	ret = errno;
	pthread_exit(ret);
	return NULL;
}

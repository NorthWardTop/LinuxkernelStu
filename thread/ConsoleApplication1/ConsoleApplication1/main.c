/*
 * @Author: northward
 * @Github: https://github.com/northwardtop
 * @Date: 2019-02-14 19:37:41
 * @LastEditors: northward
 * @LastEditTime: 2019-02-15 21:30:28
 * @Description: ����pthread_key_create()
 * int pthread_key_create (pthread_key_t *__key, void (*__destr_function) (void *))
 *      �������߳̾���˽������key
 *      ��ͬ�߳̿���ʹ��ͬ��������, ���Ǿ��в�ͬ�ĵ�ַ�Ϳռ�
 *      ��TSD�ط���, ע��(pthread_key_delete(key))���ص���,
 *      ע�������������߳��Ƿ�ʹ����, ����������NULL
 *      �߳��˳�ʱ����ò���������ָ��
 *      �������麯��, ͬ������ͬ��ʵ�ַ�����ͬ
 * ��д˽������
 *      int pthread_setspecific
 *      void* pthread_getspecific
 * ɾ��˽������
		
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

 //����˽�����ݱ���ṹ��
typedef struct _Private_Data
{
	int x;
	int y;
} private_data_t;

/**
 * @description:
 * @param {type}
 * @return:
 */
void main_thread(void *key)
{
	printf("this is my main thread, thread id: %lu, my private data is: %d\n",
		pthread_self(), ((private_data_t *)key)->x);
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void *child_thread1(void *arg)
{
	private_data_t setval;
	setval.x = 55;
	setval.y = 55;

	printf("child thread 1, setting key 55\n");
	printf("before change key: %d, %d\n", \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->x, \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->y);
	pthread_setspecific(*(pthread_key_t *)arg, &(setval.x)); //����ֵΪ55
	printf("before change key: %d, %d\n", \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->x, \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->y);
}

/**
 * @description:
 * @param {type}
 * @return:
 */
void *child_thread2(void *arg)
{
	private_data_t setval;
	setval.x = 66;
	setval.y = 66;

	printf("child thread 2, setting key 66\n");
	printf("before change key: %d, %d\n", \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->x, \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->y);
	pthread_setspecific(*(pthread_key_t *)arg, &(setval.x)); //����ֵΪ66
	printf("before change key: %d, %d\n", \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->x, \
		((private_data_t *)pthread_getspecific(*(pthread_key_t*)arg))->y);
}

/**
 * @description:
 * @param {type}
 * @return:
 */
int main(int argc, char const *argv[])
{
	pthread_key_t key; //����һ��˽�����ݱ���
	pthread_t tid1, tid2;
	private_data_t test;
	test.x = 1;
	test.y = 2;
	//�������߳�
	pthread_key_create(&key, main_thread);
	pthread_setspecific(key, &test); //�޸�keyΪ�Զ�������
	//�����������߳�
	pthread_create(&tid1, NULL, child_thread1, (pthread_key_t*)&key);
	pthread_create(&tid2, NULL, child_thread2, (pthread_key_t*)&key);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_key_delete(key);

	return 0;
}


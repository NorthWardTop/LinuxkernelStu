/*
�߳����Խ��������:�����߳��ܹ����뵽����Դ(ջ�ռ���Ϣ)Ȩ��
typedef struct
	{
		   int                           detachstate;     �̵߳ķ���״̬ ���Ƿ���Ա��ȴ�pthread_join
														PTHREAD_CREATE_JOINABLE   able
														PTHREAD_CREATE_JOINUNABLE unable

		   int                          schedpolicy;   �̵߳��Ȳ���  ���õ�ǰ�̵߳ĵ��Ȳ���
														����FIFO,�ȴ���������
														ʱ��Ƭ
														���ȼ�

		   struct sched_param      schedparam;   �̵߳ĵ��Ȳ���  ����ȵ�ǰ(�ϸ�����)���Դ������

		   int                          inheritsched;    �̵߳ļ̳��� �Ƿ�̳д����̵߳ĵ��Ȳ���

		   int                          scope;          �̵߳�������
		   size_t                      guardsize; �߳�ջĩβ�ľ��仺������С
												  Ĭ��ֵ PAGESIZE

		   int                         stackaddr_set;  �����߳�ջ�Ļ���ַ
		   void *                     stackaddr;      �߳�ջ��λ��
		   size_t                      stacksize;       �߳�ջ�Ĵ�С
	}pthread_attr_t;

	pthread_attr_t  attr

	Linuxϵͳ��pthread_attr_t�������ǲ�͸��,����attr.xxx����,ֻ��API����

   ֻ��ʹ���ض���ϵͳ�ṩ��API�������������
   ��ʼ���߳�����
   ����/��ȡ detachstate
   ����/��ȡ �߳�ջ������
		1.�������ջ�Ĵ�С����
		2.�������stack�ĵ�ַ
		3.�������ջ�ı�����

	�߳�ID������
		pthread_t pthread_self(void)

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int main(int argc, const char* argv[])
{

}

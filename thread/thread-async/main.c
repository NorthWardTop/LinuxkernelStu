/*
�߳�ͬ��,�������źż���,�źű�����ӵ��
1.ÿ���߳̿��������̷߳����ź�(pthread_kill�ź�)
2.ÿ���߳̿������ñ��߳��Լ����ź����μ���(���߳�ӵ��),��ʼֵ�Ǽ̳��ڸ��߳�
3.ͬ���������е��̹߳����ĳ�źŴ�����(ִ�����һ�����õĴ�����)
4.���������������ֹ�ź�, ������������߳���ֹ
1.�źŷ��ͺ���
	//��sig=0ʱ��������߳��Ƿ����,�������ź�,���ڻ�ɹ�����0,���ɹ������ڷ���errno
	int pthread_kill(pthread_t thread, int sig);
2.�����ź���������
	int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);
	how: SIG_BLOCK(�ڶ������ź�����λ�������) SIG_UNBLOCK(�ڶ�����������λ�������) SIG_SETMASK(ֱ������)
	�����źŲ������κ��޸Ĳ�������(SIGKILL SIGSTOP)
3.�����ź�ִ�к���
	 int sigaction(int signum, const struct sigaction *act,
                     struct sigaction *oldact);


	

��ҵ:
*/

#include <pthread.h>
#include <dksk>
#include <signal.h>

int main(int argc, const char* argv[])
{
	pthread_kill()
}


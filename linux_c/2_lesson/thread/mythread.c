#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void* thread_run(void* arg)
{
	while (1){
		printf("I am %s, pid : %d, my thread id is : %p\n", (char*)arg, getpid(), pthread_self());
		sleep(1);
	}
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thread_run, (void*)"thread 1");
	while (1){
		printf("I am main thread ：%p, new thread : %p, pid : %d\n", pthread_self(), tid, getpid());
		sleep(2);
	}
}

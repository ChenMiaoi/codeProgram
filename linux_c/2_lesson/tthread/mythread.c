#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int a = 10;

void* thread_run(void* arg)
{
    //pthread_detach(pthread_self());
    while (1) {
        printf("%s : %lx, pid : %d\n", (char *) arg, pthread_self(), getpid());
        printf("%s global var : %d, %p\n", (char*)arg, a, &a);
        sleep(1);
    }
    //pthread_exit((void*)10);
    //exit(10);
    //int a = 10;
    //a /= 0;
    return (void*)10;
}

int main()
{
    pthread_t tid;
    pthread_t tid1;
    pthread_create(&tid, NULL, thread_run, "thread0");
    pthread_create(&tid1, NULL, thread_run, "thread1");

    printf("main : %lx, pid : %d\n", pthread_self(), getpid());
    printf("before : %s global var : %d, %p\n", "main", a, &a);
    sleep(10);
    a = 100;
    //pthread_cancel(tid);
    printf("after : %s global var : %d, %p\n", "main", a, &a);
    printf("new thread %lx be cancel!\n", tid);

    void* ret = NULL;
    pthread_join(tid, &ret);
    printf("thread quit code : %d\n", (long long)ret);
    return 100;
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int ticket = 10000;
pthread_mutex_t lock;

void* get_ticket(void* arg)
{
    usleep(1000);
    int no = (int)arg;
    while (1){
        pthread_mutex_lock(&lock);
        if (ticket > 0){
            usleep(1000);
            printf("thread %d get the ticket, no : %d\n", no, ticket);
            ticket--;
            pthread_mutex_unlock(&lock);
        } else{
            pthread_mutex_unlock(&lock);
            break;
        }
    }
}

int main()
{
    pthread_t tid[4];
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < 4; ++i) {
        pthread_create(tid + i, NULL, get_ticket, (void*)i);
    }
    for (int i = 0; i < 4; ++i) {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    return 0;
}
#ifndef THREADPOOL_THREADPOOL_HPP
#define THREADPOOL_THREADPOOL_HPP

#include <iostream>
#include <pthread.h>
#include <queue>
#include <cmath>
#include <unistd.h>

#define NUM 10

class Task {
public:
    int base;
public:
    Task(){}
    Task(int _b) :base(_b) {}
    void Run(){
        std::cout << "thread is[" << pthread_self() << "]Task running...done : base # " << base << " pow is # " << pow(base, 2) << std::endl;
    }
    ~Task(){}
};

class ThreadPool {
public:
    ThreadPool(int _max = NUM) :max_num(_max), quit(false)
    {}

    static void* Rountine(void* arg){
        ThreadPool* this_p = (ThreadPool*)arg;
        while (!this_p->quit){
            this_p->LockQueue();
            while (!this_p->quit && this_p->IsEmpty()){
                this_p->ThreadWait();
            }
            Task t;
            if (!this_p->quit && this_p->IsEmpty()){
                this_p->Get(t);
            }
            this_p->UnlockQueue();
            t.Run();
        }
    }

    //server
    void Put(Task& in){
        LockQueue();
        q.push(&in);
        UnlockQueue();
        ThreadWakeUp();
    }
    //thread
    void Get(Task& out){
        Task* t = q.front();
        q.pop();
        out = *t;
    }

    void ThreadPoolInit(){
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&cond, nullptr);

        pthread_t t;
        for (int i = 0; i < max_num; i++){
            pthread_create(&t, nullptr, Rountine, this);
        }
    }

    ~ThreadPool(){
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&cond);
    }

public:
    void LockQueue(){
        pthread_mutex_lock(&lock);
    }
    void UnlockQueue(){
        pthread_mutex_unlock(&lock);
    }
    bool IsEmpty(){
        return q.size() == 0;
    }
    void ThreadWait(){
        pthread_cond_wait(&cond, &lock);
    }
    void ThreadWakeUp(){
        /*
         * 群体唤醒
         * if (low_water){
         *      pthread_cond_broadcast(&cond);
         * }
         * */
        //单个唤醒
        pthread_cond_signal(&cond);
    }
    void ThreadQuit(){
        if (!IsEmpty()){
            std::cout << "Task queue in un-empty" << std::endl;
            return;
        }
        quit = true;
        ThreadsWakeUp();
    }
    void ThreadsWakeUp(){
        pthread_cond_broadcast(&cond);
    }
private:
    std::queue<Task*> q;    //防止一瞬间任务过多，使用Task*
    int max_num;
    pthread_mutex_t lock;
    pthread_cond_t cond;    //只让消费者进行, thread pool thread
    bool quit;
};
#endif //THREADPOOL_THREADPOOL_HPP

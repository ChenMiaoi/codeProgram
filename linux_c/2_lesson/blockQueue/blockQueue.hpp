#ifndef BLOCKQUEUE_BLOCKQUEUE_HPP
#define BLOCKQUEUE_BLOCKQUEUE_HPP

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <queue>

class Task{
public:
    int x;
    int y;
public:
    Task(){}
    Task(int _x, int _y) :x(_x), y(_y)
    {}
    int Run(){
        return x + y;
    }
    ~Task()
    {}
};

class BlockQueue{
public:
    BlockQueue(size_t _cap) :cap(_cap)
    {
        pthread_mutex_init(&lock, nullptr);
        pthread_cond_init(&c_cond, nullptr);
        pthread_cond_init(&p_cond, nullptr);
    }

    void Put(Task t){
        LockQueue();
        while (IsFull()){
            WakeUpComsumer();
            ProductorWait();
        }
        q.push(t);
        UnLockQueue();
    }

    void Get(Task& t){
        LockQueue();
        while (IsEmpty()){
            WakeUpProductor();
            ComsumerWait();
        }
        t = q.front();
        q.pop();
        UnLockQueue();
    }

    ~BlockQueue(){
        pthread_mutex_destroy(&lock);
        pthread_cond_destroy(&c_cond);
        pthread_cond_destroy(&p_cond);
    }
private:
    bool IsFull(){
        return q.size() >= cap;
    }
    bool IsEmpty(){
        return q.empty();
    }

    void LockQueue(){
        pthread_mutex_lock(&lock);
    }
    void UnLockQueue(){
        pthread_mutex_unlock(&lock);
    }

    void WakeUpComsumer(){
        pthread_cond_signal(&c_cond);
    }
    void WakeUpProductor(){
        pthread_cond_signal(&p_cond);
    }

    void ComsumerWait(){
        pthread_cond_wait(&c_cond, &lock);
    }
    void ProductorWait(){
        pthread_cond_wait(&p_cond, &lock);
    }
private:
    std::queue<Task> q;
    pthread_mutex_t lock;
    pthread_cond_t c_cond;  //将来条件不满足时，消费者在该条件变量下等待
    pthread_cond_t p_cond;  //将来条件不满足时，生产者在该条件变量下等待
    size_t cap;
};
#endif //BLOCKQUEUE_BLOCKQUEUE_HPP

#ifndef RINGQUEUE_RINGQUEUE_HPP
#define RINGQUEUE_RINGQUEUE_HPP

#include <iostream>
#include <pthread.h>
#include <vector>
#include <semaphore.h>
#include <unistd.h>

#define NUM 10

class RingQueue{
public:
    RingQueue(int _cap = NUM) :max_cap(_cap), c_index(0), p_index(0), v(_cap)
    {
        sem_init(&sem_blank, 0, max_cap);
        sem_init(&sem_data, 0, 0);
    }

    void Get(int& out){
        P(sem_data);
        //消费
        out = v[c_index];
        c_index++;
        c_index %= max_cap;
        V(sem_blank);
    }
    void Put(const int& in){
        P(sem_blank);
        //生产
        v[p_index] = in;
        p_index++;
        p_index %= max_cap;
        V(sem_data);
    }

    ~RingQueue(){
        sem_destroy(&sem_data);
        sem_destroy(&sem_blank);
    }
private:
    void P(sem_t& s){
        sem_wait(&s);
    }
    void V(sem_t& s){
        sem_post(&s);
    }
private:
    std::vector<int> v;
    size_t max_cap;
    sem_t sem_blank;    //生产者
    sem_t sem_data;     //消费者
    int c_index;        //消费者
    int p_index;        //生产者
};
#endif //RINGQUEUE_RINGQUEUE_HPP

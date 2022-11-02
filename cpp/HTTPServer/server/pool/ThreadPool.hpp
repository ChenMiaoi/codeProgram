#ifndef HTTPSERVER_THREADPOOL_HPP
#define HTTPSERVER_THREADPOOL_HPP

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <pthread.h>
#include "Task.hpp"
#include "../src/Log.hpp"

#define  NUM 5

class ThreadPool {
private:
    ThreadPool(int num = NUM) : _num(num), _stop(false) {
        pthread_mutex_init(&_lock, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    ThreadPool(const ThreadPool&) {}
public:
    ~ThreadPool() {
        pthread_mutex_destroy(&_lock);
        pthread_cond_destroy(&_cond);
    }
public:
    static ThreadPool* getInstance() {
        pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
        if (_single_instance == nullptr) {
            pthread_mutex_lock(&mtx);
            if (_single_instance == nullptr) {
                _single_instance = new ThreadPool();
                _single_instance->InitThreadPool();
            }
            pthread_mutex_unlock(&mtx);
        }
        return _single_instance;
    }

    bool IsStop() {
        return true;
    }

    bool TaskQueueIsEmpty() { return _task_queue.size() == 0; }

    void Lock() { pthread_mutex_lock(&_lock); }

    void UnLock() { pthread_mutex_unlock(&_lock); }

    static void* Routine(void* args) {
        ThreadPool* tp = (ThreadPool*)args;
        while (true) {
            Task t;
            tp->Lock();
            while (tp->TaskQueueIsEmpty()) {
                tp->ThreadWait(); // 醒来后，一定是占有互斥锁的
            }
            tp->PopTask(t);
            tp->UnLock();
            t.ProcessOn();
        }
    }

    bool InitThreadPool() {
        for (int i = 00; i < _num; i++) {
            pthread_t tid;
            if (pthread_create(&tid, nullptr, Routine, this) != 0) {
                LOG(FATAL, "create thread pool error!");
                return false;
            }
        }
        LOG(INFO, "create thread pool success!");
        return true;
    }

    void ThreadWait() { pthread_cond_wait(&_cond, &_lock); }

    void ThreadWeakUp() { pthread_cond_signal(&_cond); }

    void PushTask(const Task& task) { //in
        this->Lock();
        _task_queue.push(task);
        this->UnLock();
        this->ThreadWeakUp();
    }

    void PopTask(Task& task) { //out
        task = _task_queue.front();
        _task_queue.pop();
    }
private:
    int _num;
    bool _stop;
    std::queue<Task> _task_queue;
    pthread_mutex_t _lock;
    pthread_cond_t _cond;
    static ThreadPool* _single_instance;
    //std::mutex _mtx;
};

ThreadPool* ThreadPool::_single_instance = nullptr;

#endif //HTTPSERVER_THREADPOOL_HPP

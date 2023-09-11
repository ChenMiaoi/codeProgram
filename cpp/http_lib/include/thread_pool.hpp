#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "def.hpp"
#include "task_queue.hpp"

#include <cstddef>
#include <cassert>
#include <functional>
#include <list>
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>

namespace httplib {
    class ThreadPool: public TaskQueue {
    public:
        explicit ThreadPool(size_t n);
        ThreadPool(const ThreadPool&) = delete;
        ~ThreadPool() override = default;

        auto enqueue(std::function<void(void)> fn) -> void override;
        auto shutdown() -> void override;
    private:
        struct worker;
        friend struct worker;

        std::vector<std::thread> _threads;
        std::list<std::function<void(void)>> _jobs;

        bool _shutdown;
        std::mutex _mtx;
        std::condition_variable _cond;
    };
}

#endif //!__THREAD_POOL_H__
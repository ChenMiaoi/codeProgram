#include "../thread_pool.hpp"

namespace httplib {
    struct ThreadPool::worker {
        explicit worker(ThreadPool& pool): _pool(pool) {}

        void operator() () {
            while (true) {
                std::function<void(void)> fn;
                {
                    std::unique_lock<std::mutex> lock(_pool._mtx);
                    _pool._cond.wait(lock, [&] {
                        return !_pool._jobs.empty() || _pool._shutdown;
                    });
                    if (_pool._shutdown && _pool._jobs.empty()) break;

                    fn = std::move(_pool._jobs.front());
                    _pool._jobs.pop_front();
                }
                assert(static_cast<bool>(fn) == true);
                fn();
            }
        }

        ThreadPool& _pool;
    };

    ThreadPool::ThreadPool(size_t n): _shutdown(false) {
        while (n) {
            _threads.emplace_back(worker(*this));
            n--;
        }
    }

    auto ThreadPool::enqueue(std::function<void ()> fn) -> void {
        {
            std::unique_lock<std::mutex> lock(_mtx);
            _jobs.emplace_back(std::move(fn));
        }
        _cond.notify_one();
    }
    auto ThreadPool::shutdown() -> void {
        {
            std::unique_lock<std::mutex> lock(_mtx);
            _shutdown = true;
        }
        _cond.notify_all();

        for (auto& thread : _threads)
            thread.join();
    }
}
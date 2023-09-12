#ifndef __TASK_QUEUE_H__
#define __TASK_QUEUE_H__

#include "def.hpp"
#include <functional>

namespace httplib {
    class TaskQueue {
    public:
        TaskQueue() = default;
        virtual ~TaskQueue() = default;

        virtual auto enqueue(std::function<void(void)> fn) -> void = 0;
        virtual auto shutdown() -> void = 0;
        // virtual auto on_idle()  -> void = 0;
    };
}

#endif //!__TASK_QUEUE_H__
mod context;
mod switch;
#[allow(clippy::module_inception)]
mod task;

use crate::config::MAX_APP_NUM;
use crate::loader::{get_num_app, init_app_cx};
use crate::sync::UPSafeCell;
use lazy_static::*;
use switch::__switch;
pub use task::{TaskControlBlock, TaskStatus};
pub use context::TaskContext;

pub struct TaskManager {                                                                            // 任务管理的结构体
    num_app: usize,                                                                                 // 任务数
    inner: UPSafeCell<TaskManagerInner>,                                                            // 确保安全以及封装任务信息
}

pub struct TaskManagerInner {                                                                       // 任务管理的封装
    tasks: [TaskControlBlock; MAX_APP_NUM],                                                         // 任务队列
    current_task: usize,                                                                            // 当前任务索引
}

lazy_static! {
    pub static ref TASK_MANAGER: TaskManager = {                                                    // 定义任务管理变量
        let num_app = get_num_app();                                                        // 获取任务数
        let mut tasks = [TaskControlBlock {                                // 任务队列的初始化
            task_cx: TaskContext::zero_init(),
            task_status: TaskStatus::UnInit,                                                        // 初始化任务状态
        }; MAX_APP_NUM];
        for (i, task) in tasks.iter_mut().enumerate() {
            task.task_cx = TaskContext::goto_restore(init_app_cx(i));                               // 构建任务，得到任务的上下文
            task.task_status = TaskStatus::Ready;                                                   // 设置任务状态
        }
        TaskManager {                                                                               // 返回该任务列表
            num_app,
            inner: unsafe {
                UPSafeCell::new(TaskManagerInner {
                    tasks,
                    current_task: 0,
                })
            },
        }
    };
}

impl TaskManager {
    fn run_first_task(&self) -> ! {                                                                 // 开始运行
        let mut inner = self.inner.exclusive_access();                   // 获取任务管理信息
        let task0 = &mut inner.tasks[0];                                    // 获取第一个任务
        task0.task_status = TaskStatus::Running;                                                    // 设置第一个任务状态
        let next_task_cx_ptr = &task0.task_cx as *const TaskContext;           // 将第一个任务设置为下一个任务
        drop(inner);                                                                            // 释放任务管理信息
        let mut _unused = TaskContext::zero_init();                                                 // 设置用于交换的不被使用的任务
        unsafe {
            __switch(&mut _unused as *mut TaskContext, next_task_cx_ptr);      // 交换任务开始执行
        }
        panic!("unreachable in run_first_task!");
    }

    fn mark_current_suspended(&self) {                                                              // 标志当前任务中断
        let mut inner = self.inner.exclusive_access();                  // 获取任务管理信息
        let current = inner.current_task;                                                   // 获取当前任务
        inner.tasks[current].task_status = TaskStatus::Ready;                                       // 将状态从Run改为Ready
    }

    fn mark_current_exit(&self) {                                                                   // 标志当前任务退出
        let mut inner = self.inner.exclusive_access();
        let current = inner.current_task;
        inner.tasks[current].task_status = TaskStatus::Exited;                                      // 将状态改为Exit
    }

    fn find_next_task(&self) -> Option<usize> {                                                     // 获取下一个任务
        let inner = self.inner.exclusive_access();
        let current = inner.current_task;
        (current + 1..current + self.num_app + 1)                                                   // 在当前任务列表中寻找
            .map(|id| id % self.num_app)
            .find(|id| inner.tasks[*id].task_status == TaskStatus::Ready)                  // 当任务状态是Ready即可被记为下一个任务
    }

    fn run_next_task(&self) {                                                                       // 运行下一个任务
        if let Some(next) = self.find_next_task() {                                         // 如果能找到下一个任务
            let mut inner = self.inner.exclusive_access();
            let current = inner.current_task;
            inner.tasks[next].task_status = TaskStatus::Running;                                    // 将下一个任务的状态修改为Running
            inner.current_task = next;                                                              // 将任务管理中当前任务设置为下一个任务的标号
            let current_task_cx_ptr =                                           // 获取当前任务的上下文信息
                &mut inner.tasks[current].task_cx as *mut TaskContext;
            let next_task_cx_ptr =                                             // 获取下一个任务的上下文信息
                &inner.tasks[next].task_cx as *const TaskContext;
            drop(inner);                                                                        // 释放任务管理信息
            unsafe {
                __switch(current_task_cx_ptr, next_task_cx_ptr);                                    // 对当前任务和下一个任务进行交换
            }
        } else {
            panic!("All applications completed!");
        }
    }
}

pub fn run_first_task() {                                                                           // 外部接口，开始执行任务
    TASK_MANAGER.run_first_task();
}

fn run_next_task() {                                                                                // 外部接口，执行下一个任务
    TASK_MANAGER.run_next_task();
}

fn mark_current_suspended() {                                                                       // 外部接口，中断当前任务
    TASK_MANAGER.mark_current_suspended();
}

fn mark_current_exit() {                                                                            // 外部接口，退出当前任务
    TASK_MANAGER.mark_current_exit();
}

pub fn suspend_current_and_run_next() {                                                             // 外部接口，中断当前任务，执行下一个任务
    mark_current_suspended();
    run_next_task();
}

pub fn exit_current_and_run_next() {                                                                // 外部接口，退出当前任务，执行下一个任务
    mark_current_exit();
    run_next_task();
}
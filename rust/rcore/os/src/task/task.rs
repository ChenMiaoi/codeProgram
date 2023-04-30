use crate::config::MAX_SYSCALL_NUM;
use super::context::TaskContext;

#[derive(Copy, Clone)]
pub struct TaskControlBlock {                                       // 任务控制块
    pub task_status: TaskStatus,                                    // 任务状态
    pub task_cx: TaskContext,                                       // 任务上下文信息
    pub task_syscall_time: [u32; MAX_SYSCALL_NUM],                  // 任务调用时间
    pub task_start_time: usize,                                     // 任务起始时间
}

#[derive(Copy, Clone, PartialEq)]
pub enum TaskStatus {                                               // 任务状态
    UnInit,                                                         // 未初始化
    Ready,                                                          // 准备可以运行了
    Running,                                                        // 运行中
    Exited,                                                         // 退出
}
use super::context::TaskContext;

#[derive(Copy, Clone)]
pub struct TaskControlBlock {                                       // 任务控制块
    pub task_status: TaskStatus,                                    // 任务状态
    pub task_cx: TaskContext,                                       // 任务上下文信息
}

#[derive(Copy, Clone, PartialEq)]
pub enum TaskStatus {                                               // 任务状态
    UnInit,                                                         // 未初始化
    Ready,                                                          // 准备可以运行了
    Running,                                                        // 运行中
    Exited,                                                         // 退出
}
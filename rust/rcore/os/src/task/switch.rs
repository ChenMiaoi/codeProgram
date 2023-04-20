use super::context::TaskContext;
use core::arch::global_asm;

global_asm!(include_str!("switch.S"));

///! 实际上此处才是真正的切换任务的地方，trap只是进行了提权和交换上下文
extern "C" {
    pub fn __switch(
        current_task_cx_ptr: *mut TaskContext,                      // 当前任务上下文信息
        next_task_cx_ptr: *const TaskContext                        // 下一个任务上下文信息
    );
}
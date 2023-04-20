use log::trace;
use crate::{
    config::MAX_SYSCALL_NUM,
    task::{exit_current_and_run_next, suspend_current_and_run_next, TaskStatus},
    timer::get_time_ms,
};

#[repr(C)]                                                              // 兼容C语言的结构体布局，使其能够安全的传递給C函数或从C函数返回
#[derive(Debug)]
pub struct TimeVal {                                                    // 时间结构体
    pub sec: usize,                                                     // 秒
    pub usec: usize,                                                    // 微妙
}

#[allow(dead_code)]
pub struct TaskInfo {                                                   // 任务信息的结构体
    status: TaskStatus,                                                 // 任务当前状态
    syscall_times: [u32; MAX_SYSCALL_NUM],                              // syscall被任务调用的次数
    time: usize,                                                        // 任务运行的总时间
}

pub fn sys_exit(exit_code: i32) -> ! {                                  // 退出
    trace!("[kernel] Application exited with code {}", exit_code);
    exit_current_and_run_next();                                        // 退出当前程序，执行下一个程序
    panic!("Unreachable in sys_exit!");
}

pub fn sys_yield() -> isize {
    trace!("kernel: sys_yield");
    suspend_current_and_run_next();                                     // 中断当前程序，执行下一个程序
    0
}

pub fn sys_get_time(ts: *mut TimeVal, _tz: usize) -> isize {
    trace!("kernel: sys_get_time");
    let us = get_time_ms();                                     // 获取时钟计时
    unsafe {
        *ts = TimeVal {
            sec: us / 1_000_000,
            usec: us % 1_000_000,
        };
    }
    0
}

pub fn sys_task_info(_ti: *mut TaskInfo) -> isize {
    trace!("kernel: sys_task_info");
    -1
}
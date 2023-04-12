use log::trace;
use crate::batch::run_next_app;

pub fn sys_exit(exit_code: i32) -> ! {                              // 退出
    trace!("[kernel] Application exited with code {}", exit_code);
    run_next_app();
}
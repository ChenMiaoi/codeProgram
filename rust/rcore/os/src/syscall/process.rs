use log::trace;

pub fn sys_exit(exit_code: i32) -> ! {                              // 退出
    trace!("[kernel] Application exited with code {}", exit_code);
    // next app
}
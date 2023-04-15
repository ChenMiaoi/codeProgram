pub const SYSCALL_READ      : usize = 63;                                   // 读操作系统调用二进制数
pub const SYSCALL_WRITE     : usize = 64;                                   // 写操作系统调用二进制数
pub const SYSCALL_EXIT      : usize = 93;                                   // 退出操作系统调用二进制数

pub fn syscall(id: usize, args: [usize; 3]) -> isize {                      // 系统调用的通用函数，用该函数执行汇编
    let mut ret: isize;
    unsafe {
        core::arch::asm!(
            "ecall",                                                        // 调用ecall，进行提权
            inlateout("a0") args[0] => ret,                                 // 第一个参数作为返回值
            in("a1") args[1],
            in("a2") args[2],
            in("a7") id,                                                    // 调用的操作，由trap handler决定
        );
    }
    ret
}

pub fn sys_read(fd: usize, buffer: &mut [u8]) -> isize {
    syscall(
        SYSCALL_READ,
        [fd, buffer.as_ptr() as usize, buffer.len()]
    )
}

pub fn sys_write(fd: usize, buffer: &mut [u8]) -> isize {
    syscall(
        SYSCALL_WRITE,
        [fd, buffer.as_ptr() as usize, buffer.len()]
    )
}

pub fn sys_exit(exit_code: i32) -> ! {
    syscall(
        SYSCALL_EXIT,
        [exit_code as usize, 0, 0],
    );
    panic!("sys_exit nerver returns!");
}
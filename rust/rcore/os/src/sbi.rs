use core::arch::asm;

const SBI_SET_TIMER         : usize = 0;                                           // SBI中的时钟中断
const SBI_CONSOLE_PUTCHAR   : usize = 1;                                           // SBI中的终端输出字符
const SBI_SHUTDOWN          : usize = 8;                                           // SBI中的退出

fn sbi_call(which: usize, arg0: usize, arg1: usize, arg2: usize) -> usize {
    let mut ret: usize;
    unsafe {
        asm!(
            "li x16, 0",
            "ecall",                                                            // 只管ecall，特权调用后具体由trap handler来决定
            inlateout("a0") arg0 => ret,
            in("a1") arg1,
            in("a2") arg2,
            in("a7") which,
        );
    }
    ret
}

pub fn set_timer(timer: usize) {
    sbi_call(SBI_SET_TIMER, timer, 0, 0);
}

pub fn console_putchar(c: usize) {                                              // 调用SBI接口
    sbi_call(SBI_CONSOLE_PUTCHAR, c, 0, 0);
}

pub fn shutdown() -> ! {
    // crate::boards::QEMU_EXIT_HANDLE.exit_failure();
    sbi_call(SBI_SHUTDOWN, 0, 0, 0);
    panic!("It should shutdown");
}
use core::arch::asm;

const EXIT_SUCCESS: u32      = 0x5555;                      // 相当于exit(0)，qemu成功退出
const EXIT_FAILURE: u32      = exit_code_encode(1);   // 相当于exit(1)
const EXIT_FAILURE_FLAG: u32 = 0x3333;                      // qemu退出的标志
const EXIT_RESET: u32        = 0x7777;                      // qemu重置

const fn exit_code_encode(code: u32) -> u32 {
    (code << 16) | EXIT_FAILURE_FLAG
}

pub trait QEMUExit {
    fn exit(&self, code: u32) -> !;                         // 类似于exit(status)
    fn exit_success(&self) -> !;                            // 成功退出
    fn exit_failure(&self) -> !;                            // 失败退出
}

pub struct RISCV64 {                                        // riscv64的地址
    addr: u64,
}

impl RISCV64 {
    pub const fn new(addr: u64) -> Self {
        RISCV64 { addr }
    }
}

impl QEMUExit for RISCV64 {
    fn exit(&self, code: u32) -> ! {                        // 为riscv64实现退出
        let new_code = match code {
            EXIT_SUCCESS | EXIT_FAILURE | EXIT_RESET => code,
            _ => exit_code_encode(code),
        };
        unsafe {
            asm!(
                "sw {0}, 0({1})",                           // 将退出码保存到对应寄存器中
                in(reg)new_code, in(reg)self.addr
            );
            loop {
                asm!("wfi", options(nomem, nostack));       // wfi是休眠指令，同时通过选项禁止了内存和堆栈操作
            }
        }
    }
    fn exit_failure(&self) -> ! {
        self.exit(EXIT_FAILURE);
    }
    fn exit_success(&self) -> ! {
        self.exit(EXIT_SUCCESS);
    }
}

const VIRT_TEST: u64 = 0x00100000;                          // virt的退出地址
pub const QEMU_EXIT_HANDLE: RISCV64 = RISCV64::new(VIRT_TEST);
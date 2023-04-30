#[allow(unussed)]

pub const USER_STACK_SIZE   : usize = 4096;                                 // 用户栈大小
pub const KERNEL_STACK_SIZE : usize = 4096 * 2;                             // 内核栈大小
pub const KERNEL_HEAP_SIZE  : usize = 0x20000;                              // 内核堆大小
pub const MAX_APP_NUM       : usize = 16;                                   // 最大用户程序数量
pub const APP_BASE_ADDRESS  : usize = 0x80400000;                           // 用户程序基址
pub const APP_SIZE_LIMIT    : usize = 0x20000;                              // 用户程序最大地址

pub const MAX_SYSCALL_NUM   : usize = 500;                                  // 最大系统调用数
pub const CLOCK_FREQ        : usize = 12500000;                             // QEUM virt硬件时钟频率
pub const MEMORY_END        : usize = 0x88000000;                           // 最大应用内存终止

pub const PAGE_SIZE         : usize = 0x1000;                               // 页大小，4KB
pub const PAGE_SIZE_BITS    : usize = 0xc;                                  // 用12位比特来表示4KB
pub const TRAMPOLINE        : usize = usize::MAX - PAGE_SIZE + 1;           //
pub const TRAP_CONTEXT_BASE : usize = TRAMPOLINE - PAGE_SIZE;               //
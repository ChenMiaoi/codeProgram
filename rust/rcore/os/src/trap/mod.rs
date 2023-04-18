mod context;

use crate::batch::run_next_app;
use crate::syscall::syscall;
use core::arch::global_asm;
use riscv::register::{
    mtvec::TrapMode,
    scause::{self, Exception, Interrupt, Trap},
    sie, stval, stvec,
};
use crate::println;
pub use crate::trap::context::TrapContext;

global_asm!(include_str!("trap.S"));

pub fn init() {
    extern "C" {
        fn __alltraps();                                                    // 调用汇编中的__alltraps陷入内核，保存上下文寄存器，进入trap_handler函数
    }
    unsafe {
        // stvec寄存器用于存储陷阱处理程序的基地址
        // 其中，write方法能够将__alltraps的地址存入stvec中，采用直接处理的模式，该模式会直接跳转到指定地址进行处理
        // 而对应有一种TrapMode::Vector，会跳转到一个间接的地址进行处理
        stvec::write(__alltraps as usize, TrapMode::Direct);
    }
}

pub fn enable_timer_interrupt() {
    unsafe {
        // sie是riscv中的S模式下的中断使能
        sie::set_stimer();
    }
}

#[no_mangle]
pub fn trap_handler(cx: &mut TrapContext) -> &mut TrapContext {
    let scause = scause::read();                                    // 读取scause寄存器
    let stval = stval::read();                                       // 读取stval寄存器，用于存储发生异常指令的地址
    match scause.cause() {                                                   // 此时，我们只处理异常，不处理中断
        Trap::Exception(Exception::UserEnvCall) => {                         // 处理Usercall，也就是ecall指令
            cx.sepc += 4;                                                    // 指向异常的下一条指令
            cx.x[10] = syscall(cx.x[17], [cx.x[10], cx.x[11], cx.x[12]]) as usize;
        },
        Trap::Exception(Exception::StoreFault) |
        Trap::Exception(Exception::StorePageFault) => {                      // 处理存储错误和存储页面错误
            println!("[Kernel] PageFault in application, kernel killed it");
            run_next_app();
        },
        Trap::Exception(Exception::IllegalInstruction) => {                  // 处理非法指令
            println!("[kernel] IllegalInstruction in application, kernel killed it");
            run_next_app();
        },
        Trap::Interrupt(Interrupt::SupervisorTimer) => {
            todo!()
        },
        _ => {
            panic!(
                "Unsupported trap {:?}, stval = {:#?}!",
                scause.cause(),
                stval
            );
        },
    }
    cx
}
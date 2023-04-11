use riscv::register::sstatus::{self, SPP, Sstatus};

#[repr(C)]
pub struct TrapContext {                                // 上下文寄存器
    pub x: [usize; 32],                                 // 对应RISCV 32个通用寄存器
    pub sstatus: Sstatus,                               // 特权指令集中的sstatus是mstatus的子集，里面拥有各种信息
    pub sepc: usize,                                    // 指向发生异常的指令，可以保存陷入异常时代码的地址
}

impl TrapContext {
    pub fn set_sp(&mut self, sp: usize) {               // 设置栈指针
        self.x[2] = sp;
    }

    pub fn app_init_context(entry: usize, sp: usize) -> Self {
        let mut sstatus = sstatus::read();    // 读取sstatus中的信息，赋值给sstatus
        sstatus.set_spp(SPP::User);                     // 设置发生trap时，源自于谁，此处是设置为User
        let mut cx = Self {               // 准备上下文
            x: [0; 32],
            sstatus,
            sepc: entry,
        };
        cx.set_sp(sp);                                  // 设置栈指针
        cx
    }
}
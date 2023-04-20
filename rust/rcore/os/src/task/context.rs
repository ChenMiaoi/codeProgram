#[derive(Copy, Clone)]
#[repr(C)]
pub struct TaskContext {                                            // 任务的上下文信息结构体
    ra: usize,                                                      // 需要返回的地址，也就是被调用的地址处
    sp: usize,                                                      // 当前的栈指针
    s: [usize; 12],                                                 // 其余需要被保存的寄存器
}

impl TaskContext {
    pub fn zero_init() -> Self {                                    // 为零初始化
        Self {
            ra: 0,
            sp: 0,
            s: [0; 12],
        }
    }

    pub fn goto_restore(kstack_ptr: usize) -> Self {                // 创建一个以上下文恢复的地址函数与内核栈指针构成的新的任务上下文
        extern "C" {
            fn __restore();
        }
        Self {
            ra: __restore as usize,                                 // 返回地址为trap return
            sp: kstack_ptr,                                         // 内核栈指针
            s: [0; 12],
        }
    }
}
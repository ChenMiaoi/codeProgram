use crate::config::*;
use crate::trap::TrapContext;
use core::arch::asm;

#[repr(align(4096))]                                                                        // 内存对齐，4K
#[derive(Copy, Clone)]                                                                      // 自动生成Copy和Clone trait
struct KernelStack {                                                                        // 内核栈定义结构
    data: [u8; KERNEL_STACK_SIZE],
}

#[repr(align(4096))]
#[derive(Copy, Clone)]
struct UserStack {                                                                          // 用户栈定义结构
    data: [u8; USER_STACK_SIZE],
}

static KERNEL_STACK: [KernelStack; MAX_APP_NUM] = [KernelStack {                            // 内核栈实例
    data: [0; KERNEL_STACK_SIZE],
}; MAX_APP_NUM];

static USER_STACK: [UserStack; MAX_APP_NUM] = [UserStack {                                  // 用户栈实例
    data: [0; USER_STACK_SIZE],
}; MAX_APP_NUM];

impl KernelStack {
    fn get_sp(&self) -> usize {                                                             // 获取内核栈指针
        self.data.as_ptr() as usize + KERNEL_STACK_SIZE                                     // 由于向下增长，因此需要加上栈大小
    }
    pub fn push_context(&self, trap_cx: TrapContext) -> usize {                             // 压入上下文信息
        let trap_cx_ptr =                                               // 获取当前栈指针
            (self.get_sp() - core::mem::size_of::<TrapContext>()) as *mut TrapContext;
        unsafe {
            *trap_cx_ptr = trap_cx;                                                         // 存入上下文
        }
        trap_cx_ptr as usize
    }
}

impl UserStack {
    fn get_sp(&self) -> usize {                                                             // 获取用户栈指针
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }
}

fn get_base_i(app_id: usize) -> usize {                                                     // 获取对应应用程序的起始基址
    APP_BASE_ADDRESS + app_id * APP_SIZE_LIMIT
}

pub fn get_num_app() -> usize {                                                             // 获取应用程序地址
    extern "C" {
        fn _num_app();
    }
    unsafe { (_num_app as usize as *const usize).read_volatile() }
}

pub fn load_apps() {                                                                        // 载入应用程序
    extern "C" {
        fn _num_app();
    }
    let num_app_ptr = _num_app as usize as *const usize;                    // 获取应用程序指针
    let num_app = get_num_app();                                                   // 获取应用程序数据
    let app_start = unsafe {                                                    // 获取应用的起始数据
        core::slice::from_raw_parts(num_app_ptr.add(1), num_app + 1)
    };
    unsafe { asm!("fence.i"); }                                                             // 确保写入正确
    for i in 0..num_app {
        let base_i = get_base_i(i);                                        // 获取应用程序起始地址
        (base_i..base_i + APP_SIZE_LIMIT)                                                   // 对应用程序空间进行初始化
            .for_each(|addr| unsafe {
                (addr as *mut u8).write_volatile(0)                                    // 逐一写入0进行初始化
            });
        let src = unsafe { core::slice::from_raw_parts(                             // 获取应当加载的应用程序资源
                app_start[i] as *const u8, app_start[i + 1] - app_start[i]       // 从app_start ~ app_start + 1
        )};
        let dst = unsafe { core::slice::from_raw_parts_mut(                     // 用dst来承载需要被写入的目的地址
            base_i as *mut u8, src.len()
        )};
        dst.copy_from_slice(src);                                                            // 拷贝进应用的实际物理地址
    }
}

pub fn init_app_cx(app_id: usize) -> usize {                                                 // 初始化应用程序上下文
    KERNEL_STACK[app_id].push_context(TrapContext::app_init_context(                // 压入上下文
        get_base_i(app_id),                                                           // 应用程序的基址
        USER_STACK[app_id].get_sp(),                                                     // 用户态中对应的栈指针
    ))
}
use crate::sync::UPSafeCell;
use crate::trap::TrapContext;
use core::arch::asm;
use lazy_static::*;

const USER_STACK_SIZE: usize        = 4096 * 2;                                             // 用户栈大小
const KERNEL_STACK_SIZE: usize      = 4096 * 2;                                             // 内核栈大小
const MAX_APP_NUM: usize            = 16;                                                   // 最大的用户程序数
const APP_BASE_ADDRESS: usize       = 0x80400000;                                           // 用户程序的起始地址
const APP_SIZE_LIMIT: usize         = 0x20000;                                              // 每个程序的最大地址

#[repr(align(4096))]                                                                        // 指定内存对齐的属性
struct KernelStack {                                                                        // 定义内核栈
    data: [u8; KERNEL_STACK_SIZE],
}

#[repr(align(4096))]
struct UserStack {                                                                          // 定义用户栈
    data: [u8; USER_STACK_SIZE],
}

static KERNEL_STACK: KernelStack = KernelStack {                                            // 实例出内核栈
    data: [0; KERNEL_STACK_SIZE],
};

static USER_STACK: UserStack = UserStack {                                                  // 实例出用户栈
    data: [0; USER_STACK_SIZE],
};

impl KernelStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + KERNEL_STACK_SIZE
    }           // 获取内核栈指针
    pub fn push_context(&self, cx: TrapContext) -> &'static mut TrapContext {               // 存入APP寄存器上下文，传出指针
        let cx_ptr =                                                    // 获取栈指针，因为栈是向下增长，因此要减去
            (self.get_sp() - core::mem::size_of::<TrapContext>()) as *mut TrapContext;
        unsafe {
            *cx_ptr = cx;                                                                   // 将APP的寄存器内容赋值
        }
        unsafe { cx_ptr.as_mut().unwrap() }                                                 // 以指针形式传出
    }
}

impl UserStack {
    fn get_sp(&self) -> usize {
        self.data.as_ptr() as usize + USER_STACK_SIZE
    }             // 获取用户栈指针
}

struct AppManager {
    num_app: usize,                                                                         // 用户程序数量
    current_app: usize,                                                                     // 当前用户程序标号
    app_start: [usize; MAX_APP_NUM + 1],                                                    // 用户程序的起始地址
}

impl AppManager {
    pub fn print_app_info(&self) {                                                          // 打印出所有用户程序
        println!("[kernel] app's number = {}", self.num_app);
        for i in 0..self.num_app {
            println!(
                "[kernel] app{} [{:#x}, {:#x})",
                i, self.app_start[i], self.app_start[i + 1]                                 // 一个用户程序的地址大小等于后一个程序的起始地址减去自身的起始地址
            );
        }
    }

    unsafe fn load_app(&self, app_id: usize) {                                              // 载入指定用户程序
        if app_id >= self.num_app {                                                         // 不允许载入非法的程序号
            println!("All applications completed!");
            use crate::boards::QEMUExit;
            crate::boards::QEMU_EXIT_HANDLE.exit_success();
        }
        println!("[kernel] Loading app{}", app_id);

        core::slice::from_raw_parts_mut(                                                    // 准备出一块地址空间，且类型为[u8;]
            APP_BASE_ADDRESS as *mut u8, APP_SIZE_LIMIT
        ).fill(0);                                                                  // 初始化为0
        let app_src = core::slice::from_raw_parts(                                  // 得到当前应用程序的地址空间，且类型为&[u8]
            self.app_start[app_id] as *const u8,
            self.app_start[app_id + 1] - self.app_start[app_id],
        );
        let app_dst = core::slice::from_raw_parts_mut(                          // 在一开始设定的用户程序基址上切出一块用户程序的空间
            APP_BASE_ADDRESS as *mut u8, app_src.len()
        );
        app_dst.copy_from_slice(app_src);                                                   // 将用户数据拷贝进基址上对应的地址
                                                                                            // fence.i用于同步指令和数据流，如果没有RISCV不保证存储指令写到内存指令的数据可以被取到
        asm!("fence.i");                                                                    // 如果有了，那么RISCV就会保证存储指令写到内存指令区时可以被取指令取到
    }

    pub fn get_current_app(&self) -> usize {                                                // 获取当前用户程序
        self.current_app
    }
    pub fn move_to_next_app(&mut self) {                                                    // 移动到下一个程序(准备)
        self.current_app += 1;
    }
}

lazy_static! {                                                                              // lazy_static的作用在于惰性求值，只有第一次会被初始化
    static ref APP_MANAGER: UPSafeCell<AppManager> = unsafe {                               // 实例AppManger
        UPSafeCell::new({                                                                   // 为了线程安全，因为不止一个app
            extern "C" {
                fn _num_app();                                                              // 获取汇编中的_num_app
            }
            let num_app_ptr = _num_app as usize as *const usize;            //  得到用户程序的指针
            let num_app = num_app_ptr.read_volatile();                              // 读取其数据
            let mut app_start: [usize; MAX_APP_NUM + 1] = [0; MAX_APP_NUM + 1];             // 设置应用程序起始
            let app_start_raw: &[usize] =                                                   // 得到用户程序起始和结束地址
                core::slice::from_raw_parts(num_app_ptr.add(1), num_app + 1);
            app_start[..=num_app].copy_from_slice(app_start_raw);                           // 将用户程序的起始和结束地址存入
            AppManager {
                num_app, current_app: 0, app_start,                                         // 返回AppManager
            }
        })
    };
}

pub fn init() {
    print_app_info();
}

pub fn print_app_info() {
    APP_MANAGER.exclusive_access().print_app_info();
}

pub fn run_next_app() -> ! {                                                                // 运行下一个程序
    let mut app_manager = APP_MANAGER.exclusive_access();             // 获取APP_MANAGER里面拥有用户程序信息
    let current_app = app_manager.get_current_app();                                // 获取当前运行的用户程序
    unsafe {
        app_manager.load_app(current_app);                                          // 载入当前程序
    }
    app_manager.move_to_next_app();                                                         // 准备下一个运行程序
    drop(app_manager);                                                                  // 注销当前运行程序
    extern "C" {
        fn __restore(cx_addr: usize);                                                       // 开始返回，恢复上下文寄存器
    }
    unsafe {
        __restore(KERNEL_STACK.push_context(TrapContext::app_init_context(              // 向__restore传入上下文寄存器
            APP_BASE_ADDRESS,                                                        // 用户程序的基址
            USER_STACK.get_sp(),                                                        // 用户栈指针
        )) as *const _ as usize);
    }
    panic!("Unreachable in batch::run_current_app!");
}
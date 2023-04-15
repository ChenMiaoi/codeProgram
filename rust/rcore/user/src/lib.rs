#![no_std]
#![feature(linkage)]
#![feature(panic_info_message)]
#![feature(alloc_error_handler)]

extern crate alloc;
extern crate core;
#[macro_use]
extern crate bitflags;

#[macro_use]
pub mod console;
mod syscall;
mod lang_item;

use alloc::vec::Vec;
use buddy_system_allocator::LockedHeap;
pub use syscall::*;
pub use console::{flush, STDIN, STDOUT};

const USER_HEAP_SIZE: usize = 16384;                                                    // 定义用户堆空间大小16K
static mut HEAP_SPACE: [u8; USER_HEAP_SIZE] = [0; USER_HEAP_SIZE];                      // 定义堆空间数组

#[global_allocator]
static HEAP: LockedHeap = LockedHeap::empty();                                          // LockedHeap是一个拥有锁的堆，实现了GlobalAlloc，是一个线程安全的堆

#[alloc_error_handler]
pub fn handle_alloc_error(layout: core::alloc::Layout) -> ! {
    panic!("Heap allocation error, layout = {:?}", layout);
}

fn clear_bss() {
    extern "C" {
        fn start_bss();
        fn end_bss();
    }
    unsafe {
        core::slice::from_raw_parts_mut(
            start_bss as usize as *mut u8,
            end_bss as usize - start_bss as usize,
        ).fill(0);
    }
}
                                                                                        // 该函数在程序启动时初始化堆，并且调用main
#[no_mangle]
#[link_section = ".text.entry"]                                                         // 指明函数存放在那个段中
pub extern "C" fn _start(argc: usize, argv: usize) -> ! {
    clear_bss();
    unsafe {
        HEAP.lock()                                                 // 申请锁资源
            .init(HEAP_SPACE.as_ptr() as usize, USER_HEAP_SIZE);          // 初始化堆空间
    }
    let mut v: Vec<&'static str> = Vec::new();
    for i in 0..argc {                                                         // 命令行参数个数
        let str_start = unsafe {                                               // 获取命令行参数的开始地址
            ((argv + i * core::mem::size_of::<usize>()) as *const usize).read_volatile()
        };
        let len = (0usize..)                                                    // 获取命令行参数的个数
            .find(|i| unsafe {
                ((str_start + *i) as *const u8).read_volatile() == 0
            }).unwrap();
        v.push(
            core::str::from_utf8(unsafe {                                   // 切割命令行参数，使其成为一个slice
                core::slice::from_raw_parts(str_start as *const u8, len)
            }).unwrap(),
        );
    }
    exit(main(argc, v.as_slice()));
}

#[linkage = "weak"]
#[no_mangle]
fn main(_argc: usize, _argv: &[&str]) -> i32 {
    panic!("Cannot find main!");
}

pub fn read(fd: usize, buf: &mut [u8]) -> isize {                                       // 用户态的read API
    sys_read(fd, buf)                                                           // 调用内核的syscall
}

pub fn write(fd: usize, buf: &mut [u8]) -> isize {
    sys_write(fd, buf)
}        // 用户态的write API

pub fn exit(exit_code: i32) -> ! {                                                      // 用户态的exit API
    console::flush();                                                                   // 在退出前，将输入输出缓冲清空
    sys_exit(exit_code);
}
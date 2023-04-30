// #![deny(missing_docs)]
// #![deny(warnings)]
#![no_std]
#![no_main]
#![warn(unused_doc_comments)]
#![feature(panic_info_message)]
#![feature(alloc_error_handler)]

extern crate alloc;

use core::arch::global_asm;
use log::*;

#[macro_use]
mod console;
mod loader;
mod heap_alloc;
pub mod mm;
pub mod timer;
pub mod config;
pub mod trap;
pub mod task;
pub mod sync;
pub mod syscall;
pub mod lang_items;
pub mod sbi;
pub mod logging;

#[path = "boards/qemu.rs"]
mod boards;

global_asm!(include_str!("entry.asm"));
global_asm!(include_str!("link_app.S"));

pub fn clear_bss() {
    extern "C" {
        fn start_bss();
        fn end_bss();
    }
    (start_bss as usize..end_bss as usize).for_each(| a  | unsafe {
        (a as *mut u8).write_volatile(0)
    });
}

fn kernel_log_info() {
    extern "C" {
        fn start_text();
        fn end_text();
        fn start_rodata();
        fn end_rodata();
        fn start_data();
        fn end_data();
        fn start_bss();
        fn end_bss();
        fn boot_stack_lower_bound();
        fn boot_stack_top();
    }
    clear_bss();
    logging::init();
    println!("[kernel] Hello World!");
    trace!("[kernel] .rodata [{:#?}, {:#?})", start_rodata as usize, end_rodata as usize);
    debug!("[kernel] .text [{:#?}, {:#?})", start_text as usize, end_text as usize);
    info!("[kernel] .data [{:#?}, {:#?})", start_data as usize, end_data as usize);
    warn!("[kernel] .boot_stack top = {:#?}, \
        lower = {:#?}", boot_stack_top as usize, boot_stack_lower_bound as usize);
    error!("[kernel] .bss [{:#?}, {:#?})", start_bss as usize, end_bss as usize);

}

#[no_mangle]
pub fn start_main() -> ! {
    clear_bss();
    kernel_log_info();
    mm::init();
    println!("[kernel] back to world!");
    mm::remap_test();
    trap::init();
    trap::enable_timer_interrupt();
    timer::set_next_trigger();
    task::run_first_task();
    panic!("Unreachable in rust_main!");
}
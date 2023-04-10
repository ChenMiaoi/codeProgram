// #![deny(missing_docs)]
// #![deny(warnings)]
#![no_std]
#![no_main]
#![feature(panic_info_message)]

use core::arch::global_asm;
use log::*;

#[macro_use]
mod lang_items;
mod console;
mod sbi;
mod logging;

#[path = "boards/qemu.rs"]
mod boards;

global_asm!(include_str!("entry.asm"));

pub fn clear_bss() {
    extern "C" {
        fn start_bss();
        fn end_bss();
    }
    (start_bss as usize..end_bss as usize).for_each(| a  | unsafe {
        (a as *mut u8).write_volatile(0)
    });
}

#[no_mangle]
pub fn start_main() -> ! {
    extern "C" {
        fn start_text();
        fn end_text();
        fn start_rodata();
        fn end_rodata();
        fn start_data();
        fn end_data();
        fn start_bss();
        fn end_bss();
        fn boot_stact_lower_bound();
        fn boot_stack_top();
    }
    clear_bss();
    logging::init();
    println!("[kernel] Hello World!");
    trace!("[kernel] .rodata [{:#?}, {:#?})", start_rodata as usize, end_rodata as usize);
    debug!("[kernel] .text [{:#?}, {:#?})", start_text as usize, end_text as usize);
    info!("[kernel] .data [{:#?}, {:#?})", start_data as usize, end_data as usize);
    warn!("[kernel] .boot_stack top = {:#?}, lower = {:#?}", start_rodata as usize, end_rodata as usize);
    error!("[kernel] .bss [{:#?}, {:#?})", start_bss as usize, end_bss as usize);
    use crate::boards::QEMUExit;
    crate::boards::QEMU_EXIT_HANDLE.exit_success();
}
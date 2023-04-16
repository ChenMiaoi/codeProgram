#![no_std]
#![no_main]

extern crate user_lib;

#[no_mangle]
pub fn main() -> i32 {
    let mut sstatus: usize;
    unsafe {
        core::arch::asm!("csrr {}, sstatus", out(reg) sstatus);
    }
    panic!("(-_-) I get sstatus: {:x}\nFAIL: T.T\n", sstatus);
}
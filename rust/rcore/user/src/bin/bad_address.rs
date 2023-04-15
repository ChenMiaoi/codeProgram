#![no_std]
#![no_main]

extern crate user_lib;

#[no_mangle]
pub fn main() {
    unsafe {
        #[allow(clippy::zero_ptr)]
        (0x0 as *mut u8).write_volatile(0);         // 对0地址写入会导致错误
    }
    panic!("FAIL: T.T\n");
}
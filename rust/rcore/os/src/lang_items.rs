use core::panic::PanicInfo;
use crate::println;
use crate::sbi::shutdown;

#[panic_handler]
fn panic(info: &PanicInfo) -> ! {                                       // 重写main函数的返回值
    if let Some(location) = info.location() {               // panic信息
        println!(
            "[kernel] Panicked at {}:{} {}",
            location.file(),
            location.line(),
            info.message().unwrap()
        );
    } else {
        println!("[kernel] Panicked: {}", info.message().unwrap());
    }
    shutdown()
}
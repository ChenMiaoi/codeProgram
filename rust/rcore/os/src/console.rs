use crate::sbi::console_putchar;
use core::fmt::{self, Write};

struct Stdout;

impl Write for Stdout {                                     // 为Stdout重写Write
    fn write_str(&mut self, s: &str) -> fmt::Result {
        for c in s.chars() {
            console_putchar(c as usize);                // 调用SBI console_putchar
        }
        Ok(())
    }
}

pub fn print(args: fmt::Arguments) {                        // 重写print
    Stdout.write_fmt(args).unwrap();
}

#[macro_export]
macro_rules! print {                                        // 重写print!
    ($fmt: literal $(, $($arg: tt)+)?) => {                 // fmt是格式，需要用逗号分隔，参数是匿名类型
        $crate::console::print(format_args!($fmt $(, $($arg)+)?))
    }
}

#[macro_export]
macro_rules! println {
    ($fmt: literal $(, $($arg: tt)+)?) => {                 // 重写println!
        $crate::console::print(format_args!(concat!($fmt, "\n") $(, $($arg)+)?))
    }
}
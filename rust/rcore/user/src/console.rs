use alloc::collections::vec_deque::VecDeque;
use alloc::sync::Arc;
use core::fmt::{self, Write};
use spin::mutex::Mutex;

use super::{read, write};
use lazy_static::*;

pub const STDIN     : usize = 0;                                                            // 标准输入
pub const STDOUT    : usize = 1;                                                            // 标准输出

const CONSOLE_BUFFER_SIZE: usize = 256 * 10;                                                // 终端输入的缓冲区大小

struct ConsoleBuffer(VecDeque<u8>);                                                         // 终端缓冲区结构，使用VecDeque
                                                                                            // VecDeque是一个双端队列，且可扩展的缓冲区
lazy_static! {
    static ref CONSOLE_BUFFER: Arc<Mutex<ConsoleBuffer>> = {                                // 在第一次初始化时进行赋值
        let buffer = VecDeque::<u8>::with_capacity(CONSOLE_BUFFER_SIZE);    // 定义一个以缓冲区大小的双端队列作为终端缓冲区
        Arc::new(Mutex::new(ConsoleBuffer(buffer)))                                         // 返回一个Arc引用计数的智能指针，且加锁
    };
}

impl ConsoleBuffer {
    fn flush(&mut self) -> isize {                                                          // 清空缓冲区
        let s = self.0.make_contiguous();                                       // 可以将VecDeque进行旋转，使其元素不再环绕，返回一个可变切片
        let ret = write(STDOUT, s);                                       // 通过write可以向标准输出中写入
        self.0.clear();                                                                     // 对缓冲区 清空
        ret
    }
}

impl Write for ConsoleBuffer {
    fn write_str(&mut self, s: &str) -> fmt::Result {                                       // 为缓冲区实现Write trait
        for c in s.as_bytes().iter() {
            self.0.push_back(*c);                                                   // 输入进缓冲区
            if *c == b'\n' || self.0.len() == CONSOLE_BUFFER_SIZE && -1 == self.flush() {   // 如果等于\n，或者长度大于等于缓冲区大小，或者刷新失败
                return Err(fmt::Error);                                                     // 抛出错误
            }
        }
        Ok(())
    }
}

#[allow(unused)]
pub fn print(args: fmt::Arguments) {
    let mut buf = CONSOLE_BUFFER.lock();                        // 获取缓冲区锁资源
    buf.write_fmt(args);
}

#[macro_export]
macro_rules! print {
    ($fmt: literal $(, $($arg: tt)+)?) => {
        $crate::console::print(format_args!($fmt $(, $($arg)+)?));
    };
}

#[macro_export]
macro_rules! println {
    ($fmt: literal $(, $($arg: tt)+)?) => {
        $crate::console::print(format_args!(concat!($fmt, "\n") $(, $($arg)+)?));
    };
}

pub fn getchar() -> u8 {
    let mut c = [0u8; 1];
    read(STDIN, &mut c);
    c[0]
}

pub fn flush() {
    let mut buf = CONSOLE_BUFFER.lock();
    buf.flush();
}
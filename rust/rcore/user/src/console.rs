use core::fmt::{self, Write};

pub const STDOUT: usize = 1;

const CONSOLE_BUFFER_SIZE: usize = 256 * 10;

struct ConsoleBuffer;

impl Write for ConsoleBuffer {
    fn write_char(&mut self, c: char) -> std::fmt::Result {
        todo!()
    }
}
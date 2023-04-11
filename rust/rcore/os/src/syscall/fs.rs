use log::trace;

const FD_STDOUT: usize = 1;                                                     // 标准输出

pub fn sys_write(fd: usize, buf: *const u8, len: usize) -> isize {
    trace!("kernel: sys_write");
    match fd {
        FD_STDOUT => {
            // core::slice::from_raw_parts用于从指针以一个长度创建一个切片，其中，len参数是元素的数量
            let slice = unsafe { core::slice::from_raw_parts(buf, len) };
            // core::str::from_utf8确保了一个字节切片(UTF8)转换为字符串切片
            let str = core::str::from_utf8(slice).unwrap();
            print!("{}", str);
            len as isize
        },
        _ => {
            panic!("Unsupported fd in sys_write!");
        }
    }
}
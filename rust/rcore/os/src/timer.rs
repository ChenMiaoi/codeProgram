use crate::config::CLOCK_FREQ;
use crate::sbi::set_timer;
use riscv::register::time;

const TICKS_PRE_SEC : usize = 100;                                  // 每秒对应的时间片
#[allow(dead_code)]                                                 // 允许使用死代码
const MSEC_PRE_SEC  : usize = 1000;                                 // 每秒对应的毫秒数
#[allow(dead_code)]
const MICRO_PRE_SEC : usize = 1_000_000;                            // 每秒对应的微秒数

pub fn get_time() -> usize {
    time::read()                                                    // 通过计时器寄存器获取时间 -> 以时间片的形式
}

pub fn get_time_ms() -> usize {
    time::read() / (CLOCK_FREQ / MSEC_PRE_SEC)                      // 将时间转化为毫秒的形式
}

pub fn get_time_us() -> usize {
    time::read() * MICRO_PRE_SEC / CLOCK_FREQ                       // 将时间转化为微秒的形式
}

pub fn set_next_trigger() {
    set_timer(get_time() + CLOCK_FREQ / TICKS_PRE_SEC);             // 设置下一个定时中断
}
use log::{self, Level, LevelFilter, Log, Metadata, Record};
use crate::println;

struct SimpleLogger;

impl Log for SimpleLogger {
    fn enabled(&self, metadata: &Metadata) -> bool {            // 重写enabled方法
        true
    }
    fn flush(&self) {}
    fn log(&self, record: &Record) {                            // 重写log方法
        if !self.enabled(record.metadata()) {
            return;
        }
        let color: i32 = match record.level() {                 // 设置输出色彩
            Level::Error => 31,         // Red
            Level::Warn => 93,          // BrightYellow
            Level::Info => 34,          // Blue
            Level::Debug => 32,         // Green
            Level::Trace => 90,         // BrightBlack
        };
        println!(                                               // 输出
            "\u{1B}[{}m[{:>5}]] {}\u{1B}[0m",
            color, record.level(), record.args(),
        );
    }
}

pub fn init() {                                                 // 初始化log信息
    static LOGGER: SimpleLogger = SimpleLogger;
    log::set_logger(&LOGGER).unwrap();
    log::set_max_level(match option_env!("LOG") {               // 允许使用环境参数LOG来确定是否输出
        Some("ERROR") => LevelFilter::Error,
        Some("WARN") => LevelFilter::Warn,
        Some("INFO") => LevelFilter::Info,
        Some("DEBUG") => LevelFilter::Debug,
        Some("TRACE") => LevelFilter::Trace,
        _ => LevelFilter::Off,
    });
}
use std::env;
use log::LevelFilter;

mod logging;

struct SimpleLog;

pub fn init() {
    static LOGGER: SimpleLog = SimpleLog;
    log::set_logger(&LOGGER).unwrap();
    if let Ok(log_level) = env::var("AnythingLog") {
        match log_level.as_str() {
            "ERROR" => log::set_max_level(LevelFilter::Error),
            "WARN" => log::set_max_level(LevelFilter::Warn),
            "INFO" => log::set_max_level(LevelFilter::Info),
            "DEBUG" => log::set_max_level(LevelFilter::Debug),
            "TRACE" => log::set_max_level(LevelFilter::Trace),
            _ => {
                println!("[DEBUG]");
                log::set_max_level(LevelFilter::Off);
            }
        }
    } else {
        println!("[DEBUG]");
        log::set_max_level(LevelFilter::Off);
    }
}

// #[macro_export]
// macro_rules! info {
//     ($arg:expr) => {
//         info!(concat!($arg, " in ", file!(), " at ", line!(), " lines"));
//     };
// }
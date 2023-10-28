use std::fs::OpenOptions;
use std::io::{self, Write};
use log::{Level, Log, Metadata, Record};
use crate::log::SimpleLog;

impl Log for SimpleLog {
    fn enabled(&self, _metadata: &Metadata) -> bool {
        true
    }
    fn log(&self, record: &Record) {
        if !self.enabled(record.metadata()) {
            return;
        }
        let file = record.file().unwrap();
        let line = record.line().unwrap();
        let color: i32 = match record.level() {
            Level::Error => 31,
            Level::Warn => 93,
            Level::Info => 34,
            Level::Debug => 32,
            Level::Trace => 37,
        };
        let mut stderr = std::io::stderr();
        writeln!(stderr, "\u{1B}[{}m{} [{:>5}] <{}:{}>: {}\u{1B}[0m",
                 color, chrono::Local::now().format("%Y-%m-%d %H:%M:%S"), record.level(),
                 file, line, record.args()
        ).unwrap();
        let mut log_file = OpenOptions::new()
            .create(true)
            .append(true)
            .open("log.txt")
            .unwrap();
        writeln!(log_file, "{} [{:>5}] <{:?}:{:?}>: {}",
                 chrono::Local::now().format("%Y-%m-%d %H:%M:%S"), record.level(),
                 file, line, record.args()
        ).unwrap();
    }
    fn flush(&self) {}
}
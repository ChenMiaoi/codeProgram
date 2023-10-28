use std::fmt;
use std::fmt::{Formatter, write};
use clap::ValueEnum;

#[derive(Copy, Clone, PartialOrd, PartialEq, Debug, ValueEnum)]
pub enum LevelMode {
    /// The max level up to TRACE
    Trace,
    /// The max level up to INFO
    Info,
    /// The max level up to DEBUG
    Debug,
    /// The max level up to WARN
    Warn,
    /// The max level up to ERROR
    Error,
}

impl fmt::Display for LevelMode {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        match self {
            LevelMode::Trace => write!(f, "trace"),
            LevelMode::Info => write!(f, "info"),
            LevelMode::Debug => write!(f, "debug"),
            LevelMode::Warn => write!(f, "warn"),
            LevelMode::Error => write!(f, "error"),
        }
    }
}
mod log;
mod cli;

use std::env;
use ::log::{debug, error, info, trace, warn};
use clap::{Parser};
use crate::cli::AnythingArgs;
use crate::cli::cli_config::LevelMode;

fn main() {
    let args = AnythingArgs::parse();

    let path = match args.path.clone() {
        None => String::from("."),
        Some(dir_path) => dir_path,
    };
    let log_level = match args.level {
        LevelMode::Trace => "TRACE",
        LevelMode::Info => "INFO",
        LevelMode::Debug => "DEBUG",
        LevelMode::Warn => "WARN",
        LevelMode::Error => "ERROR",
    };

    println!("{:#?}", path);

    env::set_var("AnythingLog", log_level);
    log::init();
    if let Ok(level) = env::var("AnythingLog") {
        info!("Setting Log lowest Level report -> {level}");
    }

}

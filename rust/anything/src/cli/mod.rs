pub mod cli_config;

use clap::Parser;
use crate::cli::cli_config::LevelMode;

#[derive(Parser, Debug)]
#[command(
author = "Chen Miao",
version = "v0.1.0",
about = "A simple grep file call",
long_about = None
)]
pub struct AnythingArgs {
    /// search file
    #[arg(short = 'f', long = "file", required = true)]
    pub file: String,
    /// case-sensitive search (default: smart case)
    #[arg(short = 's', long = "sensitive")]
    pub sensitive: bool,
    /// search full path
    #[arg(short = 'p', long = "path", required = false)]
    pub path: Option<String>,
    /// log level
    #[arg(short = 'l', long = "level", required = false, default_value_t = LevelMode::Info, next_line_help = true)]
    pub level: LevelMode,
}

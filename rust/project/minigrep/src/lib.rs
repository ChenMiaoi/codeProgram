use std::{env, error::Error, fs};

pub struct Config<'a> {
    query: &'a str,
    file_path: &'a str,
    ignore_case: bool,
}

impl<'a> Config<'a> {
    pub fn new(args: &[String]) -> Config {
        if args.len() < 3 {
            panic!("Usage:\n\tquery file_path")
        }
        Config { query: &args[1], file_path: &args[2], ignore_case: false }
    }

    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough argument.\nUsage:\n\tquery file_path [option: -i]")
        }
        Ok(Config {
            query: &args[1], file_path: &args[2], ignore_case: match args.len() {
                4 => &args[3] == "-i",
                x if x < 4 => false,
                _ => false,
            }
        })
    }

    pub fn query(&self) -> &str {
        self.query
    }

    pub fn file_path(&self) -> &str {
        self.file_path
    }
}

pub fn run(config: Config) -> Result<(), Box<dyn Error>> {
    let contents = fs::read_to_string(config.file_path)?;
    let mut count = 1;

    let result = if config.ignore_case {
        search_case_insensitive(config.query, &contents)
    } else {
        search(config.query, &contents)
    };
    for line in result {
        println!("{count}: {line}");
        count += 1;
    }
    Ok(())
}

pub fn search<'a> (query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();
    for line in contents.lines() {
        if line.contains(query) {
            result.push(line);
        }
    }
    result
}

pub fn search_case_insensitive<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();
    for line in contents.lines() {
        if line.to_lowercase().contains(&(query.to_lowercase())) {
            result.push(line);
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn one_result() {
        let query = "duct";
        let contents = "\
            Rust:\n\
            safe, fast, productive.\n\
            Pick three.\n
        ";
        assert_eq!(vec!["safe, fast, productive."], search(query, contents));
    }

    #[test]
    fn case_insensitive() {
        let query = "rUsT";
        let contents = "\
            Rust:\n\
            safe, fast, productive.\n\
            Pick three.\n\
            Trust me.\n
        ";
        assert_eq!(vec!["Rust:", "Trust me."], search_case_insensitive(query, contents));
    }
}
use restaurant::eat_in_restaurant;
use std:: {
    collections::HashMap,
    fmt,
};

use std::io::{
    self,
    Write,
    Result as IoResult
};

use rand::Rng;

fn function1() -> fmt::Result {
    Ok(())
}

fn function2() -> IoResult<()> {
    Ok(())
}

fn main() {
    println!("Hello World");
    eat_in_restaurant();
    let mut map = HashMap::new();
    map.insert(1, 2);
    dbg!(map);
}
#![no_std]
#![feature(linkage)]

#[macro_use]
pub mod console;

#[linkage = "weak"]
#[no_mangle]
fn main() {
    println!("Hello, world!");
}

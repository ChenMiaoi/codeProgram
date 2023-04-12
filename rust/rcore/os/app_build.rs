use std::fs::{read_dir, File};
use std::io::{Result, Write};

fn main() {
    println!("cargo: return-if-changed = ../user/src/");
    println!("cargo: return-if-changed = {}", TARGET_PATH);
    insert_app_data().unwrap();
}

static TARGET_PATH: &str = "../user/build/bin/";

fn insert_app_data() -> Result<()> {
    let mut f = File::create("src/link_app.S").unwrap();
    let mut apps: Vec<_> = read_dir("../user/build/bin/")
        .unwrap()
        .into_iter()
        .map(| dir_entry | {
            let mut name_with_ext = dir_entry.unwrap()
                .file_name().into_string().unwrap();
            name_with_ext.drain(
                name_with_ext.find('.').unwrap()..name_with_ext.len()
            );
            name_with_ext })
        .collect();
    apps.sort();

    writeln!(
        f, r#"
            .align 3
            .section .data
            .global _num_app
        _num_app:
            .quad {}"#, apps.len()
    )?;
    for i in 0..apps.len() {
        writeln!(f, r#"     .quad app{}_start"#, i)?;
    }
    writeln!(f, r#"     .quad app{}_end"#, apps.len() - 1)?;

    for (idx, app) in apps.iter().enumerate() {
        println!("app{}: {}", idx, app);
        writeln!(
            f, r#"
                .section .data
                .global app{0}_start
                .global app{0}_end
            app{0}_start:
                .incbin "{2}{1}.bin"
            app{0}.end:"#, idx, app, TARGET_PATH
        )?;
    }
    Ok(())
}
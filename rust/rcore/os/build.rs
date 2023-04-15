/// 用于生成link_app.S的文件
/// 同时，build.rs是一个Rust构建脚本，会被cargo自行运行，当然也可以使用'`build = "my_build.rs"`在`cargo.toml`中自定义

use std::fs::{read_dir, File};
use std::io::{Result, Write};

fn main() {
    println!("cargo: return-if-changed = ../user/src/");                                // 该指令是一个cargo构建脚本指令，
    println!("cargo: return-if-changed = {}", TARGET_PATH);                             // 一旦给定的路径发生了更改，则重新运行该脚本
    insert_app_data().unwrap();
}

static TARGET_PATH: &str = "../user/build/bin/";                                        // 用户态代码存放的文件夹

fn insert_app_data() -> Result<()> {                                                    // 写入link_app.S的函数
    let mut f = File::create("src/link_app.S").unwrap();                  // 创建一个link_app.S的文件
    let mut apps: Vec<_> = read_dir("../user/build/bin/")               // 读取用户态下的代码文件
        .unwrap()                                      // 不抛出异常
        .into_iter()
        .map(| dir_entry | {
            let mut name_with_ext = dir_entry.unwrap()             // 将文件名转化为字符串
                .file_name().into_string().unwrap();
            name_with_ext.drain(                                                        // 接收一个数组作为参数，删除以"."结尾的字符串
                name_with_ext.find('.').unwrap()..name_with_ext.len()      // 也就是保留文件名，去除文件后缀
            );
            name_with_ext })
        .collect();
    apps.sort();                                                                        // 对文件名进行重新排序

    writeln!(
        f, r#"
    .align 3
    .section .data
    .global _num_app
_num_app:
     .quad {}"#, apps.len()
    )?;                                                                                 // 写入汇编
    for i in 0..apps.len() {
        writeln!(f, r#"    .quad app{}_start"#, i)?;                                    // .quad是一个伪指令，用于定义一个8字节的常量
    }                                                                                   // 此处是声明应用程序的序列号，以及地址
    writeln!(f, r#"    .quad app{}_end"#, apps.len() - 1)?;

    for (idx, app) in apps.iter().enumerate() {
        println!("app{}: {}", idx, app);
        writeln!(                                                                       // 写入汇编
            f, r#"
    .section .data
    .global app{0}_start
    .global app{0}_end
app{0}_start:
    .incbin "{2}{1}.bin"
app{0}_end:"#, idx, app, TARGET_PATH
        )?;                                                                             // .incbin也是一个伪指令，用于将一个文件包含在另一个文件中
    }
    Ok(())
}
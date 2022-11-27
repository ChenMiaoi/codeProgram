use std::fmt::format;

fn main() {
    // let mut s = String::new();
    let data = "initial contents";
    let s = data.to_string();
    let s = "initial contents".to_string();
    dbg!(s);
    let mut s = String::from("initial contents");
    // String::from <=> str.to_string
    // rust中字符串是UTF-8的

    // String可以使用 + 运算符或者 format宏来拼接
    s.push_str(" hello world");
    // 或者使用push_str来追加字符串
    dbg!(s);

    let s1 = String::from("hello");
    let s2 = String::from(" world");
    let s3 = s1 + &s2;
    // fn add(self, s: &str) -> String
    // 此处，s1会被移动到s3
    println!("{}", s3);

    // 使用format宏实现复杂的字符串链接
    let s1 = String::from("tie");
    let s2 = String::from("tac");
    let s3 = String::from("toe");
    let s = format!("{}-{}-{}", s1, s2, s3);
    println!("{}", s);

    // Rust不允许索引字符串，但是可以slice字符串
    let s = &s[0..4];
    println!("{}", s);

    // 遍历字符串
    for c in s.chars() {
        println!("{}", c);
    }

    for b in s.bytes() {
        println!("{}", b);
    }
}
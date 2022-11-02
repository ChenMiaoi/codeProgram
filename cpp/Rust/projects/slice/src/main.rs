fn first_world(str: &String) -> &str {
    let byte = str.as_bytes();

    for (i, &item) in byte.iter().enumerate() { // enumerate方法返回两个值，第一个是索引，第二个是集合中元素的引用
        if item == b' ' {
            return &str[..i];
        }
    }
    return &str[..];
}
fn main() {
    let str: String = String::from("hello world");
    println!("The first world is : {}", first_world(&str));

    let a = [1, 2, 3, 4, 5];
    let slice = &a[..3];
    assert_eq!(slice, &a[..3]);
}

fn main() {
    let v: Vec<i32> = Vec::new();
    // 如果使用Vec::new()创建，必须显示声明类型，不然无法知道Vec的泛型
    // rust提供了一个vec!宏, 使用宏来创建就不需要声明类型，编译器可以自动推导
    let v1 = vec![1, 2, 3];
    // v.push(1); 此时的v是let的，也就意味着不可变，因此如果想要添加，一开始就需要声明
    let mut v2 = vec![1, 2, 3];
    v2.push(4);
    dbg!(v2);

    let third = &v1[2];
    println!("The third element is {}", third);

    match v1.get(5) {
        Some(third) => println!("The third element is {}", third),
        None => println!("There is no third element")
    }

    // 直接索引不会对索引值进行处理，运行如果越界则会出现panic，使用get方法则返回None

    let mut v4 = vec![1, 2, 3, 4];
    let first = &v4[0];

    v4.push(5);
    // println!("{}", first); rust阻止了firsr的调用
    // 当我们获取了第一个元素的不可变引用时，对Vec进行添加元素有可能导致空间不足，当空间不足时，Vec会要求
    // 开辟新空间，那么原本的旧空间就被释放，因此rust不允许调用第一个元素的引用，因此Vec的第一个元素会关心尾部空间

    for i in &v4 {
        println!("{}", i);
    }

    for i in &mut v4 {
        *i += 50; // 对引用进行解引用
    }

    #[derive(Debug)]
    enum Person {
        Name(String),
        Addr(String),
        Age(u32),
        Score(f64)
    }

    let row = vec![
        Person::Name(String::from("asd")),
        Person::Addr(String::from("jkb")),
        Person::Age(32),
        Person::Score(95.65)
    ];

    dbg!(row);
}

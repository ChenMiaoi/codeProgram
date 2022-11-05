#[derive(Debug)]
enum IpAddrKind {
    V4,
    V6
}

fn route(ip_type: IpAddrKind) {

}

#[derive(Debug)]
struct IpAddr {
    kind: IpAddrKind,
    address: String
}

#[derive(Debug)]
enum UsState {
    Alabama,
    Alaska
}

enum Coin {
    Penny,
    Nickel,
    Dime,
    Quarter(UsState)
}

fn value_in_cents(coin: Coin) -> u32 {
    match coin {
        Coin::Penny => {
            print!("Lucky Peeny");
            1
        },
        Coin::Nickel => 5,
        Coin::Dime => 10,
        Coin::Quarter(state) => {
            println!("Satete quarter from {:?}!", state);
            25
        }
    }
}

fn plus_one(x: Option<i32>) -> Option<i32> {
    match x {
        None => None,
        Some(i) => Some(i + 1)
    }
}

fn main() {
    println!("Hello, world!");
    route(IpAddrKind::V4);
    let home: IpAddr = IpAddr{
        kind: IpAddrKind::V4,
        address: String::from("127.0.0.1")
    };

    let loopback: IpAddr = IpAddr {
        kind: IpAddrKind::V4,
        address: String::from("::1")
    };

    let x = Some(10);
    let y = Some(30);
    let sum: Option<u32> = None;

    dbg!(home);
    let a = value_in_cents(Coin::Penny);
    dbg!(a);
    let b = value_in_cents(Coin::Quarter(UsState::Alabama));
    dbg!(b);

    let five = Some(5);
    let six = plus_one(five);
    let none = plus_one(None);
}
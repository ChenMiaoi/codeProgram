use std::sync::atomic::AtomicUsize;
use std::sync::atomic::Ordering;
#[derive(Debug)]
struct User {
    active: bool,
    username: String,
    email: String,
    sign_id: usize
}

fn build_user(email: String, username: String) -> User {
    static ID: AtomicUsize = AtomicUsize::new(1);

    User {
        email,
        username,
        active: true,
        sign_id: ID.fetch_add(1, Ordering::SeqCst)
    }
}

#[derive(Debug)]
struct Rectangle {
    width: u32,
    height: u32
}

impl Rectangle {
    fn area(&self) -> u32 {
        self.width * self.height
    }
}

fn main() {
    let user1 = build_user(
        String::from("someone@email.com"),
        String::from("someoneuser")
    );

    let user2 = build_user(
        String::from("someone@email.com"),
        String::from("someoneuser")
    );

    //struct的更新语法
    let user3 = User {
        email: String::from("another@email.com"),
        ..user2
    };

    let rect1 = Rectangle {
        width: 30,
        height: 2
    };

    println!("The User ID: {}", user1.sign_id);
    println!("The User ID: {}", user2.sign_id);
    println!("The User is: {:#?}", user3);
    dbg!(&user3);
    dbg!(&rect1.area());
}

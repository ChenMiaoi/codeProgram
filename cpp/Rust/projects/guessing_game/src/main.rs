use std::io;
use std::cmp::Ordering;
use rand::Rng;

fn main() {
    println!("Guess The Number!");

    let secret_number = rand::thread_rng().gen_range(1..=10);

    'game_start: loop {
        let mut guess = String::new();
        println!("Please Enter Your Guess: ");
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");

        let guess: u32 = match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        println!("Your guess: {guess}");

        match guess.cmp(&secret_number) {
            Ordering::Less => println!("Too small!!"),
            Ordering::Greater => println!("Too big!!"),
            Ordering::Equal => {
                println!("You win!!");
                break 'game_start;
            },
        };
    }
}

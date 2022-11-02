fn main() {
    println!("Hello, world!");
    //another_function();
    //print_labeld_measurement(5, 'h');
    let x = five();
    println!("The value is {x}");
}

fn five() -> i32 {
    5
}

fn print_labeld_measurement(value: i32, unit_label: char){
    println!("The measuerment is : {value}{unit_label}");
}

fn another_function(){
    println!("Another function");
}

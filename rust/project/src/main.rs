const fn fib(n: u128) -> u128 {
    const fn helper(n: u128, a: u128, b: u128, i: u128) -> u128 {
        if i <= n {
            helper(n, b, a + b, i + 1)
        }else {
            b
        }
    }
    helper(n, 1, 1, 2)
}

const X: u128 = fib(100);

fn main() {
    println!("{}", X);
}

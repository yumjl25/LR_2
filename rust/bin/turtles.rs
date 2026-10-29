use lr2_rust::set::Set;
use std::io;

fn main() {
    println!("Введите количество черепах N:");
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let n: usize = input.trim().parse().unwrap();

    let mut set = Set::new();
    let mut max_true = 0;

    println!("Введите пары a и b для каждой черепахи:");

    for _ in 0..n {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();
        let mut parts = line.split_whitespace();
        
        if let (Some(a_str), Some(b_str)) = (parts.next(), parts.next()) {
            let a: usize = a_str.parse().unwrap();
            let b: usize = b_str.parse().unwrap();

            if a + b == n - 1 {
                let key = format!("{}_{}", a, b);
                
                if !set.at(&key) {
                    set.add(&key);
                    max_true += 1;
                }
            }
        }
    }

    println!("Максимальное количество правдивых черепах: {}", max_true);
}
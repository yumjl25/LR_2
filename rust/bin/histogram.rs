use lr2_rust::array::Array;
use std::io::{self, Write};

fn main() {
    print!("Введите текст на английском: ");
    io::stdout().flush().unwrap();

    let mut text = String::new();
    io::stdin().read_line(&mut text).unwrap();
    let text = text.trim_end();

    let mut freq = [0; 256];
    let mut max_freq = 0;

    for c in text.chars() {
        if c == ' ' || c == '\n' || c == '\r' {
            continue;
        }
        let idx = c as usize;
        freq[idx] += 1;
        if freq[idx] > max_freq {
            max_freq = freq[idx];
        }
    }

    let mut unique_chars = Array::new();
    for i in 0..256 {
        if freq[i] > 0 {
            let s = (i as u8 as char).to_string();
            unique_chars.push(s); 
        }
    }

    let n = unique_chars.len();
    for i in 0..n {
        for j in 0..(n - i - 1) {
            let s1 = unique_chars.get(j).unwrap();
            let s2 = unique_chars.get(j + 1).unwrap();
            
            let c1 = s1.chars().next().unwrap();
            let c2 = s2.chars().next().unwrap();
            
            if (c1 as usize) > (c2 as usize) {
                unique_chars.set(j, c2.to_string());
                unique_chars.set(j + 1, c1.to_string());
            }
        }
    }

    println!();
    if max_freq == 0 { return; }

    for level in (1..=max_freq).rev() {
        for i in 0..n {
            let s = unique_chars.get(i).unwrap();
            let c = s.chars().next().unwrap();
            if freq[c as usize] >= level {
                print!("#");
            } else {
                print!(" ");
            }
        }
        println!();
    }

    for i in 0..n {
        let s = unique_chars.get(i).unwrap();
        print!("{}", s);
    }
    println!();
}
use lr2_rust::hash::HashSet;
use std::io::{self, Write};

fn is_isomorphic(s: &str, t: &str) -> bool {
    if s.len() != t.len() { return false; }

    let mut set = HashSet::new();

    let s_chars: Vec<char> = s.chars().collect();
    let t_chars: Vec<char> = t.chars().collect();

    for i in 0..s_chars.len() {
        let c1 = s_chars[i];
        let c2 = t_chars[i];

        let key = format!("s_{}_t_{}", c1, c2);
        
        if set.contains(&key) {
            continue;
        }

        let prefix = format!("s_{}_", c1);
        let suffix = format!("_t_{}", c2);

        if set.contains_prefix(&prefix) || set.contains_suffix(&suffix) {
            return false;
        }

        set.add(&key);
    }

    true
}

fn main() {
    print!("Введите первую строку: ");
    io::stdout().flush().unwrap();
    let mut s = String::new();
    io::stdin().read_line(&mut s).unwrap();
    let s = s.trim();

    print!("Введите вторую строку: ");
    io::stdout().flush().unwrap();
    let mut t = String::new();
    io::stdin().read_line(&mut t).unwrap();
    let t = t.trim();

    if is_isomorphic(s, t) {
        println!("Результат: Строки изоморфны (TRUE)");
    } else {
        println!("Результат: Строки не изоморфны (FALSE)");
    }
}
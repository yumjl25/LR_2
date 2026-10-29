use lr2_rust::set::Set;
use std::env;
use std::fs;

fn main() {
    let args: Vec<String> = env::args().collect();
    let mut filename = String::new();
    let mut query = String::new();

    let mut i = 1;
    while i < args.len() {
        if args[i] == "--file" && i + 1 < args.len() {
            filename = args[i + 1].clone();
            i += 2;
        } else if args[i] == "--query" && i + 1 < args.len() {
            query = args[i + 1].clone();
            i += 2;
        } else {
            i += 1;
        }
    }

    if filename.is_empty() || query.is_empty() {
        eprintln!("Usage: {} --file <file> --query '<command>'", args[0]);
        return;
    }

    let mut set = Set::new();

    if let Ok(content) = fs::read_to_string(&filename) {
        for line in content.lines() {
            if line.starts_with("SETADD ") {
                let val = line.trim_start_matches("SETADD ").trim();
                set.add(val);
            }
        }
    }

    let parts: Vec<&str> = query.split_whitespace().collect();
    if parts.len() >= 2 {
        let cmd = parts[0];
        
        if cmd == "SETADD" && parts.len() >= 3 {
            set.add(parts[2]);
            println!("{}", parts[2]);
        } else if cmd == "SETDEL" && parts.len() >= 3 {
            set.del(parts[2]);
            println!("{}", parts[2]);
        } else if cmd == "SET_AT" && parts.len() >= 3 {
            let res = set.at(parts[2]);
            println!("{}", if res { "TRUE" } else { "FALSE" });
        }
    }

    set.save(&filename);
}
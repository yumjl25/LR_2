use lr2_rust::list::List;
use std::io::{self, Write};

fn rebuild_list(cache: &mut List) {
    let mut items = Vec::new();
    for i in 0..cache.len() {
        if let Some(entry) = cache.get_at(i) {
            items.push(entry);
        }
    }
    
    items.sort_by_key(|s| {
        s.split(':').nth(2).unwrap().parse::<u32>().unwrap_or(0)
    });

    while cache.len() > 0 {
        cache.del_head();
    }

    for item in items {
        cache.push_tail(item);
    }
}

fn main() {
    print!("Введите емкость кэша (cap) и количество запросов (Q): ");
    io::stdout().flush().unwrap();
    
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let mut parts = input.split_whitespace();
    let cap: usize = parts.next().unwrap().parse().unwrap();
    let q: usize = parts.next().unwrap().parse().unwrap();

    let mut cache = List::new();
    let mut output = String::new();

    for _ in 0..q {
        let mut line = String::new();
        io::stdin().read_line(&mut line).unwrap();
        let mut cmd_parts = line.split_whitespace();
        
        let cmd = cmd_parts.next().unwrap_or("");
        if cmd.is_empty() { break; }

        if cmd == "SET" {
            let key = cmd_parts.next().unwrap();
            let value = cmd_parts.next().unwrap();
            let key_prefix = format!("{}:", key);

            let mut found_idx = None;
            for i in 0..cache.len() {
                if let Some(entry) = cache.get_at(i) {
                    if entry.starts_with(&key_prefix) {
                        found_idx = Some(i);
                        break;
                    }
                }
            }

            if let Some(idx) = found_idx {
                let old_entry = cache.get_at(idx).unwrap();
                cache.del_value(old_entry);
            } else if cache.len() >= cap {
                rebuild_list(&mut cache); 
                if let Some(_oldest) = cache.del_head() {}
            }

            let entry = format!("{}:{}:1", key, value);
            cache.push_tail(entry);

        } else if cmd == "GET" {
            let key = cmd_parts.next().unwrap();
            let key_prefix = format!("{}:", key);

            let mut found_idx = None;
            for i in 0..cache.len() {
                if let Some(entry) = cache.get_at(i) {
                    if entry.starts_with(&key_prefix) {
                        found_idx = Some(i);
                        break;
                    }
                }
            }

            if let Some(idx) = found_idx {
                let entry = cache.get_at(idx).unwrap();
                let parts: Vec<&str> = entry.split(':').collect();
                let val = parts[1].to_string();
                let freq: u32 = parts[2].parse().unwrap();

                output.push_str(&format!("{} ", val));

                cache.del_value(entry);
                let new_entry = format!("{}:{}:{}", key, val, freq + 1);
                cache.push_tail(new_entry);
            } else {
                output.push_str("-1 ");
            }
        }
        
        rebuild_list(&mut cache);
    }
    println!("Вывод: {}", output.trim());
}
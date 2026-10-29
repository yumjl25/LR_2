use lr2_rust::htree::{HNode, NodeLink};
use std::io::{self, Write};

fn generate_codes(node: &NodeLink, code: String, codes: &mut [String; 256]) {
    if let Some(n) = node {
        let borrowed = n.borrow();
        
        if borrowed.left.is_none() && borrowed.right.is_none() {
            codes[borrowed.ch as usize] = code;
            return;
        }
        
        generate_codes(&borrowed.left, format!("{}0", code), codes);
        generate_codes(&borrowed.right, format!("{}1", code), codes);
    }
}

fn decode(root: &NodeLink, encoded: &str) -> String {
    let mut result = String::new();
    let mut cur = root.clone();

    for bit in encoded.chars() {
        if let Some(ref n) = cur {
            let next = if bit == '0' {
                n.borrow().left.clone()
            } else {
                n.borrow().right.clone()
            };

            if let Some(next_node) = next {
                let is_leaf = next_node.borrow().left.is_none() && next_node.borrow().right.is_none();
                if is_leaf {
                    result.push(next_node.borrow().ch);
                    cur = root.clone();
                } else {
                    cur = Some(next_node);
                }
            }
        }
    }
    result
}

fn main() {
    print!("Введите строку для сжатия: ");
    io::stdout().flush().unwrap();

    let mut text = String::new();
    io::stdin().read_line(&mut text).unwrap();
    let text = text.trim_end();

    if text.is_empty() { return; }

    let mut freq = [0; 256];
    for c in text.chars() {
        freq[c as usize] += 1;
    }

    let mut nodes: [NodeLink; 256] = std::array::from_fn(|_| None);
    let mut count = 0;

    for i in 0..256 {
        if freq[i] > 0 {
            nodes[count] = HNode::new(i as u8 as char, freq[i]);
            count += 1;
        }
    }

    if count == 1 {
        let ch = text.chars().next().unwrap();
        println!("\nТаблица кодов:\n{} : 0", ch);
        let encoded: String = text.chars().map(|_| '0').collect();
        println!("\nЗакодированная строка: {}", encoded);
        println!("Декодированная строка: {}", text);
        return;
    }

    while count > 1 {
        for i in 0..count {
            for j in 0..(count - i - 1) {
                let w1 = nodes[j].as_ref().unwrap().borrow().weight;
                let w2 = nodes[j + 1].as_ref().unwrap().borrow().weight;
                if w1 < w2 {
                    nodes.swap(j, j + 1);
                }
            }
        }

        let right = nodes[count - 1].take();
        count -= 1;
        let left = nodes[count - 1].take();
        count -= 1;

        let parent = HNode::combine(left, right);
        
        nodes[count] = parent;
        count += 1;
    }

    let root = nodes[0].clone();

    let mut codes: [String; 256] = std::array::from_fn(|_| String::new());
    generate_codes(&root, String::new(), &mut codes);

    println!("\nТаблица кодов:");
    for i in 0..256 {
        if !codes[i].is_empty() {
            println!("{} : {}", i as u8 as char, codes[i]);
        }
    }

    let mut encoded = String::new();
    for c in text.chars() {
        encoded.push_str(&codes[c as usize]);
    }
    println!("\nЗакодированная строка: {}", encoded);

    let decoded = decode(&root, &encoded);
    println!("Декодированная строка: {}", decoded);
}
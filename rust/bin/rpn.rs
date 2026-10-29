use lr2_rust::stack::Stack; 

fn main() {
    println!("Введите выражение:");
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input = input.trim();

    let mut stack = Stack::new();

    for token in input.split_whitespace() {
        if token == "+" || token == "-" || token == "*" || token == "/" {
            let b_str = match stack.pop() {
                Some(v) => v,
                None => { println!("Ошибка: недостаточно операндов"); return; }
            };
            let a_str = match stack.pop() {
                Some(v) => v,
                None => { println!("Ошибка: недостаточно операндов"); return; }
            };

            let b: i32 = b_str.parse().unwrap();
            let a: i32 = a_str.parse().unwrap();

            let result = match token {
                "+" => a + b,
                "-" => a - b,
                "*" => a * b,
                "/" => {
                    if b == 0 { println!("Ошибка: деление на ноль"); return; }
                    a / b
                },
                _ => unreachable!(),
            };

            stack.push(result.to_string());
        } else {
            stack.push(token.to_string());
        }
    }

    match stack.pop() {
        Some(res) => println!("Результат: {}", res),
        None => println!("Ошибка: некорректное выражение"),
    }
}
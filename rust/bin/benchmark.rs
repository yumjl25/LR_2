use lr2_rust::hash::HashSet;
use lr2_rust::cuckoo::CuckooTable;
use std::time::Instant;

fn main() {
    let n = 10000;
    println!("Эмпирический анализ хеш-таблиц");
    println!("Количество элементов: {}\n", n);

    let start_chain = Instant::now();
    let mut chain_set = HashSet::new();
    for i in 0..n {
        chain_set.add(&i.to_string());
    }
    let duration_chain = start_chain.elapsed();
    println!("[Метод цепочек]");
    println!("Время вставки: {:?}", duration_chain);

    let start_cuckoo = Instant::now();
    let mut cuckoo_table = CuckooTable::new();
    for i in 0..n {
        cuckoo_table.add(i);
    }
    let duration_cuckoo = start_cuckoo.elapsed();
    println!("[Хеширование кукушки]");
    println!("Время вставки: {:?}", duration_cuckoo);

    let start_search_chain = Instant::now();
    for i in 0..1000 {
        chain_set.contains(&i.to_string());
    }
    let duration_search_chain = start_search_chain.elapsed();

    let start_search_cuckoo = Instant::now();
    for i in 0..1000 {
        cuckoo_table.contains(i);
    }
    let duration_search_cuckoo = start_search_cuckoo.elapsed();

    println!("\n[Поиск 1000 элементов]");
    println!("Цепочки: {:?}", duration_search_chain);
    println!("Кукушка: {:?}", duration_search_cuckoo);
}
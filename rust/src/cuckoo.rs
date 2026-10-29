// Структура ячейки
#[derive(Clone, Copy)]
pub struct CuckooEntry {
    pub key: Option<usize>, 
    pub occupied: bool,
}

pub struct CuckooTable {
    table1: [CuckooEntry; 1024],
    table2: [CuckooEntry; 1024],
    size: usize,
}

impl CuckooTable {
    pub fn new() -> Self {
        CuckooTable {
            table1: [CuckooEntry { key: None, occupied: false }; 1024],
            table2: [CuckooEntry { key: None, occupied: false }; 1024],
            size: 0,
        }
    }

    fn hash1(&self, key: usize) -> usize {
        key % 1024
    }

    fn hash2(&self, key: usize) -> usize {
        (key / 1024) % 1024
    }

    pub fn add(&mut self, key: usize) -> bool {
        let mut cur_key = key;
        let mut use_table1 = true;

        for _ in 0..50 { 
            if use_table1 {
                let idx = self.hash1(cur_key);
                if !self.table1[idx].occupied {
                    self.table1[idx] = CuckooEntry { key: Some(cur_key), occupied: true };
                    self.size += 1;
                    return true;
                }
                let kicked = self.table1[idx].key.unwrap();
                self.table1[idx] = CuckooEntry { key: Some(cur_key), occupied: true };
                cur_key = kicked;
                use_table1 = false;
            } else {
                let idx = self.hash2(cur_key);
                if !self.table2[idx].occupied {
                    self.table2[idx] = CuckooEntry { key: Some(cur_key), occupied: true };
                    self.size += 1;
                    return true;
                }
                // Вытесняем
                let kicked = self.table2[idx].key.unwrap();
                self.table2[idx] = CuckooEntry { key: Some(cur_key), occupied: true };
                cur_key = kicked;
                use_table1 = true;
            }
        }
        false
    }

    pub fn contains(&self, key: usize) -> bool {
        let idx1 = self.hash1(key);
        if self.table1[idx1].occupied && self.table1[idx1].key == Some(key) { return true; }
        
        let idx2 = self.hash2(key);
        if self.table2[idx2].occupied && self.table2[idx2].key == Some(key) { return true; }
        
        false
    }
}
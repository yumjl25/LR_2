use std::collections::hash_map::DefaultHasher;
use std::hash::{Hash, Hasher};

const TABLE_SIZE: usize = 1000;

pub struct HashNode {
    pub key: String,
    pub next: Option<Box<HashNode>>,
}

pub struct HashSet {
    buckets: [Option<Box<HashNode>>; TABLE_SIZE],
    size: usize,
}

impl HashSet {
    pub fn new() -> Self {
        let buckets = std::array::from_fn(|_| None);
        HashSet { buckets, size: 0 }
    }

    fn hash(&self, key: &str) -> usize {
        let mut hasher = DefaultHasher::new();
        key.hash(&mut hasher);
        (hasher.finish() as usize) % TABLE_SIZE
    }

    pub fn add(&mut self, key: &str) {
        let idx = self.hash(key);
        let mut cur = &mut self.buckets[idx];
        
        while let Some(node) = cur {
            if node.key == key { return; }
            cur = &mut node.next;
        }
        
        let new_node = Box::new(HashNode {
            key: key.to_string(),
            next: self.buckets[idx].take(),
        });
        self.buckets[idx] = Some(new_node);
        self.size += 1;
    }

    pub fn get(&self, key: &str) -> Option<String> {
        let idx = self.hash(key);
        let mut cur = &self.buckets[idx];
        while let Some(node) = cur {
            if node.key == key {
                return Some(node.key.clone());
            }
            cur = &node.next;
        }
        None
    }

    pub fn contains(&self, key: &str) -> bool {
        let idx = self.hash(key);
        let mut cur = &self.buckets[idx];
        while let Some(node) = cur {
            if node.key == key { return true; }
            cur = &node.next;
        }
        false
    }

    pub fn contains_prefix(&self, prefix: &str) -> bool {
        for i in 0..TABLE_SIZE {
            let mut cur = &self.buckets[i];
            while let Some(node) = cur {
                if node.key.starts_with(prefix) {
                    return true;
                }
                cur = &node.next;
            }
        }
        false
    }

    pub fn contains_suffix(&self, suffix: &str) -> bool {
        for i in 0..TABLE_SIZE {
            let mut cur = &self.buckets[i];
            while let Some(node) = cur {
                if node.key.ends_with(suffix) {
                    return true;
                }
                cur = &node.next;
            }
        }
        false
    }

    pub fn remove(&mut self, key: &str) {
        let idx = self.hash(key);
        
        let mut current = &mut self.buckets[idx];
        
        while current.is_some() {
            if current.as_ref().unwrap().key == key {
                let mut node = current.take().unwrap();
                *current = node.next.take();
                self.size -= 1;
                return;
            }
            current = &mut current.as_mut().unwrap().next;
        }
    }

    pub fn save_to_file(&self, filename: &str) {
        use std::fs::File;
        use std::io::Write;
        
        let mut file = File::create(filename).unwrap();
        for i in 0..TABLE_SIZE {
            let mut cur = &self.buckets[i];
            while let Some(node) = cur {
                writeln!(file, "SETADD myset {}", node.key).unwrap();
                cur = &node.next;
            }
        }
    }
}
use crate::hash::HashSet;

pub struct Set {
    data: HashSet,
}

impl Set {
    pub fn new() -> Self {
        Set { data: HashSet::new() }
    }
    pub fn add(&mut self, value: &str) { self.data.add(value); }
    pub fn del(&mut self, value: &str) { self.data.remove(value); }
    pub fn at(&self, value: &str) -> bool { self.data.contains(value) }
    pub fn save(&self, filename: &str) { self.data.save_to_file(filename); }
}
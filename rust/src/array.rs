use std::alloc::{alloc, realloc, dealloc, Layout};
use std::ptr;

const INIT_CAPACITY: usize = 4;

pub struct Array {
    pub data: *mut String,
    pub size: usize,
    pub capacity: usize,
}

impl Array {
    pub fn new() -> Array {
        let layout = Layout::array::<String>(INIT_CAPACITY).unwrap();
        let data = unsafe { alloc(layout) as *mut String };
        Array {
            data,
            size: 0,
            capacity: INIT_CAPACITY,
        }
    }

    pub fn len(&self) -> usize {
        self.size
    }

    pub fn is_empty(&self) -> bool {
        self.size == 0
    }

    fn resize(&mut self) {
        let new_capacity = self.capacity * 2;
        let old_layout = Layout::array::<String>(self.capacity).unwrap();
        let new_layout = Layout::array::<String>(new_capacity).unwrap();

        unsafe {
            let new_data = realloc(self.data as *mut u8, old_layout, new_layout.size()) as *mut String;
            self.data = new_data;
            self.capacity = new_capacity;
        }
    }

    pub fn push(&mut self, value: String) {
        if self.size == self.capacity {
            self.resize();
        }
        unsafe {
            ptr::write(self.data.add(self.size), value);
        }
        self.size += 1;
    }

    pub fn push_at(&mut self, value: String, index: usize) {
        if index > self.size {
            println!("Index out of range");
            return;
        }
        if self.size == self.capacity {
            self.resize();
        }
        unsafe {
            for i in (index..self.size).rev() {
                let v = ptr::read(self.data.add(i));
                ptr::write(self.data.add(i + 1), v);
            }
            ptr::write(self.data.add(index), value);
        }
        self.size += 1;
    }

    pub fn get(&self, index: usize) -> Option<&String> {
        if index >= self.size {
            return None;
        }
        unsafe { Some(&*self.data.add(index)) }
    }

    pub fn set(&mut self, index: usize, value: String) {
        if index >= self.size {
            println!("Index out of range");
            return;
        }
        unsafe {
            ptr::drop_in_place(self.data.add(index)); 
            ptr::write(self.data.add(index), value); 
        }
    }

    pub fn del(&mut self, index: usize) -> Option<String> {
        if index >= self.size {
            return None;
        }
        unsafe {
            let value = ptr::read(self.data.add(index)); 
            for i in index..self.size - 1 {
                let v = ptr::read(self.data.add(i + 1));
                ptr::write(self.data.add(i), v);
            }
            self.size -= 1;
            Some(value)
        }
    }

    pub fn print(&self) {
        if self.is_empty() {
            println!("ARRAY: empty");
            return;
        }
        println!("ARRAY:");
        for i in 0..self.size {
            let v = unsafe { &*self.data.add(i) };
            println!("  [{}] {}", i, v);
        }
    }
}

impl Drop for Array {
    fn drop(&mut self) {
        unsafe {
            for i in 0..self.size {
                ptr::drop_in_place(self.data.add(i));
            }
            let layout = Layout::array::<String>(self.capacity).unwrap();
            dealloc(self.data as *mut u8, layout);
        }
    }
}
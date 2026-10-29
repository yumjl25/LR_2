use std::rc::{Rc, Weak};
use std::cell::RefCell;

pub type StrongLink = Option<Rc<RefCell<LNode>>>;
pub type WeakLink   = Option<Weak<RefCell<LNode>>>;

pub struct LNode {
    pub data: String,
    pub prev: WeakLink,
    pub next: StrongLink,
}

pub struct List {
    pub head: StrongLink,
    pub tail: StrongLink,
    pub size: usize,
}

impl List {
    pub fn new() -> List {
        List { head: None, tail: None, size: 0 }
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn push_head(&mut self, value: String) {
        let node = Rc::new(RefCell::new(LNode {
            data: value,
            prev: None,
            next: self.head.clone(),
        }));
        match &self.head {
            Some(head) => { head.borrow_mut().prev = Some(Rc::downgrade(&node)); }
            None => { self.tail = Some(Rc::clone(&node)); }
        }
        self.head = Some(node);
        self.size += 1;
    }

    pub fn push_tail(&mut self, value: String) {
        let node = Rc::new(RefCell::new(LNode {
            data: value,
            prev: self.tail.as_ref().map(|t| Rc::downgrade(t)),
            next: None,
        }));
        match &self.tail {
            Some(tail) => { tail.borrow_mut().next = Some(Rc::clone(&node)); }
            None => { self.head = Some(Rc::clone(&node)); }
        }
        self.tail = Some(node);
        self.size += 1;
    }

    pub fn push_before(&mut self, target: String, value: String) {
        if let Some(head) = self.head.clone() {
            if head.borrow().data == target {
                self.push_head(value);
                return;
            }
        }
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == target {
                let prev = node.borrow().prev.clone();
                let new_node = Rc::new(RefCell::new(LNode {
                    data: value,
                    prev: prev.clone(),
                    next: Some(Rc::clone(&node)),
                }));
                node.borrow_mut().prev = Some(Rc::downgrade(&new_node));
                match prev {
                    Some(weak) => {
                        if let Some(prev_rc) = weak.upgrade() {
                            prev_rc.borrow_mut().next = Some(Rc::clone(&new_node));
                        }
                    }
                    None => { self.head = Some(Rc::clone(&new_node)); }
                }
                self.size += 1;
                return;
            }
            cur = node.borrow().next.clone();
        }
        println!("Target not found");
    }

    pub fn push_after(&mut self, target: String, value: String) {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == target {
                let next = node.borrow().next.clone();
                let new_node = Rc::new(RefCell::new(LNode {
                    data: value,
                    prev: Some(Rc::downgrade(&node)),
                    next: next.clone(),
                }));
                node.borrow_mut().next = Some(Rc::clone(&new_node));
                match next {
                    Some(n) => { n.borrow_mut().prev = Some(Rc::downgrade(&new_node)); }
                    None => { self.tail = Some(Rc::clone(&new_node)); }
                }
                self.size += 1;
                return;
            }
            cur = node.borrow().next.clone();
        }
        println!("Target not found");
    }

    pub fn len(&self) -> usize {
        self.size
    }

    pub fn get_head(&self) -> Option<String> {
        self.head.as_ref().map(|node| node.borrow().data.clone())
    }

    pub fn get_tail(&self) -> Option<String> {
        self.tail.as_ref().map(|node| node.borrow().data.clone())
    }

    pub fn get_at(&self, index: usize) -> Option<String> {
        if index >= self.size {
            return None;
        }
        let mut cur = self.head.clone();
        for _ in 0..index {
            if let Some(node) = cur {
                cur = node.borrow().next.clone();
            } else {
                return None;
            }
        }
        cur.map(|node| node.borrow().data.clone())
    }

    pub fn del_head(&mut self) -> Option<String> {
        match self.head.take() {
            None => None,
            Some(head) => {
                let value = head.borrow().data.clone();
                let next = head.borrow().next.clone();
                match &next {
                    Some(n) => { n.borrow_mut().prev = None; }
                    None => { self.tail = None; }
                }
                self.head = next;
                self.size -= 1;
                Some(value)
            }
        }
    }

    pub fn del_tail(&mut self) -> Option<String> {
        match self.tail.take() {
            None => None,
            Some(tail) => {
                let value = tail.borrow().data.clone();
                let prev = tail.borrow().prev.clone();
                match prev {
                    Some(weak) => {
                        if let Some(prev_rc) = weak.upgrade() {
                            prev_rc.borrow_mut().next = None;
                            self.tail = Some(Rc::clone(&prev_rc));
                        }
                    }
                    None => { self.head = None; }
                }
                self.size -= 1;
                Some(value)
            }
        }
    }

    pub fn del_value(&mut self, value: String) -> bool {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == value {
                let prev = node.borrow().prev.clone();
                let next = node.borrow().next.clone();
                match &prev {
                    Some(weak) => {
                        if let Some(prev_rc) = weak.upgrade() {
                            prev_rc.borrow_mut().next = next.clone();
                        }
                    }
                    None => { self.head = next.clone(); }
                }
                match &next {
                    Some(n) => { n.borrow_mut().prev = prev.clone(); }
                    None => {
                        match prev {
                            Some(weak) => {
                                if let Some(prev_rc) = weak.upgrade() {
                                    self.tail = Some(prev_rc);
                                }
                            }
                            None => { self.tail = None; }
                        }
                    }
                }
                self.size -= 1;
                return true;
            }
            cur = node.borrow().next.clone();
        }
        false
    }

    pub fn search(&self, value: String) -> bool {
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            if node.borrow().data == value { return true; }
            cur = node.borrow().next.clone();
        }
        false
    }

    pub fn print(&self) {
        if self.is_empty() {
            println!("LIST: empty");
            return;
        }
        println!("LIST:");
        let mut cur = self.head.clone();
        while let Some(node) = cur {
            println!("  {}", node.borrow().data);
            cur = node.borrow().next.clone();
        }
    }
}
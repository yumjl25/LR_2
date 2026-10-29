use std::rc::Rc;
use std::cell::RefCell;

pub type NodeLink = Option<Rc<RefCell<HNode>>>;

pub struct HNode {
    pub ch: char,           
    pub weight: usize,      
    pub left: NodeLink,
    pub right: NodeLink,
}

impl HNode {
    pub fn new(ch: char, weight: usize) -> NodeLink {
        Some(Rc::new(RefCell::new(HNode {
            ch,
            weight,
            left: None,
            right: None,
        })))
    }

    pub fn combine(left: NodeLink, right: NodeLink) -> NodeLink {
        let w_left = left.as_ref().unwrap().borrow().weight;
        let w_right = right.as_ref().unwrap().borrow().weight;

        Some(Rc::new(RefCell::new(HNode {
            ch: '\0',
            weight: w_left + w_right,
            left,
            right,
        })))
    }
}
pub struct SNode {
    pub data: String,
    pub next: Option<Box<SNode>>,
}

pub struct Stack {
    pub head: Option<Box<SNode>>,
}

impl Stack {
    pub fn new() -> Stack {
        Stack { head: None }
    }

    pub fn is_empty(&self) -> bool {
        self.head.is_none()
    }

    pub fn push(&mut self, value: String) {
        let node = SNode { data: value, next: self.head.take() };
        self.head = Some(Box::new(node));
    }

    pub fn pop(&mut self) -> Option<String> {
        match self.head.take() {
            None => None,
            Some(node) => {
                self.head = node.next;
                Some(node.data)
            }
        }
    }

    pub fn get(&self) -> Option<String> {
        match &self.head {
            None => None,
            Some(node) => Some(node.data.clone()),
        }
    }

    pub fn print(&self) {
        if self.is_empty() {
            println!("STACK: empty");
            return;
        }
        println!("STACK:");
        let mut cur = &self.head;
        while let Some(node) = cur {
            println!("  {}", node.data);
            cur = &node.next;
        }
    }
}
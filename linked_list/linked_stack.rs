use std::mem;

struct Node<T> {
    el: T,
    next: Link<T>,
}

type Link<T> = Option<Box<Node<T>>>;

pub struct List<T> {
    head: Link<T>,
}

impl<T> List<T> {
    pub fn new() -> Self {
        List { head: None }
    }

    pub fn push(&mut self, val: T) {
        let new_el: Link<T> = Some(Box::new(Node {
            el: val,
            next: self.head.take(),
        }));
        self.head = new_el;
    }

    pub fn pop(&mut self) -> Option<T> {
        self.head.take().map(|boxed| {
            self.head = boxed.next;
            boxed.el
        })
    }

    pub fn top(&mut self) -> Option<&T> {
        self.head.as_ref().map(|boxed| &(boxed.el))
    }

    pub fn length(&self) -> i32 {
        let mut length = 0;
        let mut iter = &self.head;
        while let Some(boxed) = iter {
            length += 1;
            iter = &boxed.next;
        }
        length
    }
}

impl<T> Drop for List<T> {
    fn drop(&mut self) {
        let mut cur_link = mem::replace(&mut self.head, None);

        while let Some(mut boxed_node) = cur_link {
            cur_link = mem::replace(&mut boxed_node.next, None);
        }
    }
}

#[test]
fn test_push() {
    let mut my_list = List::new();
    my_list.push(123);
    assert_eq!(my_list.top().unwrap(), &123);
}

#[test]
fn test_pop() {
    let mut my_list = List::new();
    my_list.push(123);
    my_list.push(124);
    assert_eq!(my_list.pop().unwrap(), 124);
}

#[test]
fn test_zero_length() {
    let my_list = List::<i32>::new();
    assert_eq!(my_list.length(), 0);
}

#[test]
fn test_non_zero_length() {
    let mut my_list = List::new();
    my_list.push(123);
    my_list.push(124);
    my_list.push(125);
    assert_eq!(my_list.length(), 3);
}

fn main() {
    let mut my_list = List::new();
    let mut top = my_list.top();
    println!("Hello, {:?}!", top);
    my_list.push(124);
    top = my_list.top();
    println!("Hello, {:?}!", top);
}

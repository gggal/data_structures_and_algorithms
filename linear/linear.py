class Stack:

    def __init__(self):
        self.arr = []

    def push(self, el):
        self.arr.append(el)

    def pop(self):
        self.arr.pop(len(self.arr) - 1)

    def peek(self):
        return self.arr[len(self.arr) - 1]

    def length(self):
        return len(self.arr)
    
class Queue:

    def __init__(self):
        self.arr = []

    def enqueue(self, el):
        self.arr.append(el)

    def dequeue(self):
        self.arr.pop(0)

    def peek(self):
        return self.arr[0]

    def length(self):
        return len(self.arr)

class CyclicQueue:

    class Node:

        def __init__(self, value, prev_node, next_node):
            self.val = value
            self.prev = prev_node
            self.next = next_node

    def __init__(self):
        start = CyclicQueue.Node(None, None, None)
        start.prev = start.next = start
        self.frm = start
        self.to = start
        self.size = 0

    def enqueue(self, el):
        if self.to.next == self.frm:
            self.resize()

        self.to.val = el
        self.to = self.to.next
        self.size += 1

    def dequeue(self):
        if self.size != 0:
            self.frm = self.frm.next
            self.size -= 1

    def peek(self):
        if self.size != 0:
            return self.frm.val
        return None

    def length(self):
        return self.size

    def resize(self):
        prev_node = self.to
        next_node = self.to.next

        new_node = CyclicQueue.Node(None, prev_node, next_node)
        prev_node.next = new_node
        next_node.prev = new_node


my_stack = Stack()
assert(my_stack.length() == 0)

for i in range(10):
    my_stack.push(i);
    assert(my_stack.length() == i + 1)
    assert(my_stack.peek() == i)

my_stack.pop()
assert(my_stack.peek() == 8)
assert(my_stack.length() == 9)

# queue

my_queue = Queue();
assert(my_queue.length() == 0)

for i in range(10):
    my_queue.enqueue(i)
    assert(my_queue.length() == i + 1)


for i in range(10):
    assert(my_queue.peek() == i)
    my_queue.dequeue()
    assert(my_queue.length() == 10 - i - 1)


my_cyclic_queue = CyclicQueue()


for i in range(10):
    my_cyclic_queue.enqueue(i)
    assert(my_cyclic_queue.length() == i + 1)


for i in range(10):
    assert(my_cyclic_queue.peek() == i)
    my_cyclic_queue.dequeue()
    assert(my_cyclic_queue.length() == 10 - i - 1)




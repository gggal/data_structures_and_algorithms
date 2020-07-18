class Node:

    def __init__(self, val, next_node):
        self.val = val
        self.next_node = next_node

class SinglyLinkedList:

    def __init__(self):
        self.start = None

    def add_element(self, el):
        self.start = Node(el, self.start)

    def contains_element(self, el):
        return self.find_node(self.start, el) is not None

    def get_by_index(self, idx):
        node = self.get_by_index_helper(self.start, idx)
        return None if node is None else node.val

    def remove_by_index(self, idx):
        if idx == 0 and self.start is not None:
            self.start = self.start.next_node
        else:
            prev_node = self.get_by_index_helper(self.start, idx - 1)
            to_remove = prev_node.next_node if prev_node is not None else None
            next_node = to_remove.next_node if to_remove is not None else None
            prev_node.next_node = next_node

    def remove_element(self, el):
        if self.start is not None and el == self.start.val:
            self.start = self.start.next_node
        else:
            prev_node = self.find_prev_node(self.start, el)
            to_remove = prev_node.next_node if prev_node is not None else None
            next_node = to_remove.next_node if to_remove is not None else None
            prev_node.next_node = next_node

    def length(self):
        return self.length_helper(self.start, 0)

    @staticmethod
    def find_prev_node(node, el):
        if node is None or node.next_node is None:
            return None
        elif node.next_node.val == el:
            return node
        else:
            return SinglyLinkedList.find_prev_node(node.next_node, el)

    @staticmethod
    def find_node(node, el):
        if node is not None and node.val == el:
            return node
        else:
            prev_node = SinglyLinkedList.find_prev_node(node, el)
            return prev_node.next_node if prev_node is not None else None 

    @staticmethod
    def get_by_index_helper(node, left):
        if node is None:
            return None
        elif left == 0:
            return node
        else:
            return SinglyLinkedList.get_by_index_helper(node.next_node, left - 1)

    @staticmethod
    def length_helper(node, accum_length):
        if node is None:
            return accum_length
        else:
            return SinglyLinkedList.length_helper(node.next_node, accum_length + 1)


my_list = SinglyLinkedList()
assert my_list.length() == 0

my_list.add_element(2);
my_list.add_element(3);

assert my_list.length() == 2
assert my_list.contains_element(2)
assert my_list.contains_element(3)
assert not my_list.contains_element(1)
assert my_list.get_by_index(0) == 3
assert my_list.get_by_index(1) == 2
assert my_list.get_by_index(3) == None

	# remove first element
my_list.remove_element(3)
assert not my_list.contains_element(3)
assert my_list.length() == 1

	# remove single element
my_list.remove_element(2)
assert not my_list.contains_element(2)
assert my_list.length() == 0
	
	# remove last element
my_list.add_element(2);
my_list.add_element(3);
my_list.remove_element(2)
assert not my_list.contains_element(2)
assert my_list.length() == 1

	# remove by index
my_list.add_element(1);
my_list.add_element(2);
my_list.remove_by_index(2)
assert my_list.length() == 2
my_list.remove_by_index(1)
assert my_list.length() == 1
my_list.remove_by_index(0)
assert my_list.length() == 0
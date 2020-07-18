class BSTree:

    class Node:
        def __init__(self, value):
            self.val = value
            self.left = None
            self.right = None


    def __init__(self):
        self.root = None

    def add_element(self, el):
        if self.root is None:
            self.root = BSTree.Node(el)
        else:
            self.add_element_helper(self.root, el)

    def contains_element(self, el):
        return self.get_node(self.root, el) is not None

    def delete_element(self, el):
        parent = self.get_parent(self.root, el)
        to_replace = self.get_node(self.root, el)

        if to_replace is not None:
            if to_replace.left is not None:
                to_replace.val = self.prune(to_replace)
            elif parent is None: # root is to be deleted
                self.root = self.root.right
            elif parent and parent.left == to_replace: # the element being deleted is the smallest one
                parent.left = to_replace.right
            elif parent and parent.right == to_replace:
                parent.right = to_replace.right


    def print(self):
        print("Tree: ", end=" ")
        self.traverse(self.root)
        print()

    @staticmethod
    def traverse(tree):
        if tree is not None:
            BSTree.traverse(tree.left)
            print(tree.val, end=" ")
            BSTree.traverse(tree.right)

    @staticmethod
    def get_node(tree, el):
        if tree is None or tree.val == el:
            return tree
        elif tree.val < el:
            return BSTree.get_node(tree.right, el)
        else:
            return BSTree.get_node(tree.left, el)

    @staticmethod
    def add_element_helper(tree, el):
        if el < tree.val:
            if tree.left is None:
                tree.left = BSTree.Node(el)
            else:
                BSTree.add_element_helper(tree.left, el)
        else:
            if tree.right is None:
                tree.right = BSTree.Node(el)
            else:
                BSTree.add_element_helper(tree.right, el)

    @staticmethod
    def prune(tree):
        if tree is None or tree.left is None:
            return None
        elif tree.left.left is None:
            min_val = tree.left.val
            tree.left = tree.left.right
            return min_val
        else:
            return BSTree.prune(tree.left)

    @staticmethod
    def get_parent(tree, el):
        if tree is None:
            return None
        elif tree.left and tree.left.val == el or tree.right and tree.right.val == el:
            return tree
        elif el < tree.val:
            return BSTree.get_parent(tree.left, el)
        else:
            return BSTree.get_parent(tree.right, el)

    
myTree = BSTree()
myTree.add_element(2)
myTree.add_element(1)
myTree.add_element(3)

assert(myTree.contains_element(1))
assert(myTree.contains_element(2))
assert(myTree.contains_element(3))
assert(not myTree.contains_element(4))

myTree.delete_element(3)

myTree.print()

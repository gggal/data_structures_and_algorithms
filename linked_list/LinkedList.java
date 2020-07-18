class LinkedList {

    // inner static class so it can be called without a Main instance
    static class SinglyLinkedList<T> {

        static class Node<T> {
            private Node<T> nextNode;
            private T val;

            public Node(Node<T> nextNode, T val) {
                this.nextNode = nextNode;
                this.val = val;
            }

            public T getVal() {
                return this.val;
            }

            public Node<T> getNextNode() {
                return this.nextNode;
            }

            public void setVal(T val) {
                this.val = val;
            }

            public void setNextNode(Node<T> nextNode) {
                this.nextNode = nextNode;
            }
        }

        private Node<T> start;

        public SinglyLinkedList() {
            this.start = null;
        }

        public void addElement(T el) {
            this.start = new Node<>(start, el);
        }

        public boolean containsElement(T el) {
            return findElement(start, el) != null;
        }

        public T getByIndex(int index) {
            Node<T> node = getByIndexHelper(start, index);
            return (node != null ? node.getVal() : null);
        }

        public void removeByIndex(int idx) {
            if(start != null && idx == 0) {
                this.start = this.start.getNextNode();
            } else {
                removeNext(getByIndexHelper(start, idx - 1));
            }
        }

        public void removeElement(T el) {
            if(start != null && start.getVal() == el) {
                start = start.nextNode;
            } else {
                removeNext(findPrevElement(start, el));
            }
        }

        public int length() {
            return lengthHelper(start, 0);
        }

        private Node<T> findElement(Node<T> currNode, T toFind) {
            if(currNode != null && currNode.getVal() == toFind) {
                return currNode;
            } else {
                Node<T> prevNode = findPrevElement(currNode, toFind);
                return prevNode != null ? prevNode.getNextNode() : null;
            }
        }

        private Node<T> findPrevElement(Node<T> currNode, T toFind) {
            if(currNode == null || currNode.nextNode == null) {
                return null;
            } else if(currNode.getNextNode().getVal() == toFind) {
                return currNode;
            } else {
                return findPrevElement(currNode.getNextNode(), toFind);
            }
        }

        private Node<T> getByIndexHelper(Node<T> currNode, int idxLeft) {
            if(idxLeft == 0) {
                return currNode;
            } else if (currNode == null) {
                return null;
            } else {
                return getByIndexHelper(currNode.getNextNode(), idxLeft - 1);
            }
        }

        private void removeNext(Node<T> prevNode) {
            if(prevNode != null && prevNode.getNextNode() != null) {
                Node<T> toRemove = prevNode.getNextNode();
                prevNode.setNextNode(toRemove.getNextNode());
            }
        }

        private int lengthHelper(Node<T> currNode, int currLength) {
            return currNode == null ? currLength : lengthHelper(currNode.getNextNode(), currLength + 1);
        }

    }

    public static void main(String[] args) {
        SinglyLinkedList<Integer> myList = new SinglyLinkedList<>();
        assert(myList.length() == 0);

        myList.addElement(2);
        myList.addElement(3);

        assert(myList.length() == 2);
        assert(myList.containsElement(2));
        assert(myList.containsElement(3));
        assert(!myList.containsElement(1));
        assert(myList.getByIndex(0) == 3);
        assert(myList.getByIndex(1) == 2);
        assert(myList.getByIndex(3) == null);

        // remove first element
        myList.removeElement(3);
        assert(!myList.containsElement(3));
        assert(myList.length() == 1);

        // remove single element
        myList.removeElement(2);
        assert(!myList.containsElement(2));
        assert(myList.length() == 0);

        // remove last element
        myList.addElement(2);
        myList.addElement(3);
        myList.removeElement(2);
        assert(!myList.containsElement(2));
        assert(myList.length() == 1);

        // remove by index
        myList.addElement(1);
        myList.addElement(2);
        myList.removeByIndex(2);
        assert(myList.length() == 2);
        myList.removeByIndex(1);
        assert(myList.length() == 1);
        myList.removeByIndex(0);
        assert(myList.length() == 0);
    }
}
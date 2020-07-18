#include <cassert>
#include <iostream>

template <typename T>
class Vector 
{
public:

    Vector()
    {
        arr = nullptr;
        size = 0;
        capacity = 0;
    }

    ~Vector() 
    {
        delete[] arr;
        size = 0;
        capacity = 0;
    }

    void add(T el)
    {
        if(size == capacity) {
            resize();
        }

        arr[size++] = el;
    }

    bool remove(int index)
    {
        if(index >= size || index < 0) {
            return false;
        } else {
            for (int i = index; i < size - 1; ++i) {
                arr[i] = arr[i + 1];
            }
            --size;
            return true;
        }
    }

    const T* get(int index) const
    {
        if(index >= size || index < 0) {
            return nullptr;
        } else {
            return &arr[index];
        }
    }

    int length() const
    {
        return size;
    }

    void debug()
    {
        for(int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }

private:

    void resize()
    {
        T* toDelete = arr;
        capacity = (capacity == 0 ? 1 : capacity) * 2;
        T* new_arr = new T[capacity];
        for(int i = 0; i < size; ++i) {
            new_arr[i] = arr[i];
        }
        arr = new_arr;
        delete[] toDelete;
    }

private:
    T* arr;
    int size;
    int capacity;
};

template <typename T>
class Stack: public Vector<T>
{

public:
    void push(T el)
    {
        Vector<T>::add(el);
    }

    void pop()
    {
        if(Vector<T>::length() != 0) {
            Vector<T>::remove(Vector<T>::length() - 1);
        }
    }

    const T* peek() const
    {
        if(Vector<T>::length() != 0) {
            return Vector<T>::get(Vector<T>::length() - 1);
        } else {
            return nullptr;
        }
    }
};

template <typename T>
class Queue: public Vector<T>
{
public:
    void enqueue(T el)
    {
        Vector<T>::add(el);
    }

    void dequeue()
    {
        if(Vector<T>::length() != 0) {
            Vector<T>::remove(0);
        }
    }

    const T* peek() const
    {
        if(Vector<T>::length() != 0) {
            return Vector<T>::get(0);
        } else {
            return nullptr;
        }
    }
    
};

template <typename T>
class CyclicQueue
{
    struct Node
    {
        T val;
        Node* next, *prev;
    };

public:

    CyclicQueue()
    {
        Node* initNode = new Node();
        initNode->next = initNode;
        initNode->prev = initNode;

        from = to = initNode;
        size = 0;
    }

    ~CyclicQueue()
    {
        del(from);
    }

    void enqueue(T el)
    {
        if (from == to->next) {
            resize();
        }
        
        to->val = el;
        to = to->next;
        ++size;
    }

    void dequeue()
    {
        if (from != nullptr && from != to) {
            from = from->next;
            --size;
        }

    }

    const T* peek() const
    {
        if (from != nullptr && from != to) {
            return &from->val;
        } else {
            return nullptr;
        }
    }

    int length() const
    {
        return size;
    }

private:

    // must only be called when the queue is full
    void resize()
    {
        int numToAdd = size == 0 ? 1 : size;
        // std::cout << "resizing " << size << std::endl;
        for(int i = 0; i < numToAdd; ++i) {
            addNode();
        }
        
    }

    void addNode()
    {
        Node* prevNode = to;
        Node* nextNode = to->next;

        Node* newNode = new Node();
        newNode->prev = prevNode;
        newNode->next = nextNode;
        nextNode->prev = newNode;
        prevNode->next = newNode;
    }

    void del(Node* toDelete)
    {
        del(toDelete->next);
        delete toDelete;
        toDelete = nullptr;
    }

private:
    Node* from, *to;
    int size;
};

// linked deque, priority queue
int main()
{
    // stack

    Stack<int>* myStack = new Stack<int>();
    assert(myStack->length() == 0);

    for(int i = 0; i < 10; ++i) {
        myStack->push(i);
        assert(myStack->length() == i + 1);
        assert(*(myStack->peek()) == i);
    }
    myStack->pop();
    assert(*(myStack->peek()) == 8);
    assert(myStack->length() == 9);
    
    // queue

    Queue<int>* myQueue = new Queue<int>();
    assert(myQueue->length() == 0);

    for(int i = 0; i < 10; ++i) {
        // myQueue->debug();
        myQueue->enqueue(i);
        assert(myQueue->length() == i + 1);
    }

    for(int i = 0; i < 10; ++i) {
        assert(*(myQueue->peek()) == i);
        myQueue->dequeue();
        assert(myQueue->length() == 10 - i - 1);
    }

    CyclicQueue<int>* myCyclicQueue = new CyclicQueue<int>();


    for(int i = 0; i < 10; ++i) {
        myCyclicQueue->enqueue(i);
        assert(myCyclicQueue->length() == i + 1);
    }

    for(int i = 0; i < 10; ++i) {
        assert(*(myCyclicQueue->peek()) == i);
        myCyclicQueue->dequeue();
        assert(myCyclicQueue->length() == 10 - i - 1);
    }

    return 0;
}
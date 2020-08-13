#include <vector>
#include <cassert>
#include <iostream>
using std::vector;

template<typename T>
class LinearHeap
{

public: 

    LinearHeap()
    {
        array = vector<T*>();
    }

    void push(T* el)
    {
        array.push_back(el);
        siftUp(array.size() - 1);
    }

    void pop()
    {
        array.at(0) = array.at(array.size() - 1);
        array.pop_back();
        siftDown(0);
    }

    T* top()
    {
        if (array.empty()) {
            return nullptr;
        }
        return array[0];
    }

    static LinearHeap<T>* heapify(vector<T*>* list)
    {
        LinearHeap<T>* toReturn = new LinearHeap<T>();
        for (T*& el : *list) {
            toReturn->push(el);
        }
        return toReturn;
    }

    static vector<T*>* heapsort(vector<T*>* unsorted)
    {
        LinearHeap<T>* heap = heapify(unsorted);
        vector<T*>* toReturn = new vector<T*>();
        while (heap->top() != nullptr) {
            toReturn->push_back(heap->top());
            heap->pop();
        }
        return toReturn;
    }

private:

    int parent(int el)
    {
        if ( el == 0)
            return -1;
        return (el - 1) / 2;
    }

    int leftChild(int el)
    {
        int left = 2 * el + 1;
        return (left < array.size() && el != -1) ? left : -1;
    }

    int rightChild(int el)
    {
        int right = 2 * el + 2;
        return (right < array.size() && el != -1) ? right : -1;
    }

    void siftUp(int currPos)
    {
        int parentPos = parent(currPos);
        while (parentPos >= 0) {
            if (*array.at(currPos) < *array.at(parentPos)) {
                swapElements(array.at(currPos), array.at(parentPos));
                currPos = parentPos;
                parentPos = parent(parentPos);
            } else {
                break;
            }
        }
    }

    void siftDown(int currPos)
    {
        int next = nextSmallestIdx(currPos);
        while(next != -1) {
            if (*array.at(next) >= *array.at(currPos)) {
                break;
            }
            swapElements(array.at(currPos), array.at(next));
            currPos = next;
            next = nextSmallestIdx(currPos);
        }
    }

    // returns the index of the smaller child (if such exists).
    int nextSmallestIdx(int currPos)
    {
        int left = leftChild(currPos);
        int right = rightChild(currPos);
        if (currPos >= array.size()) {
            return -1;
        } else if (left == -1) {
            return right;
        } else if (right == -1) {
            return left;
        } else {
            return (*array.at(right) <= *array.at(left)) ? right : left;
        }
    }

    void swapElements(T*& first, T*& sec) {
        T* temp = first;
        first = sec;
        sec = temp;
    }

private:
    vector<T*> array;
};

int main()
{
    int* arr = new int[6]{1,2,3,4,5,6};

    LinearHeap<int>* myHeap = new LinearHeap<int>();

    for (int i = 5; i >= 0; --i) {
        myHeap->push(arr+i);
    }
    
    for(int i = 0; i < 6; i++) {
        assert(myHeap->top() == arr + i);
        myHeap->pop();
    }

    vector<int*>* vec = new vector<int*>({new int(3), new int(2), new int(1), new int(6), new int(5), new int(4)});
    auto heap = LinearHeap<int>::heapify(vec);
    vector<int*>* sorted = heap->heapsort(vec);
    for(auto el : *sorted) {
        std::cout << *el << " ";
    }
    std::cout << std::endl;

    // dealocate memory
    delete[] arr;
    for(auto el : *vec)
        delete el;
    delete vec;
    delete heap;
    delete sorted;

    return 0;
}
#include <cassert>

// I won't be separating class definition from class declaration for simplicity reason
template <typename T>
class SinglyLinkedList
{
private:

	struct Node 
	{
		T val;
		Node* nextNode;
	};

public:

	~SinglyLinkedList()
	{
		delete(this.start)
	}

	void addElement(T el) 
	{
		Node* newNode = new Node();
		newNode->val = el;
		newNode->nextNode = start;
		start = newNode;
	}

	void removeElement(T el) 
	{
		if(start != nullptr && start->val == el) {
			start = start->nextNode;
		} else {
			Node* prevNode = findPrevElement(start, el);
			removeNext(prevNode);
		}

	}

	void removeByIndex(int idx) 
	{
		if(start != nullptr && 0 == idx) {
			start = start->nextNode;
		} else {
			Node* prevNode = getByIndexHelper(start, idx - 1);	
			removeNext(prevNode);
		}
	}

	bool containsElement(T el)
	{
		return findElement(start, el) != nullptr;
	}

	T getByIndex(int idx)
	{
		Node* node = getByIndexHelper(start, idx);
		// assuming only non-negative numbers are supported
		return node != nullptr ? node->val : -1;
	}

	int length()
	{
		return lengthHelper(start, 0);
	}
	
private:
	
	Node* findPrevElement(Node* currNode, T toFind) 
	{
		if (currNode == nullptr || currNode->nextNode == nullptr) {
			return nullptr;
		} else if ((currNode->nextNode)->val == toFind) {
			return currNode;
		} else {
			return findElement(currNode->nextNode, toFind);
		}
	}

	Node* findElement(Node* currNode, T toFind)
	{
		if(currNode != nullptr && currNode->val == toFind) {
			return currNode;
		}

		Node* prevNode = findPrevElement(currNode, toFind);
		return prevNode != nullptr ? prevNode->nextNode : nullptr;
	}

	Node* getByIndexHelper(Node* currNode, int idxLeft)
	{
		if(idxLeft == 0) {
			return currNode;
		} else if (currNode == nullptr) {
			return currNode;
		} else {
			return getByIndexHelper(currNode->nextNode, --idxLeft);
		}
	}

	void removeNext(Node* prevNode)
	{
		if(prevNode != nullptr)
		{
			Node* toRemove = prevNode->nextNode;
			Node* nextNode = toRemove != nullptr ? toRemove->nextNode : nullptr;
			prevNode->nextNode = nextNode;
			delete toRemove;
		}
	}

	int lengthHelper(Node* currNode, int currLength)
	{
		return currNode == nullptr ? currLength : lengthHelper(currNode->nextNode, currLength+1);	
	}

	void delete(Node* node)
	{
		if(node != nulltr) 
		{
			delete(node->nextNode);
			delete node;
		}
	}

	Node* start;
	
};

int main()
{	
	SinglyLinkedList<int>* myList = new SinglyLinkedList<int>();
	// we start with empty list
	assert(myList->length() == 0);
	
	// adding new elements
	myList->addElement(2);
	myList->addElement(3);

	assert(myList->length() == 2);
	assert(myList->containsElement(2));
	assert(myList->containsElement(3));
	assert(!myList->containsElement(1));
	assert(myList->getByIndex(0) == 3);
	assert(myList->getByIndex(1) == 2);
	assert(myList->getByIndex(3) == -1);

	// remove first element
	myList->removeElement(3);
	assert(!myList->containsElement(3));
	assert(myList->length() == 1);

	// remove single element
	myList->removeElement(2);
	assert(!myList->containsElement(2));
	assert(myList->length() == 0);
	
	// remove last element
	myList->addElement(2);
	myList->addElement(3);
	myList->removeElement(2);
	assert(!myList->containsElement(2));
	assert(myList->length() == 1);

	// remove by index
	myList->addElement(1);
	myList->addElement(2);
	myList->removeByIndex(2);
	assert(myList->length() == 2);
	myList->removeByIndex(1);
	assert(myList->length() == 1);
	myList->removeByIndex(0);
	assert(myList->length() == 0);
	

	return 0;
}

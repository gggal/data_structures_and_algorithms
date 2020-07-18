#include <cassert>
#include <iostream>
#include <vector>

template <typename T>
class BSTree
{
    struct Node
    {
        T val;
        Node* left, *right;

        Node(T val)
        {
            this->val = val;
            left = right = nullptr;
        }
    };

public:

    BSTree()
    {
        root = nullptr;
    }

    ~BSTree()
    {
        if (root != nullptr) {
            deleteTree(root);
        }
    }

    void addElement(T el)
    {
        if (root == nullptr) {
            root = new Node(el);
        } else {
            addElementHelper(root, el);
        }
    }

    void deleteElement(T el)
    {
        Node* toDelete = findElement(root, el);
        if (toDelete != nullptr) {
            if (toDelete->left == nullptr) { // the element to delete is the smallest element
                Node* parent = findParentElement(root, toDelete->val);
                bool leftSucc = parent->left == toDelete;
                delete toDelete;
                
                if(leftSucc) {
                    parent->left = toDelete->right != nullptr ? toDelete->right : nullptr;
                } else {
                    parent->right = toDelete->right != nullptr ? toDelete->right : nullptr;
                }
                
            } else {
                T newValue = pruneSmallestElement(toDelete);
                toDelete->val = newValue;
            }
        }
    }

    bool containsElement(T el)
    {
        Node* node = findElement(root, el);
        return node != nullptr;
    }

    void print()
    {
        std::cout << "Tree: " << std::endl;
        bfs(root);
        std::cout << std::endl;
    }

private:

    void deleteTree(Node* tree)
    {
        deleteTree(tree->left);
        deleteTree(tree->right);
        delete tree;
    }

    void addElementHelper(Node* tree, T el)
    {
        // duplicate elements are not supported
        if (tree == nullptr || tree->val == el) {
            return;
        } 
        
        Node** nextNode = el < tree->val ? &tree->left : &tree->right; 
        
        if (*nextNode == nullptr) {
            *nextNode = new Node(el);

        } else {
            addElementHelper(*nextNode, el);
        }
    }

    Node* findElement(Node* tree, T el)
    {
        if (tree == nullptr || tree->val == el) {
            return tree;
        }

        Node* nextNode = el < tree->val ? tree->left : tree->right; 
        return findElement(nextNode, el);
    }

    Node* findParentElement(Node* tree, T el)
    {
        if (tree == nullptr) {
            return tree;
        } else if (tree->left != nullptr && tree->left->val == el) {
            return tree;
        } else if (tree->right != nullptr && tree->right->val == el) {
            return tree;
        }

        Node* nextNode = el < tree->val ? tree->left : tree->right; 
        return findParentElement(nextNode, el);
    }

    // deletes smallest element, fixes parent and child pointers
    T pruneSmallestElement(Node* tree)
    {
        if(tree == nullptr || tree->left == nullptr) { // empty tree
            throw 1;
        } else if (tree->left->left == nullptr) { // successor is the smallest element
            Node* toPrune = tree->left;
            T toReturn = toPrune->val;
            
            if (toPrune->right != nullptr) {
                tree->left = toPrune->right;
            } else {
                tree->left = nullptr;
            }
            delete toPrune;
            std::cout << "pruned " << toReturn << std::endl;
            return toReturn;

        } else { // continue on searching
            return pruneSmallestElement(tree->left);
        }
    }

    void dfs(Node* tree)
    {
        if (tree != nullptr) {
            dfs(tree->left);
            std::cout << tree->val << " ";
            dfs(tree->right);
            
        }
    }

    void bfs(Node* tree)
    {
        std::vector<Node*>* queue = new std::vector<Node*>{tree, };
        int lvl = 0;
        while (!queue->empty()) {
            std::cout << "level " << lvl << ": ";
            for(Node* succ : *queue) {
                std::cout << succ->val << " ";
            }
            std::cout << std::endl;

            queue = successors(queue);
            ++lvl;
        }
        delete queue;
    }

   std::vector<Node*>* successors(std::vector<Node*>* parents)
    {
        std::vector<Node*>* newVector = new std::vector<Node*>();

        for(Node* node : *parents) {
            if(node != nullptr && node->left != nullptr) {
                newVector->push_back(node->left);
            }
            if(node != nullptr && node->right != nullptr) {
                newVector->push_back(node->right);
            }
        }

        delete parents;
        return newVector;
    }

private:
    Node* root;
};

int main()
{
    BSTree<int>* myTree = new BSTree<int>();

    myTree->addElement(2);
    myTree->addElement(3);
    myTree->addElement(1);

    assert(myTree->containsElement(1));
    assert(myTree->containsElement(2));
    assert(myTree->containsElement(3));
    assert(!myTree->containsElement(4));

    myTree->deleteElement(1);
    assert(!myTree->containsElement(1));

    myTree->addElement(1);
    myTree->addElement(4);
    myTree->addElement(5);

    myTree->print();

    myTree->deleteElement(5);

    myTree->print();

    return 0;
}
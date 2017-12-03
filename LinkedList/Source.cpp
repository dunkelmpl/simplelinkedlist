#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <stdexcept>

using namespace std;

struct Node {
    Node(int value) : value(value), next(nullptr) {}

    int value;
    Node* next;
};

class LinkedList {

public:
    LinkedList() : first(nullptr), last(nullptr) {}
    virtual ~LinkedList();

public:
    void insert(int value, int index = -1);
    int removeAt(int index);

public:
    inline bool isEmpty() { return !first; }

protected:
    Node* getAt(int index, Node** prev = nullptr);

public:
    void clear();

private:
    Node *first;
    Node *last;
};

LinkedList::~LinkedList()
{
    clear();
}

void LinkedList::clear()
{
    Node* current = first;

    while (current) {
        Node* next = current->next;

        delete current;
        current = next;
    }

    first = nullptr;
    last = nullptr;
}

void LinkedList::insert(int value, int index /* = -1 */)
{
    if (this->isEmpty()) {
        this->first = new Node(value);
        this->last = this->first;

        return;
    }

    Node* prev = nullptr;
    Node* node = nullptr;

    if (index >= 0) {
        node = this->getAt(index, &prev);
    }
    else {
        prev = last;
    }

    if (!node) {
        if (prev && (prev == last)) {
            prev->next = new Node(value);
            last = prev->next;
        }
        else {
            throw runtime_error("Invalid linked list structure");
        }
    }
    else {
        Node* newNode = new Node(value);
        newNode->next = node;

        if (prev) {
            prev->next = newNode;
        }
        else {
            first = newNode;
        }
    }
}

int LinkedList::removeAt(int index)
{
    if (!first) {
        return INT_MIN;
    }

    Node* prev = nullptr;
    Node* current = this->getAt(index, &prev);

    for (int pos = 0; (pos < index) && current; pos++) {
        prev = current;
        current = current->next;
    }

    int retVal = INT_MIN;

    if (current) {
        retVal = current->value;

        if (prev) {
            prev->next = current->next;
        }
        else {
            first = current->next;
        }

        if (!current->next) {
            last = prev;
        }

        delete current;
    }

    return retVal;
}

Node* LinkedList::getAt(int index, Node** prev /* = nullptr */)
{
    Node* current = first;
    Node* prevNode = nullptr;
    for (int pos = 0; (pos < index) && current; pos++) {
        prevNode = current;
        current = current->next;
    }

    if (prev) {
        *prev = prevNode;
    }

    return current;
}

int main()
{
    {
        LinkedList list;
        list.insert(12);
        list.insert(20);
        list.insert(24, 1);
        list.insert(55);

        list.removeAt(1);
    }

    _CrtDumpMemoryLeaks();
    return 0;
}
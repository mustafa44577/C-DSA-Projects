// ============================================================
//  FILE     : 02_practice_linked_list_basics.cpp
//  TOPIC    : Linked List — Fundamentals
//  TITLE    : Singly Linked List — Push Front / Push Back / Delete
//  TYPE     : Practice
//  CONCEPTS : Node creation, Head/Tail pointers, Push/Pop operations
// ============================================================

#include <iostream>
using namespace std;

// ----- Node Class -----
class Node {
public:
    int   data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// ----- Linked List Class -----
class LinkedList {
public:
    Node* head;
    Node* tail;

    LinkedList() {
        head = tail = NULL;
    }

    // Insert at front (head)
    void push_front(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head          = newNode;
    }

    // Insert at back (tail)
    void push_back(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail       = newNode;
    }

    // Delete from front
    void delete_front() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        head       = head->next;
        temp->next = NULL;
        delete temp;
    }

    // Delete from back
    void delete_back() {
        if (head == NULL) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp->next != tail)
            temp = temp->next;
        temp->next = NULL;
        delete tail;
        tail = temp;
    }

    // Print all elements
    void print() {
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ----- Main -----
int main() {
    LinkedList ll;

    ll.push_front(10);
    ll.push_front(100);
    ll.push_front(134);
    ll.push_back(20);

    cout << "List after inserts: ";
    ll.print();

    ll.delete_front();
    ll.delete_back();

    cout << "List after deletions: ";
    ll.print();

    return 0;
}

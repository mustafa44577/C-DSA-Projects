// ============================================================
//  FILE     : 04_practice_doubly_linked_list.cpp
//  TOPIC    : Doubly Linked List (DLL)
//  TITLE    : DLL — Push Front / Push Back / Delete Front / Delete Back
//  TYPE     : Practice
//  CONCEPTS : Doubly Linked List, prev/next pointers, head/tail tracking
// ============================================================

#include <iostream>
using namespace std;

// ----- Node Class -----
class Node {
public:
    int   data;
    Node* prev;
    Node* next;

    Node(int val) {
        data = val;
        prev = NULL;
        next = NULL;
    }
};

// ----- Doubly Linked List Class -----
class DLL {
public:
    Node* head;
    Node* tail;

    DLL() {
        head = tail = NULL;
    }

    // Insert at front
    void push_front(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev    = newNode;
        head          = newNode;
    }

    // Insert at back
    void push_back(int val) {
        Node* newNode = new Node(val);
        if (head == NULL) {
            head = tail = newNode;
            return;
        }
        tail->next    = newNode;
        newNode->prev = tail;
        tail          = newNode;
    }

    // Delete from front
    void delete_front() {
        if (head == NULL) { cout << "List is empty.\n"; return; }
        Node* temp = head;
        if (head == tail) {
            head = tail = NULL;
        } else {
            head       = head->next;
            head->prev = NULL;
        }
        delete temp;
    }

    // Delete from back
    void delete_back() {
        if (head == NULL) { cout << "List is empty.\n"; return; }
        Node* temp = tail;
        if (head == tail) {
            head = tail = NULL;
        } else {
            tail       = tail->prev;
            tail->next = NULL;
        }
        delete temp;
    }

    // Print forward
    void print_forward() {
        cout << "Forward: ";
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Print backward
    void print_backward() {
        cout << "Backward: ";
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout << endl;
    }
};

// ----- Main -----
int main() {
    DLL dll;

    dll.push_front(20);
    dll.push_front(10);
    dll.push_front(100);
    dll.push_back(30);
    dll.push_back(40);

    cout << "After inserts:\n";
    dll.print_forward();
    dll.print_backward();

    dll.delete_front();
    dll.delete_back();

    cout << "\nAfter deleting front and back:\n";
    dll.print_forward();
    dll.print_backward();

    return 0;
}

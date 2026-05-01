// ============================================================
//  FILE     : 05_practice_stack_linked_list.cpp
//  TOPIC    : Stack — Using Linked List
//  TITLE    : Stack — Push / Pop / Peek (Linked List Implementation)
//  TYPE     : Practice
//  CONCEPTS : Stack LIFO, push to front, pop from front, peek
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

// ----- Stack Class (using Linked List) -----
class Stack {
public:
    Node* head;  // top of stack

    Stack() {
        head = NULL;
    }

    bool is_empty() {
        return head == NULL;
    }

    // Push — insert at front (top of stack)
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head          = newNode;
        cout << val << " pushed.\n";
    }

    // Pop — remove from front (top of stack)
    void pop() {
        if (is_empty()) { cout << "Stack is empty.\n"; return; }
        cout << head->data << " popped.\n";
        Node* temp = head;
        head       = head->next;
        delete temp;
    }

    // Peek — view top element without removing
    void peek() {
        if (is_empty()) { cout << "Stack is empty.\n"; return; }
        cout << "Top element: " << head->data << endl;
    }

    // Print entire stack (top to bottom)
    void print() {
        if (is_empty()) { cout << "Stack is empty.\n"; return; }
        Node* temp = head;
        cout << "Stack (top -> bottom): ";
        while (temp != NULL) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

// ----- Main Menu -----
int main() {
    Stack s;
    int choice, val;

    while (true) {
        cout << "\n=== Stack Menu ===\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Print Stack\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Value: "; cin >> val; s.push(val); break;
            case 2: s.pop();                                     break;
            case 3: s.peek();                                    break;
            case 4: s.print();                                   break;
            case 0: cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}

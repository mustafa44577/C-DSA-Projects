// ============================================================
//  FILE     : 11_revision_linked_list_full.cpp
//  TOPIC    : Linked List — Revision
//  TITLE    : Singly Linked List — Full Revision with Menu
//  TYPE     : Revision / Practice
//  CONCEPTS : Insert front/back, Delete front/back, Search, Display
// ============================================================

#include <iostream>
using namespace std;

// ----- Node -----
class Node {
public:
    int   data;
    Node* next;

    Node(int val) {
        data = val;
        next = NULL;
    }
};

// ----- Global pointers -----
Node* head = NULL;
Node* tail = NULL;

// ----- Operations -----

void insertFront(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    newNode->next = head;
    head          = newNode;
}

void insertBack(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail       = newNode;
}

void deleteFront() {
    if (head == NULL) { cout << "List is empty.\n"; return; }
    Node* temp = head;
    head       = head->next;
    temp->next = NULL;
    delete temp;
    if (head == NULL) tail = NULL;
}

void deleteBack() {
    if (head == NULL) { cout << "List is empty.\n"; return; }
    if (head == tail) {
        delete head;
        head = tail = NULL;
        return;
    }
    Node* temp = head;
    while (temp->next != tail)
        temp = temp->next;
    delete tail;
    tail       = temp;
    tail->next = NULL;
}

bool searchList(int key) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key) return true;
        temp = temp->next;
    }
    return false;
}

void display() {
    if (head == NULL) { cout << "List is empty.\n"; return; }
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// ----- Main Menu -----
int main() {
    int choice, val;

    while (true) {
        cout << "\n=== Linked List Revision Menu ===\n";
        cout << "1. Insert at Front\n";
        cout << "2. Insert at Back\n";
        cout << "3. Delete at Front\n";
        cout << "4. Delete at Back\n";
        cout << "5. Search\n";
        cout << "6. Display List\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Value: "; cin >> val; insertFront(val); break;
            case 2: cout << "Value: "; cin >> val; insertBack(val);  break;
            case 3: deleteFront();                                    break;
            case 4: deleteBack();                                     break;
            case 5:
                cout << "Value to search: "; cin >> val;
                cout << (searchList(val) ? "Found.\n" : "Not found.\n");
                break;
            case 6: display();  break;
            case 0: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}

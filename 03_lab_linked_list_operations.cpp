// ============================================================
//  FILE     : 03_lab_linked_list_operations.cpp
//  TOPIC    : Linked List — Lab Tasks
//  TITLE    : Singly Linked List — Full Operations Menu
//  TYPE     : Lab Task
//  CONCEPTS : Insert (front/back/position/middle), Delete,
//             Search, Reverse, Remove by Value, Count, Middle
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

// ----- Global Head / Tail -----
Node* head = NULL;
Node* tail = NULL;

// ----- Insert Operations -----

void add_front(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    newNode->next = head;
    head          = newNode;
}

void add_back(int val) {
    Node* newNode = new Node(val);
    if (head == NULL) {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail       = newNode;
}

void insert_at_position(int val, int pos) {
    Node* newNode = new Node(val);
    if (pos == 1) {
        newNode->next = head;
        head          = newNode;
        if (tail == NULL) tail = newNode;
        return;
    }
    Node* temp  = head;
    int   count = 1;
    while (count < pos - 1 && temp != NULL) {
        temp = temp->next;
        count++;
    }
    if (temp == NULL) {
        cout << "Position out of range.\n";
        delete newNode;
        return;
    }
    newNode->next = temp->next;
    temp->next    = newNode;
    if (newNode->next == NULL) tail = newNode;
}

void insert_middle(int val) {
    if (head == NULL) {
        head = new Node(val);
        return;
    }
    int   count = 0;
    Node* temp  = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    insert_at_position(val, count / 2 + 1);
}

// ----- Delete Operations -----

void delete_front() {
    if (head == NULL) { cout << "List is empty.\n"; return; }
    Node* temp = head;
    head       = head->next;
    delete temp;
    if (head == NULL) tail = NULL;
}

void delete_back() {
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

void delete_by_value(int key) {
    Node* temp = head;
    Node* prev = NULL;
    while (temp != NULL) {
        if (temp->data == key) {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            if (temp == tail) tail = prev;
            delete temp;
            cout << key << " deleted.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << key << " not found.\n";
}

// Remove ALL occurrences of a value
void remove_all_occurrences(int val) {
    while (head != NULL && head->data == val) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
    Node* curr = head;
    while (curr != NULL && curr->next != NULL) {
        if (curr->next->data == val) {
            Node* temp  = curr->next;
            curr->next  = curr->next->next;
            delete temp;
        } else {
            curr = curr->next;
        }
    }
}

// ----- Search -----

void search(int key) {
    Node* temp  = head;
    int   count = 1;
    while (temp != NULL) {
        if (temp->data == key) {
            cout << key << " found at position " << count << ".\n";
            return;
        }
        temp = temp->next;
        count++;
    }
    cout << key << " not found.\n";
}

// ----- Reverse -----

void reverse() {
    Node* prev = NULL;
    Node* curr = head;
    tail       = head;
    while (curr != NULL) {
        Node* next = curr->next;
        curr->next = prev;
        prev       = curr;
        curr       = next;
    }
    head = prev;
    cout << "List reversed.\n";
}

// ----- Print -----

void print() {
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
    int choice, val, pos;

    while (true) {
        cout << "\n=== Linked List Menu ===\n";
        cout << "1. Add Front\n";
        cout << "2. Add Back\n";
        cout << "3. Delete Front\n";
        cout << "4. Delete Back\n";
        cout << "5. Insert at Position\n";
        cout << "6. Insert at Middle\n";
        cout << "7. Delete by Value\n";
        cout << "8. Search\n";
        cout << "9. Reverse\n";
        cout << "10. Print List\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: cout << "Value: "; cin >> val; add_front(val);              break;
            case 2: cout << "Value: "; cin >> val; add_back(val);               break;
            case 3: delete_front();                                              break;
            case 4: delete_back();                                               break;
            case 5:
                cout << "Value: "; cin >> val;
                cout << "Position: "; cin >> pos;
                insert_at_position(val, pos);
                break;
            case 6: cout << "Value: "; cin >> val; insert_middle(val);          break;
            case 7: cout << "Value: "; cin >> val; delete_by_value(val);        break;
            case 8: cout << "Value: "; cin >> val; search(val);                 break;
            case 9: reverse();                                                   break;
            case 10: print();                                                    break;
            case 0: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}

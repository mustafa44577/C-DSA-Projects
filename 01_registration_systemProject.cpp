// ============================================================
//  FILE     : 01_assignment_registration_system.cpp
//  TOPIC    : Linked List — Assignment 1
//  TITLE    : Talent Quest Fest 2.0 — Registration System
//  TYPE     : Assignment
//  CONCEPTS : Singly Linked List, Input Validation, Set Operations
//             (Union / Intersection / Difference)
// ============================================================

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ----- Node Structure -----
struct Node {
    string name;
    string cnic;
    string competition;
    string contact;
    Node* next;

    Node(string n, string c, string comp, string cont = "") {
        name        = n;
        cnic        = c;
        competition = comp;
        contact     = cont;
        next        = NULL;
    }
};

// ----- Input Validation Helpers -----

bool isNumeric(const string& s) {
    for (char ch : s)
        if (!isdigit(ch)) return false;
    return true;
}

string getValidCNIC() {
    string cnic;
    while (true) {
        cout << "Enter CNIC (13 digits numeric): ";
        getline(cin, cnic);
        if (cnic.size() == 13 && isNumeric(cnic)) return cnic;
        cout << "Invalid CNIC! Must be exactly 13 numeric digits.\n";
    }
}

string getValidContact() {
    string contact;
    while (true) {
        cout << "Enter Contact Number (11 digits numeric): ";
        getline(cin, contact);
        if (contact.size() == 11 && isNumeric(contact)) return contact;
        cout << "Invalid Contact! Must be exactly 11 numeric digits.\n";
    }
}

// ----- Linked List Operations -----

// Add node at end of list
void add(Node*& head, string name, string cnic, string comp, string contact = "") {
    Node* newNode = new Node(name, cnic, comp, contact);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

// Display all nodes in a list
void display(Node* head, string title) {
    cout << "\n--- " << title << " ---\n";
    if (head == NULL) {
        cout << "List is empty.\n";
        return;
    }
    Node* temp = head;
    while (temp != NULL) {
        cout << "Name: " << temp->name
             << " | CNIC: " << temp->cnic
             << " | Competition: " << temp->competition;
        if (!temp->contact.empty())
            cout << " | Contact: " << temp->contact;
        cout << endl;
        temp = temp->next;
    }
}

// Remove duplicate CNICs from a list
void removeDuplicates(Node* head) {
    for (Node* i = head; i != NULL; i = i->next) {
        Node* prev = i;
        for (Node* j = i->next; j != NULL;) {
            if (j->cnic == i->cnic) {
                prev->next = j->next;
                delete j;
                j = prev->next;
            } else {
                prev = j;
                j    = j->next;
            }
        }
    }
}

// Check if a CNIC exists in a list
bool exists(Node* head, string cnic) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->cnic == cnic) return true;
        temp = temp->next;
    }
    return false;
}

// Build Verified list — CNICs present in BOTH slip & online lists (Intersection)
Node* buildVerified(Node* slip, Node* online) {
    Node* verified = NULL;
    for (Node* i = slip; i != NULL; i = i->next)
        if (exists(online, i->cnic))
            add(verified, i->name, i->cnic, i->competition);
    return verified;
}

// Build Unpaid list — CNICs in slip but NOT in online list (Difference)
Node* buildUnpaid(Node* slip, Node* online) {
    Node* unpaid = NULL;
    for (Node* i = slip; i != NULL; i = i->next)
        if (!exists(online, i->cnic))
            add(unpaid, i->name, i->cnic, i->competition);
    return unpaid;
}

// Free all nodes in a list
void deleteList(Node* head) {
    while (head) {
        Node* temp = head;
        head       = head->next;
        delete temp;
    }
}

// ----- Main -----
int main() {
    Node* slip   = NULL;
    Node* online = NULL;

    cout << "\n=== Talent Quest Fest 2.0 — Registration System ===\n";
    cout << "Commands:\n";
    cout << "  S — Add to Slip list\n";
    cout << "  O — Add to Online list\n";
    cout << "  D — Remove duplicates from both lists\n";
    cout << "  V — Show Verified Participants (in both lists)\n";
    cout << "  P — Show Slip-only Participants (submitted slip but not online)\n";
    cout << "  L — Display all lists\n";
    cout << "  E — Exit\n";

    while (true) {
        cout << "\nEnter command: ";
        char ch;
        cin >> ch;
        ch = tolower(ch);
        cin.ignore();

        if (ch == 'e') {
            cout << "Exiting program...\n";
            break;
        }

        switch (ch) {
            case 's': {
                string name, cnic, comp;
                cout << "Enter Name: ";
                getline(cin, name);
                cnic = getValidCNIC();
                cout << "Enter Competition: ";
                getline(cin, comp);
                add(slip, name, cnic, comp);
                cout << "Added to Slip list.\n";
                break;
            }
            case 'o': {
                string name, cnic, comp, contact;
                cout << "Enter Name: ";
                getline(cin, name);
                cnic    = getValidCNIC();
                cout << "Enter Competition: ";
                getline(cin, comp);
                contact = getValidContact();
                add(online, name, cnic, comp, contact);
                cout << "Added to Online list.\n";
                break;
            }
            case 'd':
                removeDuplicates(slip);
                removeDuplicates(online);
                cout << "Duplicates removed from both lists.\n";
                break;
            case 'v': {
                removeDuplicates(slip);
                removeDuplicates(online);
                Node* verified = buildVerified(slip, online);
                display(verified, "Verified Participants (Slip + Online)");
                deleteList(verified);
                break;
            }
            case 'p': {
                removeDuplicates(slip);
                removeDuplicates(online);
                Node* unpaid = buildUnpaid(slip, online);
                display(unpaid, "Slip-Only Participants (Not Registered Online)");
                deleteList(unpaid);
                break;
            }
            case 'l':
                display(slip,   "Slip List");
                display(online, "Online List");
                break;
            default:
                cout << "Invalid command! Use S, O, D, V, P, L, or E.\n";
        }
    }

    deleteList(slip);
    deleteList(online);
    cout << "Program ended.\n";
    return 0;
}

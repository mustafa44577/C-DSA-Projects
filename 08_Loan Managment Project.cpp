// ============================================================
//  FILE     : 08_assignment_loan_management_bst.cpp
//  TOPIC    : Binary Search Tree (BST) — Real-Life Application
//  TITLE    : Friend Loan Management System
//  TYPE     : Assignment / Project
//  CONCEPTS : BST for user storage, Linked List for transactions,
//             Fine calculation, Inorder traversal for summary
// ============================================================

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ----- Transaction Node (Linked List) -----
struct TransactionNode {
    int   tid;
    int   borrowerId;
    int   lenderId;
    float amount;
    int   borrowedDays;
    int   allowedExtraDays;
    float finePercentage;
    bool  returned;
    TransactionNode* next;
};

// ----- User Node (BST Node) -----
struct UserNode {
    int              id;
    string           name;
    bool             active;
    TransactionNode* borrowList;   // loans this user has taken
    TransactionNode* paymentList;  // loans this user has given
    UserNode*        left;
    UserNode*        right;
};

// ============================================================
//  Helper Functions
// ============================================================

UserNode* createUser(int id, string name, bool active) {
    UserNode* node     = new UserNode();
    node->id           = id;
    node->name         = name;
    node->active       = active;
    node->borrowList   = NULL;
    node->paymentList  = NULL;
    node->left         = NULL;
    node->right        = NULL;
    return node;
}

UserNode* addUser(UserNode* root, int id, string name, bool active) {
    if (root == NULL)       return createUser(id, name, active);
    if (id < root->id)      root->left  = addUser(root->left,  id, name, active);
    else if (id > root->id) root->right = addUser(root->right, id, name, active);
    else                    cout << "Duplicate User ID! User not added.\n";
    return root;
}

UserNode* findUser(UserNode* root, int id) {
    if (root == NULL || root->id == id) return root;
    if (id < root->id) return findUser(root->left,  id);
    return              findUser(root->right, id);
}

// Check if a transaction ID is globally unique
bool isTidUnique(UserNode* root, int tid) {
    if (root == NULL) return true;
    TransactionNode* temp = root->borrowList;
    while (temp) {
        if (temp->tid == tid) return false;
        temp = temp->next;
    }
    return isTidUnique(root->left, tid) && isTidUnique(root->right, tid);
}

// Find which user owns a transaction ID
UserNode* findOwnerOfTid(UserNode* root, int tid) {
    if (root == NULL) return NULL;
    TransactionNode* temp = root->borrowList;
    while (temp) {
        if (temp->tid == tid) return root;
        temp = temp->next;
    }
    UserNode* leftResult = findOwnerOfTid(root->left, tid);
    if (leftResult) return leftResult;
    return findOwnerOfTid(root->right, tid);
}

// ============================================================
//  Core System Functions
// ============================================================

// Record a new loan between two users
void borrowLoan(UserNode* root) {
    int   tid, bid, lid, bdays, adays;
    float amt, fine;

    cout << "Transaction ID:         "; cin >> tid;
    if (!isTidUnique(root, tid)) {
        cout << "Error: Transaction ID already exists!\n";
        return;
    }

    cout << "Borrower ID:            "; cin >> bid;
    cout << "Lender ID:              "; cin >> lid;

    UserNode* bUser = findUser(root, bid);
    UserNode* lUser = findUser(root, lid);

    if (!bUser || !lUser) {
        cout << "Error: One or both users not found.\n";
        return;
    }
    if (!bUser->active || !lUser->active) {
        cout << "Error: One or both users are inactive.\n";
        return;
    }
    if (bid == lid) {
        cout << "Error: Self-borrowing not allowed.\n";
        return;
    }

    cout << "Amount:                 "; cin >> amt;
    cout << "Borrowed Days:          "; cin >> bdays;
    cout << "Allowed Extra Days:     "; cin >> adays;
    cout << "Fine % per late day:    "; cin >> fine;

    // Add to borrower's borrow list
    TransactionNode* bNode = new TransactionNode{tid, bid, lid, amt, bdays, adays, fine, false, bUser->borrowList};
    bUser->borrowList = bNode;

    // Add to lender's payment list
    TransactionNode* lNode = new TransactionNode{tid, bid, lid, amt, bdays, adays, fine, false, lUser->paymentList};
    lUser->paymentList = lNode;

    cout << "Transaction recorded successfully.\n";
}

// Return a loan and calculate fine if late
void returnLoan(UserNode* root, int tid, int actualDaysPassed) {
    UserNode* borrower = findOwnerOfTid(root, tid);
    if (!borrower) {
        cout << "Error: Transaction ID not found.\n";
        return;
    }

    TransactionNode* t = borrower->borrowList;
    while (t && t->tid != tid) t = t->next;

    if (!t) { cout << "Error: Transaction not found.\n"; return; }
    if (t->returned) { cout << "Error: Loan already returned.\n"; return; }

    int   deadline    = t->borrowedDays + t->allowedExtraDays;
    float finalAmount = t->amount;

    if (actualDaysPassed > deadline) {
        int   lateDays = actualDaysPassed - deadline;
        float fineAmt  = (t->amount * t->finePercentage / 100.0f) * lateDays;
        finalAmount   += fineAmt;
        cout << "LATE by " << lateDays << " days. Fine: " << fineAmt << endl;
    } else {
        cout << "Returned on time.\n";
    }

    t->returned = true;

    // Mark returned in lender's payment list
    UserNode* lender = findUser(root, t->lenderId);
    if (lender) {
        TransactionNode* lt = lender->paymentList;
        while (lt) {
            if (lt->tid == tid) { lt->returned = true; break; }
            lt = lt->next;
        }
    }
    cout << "Loan returned. Total paid: " << finalAmount << endl;
}

// Display a specific user's transactions
void displayUserTransactions(UserNode* root, int id) {
    UserNode* user = findUser(root, id);
    if (!user) { cout << "User not found.\n"; return; }

    cout << "\n--- Account of " << user->name << " ---\n";
    cout << "Loans Taken:\n";
    TransactionNode* t = user->borrowList;
    if (!t) cout << "  None\n";
    while (t) {
        cout << "  TID: " << t->tid << " | Amount: " << t->amount
             << " | Status: " << (t->returned ? "Returned" : "Pending") << endl;
        t = t->next;
    }
    cout << "Loans Given:\n";
    t = user->paymentList;
    if (!t) cout << "  None\n";
    while (t) {
        cout << "  TID: " << t->tid << " | Amount: " << t->amount
             << " | Status: " << (t->returned ? "Returned" : "Pending") << endl;
        t = t->next;
    }
}

// Inorder traversal for sorted user summary
void systemSummary(UserNode* root) {
    if (!root) return;
    systemSummary(root->left);
    cout << "ID: " << root->id << " | Name: " << root->name
         << " | Status: " << (root->active ? "Active" : "Inactive") << endl;
    systemSummary(root->right);
}

// ----- Main Menu -----
int main() {
    UserNode* root = NULL;
    int choice;

    while (true) {
        cout << "\n=== Friend Loan Management System ===\n";
        cout << "1. Add User\n";
        cout << "2. Record Loan\n";
        cout << "3. Return Loan\n";
        cout << "4. View User Account\n";
        cout << "5. System Summary\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id; string name;
                cout << "User ID: ";   cin >> id;
                cout << "User Name: "; cin >> name;
                root = addUser(root, id, name, true);
                cout << "User added.\n";
                break;
            }
            case 2: borrowLoan(root); break;
            case 3: {
                int tid, days;
                cout << "Transaction ID: ";              cin >> tid;
                cout << "Total days since loan taken: "; cin >> days;
                returnLoan(root, tid, days);
                break;
            }
            case 4: {
                int id;
                cout << "User ID: "; cin >> id;
                displayUserTransactions(root, id);
                break;
            }
            case 5:
                cout << "\n=== All Users (sorted by ID) ===\n";
                systemSummary(root);
                break;
            case 0:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}

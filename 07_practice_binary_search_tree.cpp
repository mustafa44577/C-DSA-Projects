// ============================================================
//  FILE     : 07_practice_binary_search_tree.cpp
//  TOPIC    : Binary Search Tree (BST)
//  TITLE    : BST — Full Implementation
//  TYPE     : Practice
//  CONCEPTS : Insert, Delete, Search, Traversals (Pre/In/Post),
//             Min/Max, 2nd Min/Max, Height, Node Counts
// ============================================================

#include <iostream>
using namespace std;

// ----- Node Structure -----
struct Node {
    int   data;
    Node* left;
    Node* right;
};

// ----- Node Creation -----
Node* create(int value) {
    Node* newNode  = new Node();
    newNode->data  = value;
    newNode->left  = NULL;
    newNode->right = NULL;
    return newNode;
}

// ----- Insert -----
Node* add(Node* root, int value) {
    if (root == NULL)       return create(value);
    if (value < root->data) root->left  = add(root->left,  value);
    else if (value > root->data) root->right = add(root->right, value);
    else                    cout << "Duplicate value: " << value << endl;
    return root;
}

// ----- Delete -----
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return NULL;

    if (key < root->data)
        root->left  = deleteNode(root->left,  key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Case 1: No left child
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        // Case 2: No right child
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Case 3: Two children — replace with in-order successor (smallest in right subtree)
        else {
            Node* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            root->data  = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }
    return root;
}

// ----- Search -----
bool search(Node* root, int key) {
    if (root == NULL)       return false;
    if (root->data == key)  return true;
    if (key < root->data)   return search(root->left,  key);
    else                    return search(root->right, key);
}

// ----- Min / Max -----
int findMin(Node* root) {
    if (root == NULL) { cout << "BST is empty.\n"; return -1; }
    while (root->left != NULL)
        root = root->left;
    return root->data;
}

int findMax(Node* root) {
    if (root == NULL) { cout << "BST is empty.\n"; return -1; }
    while (root->right != NULL)
        root = root->right;
    return root->data;
}

// ----- Second Minimum -----
int findSecondMin(Node* root) {
    if (root == NULL || root->left == NULL) return -1;

    Node* parent = NULL;
    Node* curr   = root;
    while (curr->left != NULL) {
        parent = curr;
        curr   = curr->left;
    }
    // If minimum node has right subtree, second min is leftmost of that subtree
    if (curr->right != NULL) {
        Node* temp = curr->right;
        while (temp->left != NULL)
            temp = temp->left;
        return temp->data;
    }
    return parent->data;
}

// ----- Second Maximum -----
int findSecondMax(Node* root) {
    if (root == NULL || root->right == NULL) return -1;

    Node* parent = NULL;
    Node* curr   = root;
    while (curr->right != NULL) {
        parent = curr;
        curr   = curr->right;
    }
    // If max node has left subtree, second max is rightmost of that subtree
    if (curr->left != NULL) {
        Node* temp = curr->left;
        while (temp->right != NULL)
            temp = temp->right;
        return temp->data;
    }
    return parent->data;
}

// ----- Traversals -----
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(Node* root) {           // gives sorted output
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// ----- Counting & Height -----
int countTotal(Node* root) {
    if (root == NULL) return 0;
    return 1 + countTotal(root->left) + countTotal(root->right);
}

int countLeafNodes(Node* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

int countInternalNodes(Node* root) {
    if (root == NULL) return 0;
    if (root->left != NULL || root->right != NULL)
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    return 0;
}

int height(Node* root) {
    if (root == NULL) return 0;
    int lh = height(root->left);
    int rh = height(root->right);
    return (lh > rh ? lh : rh) + 1;
}

// ----- Main -----
int main() {
    Node* root = NULL;
    int n, value;

    cout << "How many nodes to insert? ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Value: ";
        cin >> value;
        root = add(root, value);
    }

    cout << "\nPreorder:  "; preorder(root);  cout << endl;
    cout << "Inorder:   "; inorder(root);   cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;

    cout << "\nTotal nodes:    " << countTotal(root)         << endl;
    cout << "Leaf nodes:     " << countLeafNodes(root)      << endl;
    cout << "Internal nodes: " << countInternalNodes(root)  << endl;
    cout << "Height:         " << height(root)              << endl;
    cout << "Min value:      " << findMin(root)             << endl;
    cout << "Max value:      " << findMax(root)             << endl;

    int sMin = findSecondMin(root);
    cout << "2nd Min: " << (sMin != -1 ? to_string(sMin) : "Not found") << endl;

    int sMax = findSecondMax(root);
    cout << "2nd Max: " << (sMax != -1 ? to_string(sMax) : "Not found") << endl;

    // Delete
    int key;
    cout << "\nEnter value to delete: ";
    cin >> key;
    if (search(root, key)) {
        root = deleteNode(root, key);
        cout << key << " deleted.\n";
        cout << "Inorder after deletion: "; inorder(root); cout << endl;
    } else {
        cout << key << " not found in BST.\n";
    }

    // Search
    cout << "\nEnter value to search: ";
    cin >> key;
    cout << (search(root, key) ? "Found in BST.\n" : "Not found.\n");

    return 0;
}

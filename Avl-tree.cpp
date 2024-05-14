#include <iostream>
#include <algorithm>

// Node structure to store the data and 
// the pointers to the left and 
// right children 
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// Function to find max of two integers 
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Calculates the height of the node 
int height(Node* N) {
    if (N == nullptr) {
        return 0;
    }
    return N->height;
}

// Creates a new Node structure 
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// Performs a right rotation on the node 
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

// Performs a left rotation on the node 
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

// Calculates the balance factor 
// of the node 
int getBalanceFactor(Node* N) {
    if (N == nullptr) {
        return 0;
    }
    return height(N->left) - height(N->right);
}

// Inserts a new node into the 
// AVL Tree 
Node* insertNode(Node* node, int key) {
    if (node == nullptr) {
        return newNode(key);
    }
    if (key < node->key) {
        node->left = insertNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertNode(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balanceFactor = getBalanceFactor(node);

    if (balanceFactor > 1) {
        if (key < node->left->key) {
            return rightRotate(node);
        }
        else if (key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }

    if (balanceFactor < -1) {
        if (key > node->right->key) {
            return leftRotate(node);
        }
        else if (key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}

// Fetches the Node with minimum 
// value from the AVL tree 
Node* nodeWithMinimumValue(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Deletes a node from the AVL Tree 
Node* deleteNode(Node* root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            Node* temp = nodeWithMinimumValue(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balanceFactor = getBalanceFactor(root);

    if (balanceFactor > 1) {
        if (getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }

    if (balanceFactor < -1) {
        if (getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

// Prints the AVL tree 
void printTree(Node* root, std::string indent, bool last) {
    if (root != nullptr) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "   ";
        }
        else {
            std::cout << "L----";
            indent += "|  ";
        }
        std::cout << root->key << std::endl;
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

int main()
{
	Node* root = NULL;
	root = insertNode(root, 30);
	root = insertNode(root, 15);
	root = insertNode(root, 20);
	root = insertNode(root, 25);
	root = insertNode(root, 23);
	root = insertNode(root, 24);
	root = insertNode(root, 10);
	root = insertNode(root, 14);
	root = insertNode(root, 8);
	root = insertNode(root, 40);
	root = insertNode(root, 50);
	root = insertNode(root, 45);
	root = insertNode(root, 47);
	root = insertNode(root, 46);
	root = insertNode(root, 55);
	root = deleteNode(root, 40);
    printTree(root, "", true);
}


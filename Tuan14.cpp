#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int getHeight(Node* n) {
    if (n == nullptr) return 0;
    return n->height;
}

Node* insert(Node* node, int key) {
    if (node == nullptr) return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    return node;
}

void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int arr[] = {32, 51, 27, 83};
    for (int i = 0; i < 4; i++) {
        root = insert(root, arr[i]);
    }
    preOrder(root);
    return 0;
}
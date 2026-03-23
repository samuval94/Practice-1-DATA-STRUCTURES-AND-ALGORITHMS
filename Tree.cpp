#include "Tree.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Constructor del Nodo
Node::Node(const string& k) {
    key = k;
    left = nullptr;
    right = nullptr;
    height = 1;
}

// Altura y Balance
int AVLTree::height(const Node *n) {
    return n ? n->height : 0;
}

int AVLTree::getBalance(const Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}

// Rotación Simple a la Derecha (Izquierda-Izquierda)
Node* AVLTree::rotateRight(Node *y) {
    Node *x  = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left  = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Rotación Simple a la Izquierda (Derecha-Derecha)
Node* AVLTree::rotateLeft(Node *x) {
    Node *y  = x->right;
    Node *T2 = y->left;

    y->left  = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Insert con balanceo automático — O(log n)
Node* AVLTree::insert(Node* node, const string& key) {
    if (!node) return new Node(key);

    if (key < node->key)
        node->left  = insert(node->left,  key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // No se permiten duplicados

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)   // CASO 1: Izquierda-Izquierda
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)  // CASO 2: Derecha-Derecha
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {  // CASO 3: Izquierda-Derecha
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) { // CASO 4: Derecha-Izquierda
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Recorrido Inorder — imprime en pantalla O(n)
void AVLTree::inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << "[" << root->key << "] ";
        inorder(root->right);
    }
}

// Recorrido Inorder — guarda en vector O(n)
void AVLTree::inorderToVector(Node* root, vector<string>& result) {
    if (root) {
        inorderToVector(root->left,  result);
        result.push_back(root->key);
        inorderToVector(root->right, result);
    }
}

// Memoria estimada: cada nodo = string + 2 punteros + int
long long AVLTree::memoriaEstimada(int n) {
    long long tamNodo = sizeof(string) + sizeof(Node*) * 2 + sizeof(int);
    return tamNodo * n;
}
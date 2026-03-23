#ifndef C___ESTRUCTURAS_DE_DATOS_TREE_H
#define C___ESTRUCTURAS_DE_DATOS_TREE_H

#include <string>
#include <vector>
using namespace std;

// Representa cada palabra insertada en el árbol
class Node {
public:
    string key;     // la palabra
    Node *left;     // hijo izquierdo
    Node *right;    // hijo derecho
    int height;     // altura del nodo (necesaria para el balanceo)

    Node(const string& k);
};

// Árbol AVL — se balancea automáticamente en cada inserción
class AVLTree {
public:
    int height(const Node *n);
    int getBalance(const Node *n);
    Node* rotateRight(Node *y);
    Node* rotateLeft(Node *x);
    Node* insert(Node* node, const string& key);
    void inorder(Node* root);
    void inorderToVector(Node* root, vector<string>& result);
    long long memoriaEstimada(int n);
};


#endif //C___ESTRUCTURAS_DE_DATOS_TREE_H
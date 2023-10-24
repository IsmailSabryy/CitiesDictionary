#pragma once
#include <iostream>
#include"Queuet.h"
#include"Stackt.h"
using namespace std;


template <class KeyType, class DataType>
class BST {
private:
    struct Node {
        KeyType key;
        DataType data;
        Node* left;
        Node* right;
    };

    Node* root;

    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    bool insert2(Node*& aRoot, const KeyType& k, const DataType& d) {
        if (aRoot == nullptr) {
            aRoot = new Node;
            aRoot->left = nullptr;
            aRoot->right = nullptr;
            aRoot->key = k;
            aRoot->data = d;
            return true;
        }
        else if (k == aRoot->key) {
            return false;
        }
        else if (k < aRoot->key) {
            return insert2(aRoot->left, k, d);
        }
        else {
            return insert2(aRoot->right, k, d);
        }
    }

    bool search2(Node* aRoot, const KeyType& k) const {
        if (aRoot == nullptr) {
            return false;
        }
        else if (k == aRoot->key) {
            return true;
        }
        else if (k < aRoot->key) {
            return search2(aRoot->left, k);
        }
        else {
            return search2(aRoot->right, k);
        }
    }

    bool retrieve2(Node* aRoot, const KeyType& k, DataType& d) const {
        if (aRoot == nullptr) {
            return false;
        }
        else if (k == aRoot->key) {
            d = aRoot->data;
            return true;
        }
        else if (k < aRoot->key) {
            return 
                retrieve2(aRoot->left, k, d);
        }
        else {
            return retrieve2(aRoot->right, k, d);
        }
    }

    void deleteTree(Node* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    void traverse2(Node* aRoot) const {
        {
            if (aRoot != NULL)
            { 
                traverse2(aRoot->left);
                cout << aRoot->data << endl;
                traverse2(aRoot->right);
            }

        }
    }

    void parentSearch(const KeyType& k, bool& found, Node*& locptr, Node*& parent) const {
        locptr = root;
        parent = NULL;
        found = false;
        while (!found && locptr != NULL) {
            if (k < locptr->key) {
                parent = locptr;
                locptr = locptr->left;
            }
            else if (locptr->key < k) {
                parent = locptr;
                locptr = locptr->right;
            }
            else found = true;
        }
    }

public:
    BST() {
        root = nullptr;
    }  
    ~BST() {
        deleteTree(root);
    }

    bool empty() const {
        return (root == nullptr);
    }

    void traverse() const {
        
            traverse2(root);
        }

    void preorder() const {
        Stackt<Node*> s;
        Node* t = root;
        s.push(t);
        while (!s.stackIsEmpty()) {
            s.pop(t);
            std::cout << t->key << std::endl;
            if (t->right != nullptr) s.push(t->right);
            if (t->left != nullptr) s.push(t->left);
        }
    }

    void levelorder() const {
        Queuet<Node*> q;
        Node* t = root;
        q.enqueue(t);
        while (!q.queueIsEmpty()) {
            q.dequeue(t);
            std::cout << t->key << std::endl;
            if (t->left != nullptr) q.enqueue(t->left);
            if (t->right != nullptr) q.enqueue(t->right);
        }
    }

    bool insert(const KeyType& k, const DataType& d) {
        return insert2(root, k, d);
    }

    bool retrieve(const KeyType& k, DataType& d) const {
        return retrieve2(root, k, d);
    }

    bool search(const KeyType& k) const {
        return search2(root, k);
    }

    void remove(const KeyType& k) {
        bool found;
        Node* x, parent;

        parentSearch(k, found, x, parent);
        if (!found) {
            std::cout << "Item not in BST\n";
            return;
        }

        if ((x->left != nullptr) && (x->right != nullptr)) {

            Node* xSucc = x->right;
            parent = x;
            while (xSucc->left != nullptr) {
                parent = xSucc;
                xSucc = xSucc->left;
            }

            x->key = xSucc->key;
            x->data = xSucc->data;
            x = xSucc;
        }
        Node* subtree = x->left;
        if (subtree == nullptr) subtree = x->right;
        if (parent == nullptr) root = subtree;
        else if (parent->left == x) parent->left = subtree;
        else parent->right = subtree;
        delete x;
    }
};


 

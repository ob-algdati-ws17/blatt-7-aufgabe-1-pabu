//
// Created by Burger, Patrick on 09.01.18.
//

#ifndef BLATT_7_AUFGABE_1_PABU_AVLTREE_H
#define BLATT_7_AUFGABE_1_PABU_AVLTREE_H

#include <vector>

class AVLTree {
private:
    struct Node {
        const int key;
        int bal = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        Node(const int);
        Node(const int, Node *, Node *);

        /// Helper
        void setLeftChild(Node*);
        void setRightChild(Node*);

        bool search(const int value) const;

        std::vector<int> *preorder() const; // (Hauptreihenfolge)
        std::vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        std::vector<int> *postorder() const; // (Nebenreihenfolge)

        ~Node();
    };

    /// Private Modification Helpers
    void insert(Node*, const int);
    /// Balancing
    void upin(Node*);
    /// Rotations
    Node* rotateLeft(Node*, Node* &);
    Node* rotateRight(Node*, Node* &);

    Node *root = nullptr;
public:
    ~AVLTree();

    bool search(const int value) const;
    void insert(const int);

    std::vector<int> *preorder() const; // Hauptreihenfolge
    std::vector<int> *inorder() const; // Symmetrische Reihenfolge
    std::vector<int> *postorder() const; // Nebenreihenfolge
};


#endif //BLATT_7_AUFGABE_1_PABU_AVLTREE_H

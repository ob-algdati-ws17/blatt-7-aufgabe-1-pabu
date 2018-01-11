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
        int bal;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *prev = nullptr;

        Node(const int);
        Node(const int, Node *, Node *);

        void insert(const int);

        std::vector<int> *preorder() const; // (Hauptreihenfolge)
        std::vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        std::vector<int> *postorder() const; // (Nebenreihenfolge)

        ~Node();
    };

    Node *root = nullptr;
public:
    ~AVLTree();

    void insert(const int);

    std::vector<int> *preorder() const; // Hauptreihenfolge
    std::vector<int> *inorder() const; // Symmetrische Reihenfolge
    std::vector<int> *postorder() const; // Nebenreihenfolge
};


#endif //BLATT_7_AUFGABE_1_PABU_AVLTREE_H

//
// Created by Burger, Patrick on 09.01.18.
//

#ifndef BLATT_7_AUFGABE_1_PABU_AVLTREE_H
#define BLATT_7_AUFGABE_1_PABU_AVLTREE_H

#include <vector>

class AVLTree {
private:
    struct Node {
        int key;
        int bal = 0;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        Node(int);
        Node(int, Node *, Node *);

        bool isBalanced() const;
        /// Helper
        void setLeftChild(Node*);
        void setRightChild(Node*);
        bool hasOnlyOneChild();

        bool search(const int value) const;

        void removeMeFromMyParent();


        std::vector<int> *preorder() const; // (Hauptreihenfolge)
        std::vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        std::vector<int> *postorder() const; // (Nebenreihenfolge)

        ~Node();
    };

    /// Private Modification Helpers
    void insert(Node*, int);

    /// Balancing
    void upin(Node*);
    void upout(Node*);

    void removeNodeWithTwoLeaves(Node*);
    void removeNodeWithOneLeaf(Node*);
    void removeNodeWithNoLeaves(Node*);

    /// Rotations
    Node* rotateLeft(Node*, Node* &);
    Node* rotateRight(Node*, Node* &);

    //Node *root = nullptr;
public:
    Node *root = nullptr;
    ~AVLTree();

    bool search(int) const;
    void insert(int);
    void remove(int);

    std::vector<int> *preorder() const; // Hauptreihenfolge
    std::vector<int> *inorder() const; // Symmetrische Reihenfolge
    std::vector<int> *postorder() const; // Nebenreihenfolge
};


#endif //BLATT_7_AUFGABE_1_PABU_AVLTREE_H

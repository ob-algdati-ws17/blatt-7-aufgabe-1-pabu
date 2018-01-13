//
// Created by Burger, Patrick on 09.01.18.
//

#include <vector>
#include "AVLTree.h"

using namespace std;

/**
 * Constructors
 */

AVLTree::Node::Node(const int k) : key(k) {}

AVLTree::Node::Node(const int k, Node *left, Node *right) : key(k), left(left), right(right) {}

/**
 * Destructors
 */

AVLTree::~AVLTree() {
    delete root;
}

AVLTree::Node::~Node() {
    delete left;
    delete right;
}

/**
 * Insert
 */

void AVLTree::insert(const int value) {
    // check if AVLTree root already exists
    if (root == nullptr) {
        // new AVLTree, create Node with value
        root = new Node(value);
    } else {
        // try to insert as child of root Node
        insert(root, value);
    }
}

/// Tries to insert value as child of given Node
void AVLTree::insert(Node* node, const int value) {
    // check if node contains key already and early return when exists
    if (value == node->key) { return; }

    // LEFT SIDE: check if value belongs on the LEFT side
    if (value < node->key) {
        if (node->left != nullptr) {
            // side has already successor, pass value to following Node
            insert(node->left, value);
        } else {
            // replace leave by new Node with value
            auto newNode = new Node(value);
            node->setLeftChild(newNode);
            node->bal -= 1;

            upin(node);
        }
    }
    // RIGHT SIDE: value has to be bigger than key and belongs on right side
    else {
        if (node->right != nullptr) {
            // side has already successor, pass value to following Node
            insert(node->right, value);
        } else {
            // replace leave by new Node with value
            node->right = new Node(value);
            node->right->parent = node;
            node->bal += 1;

            upin(node);
        }
    }
}

/**
 * Upin & Balance
 */

void AVLTree::upin(Node* node) {
    // exclude case that node is balanced, so bal = {-1,1} or is root
    if (node->bal == 0 || node->parent == nullptr) { return; }

    // helper var for better readability
    Node* parent = node->parent;

    // left node grew by 1
    if (parent->left == node) {
        switch (parent->bal) {
            case -1:
                switch (node->bal) {
                    case 1:
                        // right branch of node has h+2 -> rotate left-right
                        break;

                    case -1:
                        Node* grandParent = node->parent->parent;
                        // left branch of node has h+2 -> rotate right
                        auto rotatedSubTree = rotateRight(parent);

                        if (grandParent != nullptr) {
                            grandParent->setLeftChild(rotatedSubTree);
                        } else {
                            root = rotatedSubTree;
                        }
                        break;
                }
                break;

            case 0:
                parent->bal -= 1;
                upin(parent);
                break;

            case 1:
                parent->bal -= 0;
                break;
        }
    }
}

/**
 * Rotation
 */

/// Rotate right (sub)tree where root is given node & return rotated (sub)tree with new root
AVLTree::Node *AVLTree::rotateRight(Node* node) {
    // temp save
    auto newRoot = node->left;
    auto movingNode = newRoot->right;

    // perform rotation
    newRoot->setRightChild(node);
    node->setLeftChild(movingNode);
    newRoot->parent = nullptr;

    // balance
    node->bal += 1;
    newRoot->bal += 1;

    return newRoot;
}

/// Rotate left (sub)tree where root is given node & return rotated (sub)tree with new root
AVLTree::Node *AVLTree::rotateLeft(Node* node) {
    // temp save
    auto newRoot = node->right;
    auto movingNode = newRoot->right;

    // perform rotation
    newRoot->setLeftChild(node);
    node->setRightChild(movingNode);
    newRoot->parent = nullptr;

    // balance
    node->bal -= 1;
    newRoot->bal -= 1;


    return newRoot;
}


/**
 * Helper
 */

void AVLTree::Node::setLeftChild(Node* child) {
    this->left = child;

    if (child != nullptr) {
        child->parent = this;
    }
}

void AVLTree::Node::setRightChild(Node* child) {
    this->right = child;

    if (child != nullptr) {
        child->parent = this;
    }
}


/**
 * Traversal
 * © Prof. Dr. Oliver Braun
 * Code is copied from proposed solution for Blatt 6
 */
vector<int> *AVLTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AVLTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel
    vec->push_back(key);
    // linker Teilbaum
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechter Teilbaum
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AVLTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AVLTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linker Teilbaum
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel
    vec->push_back(key);
    // rechter Teilbaum
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AVLTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AVLTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linker Teilbaum
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechter Teilbaum
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel
    vec->push_back(key);
    return vec;
}

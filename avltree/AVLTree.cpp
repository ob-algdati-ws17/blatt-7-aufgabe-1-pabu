//
// Created by Burger, Patrick on 09.01.18.
//

#include <vector>
#include "AVLTree.h"

using namespace std;

/*
 * Constructors
 */

AVLTree::Node::Node(const int k) : key(k) {}

AVLTree::Node::Node(const int k, Node *left, Node *right) : key(k), left(left), right(right) {}

/*
 * Destructors
 */

AVLTree::~AVLTree() {
    delete root;
}

AVLTree::Node::~Node() {
    delete left;
    delete right;
    delete prev;
}

/*
 * Insert
 */

void AVLTree::insert(const int value) {
    // check if AVLTree root already exists
    if (root == nullptr) {
        // new AVLTree, create Node with value
        root = new Node(value);
    } else {
        // call insert method on root Node
        root->insert(value);
    }
}

void AVLTree::Node::insert(const int value) {
    // check if self contains key already and early return when exists
    if (value == key) { return; }

    // LEFT SIDE: check if value belongs on the LEFT side
    if (value < key) {
        if (left != nullptr) {
            // side has already successor, pass value to following Node
            left->insert(value);
        } else {
            // replace leave by new Node with value
            left = new Node(value);

            // TODO: add balancing adjustment
        }
    }
    // RIGHT SIDE: value has to be bigger than key and belongs on right side
    else {
        if (right != nullptr) {
            // side has already successor, pass value to following Node
            right->insert(value);
        } else {
            // replace leave by new Node with value
            right = new Node(value);

            // TODO: add balancing adjustment
        }
    }
}

/*
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

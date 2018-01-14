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
 * Search
 */


bool AVLTree::search(const int value) const {
    if(root == nullptr)
        // key not found
        return false;

    return root->search(value);
}

bool AVLTree::Node::search(const int value) const {
    if (this->key == value)
        return true;

    Node* next = nullptr;
    if (value < this->key && this->left != nullptr) {
        next = this->left;
    } else if (this->right != nullptr) {
        next = this->right;
    }

    if (next == nullptr)
        return false;

    return next->search(value);
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
 * Remove
 */
void AVLTree::remove(const int value) {
    // check if AVLTree root exists
    if (root == nullptr)
        return;

    if(root->key == value && root->right == nullptr && root->left == nullptr) {
        root = nullptr;
        return;
    }

    Node* next = root;
    // search for relevant node
    while(next->key != value) {
        if (value < next->key && next->left != nullptr) {
            next = next->left;
        }
        else if (next->right != nullptr) {
            next = next->right;
        }
        else {
            return;
        }
    }

    // case 1 - node has no leaves
    if (next->left == nullptr && next->right == nullptr) {
        removeNodeWithTwoLeaves(next);
        return;
    }

    // case 2 - has only one leaf
    if (next->hasOnlyOneChild()) {
        removeNodeWithOneLeaf(next);
        return;
    }

    // case 3 - has two leaves
    if (next->left != nullptr && next->right != nullptr) {
        removeNodeWithNoLeaves(next);
        return;
    }
}

void AVLTree::removeNodeWithTwoLeaves(Node* node) {
    auto parent = node->parent;

    // remove node and adjust parents balance
    if (parent->left == node) {
        parent->bal += 1;

        switch (parent->bal) {
            case 0:
                // height changes
                node->removeMeFromMyParent();
                upout(parent);
                break;
            case 1:
                node->removeMeFromMyParent();
                break;
            case 2:
                upout(node);
                node->removeMeFromMyParent();
                break;
        }
    }
    else if (parent->right == node){
        parent->bal -= 1;

        switch (parent->bal) {
            case 0:
                // height changes causing parent is now balanced -> upout(parent)
                node->removeMeFromMyParent();
                upout(parent);
                break;
            case -1:
                // no height changes, parent has still a child
                node->removeMeFromMyParent();
                break;
            case -2:
                // need rotation cause balance is out of bounds
                Node* newRoot = nullptr;
                Node** anchor = nullptr;
                if (parent->parent == nullptr) {
                    anchor = &root;
                } else {
                    anchor = parent->parent->left == parent->parent ? &parent->left : &parent->right;
                }

                if (parent->left->right == nullptr) {
                    newRoot = rotateRight(parent, *anchor);
                } else {
                    rotateLeft(parent->left, parent->left);
                    newRoot = rotateRight(parent, *anchor);
                }
                upout(newRoot);
                node->removeMeFromMyParent();
                break;
        }
    }
}

void AVLTree::removeNodeWithOneLeaf(Node* node) {
    if (node->left != nullptr) {
        // TODO: not sure
        node->parent->bal += 1;

        // assign node's parent as parent of child
        node->left->parent = node->parent;

        // assign node's child as child of node's parent
        if (node->parent->left == node) {
            node->parent->left = node->left;
        } else {
            node->parent->right = node->left;
        }

        upout(node->left);
        node->removeMeFromMyParent();
    } else {
        // TODO: not sure
        node->parent->bal -= 1;

        // assign node's parent as parent of child
        node->right->parent = node->parent;

        // assign node's child as child of node's parent
        if (node->parent->left == node) {
            node->parent->left = node->right;
        } else {
            node->parent->right = node->right;
        }

        upout(node->right);
        node->removeMeFromMyParent();
    }
}

void AVLTree::removeNodeWithNoLeaves(Node* node) {
    // symmetric predecessor
    auto predecessor = node->left;
    // go along leftest branch and find smallest node with key > node.key
    while (predecessor->right != nullptr) {
        predecessor = predecessor->right;
    }

    // replace node key with symmetric predecessor key
    node->key = predecessor->key;

    if (predecessor->hasOnlyOneChild()) {
        removeNodeWithOneLeaf(predecessor);
    } else {
        removeNodeWithTwoLeaves(predecessor);
    }
}

void AVLTree::Node::removeMeFromMyParent() {
    if (this->parent->left == this) {
        this->parent->left = nullptr;
    } else {
        this->parent->right = nullptr;
    }
    this->parent = nullptr;
}


/**
 * Upin & Upout & Balance
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
                        // left branch of node has h+2 -> double rotate left-right
                        rotateLeft(node, parent->left);
                        rotateRight(parent, ((parent->parent != nullptr ? parent->parent->left : root)));

                        parent->parent->bal = 0;
                        parent->bal += 1;
                        break;

                    case -1:
                        // left branch of node has h+1 -> rotate right
                        rotateRight(parent, (parent->parent != nullptr ? parent->parent->left : root));
                        break;
                }
                break;

            case 0:
                parent->bal -= 1;
                upin(parent);
                break;

            case 1:
                parent->bal -= 1;
                break;
        }
    } else if (parent->right == node) {
        switch (parent->bal) {
            case -1:
                parent->bal += 1;
                break;
            case 0:
                parent->bal += 1;
                upin(parent);
                break;
            case 1:
                switch (node->bal) {
                    case -1:
                        // right branch of node has h+2 -> double rotate left-right
                        rotateRight(node, parent->right);
                        rotateLeft(parent, (parent->parent != nullptr ? parent->parent->right : root));

                        break;
                    case 1:
                        rotateLeft(parent, (parent->parent != nullptr ? parent->parent->right : root));

                        break;
                }
                break;
        }
    }
}

void AVLTree::upout(Node* node) {
    if ((node->bal != 0) || (node == root)) { return; }

    // node is left son
    if (node->parent->left == node) {
        switch (node->parent->bal) {
            case -1: {
                node->parent->bal = 0;
                upout(node->parent);
                break;
            }
            case 0: {
                node->parent->bal = 1;
                break;
            }
            case 1: {
                switch (node->parent->right->bal) {
                    case -1: {
                        rotateRight(node->parent->right, node->parent->right);
                        auto newRootDouble = rotateLeft(node->parent, (node->parent->parent->left == node->parent
                                                                       ? node->parent->parent->left
                                                                       : node->parent->parent->right));
                        upout(newRootDouble);
                        break;
                    }
                    case 0: {
                        rotateLeft(node->parent,
                                   (node->parent->parent->left == node->parent ? node->parent->parent->left
                                                                               : node->parent->parent->right));
                        node->parent->bal = 1;
                        node->parent->parent->bal = -1;
                        break;
                    }
                    case 1: {
                        auto newRoot = rotateLeft(node->parent, (node->parent->parent->left == node->parent
                                                                 ? node->parent->parent->left
                                                                 : node->parent->parent->right));
                        upout(newRoot);
                        break;
                    }
                }
            }
        }
    } else if (node->parent->right == node) {
        switch (node->parent->bal) {
            case -1: {
                switch (node->parent->right->bal) {
                    case -1: {
                        auto newRoot = rotateRight(node->parent, (node->parent->parent->left == node->parent ? node->parent->parent->left : node->parent->parent->right));
                        upout(newRoot);
                        break;
                    }

                    case 0: {
                        rotateRight(node->parent, (node->parent->parent->left == node->parent ? node->parent->parent->left : node->parent->parent->right));
                        node->parent->bal = -1;
                        node->parent->parent->bal = 1;
                        break;
                    }

                    case 1: {
                        rotateLeft(node->parent->left, node->parent->left);
                        auto newRootDouble = rotateRight(node->parent, (node->parent->parent->left == node->parent ? node->parent->parent->left : node->parent->parent->right));
                        upout(newRootDouble);
                        break;
                    }
                }
                break;
            }
            case 0: {
                node->parent->bal = -1;
                break;
            }
            case 1: {
                node->parent->bal = 0;
                upout(node->parent);
                break;
            }
        }
    }
}

/**
 * Rotation
 */

/// Rotate right (sub)tree where root is given node & return rotated (sub)tree with new root
AVLTree::Node *AVLTree::rotateRight(Node* node, Node* &anchor) {
    // temp save
    auto newRoot = node->left;
    auto movingNode = newRoot->right;
    newRoot->parent = anchor->parent;

    // perform rotation
    newRoot->setRightChild(node);
    node->setLeftChild(movingNode);

    // balance
    node->bal +=1;
    newRoot->bal += 1;

    // reattach newRoot at anchor
    anchor = newRoot;

    return newRoot;
}

/// Rotate left (sub)tree where root is given node & return rotated (sub)tree with new root
AVLTree::Node *AVLTree::rotateLeft(Node* node, Node* &anchor) {
    // temp save
    auto newRoot = node->right;
    auto movingNode = newRoot->left;
    newRoot->parent = anchor->parent;

    // perform rotation
    newRoot->setLeftChild(node);
    node->setRightChild(movingNode);
    newRoot->parent = nullptr;

    // balance
    node->bal -= 1;
    newRoot->bal -= 1;


    // reattach newRoot at anchor
    anchor = newRoot;

    return newRoot;
}


/**
 * Helper
 */

bool AVLTree::Node::hasOnlyOneChild() {
    if ((this->right != nullptr && this->left == nullptr) || (this->right == nullptr && this->left != nullptr))
        return true;

    return false;
}

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

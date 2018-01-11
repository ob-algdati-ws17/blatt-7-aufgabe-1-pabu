#include "testAVLTree.h"
#include <memory>

using namespace std;

// empty tree

TEST(AVLTreeTest, Empty_Tree) {
    AVLTree tree;
    EXPECT_EQ(tree.inorder(), nullptr);
}

// insert in tree

TEST(AVLTreeTest, Insert_In_Empty_Tree) {
    AVLTree tree;
    tree.insert(5);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5));
}

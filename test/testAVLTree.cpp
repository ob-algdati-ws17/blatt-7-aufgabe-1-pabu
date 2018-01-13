#include "testAVLTree.h"
#include <memory>

using namespace std;

/********************************************************************
 * EMPTY TREE
 *******************************************************************/

TEST(AVLTreeTest, Empty_Tree) {
    AVLTree tree;
    EXPECT_EQ(tree.inorder(), nullptr);
}

/********************************************************************
 * INSERT
 *******************************************************************/

/*
 * Insert in tree
 */
TEST(AVLTreeTest, Insert_In_Empty_Tree) {
    AVLTree tree;
    tree.insert(5);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(5));
}

TEST(AVLTreeTest, Insert_In_SingleNode_Tree) {
    AVLTree treeLeftHeavy;
    treeLeftHeavy.insert(5);
    treeLeftHeavy.insert(3);
    EXPECT_THAT(*treeLeftHeavy.inorder(), testing::ElementsAre(3, 5));
    EXPECT_THAT(*treeLeftHeavy.preorder(), testing::ElementsAre(5, 3));

    AVLTree treeRightHeavy;
    treeRightHeavy.insert(5);
    treeRightHeavy.insert(7);
    EXPECT_THAT(*treeRightHeavy.inorder(), testing::ElementsAre(5, 7));
    EXPECT_THAT(*treeRightHeavy.postorder(), testing::ElementsAre(7, 5));

    AVLTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(3, 5, 7));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(3, 7, 5));
}

/*
 * Insert in tree & rotate right
 */

TEST(AVLTreeTest, Insert_And_Rotate_On_Root) {
    AVLTree tree;
    tree.insert(100);
    tree.insert(50);

    // now right rotation at root level is needed
    tree.insert(30);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(50, 30, 100));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 50, 100));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 100, 50));
}

TEST(AVLTreeTest, Insert_And_Rotate_Right) {
    AVLTree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(30);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 50, 30, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 50, 100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 50, 150, 100));

    // now right rotation at root level is needed
    tree.insert(20);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 30, 20, 50, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(20, 30, 50, 100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(20, 50, 30, 150, 100));
}

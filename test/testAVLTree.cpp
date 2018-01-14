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
    AVLTree treeLeft;
    treeLeft.insert(100);
    treeLeft.insert(50);

    // now right rotation at root level is needed
    treeLeft.insert(30);

    EXPECT_THAT(*treeLeft.preorder(), testing::ElementsAre(50, 30, 100));
    EXPECT_THAT(*treeLeft.inorder(), testing::ElementsAre(30, 50, 100));
    EXPECT_THAT(*treeLeft.postorder(), testing::ElementsAre(30, 100, 50));

    AVLTree treeRight;
    treeRight.insert(100);
    treeRight.insert(150);

    // now right rotation at root level is needed
    treeRight.insert(200);

    EXPECT_THAT(*treeRight.preorder(), testing::ElementsAre(150, 100, 200));
    EXPECT_THAT(*treeRight.inorder(), testing::ElementsAre(100, 150, 200));
    EXPECT_THAT(*treeRight.postorder(), testing::ElementsAre(100, 200, 150));
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

TEST(AVLTreeTest, Insert_And_Rotate_Left) {
    AVLTree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(200);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 50, 150, 200));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(50, 100, 150, 200));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(50, 200, 150, 100));

    // now right rotation at root level is needed
    tree.insert(300);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 50, 200, 150, 300));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(50, 100, 150, 200, 300));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(50, 150, 300, 200, 100));
}

TEST(AVLTreeTest, Insert_And_Rotate_Left_Right) {
    AVLTree tree;
    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(30);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 50, 30, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 50, 100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 50, 150, 100));

    // now right rotation at root level is needed
    tree.insert(70);
    tree.insert(60);

    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(70, 50, 30, 60, 100, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 50, 60, 70, 100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 60, 50, 150, 100, 70));
}

/********************************************************************
 * SEARCH
 *******************************************************************/

TEST(AVLTreeTest, Search_In_Tree) {
    AVLTree tree;
    EXPECT_FALSE(tree.search(50));

    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(30);
    tree.insert(70);
    tree.insert(60);

    EXPECT_FALSE(tree.search(200));
    EXPECT_TRUE(tree.search(150));
}

/********************************************************************
 * REMOVE
 *******************************************************************/

TEST(AVLTreeTest, Delete_Single_Root_Node) {
    AVLTree tree;

    tree.insert(100);

    tree.remove(100);
    EXPECT_EQ(tree.inorder(), nullptr);
}

TEST(AVLTreeTest, Delete_Node_With_Leaves) {
    AVLTree tree;

    tree.insert(100);
    tree.insert(50);
    tree.insert(150);

    tree.remove(50);
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(150, 100));

    tree.remove(150);
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(100));
}

TEST(AVLTreeTest, Delete_Node_With_No_Leaves) {
    AVLTree tree;

    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(30);
    tree.insert(70);
    tree.insert(60);

    tree.remove(50);
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(70, 30, 60, 100, 150));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 60, 70, 100, 150));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(60, 30, 150, 100, 70));
}

TEST(AVLTreeTest, Delete_Node_With_Left_Leave) {
    AVLTree tree;

    tree.insert(100);
    tree.insert(50);
    tree.insert(150);
    tree.insert(30);
    tree.insert(70);
    tree.insert(60);

    tree.remove(150);
    tree.remove(100);
    EXPECT_THAT(*tree.preorder(), testing::ElementsAre(60, 50, 30, 70));
    EXPECT_THAT(*tree.inorder(), testing::ElementsAre(30, 50, 60, 70));
    EXPECT_THAT(*tree.postorder(), testing::ElementsAre(30, 50, 70, 60));
}
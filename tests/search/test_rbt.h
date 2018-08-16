#ifndef ALGS4_TEST_RBT_H
#define ALGS4_TEST_RBT_H

#include <gtest/gtest.h>

#include "search/rbt.h"
#include "common/word_reader.h"

using namespace std;

TEST(RBT_TEST, TEST_CREATE_TREE) {
    RBT<int, int> rbt;
    RBT<int, int>::Node root = rbt.root;
    EXPECT_EQ(root, nullptr);
    EXPECT_EQ(rbt.GetSize(), 0);
    EXPECT_THROW(rbt.Get(1), runtime_error);
}

TEST(RBT_TEST, TEST_PUT_GET_SIZE) {
    RBT<int, int> rbt;
    rbt.Put(1, 2);
    EXPECT_EQ(rbt.GetSize(), 1);
    EXPECT_EQ(rbt.Get(1), 2);

    rbt.Put(1, 3);
    EXPECT_EQ(rbt.GetSize(), 1);
    EXPECT_EQ(rbt.Get(1), 3);

    rbt.Put(2, 4);
    EXPECT_EQ(rbt.GetSize(), 2);
    EXPECT_EQ(rbt.Get(2), 4);

    rbt.Put(4, 11);
    EXPECT_EQ(rbt.GetSize(), 3);
    EXPECT_EQ(rbt.Get(4), 11);

    rbt.Put(-4, -11);
    EXPECT_EQ(rbt.GetSize(), 4);
    EXPECT_EQ(rbt.Get(-4), -11);
}

TEST(RBT_TEST, TEST_PUT_SINGLE_2_NODE_LEFT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-1, -1);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(0)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-1)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_SINGLE_2_NODE_RIGHT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(1, 1);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_TRUE(rbt.GetNode(0)->IsRed());
    EXPECT_FALSE(rbt.GetNode(1)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_LEFT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);

    rbt.Put(-20, -20);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(0)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-20)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_MID) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);

    rbt.Put(-5, -5);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(0)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-5)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_RIGHT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);

    rbt.Put(10, 10);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(0)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_BOTTOM_2_NODE_LEFT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);

    rbt.Put(-20, -20);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-20)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_BOTTOM_2_NODE_RIGHT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);

    rbt.Put(-5, -5);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-5)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-10)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_LEFT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-20)->IsRed());

    rbt.Put(-30, -30);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-30)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-20)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_MID) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-20)->IsRed());

    rbt.Put(-15, -15);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-20)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-15)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
}

TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_RIGHT) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-20)->IsRed());

    rbt.Put(-5, -5);
    EXPECT_FALSE(rbt.GetRoot()->IsRed());
    EXPECT_FALSE(rbt.GetNode(-20)->IsRed());
    EXPECT_FALSE(rbt.GetNode(-5)->IsRed());
    EXPECT_TRUE(rbt.GetNode(-10)->IsRed());
    EXPECT_FALSE(rbt.GetNode(10)->IsRed());
}

TEST(RBT_TEST, TEST_TREE_IS_BALANCED) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    rbt.Put(-5, -5);
    EXPECT_TRUE(rbt.CheckTree());
}

TEST(RBT_TEST, TEST_DELETE) {
    RBT<int, int> rbt;
    rbt.Put(0, 0);
    rbt.Put(-10, -10);
    rbt.Put(10, 10);
    rbt.Put(-20, -20);
    rbt.Put(-5, -5);
    EXPECT_TRUE(rbt.CheckTree());

    rbt.Delete(0);
    EXPECT_EQ(rbt.GetSize(), 4);
    EXPECT_TRUE(rbt.CheckTree());

    rbt.Delete(-10);
    EXPECT_EQ(rbt.GetSize(), 3);
    EXPECT_TRUE(rbt.CheckTree());

    rbt.Delete(-20);
    EXPECT_EQ(rbt.GetSize(), 2);
    EXPECT_TRUE(rbt.CheckTree());

    rbt.Delete(-5);
    EXPECT_EQ(rbt.GetSize(), 1);
    EXPECT_TRUE(rbt.CheckTree());

    rbt.Delete(10);
    EXPECT_EQ(rbt.GetSize(), 0);
    EXPECT_TRUE(rbt.CheckTree());

    EXPECT_THROW(rbt.Delete(1), runtime_error);
}

TEST(RBT_TEST, CASE_TEST) {
    vector<string> words = ReadWords("data/tale.txt");
    RBT<string, int> rbt;
    for (auto &word:words) {
        if (rbt.Contains(word)) {
            rbt.Put(word, rbt.Get(word) + 1);
        } else {
            rbt.Put(word, 1);
        }
    }

    EXPECT_NE(rbt.GetSize(), 0);
    EXPECT_TRUE(rbt.CheckTree());

    vector<string> counter;
    rbt.Keys(counter);
    string maxCounter = " ";
    rbt.Put(maxCounter, 0);
    for (auto &word:counter) {
        if (rbt.Get(word) > rbt.Get(maxCounter)) {
            maxCounter = word;
        }
    }
    while (rbt.GetSize()) {
        string minKey = rbt.Min();
        rbt.Delete(minKey);
    }
    EXPECT_EQ(rbt.GetSize(), 0);
    EXPECT_TRUE(rbt.CheckTree());
}

#endif //ALGS4_TEST_RBT_H

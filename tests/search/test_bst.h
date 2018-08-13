#ifndef ALGS4_TEST_BST_H
#define ALGS4_TEST_BST_H

#include <gtest/gtest.h>

#include "search/bst.h"
#include "common/file_word_reader.h"

using namespace std;

TEST(BST_TEST, FULL_TEST) {
    vector<string> words = ReadWords("data/tale.txt");
    BST<string, int> bst;
    for (auto &word:words) {
        if (bst.Contains(word)) {
            bst.Put(word, bst.Get(word) + 1);
        } else {
            bst.Put(word, 1);
        }
    }

    EXPECT_NE(bst.Size(), 0);

    vector<string> counter;
    bst.Keys(counter);
    string maxCounter = " ";
    bst.Put(maxCounter, 0);
    for (auto &word:counter) {
        if (bst.Get(word) > bst.Get(maxCounter)) {
            maxCounter = word;
        }
    }
    while (bst.Size()) {
        string minKey = bst.Min()->key;
        bst.Delete(minKey);
    }
    EXPECT_EQ(bst.Size(), 0);
}

#endif //ALGS4_TEST_BST_H

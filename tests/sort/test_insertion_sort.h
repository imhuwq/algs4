#ifndef ALGS4_TEST_INSERTION_SORT_H
#define ALGS4_TEST_INSERTION_SORT_H

#include <gtest/gtest.h>

#include "sort/insertion_sort.h"
#include "common/number_reader.h"

TEST(INSERTION_SORT_TEST, CASE_TEST) {
    string filePath = "data/32Kints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    InsertionSort<int> sort;
    sort.Sort(nums);
    EXPECT_TRUE(sort.IsSorted(nums));
}
#endif //ALGS4_TEST_INSERTION_SORT_H

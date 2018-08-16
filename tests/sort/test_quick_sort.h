#ifndef ALGS4_TEST_QUICK_SORT_H
#define ALGS4_TEST_QUICK_SORT_H

#include <gtest/gtest.h>

#include "sort/quick_sort.h"
#include "common/number_reader.h"

TEST(QUICK_SORT_TEST, CASE_TEST) {
    string filePath = "data/32Kints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    QuickSort<int> sort;
    sort.Sort(nums);
    EXPECT_TRUE(sort.IsSorted(nums));
}

#endif //ALGS4_TEST_QUICK_SORT_H

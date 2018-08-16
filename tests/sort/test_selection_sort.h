#ifndef ALGS4_TEST_SELECTION_SORT_H
#define ALGS4_TEST_SELECTION_SORT_H

#include <gtest/gtest.h>

#include "sort/selection_sort.h"
#include "common/number_reader.h"

TEST(SELECTION_SORT_TEST, CASE_TEST) {
    string filePath = "data/32Kints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    SelectionSort<int> sort;
    sort.Sort(nums);
    EXPECT_TRUE(sort.IsSorted(nums));
}

#endif //ALGS4_TEST_SELECTION_SORT_H

#ifndef ALGS4_TEST_HEAP_SORT_H
#define ALGS4_TEST_HEAP_SORT_H

#include <gtest/gtest.h>

#include "sort/heap_sort.h"
#include "common/number_reader.h"

TEST(HEAP_SORT_TEST, CASE_TEST) {
    string filePath = "data/32Kints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    HeapSort<int> sort;
    sort.Sort(nums);
}

#endif //ALGS4_TEST_HEAP_SORT_H

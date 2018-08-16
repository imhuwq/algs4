#ifndef ALGS4_TEST_SHELL_SORT_H
#define ALGS4_TEST_SHELL_SORT_H

#include <gtest/gtest.h>

#include "sort/shell_sort.h"
#include "common/number_reader.h"

TEST(SHELL_SORT_TEST, CASE_TEST) {
    string filePath = "data/32Kints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    ShellSort<int> sort;
    sort.Sort(nums);
}

#endif //ALGS4_TEST_SHELL_SORT_H

#include <iostream>
#include "search/rbt.h"
#include "sort/merge_sort.h"
#include "common/word_reader.h"
#include "common/number_reader.h"

int main() {
    string filePath = "data/1Mints.txt";
    vector<int> nums = ReadNumbers<int>(filePath);
    MergeSort<int> sort;
    sort.Sort(nums);
    DEBUG(sort.IsSorted(nums));
}
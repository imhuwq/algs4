#include <vector>
#include <iostream>
#include "heap_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 9, 7, 8, 6, 3, 1, 7, 2};
    HeapSort<int> sort;
    sort.Show(nums);
    sort.Sort(nums);
    cout << (sort.IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    sort.Show(nums);
}
#include <vector>
#include <iostream>
#include "quick_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 2, 3, 4, 5, 7, 3, 6, 8};
    QuickSort<int> sort;
    sort.Show(nums);
    sort.Sort(nums);
    cout << (sort.IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    sort.Show(nums);
}
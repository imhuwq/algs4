#include <vector>
#include "selection_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 3, 7, 8};
    SelectionSort<int>::Show(nums);
    SelectionSort<int>::Sort(nums);
    cout << (SelectionSort<int>::IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    SelectionSort<int>::Show(nums);
}
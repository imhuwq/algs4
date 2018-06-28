#include <vector>
#include "insertion_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 3, 7, 8, 6};
    InsertionSort<int>::Show(nums);
    InsertionSort<int>::Sort(nums);
    cout << (InsertionSort<int>::IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    InsertionSort<int>::Show(nums);
}
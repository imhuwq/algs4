#include <vector>
#include "merge_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 3, 7, 8, 6, 1, 543, 123, 768, 123, 657, 234, 234, 213, 657, 768, 879, 213, 234};
    MergeSort<int> sort;
    sort.Show(nums);
    sort.SortBU(nums);
    cout << (sort.IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    sort.Show(nums);
}
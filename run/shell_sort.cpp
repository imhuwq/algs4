#include <vector>
#include "shell_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 3, 7, 8, 6};
    ShellSort<int> sort;
    sort.Show(nums);
    sort.Sort(nums);
    cout << (sort.IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    sort.Show(nums);
}
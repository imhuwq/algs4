#include <vector>
#include "shell_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    vector<int> nums = {5, 1, 3, 7, 8, 6};
    ShellSort<int>::Show(nums);
    ShellSort<int>::Sort(nums);
    cout << (ShellSort<int>::IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    ShellSort<int>::Show(nums);
}
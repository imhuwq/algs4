#include <vector>
#include <iostream>

#include "number_reader.h"
#include "selection_sort.h"

using namespace std;

int main(const int argc, const char **argv) {
    string filePath;
    cout << "请输入数据文件路径: ";
    cin >> filePath;
    cout << endl;

    vector<int> nums = ReadNumbers<int>(filePath);
    SelectionSort<int> sort;
    sort.Show(nums);
    sort.Sort(nums);
    cout << (sort.IsSorted(nums) ? "Sorted" : "Unsorted") << endl;
    sort.Show(nums);
}
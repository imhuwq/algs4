#ifndef ALGS4_SORT_INSERTION_SORT_H
#define ALGS4_SORT_INSERTION_SORT_H

#include "sort_base.h"

// 插入排序也是一个 O(N^2) 时间的排序算法，它的效率和输入元素的排序状态有关。
// 插入排序平均 (N^2) / 4 次比较和交换，最差 (N^2) / 2 次比较和交换，最好 (N-1) 次比较和 0 次交换
// 可以通过把较大元素往右移动而不总是交换元素来大幅提高效率。
template<typename T>
class InsertionSort : public SortBase<T> {
public:
    static void Sort(vector<T> &elements) {
        unsigned int size = elements.size();
        unsigned exchanges = 0;
        // 首先进行一个粗略的排序，确保最小的元素在最左
        for (unsigned int i = size - 1; i > 0; i--) {
            if (SortBase<T>::Less(elements[i], elements[i - 1])) {
                SortBase<T>::Exch(elements, i, i - 1);
                exchanges++;
            }
        }
        if (exchanges == 0) return;

        // 最小的在最左，前两个一定是有序的，所以直接从第三个开始
        for (unsigned int i = 2; i < size; i++) {
            // 选定当前进行插入的元素
            T element = elements[i];

            // j 是打算插入的位置
            unsigned int j = i;

            // 只要选定的元素比 j 左边的元素小...
            while (SortBase<T>::Less(element, elements[j - 1])) {  // 最小的已经在最左，所以 while 循环一定会在 j = 1 时跳出
                // 就把小的元素右移一位...
                elements[j] = elements[j - 1];
                // 再把 j 往左移动一位;
                j--;
            }
            // 否则把选定的元素插入到 j 的位置
            elements[j] = element;
        }
    }
};

#endif //ALGS4_SORT_INSERTION_SORT_H

#ifndef ALGS4_SORT_SELECTIONSORT_H
#define ALGS4_SORT_SELECTIONSORT_H

#include "sort_base.h"

// 选择排序是最简单的排序算法之一，需要使用 O(N) 次交换和 O(N^2) 次比较。
// 优点是交换次数是最少的，缺点是运行时间和输入的状态无关，即即使输入的元素已经是排好序的，也需要那么多的时间。
// 思路是遍历元素 N 次，第 i 次遍历从 i-1...N-1 里面选出一个最小的放到 i-1 位置上。
template<typename T>
class SelectionSort : public SortBase<T> {
public:
    static void Sort(vector<T> &elements) {
        unsigned int min;
        unsigned int size = elements.size();
        for (unsigned int i = 0; i < size; i++) {
            min = i;
            for (unsigned int j = i + 1; j < size; j++) {
                if (Less(elements[j], elements[min])) min = j;
            }
            Exch(elements, i, min);
        }
    }
};

#endif //ALGS4_SORT_SELECTIONSORT_H

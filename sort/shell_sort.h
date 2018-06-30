#ifndef ALGS4_SORT_SHELL_SORT_H
#define ALGS4_SORT_SHELL_SORT_H

#include "sort_base.h"

// 希尔排序是插入排序的一个变种，它利用了插入排序对输入状态敏感的特点
// 希尔排序的思路是，一方面在加大的集合中使用更长的移动步长来快速移动元素
// 另一方面形成 h-th 有序序列后,利用插入排序在处理部分有序的集合时更加高效的特点
template<typename T>
class ShellSort : public SortBase<T> {
public:
    void Sort(vector<T> &elements) {
        unsigned int size = elements.size();
        unsigned int exchanges = 0;

        // 首先进行一个粗略的排序，确保最小的元素在最左
        for (unsigned int i = size - 1; i > 0; i--) {
            if (SortBase<T>::Less(elements[i], elements[i - 1])) {
                SortBase<T>::Exch(elements, i, i - 1);
                exchanges++;
            }
        }

        if (exchanges == 0) return;

        // 接下来的思路和插入排序仍然一致，只不过使用了一个递减的 h 作为比较/移动的步长
        // 当 h 减少到 1 时，就和普通的插入排序完全一样了，但此时被处理的已经是一个至少 4-th 有序的集合
        unsigned int h = 1;
        while (h < size / 3) h = h * 3 + 1;
        while (h >= 1) {
            unsigned int k = h == 1 ? 2 : h;
            for (unsigned int i = k; i < size; i++) {
                T element = elements[i];
                unsigned int j = i;
                while (SortBase<T>::Less(element, elements[j - h])) {
                    elements[j] = elements[j - h];
                    j -= h;
                }
                elements[j] = element;
            }
            h = h / 3;
        }
    }
};

#endif //ALGS4_SORT_SHELL_SORT_H

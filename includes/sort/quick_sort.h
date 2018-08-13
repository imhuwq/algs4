#ifndef ALGS4_QUICK_SORT_H
#define ALGS4_QUICK_SORT_H

#include "sort_base.h"

// 快速排序是一个 O(NlgN) 时间的排序算法, 不需要额外空间
// 快速排序的思路是采用分治法把集合分成左右两边，并且左边的都小于分界的元素，右边的都不小于分界的元素
// 分界后，再把左边和右边分别继续执行以上操作，直到最小的子集合也满足左边的元素都小于右边的元素时，排序就完成了
// 大概需要 O(lgN) 次划分，每次划分需要 O(N) 次比较
template<typename T>
class QuickSort : public SortBase<T> {
private:
    unsigned int Partition(vector<T> &elements, unsigned int lo, unsigned int hi) {
        T key = elements[lo];
        unsigned int left = lo;
        unsigned int right = hi + 1;
        while (true) {
            while (SortBase<T>::Less(elements[++left], key)) {
                if (left == hi) {
                    SortBase<T>::Exch(elements, lo, left);
                    return left;
                }
            }

            while (SortBase<T>::Less(key, elements[--right])) {
                if (right == lo + 1) {
                    return lo;
                }
            }

            if (left >= right) break;
            SortBase<T>::Exch(elements, left, right);
        }
        SortBase<T>::Exch(elements, lo, right);
        return right;
    }

    // 把区间划分成左右两边，再分别排序，排序中会再次划分和排序，所以是递归调用
    void Sort(vector<T> &elements, unsigned int lo, unsigned int hi) {
        if (hi <= lo) return;
        unsigned int divide = Partition(elements, lo, hi);
        if (divide == 0) return;
        Sort(elements, lo, divide - 1);
        Sort(elements, divide + 1, hi);
    }

public:
    void Sort(vector<T> &elements) {
        // 随机打乱避免最差情况
//        shuffle(begin(elements), end(elements), default_random_engine{});
        Sort(elements, 0, elements.size() - 1);
    }
};

#endif //ALGS4_QUICK_SORT_H

#ifndef ALGS4_SORT_MERGE_SORT_H
#define ALGS4_SORT_MERGE_SORT_H

#include <iterator>
#include <algorithm>
#include <sstream>

#include "sort_base.h"
#include "insertion_sort.h"

// 归并排序是一个时间 lgN 但空间 N 的排序算法, 它的优点是把时间缩小到了对数级别, 缺陷是需要使用额外的空间
// 归并排序的思路是, 把集合对半拆分进行排序形成相邻有序的子集合, 然后合并子集合. 这里用到了递归的思想
// 相邻的子集合排序后, 把它们复制到一个辅助集合中去,再从辅助集合中分别拿出两个子集合的元素来比较,并把较小的那个插入到合并的集合中
// 在处理较小的子集合时,转向插入排序效率更好, 而当两个有序的子集合中左侧最大元素不大于右侧最小元素时,可以直接合并而不用分别比较子集合中的元素
// 也可以循环替换集合和辅助集合以减少复制子集合到辅助集合的开销
// 归并排序还有另外一种思路,不是从上往下拆分子集合排序再合并,而是直接从最小的子集合开始一路合并上来, 这时没有了递归, 代码量也更少了,
// 但 MergeUp 时不能通过交换辅助集合的办法减少复制元素的开销
template<typename T>
class MergeSort : public SortBase<T> {
public:
    // 把集合拆分为子集合,分别排序后再合并
    void Sort(vector<T> &elements) {
        aux = elements;
        unsigned int size = elements.size();
        unsigned int lo = 0;
        unsigned int hi = size - 1;
        unsigned int mid = size / 2;

        // 分别排序左边的子集合和右边的子集合
        Sort(aux, elements, lo, mid);       // 交换集合和辅助集合,减少复制子集合到辅助集合的开销
        Sort(aux, elements, mid + 1, hi);   // 交换集合和辅助集合,减少复制子集合到辅助集合的开销
        // 然后再排序
        Merge(elements, aux, lo, mid, hi);  // 交换集合和辅助集合,减少复制子集合到辅助集合的开销
    }

    // 直接从最小的子集合开始网上合并, 没有递归了
    void SortBU(vector<T> &elements) {
        unsigned int size = elements.size();
        aux.reserve(size);
        // sz 为子集合大小, 最小为 1, 最大为 size 的一半
        for (unsigned int sz = 1; sz < size; sz *= 2) {
            // 第一对进行合并的相邻子集合的区间为 0...sz*2-1, 之后每一对起始位置间隔为 sz*2
            for (unsigned int lo = 0; lo < size - sz; lo += sz * 2) {
                unsigned int mid = lo + sz - 1;
                unsigned int hi = min(lo + sz * 2 - 1, size);
                MergeUp(elements, aux, lo, mid, hi);
            }
        }

    }


private:
    vector<T> aux;
    unsigned int cutoff = 7;
    InsertionSort<T> insertionSort;

    // 根据辅助集合中的元素对 lo...hi 范围进行排序,把结果放到 elements 中
    void Sort(vector<T> &elements, vector<T> &aux, unsigned int lo, unsigned int hi) {
        // 子集合较小时, 使用插入排序
        if (hi <= lo + cutoff) {
            insertionSort.Sort(elements, lo, hi);
            return;
        }
        unsigned int mid = lo + (hi - lo) / 2;

        // 分别排序左边的子集合和右边的子集合
        Sort(aux, elements, lo, mid);
        Sort(aux, elements, mid + 1, hi);

        // 再合并两个子集合
        if (aux[mid] < aux[mid + 1]) {
            copy(begin(aux) + lo, begin(aux) + hi + 1, begin(elements) + lo);
        } else {
            Merge(elements, aux, lo, mid, hi);
        }
    }

    void Merge(vector<T> &elements, vector<T> &aux, unsigned int lo, unsigned int mid, unsigned int hi) {
        unsigned int left_pos = lo;
        unsigned int left_end = mid;
        unsigned int right_pos = mid + 1;
        unsigned int right_end = hi;

        unsigned int cur_pos = lo;
        while (cur_pos <= hi) {
            if (left_pos > left_end) elements[cur_pos] = aux[right_pos++];                                  // 左边的子集合已经全部拿完了,直接拿右边的元素
            else if (right_pos > right_end) elements[cur_pos] = aux[left_pos++];                            // 右边的子集合已经全部拿完了,直接拿左边的元素
            else if (MergeSort::Less(aux[left_pos], aux[right_pos])) elements[cur_pos] = aux[left_pos++];   // 从左边和右边选择更小的那个
            else elements[cur_pos] = aux[right_pos++];                                                      // 从左边和右边选择更小的那个
            cur_pos++;
        }
    }

    void MergeUp(vector<T> &elements, vector<T> &aux, unsigned int lo, unsigned int mid, unsigned int hi) {
        unsigned int left_pos = lo;
        unsigned int left_end = mid;
        unsigned int right_pos = mid + 1;
        unsigned int right_end = hi;

        // 仍然需要复制元素到 aux 里面
        for (int k = lo; k <= hi; k++) {
            aux[k] = elements[k];
        }

        unsigned int cur_pos = lo;
        while (cur_pos <= hi) {
            if (left_pos > left_end) elements[cur_pos] = aux[right_pos++];                                  // 左边的子集合已经全部拿完了,直接拿右边的元素
            else if (right_pos > right_end) elements[cur_pos] = aux[left_pos++];                            // 右边的子集合已经全部拿完了,直接拿左边的元素
            else if (MergeSort::Less(aux[left_pos], aux[right_pos])) elements[cur_pos] = aux[left_pos++];   // 从左边和右边选择更小的那个
            else elements[cur_pos] = aux[right_pos++];                                                      // 从左边和右边选择更小的那个
            cur_pos++;
        }
    }
};

#endif //ALGS4_MERGE_SORT_H

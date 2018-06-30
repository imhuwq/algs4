#ifndef ALGS4_SORT_HEAP_SORT_H
#define ALGS4_SORT_HEAP_SORT_H

#include "sort_base.h"

#include <error.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;

template<typename T>
class MaxHeap {
private:
    unsigned int size;
    vector<T> pq;
    std::less<int> less_cmp;

    void swim(unsigned int index) {
        unsigned int parent = index / 2;
        while (index > 1 and less_cmp(pq[parent], pq[index])) {
            swap(pq[index], pq[parent]);
            index = parent;
            parent /= 2;
        }
    }

    void sink(unsigned int index) {
        unsigned int child = index * 2;
        while (child <= size) {
            if (child + 1 <= size and less_cmp(pq[child], pq[child + 1])) child++;
            if (less_cmp(pq[index], pq[child])) swap(pq[index], pq[child]);
            else break;
            index = child;
            child = index * 2;
        }
    }

public:
    MaxHeap(unsigned int size) : size(0), pq(size + 1, T()) {}

    explicit MaxHeap(vector<T> &elements) : size(elements.size()) {
        pq.reserve(elements.size() + 1);
        copy(begin(elements), begin(elements) + size, begin(pq) + 1);
        for (unsigned int index = size / 2; index >= 1; index--) sink(index);
    }

    unsigned int Size() { return size; }

    void Insert(T &element) {
        pq[++size] = element;
        swim(size);
    }

    T Max() { return pq[1]; }

    T Pop() {
        if (size == 0) throw runtime_error("Pop from an empty heap");
        T max = pq[1];
        pq[1] = pq[size--];
        pq.pop_back();
        sink(1);
        return max;
    }
};

template<typename T>
class MinHeap {
private:
    unsigned int size;
    vector<T> pq;
    std::greater<int> greater_cmp;

    void swim(unsigned int index) {
        unsigned int parent = index / 2;
        while (index > 1 and greater_cmp(pq[parent], pq[index])) {
            swap(pq[index], pq[parent]);
            index = parent;
            parent /= 2;
        }
    }

    void sink(unsigned int index) {
        unsigned int child = index * 2;
        while (child <= size) {
            if (child + 1 <= size and greater_cmp(pq[child], pq[child + 1])) child++;
            if (greater_cmp(pq[index], pq[child])) swap(pq[index], pq[child]);
            else break;
            index = child;
            child = index * 2;
        }
    }

public:
    MinHeap(unsigned int size) : size(0), pq(size + 1, T()) {}

    explicit MinHeap(vector<T> &elements) : size(elements.size()) {
        pq.reserve(elements.size() + 1);
        copy(begin(elements), begin(elements) + size, begin(pq) + 1);
        for (unsigned int index = size / 2; index >= 1; index--) sink(index);
    }

    unsigned int Size() { return size; }

    void Insert(T &element) {
        pq[++size] = element;
        swim(size);
    }

    T Min() { return pq[1]; }

    T Pop() {
        if (size == 0) throw runtime_error("Pop from an empty heap");
        T min = pq[1];
        pq[1] = pq[size--];
        pq.pop_back();
        sink(1);
        return min;
    }
};


// 堆排序使用不超过 2N + 2NlgN 次比较和 N + NlgN 次交换来实现排序，不需要使用额外的空间
// 堆排序的思路是，把集合构建成一个堆结构，然后依次从堆里面拿出最大的放到最后面
// 这里所用的堆结构有这个特征，对集合中索引为 i 的元素，索引 2i 和 2i+1 的元素为子元素(如果存在的话)，并且不大于其父元素
// 由父元素和子元素索引之间的 2 倍关系可以看出这是一个 lgN 相关的算法
template<typename T>
class HeapSort : public SortBase<T> {
public:
    void Sort(vector<T> &elements) {
        unsigned int size = elements.size();

        // 从半中间的元素开始调用 Sink 来把整个集合构建成堆集合
        // 相当于先构建最末端的小堆(索引比较大的堆)，再通过对它们的父亲调用 sink 构建更大的堆，直到对第一个元素调用 sink 构建整个集合的堆
        // 这里利用到了和归并排序里面 MergeBU 类似的思路，并且利用了对两个小堆的父亲执行一次 sink 即可直接构建以父亲为根的大堆的特性
        // 这里使用到了不多于 2N 次比较和 N 次交换
        for (unsigned int index = size / 2; index >= 1; index--) Sink(elements, index, size);

        // 构建成堆后，依次选出最大的元素放到后面
        // 这里使用到了 N 次 Sink, 也就是 2NlgN次比较和 NlgN 次 交换
        while (size > 1) {
            Exch(elements, 1, size--);
            Sink(elements, 1, size);
        }

        // 总共 2N+2lgN 次比较和 N+lgN 次交换
    }

private:
    bool Less(const vector<T> &elements, unsigned int i, unsigned int j) {
        return SortBase<T>::Less(elements[i - 1], elements[j - 1]);
    }

    void Exch(vector<T> &elements, unsigned int i, unsigned int j) {
        SortBase<T>::Exch(elements, i - 1, j - 1);
    }

    // 把集合中索引为 index 的元素下沉， 区间为 index...end，下沉操作后，index...end 区间为堆结构
    // 每次 Sink 需要 lg(end-index) 次交换 和 2lg(end-index）次 比较， 分别简化为 O(lgN) 和 O(2lgN)
    void Sink(vector<T> &elements, unsigned int index, unsigned int end) {
        unsigned int child = index * 2;
        while (child <= end) {
            if (child + 1 <= end and Less(elements, child, child + 1)) child += 1;
            if (Less(elements, index, child)) Exch(elements, index, child);
            index = child;
            child = index * 2;
        }
    }
};

#endif //ALGS4_SORT_HEAP_SORT_H

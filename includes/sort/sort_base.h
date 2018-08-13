#ifndef ALGS4_SORT_SORTBASE_H
#define ALGS4_SORT_SORTBASE_H


// 各种排序的时间和空间, 以及说明
// 排序方法             时间              空间              备注
// 选择排序             O(N^2)            \
// 插入排序             O(N^2)            \                虽然也是平方级的，但是通常不要那么久，对小规模集合效率比较高
// 希尔排序             不到O(N^2)         \
// 归并排序             O(NlgN)           O(N)             需要额外空间，但表现非常稳定
// 快速排序             O(NlgN)           \                不需要额外空间，但表现没那么稳定，最差可能是 O(N^2)
// 堆排序               O(NlgN+N)        \                 不需要额外空间，表现比较稳定，但通常情况下没有快排效率那么高

// 关于各类算法比较普遍的优化思路：
// 1. 减少创建局部变量的次数
// 2. 减少通过下表获取集合元素的次数
// 3. 减少递归的次数以避免栈消耗
// 4. 内存的 locality


#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template<typename T>
class SortBase {
public:
    // 子类实现具体的排序算法，所有元素放在 vector 中
    virtual void Sort(vector<T> &elements) {}

    // 检查所有元素是否按从小到大排列好了
    bool IsSorted(const vector<T> &elements) {
        for (int i = 1; i < elements.size(); i++) {
            if (SortBase::Less(elements[i], elements[i - 1])) return false;
        }
        return true;
    }

    // 在一行中输出所有的元素，元素类型必须实现了 operator<<
    void Show(const vector<T> &elements) {
        for (auto &element:elements) {
            cout << element << " ";
        }
        cout << endl;
    }

protected:
    static bool Less(const T &a, const T &b) { return a < b; }

    static bool More(const T &a, const T &b) { return a > b; }

    // 交换 index i 和 j 处的元素
    static void Exch(vector<T> &elements, unsigned int i, unsigned int j) {
        swap(elements[i], elements[j]);
    }
};

#endif //ALGS4_SORT_SORTBASE_H

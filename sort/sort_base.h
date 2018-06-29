#ifndef ALGS4_SORT_SORTBASE_H
#define ALGS4_SORT_SORTBASE_H

#include <vector>
#include <iostream>

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
    static bool Less(T a, T b) { return a < b; }

    // 交换 index i 和 j 处的元素
    static void Exch(vector<T> &elements, unsigned int i, unsigned int j) {
        T tmp = elements[i];
        elements[i] = elements[j];
        elements[j] = tmp;
    }
};

#endif //ALGS4_SORT_SORTBASE_H

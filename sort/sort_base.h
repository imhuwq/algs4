#ifndef ALGS4_SORT_SORTBASE_H
#define ALGS4_SORT_SORTBASE_H

#include <vector>
#include <iostream>

using namespace std;

template<typename T>
class SortBase {
public:
    static void Sort(vector<T> comparable) {}

    static bool IsSorted(const vector<T> &comparable) {
        for (int i = 1; i < comparable.size(); i++) {
            if (Less(comparable[i], comparable[i - 1])) return false;
        }
    }

    static void Show(const vector<T> comparable) {
        for (auto &mem:comparable) {
            cout << mem << " ";
        }
        cout << endl;
    }

private:
    static bool Less(T a, T b) { return a < b; }

    static void Exch(vector<T> &comparable, unsigned int i, unsigned int j) {
        T tmp = comparable[i];
        comparable[i] = comparable[j];
        comparable[j] = tmp;
    }
};

#endif //ALGS4_SORT_SORTBASE_H

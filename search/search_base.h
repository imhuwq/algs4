#ifndef ALGS4_SEARCH_SEARCH_BASE_H
#define ALGS4_SEARCH_SEARCH_BASE_H

#include <vector>

using namespace std;

template<typename K, typename V>
class SearchBase {

public:
    virtual void Put(const K &key, const V val) = 0;

    virtual V Get(const K &key) = 0;

    virtual void Delete(const K &key) = 0;

    bool Contains(const K &key) { return Get(key) == nullptr; }

    bool IsEmpty() { return Size() == 0; }

    virtual int Size() = 0;

    virtual int Size(const K &lo, const K &hi) {
        if (hi < lo) return 0;
        else if (Contains(hi)) return Rank(hi) - Rank(lo) + 1;
        else return Rank(hi) - Rank(lo);
    }

    virtual K Min() = 0;

    void DeleteMin() { Delete(Min()); }

    virtual K Max() = 0;

    void DeleteMax() { Delete(Max()); }

    virtual K Floor(const K &key) = 0;

    virtual K Ceiling(const K &key) = 0;

    virtual int Rank(const K &key) = 0;

    virtual K Select(int rank) = 0;

    virtual vector<K> Keys(const K &lo, const K &hi) = 0;

    vector<K> Keys() { return Keys(Min(), Max()); }
};

#endif //ALGS4_SEARCH_SEARCH_BASE_H

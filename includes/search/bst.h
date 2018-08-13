#ifndef ALGS4_SEARCH_BST_H
#define ALGS4_SEARCH_BST_H

#include <vector>
#include <memory>
#include <error.h>

using namespace std;

// 二叉树的特点是树由节点构成，每个节点包含指向左右两个子节点的指针，左边的节点比自己小，右边的节点比自己大(不支持相同的节点)。
// 二叉树使用 O(lgN) 次查找，最坏情况下要使用 N 次查找
template<typename K, typename V>
class BST {
private:
    struct Node_;
    typedef shared_ptr<Node_> Node;

    struct Node_ {
        Node_() = default;

        Node_(const K &k, const V &v) : key(k), val(v) {}

        K key;
        V val;
        Node left = nullptr;
        Node right = nullptr;
        int size = 1;
    };

    Node root;

    int Size(Node node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    Node Put(Node node, const K &k, const V &v) {
        if (node == nullptr) {
            node = make_shared<Node_>(k, v);
            node->val = v;
            return node;
        }
        if (k > node->key) node->right = Put(node->right, k, v);
        else if (k < node->key) node->left = Put(node->left, k, v);
        else node->val = v;
        node->size = Size(node->left) + 1 + Size(node->right);
        return node;
    }

    V Get(const Node node, const K &key) {
        if (node == nullptr) throw runtime_error("Get value from empty node");
        if (key > node->key) return Get(node->right, key);
        else if (key < node->key) return Get(node->left, key);
        return node->val;
    }

    Node DeleteMin(Node node) {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node->right;
        node->left = DeleteMin(node->left);
        node->size = Size(node->left) + 1 + Size(node->right);
        return node;
    }

    Node Delete(Node node, const K &key) {
        if (node == nullptr) return nullptr;
        if (key < node->key) node->left = Delete(node->left, key);
        else if (key > node->key) node->right = Delete(node->right, key);
        else if (key == node->key) {
            if (node->right == nullptr) return node->left;
            if (node->left == nullptr) return node->right;
            Node tmpNode = node;
            node = Min(tmpNode->right);
            node->right = DeleteMin(tmpNode->right);
            node->left = tmpNode->left;
        }
        node->size = Size(node->left) + 1 + Size(node->right);
        return node;
    }

    bool Contains(Node node, const K &key) {
        if (node == nullptr) return false;
        if (key > node->key) return Contains(node->right, key);
        else if (key < node->key) return Contains(node->left, key);
        return true;
    }

    bool Min(Node node, K &key) {
        if (node == nullptr) return false;
        if (node->left != nullptr) return Min(node->left, key);
        key = node->key;
        return true;
    }

    Node Min(Node node) {
        if (node == nullptr) return nullptr;
        if (node->left != nullptr) return Min(node->left);
        return node;
    }

    bool Max(Node node, K &key) {
        if (node == nullptr) return false;
        if (node->right != nullptr) return Max(node->right, key);
        key = node->key;
        return true;
    }

    Node Max(Node node) {
        if (node == nullptr) return nullptr;
        if (node->right != nullptr) return Max(node->right);
        return node;
    }

    bool Floor(Node node, const K &key, K &receiveKey) {
        if (node == nullptr) return false;
        if (key < node->key) return Floor(node->left, key, receiveKey);
        if (key == node->key) receiveKey = key;
        if (!Floor(node->right, key, receiveKey)) receiveKey = node->key;
        return true;
    }

    bool Ceiling(Node node, const K &key, K &receiveKey) {
        if (node == nullptr) return false;
        if (key > node->key) return Ceiling(node->right, key, receiveKey);
        if (key == node->key) receiveKey = key;
        if (!Ceiling(node->left, key, receiveKey)) receiveKey = node->key;
        return true;
    }

    int Rank(Node node, const K &key) {
        if (node == nullptr) return 0;
        if (key == node->key) return Size(node->left);
        if (key < node->key) return Rank(node->left, key);
        return Size(node->left) + 1 + Rank(node->right);
    }

    Node Select(Node node, int rank) {
        if (node == nullptr) return nullptr;
        int leftSize = Size(node->left);
        if (rank < leftSize) return Select(node->left, rank);
        if (rank > leftSize) return Select(node->right, rank - leftSize - 1);
        return node;
    }

    void Keys(Node &node, const K &lo, const K &hi, vector<K> &receiveVector) {
        if (node == nullptr) return;
        if (lo < node->key) Keys(node->left, lo, hi, receiveVector);
        if (lo <= node->key && hi >= node->key) receiveVector.push_back(node->key);
        if (hi > node->key) Keys(node->right, lo, hi, receiveVector);
    }

public:
    BST() { root = nullptr; }

    int Size() { return Size(root); }

    void Put(const K &key, const V &val) { root = Put(root, key, val); }

    V Get(const K &key) { return Get(root, key); }

    void Delete(const K &key) { root = Delete(root, key); }

    bool Contains(const K &key) { return Contains(root, key); }

    bool Min(K &key) { return Min(root, key); }

    Node Min() { return Min(root); }

    bool Max(K &key) { return Max(root, key); }

    Node Max() { return Max(root); }

    bool Floor(const K &key, K &receiveKey) { return Floor(root, key, receiveKey); }

    bool Ceiling(const K &key, K &receiveKey) { return Ceiling(root, key, receiveKey); }

    int Rank(const K &key) { return Rank(root, key); }

    Node Select(int rank) { return Select(root, rank); }

    void Keys(const K &lo, const K &hi, vector<K> &receiveVector) { Keys(root, lo, hi, receiveVector); }

    void Keys(vector<K> &receiveVector) {
        K minKey, maxKey;
        if (Min(minKey) && Max(maxKey)) return Keys(minKey, maxKey, receiveVector);
    }
};

#endif //ALGS4_SEARCH_BST_H

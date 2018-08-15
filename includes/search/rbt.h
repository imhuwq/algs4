#ifndef ALGS4_SEARCH_RBT_H
#define ALGS4_SEARCH_RBT_H

#include <vector>
#include <memory>
#include <error.h>
#include <gtest/gtest_prod.h>

using namespace std;

typedef bool COLOR;
#define RED true
#define BLACK false

template<typename K, typename V>
class RBT {
    FRIEND_TEST(RBT_TEST, TEST_CREATE_TREE);

    FRIEND_TEST(RBT_TEST, TEST_PUT_SINGLE_2_NODE_LEFT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_SINGLE_2_NODE_RIGHT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_LEFT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_MID);

    FRIEND_TEST(RBT_TEST, TEST_PUT_SINGLE_3_NODE_RIGHT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_BOTTOM_2_NODE_LEFT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_BOTTOM_2_NODE_RIGHT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_LEFT);

    FRIEND_TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_MID);

    FRIEND_TEST(RBT_TEST, TEST_PUT_BOTTOM_3_NODE_RIGHT);

    FRIEND_TEST(RBT_TEST, TEST_TREE_IS_BALANCED);

private:
    struct Node_;
    typedef shared_ptr<Node_> Node;


    struct Node_ {
        Node_() : left(nullptr), right(nullptr), color(BLACK) {}

        Node_(const K &key, const V &val) : k(key), v(val), left(nullptr), right(nullptr), color(RED) {}

        K k;
        V v;
        Node left = nullptr;
        Node right = nullptr;
        COLOR color = BLACK;
        int size = 1;

        bool IsRed() { return this != nullptr && color == RED; }
    };

    Node root;

    int GetSize(Node node) {
        if (node == nullptr) return 0;
        return node->size;
    }

    V Get(Node node, const K &key) {
        if (node == nullptr) throw runtime_error("Get value from empty node");
        if (key == node->k) return node->v;
        else if (key < node->k) return Get(node->left, key);
        return Get(node->right, key);
    }

    // this method is only for test purpose
    Node GetNode(Node node, const K &key) {
        if (node == nullptr) throw runtime_error("Get node from empty node");
        if (key == node->k) return node;
        else if (key < node->k) return GetNode(node->left, key);
        else if (key > node->k) return GetNode(node->right, key);
    }

    // this method is only for test purpose
    Node GetNode(const K &key) { return GetNode(root, key); }

    // this method is only for test purpose
    Node GetRoot() { return root; }

    // this method is only for test purpose
    int CheckTree(Node node, COLOR parent_color, int black_link) {
        if (node == nullptr) return black_link;
        if (parent_color == RED && node->IsRed()) return -1;
        if (!node->IsRed()) black_link += 1;
        int left_black_link = CheckTree(node->left, node->color, black_link);
        int right_black_link = CheckTree(node->right, node->color, black_link);
        if (left_black_link == right_black_link) return left_black_link;
        else return -1;
    }

    // this method is only for test purpose
    bool CheckTree() {
        if (root == nullptr) return true;
        if (root->IsRed()) return false;
        int black_link = 0;
        return CheckTree(root->left, root->color, black_link) == CheckTree(root->right, root->color, black_link) >= 0;
    }

    Node FlipColor(Node node) {
        assert(!node->IsRed());
        assert(node->left->IsRed());
        assert(node->right->IsRed());

        node->left->color = BLACK;
        node->right->color = BLACK;
        node->color = RED;

        return node;
    }

    Node RotateLeft(Node node) {
        assert(node != nullptr);
        assert(node->right->IsRed());

        Node new_node = node->right;
        node->right = new_node->left;
        new_node->left = node;

        new_node->size = node->size;
        node->size = GetSize(node->left) + GetSize(node->right) + 1;

        new_node->color = node->color;
        node->color = RED;

        return new_node;
    }

    Node RotateRight(Node node) {
        assert(node != nullptr);
        assert(node->left->IsRed());

        Node new_node = node->left;
        node->left = new_node->right;
        new_node->right = node;

        new_node->size = node->size;
        node->size = GetSize(node->left) + GetSize(node->right) + 1;

        new_node->color = node->color;
        node->color = RED;
        return new_node;
    }

    Node BalanceNode(Node node) {
        if (node == nullptr) return node;
        if (node->right->IsRed() && !node->left->IsRed()) node = RotateLeft(node);
        if (node->left->IsRed() && node->left->left->IsRed()) node = RotateRight(node);
        if (node->left->IsRed() && node->right->IsRed()) node = FlipColor(node);
        return node;
    }

    Node Put(Node node, const K &key, const V &value) {
        if (node == nullptr) return make_shared<Node_>(key, value);
        if (key == node->k) node->v = value;
        else if (key < node->k) node->left = Put(node->left, key, value);
        else if (key > node->k) node->right = Put(node->right, key, value);
        node = BalanceNode(node);
        node->size = GetSize(node->left) + GetSize(node->right) + 1;
        return node;
    }

public:
    RBT() : root(nullptr) {}

    int GetSize() { return GetSize(root); }

    V Get(const K &key) { return Get(root, key); }

    void Put(const K &key, const V &value) {
        root = Put(root, key, value);
        root->color = false;
    }
};

#endif //ALGS4_SEARCH_RBT_H

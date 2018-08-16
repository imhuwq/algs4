#ifndef ALGS4_SEARCH_RBT_H
#define ALGS4_SEARCH_RBT_H

#include <vector>
#include <memory>
#include <error.h>
#include <gtest/gtest_prod.h>
#include <cassert>

using namespace std;

#define DEBUG(msg) std::cerr << (msg) << endl

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

    FRIEND_TEST(RBT_TEST, TEST_DELETE);

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
        if (node == nullptr) throw runtime_error("Get value by a unset key");
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
    int ReCountSize(Node node) {
        if (node == nullptr) return 0;
        return ReCountSize(node->left) + ReCountSize(node->right) + 1;
    }

    // this method is only for test purpose
    int CheckTree(Node node, COLOR parent_color, int black_link) {
        if (node == nullptr) return black_link;
        if (parent_color == RED && node->IsRed()) return -1;
        if (!node->IsRed()) black_link += 1;
        int left_black_link = CheckTree(node->left, node->color, black_link);
        int right_black_link = CheckTree(node->right, node->color, black_link);
        if (left_black_link != right_black_link) return -1;
        else if (ReCountSize(node) != node->size) return -1;
        return left_black_link;
    }

    // this method is only for test purpose
    bool CheckTree() {
        if (root == nullptr) return true;
        if (root->IsRed()) return false;
        int black_link = 0;
        return CheckTree(root->left, root->color, black_link) == CheckTree(root->right, root->color, black_link) >= 0;
    }

    Node FlipColor(Node node) {
        node->left->color = !node->left->color;
        node->right->color = !node->right->color;
        node->color = !node->color;

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
        node->size = GetSize(node->left) + GetSize(node->right) + 1;
        return node;
    }

    Node Put(Node node, const K &key, const V &value) {
        if (node == nullptr) return make_shared<Node_>(key, value);
        if (key == node->k) node->v = value;
        else if (key < node->k) node->left = Put(node->left, key, value);
        else if (key > node->k) node->right = Put(node->right, key, value);
        node = BalanceNode(node);
        return node;
    }

    Node Min(Node node) {
        assert(node != nullptr);
        if (node->left != nullptr) return Min(node->left);
        return node;
    }

    Node MoveRedLeft(Node node) {
        assert(node->IsRed() && !node->left->IsRed() && !node->left->left->IsRed());
        node = FlipColor(node);
        if (node->right->left->IsRed()) {
            node->right = RotateRight(node->right);
            node = RotateLeft(node->left);
            node = FlipColor(node);
        }
        return node;
    }

    Node MoveRedRight(Node node) {
        assert(node->IsRed() && !node->right->IsRed() && !node->right->left->IsRed());
        node = FlipColor(node);
        if (node->left->left->IsRed()) {
            node = RotateRight(node);
            node = FlipColor(node);
        }
        return node;

    }

    Node DeleteMin(Node node) {
        assert(node != nullptr);
        assert(node->IsRed() || node->left->IsRed());
        if (node->left == nullptr) return nullptr;
        if (!node->left->IsRed() && !node->left->left->IsRed()) node = MoveRedLeft(node);
        node->left = DeleteMin(node->left);
        node = BalanceNode(node);
        return node;
    }

    Node Delete(Node node, const K &key) {
        if (node == nullptr) throw runtime_error("Delete value by a unset key");

        if (key < node->k) {
            if (!node->left->IsRed() && !node->left->left->IsRed()) node = MoveRedLeft(node);
            node->left = Delete(node->left, key);
        } else {
            if (node->left->IsRed()) node = RotateRight(node);

            if (key == node->k && node->right == nullptr) return nullptr;

            if (!node->right->IsRed() && !node->right->left->IsRed()) node = MoveRedRight(node);

            if (key == node->k) {
                Node min_node = Min(node->right);
                node->k = min_node->k;
                node->v = min_node->v;
                node->right = DeleteMin(node->right);
            } else {
                node->right = Delete(node->right, key);
            }
        }

        node = BalanceNode(node);
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

    void Delete(const K &key) {
        if (root == nullptr) throw runtime_error("Delete from empty tree");
        if (!root->left->IsRed() && !root->right->IsRed()) root->color = RED;
        root = Delete(root, key);
        if (root != nullptr) root->color = BLACK;
    }
};

#endif //ALGS4_SEARCH_RBT_H

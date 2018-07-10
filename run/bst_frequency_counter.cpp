#include "bst.h"
#include "file_word_reader.h"

int main(const int *argc, const char **argv) {
    string filePath;
    cout << "请输入数据文件路径: ";
    cin >> filePath;
    cout << endl;

    vector<string> words = ReadWords(filePath);
    BST<string, int> bst;
    for (auto &word:words) {
        if (bst.Contains(word)) {
            bst.Put(word, bst.Get(word) + 1);
        } else {
            bst.Put(word, 1);
        }
    }

    vector<string> counter;
    bst.Keys(counter);
    string maxCounter = " ";
    bst.Put(maxCounter, 0);
    for (auto &word:counter) {
        if (bst.Get(word) > bst.Get(maxCounter)) {
            maxCounter = word;
        }
    }

    string maxKey = bst.Max()->key;
    cout << "Max key: " << maxKey << endl;

    while (bst.Size()) {
        string minKey = bst.Min()->key;
        cout << minKey << " " << bst.Get(minKey) << endl;
        bst.Delete(minKey);
    }
}
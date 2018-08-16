#include <iostream>
#include "search/rbt.h"
#include "common/word_reader.h"

int main() {
    vector<string> words = ReadWords("data/tale.txt");
    RBT<string, int> rbt;
    for (auto &word:words) {
        if (rbt.Contains(word)) {
            rbt.Put(word, rbt.Get(word) + 1);
        } else {
            rbt.Put(word, 1);
        }
    }

    vector<string> counter;
    rbt.Keys(counter);
    string maxCounter = " ";
    rbt.Put(maxCounter, 0);
    for (auto &word:counter) {
        if (rbt.Get(word) > rbt.Get(maxCounter)) {
            maxCounter = word;
        }
    }
    while (rbt.GetSize()) {
        string minKey = rbt.Min();
        rbt.Delete(minKey);
    }
}
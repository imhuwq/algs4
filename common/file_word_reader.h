#ifndef ALGS4_COMMON_FILE_WORD_READER_H
#define ALGS4_COMMON_FILE_WORD_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

vector<string> ReadWords(const string &filePath) {
    ifstream stream(filePath);

    string word;
    vector<string> words;

    while (stream >> word) {
        words.push_back(word);
    }

    stream.close();
    return words;
}

#endif //ALGS4_COMMON_FILE_WORD_READER_H

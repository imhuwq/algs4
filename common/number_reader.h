#ifndef ALGS4_COMMON_NUMBER_READER_H
#define ALGS4_COMMON_NUMBER_READER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template<typename Num>
vector<Num> ReadNumbers(const string &filePath) {
    ifstream stream(filePath);

    Num number;
    vector<Num> numbers;

    if (stream) cout << filePath << endl;

    while (stream >> number) {
        cout << number << endl;
        numbers.push_back(number);
    }

    stream.close();
    return numbers;
}

#endif //ALGS4_COMMON_NUMBER_READER_H

#include <iostream>

#include "number_reader.h"

using namespace std;

int main(const int argc, const char **argv) {
	string filePath;
	cout << "请输入数据文件路径: ";
	cin >> filePath;
	cout << endl;

	vector<int> numbers = ReadNumbers<int>(filePath);

	cout << numbers.size() << endl;
}

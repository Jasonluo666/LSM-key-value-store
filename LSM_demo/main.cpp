#include "iostream"
#include "DiskRun.hpp"

using namespace std;

int main(int argc, char* argv) {

	cout << "hello world" << endl;

	DiskRun<int, int> diskRun(1024, 16, 1, 1);
	vector<Pair<int, int>> test;
	for (int i = 0; i < 100; i++) {
		test.push_back(Pair<int, int>(i, i));
	}
	
	diskRun.merge(test);
	diskRun.rangeSearch(0, 10);

	system("pause");
	return 0;
}
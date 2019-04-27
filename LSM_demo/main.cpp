#include "iostream"
#include "DiskRun.hpp"
#include "BloomFilter.hpp"
#include "LSM.hpp"

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

	int test_num = 10000;
	BloomFilter<int> filter(test_num, 0.1);
	for(int i = 0; i < test_num; i++) {
		filter.addKey(i);
	}

	int matrix[2][2] = {0, 0, 0, 0};
	for(int i = 0; i < test_num * 2; i++) {

		if (filter.contain(i))
			if (i < test_num)
				matrix[0][0] += 1;
			else
				matrix[0][1] += 1;
		else
			if (i < test_num)
				matrix[1][0] += 1;
			else
				matrix[1][1] += 1;
	}

	cout << "TP" << matrix[0][0] << endl;
	cout << "FP" << matrix[0][1] << endl;
	cout << "FN" << matrix[1][0] << endl;
	cout << "TN" << matrix[1][1] << endl;

	system("pause");
	return 0;
}
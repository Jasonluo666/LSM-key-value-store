#include "iostream"
#include "DiskRun.hpp"
#include "LSM.hpp"
#include "stdlib.h"
#include "test.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	cout << "hello world" << endl;
	LSM<int,int> tree(4096,4096,16,2);
	//for(int i = 0; i < 1024; i++){
 //       tree.insert(i,i);
	//}
	//for(int i = 0; i < 2000; i++){
 //       prints(tree.lookup(i));
	//}

	TestParams param;
	param.num_insert = 1000;
	param.num_lookup = 2000;
	param.range_min = 0;
	param.range_max = 2000;

	performanceTest<int, int>(tree, param);
	//prints(tree.range(-500,1500));

	/*
	int test_num = 10000;
	BloomFilter<int> filter(test_num, 0.1);
	for (int i = 0; i < test_num; i++) {
		filter.addKey(i);
	}

	int matrix[2][2] = { 0, 0, 0, 0 };
	for (int i = 0; i < test_num * 2; i++) {

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
	*/

	system("pause");
	return 0;
}

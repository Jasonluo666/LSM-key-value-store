#include "iostream"
#include "DiskRun.hpp"
#include "LSM.hpp"
#include "stdlib.h"
#include "test.hpp"

using namespace std;

int main(int argc, char* argv[]) {

	cout << "hello world" << endl;
	//LSM<int,int> tree(4096,4096,16,2, 0.1);

//	for(int i = 0; i < 10000; i++){
//        tree.insert(i,i);
//	}
//	for(int i = 0; i < 10000; i+=2){
//        tree.delete_key(i);
//	}
//	for(int i = 0; i < 10000; i++){
//        prints(tree.lookup(i));
//	}
//	prints(tree.range(-500,1500));

	//for(int i = 0; i < 1024; i++){
 //       tree.insert(i,i);
	//}
	//for(int i = 0; i < 2000; i++){
 //       prints(tree.lookup(i));
	//}

	LSMParams param;

	//performanceTest<int, int>(param, 10000, 10000);
	//rangeSearchTest<int, int>(param, 1000, 0, 2000);

	//bloomfilterTest<int, int>(param, 1000);
	//throughputTest<int, int>(param, 32768);
	runsizeTest<int, int>(param, 32768);

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
	//tree.clearfiles();

	system("pause");
	return 0;
}

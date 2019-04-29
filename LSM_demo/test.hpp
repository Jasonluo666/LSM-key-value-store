#ifndef _TEST
#define _TEST

#include <iostream>
#include <vector>
#include "Run.hpp"

using namespace std;

void prints( vector<Pair<int,int> > KV_pairs){
    for(int i = 0; i < (int)KV_pairs.size(); i++){
//        if(KV_pairs[i].value != TOMBSTONE)
        cout<<"<"<<KV_pairs[i].key<<","<<KV_pairs[i].value<<">"<<endl;
    }
}

void prints(Pair<int,int> aPair){
    if(aPair.value == TOMBSTONE){
        cout<<"No such entry"<<endl;
    }
    else{
        cout<<"<"<<(aPair).key<<","<<(aPair).value<<">"<<endl;
    }
}

vector<Pair<int,int> > createvector(int n){
    vector<Pair<int,int> > Pairs;
    Pair<int,int> aPair;
    for(int i = 0; i < n; i++){
        aPair.key = i;
        aPair.value = i;
        Pairs.push_back(aPair);
    }
    return Pairs;
}

#endif // _TEST


#include <iostream>
#include "fstream"
#include "vector"
#include <random>
#include <windows.h>
using namespace std;

struct TestParams {
	int num_insert;
	int num_lookup;
	int range_min = 0;
	int range_max = 10000;
	int printout_num = 100;
};

template<typename K, typename V>
void performanceTest(LSM<K, V> lsm, TestParams param) {
	//LSM* lsm(param.entry_per_run, param.run_per_level, param.fp_rate, param.pageSize);

	SYSTEMTIME start, finish;
	vector<int> insert_data;
	std::uniform_int_distribution<int> distribution(INT_MIN + 1, INT_MAX);
	std::default_random_engine generator;

	// insert uniformly distributed data
	for (int i = 0; i < param.num_insert; i++) {
		insert_data.push_back(distribution(generator));
	}

	cout << "insert start" << endl;
	GetSystemTime(&start);
	for (int i = 0; i < param.num_insert; i++) {
		if (i % param.printout_num == 0) {
			GetSystemTime(&finish);
			cout << "stage: " << i << " : time cost: " << finish.wMilliseconds - start.wMilliseconds << endl;
		}
		lsm.insert(insert_data[i], i);
	}
	GetSystemTime(&finish);
	cout << "insert finish" << endl;

	cout << "time cost " <<  (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms" << endl;


	cout << "sequential lookup start" << endl;
	GetSystemTime(&start);
	Pair<K, V> pair;
	for (int i = 0; i < param.num_lookup; i++) {
		if (i % param.printout_num == 0) {
			GetSystemTime(&finish);
			cout << "stage: " << i << " : time cost: " << finish.wMilliseconds - start.wMilliseconds << endl;
		}

		if (i < param.num_insert) {
			pair = lsm.lookup(insert_data[i]);
		}
		//  some random lookup value (test not found cost)
		else {
			pair = lsm.lookup(distribution(generator));
		}
	}
	GetSystemTime(&finish);
	cout << "sequential lookup finish" << endl;


	cout << "time cost " <<  (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms" << endl;



	// update -> insert same keys with different values
	cout << "update start" << endl;
	GetSystemTime(&start);
	for (int i = 0; i < param.num_insert; i++) {
		if (i % param.printout_num == 0) {
			GetSystemTime(&finish);
			cout << "stage: " << i << " : time cost: " << finish.wMilliseconds - start.wMilliseconds << endl;
		}

		lsm.insert(insert_data[i], -1);
	}
	GetSystemTime(&finish);
	cout << "insert finish" << endl;

	// check if uodated -> current values are equal to -1
	cout << "validation.." << endl;
	for (int i = 0; i < param.num_insert; i++) {
		pair = lsm.lookup(insert_data[i]);
		if (pair.value != -1)
			break;
	}

	/* TODO: size should not change */

	if (pair.value != -1)
		cout << "validation fails" << endl;
	else
		cout << "validation succeeds" << ends;


	cout << "time cost " <<  (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms" << endl;



	// delete -> delete all values
	cout << "delete start" << endl;
	GetSystemTime(&start);
	for (int i = 0; i < param.num_insert; i++) {
		if (i % param.printout_num == 0) {
			GetSystemTime(&finish);
			cout << "stage: " << i << " : time cost: " << finish.wMilliseconds - start.wMilliseconds << endl;
		}

		lsm.delete_key(insert_data[i]);
	}
	GetSystemTime(&finish);
	cout << "insert finish" << endl;

	// check if deleted -> push new data in
	cout << "validation.." << endl;
	for (int i = 0; i < param.num_insert; i++) {
		pair = lsm.lookup(insert_data[i]);
		if (pair.value != TOMBSTONE)
			break;
	}

	/* TODO: size should not change */

	if (pair.value != TOMBSTONE)
		cout << "validation fails" << endl;
	else

		cout << "validation succeeds" << ends;


	cout << "time cost " <<  (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms" << endl;

}

template<typename K, typename V>
void rangeSearchTest(LSM<K, V> lsm, TestParams param) {
	//LSM* lsm(param.entry_per_run, param.run_per_level, param.fp_rate, param.pageSize);

	SYSTEMTIME start, finish;
	vector<int> insert_data;

	// insert uniformly distributed data
	for (int i = param.range_min; i < param.range_max; i++) {
		insert_data.push_back(i);
	}

	cout << "insert start" << endl;
	GetSystemTime(&start);
	for (int i = param.range_min; i < param.range_max; i++) {
		if (i % param.printout_num == 0) {
			GetSystemTime(&finish);
			cout << "stage: " << i << " : time cost: " << finish.wMilliseconds - start.wMilliseconds << endl;
		}

		lsm.insert(insert_data[i], i);
	}
	GetSystemTime(&finish);
	cout << "insert finish" << endl;


	cout << "time cost " << (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms"<< endl;


	cout << "range search start" << endl;
	GetSystemTime(&start);
	vector< Pair<K, V> > search = lsm.range(param.range_min, param.range_max);
	cout << "range search finish" << endl;
	GetSystemTime(&finish);

	cout << "validation.." << endl;

	for (int i = 0; i < param.num_insert; i++) {
		lsm.insert(insert_data[i], i);
	}

	/* TODO: size should not change */
	int return_size = (int)(lsm.range(param.range_min, param.range_max)).size();

	if (return_size != param.range_max - param.range_min)
		cout << "validation fails" << endl;
	else
		cout << "validation succeeds" << ends;

	cout << "time cost " <<  (finish.wSecond - start.wSecond) * 1000 + finish.wMilliseconds - start.wMilliseconds << "ms" << endl;
}
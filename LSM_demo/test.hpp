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

struct LSMParams {
	int buffer_size = 4096;
	int page_size = 4096;
	int max_level = 8;
	int runs_per_level = 2;
	double FP_rate = 0.1;
	int printout_num = 100;
};

template<typename K, typename V>
void runsizeTest(LSMParams param, int num_opr) {
	DWORD start, finish;
	vector<int> insert_data, lookup_key;
	std::uniform_int_distribution<int> distribution(INT_MIN + 1, INT_MAX);
	std::default_random_engine generator;

	// insert uniformly distributed data
	for (int i = 0; i < num_opr; i++) {
		insert_data.push_back(distribution(generator));
		lookup_key.push_back(distribution(generator));
	}

	for (int n_page = 1; n_page <= 64; n_page *= 2) {
		int buffer_size = param.page_size * n_page;
		cout << "run size (n times of page size): " << n_page << " ------------------------------------------------" << endl;
		LSM<K, V> lsm(buffer_size, param.page_size, param.max_level, param.runs_per_level, param.FP_rate);
		cout << "insert start" << endl;
		start = GetTickCount();
		for (int i = 0; i < num_opr; i++) {
			if (i % param.printout_num == 0) {
				finish = GetTickCount();
				cout << "stage: " << i << " : time cost: " << finish - start << endl;
			}

			lsm.insert(insert_data[i], i);
		}
		finish = GetTickCount();
		cout << "insert finish" << endl;
		cout << "time cost " << finish - start << "ms" << endl;

		cout << "lookup start" << endl;
		start = GetTickCount();
		for (int i = 0; i < num_opr; i++) {
			if (i % param.printout_num == 0) {
				finish = GetTickCount();
				cout << "stage: " << i << " : time cost: " << finish - start << endl;
			}

			lsm.lookup(lookup_key[i]);
		}
		cout << "lookup finish" << endl;
		cout << "time cost " << finish - start << "ms" << endl;

		lsm.clearfiles();
	}
}

template<typename K, typename V>
void throughputTest(LSMParams param, int num_opr){
	DWORD start, finish;
	vector<int> insert_data, lookup_key;
	std::uniform_int_distribution<int> distribution(INT_MIN + 1, INT_MAX);
	std::default_random_engine generator;

	// insert uniformly distributed data
	for (int i = 0; i < num_opr; i++) {
		insert_data.push_back(distribution(generator));
		lookup_key.push_back(distribution(generator));
	}

	for (double lookup_ratio = 0.1; lookup_ratio < 1.01; lookup_ratio += 0.1) {
		cout << "lookup ratio: " << lookup_ratio << " ------------------------------------------------" << endl;
		LSM<K, V> lsm(param.buffer_size, param.page_size, param.max_level, param.runs_per_level, param.FP_rate);
		cout << "lookup + insert start" << endl;
		start = GetTickCount();
		for (int i = 0; i < num_opr; i++) {
			if (i % param.printout_num == 0) {
				finish = GetTickCount();
				cout << "stage: " << i << " : time cost: " << finish - start << endl;
			}
			
			if ((i % 10) / 10.0 <= lookup_ratio)
				lsm.insert(insert_data[i], i);
			else
				lsm.lookup(lookup_key[i]);
		}
		finish = GetTickCount();
		cout << "lookup + insert finish" << endl;

		cout << "time cost " << finish - start << "ms" << endl;

		lsm.clearfiles();
	}
}

template<typename K, typename V>
void bloomfilterTest(LSMParams param, int num_insert) {

	DWORD start, finish;
	vector<int> insert_data, lookup_key;
	std::uniform_int_distribution<int> distribution(INT_MIN + 1, INT_MAX);
	std::default_random_engine generator;

	// insert uniformly distributed data
	for (int i = 0; i < num_insert; i++) {
		insert_data.push_back(distribution(generator));
		lookup_key.push_back(distribution(generator));
	}

	for (double fp_rate = 0.1; fp_rate < 1.01; fp_rate += 0.1) {
		cout << "FP rate: " << fp_rate << " ------------------------------------------------" << endl;
		LSM<K, V> lsm(param.buffer_size, param.page_size, param.max_level, param.runs_per_level, fp_rate);
		cout << "insert start" << endl;
		start = GetTickCount();
		for (int i = 0; i < num_insert; i++) {
			if (i % param.printout_num == 0) {
				finish = GetTickCount();
				cout << "stage: " << i << " : time cost: " << finish - start << endl;
			}
			lsm.insert(insert_data[i], i);
		}
		finish = GetTickCount();
		cout << "insert finish" << endl;

		cout << "time cost " << finish - start << "ms" << endl;


		cout << "random lookup start" << endl;
		start = GetTickCount();
		Pair<K, V> pair;
		for (int i = 0; i < num_insert; i++) {
			if (i % param.printout_num == 0) {
				finish = GetTickCount();
				cout << "stage: " << i << " : time cost: " << finish - start << endl;
			}

			pair = lsm.lookup(lookup_key[i]);
		}
		finish = GetTickCount();
		cout << "sequential lookup finish" << endl;

		lsm.clearfiles();
	}
}

template<typename K, typename V>
void performanceTest(LSMParams param, int num_insert, int num_lookup) {
	LSM<K, V> lsm(param.buffer_size, param.page_size, param.max_level, param.runs_per_level, param.FP_rate);

	DWORD start, finish;
	vector<int> insert_data;
	std::uniform_int_distribution<int> distribution(INT_MIN + 1, INT_MAX);
	std::default_random_engine generator;

	// insert uniformly distributed data
	for (int i = 0; i < num_insert; i++) {
		insert_data.push_back(distribution(generator));
	}

	cout << "insert start" << endl;
	start = GetTickCount();
	for (int i = 0; i < num_insert; i++) {
		if (i % param.printout_num == 0) {
			finish = GetTickCount();
			cout << "stage: " << i << " : time cost: " << finish - start << endl;
		}
		lsm.insert(insert_data[i], i);
	}
	finish = GetTickCount();
	cout << "insert finish" << endl;

	cout << "time cost " <<  finish - start << "ms" << endl;


	cout << "sequential lookup start" << endl;
	start = GetTickCount();
	Pair<K, V> pair;
	for (int i = 0; i < num_lookup; i++) {
		if (i % param.printout_num == 0) {
			finish = GetTickCount();
			cout << "stage: " << i << " : time cost: " << finish - start << endl;
		}

		if (i < num_insert) {
			pair = lsm.lookup(insert_data[i]);
		}
		//  some random lookup value (test not found cost)
		else {
			pair = lsm.lookup(distribution(generator));
		}
	}
	finish = GetTickCount();
	cout << "sequential lookup finish" << endl;


	cout << "time cost " <<  finish - start << "ms" << endl;



	// update -> insert same keys with different values
	cout << "update start" << endl;
	start = GetTickCount();
	for (int i = 0; i < num_insert; i++) {
		if (i % param.printout_num == 0) {
			finish = GetTickCount();
			cout << "stage: " << i << " : time cost: " << finish - start << endl;
		}

		lsm.insert(insert_data[i], -1);
	}
	finish = GetTickCount();
	cout << "insert finish" << endl;

	// check if uodated -> current values are equal to -1
	cout << "validation.." << endl;
	for (int i = 0; i < num_insert; i++) {
		pair = lsm.lookup(insert_data[i]);
		if (pair.value != -1)
			break;
	}

	/* TODO: size should not change */

	if (pair.value != -1)
		cout << "validation fails" << endl;
	else
		cout << "validation succeeds" << endl;


	cout << "time cost " <<  finish - start << "ms" << endl;



	// delete -> delete all values
	cout << "delete start" << endl;
	start = GetTickCount();
	for (int i = 0; i < num_insert; i++) {
		if (i % param.printout_num == 0) {
			finish = GetTickCount();
			cout << "stage: " << i << " : time cost: " << finish - start << endl;
		}

		lsm.delete_key(insert_data[i]);
	}
	finish = GetTickCount();
	cout << "insert finish" << endl;

	// check if deleted -> push new data in
	cout << "validation.." << endl;
	for (int i = 0; i < num_insert; i++) {
		pair = lsm.lookup(insert_data[i]);
		if (pair.value != TOMBSTONE)
			break;
	}

	if (pair.value != TOMBSTONE)
		cout << "validation fails" << endl;
	else

		cout << "validation succeeds" << endl;


	cout << "time cost " <<  finish - start << "ms" << endl;

}

template<typename K, typename V>
void rangeSearchTest(LSMParams param, int num_insert, int range_min, int range_max) {
	LSM<K, V> lsm(param.buffer_size, param.page_size, param.max_level, param.runs_per_level, param.FP_rate);

	DWORD start, finish;
	vector<int> insert_data;

	// insert uniformly distributed data
	for (int i = range_min; i < range_max; i++) {
		insert_data.push_back(i);
	}

	cout << "insert start" << endl;
	start = GetTickCount();
	for (int i = range_min; i < range_max; i++) {
		if (i % param.printout_num == 0) {
			finish = GetTickCount();
			cout << "stage: " << i << " : time cost: " << finish - start << endl;
		}

		lsm.insert(insert_data[i], i);
	}
	finish = GetTickCount();
	cout << "insert finish" << endl;


	cout << "time cost " << finish - start << "ms"<< endl;


	cout << "range search start" << endl;
	start = GetTickCount();
	vector< Pair<K, V> > search = lsm.range(range_min, range_max);
	cout << "range search finish" << endl;
	finish = GetTickCount();

	cout << "validation.." << endl;

	for (int i = 0; i < num_insert; i++) {
		lsm.insert(insert_data[i], i);
	}

	/* TODO: size should not change */
	int return_size = (int)(lsm.range(range_min, range_max)).size();

	if (return_size != range_max - range_min)
		cout << "validation fails" << endl;
	else
		cout << "validation succeeds" << endl;

	cout << "time cost " <<  finish - start << "ms" << endl;
}

#pragma once

#include "Run.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

template<typename K, typename V>
class DiskRun : Run<K, V> {
    typedef KV_pair Pair<K,V>;
	DiskRun(int capacity, int pagesize, int level, int run_No, vector<KV_pair> buff){
	    char dir[] = "LSM_L"+to_string(level)+"_R"+to_string(run)+".run";
	    fstream file(dir, ios::out | ios::binary);
	    if(!file.open()){
            cout<<"Cannot Open File\n";
	    }
	}
public:
	void insert(KV_pair kv);
	KV_pair* lookup(K key) = 0;
	vector<KV_pair> rangeSearch(K key_min, K key_max);
	void deleteKey(K key);

private:
    int capacity;
    int pagesize;
    int level;
    int run_No;
	void merge();
};

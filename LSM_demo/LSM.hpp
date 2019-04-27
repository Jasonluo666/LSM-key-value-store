#pragma once

#include "Run.hpp"
#include "buffer.hpp"
#include "DiskRun.hpp"
#include "Vector"
#include "BloomFilter.hpp"

template<typename K, typename V>
class LSM {
private:
    typedef Pair<K,V> KV_pair;
    Buffer<K,V>* buff;
    DiskRun<K,V>* runs;
    int buffer_size;
    int max_level;
    int runs_per_level;
    int page_size;

	// sort two sorted arrays
	vector<KV_pair> trickySort(vector<KV_pair> new_vec, vector<KV_pair> old_vec) {
		int pointer1 = 0, pointer2 = 0;
		vector<KV_pair> merged;

		// two pointers scan thru the vectors
		while (pointer1 < new_vec.size() && pointer2 < old_vec.size()) {
			if (new_vec[pointer1] < old_vec[pointer2]) {
				merged.push_back(new_vec[pointer1]);
				pointer1 += 1;
			}
			else if (new_vec[pointer1] > old_vec[pointer2]) {
				merged.push_back(old_vec[pointer2]);
				pointer2 += 1;
			}
			else {	// equal -> check if it's TOMBSTONE
				if (new_vec[pointer1].value != TOMBSTONE)
					merged.push_back(new_vec[pointer1]);

				pointer1 += 1;
				pointer2 += 1;
			}
		}

		// append the leftover
		if (pointer1 < new_vec.size())
			merged.insert(merged.end(), new_vec.begin() + pointer1, new_vec.end());
		// append the leftover
		if (pointer2 < old_vec.size())
			merged.insert(merged.end(), old_vec.begin() + pointer2, old_vec.end());

		return merged;
	}

public:
    LSM(){

    }

    LSM(int buffer_size, int page_size, int max_level, int runs_per_level){
        this->buffer_size = buffer_size;
        this->page_size = page_size;
        this->max_level = max_level;
        this->runs_per_level = runs_per_level;
        buff = new Buffer<K, V>(buffer_size/sizeof(KV_pair));
        runs = new DiskRun<K,V>[max_level];
    }

	void insert(K key, V value) {
	    buff.insert(Pair<K,V>(key,value));
	    if(buff.isfull()){
            for(int i = 0; i < max_level; i++){
                if(!runs[i].doExist){
                    ;
                }
            }
	    }
	}

	vector<Pair<K, V> > range(K key_min, K key_max) {

	}
	void delete_key(K key) {

	}
	Pair<K,V>* lookup(K key) {

	}
};

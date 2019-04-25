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
    Buffer<K,V> buff;
    DiskRun<K,V>* runs;
    int buffer_size;
    int max_level;
    int runs_per_level;
    int page_size;
public:

    LSM(){
    }

    LSM(int buffer_size, int page_size, int max_level, int runs_per_level){
        this->buffer_size = buffer_size;
        this->page_size = page_size;
        this->max_level = max_level;
        this->runs_per_level = runs_per_level;
        buff.Buffer(buffer_size/sizeof(KV_pair));
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

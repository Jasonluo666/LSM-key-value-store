#pragma once
#include <vector>

using namespace std;

template <typename K, typename V>
struct Pair {
	K key;
	V value;
  
	bool operator == (Pair kv) const {
		return kv.key == key and kv.value == value;
	}

	bool operator > (Pair kv) const {
		return key > kv.key;
	}

	bool operator < (Pair kv) {
		return key < kv.key;
	}
};

template <typename K, typename V>
class Run {
public:
    Run() {

	}
	virtual void insert(Pair<K,V> kv) = 0;
	virtual Pair<K,V>* lookup(K key) = 0;
	virtual vector<Pair<K,V> > rangeSearch(K key_min, K key_max) = 0;
	virtual void deleteKey(K key) = 0;

private:
	virtual void merge() = 0;
};


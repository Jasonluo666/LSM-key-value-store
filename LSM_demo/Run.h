#pragma once

template <typename K, typename V>
struct Pair {
	K key;
	V value;

	bool operator == (Pair kv) const {
		return kv.key == key and kv.value == value;
	}

	bool operator > (Pair kv) const {
		return kv.key > key;
	}

	bool operator < (Pair kv) {
		return kv.key < key;
	}
};

template <typename K, typename V>
class Run {
	Run() {

	}

public:
	virtual void insert(Pair kv) = 0;
	virtual void lookup(K key) = 0;
	virtual void rangeSearch(K key_min, K key_max) = 0;
	virtual void deleteKey(K key) = 0;

private:
	virtual void merge() = 0;
};


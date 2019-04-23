#pragma once

template <typename K, typename V>
struct Pair {
	K key;
	V value;

	Pair() {

	}

	Pair(K key, V value) {
		this->key = key;
		this->value = value;
	}

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
	typedef KV_pair Pair<K, V>;
	virtual void merge() = 0;
public:
	Run();
	virtual void insert(KV_pair kv) = 0;
	virtual void lookup(K key) = 0;
	virtual void rangeSearch(K key_min, K key_max) = 0;
	virtual void deleteKey(K key) = 0;
};


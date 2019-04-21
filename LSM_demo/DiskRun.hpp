#pragma once

#include "Run.h"

template<typename K, typename V>
class DiskRun : Run<K, V> {
	DiskRun();
public:
	void insert(Pair kv);
	void lookup(K key) = 0;
	void rangeSearch(K key_min, K key_max);
	void deleteKey(K key);

private:
	void merge();
};
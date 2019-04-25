#pragma once
#include "iostream"
#include "vector"
#include <unordered_map>
using namespace std;

template<typename K>
class BloomFilter {
	int size;
	vector<bool> filter;
	int n_hash;
	hash<K> hash_func1;
	hash<size_t> hash_func2;
public:
	BloomFilter(int n_item, double fp_rate) {	// initialize the bloom filter
		size = (int) -n_item * log(fp_rate) / 0.480453;
		n_hash = size / n_item * 0.693147;

		filter = vector<bool>(size);
	}

	void addKey(K key) {
		size_t current_hash = hash_func1(key);

		for (int n = 0; n < n_hash; n++) {
			filter[current_hash % size] = true;
			current_hash = hash_func2(current_hash);
		}
	}

	bool contain(K key) {
		size_t current_hash = hash_func1(key);

		for (int n = 0; n < n_hash; n++) {
			if (m_bits[current_hash % size] != true)
				return false;

			current_hash = hash_func2(current_hash);
		}
				
		return true;
	}
};
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
	BloomFilter(int n_item, double fp_rate) {
		size = (int) -n_item * log(fp_rate) / 0.480453;
		n_hash = size / n_item * 0.693147;

		filter = vector<bool>(size);
	}

	void addKey(K key) {
		size_t hash1 = hash_func1(key);
		size_t hash2 = hash_func2(hash1);

		for (int n = 0; n < n_hash; n++)
			m_bits[(hash1 + n * hash2) % size] = true;
	}

	bool contain(K key) {
		size_t hash1 = hash_func1(key);
		size_t hash2 = hash_func2(hash1);

		for (int n = 0; n < n_hash; n++)
			if (m_bits[(hash1 + n * hash2) % size] != true)
				return false;
		return true;
	}
};
#pragma once
#include "iostream"
#include "vector"
#include <unordered_map>
#include <cmath>
#include <stdio.h>

using namespace std;

class bitmap {
	char* bits;
public:
	bitmap(int size) {
		bits = (char*)malloc(sizeof(char) * (size / 8 + (!!(size % 8))));
		memset(bits, 0, sizeof(char) * (size / 8 + (!!(size % 8))));
	}

	void toggle_bit(int index) {
		bits[index / 8] ^= 1 << (index % 8);
	}

	char get_bit(int index) {
		return 1 & (bits[index / 8] >> (index % 8));
	}
};

template<typename K>
class BloomFilter {
	int size;
	bitmap* filter;
	int n_hash;
	hash<K> hash_func1;
	hash<size_t> hash_func2;
public:
	int get_size() { return size; }
	BloomFilter(int n_item, double fp_rate) {	// initialize the bloom filter
		if (fp_rate < 1.0)
			size = (int)-n_item * log(fp_rate) / 0.480453;
		else
			size = 0;
		n_hash = size / n_item * 0.693147;

		filter = new bitmap(size);
		//clearit();
	}

	void addKey(K key) {
		size_t current_hash = hash_func1(key);

		for (int n = 0; n < n_hash; n++) {
			filter->toggle_bit(current_hash % size);
			current_hash = hash_func2(current_hash);
		}
	}

	void clearit(){
		free(filter);
		filter = new bitmap(size);
	}

	bool contain(K key) {
		size_t current_hash = hash_func1(key);

		for (int n = 0; n < n_hash; n++) {
			if (filter->get_bit(current_hash % size) != true)
				return false;

			current_hash = hash_func2(current_hash);
		}

		return true;
	}
};

#pragma once
#include "iostream"
#include "fstream"
#include "Run.h"
using namespace std;

template<typename K, typename V>
class DiskRun : Run<K, V> {
	typedef KV_pair Pair<K, V>;
	void merge();
	int page_num;
	int page_size;
	K* fence_pointer;
	K MAX;
	string dir;
	
public:
	DiskRun() {

	}

	void insert(KV_pair kv) {

	}
	void lookup(K key) {

	}

	vector<KV_pair> rangeSearch(K key_min, K key_max) {
		vector<KV_pair> kv_pairs;
		fstream run;
		K buffer_key;
		V buffer_value;

		if (key_min <= MAX && key_max >= fence_pointer[0]) {
			run.open(dir.c_str(), ios::in | ios::binary);

			for (int page_index; page_index < page_num; page_index++) {
				if (key_min <= fence_pointer[page_index + 1] && key_max >= fence_pointer[page_index]) {
					// read page [index * page_size, index * page_size + page_size]
					
					// switch the read pointer
					streampos current_pos = index * page_size;
					run.seekg(current_pos);
					while(current_pos + sizeof(K) + sizeof(V) <= index * page_size + page_size){
						// read K, V value
						run.read((char*)&buffer_key, sizeof(K));
						run.read((char*)&buffer_value, sizeof(V));
						
						// fetch valid data
						if (buffer_key >= key_min && buffer_key <= key_max) {
							KV_pair new_pair(buffer_key, buffer_value);
							kv_pairs.push_back(new_pair);
						}

						current_pos = run.tellg();
					}

				}
			}

			if (key_min <= MAX && key_max >= fence_pointer[page_num]) {
				// read page [page_num * page_size, page_num * page_size + page_size]
				// get the tail position
				myfile.seekg(0, ios::end);
				int tail = run.tellg();

				// switch the read pointer
				streampos current_pos = page_num * page_size;
				run.seekg(current_pos);
				while (current_pos + sizeof(K) + sizeof(V) <= tail) {
					// read K, V value
					run.read((char*)&buffer_key, sizeof(K));
					run.read((char*)&buffer_value, sizeof(V));

					// fetch valid data
					if (buffer_key >= key_min && buffer_key <= key_max) {
						KV_pair new_pair(buffer_key, buffer_value);
						kv_pairs.push_back(new_pair);
					}

					current_pos = run.tellg();
				}
			}
		}

		return kv_pairs;
	};

	void deleteKey(K key) {

	}
};
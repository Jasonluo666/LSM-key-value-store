#pragma once
#include "Run.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string to_String(int n)
{
    const int max = 100;
    int m = n;
    char s[max];
    char ss[max];
    int i=0,j=0;
    if (n < 0)
    {
        m = 0 - m;
        j = 1;
        ss[0] = '-';
    }
    while (m>0)
    {
        s[i++] = m % 10 + '0';
        m /= 10;
    }
    s[i] = '\0';
    i = i - 1;
    while (i >= 0)
    {
        ss[j++] = s[i--];
    }
    ss[j] = '\0';
    return ss;
}

template<typename K, typename V>
class DiskRun : Run<K, V> {
  typedef Pair<K, V> KV_pair;
  int capacity;
  int entries_in_page;
  int level;
  int run_No;
  int entries_num;
	int page_num;
	int page_size;
	bool doExist;
	K* fence_pointer;
	K MIN;
	K MAX;
	string dir;

public:
	DiskRun() {

	}

	DiskRun(int capacity, int pagesize, int level, int run_No){
	    MIN = 0;
	    MAX = 0;
	    dir = "./data/LSM_L"+to_String(level)+"_R"+to_String(run_No)+".run";
	    this->capacity = capacity;
	    this->page_size = pagesize;
	    this->level = level;
	    this->run_No = run_No;
	    doExist = false;
	}

	void insert(KV_pair kv) {

	}

	bool overlimit(){
	    return entries_num >= capacity;
	}

	bool overlimit(int n){
	    return entries_num + n >= capacity;
	}

	KV_pair* lookup(K key){
	    int i;
	    KV_pair *aPair = new KV_pair;
	    if(key >= MIN && key <= MAX)
	    for(i=0; i<page_num; i++){
	        if( (i==page_num-1 && key >= fence_pointer[i] && key <= MAX) || (key >= fence_pointer[i] && key < fence_pointer[i+1] )){
	            break;
            }
	    }
	    if(i==page_num)return NULL;
	    vector<KV_pair> KV_pairs(this->load(i));
	    for(i=0;i<(int)KV_pairs.size();i++){
            if(KV_pairs[i].key == key){
                aPair->key = KV_pairs[i].key;
                aPair->value = KV_pairs[i].value;
                return aPair;
            }
	    }
	    return NULL;
	}

	vector<KV_pair> rangeSearch(K key_min, K key_max) {
		vector<KV_pair> kv_pairs;
		fstream run;
		K buffer_key;
		V buffer_value;

		if (key_min <= MAX && key_max >= fence_pointer[0]) {
			run.open(dir.c_str(), ios::in | ios::binary);

			for (int page_index = 0; page_index < page_num - 1; page_index++) {
				if (key_min <= fence_pointer[page_index + 1] && key_max >= fence_pointer[page_index]) {
					// read page [index * page_size, index * page_size + page_size]
					cout << fence_pointer[page_index];
					// switch the read pointer
					streampos current_pos = page_index * page_size;
					run.seekg(current_pos);
					while((int) current_pos + sizeof(K) + sizeof(V) <= page_index * page_size + page_size){
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

			if (key_min <= MAX && key_max >= fence_pointer[page_num - 1]) {
				// read page [page_num * page_size, page_num * page_size + page_size]
				// get the tail position
				run.seekg(0, ios::end);
				int tail = run.tellg();

				// switch the read pointer
				streampos current_pos = page_num * page_size;
				run.seekg(current_pos);
				while ((int) current_pos + sizeof(K) + sizeof(V) <= tail) {
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

	vector<KV_pair> load(){
	    vector<KV_pair> kv_pairs;
	    KV_pair aPair;
	    fstream file(dir.c_str(),ios::in||ios::binary);
	    if(!file.is_open()){
            cout<<"Cannot load\n";
	    }
	    for(;file.read((char *) &aPair, sizeof(KV_pair));){
	        kv_pairs.push_back(aPair);
	    }
	    file.close();
	    return kv_pairs;
	}

	vector<KV_pair> load(int page_i){
	    int i;
	    vector<KV_pair> kv_pairs;
	    KV_pair aPair;
	    fstream file(dir.c_str(), ios::in | ios::binary);
	    if(!file.is_open()){
            cout<<"Cannot load\n";
	    }
	    file.seekg(page_i*page_size,ios::beg);
	    for(i=page_i*entries_in_page;file.read((char *) &aPair, sizeof(KV_pair));i++){
	        if(i >= page_i*entries_in_page && i < (page_i+1)*entries_in_page){
	            kv_pairs.push_back(aPair);
	        }
	        if(i >= (page_i+1)*entries_in_page){
                break;
	        }
	    }
	    file.close();
	    return kv_pairs;
	}

	void empty(){
	    entries_num = 0;
	    doExist = false;
	    MIN = 0;
	    MAX = 0;
	    delete fence_pointer;
	}

	int get_entries_num(){
	    return this->entries_num;
	}

	void remove(){
	    entries_num = 0;
	    doExist = false;
	    MIN = 0;
	    MAX = 0;
	    delete fence_pointer;
	    remove(dir.c_str());
	}

	bool exist(){
	    return doExist;
	}

	void merge(vector<KV_pair> KV_pairs){
	    fstream file(dir.c_str(), ios::out | ios::binary);
        if(!file.is_open()){
            cout<<"Cannot Open File\n";
            return;
	    }
	    entries_num = KV_pairs.size();
	    if(entries_num > capacity){
            cout<<"Out of run capacity"<<endl;
            return;
	    }
        page_num = (entries_num * sizeof(KV_pair) / page_size);
	    if(entries_num*sizeof(KV_pair)%page_size > 0)page_num++;
	    fence_pointer = new K[page_num];
	    entries_in_page = page_size / sizeof(KV_pair);
	    MIN = KV_pairs[0].key;
	    MAX = KV_pairs[KV_pairs.size()-1].key;
	    for(int i = 0; i < (int)KV_pairs.size(); i++){
            if(i%entries_in_page==0){
                fence_pointer[i/entries_in_page] = KV_pairs[i].key;
            }
            file.write((char *) &KV_pairs[i], sizeof(KV_pair));
        }
        file.close();
    }

    void merge(){
        string newdir = "./data/LSM_L"+to_String(level+1)+"_R"+to_String(run_No)+".run";
        rename(dir.c_str(),newdir.c_str());
    }

};

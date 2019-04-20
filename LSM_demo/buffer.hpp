#ifndef _Buffer
#define _Buffer
#include <vector>

using namespace std;

template<typename Key,typename Value>
class Buffer{
public :

    typedef Pair<Key,Value> KV_pair

    Buffer(int capacity){
        this.capacity = capacity;
        elem_num = 0;
        MIN = 0;
        MAX = 0;
    }

    void insert(KV_pair kv_pair){
        int i;
        if(KV_pairs.empty()){
            MIN = kv_pair.key;
            MAX = kv_pair.key;
        }
        for(i = 0; i < elem_num; i++){
            if(KV_pairs[i].key == kv_pair.key){
                KV_pairs[i].value = kv_pair.value;
            }
        }
        if(i == elem_num){
            KV_pairs.push_back(kv_pair);
        }
        if(kv_pair.key < MIN){
            MIN = kv_pair.key;
        }
        if(kv_pair.key > MAX){
            MAX = kv_pair.key;
        }
        elem_num++;
    }

    KV_pair* lookup(Key key){
        if(key < MIN && key > MAX){
            return NULL;
        }
        for(int i = 0; i < elem_num; i++){
            if(KV_pairs[i].key == key){
                return &KV_pairs[i];
            }
        }
        return NULL;
        //disk_lookup
    }

    vector<KV_pair> range(Key k1, Key k2){
        vector<KV_pair> kv_pairs;
        if(k1 < MIN && k2 > MAX){
            return kv_pairs;
        }
        for(int i = 0; i < elem_num; i++){
            if(KV_pairs[i].key >= k1 && KV_pairs[i].key <= k2){
                kv_pairs.push_back(KV_pairs[i]);
            }
        }
        sort(kv_pairs.begin(),kv_pairs.end());
        //sort(disk_range())
        //merge();
        return kv_pairs;
    }

    void _delete(KV_pair kv_pair){
        for(int i = 0; i < elem_num; i++){
            if(KV_pairs[i].key == kv_pair.key){
                KV_pairs.erase(i);
                elem_num -=1;
                break;
            }
        }
    }

    bool isfull(){
        return elem_num == capacity;
    }

    void clear(){
        elem_num = 0;
        KV_pairs.clear();
    }

    vector<KV_pair> push(){
        return KV_pairs;
    }

private:
    vector<KV_pair> KV_pairs;
    int elem_num;//number of Key-Value pairs
    int capacity;
    unsigned int MIN;
    unsigned int MAX;
};



#endif // _Buffer
